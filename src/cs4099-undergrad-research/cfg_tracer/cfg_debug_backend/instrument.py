from parse_cfgs import parse_cfgs
import re

INST='''#include <fstream>
#include <sstream>
#include <unistd.h>
void __bbinstr(const char bbid []) {
    std::stringstream fname;
    fname << getpid() << ".bbtrace";
    std::ofstream tracefile(fname.str().c_str(), std::ofstream::app);
    tracefile << bbid << std::endl;
    return;
}'''

def bb(bbid):
    return '__bbinstr("{}")'.format(bbid)


def cmt(bbid):
    return "/*{}*/".format(bbid)


main_start = re.compile('^int\s+main.*')
for_stmt = re.compile('for\s*\(.*;.*;.*\)')
if_stmt = re.compile('if\s*\(.*\)')
while_stmt = re.compile('while\s*\(.*\)')
do_stmt = re.compile('do$')


class Visitor:
    def __init__(self, cfg):
        self.visited = set()
        self.cfg = cfg
        self.current = cfg.entry_node
        self.next_block = list(reversed(cfg.basic_blocks[self.current].successors))

    def instr_line(self, line):
        if line == '' or self.current == self.cfg.exit_node:
            return ''
        if self.current not in self.visited:
            self.visited.add(self.current)
            if '{' in line:
                return '{}{}'.format(cmt(self.current), line.replace('{', '{'+bb(self.current)+';'))
            return '{} {};{}'.format(cmt(self.current), bb(self.current), line.strip())
        return cmt(self.current) + line

    def next_bb(self):
        if self.current == self.cfg.exit_node:
            return self.current
        while self.next_block[-1] in self.visited:
            self.next_block.pop()
        self.current = self.next_block.pop()
        self.augment_next()
        return self.current

    def augment_next(self):
        self.next_block += reversed(self.cfg.basic_blocks[self.current].successors)


class RecDescInstrument:
    def __init__(self, file, visitor):
        self.f = file
        self.v = visitor
        self.newlines = [INST]
        self.line = ''
        self.next_line()
        while not main_start.match(self.line):
            self.newlines.append(self.line)
            self.next_line()
        while '{' not in self.line:
            self.newlines.append(cmt(self.v.current) + self.line)
            self.next_line()
        self.newlines.append(self.v.instr_line(self.line))
        #self.next_line()
        self.v.next_bb()
        self._block()
        # pump is primed, let's go!
        #while self.line != '':
        #    self._stmt()

    def next_line(self):
        self.line = self.f.readline().strip()
        #print('next_line:', self.line)

    def _simple_stmt(self):
        #print('_simple_stmt', self.line)
        if for_stmt.match(self.line):
            self._for()
        elif if_stmt.match(self.line):
            self._if()
        elif while_stmt.match(self.line):
            self._while()
        elif do_stmt.match(self.line):
            self._do()
        else:
            self.newlines.append(self.v.instr_line(self.line))
            self.next_line()
            #self._stmt()

    def _stmt(self):
        #while self.line != '':
        #print('_stmt', self.line)
        if self.line == '}':
            self.newlines.append(self.line)
            self.v.next_bb()
            self.next_line()
        if for_stmt.match(self.line):
            self._for()
        elif if_stmt.match(self.line):
            self._if()
        elif while_stmt.match(self.line):
            self._while()
        elif do_stmt.match(self.line):
            self._do()
        else:
            self.newlines.append(self.v.instr_line(self.line))
            self.next_line()
            #self._stmt()

    def _unbraced_stmt(self):
        #print('_unbraced_stmt', self.line)
        self.newlines.append('{')
        self._simple_stmt()
        self.newlines.append('}')

    def _block(self):
        #print('_block', self.line)
        if self.line != '{':
            self._stmt()
        else:
            self.newlines.append('{')
            self.next_line()
            while self.line != '}':
                self._stmt()
                # self.next_line()
            self.newlines.append(self.line)
            self.next_line()


    def _for(self):
        #print('_for', self.line)
        loop_parts = self.line.split(';')
        self.v.next_bb()
        loop_parts[1] = bb(self.v.current) + ',' + loop_parts[1]
        # first pred should be loop update (hopefully?)
        self.v.current = self.v.cfg.basic_blocks[self.v.current].preds[0]
        self.v.visited.add(self.v.current)
        loop_parts[2] = bb(self.v.current) + ',' + loop_parts[2]
        newline = ';'.join(loop_parts)
        self.newlines.append(newline)
        self.v.next_bb()
        self.next_line()
        oneline = self.line != '{'
        if oneline:
            self.newlines.append('{')
        self._block()
        if oneline:
            self.newlines.append('}')
        self.v.next_bb()

    def _if(self):
        #print('_if', self.line)
        if_parts = self.line.split('(', 1)
        # self.v.next_bb()
        # If statement is part of the previous bb
        if_parts[1] = bb(self.v.current) + ',' + if_parts[1]
        newline = '('.join(if_parts)
        self.newlines.append(newline)
        self.v.next_bb()
        self.next_line()
        oneline = self.line != '{'
        if oneline:
            self.newlines.append('{')
        self._block()
        if oneline:
            self.newlines.append('}')
        self.v.next_bb()

    def _while(self):
        #print('_while', self.line)
        while_parts = self.line.split('(', 1)
        self.v.next_bb()
        # If statement is part of the previous bb
        while_parts[1] = bb(self.v.current) + ',' + while_parts[1]
        self.v.visited.add(self.v.current)
        newline = '('.join(while_parts)
        self.newlines.append(newline)
        #print(newline)
        if (newline[-1] == ';'):
            return
        self.v.next_bb()
        self.next_line()
        self._block()
        self.v.next_bb()
        # While has a spare bb at the end
        self.v.next_bb()

    def _do(self):
        #print('_do', self.line)
        self.newlines.append(self.line)
        self.v.next_bb()
        self.next_line()
        self._block()
        #print(self.line)
        self.v.next_bb()
        self.v.visited.add(self.v.current)
        while_parts = self.line.split('(', 1)
        while_parts[1] = bb(self.v.current) + ',' + while_parts[1]
        self.v.visited.add(self.v.current)
        newline = '('.join(while_parts)
        self.newlines.append(newline)
        self.next_line()
        self.v.next_bb()
        self.v.next_bb()



def instrument(filename):
    # for now, assume only main!
    cfg = parse_cfgs(filename)[0]
    #print(cfg)
    v = Visitor(cfg)
    current = cfg.entry_node
    with open(filename.replace('.cfg', '.cpp')) as f:
        r = RecDescInstrument(f, v)
    return r.newlines


if __name__ == '__main__':
    ##print('\n'.join(instrument('test.cfg')))
    with open('test_instr.cpp', 'w') as f:
        f.write('\n'.join(instrument('testfiles/for_nobraces.cfg')))
    ##print(main_start.match('int main(char * argv, int argc)'))
    ##print(for_stmt.match('for(int i=0; i<10; i++)'))


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

class Visitor:
    def __init__(self, cfg):
        self.visited = set()
        self.cfg = cfg
        self.current = cfg.entry_node
        self.next_block = list(reversed(cfg.basic_blocks[self.current].successors))

    def instr_line(self, line):
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
def instrument(filename):
    # for now, assume only main!
    cfg = parse_cfgs(filename)[0]
    print(cfg)
    v = Visitor(cfg)
    current = cfg.entry_node

    newlines = [INST]
    with open(filename.replace('.cfg', '.cpp')) as f:
        line = f.readline().strip()
        while not main_start.match(line):
            newlines.append(line)
            line = f.readline().strip()
        while '{' not in line:
            newlines.append(cmt(current) + line)
            line = f.readline().strip()
        # found opening bracket for main function
        newlines.append(cmt(current) + line.replace('{', '{'+bb(current) + ';'))
        print(current)
        #current = v.next_bb()
        v.next_bb()
        advance_next = False
        for line in f:
            line = line.strip()
            if for_stmt.match(line):
                # advance the cfg
                v.next_bb()
                loop_parts = line.split(';')
                loop_parts[1] = bb(v.current) + ',' + loop_parts[1]
                # first pred should be loop update (hopefully?)
                v.current = cfg.basic_blocks[v.current].preds[0]
                v.visited.add(v.current)
                loop_parts[2] = bb(v.current) + ',' + loop_parts[2]
                newline = ';'.join(loop_parts)
                newlines.append(newline)
                v.next_bb()
            else:
                newlines.append(v.instr_line(line))
                if '}' in line:
                    v.next_bb()
    return newlines


if __name__ == '__main__':
    #print('\n'.join(instrument('test.cfg')))
    with open('test_instr.cpp', 'w') as f:
        f.write('\n'.join(instrument('test.cfg')))
    #print(main_start.match('int main(char * argv, int argc)'))
    #print(for_stmt.match('for(int i=0; i<10; i++)'))


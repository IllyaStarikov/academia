import re


main_start = re.compile('int\s+main.*')
open_repl = re.compile("\/\*:(B[0-9]+):\*\/\s*")
close_repl = re.compile("\/\*:\/(B[0-9]+):\*\/\s*")
indent_repl = re.compile("^\s+")


def htmlize(line):
    return  '<span>' + close_repl.sub('</span>', open_repl.sub('<span class="\g<1>">', line)) + '</span>'


# pre: file has been instrumented and then bbinstr calls removed with
# sed 's/__bbinstr\([^;]*\)[;,]//g'
# will look best if code has been formatted with clang-format
def instr_to_html(filename):
    with open(filename) as f:
        line = f.readline()
        while not main_start.search(line):
            line = f.readline()
        newlines = ['<div class="code">', htmlize(line.rstrip())]
        newlines += [htmlize(l.rstrip()) for l in f]
        newlines.append('</div>')
        return newlines


if __name__ == "__main__":
    with open('fmt.html', 'w') as f:
        f.write('\n'.join(instr_to_html('test_fmt.cpp')))

import sys
import os
from subprocess import run, PIPE, Popen
from parse_cfgs import parse_lines
from instrument import instrument_cpp
from instr_to_html import instr_to_html

file = sys.argv[1]
dir = os.path.dirname(file)
cfgout = run(['clang++', '-Xclang', '-analyze', '-Xclang', '-analyzer-checker=debug.DumpCFG', '-Xclang',
              '-unoptimized-cfg', '-O0', '-g', '-c', file], stderr=PIPE)
# print(cfgout.stderr.decode("utf-8").splitlines())
cfg = parse_lines(cfgout.stderr.decode("utf-8").splitlines())[0]
# print(parse_lines(cfgout.stderr.decode("utf-8").splitlines()))
with open(os.path.join(dir, 'out.cfg'), 'w') as f:
    f.write('\n'.join(cfgout.stderr.decode("utf-8").splitlines()))

newfname = file.replace('.cpp', '_instr.cpp')
html_src = file.replace('.cpp', '_html.cpp')
newcpp = instrument_cpp(file, cfg)
with open(newfname, 'w') as f:
    f.write('\n'.join(newcpp))

p1 = Popen(["sed", "s/__bbinstr\([^;]*\)[;,]//g", newfname], stdout=PIPE)
p2 = Popen(['clang-format'], stdin=p1.stdout, stdout=PIPE)

with open(html_src, 'w') as f:
    f.write('\n'.join(p2.stdout.read().decode('utf-8').split('\n')))
#p2.stdout.read().decode('utf-8').split('\n')
src_html = instr_to_html(html_src)
data={'cfg': cfg.to_json(), 'html': '\n'.join(src_html)}
print(data)

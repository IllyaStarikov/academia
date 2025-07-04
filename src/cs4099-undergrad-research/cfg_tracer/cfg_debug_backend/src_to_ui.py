import sys
import os
from subprocess import run, PIPE, Popen, DEVNULL
from parse_cfgs import parse_lines
from instrument import instrument_cpp
from instr_to_html import instr_to_html
import json

file = sys.argv[1]
dir = os.path.dirname(file)
cfgout = run(['clang++', '-Xclang', '-analyze', '-Xclang', '-analyzer-checker=debug.DumpCFG', '-Xclang',
              '-unoptimized-cfg', '-O0', '-g', '-c', file], stderr=PIPE)
# print(cfgout.stderr.decode("utf-8").splitlines())
cfg = parse_lines(cfgout.stderr.decode("utf-8").splitlines())[0]
cfg.reverse_labels()
# print(parse_lines(cfgout.stderr.decode("utf-8").splitlines()))
with open(os.path.join(dir, 'out.cfg'), 'w') as f:
    f.write('\n'.join(cfgout.stderr.decode("utf-8").splitlines()))

# newfname = file.replace('.cpp', '_instr.cpp')
newfname = os.path.join(dir, 'instr.cpp')
html_src = file.replace('.cpp', '_html.cpp')
newcpp, vars = instrument_cpp(file, cfg)
with open(newfname, 'w') as f:
    f.write('\n'.join(newcpp))

# sed = 'C:\\MinGW\\msys\\1.0\\bin\\sed'
sed = 'sed'

p1 = Popen([sed, "s/__bbinstr\([^;]*\),//g", newfname], stdout=PIPE)
p1_5 = Popen([sed, "s/__bbinstr\([^;]*\);//g"], stdin = p1.stdout, stdout=PIPE)
p2 = Popen(['clang-format'], stdin=p1_5.stdout, stdout=PIPE)

with open(html_src, 'w') as f:
    f.write('\n'.join(p2.stdout.read().decode('utf-8').split('\n')))

# get initial trace
run(['clang++', '-o', os.path.join(dir, 'initrun'), newfname], stderr=DEVNULL)
init_run = run([os.path.join(dir, 'initrun')], stdout=DEVNULL, stderr=PIPE)
init_trace = init_run.stderr.decode('utf-8').splitlines()

src_html = instr_to_html(html_src)
data={'cfg': cfg.to_json(), 'html': '\n'.join(src_html), 'vars': vars, 'init_trace': init_trace}
print(json.dumps(data))

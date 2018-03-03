import json
import sys
import os
import re
from subprocess import run, PIPE, Popen, DEVNULL


file_dir = sys.argv[1]
new_vars = json.loads(sys.argv[2])
instr_file = os.path.join(file_dir, 'instr.cpp')
out_file = os.path.join(file_dir, 'repl.cpp')
init_res = {k: re.compile('\/\*%'+k+'%\*\/.*\/\*%~'+k+'%\*\/') for k in new_vars}
with open(instr_file) as f:
    with open(out_file, 'w') as f2:
        for line in f:
            newline = line
            for var in init_res:
                newline = init_res[var].sub(new_vars[var], line)
            f2.write(newline)

run(['clang++', '-o', os.path.join(file_dir, 'replrun'), out_file], stderr=DEVNULL)
repl_run = run([os.path.join(file_dir, 'replrun')], stdout=DEVNULL, stderr=PIPE)
trace = repl_run.stderr.decode('utf-8').splitlines()

print(json.dumps({'trace': trace}))
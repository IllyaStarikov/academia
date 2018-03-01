from cfg import CFG


def parse_lines(lines):
    cfgs = []
    bblines = []
    for line in lines:
        if line is '':
            cfgs[-1].add_block(bblines)
            bblines = []
        elif not line.startswith(' '):
            cfgs.append(CFG(line))
        else:
            bblines.append(line.strip())
    return cfgs


def parse_cfgs(filename):
    cfgs = []
    with open(filename) as f:
        print(f)
    with open(filename) as f:
        cfgs = parse_lines(f)
        for line in f:
            if line is '\n':
                cfgs[-1].add_block(bblines)
                bblines = []
            elif not line.startswith(' '):
                cfgs.append(CFG(line))
            else:
                bblines.append(line.strip())
    return cfgs


if __name__ == "__main__":
    import os
    cfg = parse_cfgs('testfiles/if.cfg')
    cfg_json = cfg[0].to_json()
    import json
    with open('if.json', 'w') as f:
        json.dump(cfg_json, f)

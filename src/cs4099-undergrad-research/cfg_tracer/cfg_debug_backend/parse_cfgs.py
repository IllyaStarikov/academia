from cfg import CFG
def parse_cfgs(filename):
    cfgs = []
    with open(filename) as f:
        print(f)
    with open(filename) as f:
        bblines = []
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
    cfg = parse_cfgs('test.cfg')
    cfg[0].to_dot()
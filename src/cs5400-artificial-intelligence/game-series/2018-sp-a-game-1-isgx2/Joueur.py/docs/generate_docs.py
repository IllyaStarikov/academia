import os
import os.path
import shutil
import subprocess
import argparse
import re
import sys

def run(*args, **kwargs):
    error_code = subprocess.call(*args, **kwargs)
    if error_code != 0: # an error happened
        sys.exit(error_code)


parser = argparse.ArgumentParser(description='Runs the python 3 client doc generation script.')
parser.add_argument('game', action='store', help='the name of the game you want to document. Must exist in ../games/')

args = parser.parse_args()

game_name = args.game[0].upper() + args.game[1:]
lower_game_name = game_name[0].lower() + game_name[1:]

if os.path.isdir("./output"):
    shutil.rmtree("./output")

def camelcase(word):
    return ''.join(x.capitalize() or '_' for x in word.split('_'))

game_path = "../games/" + lower_game_name
only_files = [f for f in os.listdir(game_path) if os.path.isfile(os.path.join(game_path, f))]
game_classes = []

game_rst_path = "./classes"
if os.path.isdir(game_rst_path):
    shutil.rmtree(game_rst_path)
os.makedirs(game_rst_path)

for name in only_files:
    name = os.path.splitext(name)[0]
    cc = camelcase(name)
    not_inherit = (name == "game" or name == "game_object")

    if name == "__init__":
        continue
    elif name == "ai":
        cc = "AI"

    if not not_inherit and name != "player" and name != "ai":
        game_classes.append(name)

    with open(game_rst_path + "/" + name + ".rst", "w+") as f:
        f.write("""
{cc}
{cc_underline}

.. currentmodule:: games.{lower_game_name}.{name}

.. automodule:: games.{lower_game_name}.{name}
    :members:{extra_rest}

""".format(
    cc=cc,
    cc_underline = '=' * len(cc),
    lower_game_name=lower_game_name,
    name=name,
    extra_rest="" if not_inherit else """
    :inherited-members:
    :show-inheritance:"""
))

# replace GAME_NAME in README.md with the actual game name
with open("../README.md", "r") as f:
    readme = f.read()

readme = readme.replace("GAME_NAME", game_name).replace("game_name", lower_game_name)

with open("README.md", "w+") as f:
    f.write(readme)

# convert the readme from md to rst
run(["pandoc --from=markdown --to=rst --output=readme.rst README.md"], shell=True)

with open("readme.rst", "r") as f:
    readme_rst = f.read()

# create the conf file for sphinx
with open("_conf.py", "r") as f:
    conf = f.read()

conf = conf.replace("###GAME_NAME###", game_name)

with open("./conf.py", "w+") as f:
    f.write(conf)

with open("./index.rst", "w+") as f:
    f.truncate()
    f.write("""
{readme_rst}

Classes
=======

.. toctree::
   :maxdepth: 2
   :caption: These are all the classes you will interact with to built your AI.

   classes/ai.rst
   classes/game.rst
   classes/game_object.rst
   classes/player.rst
{game_classes}

""".format(
    game_name=game_name,
    lower_game_name=lower_game_name,
    readme_rst=readme_rst,
    game_classes="\n".join(
        "   classes/{}.rst".format(game_class) for game_class in sorted(game_classes)
    )
))

run(["sphinx-build -b html ./ ./output"], shell=True)

# cleanup files we made
shutil.rmtree(game_rst_path)
os.remove("./index.rst")
os.remove("./README.md")
os.remove("./readme.rst")
os.remove("./conf.py")

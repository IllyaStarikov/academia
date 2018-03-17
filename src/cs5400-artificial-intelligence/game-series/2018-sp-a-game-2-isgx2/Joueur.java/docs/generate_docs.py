#!/usr/bin/env python3 -B

from __future__ import print_function

import os
import os.path
import subprocess
import argparse
import shutil
import markdown # this is a pip package you'll need
from datetime import date
import sys


def run(*args, **kwargs):
    error_code = subprocess.call(*args, **kwargs)
    if error_code != 0: # an error happened
        raise Exception()

JAVA_SRC_DIR = "../src/main/java"

parser = argparse.ArgumentParser(description='Runs the java client doc generation script.')
parser.add_argument('game', action='store', help='the name of the game you want to document. Must exist in {}/games/'.format(JAVA_SRC_DIR))

args = parser.parse_args()

game_name = args.game[0].upper() + args.game[1:]
lower_game_name = game_name[0].lower() + game_name[1:]

output_path = "./output"
if os.path.isdir(output_path):
    shutil.rmtree(output_path)

with open('../README.md', 'r') as readme_file:
    readme_md = readme_file.read()

readme_md = readme_md.replace("GAME_NAME", game_name).replace("game_name", lower_game_name)

temp_path = 'temp'

shutil.copytree('{}/games/'.format(JAVA_SRC_DIR), os.path.join(temp_path, 'games'), )
shutil.copytree('{}/joueur/'.format(JAVA_SRC_DIR), os.path.join(temp_path, 'joueur'))

temp_readme_html_path = os.path.join(temp_path, 'games', lower_game_name, "package.html")

with open(temp_readme_html_path, "w+") as readme_html:
    readme_html.write("<html><head></head><body>" + markdown.markdown(readme_md) + "</body></html>")

shutil.copytree('resources', os.path.join(output_path, 'resources'))

get_settings_function = """
    /**
     * Gets an AI setting passed to the program via the `--aiSettings` flag. If the flag was set it will be returned as a string value, null otherwise.
     *
     * @param key The key of the setting you wish to get the value for
     * @return A string representing the value set via command line, or null if the key was not set
     */
    public String getSetting(String key) {
        return null; // this is just for output
    }
"""

ai_path = os.path.join(temp_path, 'games', lower_game_name, 'AI.java')
with open(ai_path, 'r') as ai_file:
    ai_lines = ai_file.readlines()

for index in reversed(range(len(ai_lines))):
    if ai_lines[index].strip() == '}':
        insert_index = index
        break

ai_lines[insert_index:insert_index] = get_settings_function

with open(ai_path, 'w+') as ai_file:
    ai_file.write(''.join(ai_lines))

try:
    run([('javadoc -d {output_path} '
        '-public '
        '-use -windowtitle "{game_name} Java Client Documentation" '
        '-header "<h1>{game_name} Java Client Documentation</h1>" '
        '-bottom "&copy; {year} MST ACM SIG-GAME" '
        '-sourcepath {temp_path} '
        '-subpackages games.{lower_game_name} ').format(
        output_path=output_path,
        game_name=game_name,
        lower_game_name=lower_game_name,
        temp_path=temp_path,
        year=date.today().year,
    )], shell=True)
except:
    print("javadoc creation had a problem")
shutil.rmtree(temp_path)

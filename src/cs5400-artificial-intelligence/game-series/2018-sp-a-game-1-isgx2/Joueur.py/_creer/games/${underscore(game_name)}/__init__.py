# DO NOT MODIFY THESE IMPORTS
from games.${underscore(game_name)}.ai import AI
from games.${underscore(game_name)}.game import Game
% for game_obj_key in sort_dict_keys(game_objs):
from games.${underscore(game_name)}.${underscore(game_obj_key)} import ${game_obj_key}
% endfor

${merge("# ", "init", "# if you need to initialize this module with custom logic do so here")}

/////////////////////////////////////////////////////
// Implementation detail!!
// Do not edit anything past here!!
/////////////////////////////////////////////////////
<%include file="functions.noCreer" />
/// \cond FALSE

#include "../ai.hpp"

namespace cpp_client
{

namespace ${underscore(game_name)}
{

<% ifstr = 'if' %>
std::string AI::invoke_by_name(const std::string& name,
                               const std::unordered_map<std::string, Any>& args)
{
% for function_name in ai['function_names']:
<% function_params = ai['functions'][function_name] %>
    ${ifstr}(name == "${function_name}")
    {
% if function_params['returns'] and 'type' in function_params['returns']:
        auto ret = ${underscore(function_name)}(
<% comma = ',' %>
% for arg_params in function_params['arguments']:
<% if arg_params == function_params['arguments'][-1]:
    comma = '' %>
            args.at("${arg_params['name']}").as<${shared['gen_base_type'](arg_params['type'])}>()${comma}
            % endfor
        );
        return attr_wrapper::json_val(ret);
% else:
        ${underscore(function_name)}(
<% comma = ',' %>
% for arg_params in function_params['arguments']:
<% if arg_params == function_params['arguments'][-1]:
    comma = '' %>
            args.at("${arg_params['name']}").as<${shared['gen_base_type'](arg_params['type'])}>()${comma}
% endfor
        );
        return "";
% endif
    }<% ifstr = 'else if' %>
% endfor;
    throw Bad_response("AI told to run unknown action " + name);
}

void AI::set_game(Base_game* ptr)
{
    game = static_cast<Game>(ptr);
}

void AI::set_player(std::shared_ptr<Base_object> obj)
{
    player = std::static_pointer_cast<Player_>(obj);
}

void AI::print_win_loss_info()
{
    if(player->lost)
    {
        ended(false, player->reason_lost);
        std::cout << sgr::text_green
                     << "Game is over. I lost :( because: " << player->reason_lost << '\n';
    }
    else
    {
        ended(true, player->reason_won);
        std::cout << sgr::text_green
                     << "Game is over. I won! because: " << player->reason_won << '\n';
    }
    std::cout << sgr::reset;
}

} // end namespace ${underscore(game_name)}

} // end namespace cpp_client

/// \endcond
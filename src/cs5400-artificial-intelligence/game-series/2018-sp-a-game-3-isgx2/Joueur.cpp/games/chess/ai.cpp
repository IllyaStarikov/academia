// AI
// This is where you build your AI

#include "ai.hpp"

#include <ctime>
#include <cstdlib>


#include <unordered_map>

// You can add #includes here for your AI.

namespace cpp_client
{

namespace chess
{

/// <summary>
/// This returns your AI's name to the game server.
/// Replace the string name.
/// </summary>
/// <returns>The name of your AI.</returns>
std::string AI::get_name() const
{
    // REPLACE WITH YOUR TEAM NAME!
    return "daddy";
}

/// <summary>
/// This is automatically called when the game first starts, once the game objects are created
/// </summary>
void AI::start()
{
    // This is a good place to initialize any variables
    srand(time(NULL));
}

/// <summary>
/// This is automatically called the game (or anything in it) updates
/// </summary>
void AI::game_updated()
{
    // If a function you call triggers an update this will be called before it returns.
}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if you won, false otherwise</param>
/// <param name="reason">An explanation for why you either won or lost</param>
void AI::ended(bool won, const std::string& reason)
{
    // You can do any cleanup of your AI here.  The program ends when this function returns.
}

/// <summary>
/// This is called every time it is this AI.player's turn.
/// </summary>
/// <returns>Represents if you want to end your turn. True means end your turn, False means to keep your turn going and re-call this function.</returns>
bool AI::run_turn()
{
    /* static std::unordered_map<std::string, Piece> pieceMappings = { */
    /*     { "King", king }, */
    /*     { "Queen", queen }, */
    /*     { "Knight", knight }, */
    /*     { "Rook", rook }, */
    /*     { "Bishop", bishop }, */
    /*     { "Pawn", pawn } */
    /* }; */

    ChessEngine::ChessAI ai(game -> fen);

    /* if (game -> moves.size() == 1 || game -> moves.size() == 2 || game -> moves.size() % 9 == 0 || game -> moves.size() % 10 == 0) { */
        /* std::cout << "RESYNC"; */
        ai.updateTimer(player -> time_remaining / 1000000000.0);
    /* } */

    /* auto opponentMove = Actio */
    auto move = ai.move();

    auto beforeMoveDescription = ChessEngine::MoveEngine::bitStringToDescription(move.pieceBefore)[0];
    auto afterMoveDescription = ChessEngine::MoveEngine::bitStringToDescription(move.pieceAfter)[0];

    int beforeMoveRank = beforeMoveDescription.second;
    std::string beforeMoveFile = std::string(1, tolower(beforeMoveDescription.first));

    int afterMoveRank = afterMoveDescription.second;
    std::string afterMoveFile = std::string(1, tolower(afterMoveDescription.first));

    std::cout << "Selecting move ";
    std::cout << "from " << beforeMoveFile << beforeMoveRank;
    std::cout << " to " << afterMoveFile << afterMoveRank << ".\n";

    // Figure out what move i am doing and do that
    for (auto& movePiece : player -> pieces) {
        if (movePiece -> rank == beforeMoveRank && movePiece -> file == beforeMoveFile) {
            auto promotionString = "";
            if (move.wasPromotion) {
                switch (move.promotedTo) {
                    case ChessEngine::queen:
                        promotionString = "queen";
                        break;

                    case ChessEngine::king:
                        promotionString = "king";
                        break;

                    case ChessEngine::knight:
                        promotionString = "knight";
                        break;

                    case ChessEngine::pawn:
                        promotionString = "pawn";
                        break;

                    case ChessEngine::rook:
                        promotionString = "rook";
                        break;

                    case ChessEngine::bishop:
                        promotionString = "bishop";
                        break;
                }
            }

            movePiece -> move(afterMoveFile, afterMoveRank, promotionString);
        }
    }

    return true; // to signify we are done with our turn.
}

/// <summary>
///  Prints the current board using pretty ASCII art
/// </summary>
/// <remarks>
/// Note: you can delete this function if you wish
/// </remarks>
void AI::print_current_board()
{
    for(int rank = 9; rank >= -1; rank--)
    {
        std::string str = "";
        if(rank == 9 || rank == 0) // then the top or bottom of the board
        {
            str = "   +------------------------+";
        }
        else if(rank == -1) // then show the ranks
        {
            str = "     a  b  c  d  e  f  g  h";
        }
        else // board
        {
            str += " ";
            str += std::to_string(rank);
            str += " |";
            // fill in all the files with pieces at the current rank
            for(int file_offset = 0; file_offset < 8; file_offset++)
            {
                std::string file(1, 'a' + file_offset); // start at a, with with file offset increasing the char;
                chess::Piece current_piece = nullptr;
                for(const auto& piece : game->pieces)
                {
                    if(piece->file == file && piece->rank == rank) // then we found the piece at (file, rank)
                    {
                        current_piece = piece;
                        break;
                    }
                }

                char code = '.'; // default "no piece";
                if(current_piece != nullptr)
                {
                    code = current_piece->type[0];

                    if(current_piece->type == "Knight") // 'K' is for "King", we use 'N' for "Knights"
                    {
                        code = 'N';
                    }

                    if(current_piece->owner->id == "1") // the second player (black) is lower case. Otherwise it's upppercase already
                    {
                        code = tolower(code);
                    }
                }

                str += " ";
                str += code;
                str += " ";
            }

            str += "|";
        }

        std::cout << str << std::endl;
    }
}

// You can add additional methods here for your AI to call

} // chess

} // cpp_client

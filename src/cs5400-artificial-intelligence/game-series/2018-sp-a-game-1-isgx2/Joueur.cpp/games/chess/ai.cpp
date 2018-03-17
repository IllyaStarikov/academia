// AI
// This is where you build your AI

#include "ai.hpp"

// <<-- Creer-Merge: includes -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add #includes here for your AI.
// <<-- /Creer-Merge: includes -->>

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
    // <<-- Creer-Merge: get-name -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // REPLACE WITH YOUR TEAM NAME!
    return "Chess C++ Player";
    // <<-- /Creer-Merge: get-name -->>
}

/// <summary>
/// This is automatically called when the game first starts, once the game objects are created
/// </summary>
void AI::start()
{
    // <<-- Creer-Merge: start -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // This is a good place to initialize any variables
    // <<-- /Creer-Merge: start -->>
}

/// <summary>
/// This is automatically called the game (or anything in it) updates
/// </summary>
void AI::game_updated()
{
    // <<-- Creer-Merge: game-updated -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // If a function you call triggers an update this will be called before it returns.
    // <<-- /Creer-Merge: game-updated -->>
}

/// <summary>
/// This is automatically called when the game ends.
/// </summary>
/// <param name="won">true if you won, false otherwise</param>
/// <param name="reason">An explanation for why you either won or lost</param>
void AI::ended(bool won, const std::string& reason)
{
    //<<-- Creer-Merge: ended -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // You can do any cleanup of your AI here.  The program ends when this function returns.
    //<<-- /Creer-Merge: ended -->>
}

/// <summary>
/// This is called every time it is this AI.player's turn.
/// </summary>
/// <returns>Represents if you want to end your turn. True means end your turn, False means to keep your turn going and re-call this function.</returns>
bool AI::run_turn()
{
    // <<-- Creer-Merge: runTurn -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
    // Put your game logic here for run_turn here
    // <<-- /Creer-Merge: runTurn -->>
    ChessAI ai(game -> fen);

    auto moves = ChessAI::actions(ai.currentState);
    for (const auto move : moves) {
        if (move.color == white) {
            std::cout << "White ";
        } else {
            std::cout << "Black ";
        }

        switch (move.piece) {
            case queen:
                std::cout << "Queen ";
                break;

            case king:
                std::cout << "King ";
                break;

            case knight:
                std::cout << "Knight ";
                break;

            case pawn:
                std::cout << "Pawn ";
                break;

            case rook:
                std::cout << "Rook ";
                break;

            case bishop:
                std::cout << "Bishop ";
                break;
        }

        std::cout << "from " << ChessEngine::bitStringToDescription(move.pieceBefore)[0].first << ChessEngine::bitStringToDescription(move.pieceBefore)[0].second;
        std::cout << " to " << ChessEngine::bitStringToDescription(move.pieceAfter)[0].first << ChessEngine::bitStringToDescription(move.pieceAfter)[0].second;
        std::cout << "\n";
    }

    // Random Choice
    auto randomIterator = moves.begin();
    std::advance(randomIterator, std::rand() % moves.size());
    auto move = randomIterator[0];

    auto beforeMoveDescription = ChessEngine::bitStringToDescription(move.pieceBefore)[0];
    auto afterMoveDescription = ChessEngine::bitStringToDescription(move.pieceAfter)[0];

    int beforeMoveRank = beforeMoveDescription.second;
    std::string beforeMoveFile = std::string(1, tolower(beforeMoveDescription.first));

    int afterMoveRank = afterMoveDescription.second;
    std::string afterMoveFile = std::string(1, tolower(afterMoveDescription.first));

    std::cout << "\nSelecting Move ";
    std::cout << "from " << beforeMoveFile << beforeMoveRank;
    std::cout << " to " << afterMoveFile << afterMoveRank;
    std::cout << "\n\n";

    // Figure out what move i am doing and do that
    for (auto& movePiece : player -> pieces) {
        if (movePiece -> rank == beforeMoveRank && movePiece -> file == beforeMoveFile) {
            auto promotionString = "";
            if (move.wasPromotion) {
                switch (move.promotedTo) {
                    case queen:
                        promotionString = "queen";
                        break;

                    case king:
                        promotionString = "king";
                        break;

                    case knight:
                        promotionString = "knight";
                        break;

                    case pawn:
                        promotionString = "pawn";
                        break;

                    case rook:
                        promotionString = "rook";
                        break;

                    case bishop:
                        promotionString = "bishop";
                        break;
                }
            }

            movePiece -> move(afterMoveFile, afterMoveRank, promotionString);
        }
    }

    auto state = ai.currentState;
    ai.currentState = ChessAI::result(state, move);

    moves = ChessAI::actions(ai.currentState);
    for (const auto move : moves) {
        if (move.color == white) {
            std::cout << "White ";
        } else {
            std::cout << "Black ";
        }

        switch (move.piece) {
            case queen:
                std::cout << "Queen ";
                break;

            case king:
                std::cout << "King ";
                break;

            case knight:
                std::cout << "Knight ";
                break;

            case pawn:
                std::cout << "Pawn ";
                break;

            case rook:
                std::cout << "Rook ";
                break;

            case bishop:
                std::cout << "Bishop ";
                break;
        }

        std::cout << "from " << ChessEngine::bitStringToDescription(move.pieceBefore)[0].first << ChessEngine::bitStringToDescription(move.pieceBefore)[0].second;
        std::cout << " to " << ChessEngine::bitStringToDescription(move.pieceAfter)[0].first << ChessEngine::bitStringToDescription(move.pieceAfter)[0].second;
        std::cout << "\n";
    }


    return true;
}

//<<-- Creer-Merge: methods -->> - Code you add between this comment and the end comment will be preserved between Creer re-runs.
// You can add additional methods here for your AI to call
//<<-- /Creer-Merge: methods -->>

} // chess

} // cpp_client

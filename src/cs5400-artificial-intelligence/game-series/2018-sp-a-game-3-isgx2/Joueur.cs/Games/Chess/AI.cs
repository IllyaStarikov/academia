// This is where you build your AI for the Chess game.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Joueur.cs.Games.Chess
{
    /// <summary>
    /// This is where you build your AI for the Chess game.
    /// </summary>
    class AI : BaseAI
    {
        #region Properties
#pragma warning disable 0169 // the never assigned warnings between here are incorrect. We set it for you via reflection. So these will remove it from the Error List.
#pragma warning disable 0649
        /// <summary>
        /// This is the Game object itself, it contains all the information about the current game
        /// </summary>
        public readonly Chess.Game Game;
        /// <summary>
        /// This is your AI's player. This AI class is not a player, but it should command this Player.
        /// </summary>
        public readonly Chess.Player Player;
#pragma warning restore 0169
#pragma warning restore 0649
        #endregion


        #region Methods
        /// <summary>
        /// This returns your AI's name to the game server. Just replace the string.
        /// </summary>
        /// <returns>string of you AI's name.</returns>
        public override string GetName()
        {
            return "Chess C# Player"; // REPLACE THIS WITH YOUR TEAM NAME!
        }

        /// <summary>
        /// This is automatically called when the game first starts, once the Game object and all GameObjects have been initialized, but before any players do anything.
        /// </summary>
        /// <remarks>
        /// This is a good place to initialize any variables you add to your AI, or start tracking game objects.
        /// </remarks>
        public override void Start()
        {
            base.Start();
        }

        /// <summary>
        /// This is automatically called every time the game (or anything in it) updates.
        /// </summary>
        /// <remarks>
        /// If a function you call triggers an update this will be called before that function returns.
        /// </remarks>
        public override void GameUpdated()
        {
            base.GameUpdated();
        }

        /// <summary>
        /// This is automatically called when the game ends.
        /// </summary>
        /// <remarks>
        /// You can do any cleanup of you AI here, or do custom logging. After this function returns the application will close.
        /// </remarks>
        /// <param name="won">true if your player won, false otherwise</param>
        /// <param name="reason">a string explaining why you won or lost</param>
        public override void Ended(bool won, string reason)
        {
            base.Ended(won, reason);
        }


        /// <summary>
        /// This is called every time it is this AI.player's turn.
        /// </summary>
        /// <returns>Represents if you want to end your turn. True means end your turn, False means to keep your turn going and re-call this function.</returns>
        public bool RunTurn()
        {
            // Here is where you'll want to code your AI.

            // We've provided sample code that:
            //    1) prints the board to the console
            //    2) prints the opponent's last move to the console
            //    3) prints how much time remaining this AI has to calculate moves
            //    4) makes a random (and probably invalid) move.

            // 1) print the board to the console
            this.PrintCurrentBoard();

            // 2) print the opponent's last move to the console
            if (this.Game.Moves.Count > 0)
            {
                Console.WriteLine("Opponent's Last Move: '" + this.Game.Moves.Last().San + "'");
            }

            // 3) print how much time remaining this AI has to calculate moves
            Console.WriteLine("Time Remaining: " + this.Player.TimeRemaining + " ns");

            // 4) make a random (and probably invalid) move.
            var rand = new Random();
            var randomPiece = this.Player.Pieces[rand.Next(this.Player.Pieces.Count)];
            string randomFile = "" + (char)(((int)"a"[0]) + rand.Next(0, 8));
            int randomRank = rand.Next(0, 8) + 1;
            randomPiece.Move(randomFile, randomRank);

            return true; // to signify we are done with our turn.
        }

        /// <summary>
        /// Prints the current board using pretty ASCII art
        /// </summary>
        /// <remarks>
        /// Note: you can delete this function if you wish
        /// </remarks>
        public void PrintCurrentBoard()
        {
            for (int rank = 9; rank >= -1; rank--)
            {
                string str = "";
                if (rank == 9 || rank == 0) // then the top or bottom of the board
                {
                    str = "   +------------------------+";
                }
                else if (rank == -1) // then show the ranks
                {
                    str = "     a  b  c  d  e  f  g  h";
                }
                else // board
                {
                    str += " " + rank + " |";
                    // fill in all the files with pieces at the current rank
                    for (int fileOffset = 0; fileOffset < 8; fileOffset++)
                    {
                        string file = "" + (char)(((int)"a"[0]) + fileOffset); // start at a, with with file offset increasing the char;
                        Piece currentPiece = null;
                        foreach (var piece in this.Game.Pieces)
                        {
                            if (piece.File == file && piece.Rank == rank) // then we found the piece at (file, rank)
                            {
                                currentPiece = piece;
                                break;
                            }
                        }

                        char code = '.'; // default "no piece";
                        if (currentPiece != null)
                        {
                            code = currentPiece.Type[0];

                            if (currentPiece.Type == "Knight") // 'K' is for "King", we use 'N' for "Knights"
                            {
                                code = 'N';
                            }

                            if (currentPiece.Owner.Id == "1") // the second player (black) is lower case. Otherwise it's upppercase already
                            {
                                code = Char.ToLower(code);
                            }
                        }

                        str += " " + code + " ";
                    }

                    str += "|";
                }

                Console.WriteLine(str);
            }
        }

        #endregion
    }
}

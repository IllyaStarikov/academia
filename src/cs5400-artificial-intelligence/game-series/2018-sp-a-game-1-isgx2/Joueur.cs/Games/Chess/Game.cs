// The traditional 8x8 chess board with pieces.

// DO NOT MODIFY THIS FILE
// Never try to directly create an instance of this class, or modify its member variables.
// Instead, you should only be reading its variables and calling its functions.

using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace Joueur.cs.Games.Chess
{
    /// <summary>
    /// The traditional 8x8 chess board with pieces.
    /// </summary>
    class Game : BaseGame
    {
        #region Properties
        /// <summary>
        /// The player whose turn it is currently. That player can send commands. Other players cannot.
        /// </summary>
        public Chess.Player CurrentPlayer { get; protected set; }

        /// <summary>
        /// The current turn number, starting at 0 for the first player's turn.
        /// </summary>
        public int CurrentTurn { get; protected set; }

        /// <summary>
        /// Forsyth–Edwards Notation, a notation that describes the game board.
        /// </summary>
        public string Fen { get; protected set; }

        /// <summary>
        /// The maximum number of turns before the game will automatically end.
        /// </summary>
        public int MaxTurns { get; protected set; }

        /// <summary>
        /// The list of Moves that have occurred, in order.
        /// </summary>
        public IList<Chess.Move> Moves { get; protected set; }

        /// <summary>
        /// All the uncaptured Pieces in the game.
        /// </summary>
        public IList<Chess.Piece> Pieces { get; protected set; }

        /// <summary>
        /// List of all the players in the game.
        /// </summary>
        public IList<Chess.Player> Players { get; protected set; }

        /// <summary>
        /// A unique identifier for the game instance that is being played.
        /// </summary>
        public string Session { get; protected set; }

        /// <summary>
        /// How many turns until the game ends because no pawn has moved and no Piece has been taken.
        /// </summary>
        public int TurnsToDraw { get; protected set; }

        #endregion


        #region Methods
        /// <summary>
        /// Creates a new instance of Game. Used during game initialization, do not call directly.
        /// </summary>
        protected Game() : base()
        {
            this.Name = "Chess";

            this.Moves = new List<Chess.Move>();
            this.Pieces = new List<Chess.Piece>();
            this.Players = new List<Chess.Player>();
        }

        #endregion
    }
}

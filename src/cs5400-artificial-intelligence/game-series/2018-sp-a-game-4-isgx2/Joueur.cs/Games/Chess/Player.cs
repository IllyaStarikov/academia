// A player in this game. Every AI controls one player.

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
    /// A player in this game. Every AI controls one player.
    /// </summary>
    class Player : Chess.GameObject
    {
        #region Properties
        /// <summary>
        /// What type of client this is, e.g. 'Python', 'JavaScript', or some other language. For potential data mining purposes.
        /// </summary>
        public string ClientType { get; protected set; }

        /// <summary>
        /// The color (side) of this player. Either 'White' or 'Black', with the 'White' player having the first move.
        /// </summary>
        public string Color { get; protected set; }

        /// <summary>
        /// True if this player is currently in check, and must move out of check, false otherwise.
        /// </summary>
        public bool InCheck { get; protected set; }

        /// <summary>
        /// If the player lost the game or not.
        /// </summary>
        public bool Lost { get; protected set; }

        /// <summary>
        /// If the Player has made their move for the turn. true means they can no longer move a Piece this turn.
        /// </summary>
        public bool MadeMove { get; protected set; }

        /// <summary>
        /// The name of the player.
        /// </summary>
        public string Name { get; protected set; }

        /// <summary>
        /// This player's opponent in the game.
        /// </summary>
        public Chess.Player Opponent { get; protected set; }

        /// <summary>
        /// All the uncaptured chess Pieces owned by this player.
        /// </summary>
        public IList<Chess.Piece> Pieces { get; protected set; }

        /// <summary>
        /// The direction your Pieces must go along the rank axis until they reach the other side. Will be +1 if the Player is 'White', or -1 if the Player is 'Black'.
        /// </summary>
        public int RankDirection { get; protected set; }

        /// <summary>
        /// The reason why the player lost the game.
        /// </summary>
        public string ReasonLost { get; protected set; }

        /// <summary>
        /// The reason why the player won the game.
        /// </summary>
        public string ReasonWon { get; protected set; }

        /// <summary>
        /// The amount of time (in ns) remaining for this AI to send commands.
        /// </summary>
        public double TimeRemaining { get; protected set; }

        /// <summary>
        /// If the player won the game or not.
        /// </summary>
        public bool Won { get; protected set; }

        #endregion


        #region Methods
        /// <summary>
        /// Creates a new instance of Player. Used during game initialization, do not call directly.
        /// </summary>
        protected Player() : base()
        {
            this.Pieces = new List<Chess.Piece>();
        }

        #endregion
    }
}

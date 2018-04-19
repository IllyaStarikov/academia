// Contains all details about a Piece's move in the game.

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
    /// Contains all details about a Piece's move in the game.
    /// </summary>
    class Move : Chess.GameObject
    {
        #region Properties
        /// <summary>
        /// The Piece captured by this Move, null if no capture.
        /// </summary>
        public Chess.Piece Captured { get; protected set; }

        /// <summary>
        /// The file the Piece moved from.
        /// </summary>
        public string FromFile { get; protected set; }

        /// <summary>
        /// The rank the Piece moved from.
        /// </summary>
        public int FromRank { get; protected set; }

        /// <summary>
        /// The Piece that was moved.
        /// </summary>
        public Chess.Piece Piece { get; protected set; }

        /// <summary>
        /// The Piece type this Move's Piece was promoted to from a Pawn, empty string if no promotion occurred.
        /// </summary>
        public string Promotion { get; protected set; }

        /// <summary>
        /// The standard algebraic notation (SAN) representation of the move.
        /// </summary>
        public string San { get; protected set; }

        /// <summary>
        /// The file the Piece moved to.
        /// </summary>
        public string ToFile { get; protected set; }

        /// <summary>
        /// The rank the Piece moved to.
        /// </summary>
        public int ToRank { get; protected set; }

        #endregion


        #region Methods
        /// <summary>
        /// Creates a new instance of Move. Used during game initialization, do not call directly.
        /// </summary>
        protected Move() : base()
        {
        }

        #endregion
    }
}

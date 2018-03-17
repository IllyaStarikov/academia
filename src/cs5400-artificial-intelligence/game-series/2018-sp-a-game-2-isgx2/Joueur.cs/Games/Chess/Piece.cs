// A chess piece.

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
    /// A chess piece.
    /// </summary>
    class Piece : Chess.GameObject
    {
        #region Properties
        /// <summary>
        /// When the Piece has been captured (removed from the board) this is true. Otherwise false.
        /// </summary>
        public bool Captured { get; protected set; }

        /// <summary>
        /// The file (column) coordinate of the Piece represented as a letter [a-h], with 'a' starting at the left of the board.
        /// </summary>
        public string File { get; protected set; }

        /// <summary>
        /// If the Piece has moved from its starting position.
        /// </summary>
        public bool HasMoved { get; protected set; }

        /// <summary>
        /// The player that controls this chess Piece.
        /// </summary>
        public Chess.Player Owner { get; protected set; }

        /// <summary>
        /// The rank (row) coordinate of the Piece represented as a number [1-8], with 1 starting at the bottom of the board.
        /// </summary>
        public int Rank { get; protected set; }

        /// <summary>
        /// The type of chess Piece this is, either 'King, 'Queen', 'Knight', 'Rook', 'Bishop', or 'Pawn'.
        /// </summary>
        public string Type { get; protected set; }

        #endregion


        #region Methods
        /// <summary>
        /// Creates a new instance of Piece. Used during game initialization, do not call directly.
        /// </summary>
        protected Piece() : base()
        {
        }

        /// <summary>
        /// Moves the Piece from its current location to the given rank and file.
        /// </summary>
        /// <param name="file">The file coordinate to move to. Must be [a-h].</param>
        /// <param name="rank">The rank coordinate to move to. Must be [1-8].</param>
        /// <param name="promotionType">If this is a Pawn moving to the end of the board then this parameter is what to promote it to. When used must be 'Queen', 'Knight', 'Rook', or 'Bishop'.</param>
        /// <returns>The Move you did if successful, otherwise null if invalid. In addition if your move was invalid you will lose.</returns>
        public Chess.Move Move(string file, int rank, string promotionType="")
        {
            return this.RunOnServer<Chess.Move>("move", new Dictionary<string, object> {
                {"file", file},
                {"rank", rank},
                {"promotionType", promotionType}
            });
        }

        #endregion
    }
}

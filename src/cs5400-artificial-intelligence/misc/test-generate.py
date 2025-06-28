import chess

fen = '3k4/8/8/8/8/8/4PP2/R3KR2 w Q - 0 1 ' #"8/1q2P1kn/2P1P3/4b3/7p/2NP1P2/3P4/3Q2K1 w - - 0 1"]

board = chess.Board()
board.set_fen(fen)
print("""\tSECTION("Random ") {""")
print("""\t\tstd::string fen = "{}";""".format(fen))
print("\t\tChessAI ai(fen);\n")

print("\t\tauto actions = ChessAI::actions(ai.currentState);")
print("\t\tauto description = actionsToDescription(actions);\n")

print("\t\tREQUIRE(description.size() == {});".format(len(list(board.legal_moves))))

for move in board.legal_moves:
    move = str(move)

    print("\t\tREQUIRE(std::find(description.begin(), description.end(), std::make_pair(std::make_pair('{}', {}),  std::make_pair('{}', {}))) != description.end());".format(move[0].capitalize(), move[1], move[2].capitalize(), move[3]))

print("\t}\n")
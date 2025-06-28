from functools import reduce 

byte_array = [
    0,  #0 Color
    0,  #1 Piece Before
    0,  #2 Piece Before
    0,  #3 Piece Before
    0,  #4 Piece Before
    0,  #5 Piece Before
    0,  #6 Piece Before
    0,  #7 Piece After
    0,  #8 Piece After
    0,  #9 Piece After
    0,  #10 Piece After
    0,  #11 Piece After
    0,  #12 Piece After
    0,  #13
    0,  #14
    0,  #15
    0,  #16 Piece Moved
    0,  #17 Piece Moved
    0,  #18 Piece Moved
    0,  #19 Double Pawn Forward
    0,  #20 Queen Side Castline
    0,  #21 King Side Castling
    0,  #22 Enemy In Check
    0,  #23 Capture Type
    0,  #24 Capture Type
    0,  #25 Capture Type
    0,  #26 En Passant Flag
    0,  #27 Same Capture Piece
    1,  #28 Promotion Type
    0,  #29 Promotion Type
    0,  #30 Promotion Type
    0   #31 King Capture Flag
]

value = 0
for index, byte in enumerate(byte_array):
    if byte == 1:
        value +=  2 ** index

print("0x{}".format(format(value, '02x')))
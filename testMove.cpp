/***********************************************************************
 * Header File:
 *    TEST MOVE
 * Author:
 *    <Jessen Forbush, Roger Galan>
 * Summary:
 *    test the Move class
 ************************************************************************/


#include "testMove.h"
#include "move.h"
#include <cassert>

 /*************************************
  * Constructor : default
  * Input:
  * Output: source=INVALID
  *         dest  =INVALID
  *******************************************/
void TestMove::constructor_default()
{
   // Setup

   // Exercise
   Move m;

   // Verify
   assertUnit(m.source.colRow == 0xff);
   assertUnit(m.dest.colRow == 0xff);

}  // Teardown

 /*************************************
  * CONSTRUCTOR : standard string move
  * Input:  e5e6
  * Output: source=4,4
  *         dest  =4,5
  *         type  =MOVE
  **************************************/
void TestMove::constructString_simple()
{
   // Setup
   string moveText = "e5e6";

   // Exercise
   Move m(moveText);

   // Verify

   // Check source position (e5 = column 4, row 4)
   assertUnit(m.source.colRow == 0x44);

   // Check destination position (e6 = column 4, row 5)
   assertUnit(m.dest.colRow == 0x45);

   // Check move type
   assertUnit(m.moveType == Move::MOVE);

}  // Teardown

/*************************************
 * READ simple move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::read_simple()
{
   // Setup
   Move m;
   string moveText = "e5e6";

   // Exercise
   m.read(moveText);

   // Verify
   // Check source position (e5 = column 4, row 4)
   assertUnit(m.source.colRow == 0x44);

   // Check destination position (e6 = column 4, row 5)
   assertUnit(m.dest.colRow == 0x45);

   // Check move type
   assertUnit(m.moveType == Move::MOVE);

}   // Teardown

 /*************************************
  * READ capture move
  * Input:  e5d6r
  * Output: source=4,4
  *         dest  =3,5
  *         type  =MOVE
  *         capture=ROOK
  **************************************/
void TestMove::read_capture()
{
   // Setup
   Move m;
   string moveText = "e5d6r";

   // Exercise
   m.read(moveText);

   // Verify
   // Check source position (e5 = column 4, row 4)
   assertUnit(m.source.colRow == 0x44);

   // Check destination position (d6 = column 3, row 5)
   assertUnit(m.dest.colRow == 0x35);

   // Check move type and capture
   assertUnit(m.moveType == Move::MOVE);
   assertUnit(m.capture == ROOK);
}

/*************************************
 * READ enpassant move
 * Input:  e5f6E
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 **************************************/
void TestMove::read_enpassant()
{
   // Setup
   Move m;
   string moveText = "e5f6E";

   // Exercise
   m.read(moveText);

   // Verify
   // Check source position (e5 = column 4, row 4)
   assertUnit(m.source.colRow == 0x44);


   // Check destination position (f6 = column 5, row 5)
   assertUnit(m.dest.colRow == 0x55);

   // Check move type
   assertUnit(m.moveType == Move::ENPASSANT);
   assertUnit(m.enpassant == true);
   assertUnit(m.capture == PAWN);
}

/*************************************
 * READ king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::read_castleKing()
{
   // Setup
   Move m;
   string moveText = "e1g1c";

   // Exercise
   m.read(moveText);

   // Verify
   // Check source position (e1 = column 4, row 0)
   assertUnit(m.source.colRow == 0x40);

   // Check destination position (g1 = column 6, row 0)
   assertUnit(m.dest.colRow == 0x60);

   // Check move type
   assertUnit(m.moveType == Move::CASTLE_KING);
   assertUnit(m.castleK == true);
}

/*************************************
 * READ queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::read_castleQueen()
{
   // Setup
   Move m;
   string moveText = "e1c1C";

   // Exercise
   m.read(moveText);

   // Verify
   // Check source position (e1 = column 4, row 0)
   assertUnit(m.source.colRow == 0x40);

   // Check destination position (c1 = column 2, row 0)
   assertUnit(m.dest.colRow == 0x20);

   // Check move type
   assertUnit(m.moveType == Move::CASTLE_QUEEN);
   assertUnit(m.castleQ == true);
}

/*************************************
 * ASSIGN simple move
 * Input:  e5e6
 * Output: source=4,4
 *         dest  =4,5
 *         type  =MOVE
 **************************************/
void TestMove::assign_simple()
{
   // Setup
   Move m;
   string moveText = "e5e6";

   // Exercise
   m.assign(moveText);

   // Verify
   // Check source position (e5 = column 4, row 4)
   assertUnit(m.source.colRow == 0x44);

   // Check destination position (e6 = column 4, row 5)
   assertUnit(m.dest.colRow == 0x45);

   // Check move type
   assertUnit(m.moveType == Move::MOVE);
}

/*************************************
 * ASSIGN capture move
 * Input:  e5d6r
 * Output: source=4,4
 *         dest  =3,5
 *         type  =MOVE
 *         capture=ROOK
 **************************************/
void TestMove::assign_capture()
{
   // Setup
   Move m;
   string moveText = "e5d6r";

   // Exercise
   m.assign(moveText);

   // Verify
   // Check source position (e5 = column 4, row 4)
   assertUnit(m.source.colRow == 0x44);

   // Check destination position (d6 = column 3, row 5)
   assertUnit(m.dest.colRow == 0x35);

   // Check move type and capture
   assertUnit(m.moveType == Move::MOVE);
   assertUnit(m.capture == ROOK);
}

/*************************************
 * ASSIGN enpassant move
 * Input:  e5f6E
 * Output: source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 **************************************/
void TestMove::assign_enpassant()
{
   // Setup
   Move m;
   string moveText = "e5f6E";

   // Exercise
   m.assign(moveText);

   // Verify
   // Check source position (e5 = column 4, row 4)
   assertUnit(m.source.colRow == 0x44);

   // Check destination position (f6 = column 5, row 5)
   assertUnit(m.dest.colRow == 0x55);

   // Check move type
   assertUnit(m.moveType == Move::ENPASSANT);
   assertUnit(m.enpassant == true);
   assertUnit(m.capture == PAWN);
}

/*************************************
 * ASSIGN king side castle
 * Input:  e1g1c
 * Output: source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 **************************************/
void TestMove::assign_castleKing()
{
   // Setup
   Move m;
   string moveText = "e1g1c";

   // Exercise
   m.assign(moveText);

   // Verify
   // Check source position (e1 = column 4, row 0)
   assertUnit(m.source.colRow == 0x40);

   // Check destination position (g1 = column 6, row 0)
   assertUnit(m.dest.colRow == 0x60);

   // Check move type
   assertUnit(m.moveType == Move::CASTLE_KING);
   assertUnit(m.castleK == true);
}

/*************************************
 * ASSIGN queen side castle
 * Input:  e1c1C
 * Output: source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 **************************************/
void TestMove::assign_castleQueen()
{
   // Setup
   Move m;
   string moveText = "e1c1C";

   // Exercise
   m.assign(moveText);

   // Verify
   // Check source position (e1 = column 4, row 0)
   assertUnit(m.source.colRow == 0x40);

   // Check destination position (c1 = column 2, row 0)
   assertUnit(m.dest.colRow == 0x20);

   // Check move type
   assertUnit(m.moveType == Move::CASTLE_QUEEN);
   assertUnit(m.castleQ == true);
}

/*************************************
 * GET TEXT simple move
 * Input : source=4,4
 *         dest  =4,5
 *         type  =MOVE
 * Output:  e5e6
 **************************************/
void TestMove::getText_simple()
{
   // Setup
   Move m;
   // Set up a simple move from e5 to e6
   m.read("e5e6");

   // Exercise
   string result = m.getText();

   // Verify
   assertUnit(result == "e5e6");
}

/*************************************
 * GET TEXT capture
 * Input : source=4,4
 *         dest  =4,5
 *         type  =MOVE
 *         capture=ROOK
 * Output:  e5e6r
 **************************************/
void TestMove::getText_capture()
{
   // Setup
   Move m;
   // Set up a capture move from e5 to e6, capturing a rook
   m.read("e5e6r");

   // Exercise
   string result = m.getText();

   // Verify
   assertUnit(result == "e5e6r");
}

/*************************************
 * GET TEXT en passant
 * Input : source=4,4
 *         dest  =5,5
 *         type  =ENPASSANT
 *         capture=PAWN
 * Output:  e5f6E
 **************************************/
void TestMove::getText_enpassant()
{
   // Setup
   Move m;
   // Set up an en passant move from e5 to f6
   m.read("e5f6E");

   // Exercise
   string result = m.getText();

   // Verify
   assertUnit(result == "e5f6E");
}

/*************************************
 * GET TEXT king side castle
 * Input : source=4,0
 *         dest  =6,0
 *         type  =CASTLE_KING
 * Output:  e1g1c
 **************************************/
void TestMove::getText_castleKing()
{
   // Setup
   Move m;
   // Set up a king-side castle move from e1 to g1
   m.read("e1g1c");

   // Exercise
   string result = m.getText();

   // Verify
   assertUnit(result == "e1g1c");
}

/*************************************
 * GET TEXT queen side castle
 * Input : source=4,0
 *         dest  =2,0
 *         type  =CASTLE_QUEEN
 * Output:  e1c1C
 **************************************/
void TestMove::getText_castleQueen()
{
   // Setup
   Move m;
   // Set up a queen-side castle move from e1 to c1
   m.read("e1c1C");

   // Exercise
   string result = m.getText();

   // Verify
   assertUnit(result == "e1c1C");
}  // Teardown 

/*************************************
 * LETTER FROM PIECE TYPE space
 * Input :  SPACE
 * Output:  ' '
 **************************************/
void TestMove::letterFromPieceType_space()
{
   // Setup
   Move m;
   PieceType pt = SPACE;

   // Exercise
   char result = m.letterFromPieceType(pt);

   // Verify
   assertUnit(result == ' ');

}  // Teardown

 /*************************************
  * LETTER FROM PIECE TYPE pawn
  * Input : PAWN
  * Output:  'p'
  **************************************/
void TestMove::letterFromPieceType_pawn()
{
   // Setup
   Move m;
   PieceType pt = PAWN;

   // Exercise
   char result = m.letterFromPieceType(pt);

   // Verify
   assertUnit(result == 'p');

}  // Teardown

/*************************************
 * LETTER FROM PIECE TYPE bishop
 * Input : BISHOP
 * Output:  'b'
 **************************************/
void TestMove::letterFromPieceType_bishop()
{
   // Setup
   Move m;
   PieceType pt = BISHOP;

   // Exercise
   char result = m.letterFromPieceType(pt);

   // Verify
   assertUnit(result == 'b');

}  // Teardown

/*************************************
 * LETTER FROM PIECE TYPE knight
 * Input : KNIGHT
 * Output:  'n'
 **************************************/
void TestMove::letterFromPieceType_knight()
{
   // Setup
   Move m;
   PieceType pt = KNIGHT;

   // Exercise
   char result = m.letterFromPieceType(pt);

   // Verify
   assertUnit(result == 'n');

}  // Teardown

/*************************************
 * LETTER FROM PIECE TYPE rook
 * Input : ROOK
 * Output:  'r'
 **************************************/
void TestMove::letterFromPieceType_rook()
{
   // Setup
   Move m;
   PieceType pt = ROOK;

   // Exercise
   char result = m.letterFromPieceType(pt);

   // Verify
   assertUnit(result == 'r');

}  // Teardown

/*************************************
 * LETTER FROM PIECE TYPE queen
 * Input : QUEEN
 * Output:  'q'
 **************************************/
void TestMove::letterFromPieceType_queen()
{
   // Setup
   Move m;
   PieceType pt = QUEEN;

   // Exercise
   char result = m.letterFromPieceType(pt);

   // Verify
   assertUnit(result == 'q');

}  // Teardown

/*************************************
 * LETTER FROM PIECE TYPE king
 * Input : KING
 * Output:  'k'
 **************************************/
void TestMove::letterFromPieceType_king()
{
   // Setup
   Move m;
   PieceType pt = KING;

   // Exercise
   char result = m.letterFromPieceType(pt);

   // Verify
   assertUnit(result == 'k');

}  // Teardown

/*************************************
 * PIECE TYPE FROM LETTER pawn
 * Input : 'p'
 * Output:  PAWN
 **************************************/
void TestMove::pieceTypeFromLetter_pawn()
{
   // Setup
   Move m;
   char letter = 'p';

   // Exercise
   PieceType result = m.pieceTypeFromLetter(letter);

   // Verify
   assertUnit(result == PAWN);

}  // Teardown

/*************************************
 * PIECE TYPE FROM LETTER knight
 * Input : 'n'
 * Output:  KNIGHT
 **************************************/
void TestMove::pieceTypeFromLetter_knight()
{
   // Setup
   Move m;
   char letter = 'n';

   // Exercise
   PieceType result = m.pieceTypeFromLetter(letter);

   // Verify
   assertUnit(result == KNIGHT);

}  // Teardown

/*************************************
 * PIECE TYPE FROM LETTER bishop
 * Input : 'b'
 * Output:  BISHOP
 **************************************/
void TestMove::pieceTypeFromLetter_bishop()
{
   // Setup
   Move m;
   char letter = 'b';

   // Exercise
   PieceType result = m.pieceTypeFromLetter(letter);

   // Verify
   assertUnit(result == BISHOP);

}  // Teardown

/*************************************
 * PIECE TYPE FROM LETTER rook
 * Input : 'r'
 * Output:  ROOK
 **************************************/
void TestMove::pieceTypeFromLetter_rook()
{
   // Setup
   Move m;
   char letter = 'r';

   // Exercise
   PieceType result = m.pieceTypeFromLetter(letter);

   // Verify
   assertUnit(result == ROOK);

}  // Teardown

/*************************************
 * PIECE TYPE FROM LETTER queen
 * Input : 'q'
 * Output:  QUEEN
 **************************************/
void TestMove::pieceTypeFromLetter_queen()
{
   // Setup
   Move m;
   char letter = 'q';

   // Exercise
   PieceType result = m.pieceTypeFromLetter(letter);

   // Verify
   assertUnit(result == QUEEN);

}  // Teardown

/*************************************
 * PIECE TYPE FROM LETTER king
 * Input : 'k'
 * Output:  KING
 **************************************/
void TestMove::pieceTypeFromLetter_king()
{
   // Setup
   Move m;
   char letter = 'k';

   // Exercise
   PieceType result = m.pieceTypeFromLetter(letter);

   // Verify
   assertUnit(result == KING);

}  // Teardown


/*************************************
 * EQUAL - NOT
 * Input : b2b4 == b2b5
 * Output: false
 **************************************/
void TestMove::equal_not()
{
   // Setup
   Move m1;
   Move m2;
   m1.read("b2b4");
   m2.read("b2b5");

   // Exercise
   bool result = (m1 == m2);

   // Verify
   assertUnit(result == false);

}  // Teardown

/*************************************
 * EQUAL - EQUALS
 * Input : b2b4 == b2b4
 * Output: true
 **************************************/
void TestMove::equal_equals()
{
   // Setup
   Move m1;
   Move m2;
   m1.read("b2b4");
   m2.read("b2b4");

   // Exercise
   bool result = (m1 == m2);

   // Verify
   assertUnit(result == true);

}  // Teardown

/*************************************
 * LESS THAN - LESS THAN
 * Input : b2b2 < b2b4
 * Output: true
 *    Note that the less-than operator is needed
 *    so std::set<T> can sort the elements. Thus,
 *    any T in a set must define less-than. In this
 *    case, I defined it according to the
 *     destination's Position's location.
 **************************************/
void TestMove::lessthan_lessthan()
{
   // Setup
   Move m1;
   Move m2;
   m1.read("b2b2");
   m2.read("b2b4");

   // Exercise
   bool result = (m1 < m2);

   // Verify
   assertUnit(result == true);

}  // Teardown

/*************************************
 * LESS THAN - EQUALS
 * Input : b2b4 < b2b4
 * Output: false
 **************************************/
void TestMove::lessthan_equals()
{
   // Setup
   Move m1;
   Move m2;
   m1.read("b2b4");
   m2.read("b2b4");

   // Exercise
   bool result = (m1 < m2);

   // Verify
   assertUnit(result == false);

}  // Teardown

/*************************************
 * LESS THAN - GREATER THAN
 * Input : b2b4 < b2b2
 * Output: false
 **************************************/
void TestMove::lessthan_greaterthan()
{
   // Setup
   Move m1;
   Move m2;
   m1.read("b2b4");
   m2.read("b2b2");

   // Exercise
   bool result = (m1 < m2);

   // Verify
   assertUnit(result == false);

}  // Teardown

#include <gtest/gtest.h>
#include "fenparserpp.h"

using namespace fenparserpp;

namespace {
    TEST(FenParserTest, WrongInput) {
        FENParser parser;
        SimpleBoard board;
        EXPECT_FALSE(parser.parse("hello world", board));
        EXPECT_FALSE(parser.parse("rnbqkbnr/pppppppp/8", board));
    }
    TEST(FenParserTest, StartPosition) {
        FENParser parser;
        SimpleBoard board;
        EXPECT_TRUE(parser.parse("rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1", board));
        EXPECT_EQ(PieceColor::WHITE, board.getToPlay());
        EXPECT_EQ(Piece::ROOK, board.getPiece(0,0));
        EXPECT_EQ(Piece::ROOK, board.getPiece(0,7));
        EXPECT_EQ(Piece::KNIGHT, board.getPiece(1,0));
        EXPECT_EQ(Piece::KNIGHT, board.getPiece(1,7));
        EXPECT_EQ(Piece::BISHOP, board.getPiece(2,0));
        EXPECT_EQ(Piece::BISHOP, board.getPiece(2,7));
        EXPECT_EQ(Piece::QUEEN, board.getPiece(3,0));
        EXPECT_EQ(Piece::QUEEN, board.getPiece(3,7));
        EXPECT_EQ(Piece::KING, board.getPiece(4,0));
        EXPECT_EQ(Piece::KING, board.getPiece(4,7));

        for(int i=0;i<7;i++) {
            EXPECT_EQ(Piece::PAWN, board.getPiece(i,1));
            EXPECT_EQ(Piece::PAWN, board.getPiece(i,6));
            EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(i,6));
            EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(i,1));
            // also check the colors of the other pieces in the same loop
            EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(i,7));
            EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(i,0));
        }
        
        EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(0,0));
    }
    TEST(FenParserTest, PosWhiteToMove) {
        FENParser parser;
        SimpleBoard board;
        EXPECT_TRUE(parser.parse("2b2n2/8/8/8/8/8/8/1K2Q3 w - - 0 1", board));
        EXPECT_EQ(PieceColor::WHITE, board.getToPlay());
        EXPECT_EQ(Piece::BISHOP, board.getPiece(2,7));
        EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(2,7));
        EXPECT_EQ(Piece::KNIGHT, board.getPiece(5,7));
        EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(5,7));

        EXPECT_EQ(Piece::KING, board.getPiece(1,0));
        EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(1,0));
        EXPECT_EQ(Piece::QUEEN, board.getPiece(4,0));
        EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(4,0));
    }
    TEST(FenParserTest, PosBlackToMove) {
        FENParser parser;
        SimpleBoard board;
        EXPECT_TRUE(parser.parse("2b2n2/8/8/8/8/8/8/1K2Q3 b - - 0 1", board));
        EXPECT_EQ(PieceColor::BLACK, board.getToPlay());
        EXPECT_EQ(Piece::BISHOP, board.getPiece(2,7));
        EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(2,7));
        EXPECT_EQ(Piece::KNIGHT, board.getPiece(5,7));
        EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(5,7));

        EXPECT_EQ(Piece::KING, board.getPiece(1,0));
        EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(1,0));
        EXPECT_EQ(Piece::QUEEN, board.getPiece(4,0));
        EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(4,0));
    }
}

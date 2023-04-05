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
        EXPECT_EQ(Piece::ROOK, board.getPiece( BoardPos(0,0) ));
        EXPECT_EQ(Piece::ROOK, board.getPiece( BoardPos(0,7) ));
        EXPECT_EQ(Piece::KNIGHT, board.getPiece( BoardPos(1,0) ));
        EXPECT_EQ(Piece::KNIGHT, board.getPiece( BoardPos(1,7) ));
        EXPECT_EQ(Piece::BISHOP, board.getPiece( BoardPos(2,0) ));
        EXPECT_EQ(Piece::BISHOP, board.getPiece( BoardPos(2,7) ));
        EXPECT_EQ(Piece::QUEEN, board.getPiece( BoardPos(3,0) ));
        EXPECT_EQ(Piece::QUEEN, board.getPiece( BoardPos(3,7) ));
        EXPECT_EQ(Piece::KING, board.getPiece( BoardPos(4,0) ));
        EXPECT_EQ(Piece::KING, board.getPiece( BoardPos(4,7) ));

        for(int i=0;i<7;i++) {
            EXPECT_EQ(Piece::PAWN, board.getPiece(BoardPos(i,1)));
            EXPECT_EQ(Piece::PAWN, board.getPiece(BoardPos(i,6)));
            EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(BoardPos(i,6)));
            EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(BoardPos(i,1)));
            // also check the colors of the other pieces in the same loop
            EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(BoardPos(i,7)));
            EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(BoardPos(i,0)));
        }
        
        auto crights = board.getCastleRights();
        EXPECT_NE(crights.end(), crights.find(CastleRight::BLACK_KINGSIDE_CASTLE));
        EXPECT_NE(crights.end(), crights.find(CastleRight::WHITE_KINGSIDE_CASTLE));
        EXPECT_NE(crights.end(), crights.find(CastleRight::BLACK_QUEENSIDE_CASTLE));
        EXPECT_NE(crights.end(), crights.find(CastleRight::BLACK_QUEENSIDE_CASTLE));
        
        EXPECT_FALSE(board.getEnPassentPos().has_value());
    }
    TEST(FenParserTest, PosWhiteToMove) {
        FENParser parser;
        SimpleBoard board;
        EXPECT_TRUE(parser.parse("2b2n2/8/8/8/8/8/8/1K2Q3 w - - 0 1", board));
        EXPECT_EQ(PieceColor::WHITE, board.getToPlay());
        EXPECT_EQ(Piece::BISHOP, board.getPiece(BoardPos(2,7)));
        EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(BoardPos(2,7)));
        EXPECT_EQ(Piece::KNIGHT, board.getPiece(BoardPos(5,7)));
        EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(BoardPos(5,7)));

        EXPECT_EQ(Piece::KING, board.getPiece(BoardPos(1,0)));
        EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(BoardPos(1,0)));
        EXPECT_EQ(Piece::QUEEN, board.getPiece(BoardPos(4,0)));
        EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(BoardPos(4,0)));
        
        EXPECT_EQ(0, board.getCastleRights().size());
        EXPECT_FALSE(board.getEnPassentPos().has_value());
    }
    TEST(FenParserTest, PosBlackToMove) {
        FENParser parser;
        SimpleBoard board;
        EXPECT_TRUE(parser.parse("2b2n2/8/8/8/8/8/8/1K2Q3 b - - 0 1", board));
        EXPECT_EQ(PieceColor::BLACK, board.getToPlay());
        EXPECT_EQ(Piece::BISHOP, board.getPiece(BoardPos(2,7)));
        EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(BoardPos(2,7)));
        EXPECT_EQ(Piece::KNIGHT, board.getPiece(BoardPos(5,7)));
        EXPECT_EQ(PieceColor::BLACK, board.getPieceColor(BoardPos(5,7)));

        EXPECT_EQ(Piece::KING, board.getPiece(BoardPos(1,0)));
        EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(BoardPos(1,0)));
        EXPECT_EQ(Piece::QUEEN, board.getPiece(BoardPos(4,0)));
        EXPECT_EQ(PieceColor::WHITE, board.getPieceColor(BoardPos(4,0)));

        EXPECT_EQ(0, board.getCastleRights().size());
        EXPECT_FALSE(board.getEnPassentPos().has_value());
    }
    TEST(FenParserTest, EnPassant) {
        FENParser parser;
        SimpleBoard board;
        EXPECT_TRUE(parser.parse("rnbqkbnr/ppp1p1pp/8/3pPp2/8/8/PPPP1PPP/RNBQKBNR w KQkq f6", board));
        EXPECT_TRUE(board.getEnPassentPos().has_value());
        BoardPos bp = board.getEnPassentPos().value();
        EXPECT_EQ(5, bp.getRank());
        EXPECT_EQ(5, bp.getFile());
    }
}

#pragma once

#include <string>
#include <sstream>
#include <vector>

namespace fenparserpp
{
    enum class PieceColor {
        BLACK,
        WHITE,
        NONE
    };
    enum class Piece {
        PAWN,
        KNIGHT,
        BISHOP,
        ROOK,
        QUEEN,
        KING,
        NONE
    };
    enum class CastleRight {
        KINGSIDE_CASTLE,
        QUEENSIDE_CASTLE,
    };

    // TODO en passant position

    class BoardListener {
        public:
            virtual void reset() = 0;
            virtual void setPiece(int file, int rank, Piece piece, PieceColor pieceColor) = 0;
            virtual void setCastleRight(CastleRight right, PieceColor pieceColor) = 0;
            virtual void setToPlay(PieceColor color) = 0;
    };

    class SimpleBoard: public BoardListener {
        private:
            Piece board[8][8];
            PieceColor boardColor[8][8];
            PieceColor toPlay;
        public:
            SimpleBoard();
            void reset();
            void setPiece(int file, int rank, Piece piece, PieceColor pieceColor);
            Piece getPiece(int file, int rank);
            PieceColor getPieceColor(int file, int rank);
            void setCastleRight(CastleRight right, PieceColor pieceColor);
            inline void setToPlay(PieceColor pc) { toPlay = pc; }
            inline PieceColor getToPlay() { return toPlay; }
    };

    class FENParser
    {
    public:
        bool parse(const std::string& fen, BoardListener &listener);

    private:
      //  static void handleCastlingRights(Position& position, const std::string& s);
        bool decodeRank(const std::string& rank, int rankNr, BoardListener &listener);
        std::vector<std::string> split(const std::string& s, char delim);
        Piece getPieceFromChar(char ch);
        inline PieceColor getColorFromChar(char ch) {
            if(isupper(ch)) {
                return PieceColor::WHITE;
            } else {
                return PieceColor::BLACK;
            }
        }
        inline char getFileWithOffset(char file, int offset) {
            return file + offset;
        }
    };

};

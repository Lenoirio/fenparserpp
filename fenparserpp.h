#pragma once

#include <string>
#include <sstream>
#include <vector>
#include <unordered_set>
#include <optional>

//https://de.wikipedia.org/wiki/Forsyth-Edwards-Notation

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
        BLACK_KINGSIDE_CASTLE,
        BLACK_QUEENSIDE_CASTLE,
        WHITE_KINGSIDE_CASTLE,
        WHITE_QUEENSIDE_CASTLE
    };

    // This represents a position on the board (0-based!)
    // E.g.  F6  will return rank and file as 5
    class BoardPos {
        private:
            int file;
            int rank;
        public:
            inline BoardPos(int fe, int rk) {
                file = fe;
                rank = rk;
            }
            inline int getFile() const { return file; }
            inline int getRank() const { return rank; }
    };

    class BoardListener {
        public:
            virtual void reset() = 0;
            virtual void setPiece(const BoardPos &bpos, Piece piece, PieceColor pieceColor) = 0;
            virtual void setCastleRight(CastleRight right) = 0;
            virtual void setEnPassantPos(const BoardPos &bpos) = 0;
            virtual void setHalfMoves(int hmoves) = 0;
            virtual void setFullMoves(int fmoves) = 0;
            virtual void setToPlay(PieceColor color) = 0;
    };

    class SimpleBoard: public BoardListener {
        private:
            Piece board[8][8];
            PieceColor boardColor[8][8];
            PieceColor toPlay;
            std::unordered_set<CastleRight> castleRights;
            std::optional<BoardPos> enPassentPos;
            int halfMoves;
            int fullMoves;
        public:
            SimpleBoard();
            void reset();
            void setPiece(const BoardPos &bpos, Piece piece, PieceColor pieceColor);
            Piece getPiece(const BoardPos &bpos) const;
            PieceColor getPieceColor(const BoardPos &bpos) const;
            void setCastleRight(CastleRight right);
            inline void setToPlay(PieceColor pc) { toPlay = pc; }
            inline PieceColor getToPlay() const { return toPlay; }
            inline void setEnPassantPos(const BoardPos &bpos) { enPassentPos = bpos; }
            inline std::optional<BoardPos> getEnPassantPos() const { return enPassentPos; }
            inline void setHalfMoves(int hmoves) { halfMoves = hmoves; }
            inline int getHalfMoves() { return halfMoves; }
            inline void setFullMoves(int fmoves) { fullMoves = fmoves; }
            inline int getFullMoves() { return fullMoves; }
            inline const std::unordered_set<CastleRight>& getCastleRights() { return castleRights; }
    };

    class FENParser
    {
    public:
        bool parse(const std::string& fen, BoardListener &listener);

    private:
        void handleCastlingRights(BoardListener &listener, const std::string& s);
        bool handleEnPassent(BoardListener &listener, const std::string& s);
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

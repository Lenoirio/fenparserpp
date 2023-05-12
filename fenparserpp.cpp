/**
 * FEN Parser   (c) Markus Gietzen
 * Released under MIT license (see LICENSE.txt)
*/
#include "fenparserpp.h"

namespace fenparserpp {

bool FENParser::parse(const std::string& fen, BoardListener &listener) {
    listener.reset();

    std::vector<std::string> splitted = split(fen, ' ');
    if(splitted.size()<2) {
        return false;
    }
    std::vector<std::string> ranks = split(splitted.at(0), '/');
    if(ranks.size() !=8 ) {
        return false;
    }
    for(int r=0;r<8;r++) {
         if(!decodeRank(ranks[r], 7- r, listener)) {
            return false;
         }
    }
    if(splitted.at(1) == "w") {
        listener.setToPlay(PieceColor::WHITE);
    } else if(splitted.at(1) == "b") {
        listener.setToPlay(PieceColor::BLACK);
    } else {
        return false;
    }

    if(splitted.size()>2) {
        handleCastlingRights(listener, splitted.at(2));
    }
    
    if(splitted.size()>3) {
        if(!handleEnPassent(listener, splitted.at(3))) {
            return false;
        }
    }

    if(splitted.size()>4) {
        listener.setHalfMoves(atoi(splitted.at(4).c_str()));
    }

    if(splitted.size()>5) {
        listener.setFullMoves(atoi(splitted.at(5).c_str()));
    }

    return true;
}

bool FENParser::decodeRank(const std::string& rank, int rankNr, BoardListener &listener) {
    char file = 'a';
    for (int i = 0; i < static_cast<int>(rank.length()) && file <= 'h'; i++) {
        char c = rank.at(i);
        if (isdigit(c)) {
            file = getFileWithOffset(file, c - '0');
        } else {
            PieceColor pcolor = getColorFromChar(c);
            Piece piece = getPieceFromChar(c);
            if(piece == Piece::NONE) {  // unknown piece character
                return false;
            }
            listener.setPiece(BoardPos(file-'a', rankNr), piece, pcolor);
            file = getFileWithOffset(file, 1);
        }
    }
    return true;
}

void FENParser::handleCastlingRights(BoardListener &listener, const std::string& s) {
    if(s.find("K") != std::string::npos) {
        listener.setCastleRight(CastleRight::WHITE_KINGSIDE_CASTLE);
    }
    if(s.find("k") != std::string::npos) {
        listener.setCastleRight(CastleRight::BLACK_KINGSIDE_CASTLE);
    }
    if(s.find("Q") != std::string::npos) {
        listener.setCastleRight(CastleRight::WHITE_QUEENSIDE_CASTLE);
    }
    if(s.find("q") != std::string::npos) {
        listener.setCastleRight(CastleRight::BLACK_QUEENSIDE_CASTLE);
    }    
}

bool FENParser::handleEnPassent(BoardListener &listener, const std::string& s) {
    if(s == "-") {
        return true;
    }
    if(s.size() == 2) {
        char file = s.at(0);
        char rank = s.at(1);
        if(file>='a' && file <='h' && rank >='1' && rank<='8') {
            listener.setEnPassantPos( BoardPos(file-'a', rank-'0'-1) );
            return true;
        }
    }
    return false;
}


Piece FENParser::getPieceFromChar(char ch) {
    switch(tolower(ch)) {
        case 'p':
            return Piece::PAWN;
        case 'k':
            return Piece::KING;
        case 'q':
            return Piece::QUEEN;
        case 'r':
            return Piece::ROOK;
        case 'n':
            return Piece::KNIGHT;
        case 'b':
            return Piece::BISHOP;
        default:
            return Piece::NONE;
    }
}

std::vector<std::string> FENParser::split(const std::string& s, char delim) {
    std::vector<std::string> result;
    std::stringstream ss(s);
    std::string item;
    int numElements = 0;

    while (getline(ss, item, delim)) {
        result.push_back(item);
        if(++numElements > 20) {    // too many entries, return empty to force abortion
            result.clear();
            return result;
        }
    }

    return result;
}      


SimpleBoard::SimpleBoard() {
    reset();
}

void SimpleBoard::reset() {
    castleRights.clear();
    enPassentPos = {};
    halfMoves = 0;
    fullMoves = 0;
    for(int row =0;row<8;row++) {
        for(int rank=0;rank<8;rank++) {
            board[rank][row] = Piece::NONE;
            boardColor[rank][row] = PieceColor::NONE;
        }
    }
}

void SimpleBoard::setPiece(const BoardPos &bpos, Piece piece, PieceColor pieceColor) {
    int file = bpos.getFile();
    int rank = bpos.getRank();
    if(file >= 0 && file < 8 && rank >=0 && rank < 8) {
        board[rank][file] = piece;
        boardColor[rank][file] = pieceColor;
    }
}

Piece SimpleBoard::getPiece(const BoardPos &bpos) const {
    int file = bpos.getFile();
    int rank = bpos.getRank();
    if(file >= 0 && file < 8 && rank >=0 && rank < 8) {
        return board[rank][file];
    }
    return Piece::NONE;
}

PieceColor SimpleBoard::getPieceColor(const BoardPos &bpos) const {
    int file = bpos.getFile();
    int rank = bpos.getRank();
    if(file >= 0 && file < 8 && rank >=0 && rank < 8) {
        return boardColor[rank][file];
    }
    return PieceColor::NONE;
}

void SimpleBoard::setCastleRight(CastleRight right) {
    castleRights.insert(right);
}


}

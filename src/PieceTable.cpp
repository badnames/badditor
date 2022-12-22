//
// Created by moritz on 22.12.22.
//

#include "PieceTable.h"

namespace editor {
    PieceTable::PieceTable() : m_cursorPos(0), m_appended(""), m_pieces(std::vector<Piece>()) {
    };

    PieceTable::PieceTable(std::string initialText) {
        m_cursorPos = 0;
        m_original = initialText;
        m_appended = std::stringstream("");
        m_pieces.push_back(Piece {0, m_original.size(), true});
    }

    std::string PieceTable::get() {
        std::stringstream final;
        auto appended = m_appended.str();

        for(auto piece : m_pieces) {
            const std::string &readString = piece.original ? m_original : appended;
            auto copyLength = piece.end - piece.start;

            final << readString.substr(piece.start, piece.start + copyLength);
        }

        return final.str();
    }

    void PieceTable::put(const char c) {

    }

    void PieceTable::put(const std::string string) {

    }

    void PieceTable::cursor(const uint64_t position) {

    }

    void PieceTable::cursorInc() {

    }

    void PieceTable::cursorDec() {

    }

} // editor
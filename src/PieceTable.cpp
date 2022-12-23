//
// Created by moritz on 22.12.22.
//

#include "PieceTable.h"

#include <utility>

namespace editor {
    // helper functions
    inline uint64_t getPieceIndexForModification(std::vector<Piece> pieces, uint64_t cursorPos);
    inline uint64_t getRelativeSplitIndex(std::vector<Piece> pieces, uint64_t index, uint64_t cursorPos);
    inline std::pair<Piece, Piece> splitPiece(Piece piece, uint64_t position);

    PieceTable::PieceTable() : m_size(0), m_cursorPos(0), m_appended(""), m_pieces(std::vector<Piece>()) {
    };

    PieceTable::PieceTable(const std::string& initialText){
        m_cursorPos = 0;
        m_size = initialText.size();
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
        auto m_appendedSize = m_appended.str().size();
        m_appended << c;

        auto index = getPieceIndexForModification(m_pieces, m_cursorPos);
        Piece &piece = m_pieces[index];

        // the simpler case
        // we only need to increment the end index
        if (!piece.original && piece.end == m_appendedSize) {
            piece.end++;
            this->m_size++;
            this->cursorInc();
            return;
        }

        auto splitPoint = getRelativeSplitIndex(m_pieces, index, m_cursorPos);
        auto splits = splitPiece(piece, splitPoint);
        m_pieces.erase(std::next(m_pieces.begin(), index));

        Piece newPiece = {m_appended.str().size() - 1, m_appended.str().size(), false};

        // pieces whose start and end values are the same don't produce any text
        // we can therefore safely ignore them
        if (splits.first.start != splits.first.end) {
            m_pieces.insert(std::next(m_pieces.begin(), index), splits.first);
            index++;
        }

        m_pieces.insert(std::next(m_pieces.begin(), index), newPiece);
        index++;

        if (splits.second.start != splits.second.end) {
            m_pieces.insert(std::next(m_pieces.begin(), index), splits.second);
        }

        this->m_size++;
        this->cursorInc();
    }

    void PieceTable::put(const std::string& string) {
        auto m_appendedSizeBefore = m_appended.str().size();
        m_appended << string;

        auto index = getPieceIndexForModification(m_pieces, m_cursorPos);
        Piece &piece = m_pieces[index];

        // the simpler case
        // we only need to increment the end index
        if (!piece.original && piece.end == m_appendedSizeBefore) {
            piece.end += string.size();
            this->m_size++;
            this->cursorInc();
            return;
        }

        auto splitPoint = getRelativeSplitIndex(m_pieces, index, m_cursorPos);
        auto splits = splitPiece(piece, splitPoint);
        m_pieces.erase(std::next(m_pieces.begin(), index));

        Piece newPiece = {m_appendedSizeBefore, m_appended.str().size(), false};

        // pieces whose start and end values are the same don't produce any text
        // we can therefore safely ignore them
        if (splits.first.start < splits.first.end) {
            m_pieces.insert(std::next(m_pieces.begin(), index), splits.first);
            index++;
        }

        m_pieces.insert(std::next(m_pieces.begin(), index), newPiece);
        index++;

        if (splits.second.start < splits.second.end) {
            m_pieces.insert(std::next(m_pieces.begin(), index), splits.second);
        }

        this->m_size++;
        this->cursorInc();
    }

    void PieceTable::cursor(const uint64_t position) {
        if (m_cursorPos > m_size) {
            throw std::bad_exception();
        }

        this->m_cursorPos = position;
    }

    void PieceTable::cursorInc() {
        if (m_cursorPos >= m_size) {
            return;
        }

        m_cursorPos++;
    }

    void PieceTable::cursorDec() {
        if (m_cursorPos == 0) {
            return;
        }

        m_cursorPos--;
    }

    void PieceTable::remove() {
        if (m_size == 0) {
            return;
        }

        auto index = getPieceIndexForModification(m_pieces, m_cursorPos);
        Piece &piece = m_pieces[index];

        auto splitPoint = getRelativeSplitIndex(m_pieces, index, m_cursorPos);
        auto splits = splitPiece(piece, splitPoint);
        m_pieces.erase(std::next(m_pieces.begin(), index));

        // pieces whose start and end values are the same don't produce any text
        // we can therefore safely ignore them
        if (splits.first.start < splits.first.end - 1) {
            splits.first.end--;
            m_pieces.insert(std::next(m_pieces.begin(), index), splits.first);
            index++;
        }

        if (splits.second.start < splits.second.end) {
            m_pieces.insert(std::next(m_pieces.begin(), index), splits.second);
        }

        this->cursorDec();
        m_size--;
    }

    inline uint64_t getPieceIndexForModification(std::vector<Piece> pieces, uint64_t cursorPos) {
        uint64_t charCount = 0;

        for (uint64_t i = 0; i < pieces.size(); i++) {
            charCount += pieces[i].end - pieces[i].start;
            if (cursorPos <= charCount) {
                return i;
            }
        }

        throw std::bad_exception();
    }

    // index should be determined using getPieceIndexForModification
    inline uint64_t getRelativeSplitIndex(std::vector<Piece> pieces, uint64_t index, uint64_t cursorPos) {
        // sum up all characters that are either lie before or are in the piece that is touched by the cursor
        uint64_t charCount = 0;
        for (uint64_t i = 0; i < index; i++) {
            charCount += pieces[i].end - pieces[i].start;
        }

        return cursorPos - charCount;
    }

    inline std::pair<Piece, Piece> splitPiece(Piece piece, uint64_t position) {
        return std::pair<Piece, Piece>({piece.start, piece.start + position, piece.original},
                                       {piece.start + position, piece.end, piece.original});
    }

} // editor
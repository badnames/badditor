//
// Created by moritz on 22.12.22.
//

#ifndef EDITOR_PIECETABLE_H
#define EDITOR_PIECETABLE_H

#include <string>
#include <sstream>
#include <vector>

namespace editor {

    struct Piece {
        uint64_t start;
        uint64_t end;
        bool original;
    };

    class PieceTable {
    private:
        uint64_t m_cursorPos;
        uint64_t m_size;
        std::string m_original;
        std::stringstream m_appended;

        std::vector<Piece> m_pieces;

    public:
        PieceTable();
        explicit PieceTable(const std::string& initialText);

        std::string get();
        void put(char c);
        void put(std::string string);
        void cursor(uint64_t position);
        void cursorInc();
        void cursorDec();
    };

} // editor

#endif //EDITOR_PIECETABLE_H

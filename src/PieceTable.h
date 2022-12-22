//
// Created by moritz on 22.12.22.
//

#ifndef EDITOR_PIECETABLE_H
#define EDITOR_PIECETABLE_H

#include <string>

namespace editor {

    class PieceTable {
    public:
        PieceTable();
        explicit PieceTable(const std::string &initialText);

        std::string get();
        void put(char c);
        void put(std::string string);
        void cursor(uint64_t position);
        void cursorInc();
        void cursorDec();
    };

} // editor

#endif //EDITOR_PIECETABLE_H

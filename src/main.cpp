#include <iostream>
#include <curses.h>
#include "PieceTable.h"

namespace editor {
    void redraw(WINDOW *window, PieceTable &pieceTable);
}

int main() {
    // setup curses
    WINDOW *mainWindow = initscr();
    cbreak();
    noecho();

    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    clear();

    // initialize piece table
    editor::PieceTable pieceTable;
    pieceTable.setCursor(0);

    bool running = true;
    while(running) {
        auto input = getch();

        switch (input) {
            // quit if escape was pressed
            case 27:
                running = false;
                break;

            case KEY_BACKSPACE:
                pieceTable.remove();
                break;

            case KEY_ENTER:
                pieceTable.put('\n');
                break;

            default:
                pieceTable.put((char) input);
        }

        clear();
        editor::redraw(mainWindow, pieceTable);
        refresh();
    }

    endwin();
    std::cout << pieceTable.get() << std::endl;
    return 0;
}

namespace editor {
    void redraw(WINDOW *window, PieceTable &pieceTable) {
        int height = getmaxy(window);
        std::string text = pieceTable.get();
        std::stringstream textStream(text);

        for (auto y = 0; y < height; y++) {
            std::string line;

            if (!std::getline(textStream, line, '\n')) {
                break;
            }

            wmove(window, y, 0);
            winsstr(window, line.c_str());
        }
    }
}

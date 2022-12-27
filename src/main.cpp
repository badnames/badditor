#include <curses.h>

int main() {
    WINDOW *mainWindow = initscr();
    cbreak();
    noecho();

    intrflush(stdscr, FALSE);
    keypad(stdscr, TRUE);

    int width = 0, height = 0;
    getmaxyx(mainWindow, height, width);

    clear();
    // Hello World!
    mvaddstr(height / 2, width / 2, "Hello World!");
    refresh();

    while(true) {
        char input = getch();
        if (input == 'q') break;
    }

    endwin();

    return 0;
}

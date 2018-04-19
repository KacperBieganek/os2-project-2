//
// Created by kacper on 07.04.18.
//
#include <thread>
#include <memory>
#include "FillableWindow.hpp"
#include "TetrisWindow.hpp"
#include <ctime>

void makeWindows(std::vector<WINDOW*>& windowVector,int height,int width);
WINDOW* create_newwin(int height, int width, int starty, int startx);

int main(int argv, char **argc) {
    int width, height;
    std::mutex collectionMutex, ncursesMutex;
    bool running = true;
    std::vector <WINDOW*> windowVector;

    srand(time(NULL));
    initscr();
    start_color();
    init_pair(1, COLOR_WHITE, COLOR_RED);
    init_pair(2, COLOR_WHITE, COLOR_GREEN);
    init_pair(3, COLOR_WHITE, COLOR_BLUE);
    init_pair(4, COLOR_WHITE, COLOR_BLACK);
    getmaxyx(stdscr, height, width);
    refresh();

    makeWindows(windowVector,height,width);

    getch();

    endwin();
    return 0;
}

void makeWindows(std::vector<WINDOW*> &windowVector, int height, int width) {
    int windowWidth = width >> 2;
    windowVector.push_back(create_newwin(height , windowWidth, 0, 0));
    windowVector.push_back(create_newwin(height , windowWidth, 0, windowWidth));
    windowVector.push_back(create_newwin(height , windowWidth, 0, 2 * windowWidth));
    windowVector.push_back(create_newwin(height , windowWidth, 0, 3 * windowWidth));
}

WINDOW *create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, '*', '*');
    wrefresh(local_win);
    return local_win;
}

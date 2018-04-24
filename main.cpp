//
// Created by kacper on 07.04.18.
//
#include <vector>
#include <deque>
#include <ctime>
#include <thread>
#include "FillableWindow.hpp"
#include "TetrisWindow.hpp"

void makeWindows(std::vector<WINDOW *> &windowVector, int height, int width);

WINDOW *create_newwin(int height, int width, int starty, int startx);

void init_app(std::vector<WINDOW *> &windows, int &height, int &width);


int main(int argv, char **argc) {
    int width, height;
    std::mutex collection_mutex, ncurses_mutex;
    std::atomic<bool> running{true};
    std::vector<WINDOW *> windows;
    std::vector<std::thread> threads;
    std::deque<tetris::Block> block_queue;
    std::condition_variable cv;

    init_app(windows, height, width);

    int counter = 0;
    for (auto &window: windows) {
        if (counter > 0)
            threads.push_back(std::thread(&tetris::FillableWindow::run, tetris::FillableWindow{
                    window,
                    running,
                    block_queue,
                    collection_mutex,
                    ncurses_mutex,
                    cv,
                    height,
                    width
            }));
        else
            threads.push_back(std::thread(&tetris::TetrisWindow::run, tetris::TetrisWindow{
                    window,
                    running,
                    block_queue,
                    collection_mutex,
                    ncurses_mutex,
                    cv,
                    height,
                    width
            }));
        ++counter;

    }

    getch();

    endwin();
    return 0;
}

void init_app(std::vector<WINDOW *> &windows, int &height, int &width) {
    srand(static_cast<unsigned int>(time(NULL)));
    initscr();
    noecho();
    curs_set(FALSE);
    start_color();
    init_pair(1,COLOR_WHITE, COLOR_RED);
    init_pair(2,COLOR_WHITE, COLOR_CYAN);
    init_pair(3,COLOR_WHITE, COLOR_YELLOW);
    init_pair(4,COLOR_WHITE, COLOR_MAGENTA);
    getmaxyx(stdscr, height, width);
    refresh();
    makeWindows(windows, height, width);
    width = width >> 2;
}

void makeWindows(std::vector<WINDOW *> &windowVector, int height, int width) {
    int window_width = width >> 2;
    windowVector.push_back(create_newwin(height, window_width, 0, 0));
    windowVector.push_back(create_newwin(height, window_width, 0, window_width));
    windowVector.push_back(create_newwin(height, window_width, 0, 2 * window_width));
    windowVector.push_back(create_newwin(height, window_width, 0, 3 * window_width));
}

WINDOW *create_newwin(int height, int width, int starty, int startx) {
    WINDOW *local_win;
    local_win = newwin(height, width, starty, startx);
    box(local_win, 0, 0);
    wrefresh(local_win);
    return local_win;
}

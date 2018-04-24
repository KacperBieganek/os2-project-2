//
// Created by kacper on 19.04.18.
//

#include "TetrisWindow.hpp"
#include <unistd.h>

namespace tetris
{
    TetrisWindow::TetrisWindow(WINDOW *window,
                               std::atomic<bool> &running,
                               std::deque<Block> &block_queue,
                               std::mutex &collection_mutex,
                               std::mutex &ncurses_mutex,
                               std::condition_variable &cv,
                               int window_height,
                               int window_width) :
            window(window),
            running(running),
            block_queue(block_queue),
            collection_mutex(collection_mutex),
            ncurses_mutex(ncurses_mutex),
            cv(cv),
            window_height(window_height),
            window_width(window_width) {
    };

    void TetrisWindow::run() {
        while (running) {
            Block block = blockGenerator.generateBlock();
            drawFallingBlock(block);
            {
                std::lock_guard<std::mutex> lock(collection_mutex);
                block_queue.push_back(block);
            }
            cv.notify_one();
        }
    }

    void TetrisWindow::drawFallingBlock(Block block) {
        bool falling = true;
        int y = 0, x = rand() % (window_width - 4) + 2;
        while (falling) {
            usleep(75000);
            std::lock_guard<std::mutex> lock(ncurses_mutex);
            wclear(window);
            box(window, 0, ' ');
            for (auto point : block.relative_point_cords) {
                wattron(window,COLOR_PAIR(block.color_pair));
                if (y + point.first > 0 && y + point.first < window_height)
                    mvwprintw(window, y + point.first, x + point.second, " ");
                wattroff(window,COLOR_PAIR(block.color_pair));
            }
            y += 1;
            if (y == window_height)
                falling = false;
            wrefresh(window);
        }

    }

}
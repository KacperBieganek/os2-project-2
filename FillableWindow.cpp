//
// Created by kacper on 12.04.18.
//

#include "FillableWindow.hpp"

namespace tetris
{
    FillableWindow::FillableWindow(WINDOW *window,
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

    void FillableWindow::run() {
        while (running) {
            std::unique_lock<std::mutex> lock(collection_mutex);
            cv.wait(lock);
            Block block = block_queue.front();
            block_queue.pop_front();
            lock.unlock();
            drawBlock(block);
        }
    }

    void FillableWindow::drawBlock(Block block) {
        int y = rand() % (window_height - 5) + 2, x = rand() % (window_width - 3) + 2;
        {
            std::lock_guard<std::mutex> lock(ncurses_mutex);
            for (auto point : block.relativePointCords)
                mvwprintw(window, y + point.first, x + point.second, &block.charToDraw);
            wrefresh(window);
        }
    }
}
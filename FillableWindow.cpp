//
// Created by kacper on 12.04.18.
//

#include "FillableWindow.hpp"

namespace tetris
{
    FillableWindow::FillableWindow(WINDOW *window,
                                   std::atomic<bool> &running,
                                   std::deque<Block> &blockQueue,
                                   std::mutex &collectionMutex,
                                   std::mutex &ncursesMutex,
                                   std::condition_variable &cv,
                                   int windowHeight,
                                   int windowWidth) :
            window(window),
            running(running),
            blockQueue(blockQueue),
            collectionMutex(collectionMutex),
            ncursesMutex(ncursesMutex),
            cv(cv),
            windowHeight(windowHeight),
            windowWidth(windowWidth) {
    };

    void FillableWindow::run() {
        while (running) {
            std::unique_lock<std::mutex> lock(collectionMutex);
            cv.wait(lock);
            Block block = blockQueue.front();
            blockQueue.pop_front();
            lock.unlock();
            drawBlock(block);
        }
    }

    void FillableWindow::drawBlock(Block block) {
        int y = rand() % (windowHeight - 5) + 2, x = rand() % (windowWidth - 3) + 2;
        {
            std::lock_guard<std::mutex> lock(ncursesMutex);
            for (auto point : block.relativePointCords)
                mvwprintw(window, y + point.first, x + point.second, &block.charToDraw);
            wrefresh(window);
        }
    }
}
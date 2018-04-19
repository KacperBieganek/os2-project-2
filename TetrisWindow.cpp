//
// Created by kacper on 19.04.18.
//

#include "TetrisWindow.hpp"
#include <unistd.h>

namespace tetris
{
    TetrisWindow::TetrisWindow(WINDOW *window,
                               std::atomic<bool> &running,
                               std::deque <Block> &blockQueue,
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

    void TetrisWindow::run() {
        while (running) {
            Block block = blockGenerator.generateBlock();
            drawFallingBlock(block);
            {
                std::lock_guard <std::mutex> lock(collectionMutex);
                blockQueue.push_back(block);
            }
            cv.notify_one();
        }
    }

    void TetrisWindow::drawFallingBlock(Block block) {
        bool falling = true;
        int y = 0, x = rand() % (windowWidth - 4) + 2;
        while (falling) {
            usleep(75000);
            std::lock_guard <std::mutex> lock(ncursesMutex);
            wclear(window);
            box(window, 0, ' ');
            for (auto point : block.relativePointCords) {
                if (y + point.first > 0 && y + point.first < windowHeight)
                    mvwprintw(window, y + point.first, x + point.second, &block.charToDraw);
            }
            y += 1;
            if (y == windowHeight)
                falling = false;
            wrefresh(window);
        }

    }

}
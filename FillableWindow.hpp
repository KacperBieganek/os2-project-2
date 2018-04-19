//
// Created by kacper on 12.04.18.
//

#ifndef TETRIS_FILLABLEWINDOW_HPP
#define TETRIS_FILLABLEWINDOW_HPP

#include <ncurses.h>
#include <mutex>
#include <atomic>
#include <deque>
#include <condition_variable>
#include "Block.hpp"

namespace tetris
{
    class FillableWindow
    {
    private:
        WINDOW *window;
        std::atomic<bool> &running;
        std::deque<Block> &blockQueue;
        std::mutex &ncursesMutex;
        std::mutex &collectionMutex;
        std::condition_variable &cv;
        int windowHeight;
        int windowWidth;


        void drawBlock(Block block);

    public:
        FillableWindow(WINDOW *window,
                       std::atomic<bool> &running,
                       std::deque<Block> &blockQueue,
                       std::mutex &collectionMutex,
                       std::mutex &ncursesMutex,
                       std::condition_variable &cv,
                       int windowHeight,
                       int windowWidth);

        void run();

    };
}

#endif //TETRIS_FILLABLEWINDOW_HPP

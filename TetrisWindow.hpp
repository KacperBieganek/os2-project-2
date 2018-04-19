//
// Created by kacper on 19.04.18.
//

#ifndef TETRIS_TETRISWINDOW_HPP
#define TETRIS_TETRISWINDOW_HPP

#include <ncurses.h>
#include <memory>
#include <mutex>
#include <atomic>
#include <deque>
#include "BlockGenerator.hpp"
#include <condition_variable>


namespace tetris
{
    class TetrisWindow
    {
    private:
        WINDOW *window;
        std::atomic<bool> &running;
        std::deque <Block> &blockQueue;
        std::mutex &ncursesMutex;
        std::mutex &collectionMutex;
        std::condition_variable &cv;
        int windowHeight;
        int windowWidth;
        BlockGenerator blockGenerator;

        void drawFallingBlock(Block block);

    public:
        TetrisWindow(WINDOW *window,
                     std::atomic<bool> &running,
                     std::deque <Block> &blockQueue,
                     std::mutex &collectionMutex,
                     std::mutex &ncursesMutex,
                     std::condition_variable &cv,
                     int windowHeight,
                     int windowWidth);


        void run();

    };
}

#endif //TETRIS_TETRISWINDOW_HPP

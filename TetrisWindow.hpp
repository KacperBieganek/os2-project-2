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
        std::deque <Block> &block_queue;
        std::mutex &ncurses_mutex;
        std::mutex &collection_mutex;
        std::condition_variable &cv;
        int window_height;
        int window_width;
        BlockGenerator blockGenerator;

        void drawFallingBlock(Block block);

    public:
        TetrisWindow(WINDOW *window,
                     std::atomic<bool> &running,
                     std::deque <Block> &block_queue,
                     std::mutex &collection_mutex,
                     std::mutex &ncurses_mutex,
                     std::condition_variable &cv,
                     int window_height,
                     int window_width);


        void run();

    };
}

#endif //TETRIS_TETRISWINDOW_HPP

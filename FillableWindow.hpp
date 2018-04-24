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
        std::deque<Block> &block_queue;
        std::mutex &ncurses_mutex;
        std::mutex &collection_mutex;
        std::condition_variable &cv;
        int window_height;
        int window_width;


        void drawBlock(Block block);

    public:
        FillableWindow(WINDOW *window,
                       std::atomic<bool> &running,
                       std::deque<Block> &block_queue,
                       std::mutex &collection_mutex,
                       std::mutex &ncurses_mutex,
                       std::condition_variable &cv,
                       int window_height,
                       int window_width);

        void run();

    };
}

#endif //TETRIS_FILLABLEWINDOW_HPP

//
// Created by kacper on 12.04.18.
//

#ifndef TETRIS_FILLABLEWINDOW_HPP
#define TETRIS_FILLABLEWINDOW_HPP

#include <ncurses.h>
#include <memory>
#include <mutex>
#include <atomic>
#include "Block.hpp"
#include <stack>

namespace tetris
{
    class FillableWindow
    {
    private:
        std::unique_ptr <WINDOW> window;
        std::atomic<bool> running;
        std::stack <Block> blockStack;
        std::mutex ncursesMutex;
        std::mutex collectionMutex;
        int windowHeight;
        int windowWidth;


        void drawBlock();

    public:
        explicit FillableWindow();

        void run();

    };
}

#endif //TETRIS_FILLABLEWINDOW_HPP

//
// Created by kacper on 19.04.18.
//

#ifndef TETRIS_TETRISWINDOW_HPP
#define TETRIS_TETRISWINDOW_HPP

#include <ncurses.h>
#include <memory>
#include <mutex>
#include <atomic>
#include <stack>
#include "Block.hpp"


namespace tetris
{
    class TetrisWindow
    {
    private:
        std::unique_ptr <WINDOW> window;
        std::atomic<bool> running;
        std::stack <Block> blockStack;
        std::mutex ncursesMutex;
        std::mutex collectionMutex;
        int windowHeight;
        int windowWidth;


    };
}

#endif //TETRIS_TETRISWINDOW_HPP

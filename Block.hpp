//
// Created by kacper on 12.04.18.
//

#ifndef TETRIS_BLOCK_HPP
#define TETRIS_BLOCK_HPP

#include <vector>
#include <utility>
#include <string>

namespace tetris
{
    struct Block
    {
        std::vector <std::pair<int, int>> relativePointCords;
        std::pair<int, int> basePosition;
        char charToDraw;

        Block(std::vector <std::pair<int, int>> relativePointCords, char charToDraw) :
                relativePointCords(relativePointCords),
                charToDraw(charToDraw) {


        };

    };
}

#endif //TETRIS_BLOCK_HPP

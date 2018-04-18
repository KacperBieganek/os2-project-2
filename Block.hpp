//
// Created by kacper on 12.04.18.
//

#ifndef TETRIS_BLOCK_HPP
#define TETRIS_BLOCK_HPP

#include <vector>
#include <utility>

namespace tetris
{
    struct Block
    {
        std::vector <std::pair<int, int>> relativePointCords;
        std::pair<int, int> basePosition;

        Block(std::vector <std::pair<int, int>> relativePointCords);

    };
}

#endif //TETRIS_BLOCK_HPP

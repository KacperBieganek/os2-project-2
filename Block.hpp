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
        std::vector <std::pair<int, int>> relative_point_cords;
        int color_pair;

        Block(std::vector <std::pair<int, int>> relative_point_cords, int color_pair) :
                relative_point_cords(relative_point_cords),
                color_pair(color_pair) {


        };

    };
}

#endif //TETRIS_BLOCK_HPP

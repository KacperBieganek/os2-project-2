//
// Created by kacper on 19.04.18.
//

#ifndef TETRIS_BLOCKGENERATOR_HPP
#define TETRIS_BLOCKGENERATOR_HPP

#include "Block.hpp"

namespace tetris
{
    class BlockGenerator
    {
    private:
        std::vector <std::pair<int, int>> relativePointCordsCombination{{-1, -1},
                                                                        {-1, 0},
                                                                        {-1, 1},
                                                                        {0,  -1},
                                                                        {0,  0},
                                                                        {0,  1},
                                                                        {1,  -1},
                                                                        {1,  0},
                                                                        {1,  1}};
    public:
        BlockGenerator() {};

        Block generateBlock();

    };
}

#endif //TETRIS_BLOCKGENERATOR_HPP

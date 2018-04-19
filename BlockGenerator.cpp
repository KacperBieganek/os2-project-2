//
// Created by kacper on 19.04.18.
//

#include "BlockGenerator.hpp"
#include <stdlib.h>

namespace tetris
{
    Block BlockGenerator::generateBlock() {
        std::vector <std::pair<int, int>> relativePoints;
        for (size_t i = 0; i < 9; i++)
            if (rand() % 2)
                relativePoints.push_back(this->relativePointCordsCombination[i]);
        char c = (char) (rand() % 26 + (int) 'A');
        return Block{relativePoints, c};
    }
}
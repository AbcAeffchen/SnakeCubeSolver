//
// Created by Alex Schickedanz <alex@ae.cs.uni-frankfurt.de> on 17.01.19.
//

#ifndef SNAKECUBE_SOLVER_H
#define SNAKECUBE_SOLVER_H

#include <vector>
#include <cassert>
#include <iostream>

enum directions
{
    UP = 1, DOWN = 6, LEFT = 4, RIGHT = 3, FRONT = 2, BACK = 5
};

struct point
{
    char x, y, z;

    constexpr void moveStep(const directions dir)
    {
        switch(dir)
        {
            case UP:
                z++;
                break;
            case DOWN:
                z--;
                break;
            case LEFT:
                x++;
                break;
            case RIGHT:
                x--;
                break;
            case FRONT:
                y++;
                break;
            case BACK:
                y--;
                break;
        }
    }
};

constexpr unsigned long xDim = 0;
constexpr unsigned long yDim = 1;
constexpr unsigned long zDim = 2;

template<char size>
class Hull
{
    std::vector<bool> outerCube = std::vector<bool>(8ul * size * size * size, false);
    std::vector<char> borders = std::vector<char>(6, 0);

    template<unsigned long dim>
    void updateRange(const char v)
    {
        if(borders[2 * dim] > v)
            borders[2 * dim] = v;
        else if(borders[2 * dim + 1] < v)
            borders[2 * dim + 1] = v;
    }

    bool checkInHull(const char v) const
    {
        return -size < v && v < size;
    }

    template<unsigned long dim>
    bool checkRange(const char v) const
    {
        if(!checkInHull(v))
            return false;

        if(borders[2 * dim] <= v && v <= borders[2 * dim + 1])
            return true;

        return borders[2 * dim + 1] - borders[2 * dim] < size - 1;
    }

    constexpr unsigned long coordinateToLong(const point& p) const
    {
        return (p.x + size - 1)
               + (2ul * size) * (p.y + size - 1)
               + (4ul * size * size) * (p.z + size - 1);
    }

    bool checkValid(const point& p) const
    {
        return checkRange<xDim>(p.x) && checkRange<yDim>(p.y) && checkRange<zDim>(p.z)
               && !outerCube[coordinateToLong(p)];
    }

public:
    Hull()
    {
        outerCube[coordinateToLong({0, 0, 0})] = true;
    }

    bool use(const point& p)
    {
        if(!checkValid(p))
            return false;

        outerCube[coordinateToLong(p)] = true;
        updateRange<xDim>(p.x);
        updateRange<yDim>(p.y);
        updateRange<zDim>(p.z);

        return true;
    }
};

#endif //SNAKECUBE_SOLVER_H

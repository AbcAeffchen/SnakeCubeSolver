#include <utility>

//
// Created by Alex Schickedanz <alex@ae.cs.uni-frankfurt.de> on 17.01.19.
//

#ifndef SNAKECUBE_WALKER_H
#define SNAKECUBE_WALKER_H

#include "Hull.h"
#include <iostream>

template<char size, bool countPlacements = false>
class Walker
{
    using solution_type = std::vector<directions>;
    using segment_type = unsigned char;
    using segment_list_type = std::vector<segment_type>;

    const segment_list_type segmentList;

    unsigned long placementsCount = 0;

    void print(const solution_type& s) const
    {
        for(auto a : s)
        {
            switch(a)
            {
                case UP: std::cout << "UP"; break;
                case DOWN: std::cout << "DOWN"; break;
                case LEFT: std::cout << "LEFT"; break;
                case RIGHT: std::cout << "RIGHT"; break;
                case BACK: std::cout << "BACK"; break;
                case FRONT: std::cout << "FRONT"; break;
            }
            std::cout << ", ";
        }

        std::cout << std::endl;
    }

    void printStatistic() const
    {
        std::cout << "Placements: " << placementsCount << std::endl;
    }

    template<int i>
    directions getNextDirection(const directions prevDirection) const
    {
        switch(i)
        {
            case 0: return (prevDirection == UP || prevDirection == DOWN) ? FRONT : UP;
            case 1: return (prevDirection == RIGHT || prevDirection == LEFT) ? FRONT : RIGHT;
            case 2: return (prevDirection == RIGHT || prevDirection == LEFT) ? BACK : LEFT;
            case 3: return (prevDirection == UP || prevDirection == DOWN) ? BACK : DOWN;
            default: assert(false);
        }
    }

    bool placeSegment(Hull<size>& h, point& p, const segment_type length, const directions direction)
    {
        if constexpr (countPlacements)
            placementsCount++;

        for(unsigned int i = 0; i < length; i++)
        {
            p.moveStep(direction);

            if(!h.use(p))
                return false;
        }

        return true;
    }

    void recursiveSearch(Hull<size> h, point p, unsigned long nextSegmentIndex, solution_type& solution)
    {
        const auto prevDirection = solution[nextSegmentIndex - 1];
        if(!placeSegment(h, p, segmentList[nextSegmentIndex - 1], prevDirection))
            return;

        if(segmentList.size() < nextSegmentIndex + 1)
        {
            print(solution);
            if constexpr (countPlacements)
                printStatistic();

            return;
        }

        solution[nextSegmentIndex] = getNextDirection<0>(prevDirection);
        recursiveSearch(h, p, nextSegmentIndex + 1, solution);
        solution[nextSegmentIndex] = getNextDirection<1>(prevDirection);
        recursiveSearch(h, p, nextSegmentIndex + 1, solution);
        solution[nextSegmentIndex] = getNextDirection<2>(prevDirection);
        recursiveSearch(h, p, nextSegmentIndex + 1, solution);
        solution[nextSegmentIndex] = getNextDirection<3>(prevDirection);
        recursiveSearch(h, p, nextSegmentIndex + 1, solution);
    }

public:
    explicit Walker(segment_list_type segmentList)
        : segmentList(std::move(segmentList))
    {}

    void search()
    {
        Hull<size> h;
        point p{0,0,0};

        solution_type solution(segmentList.size());
        solution[0] = BACK;
        solution[1] = RIGHT;

        placeSegment(h, p, segmentList[0], solution[0]);
        recursiveSearch(h, p, 2, solution);
    }
};

#endif //SNAKECUBE_WALKER_H

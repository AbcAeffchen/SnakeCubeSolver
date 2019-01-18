
#include "Walker.h"
#include <ctime>

int main()
{
    Walker<4> w({2, 1, 2, 1, 1, 3, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 3, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1});

    const clock_t begin = clock();

    w.search();

    const clock_t end = clock();

    std::cout << static_cast<double>(end - begin) / CLOCKS_PER_SEC << "s" << std::endl;

    return 0;
}

#include "Walker.h"

int main()
{
    Walker<4> w({2, 1, 2, 1, 1, 3, 1, 2, 1, 2, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 2, 2, 1, 1, 1, 1, 1, 2, 3, 1, 1, 1, 3, 1, 2, 1, 1, 1, 1, 1, 1, 1, 1, 1, 3, 1});
//    Walker<3> w({2, 1, 1, 2, 1, 2, 1, 1, 2, 2, 1, 1, 1, 2, 2, 2, 2});

    auto begin = omp_get_wtime();

    w.search<false>();

    std::cout << (omp_get_wtime() - begin) << "s" << std::endl;

    return 0;
}

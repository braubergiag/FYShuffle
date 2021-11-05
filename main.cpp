
#include "FYShuffle.h"

int main() {


    int32_t  permutation_length = 100; // Длина перестановки
    int32_t sample_size = 10e5; // Объем выборки
    int32_t target_cycle_size = 3;

    FYShuffle fyShuffle(permutation_length,sample_size,target_cycle_size);
    fyShuffle.GenerateSamplesStatistics();



    return 0;
}
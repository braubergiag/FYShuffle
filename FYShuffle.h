

#ifndef VP_4_FYSHUFFLE_H
#define VP_4_FYSHUFFLE_H

#include <string>
#include <iostream>

#include <vector>
#include <random>
#include <algorithm>
#include <chrono>
#include <fstream>
#include <map>



class FYShuffle {
public:
    FYShuffle(uint32_t permutationSize, uint32_t sampleSize,uint32_t cycle_size);
    ~FYShuffle();
    void GenerateSamplesStatistics();
private:
    void Init();
    void FisherYatesShuffle();
    void FindCycles();
    void WritePermutation();
    void WriteCycleStatistics();

private:
    uint64_t m_seed = 0;
    std::mt19937 m_generator;



    uint32_t  m_permutationSize = 0;
    uint32_t  m_sampleSize = 0;
    uint8_t m_cycle_size = 0;
    std::vector<uint32_t > m_x;
    std::map<uint32_t,uint32_t > m_cycles_amount;

    std::ofstream out1,out2;

};


#endif //VP_4_FYSHUFFLE_H

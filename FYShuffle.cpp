//
// Created by glushkov on 05.11.2021.
//

#include "FYShuffle.h"


FYShuffle::FYShuffle(uint32_t permutationSize, uint32_t sampleSize,uint32_t cycle_size)
:m_permutationSize(permutationSize), m_sampleSize(sampleSize),m_cycle_size(cycle_size){
    m_seed = std::chrono::system_clock::now().time_since_epoch().count();
    m_generator.seed(m_seed);
    Init();

}
FYShuffle::~FYShuffle() {

    if (out1) out1.close();
    if (out2) out2.close();
}




void FYShuffle::GenerateSamplesStatistics(){
    for (size_t i = 0 ; i < m_sampleSize; ++i){
        FisherYatesShuffle();
        WritePermutation();
        FindCycles();
    }
    WriteCycleStatistics();

}
void FYShuffle::Init(){
    out1.open("permutations.csv");
    out2.open("cycles.csv");
    m_x.resize(m_permutationSize,0);

    for (size_t i = 0; i < m_permutationSize; ++i){
        m_x[i] = i;

    }
    WritePermutation();



}
void FYShuffle::FisherYatesShuffle(){

    double tau = 0;
    for (size_t i = m_permutationSize - 1; i > 0; --i){
        tau = std::uniform_int_distribution<int>(0, i)(m_generator);
        std::swap(m_x[i],m_x[tau]);

    }

}
void FYShuffle::FindCycles(){
    std::vector<bool> used(m_permutationSize);
    uint32_t cycles_counter= 0;
    for (size_t i = 0; i < m_permutationSize; ++i){

        if (not used[i]) {

            size_t j = i;
            std::vector<uint32_t> cycle;
            while (not used[j]) {
                cycle.push_back(m_x[j]);
                used[j] = true;
                j = m_x[j];
            }
            if (cycle.size() == m_cycle_size){
                ++cycles_counter;
            }



        }
    }
    ++m_cycles_amount[cycles_counter];

}

void FYShuffle::WritePermutation(){
    for (size_t i = 0; i < m_permutationSize; ++i){


        if (i == m_permutationSize - 1) {
            out1 << m_x[i];
        } else {
            out1 << m_x[i] << " ";
        }


    }
    out1 << "\n";
}
void FYShuffle::WriteCycleStatistics(){


    out2 << "n" << " " << "frequency" << "\n";
    for (const auto & [key,value]: m_cycles_amount){
        out2 << key << " " << value << "\n";

    }

}
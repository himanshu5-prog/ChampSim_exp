#include <algorithm>
#include <array>
#include <bitset>
#include <map>
#include <cassert>

#include "msl/fwcounter.h"
#include "ooo_cpu.h"

namespace{
    //Constants-------------------------------------
    constexpr std::size_t LOCAL_HISTORY_LENGTH = 14;
    constexpr std::size_t COUNTER_BITS = 2;
    constexpr std::size_t LOCAL_HISTORY_TABLE_SIZE = 16384;
    constexpr std::size_t PREDICTION_TABLE_SIZE = 16384;
    //---------------------------------------------------
    // typedefs------------------------------------------------------------------------------------------
    typedef std::bitset<LOCAL_HISTORY_LENGTH> LocalHistoryRegister; // Local history register

    // typedef: Array of local history registers---------------------------------------------------
    typedef std :: array <LocalHistoryRegister, LOCAL_HISTORY_TABLE_SIZE> HistoryTable; 
    //----------------------------------------------------------------------------

    // typedef: Array of prediction counter
    typedef std :: array <champsim::msl::fwcounter<COUNTER_BITS>, PREDICTION_TABLE_SIZE> PredictElement;
    //---------------------------------------------------------------------------------------------------
    std :: map <O3_CPU*, HistoryTable> LocalHistoryTable;
    std :: map <O3_CPU*, PredictElement> BranchPredictionTable;
    const std::size_t Mask = 0x3FF;

    std :: size_t getLocalHistoryIndex (uint64_t ip){
        assert ( (ip & ::Mask) < ::LOCAL_HISTORY_TABLE_SIZE);

        return (ip & ::Mask);
    }
}



void O3_CPU::initialize_branch_predictor() {}

uint8_t O3_CPU::predict_branch(uint64_t ip){
    //----------------------------------------------------------
    auto localHistIndex = getLocalHistoryIndex(ip);
    auto localHistReg = ::LocalHistoryTable[this][localHistIndex];
    ///-----------------------------------------------------------
    auto prediction = ::BranchPredictionTable[this][localHistReg.to_ullong()];

    return (prediction.value() >= 1);

}

void O3_CPU::last_branch_result(uint64_t ip, uint64_t branch_target, uint8_t taken, uint8_t branch_type){
   
   //-------
    auto localHistIndex = getLocalHistoryIndex(ip);
    auto localHistReg = ::LocalHistoryTable[this][localHistIndex];
    ///-------
   auto x = localHistReg.to_ullong();
    
    if (taken){
        ::BranchPredictionTable[this][x] += 1;
    } else {
        ::BranchPredictionTable[this][x] -= 1;
    }

    x = getLocalHistoryIndex(ip);

    ::LocalHistoryTable[this][x] = ::LocalHistoryTable[this][x] << 1;
    ::LocalHistoryTable[this][x][0] = taken;
    


}
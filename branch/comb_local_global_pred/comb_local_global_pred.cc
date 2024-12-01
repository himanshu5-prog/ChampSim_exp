#include <algorithm>
#include <array>
#include <bitset>
#include <map>
#include <cassert>

#include "msl/fwcounter.h"
#include "ooo_cpu.h"

namespace {
    // Local 

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

    // Global
    constexpr std::size_t GLOBAL_HISTORY_LENGTH = 14;
    //constexpr std::size_t COUNTER_BITS = 2;
    constexpr std::size_t GS_HISTORY_TABLE_SIZE = 16384;

    std::map<O3_CPU*, std::bitset<GLOBAL_HISTORY_LENGTH>> branch_history_vector;
    std::map<O3_CPU*, std::array<champsim::msl::fwcounter<COUNTER_BITS>, GS_HISTORY_TABLE_SIZE>> gs_history_table;

    std::size_t gs_table_hash(uint64_t ip, std::bitset<GLOBAL_HISTORY_LENGTH> bh_vector)
    {
        std::size_t hash = bh_vector.to_ullong();
        hash ^= ip;
        hash ^= ip >> GLOBAL_HISTORY_LENGTH;
        hash ^= ip >> (GLOBAL_HISTORY_LENGTH * 2);

        return hash % GS_HISTORY_TABLE_SIZE;
    }
    //---------------------------------
    bool takeLocal;
    bool currentPred;
}

void O3_CPU::initialize_branch_predictor() {
    ::takeLocal = false;
    
}

uint8_t O3_CPU::predict_branch(uint64_t ip){

    if (::takeLocal){
    
        // Local
         //----------------------------------------------------------
        auto localHistIndex = getLocalHistoryIndex(ip);
        auto localHistReg = ::LocalHistoryTable[this][localHistIndex];
        ///-----------------------------------------------------------
        auto prediction = ::BranchPredictionTable[this][localHistReg.to_ullong()];
        ::currentPred = (prediction.value() >= 1);
        return (prediction.value() >= 1);

    }  
    // global
    auto gs_hash = ::gs_table_hash(ip, ::branch_history_vector[this]);
    auto value = ::gs_history_table[this][gs_hash];
    ::currentPred = (value.value() >= (value.maximum / 2));
    return value.value() >= (value.maximum / 2);
    
}

void O3_CPU::last_branch_result(uint64_t ip, uint64_t branch_target, uint8_t taken, uint8_t branch_type){
    // Local
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

    // Global
    auto gs_hash = gs_table_hash(ip, ::branch_history_vector[this]);
    ::gs_history_table[this][gs_hash] += taken ? 1 : -1;

    // update branch history vector
    ::branch_history_vector[this] <<= 1;
    ::branch_history_vector[this][0] = taken;

    if ((::currentPred && !taken) || (!(::currentPred) && taken)){
        ::takeLocal = !(::takeLocal);
    }
}
#include <algorithm>
#include <cassert>
#include <map>
#include <vector>

#include "cache.h"

typedef std :: vector <std :: vector <uint32_t> > TABLE;
namespace FIFO {
    std :: map <CACHE*, TABLE> fifo_table;
}

void 
CACHE :: initialize_replacement(){
    FIFO::fifo_table[this] = TABLE(NUM_SET, std::vector<uint32_t> (NUM_WAY, 0));
}

uint32_t CACHE::find_victim(uint32_t triggering_cpu, uint64_t instr_id, uint32_t set, const BLOCK* current_set, uint64_t ip, uint64_t full_addr, uint32_t type){
    uint32_t id;
    id = 0;
    for (uint32_t i = 1; i < NUM_WAY; ++i){
        if (FIFO::fifo_table[this][set][i] < FIFO::fifo_table[this][set][i-1]){
            id = i;
        }
    }
    return id;
}

void CACHE::update_replacement_state(uint32_t triggering_cpu, uint32_t set, uint32_t way, uint64_t full_addr, uint64_t ip, uint64_t victim_addr, uint32_t type,
                                     uint8_t hit)
{
    assert(set < NUM_SET);
    assert(way < NUM_WAY);

    if (!hit){
        FIFO::fifo_table[this][set][way] = current_cycle;
    }

}

void CACHE::replacement_final_stats() {}
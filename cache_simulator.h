/*
Yuntao Li
yli346@jh.edu

Fangjie Li
fli35@jh.edu
*/
#ifndef CACHE_SIMULATOR_H
#define CACHE_SIMULATOR_H

#include <iostream>
#include <vector>
#include <sstream>
#include <math.h>
#include <map>
#include <utility>
#include <math.h>

#define ADDR_LEN 32 // 32 bit system
#define SAVE 0
#define LOAD 1
#define LRU 1
#define FIFO 0
#define WRITE_ALLOC 1
#define NO_WRITE_ALLOC 0
#define WRITE_BACK 1
#define WRITE_THRU 0


struct struct_addr {
    public:
        unsigned offset; // should never be used
        unsigned index;
        unsigned tag; 
};

struct metric {
    public:
        std::pair<int, int> cac_op_num;  // save, load
        std::pair<int, int> mem_op_num;  // save, load
        std::pair<int, int> load_hm; // load hit, miss
        std::pair<int, int> save_hm; // save hit, miss
        long tot_cycle;
};

struct block {
    // TODO: properly select the block type to account for various valid bit/address/etc
    public:
        std::pair<long, unsigned> content;
        int is_dirty;
};

struct set {
    public:
        std::vector<block> blocks;
        // for LRU: used to store the previously accessed block indx
        // for FIFO: used to store the current index of access.
        long stat; 
};

class cache_simulator {
    private:
        int is_write_alloc; // 1 = write-allocate, 0 = no-write-allocate
        int write_bt; // 1 = write-back, 0 = write-through
        int evict_type; // 1 = LRU, 0 = FIFO
        unsigned set_num; // # of set
        unsigned block_per_set; // # of block per set
        unsigned byte_per_block; // size of block (byte)
        unsigned idx_bnum; // # of bits for set index
        unsigned ofst_bnum; // # of bits for block offset
        std::vector<set> sets; // a vector of sets.
        metric sim_metric;

    public:
    cache_simulator(unsigned int n_set_num, unsigned int n_block_per_set, unsigned int n_byte_per_block, 
                    int n_is_write_alloc, int is_write_back, int n_evict_type);
    
    void load_data (struct_addr addr);
    void save_data (struct_addr addr);
    // given a memory address, returns the corresponding set index, tag, etc
    struct_addr get_struct_addr(unsigned raw_addr);
    // given a set index and block id, evict the block
    std::pair<int, int> fetch_evict_block(struct_addr addr, int op_type); // save/load
    // given a set index and tag, returns true if it is a hit.
    int is_hit(struct_addr);
    void process_ops(std::vector<std::pair<char, unsigned>>& ops);
    void flush_cache();
    void print_metrics(); // print the metrics
    void print_cache(); // print the cache content for debug
    
    void restart_cache();
    // get/sets for debugging tec
    metric get_metrics();
    unsigned get_set_num();
    unsigned get_block_per_set();
    unsigned get_byte_per_block();
    unsigned get_idx_bnum();
    unsigned get_ofst_bnum();
};

int read_traces(std::vector<std::pair<char, unsigned>>& vec_buffer);
int check_power_of_two(int num);
#endif


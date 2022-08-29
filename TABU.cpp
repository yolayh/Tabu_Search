#include "TABU.hpp"

int main(int argc, char *argv[]){

    const int bit = atoi(argv[1]);
    const int run = atoi(argv[2]);
    const int iteration = atoi(argv[3]);
    const int capacity = atoi(argv[4]);
    
    execution(bit, run, iteration, capacity);

    return 0;

}
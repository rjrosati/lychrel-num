//#include <gmpxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <iostream>
#include <sstream>
#include <omp.h>
#include "mpi.h"

#include "bigint.h"

#define STEP_LIMIT 310 
#define PRINT_LIMIT 150

typedef unsigned long long ull;
// generate a first-order consequence
// The idea here is to start at the first iteration of reversal-addition, rather than
//     the zeroth. This should eliminate seeds that converge to the same chain.
//     I expect a reduction in cases of ~5^10 for 21-digit ints. 
//     It would be awesome if I could figure out how to create higher-order consequences.
bigint gen_foc(int d, ull seed) { 
    bigint i(0,RADIX); i.digits.reserve(d);
    for (int j=0;j<d/2;j++) {
        i.digits.push_back(seed%(2*RADIX-1));
        seed /= (2*RADIX-1);
    }
    if (d%2 == 1) i.digits.push_back((seed%RADIX)*2);
    for (int j=d/2;j>0;j--) {
        i.digits.push_back(i.digits[j-1]);
    }
    i.resolve_carries();
    i.remove_leading_zero();
    return i;
}

int main(int argc, char* argv[]) {
    int provided;
    MPI_Init_thread(&argc,&argv,MPI_THREAD_FUNNELED,&provided); // master must make all MPI calls
    if (provided != MPI_THREAD_FUNNELED) MPI_Abort(MPI_COMM_WORLD,-2);
    int myrank,mysize;
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&mysize);
    omp_set_num_threads(1);//omp_get_num_procs());

    if (myrank==0) {
        if (argc != 2) {
            std::cout<<"Usage:"<<std::endl
                <<"\t./findchain [number of digits to search]"<<std::endl;
            MPI_Abort(MPI_COMM_WORLD,-1);
        }
    }

    int d = std::stoi(argv[1]);
    ull nums = 0;
    if (d%2==0)
        nums = pow((ull)2*RADIX-1,d/2);
    else
        nums = pow((ull)2*RADIX-1,d/2)*RADIX;

    ull minseed = myrank*nums/mysize+1;
    ull maxseed = (myrank+1)*nums/mysize+1;
    if (myrank == 0) {
        std::cout<<"checking all "<<d<<" digit integers. will check "<<nums<<" cases"<<std::endl;
        std::cout<<"checking for palindromic sequences shorter than "<<STEP_LIMIT<<" steps"<<std::endl;
        std::cout<<"will print if more than "<<PRINT_LIMIT<<" steps"<<std::endl;
        std::cout<<mysize<<" nodes"<<std::endl;
        std::cout<<omp_get_max_threads()<<" threads each"<<std::endl;
    }

    #pragma omp parallel shared(minseed,maxseed) 
    {
        int steps=0;
        #ifndef QUIET
        int numcases = 0;
        int steptimer=0;
        double tic=0,toc=0;
        #endif

        #pragma omp for schedule(dynamic,10000)
        for (ull seed=minseed; seed<maxseed; seed++) {
            bigint x = gen_foc(d,seed); 
            for (steps=0;steps <= STEP_LIMIT;steps++) {
                if (x.is_palindrome()) break;
                x.revadd();
            }
            if (steps<STEP_LIMIT+1 && steps > PRINT_LIMIT)
                std::cout<<std::string(gen_foc(d,seed))<<","<<steps<<","<<std::string(x)<<std::endl;
                // could modify this to find smallest initial int and print that out.

            #ifndef QUIET
            steptimer+=steps;
            if (i%100000 == 0) {
                tic = omp_get_wtime();
                steptimer = 0;
            } else if (i%100000 == 99999) {
                toc = omp_get_wtime();
                std::cout<<steptimer/(toc-tic)<<" radds/sec"<<std::endl;
                steptimer = 0;
            }
            #endif
            
        }
    }

    MPI_Finalize();
    
    return 0;
}

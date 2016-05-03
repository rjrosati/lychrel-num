//#include <gmpxx.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <omp.h>
#include "mpi.h"

#include "bigint.h"

#define STEP_LIMIT 290 
#define PRINT_LIMIT 150

#define NUMS_PER_NODE (int)1e7

int main(int argc, char* argv[]) {
    int provided;
    MPI_Init_thread(&argc,&argv,MPI_THREAD_FUNNELED,&provided); // master must make all MPI calls
    if (provided != MPI_THREAD_FUNNELED) MPI_Abort(MPI_COMM_WORLD,-2);
    int myrank,mysize;
    MPI_Comm_rank(MPI_COMM_WORLD,&myrank);
    MPI_Comm_size(MPI_COMM_WORLD,&mysize);
    omp_set_num_threads(omp_get_num_procs());

    if (myrank==0) {
        if (argc != 2) {
            std::cout<<"Usage:"<<std::endl<<"\t./findchain [start of search as unsigned long long]"<<std::endl;
            MPI_Abort(MPI_COMM_WORLD,-1);
        }
    }

    bigint myinit(std::stoull(argv[1]),10);

    myinit = myinit + myrank*NUMS_PER_NODE; // so we'll cover mysize*NUMS_PER_NODE numbers in total
    if (myrank == 0) {
        std::cout<<"checking for palindromic sequences shorter than "<<STEP_LIMIT<<" steps"<<std::endl;
        std::cout<<"will print if more than "<<PRINT_LIMIT<<" steps"<<std::endl;
        std::cout<<"will search "<<std::string(myinit)<<" --> "<<std::string(myinit+mysize*NUMS_PER_NODE)<<std::endl;
        std::cout<<mysize<<" nodes"<<std::endl;
        std::cout<<omp_get_max_threads()<<" threads each"<<std::endl;
    }

    #pragma omp parallel shared(myinit) 
    {
        int steps=0;
        #ifndef QUIET
        int steptimer=0;
        double tic=0,toc=0;
        #endif
        #pragma omp for schedule(dynamic,NUMS_PER_NODE/1000)
        for (int i=0; i<NUMS_PER_NODE; i++) {
            bigint x = myinit+i;
            steps = 0;
            while (true) {
                if (x.is_palindrome()) break;
                ++x; // go deeper, reverse add self
                if (steps > STEP_LIMIT) break;
                steps++;
            }
            if (steps<STEP_LIMIT+1 && steps > PRINT_LIMIT) std::cout<<std::string(myinit+i)<<","<<steps<<","<<std::string(x)<<std::endl;

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

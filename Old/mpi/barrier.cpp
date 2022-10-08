#include<iostream>
#include<sys/time.h>
#include "mpi.h"
#include <unistd.h>

using namespace std;

void test(int& RankID){
    if (RankID==0){
        sleep(1);
        cout<<"ID:"<<RankID<<","<<"OK"<<endl;
    } else {
        cout<<"ID:"<<RankID<<","<<"OK"<<endl;
    }
    MPI_Barrier(MPI_COMM_WORLD);
    return;
}

int main(int argc, char * argv[]){
    int RankID;
    struct timeval start,stop;
    MPI_Init(&argc, &argv);
	MPI_Comm_rank(MPI_COMM_WORLD, &RankID);

    gettimeofday(&start,NULL);
    test(RankID);
    gettimeofday(&stop,NULL);
    std::cout<<RankID<<":"<<
            (stop.tv_sec-start.tv_sec)*1000.0+(stop.tv_usec-start.tv_usec)/1000.0
            <<"ms"<<std::endl;
    MPI_Finalize();
    return 0;
}
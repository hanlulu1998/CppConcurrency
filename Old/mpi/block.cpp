#include <iostream>
#include <mpi.h>
#include <string.h>
#include <sys/time.h>


int main(int argc, char* argv[]){
	MPI_Init(&argc, &argv);
	struct timeval start,stop;
	int RankID;
	int size;
	MPI_Comm_rank(MPI_COMM_WORLD, &RankID);
	MPI_Comm_size(MPI_COMM_WORLD, &size);
	if (0 == RankID){
		int SendData[409600];
		for (int i = 0; i < 409600; i++){
			SendData[i]=i;
		}

		gettimeofday(&start,NULL);
		for (int i = 1; i < size; i++){
			MPI_Send(SendData, 409600, MPI_INT, i, 99, MPI_COMM_WORLD);
		}
		gettimeofday(&stop,NULL);
        std::cout<<RankID<<":"<<
            (stop.tv_sec-start.tv_sec)*1000.0+(stop.tv_usec-start.tv_usec)/1000.0
            <<"ms"<<std::endl;
		std::cout <<RankID << ":" << "OK" << std::
		endl;
	}
	else{
		int RecvData[409600];
		MPI_Status Status;
		gettimeofday(&start,NULL);
		MPI_Recv(RecvData, 409600, MPI_INT, 0, 99, MPI_COMM_WORLD,&Status);
		gettimeofday(&stop,NULL);
        std::cout<<RankID<<":"<<
            (stop.tv_sec-start.tv_sec)*1000.0+(stop.tv_usec-start.tv_usec)/1000.0
            <<"ms"<<std::endl;
		std::cout <<RankID << ":" << "OK" << std::endl;
	}
	MPI_Finalize();
	return 0;
}

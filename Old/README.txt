MPI
==需要安装MPI实现！==
1.编译源文件MPICH（或者OpenMPI）
2.Ubuntu下 sudo apt install mpich（或者openmpi）
==hostfile(config)需要改！==
格式：
主机名1：进程数1
主机名2：进程数2
主机名2：进程数2
=======编译命令=======
mpicc同gcc
mpic++同g++
=======运行命令=======
mpirun -np 进程数 --hostfile hostfile文件 可执行文件
mpiexec -n 进程数 -f config文件 可执行文件

OpenMP
=======编译命令=======
g++
gcc
添加 -fopenmp 参数
=======运行命令=======
直接运行
#! /bin/bash
mpirun --hostfile ./hostfile -np ${2} ${1}

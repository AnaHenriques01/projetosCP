#!/bin/sh

#SBATCH --partition=cpar
#SBATCH --ntasks 4
#SBATCH -c 2

perf stat make runpar CP_CLUSTERS=4 THREADS=2
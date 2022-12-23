scp -r 'include' pg50184@s7edu2.di.uminho.pt:TP2;
scp -r 'src' pg50184@s7edu2.di.uminho.pt:TP2;
scp -r 'Makefile' pg50184@s7edu2.di.uminho.pt:TP2;
make clean
make k_means
make sbatch NTASKS=2 CP_CLUSTERS=4 THREADS=4
cat out.txt
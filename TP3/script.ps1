scp -r 'include' pg50196@s7edu2.di.uminho.pt:TP3;
scp -r 'src' pg50196@s7edu2.di.uminho.pt:TP3;
scp -r 'Makefile' pg50196@s7edu2.di.uminho.pt:TP3;
ssh pg50196@s7edu2.di.uminho.pt "cd TP3/; \
make clean; \
make k_means; \
make sbatch NTASKS=2 CP_CLUSTERS=4 THREADS=4"
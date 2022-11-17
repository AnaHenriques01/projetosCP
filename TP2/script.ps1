scp -r 'include' pg50184@s7edu2.di.uminho.pt:TP2;
scp -r 'src' pg50184@s7edu2.di.uminho.pt:TP2;
scp -r 'Makefile' pg50184@s7edu2.di.uminho.pt:TP2;
ssh pg50184@s7edu2.di.uminho.pt "cd TP2/; \
 make clean; \
 make; \
 srun --partition=cpar perf stat -r 5 -c 4 -e instructions,cycles,cache-references,cache-misses bin/k_means"
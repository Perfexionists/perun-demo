 perun collect -c "./sort_file inputs/medium-sorted.txt quicksort" kperf --repeat 1 --warmup 0
 perun collect -c "./sort_file inputs/medium-sorted.txt quicksort2" kperf --repeat 1 --warmup 0

perun showdiff --offline profiles/kperf-\[match_reg
ex\]-\[email-seed.txt\].perf profiles/kperf-\[match_regex\]-\[email-bad-2.txt\].perf report
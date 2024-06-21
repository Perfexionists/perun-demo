 perun collect -c "./wordcount djb inputs/seed.txt" kperf --repeat 1 --warmup 0
 perun collect -c "./wordcount djb inputs/bad-2.txt" kperf --repeat 1 --warmup 0


perun showdiff --offline profiles/kperf-\[match_reg
ex\]-\[email-seed.txt\].perf profiles/kperf-\[match_regex\]-\[email-bad-2.txt\].perf report
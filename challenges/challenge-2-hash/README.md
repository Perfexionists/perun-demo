 perun collect -c ./match_regex -w "regex/email-regex-1 inputs/email-seed.txt" kperf --with-sudo --repeat 1 --warmup 0

 perun collect -c ./match_regex -w "regex/email-regex-1 inputs/email-bad-1.txt" kperf --with-sudo --repeat 1 --warmup 0

perun showdiff --offline profiles/kperf-\[match_reg
ex\]-\[email-seed.txt\].perf profiles/kperf-\[match_regex\]-\[email-bad-2.txt\].perf report
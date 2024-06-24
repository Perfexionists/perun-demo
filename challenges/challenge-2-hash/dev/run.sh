#!/bin/bash
perun collect -c ./wordcount -w "djb inputs/seed.txt quicksort" -o profiles/kperf-djb-seed.perf kperf
perun collect -c ./wordcount -w "student inputs/seed.txt quicksort" -o profiles/kperf-student-seed.perf kperf
perun collect -c ./wordcount -w "java inputs/seed.txt quicksort" -o profiles/kperf-java-seed.perf kperf

perun collect -c ./wordcount -w "djb inputs/bad-1.txt quicksort" -o profiles/kperf-djb-bad-1.perf kperf
perun collect -c ./wordcount -w "student inputs/bad-1.txt quicksort" -o profiles/kperf-student-bad-1.perf kperf
perun collect -c ./wordcount -w "java inputs/bad-1.txt quicksort" -o profiles/kperf-java-bad-1.perf kperf

perun collect -c ./wordcount -w "djb inputs/bad-2.txt quicksort" -o profiles/kperf-djb-bad-2.perf kperf
perun collect -c ./wordcount -w "student inputs/bad-2.txt quicksort" -o profiles/kperf-student-bad-2.perf kperf
perun collect -c ./wordcount -w "java inputs/bad-2.txt quicksort" -o profiles/kperf-java-bad-2.perf kperf

perun showdiff --offline profiles/kperf-djb-seed.perf profiles/kperf-java-seed.perf report --minimize -o diffs/seed-java-vs-djb
perun showdiff --offline profiles/kperf-djb-seed.perf profiles/kperf-student-seed.perf report --minimize -o diffs/seed-djb-vs-student
perun showdiff --offline profiles/kperf-student-seed.perf profiles/kperf-java-seed.perf report --minimize -o diffs/seed-student-vs-java

perun showdiff --offline profiles/kperf-djb-bad-1.perf profiles/kperf-java-bad-1.perf report --minimize -o diffs/bad-1-java-vs-djb
perun showdiff --offline profiles/kperf-djb-bad-1.perf profiles/kperf-student-bad-1.perf report --minimize -o diffs/bad-1-djb-vs-student
perun showdiff --offline profiles/kperf-student-bad-1.perf profiles/kperf-java-bad-1.perf report --minimize -o diffs/bad-1-student-vs-java

perun showdiff --offline profiles/kperf-djb-bad-2.perf profiles/kperf-java-bad-2.perf report --minimize -o diffs/bad-2-java-vs-djb
perun showdiff --offline profiles/kperf-djb-bad-2.perf profiles/kperf-student-bad-2.perf report --minimize -o diffs/bad-2-djb-vs-student
perun showdiff --offline profiles/kperf-student-bad-2.perf profiles/kperf-java-bad-2.perf report --minimize -o diffs/bad-2-student-vs-java
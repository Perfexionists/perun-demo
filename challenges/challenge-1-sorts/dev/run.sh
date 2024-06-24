#!/bin/bash
perun collect -c ./sort_file -w "inputs/medium-sorted.txt quicksort" -o profiles/kperf-quicksort-medium-sorted.perf kperf
perun collect -c ./sort_file -w "inputs/medium-sorted.txt quicksort-alt" -o profiles/kperf-quicksort-alt-medium-sorted.perf kperf
perun collect -c ./sort_file -w "inputs/medium-sorted.txt heapsort" -o profiles/kperf-heapsort-medium-sorted.perf kperf
perun collect -c ./sort_file -w "inputs/medium-sorted.txt insertsort" -o profiles/kperf-insertsort-medium-sorted.perf kperf
perun collect -c ./sort_file -w "inputs/medium-sorted.txt" -o profiles/kperf-medium-sorted.perf kperf

perun collect -c ./sort_file -w "inputs/medium-random.txt quicksort" -o profiles/kperf-quicksort-medium-random.perf kperf
perun collect -c ./sort_file -w "inputs/medium-random.txt quicksort-alt" -o profiles/kperf-quicksort-alt-medium-random.perf kperf
perun collect -c ./sort_file -w "inputs/medium-random.txt heapsort" -o profiles/kperf-heapsort-medium-random.perf kperf
perun collect -c ./sort_file -w "inputs/medium-random.txt insertsort" -o profiles/kperf-insertsort-medium-random.perf kperf
perun collect -c ./sort_file -w "inputs/medium-random.txt" -o profiles/kperf-medium-random.perf kperf

perun showdiff --offline profiles/kperf-quicksort-medium-sorted.perf profiles/kperf-quicksort-alt-medium-sorted.perf report --minimize -o diffs/sorted-quicksort-vs-quicksort-alt
perun showdiff --offline profiles/kperf-quicksort-medium-sorted.perf profiles/kperf-insertsort-medium-sorted.perf report --minimize -o diffs/sorted-quicksort-vs-insertsort
perun showdiff --offline profiles/kperf-quicksort-medium-sorted.perf profiles/kperf-heapsort-medium-sorted.perf report --minimize -o diffs/sorted-quicksort-vs-heapsort
perun showdiff --offline profiles/kperf-quicksort-alt-medium-sorted.perf profiles/kperf-insertsort-medium-sorted.perf report --minimize -o diffs/sorted-quicksort-alt-vs-insertsort
perun showdiff --offline profiles/kperf-quicksort-alt-medium-sorted.perf profiles/kperf-heapsort-medium-sorted.perf report --minimize -o diffs/sorted-quicksort-alt-vs-heapsort
perun showdiff --offline profiles/kperf-insertsort-medium-sorted.perf profiles/kperf-heapsort-medium-sorted.perf report --minimize -o diffs/sorted-insertsort-vs-heapsort

perun showdiff --offline profiles/kperf-quicksort-medium-random.perf profiles/kperf-quicksort-alt-medium-random.perf report --minimize -o diffs/random-quicksort-vs-quicksort-alt
perun showdiff --offline profiles/kperf-quicksort-medium-random.perf profiles/kperf-insertsort-medium-random.perf report --minimize -o diffs/random-quicksort-vs-insertsort
perun showdiff --offline profiles/kperf-quicksort-medium-random.perf profiles/kperf-heapsort-medium-random.perf report --minimize -o diffs/random-quicksort-vs-heapsort
perun showdiff --offline profiles/kperf-quicksort-alt-medium-random.perf profiles/kperf-insertsort-medium-random.perf report --minimize -o diffs/random-quicksort-alt-vs-insertsort
perun showdiff --offline profiles/kperf-quicksort-alt-medium-random.perf profiles/kperf-heapsort-medium-random.perf report --minimize -o diffs/random-quicksort-alt-vs-heapsort
perun showdiff --offline profiles/kperf-insertsort-medium-random.perf profiles/kperf-heapsort-medium-random.perf report --minimize -o diffs/random-insertsort-vs-heapsort

perun showdiff --offline profiles/kperf-medium-random.perf profiles/kperf-medium-sorted.perf report --minimize -o diffs/random-vs-sorted
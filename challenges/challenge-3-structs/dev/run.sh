#!/bin/bash

perun collect -c "./search inputs/medium-random.txt 5 10" -o profiles/kperf-medium-random-5-10.perf kperf
perun collect -c "./search inputs/medium-random.txt 50 2" -o profiles/kperf-medium-random-50-2.perf kperf
perun collect -c "./search inputs/medium-random.txt 3 10" -o profiles/kperf-medium-random-3-10.perf kperf
perun collect -c "./search inputs/medium-random.txt 13 2" -o profiles/kperf-medium-random-13-2.perf kperf
perun collect -c "./search inputs/medium-random.txt 3 5" -o profiles/kperf-medium-random-3-5.perf kperf

perun showdiff --offline profiles/kperf-medium-random-3-10.perf profiles/kperf-medium-random-5-10.perf report --minimize -o diffs/medium-random-3-10-vs-5-10
perun showdiff --offline profiles/kperf-medium-random-13-2.perf profiles/kperf-medium-random-50-2.perf report --minimize -o diffs/medium-random-13-2-vs-50-2
perun showdiff --offline profiles/kperf-medium-random-3-5.perf profiles/kperf-medium-random-3-10.perf report --minimize -o diffs/medium-random-3-5-vs-3-10
perun showdiff --offline profiles/kperf-medium-random-3-5.perf profiles/kperf-medium-random-5-10.perf report --minimize -o diffs/medium-random-3-5-vs-5-10
perun showdiff --offline profiles/kperf-medium-random-5-10.perf profiles/kperf-medium-random-13-2.perf report --minimize -o diffs/medium-random-5-10-vs-13-2
#!/bin/bash

perun collect -c "./match_regex regex/classname-regex-1.txt inputs/classname-match.txt" -o profiles/classname-1-match.perf kperf
perun collect -c "./match_regex regex/classname-regex-2.txt inputs/classname-match.txt" -o profiles/classname-2-match.perf kperf
perun collect -c "./match_regex regex/email-regex-1.txt inputs/email-match.txt" -o profiles/email-1-match.perf kperf
perun collect -c "./match_regex regex/email-regex-2.txt inputs/email-match.txt" -o profiles/email-2-match.perf kperf

perun collect -c "./match_regex regex/classname-regex-1.txt inputs/classname-non-match-1.txt" -o profiles/classname-1-non-match-1.perf kperf
perun collect -c "./match_regex regex/classname-regex-2.txt inputs/classname-non-match-1.txt" -o profiles/classname-2-non-match-1.perf kperf
perun collect -c "./match_regex regex/email-regex-1.txt inputs/email-non-match-1.txt" -o profiles/email-1-non-match-1.perf kperf
perun collect -c "./match_regex regex/email-regex-2.txt inputs/email-non-match-1.txt" -o profiles/email-2-non-match-1.perf kperf

perun collect -c "./match_regex regex/classname-regex-1.txt inputs/classname-non-match-2.txt" -o profiles/classname-1-non-match-2.perf kperf
perun collect -c "./match_regex regex/classname-regex-2.txt inputs/classname-non-match-2.txt" -o profiles/classname-2-non-match-2.perf kperf
perun collect -c "./match_regex regex/email-regex-1.txt inputs/email-non-match-2.txt" -o profiles/email-1-non-match-2.perf kperf
perun collect -c "./match_regex regex/email-regex-2.txt inputs/email-non-match-2.txt" -o profiles/email-2-non-match-2.perf kperf

perun showdiff --offline profiles/classname-1-match.perf profiles/classname-2-match.perf  report --minimize -o diffs/classname-match
perun showdiff --offline profiles/email-1-match.perf profiles/email-2-match.perf  report --minimize -o diffs/email-match
perun showdiff --offline profiles/classname-1-non-match-1.perf profiles/classname-2-non-match-1.perf  report --minimize -o diffs/classname-non-match-1
perun showdiff --offline profiles/email-1-non-match-1.perf profiles/email-2-non-match-1.perf  report --minimize -o diffs/email-non-match-1
perun showdiff --offline profiles/classname-1-non-match-2.perf profiles/classname-2-non-match-2.perf  report --minimize -o diffs/classname-non-match-2
perun showdiff --offline profiles/email-1-non-match-2.perf profiles/email-2-non-match-2.perf  report --minimize -o diffs/email-non-match-2

perun showdiff --offline profiles/classname-1-match.perf profiles/classname-1-non-match-1.perf  report --minimize -o diffs/classname-1-match-vs-non-match-1
perun showdiff --offline profiles/classname-2-match.perf profiles/classname-2-non-match-1.perf  report --minimize -o diffs/classname-2-match-vs-non-match-1
perun showdiff --offline profiles/email-1-match.perf profiles/email-1-non-match-1.perf  report --minimize -o diffs/email-1-match-vs-non-match-1
perun showdiff --offline profiles/email-2-match.perf profiles/email-2-non-match-1.perf  report --minimize -o diffs/email-2-match-vs-non-match-1

perun showdiff --offline profiles/classname-1-match.perf profiles/classname-1-non-match-2.perf  report --minimize -o diffs/classname-1-match-vs-non-match-2
perun showdiff --offline profiles/classname-2-match.perf profiles/classname-2-non-match-2.perf  report --minimize -o diffs/classname-2-match-vs-non-match-2
perun showdiff --offline profiles/email-1-match.perf profiles/email-1-non-match-2.perf  report --minimize -o diffs/email-1-match-vs-non-match-2
perun showdiff --offline profiles/email-2-match.perf profiles/email-2-non-match-2.perf  report --minimize -o diffs/email-2-match-vs-non-match-2
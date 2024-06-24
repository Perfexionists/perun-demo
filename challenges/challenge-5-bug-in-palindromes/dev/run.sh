#!/bin/bash

perun showdiff --offline profiles/bad-tacocat.perf profiles/good-tacocat.perf report --minimize -o diffs/tacocat
perun showdiff --offline profiles/bad-burritodog.perf profiles/good-burritodog.perf report --minimize -o diffs/burritodog
perun showdiff --offline profiles/bad-burritoduck.perf profiles/good-burritoduck.perf report --minimize -o diffs/burritoduck
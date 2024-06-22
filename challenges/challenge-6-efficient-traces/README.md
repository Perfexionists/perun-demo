## Challenge 6: The Messy Traces

  - **Difficulty**: medium
  - **Goal**: Optimize the code 
  - **Description**: We finally leave the artificial problems and go for something real. This is a problem, that we have been facing when analysing kernel for some time. The kernel is quite evolving project, with each release, hundreds of functions are changed, hundreds are removed, and hundreds are added. When performance analysts check the code, they not only want to find the functions that might have changed (in terms of performance), but one usually needs some other trace to compare the performance against. This is needed both for automatic and manual analysis. The project contains an AI-generated code for finding good match in previous results (so called baseline) for traces from newly generated data (so called targed). The code is quite inefficient. Try to make it more efficient. There are no limits to your imagination. However, since the code is quite complex, we recommend you to look at the computing cost of two traces: there are lots of recursive calls, right?
  - **Usage**: `./compare_traces <baseline_traces> <target_traces>`
  <details>
    <summary>Hint</summary>
    Maybe you have heard of memoization? 
  </details>

## More details

The program takes as an argument two source files which contains the list of
traces from two versions of kernel.  Each list is converted into vector of
traces, each traces is then represented as vector of strings (each string
corresponds to call of the function).

Then for each trace from the target, we traverse all traces in baseline and try to compute the cost (i.e. the difference) between two traces. The cost is computed as follows:

   1. First we try to match the topmost calls: if they are the same, then we compute the cost of the rest of two functions. The cost of matching is zero.
   2. Otherwise we try each of the following:
      1. We remove from left trace and compute the cost with the right trace.
      2. We remove from the right trace and compute the cost with the left trace.
      3. We compute the cost of the switching the topmost calls and compute the cost of the rest.
   3. We take the minimal change as the cost.

We implemented two different ways of computing the cost of switching two calls in traces:

    1. Classical "Levenshtein distance", that computes minimal number of changes needed to make to string to create the other string.
    2. Similarity heuristic, that computes the ratio between common and unique words between two calls.

Note that we generated the original program from C++ (our implementation is in Python and already has been considerably optimized to process even 20,000+ traces; in this example, however, the job is already starting). Use your own imagination.

We also prepared in `inputs` several inputs that you can try:

  1. `minimal-*` inputs contains 10--20 traces.
  2. `small-*` contains 300--400 traces.
  3. `big-*` contains 6,000--10,0000 traces.

We suggest to start working with minimal inputs, follow to simple and go to big baseline.

## How to run

We assume, you have initialized Perun somewhere along the path with `perun init`.

To measure a performance profile run the following:

    perun collect -c "./compare_traces inputs/minimal-baseline.txt inputs/minimal-target.txt" kperf --repeat 1 --warmup 0

The first command runs our perf-based collector on `./sort_file` binary with workload from `inputs` directory, it runs the measurement only once, and performs no warmups. The resulting profiles are stored in `.perun/jobs` directory. You can also run `perun status` to see which profiles are registered and can be used as tags.

Make changes to your code and then run the collector again and compare your profiles.

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison

This will take two latest profiles and generates interactive report in `diffs` directory. You can also set absolute paths or use the precollected profiles in `profiles` directory.

    perun showdiff --offline profiles/kperf-similarity.perf profiles/kperf-levenshtein.perf report --minimize -o diffs/comparison-of-cost-functions
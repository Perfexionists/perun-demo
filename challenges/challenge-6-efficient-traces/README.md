## Challenge 6: The Messy Traces

  - **Difficulty**: medium
  - **Goal**: Optimize the code 
  - **Description**: We finally leave the artificial problems and go for
  something real. This is a problem, that we have been facing when analysing
  kernel for some time. The kernel is quite evolving project, with each release,
  hundreds of functions are changed, hundreds are removed, and hundreds are
  added. When performance analysts check the code, they not only want to find
  the functions that might have changed (in terms of performance), but one
  usually needs some other trace to compare the performance against. This is
  needed both for automatic and manual analysis. The challenge contains an
  AI-generated code for finding good match in previous results (so called
  baseline) for traces from newly generated data (so called target). But the
  code is quite inefficient. Try to make it more efficient. There are no limits
  to your imagination. However, since the code is quite complex, we recommend
  you to look at the computing cost of two traces (the function
  `computeTransformationCost`): there are lots of recursive calls, right?
  - **Usage**: `./compare_traces <baseline_traces> <target_traces>`
  <details>
    <summary>Hint</summary>
    Maybe you have heard of memoization? 
  </details>

## More details

The program takes as an argument two source files; each contains the list of
traces from baseline and target versions of kernel (respectively). Each list is
converted into vector of traces, each traces is then represented as vector of
strings (each string corresponds to call of the function, delimited by `,`).

Then for each trace from the target, we traverse all traces in the baseline and
try to compute the similarity of two traces (or one could say a cost of
transforming baseline trace into the target traces). This cost (or similarity)
is computed as follows:

   1. We start the algorithm by comparing traces `lhs` and `rhs` from indexes `i = j = 0`. We then recursively call the cost function for quadruple (`lhs`, `rhs`, `i`, `j`):
    1. First we try to match the `i`th and `j`th call: if they are the same the cost is zero plus the cost of the rest of two functions (`i+1` and `j+1`).
    2. Otherwise we try each of the following:
        1. We remove from left trace (`i+1`) and compute the cost with the right trace (`j`) and add 1 (for removing).
        2. We remove from the right trace (`j+1`) and compute the cost with the left trace (`i`) and add 1 (for removing).
        3. We compute the cost of the switching the topmost calls (`i` and `j`), which is based on similarity of two function names (normalized number of common words between two calls) and add the cost of the rest (`i+1` and `j+1`).
    3. We take the minimal change of the three as the resulting cost.

We implemented two different ways of computing the cost of switching two calls in traces:

    1. Classical "Levenshtein distance", that computes minimal number of changes needed to be applied to string to create the other string.
    2. Similarity heuristic, that computes the ratio between common and unique words between two calls, i.e. (number of common words in lhs_call and rhs_call) / (number of all words).

Note that we mainly generated this C++ program using AI (our implementation is in Python and already has been considerably optimized to process even 20,000+ traces; in this example, however, the implementation is still seriously lacking). Use your own imagination.

We also prepared directory `inputs` with inputs that you can try:

  1. `minimal-*` inputs contains 10--20 traces (start here)
  2. `small-*` contains 300--400 traces (we provide measuring of these in `profiles/small-reference.perf` profile, which took about 2min, after some optimization; current implementation cannot handle this is in reasonable time).
  3. `big-*` contains 6,000--10,0000 traces (though, you probably wont be able to process it in such short time)

We suggest to start working with minimal inputs, follow to small, and if you really are confident go to the big baseline.

## How to run

The program is compilable using make:

    make

We recommend to start with empty git repo in challenges (Perun currently do some stashing behind the scene, and it might hinder your code changes):

    cd challenges
    git init; git commit --allow-empty -m "root"

We assume, you have initialized Perun somewhere along the path with `perun init` as well as some git (we recommend to create an empty git for these experiments).

To measure a performance profile run the following:

    perun collect -c "./compare_traces inputs/minimal-baseline.txt inputs/minimal-target.txt" kperf

The first command runs our perf-based collector on `./sort_file` binary with
workload from `inputs` directory, it runs the measurement only once, and
performs no warmups. The resulting profiles are stored in `.perun/jobs`
directory. You can also run `perun status` to see which profiles are registered
and can be used as tags. You can also run `perun status` to see which profiles are registered
and can be used as tags (in form of `i@p`). Alternatively, you can add `-o`
parameter (`perun collect -o out.perf ... kperf`) to save the profile outside of
Perun scope (you will have to specify the profiles manually then).

Make changes to your code and then run the collector again and compare your profiles.

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison

This will take two latest profiles and generates interactive report in `diffs` directory. You can also set absolute paths or use the precollected profiles in `profiles` directory.

    perun showdiff --offline profiles/minimal-similarity.perf profiles/minimal-levenshtein.perf report --minimize -o diffs/comparison-of-cost-functions
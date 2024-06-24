## Challenge 3: The Skipping Lists

  - **Difficulty**: easy
  - **Goal**: Sort the parameters of skiplists in terms of their efficiency.
  - **Description**: You "inherited" a legacy code from your previous colleague.
  He has been using single link lists to implement a queue of requests from your
  customers. The requests are processed in sorted order, however, sometimes
  requests with certain ids are cancelled, so the whole list has to be searched.
  You decided to optimize this process: you heard about this amazing skip-list
  structure that allows faster lookup. It basically allows you to skip bigger
  portions of the list. You implemented them, but you are not satisfied with the
  performance. Now, you have to fine-tune two of its parameters: the height and
  the probability. Try to find the optimal solution.
  - **Usage**: `./search <input> <height> <probability>`
  <details>
    <summary>Hint</summary>
    This does not need hint, only diligent work.
  </details>

## More details

The program takes as an argument source file with integers delimited by spaces.
It converts them to list structure and then it simulates some cancelation of the
request: it `n`times searches for random values.

When the program is run with a single argument, it constructs classical Single
Link Lists (you can compare their performance to those of skiplists; it is,
however, unsorted).

When the program is run with three arguments, it constructs skip lists, with the
following properties:

    1. The second argument is the maximal height of the skip list node. In
    nutshell, this number states how many pointers does the skip list contain;
    the more pointers the more levels can the node skip during the search.
    This is, however, tradeoff with memory (we will omit memory comparison, though)
    2. The third argument is the probability of creating a skip list of a higher
    level (skip lists are probabilistic structure). Basically, whenever you are
    constructing new node, you probabilistically decide, which level it is. The
    probability should be chosen to even out the distribution of the levels
    allowing fast lookup.
    
We also prepared directory `inputs` with inputs that you can try:

  1. Randomly sorted input numbers.
  2. Sorted numbers input numbers.
  3. Reversely sorted input numbers.

## Challenge parameters

We have prepared several parameters, that you should try. The first corersponds
to height and the second corresponds to probability.

    1. Height Probability: `5 10`
    2. Height Probability: `50 2`
    3. Height Probability: `3 10`
    4. Height Probability: `13 2`
    5. Height Probability: `3 5`

Try to sort these parameters in terms of effectiveness regarding the speed.

## How to run

We assume, you have initialized Perun somewhere along the path with `perun init` as well as some git (we recommend to create an empty git for these experiments).

To measure a performance profile run the following:

    perun collect -c "./search /<INPUT>" kperf
    perun collect -c "./search inputs/medium-random.txt 2 10" kperf
    perun collect -c "./search inputs/medium-sorted.txt 50 2" kperf

The first command runs our perf-based collector on `./search` binary with
workload from `inputs` directory, it runs the measurement only once, and
performs no warmups. The resulting profiles are stored in `.perun/jobs`
directory. You can also run `perun status` to see which profiles are registered
and can be used as tags (in form of `i@p`). Alternatively, you can add `-o`
parameter (`perun collect -o out.perf ... kperf`) to save the profile outside of
Perun scope (you will have to specify the profiles manually then).

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison-of-skiplists

This will take two latest profiles and generates interactive report in `diffs` directory. You can also set absolute paths or use the precollected profiles in `profiles` directory.

    perun showdiff --offline profiles/kperf-random-2-10.perf profiles/kperf-random-3-10.perf report --minimize -o diffs/comparison-of-skiplists-2-10-vs-3-10
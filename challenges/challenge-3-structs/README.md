## Challenge 3: The Skipping Lists

  - **Difficulty**: easy
  - **Goal**: Optimize the parameters of skiplists
  - **Description**: You "inherited" a legacy code from your previous colleauge. He has been using single link lists to implement a queue of requests. The requests are processed in sorted order, however, sometimes requests with certain id are cancelled, so the whole list has to be searched. You decided to optimize this process: you heard about the amazing skip-list structure for faster lookup. You implemented them, but you are not satisfied with the performance. You have to fine-tune two of its parameters: the height and the probability.
  - **Usage**: `./search <input> <height> <probability>`
  <details>
    <summary>Hint</summary>
    This does not need hint, only diligent work.
  </details>

## More details

The program takes as an argument source file with integers delimited by spaces. It converts them to list structure and then `n`times searches for random values.

When the program is run with a single argument, it constructs classical Single Link Lists (you can compare their performance to those of skiplists).

When the program is run with three arguments, it constructs skip lists, with the following properties:

    1. The second argument is the maximal height of the skip list node. This number states how many pointers does the skip list contain, the more pointers the more levels can the node skip during the search.
    2. The third argument is the probability of creating a skip list of higher level (skip lists are probabilistic structure).

We also prepared in `inputs` several inputs that you can try:

  1. Randomly sorted input numbers.
  2. Sorted numbers input numbers.
  3. Reversely sorted input numbers.

## Challenge parameters

We provide the following parameters, that could be used to fine tune the skiplists:

    1. `5 10`
    2. `50 2`
    3. `3 10`
    4. `13 2`
    5. `3 5`

Try to sort these parameters in terms of effectiveness regarding the speed.

## How to run

We assume, you have initialized Perun somewhere along the path with `perun init`.

To measure a performance profile run the following:

    perun collect -c "./search /<INPUT>" kperf --repeat 1 --warmup 0
    perun collect -c "./search inputs/<INPUT> 2 10" kperf --repeat 1 --warmup 0

The first command runs our perf-based collector on `./search` binary with
workload from `inputs` directory, it runs the measurement only once, and
performs no warmups. The resulting profiles are stored in `.perun/jobs`
directory. You can also run `perun status` to see which profiles are registered and can be used as tags.

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison-of-sll-vs-skiplist

This will take two latest profiles and generates interactive report in `diffs` directory. You can also set absolute paths or use the precollected profiles in `profiles` directory.

    perun showdiff --offline profiles/kperf-[medium-random.txt]-[2_10].perf profiles/kperf-[medium-random.txt]-[3_10].perf report --minimize -o diffs/comparison-of-sll-vs-skiplist
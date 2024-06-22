## Challenge 2: The Hashing Words

  - **Difficulty**: easy
  - **Goal**: Find the best hashing function
  - **Description**: Your boss gave you a JIRA ticket for implementation of the
  count of the words in the file. Your mentor recommended you to use hash
  tables. However, the ChatGPT gave you several different hash functions, and
  you have no idea which one is the best. Try to find the best hash function out
  of the three, that will count the examples file from your customer the
  fastest.
  - **Usage**: `./wordcount <djb|java|original> <input>`
  <details>
    <summary>Hint</summary>
    Hashing functions are by-construction constant and extremely fast, you will not see any degradations there. However, they do affect the distribution of the elements in the table, right?
  </details>

## More details

The program takes as an argument source file with words delimited by spaces. It
reads them one by one, and counts them using the implementation of hash table. The hash table can be modified by chosing a differnt underlying hash function: hash function is used in hash table to compute the bucket, where item will be stored.

Note that this is an actual replication of issue found in certain project.

You can use the following hash functions:

   1. Student: an implementation that was used in student project.
   2. DJB: djb hash function.
   3. Java: function used in java implementation.

We also prepared in `inputs` several files that you can try:

   1. Seed is an original corpus that should perform OK on all hash functions.
   2. `bad-{1,2}.txt` were generated using fuzz-testing technique and lead to considerable performance degradation in the program with hash tables. In particular, the fuzz-testing mainly used rule that duplicated words in the inputs.

You can think how the wordcount program should behave on these inputs.

## How to run

We assume, you have initialized Perun somewhere along the path with `perun init`.

To measure a performance profile run the following:

    perun collect -c "./wordcount java inputs/seed.txt" kperf --repeat 1 --warmup 0
    perun collect -c "./wordcount java inputs/bad-1.txt" kperf --repeat 1 --warmup 0

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison-of-all-vs-quicksort

The first command runs our perf-based collector on `./wordcount` binary with
workload from `inputs` directory, it runs the measurement only once, and
performs no warmups. The resulting profiles are stored in `.perun/jobs`
directory. You can also run `perun status`

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison-of-java-on-seed-vs-bad

This will take two latest profiles and generates interactive report in `diffs` directory. You can also set absolute paths or use the precollected profiles in `profiles` directory.

    perun showdiff --offline profiles/kperf-[seed.txt]-[].perf profiles/kperf-[bad-2.txt]-[].perf report --minimize -o diffs/comparison-of-java-on-seed-vs-bad
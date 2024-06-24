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

The program takes as an argument a source file with words delimited by spaces.
It reads them one by one, and counts their occurence using the implementation of
a hash table. The hash table can be modified by chosing a different underlying
hash function: a hash function is used in the hash table to compute the bucket,
where item will be stored.

The program is compilable using make:

    make

Note that this challenge is based on an actual issue found in certain (censored)
project.

You can use the following hash functions:

   1. Student: an implementation that was used in student project.
   2. DJB: djb hash function is considered to be one of the best hash functions.
   3. Java: function used in Java 1.1. string library implementation.

We also prepared directory `inputs` with several files that you can try:

   1. `seed.txt` is an original corpus (fuzzing terminology for starting point of fuzzing) that should perform without problem on all of the hash functions.
   2. `bad-{1,2}.txt` were generated using fuzz-testing technique and could lead to considerable performance degradation in the program with hash tables (there are more collisions). In particular, the fuzz-testing mainly used rule that duplicated words in the inputs.

You can think how the wordcount program should behave on these inputs.

## How to run

We assume, you have initialized Perun somewhere along the path with `perun init` as well as some git (we recommend to create an empty git for these experiments).

To measure a performance profile run the following:

    perun collect -c "./wordcount <java|djb|student> <INPUT>" kperf
    perun collect -c "./wordcount java inputs/seed.txt" kperf
    perun collect -c "./wordcount java inputs/bad-1.txt" kperf

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison-of-java-on-seed-vs-bad-1

The first command runs our perf-based collector on `./wordcount` binary with
workload from `inputs` directory, it runs the measurement only once, and
performs no warmups. The resulting profiles are stored in `.perun/jobs`
directory. You can also run `perun status` to see which profiles are registered
and can be used as tags (in form of `i@p`). Alternatively, you can add `-o`
parameter (`perun collect -o out.perf ... kperf`) to save the profile outside of
Perun scope (you will have to specify the profiles manually then).

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison-of-java-on-seed-vs-bad

This will take two latest profiles (in the Perun scope) and generates
interactive report in `diffs` directory. You can also set absolute paths or use
the precollected profiles in `profiles` directory.

    perun showdiff --offline profiles/kperf-djb-seed.perf profiles/kperf-java-seed.perf report --minimize -o diffs/comparison-of-java-vs-djb-on-seed
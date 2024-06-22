## Challenge 5: The Bad Recursion

  - **Difficulty**: medium
  - **Goal**: Find and fix the bug
  - **Description**: Your boss has assigned you a project to work on. One customer wants a suggester of a palindromes based on his username or string, or whatever. You do not question your boss and so you delegate this to your fresh intern. He implemented the code, tested it on tacocat, and it worked. But the customer called `amazing_tacocat` has experienced some issues with the code. You should fix the issue and make the palindrome generator great again.
  - **Usage**: `./generate <string>`
  <details>
    <summary>Hint</summary>
    How do parameteres in C++ work again? Is it by reference or by value?
  </details>

## More details

The program takes as an argument string. It then breaks it into characters and
starts to generate all the permutations of the string using recursive
implementation. When each permutation is constructed it is tested whether it is
palindrom. If the permutation is palindrome, it is added to the global cache.
Finally all palindromes are printed.

You can try the program e.g. on:

    1. tacocat (it is palindrome, but are there more?)
    2. burittodog
    3. quesadillamouse

We also prepared a profile, where the bug was fixed. You can compare your implementation against our reference profile `profiles/kperf-good.txt`.

## How to run

We assume, you have initialized Perun somewhere along the path with `perun init`.

To measure a performance profile run the following:

    perun collect -c "./generate cat" kperf --repeat 1 --warmup 0
    perun collect -c "./generate tacocat" kperf --repeat 1 --warmup 0

The first command runs our perf-based collector on `./sort_file` binary with workload from `inputs` directory, it runs the measurement only once, and performs no warmups. The resulting profiles are stored in `.perun/jobs` directory. You can also run `perun status` to see which profiles are registered and can be used as tags.

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison-of-cat-vs-tacocat

This will take two latest profiles and generates interactive report in `diffs` directory. You can also set absolute paths or use the precollected profiles in `profiles` directory.

    perun showdiff --offline profiles/kperf-good.perf profiles/kperf-bad.perf report --minimize -o diffs/comparison-of-good-vs-bad
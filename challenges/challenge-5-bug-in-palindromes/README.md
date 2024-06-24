## Challenge 5: The Bad Recursion

  - **Difficulty**: medium
  - **Goal**: Find and fix the bug
  - **Description**: Your boss has assigned you a project to work on. One
  customer wants a suggester of a palindromes based on his username or string,
  or whatever. You do not question your boss and so you delegate this to your
  fresh intern. He implemented the code, tested it on `tacocat`, and it worked.
  But the customer called `amazing_tacocat` has experienced some performance
  issues with the code. You should fix the issue and make the palindrome
  generator great again.
  - **Usage**: `./generate <string>`
  <details>
    <summary>Hint</summary>
    How do parameters in C++ work again? Is it by reference or by value?
  </details>

## More details

The program takes as an argument a single string. It then breaks it into
characters and starts to generate all the permutations of the string using
recursive implementation. When each permutation is constructed it is tested
whether it is palindrome. If the permutation is palindrome, it is added to the
global cache.  Finally all palindromes are printed.

You can try the program e.g. on:

    1. tacocat (it is palindrome, but are there more?)
    2. burritodog (maybe you want to try other combination?)
    3. burritoduck(or mabye other animal?)

We also prepared profiles, where the bug was fixed. You can compare your implementation against our reference profiles `profiles/good-*.txt`.

Note, that this kind of bug is actually quite common, it happened to us (or
rather to our comrades), and it happens to lot of people all over the world.

## How to run

The program is compilable using make:

    make

We recommend to start with empty git repo in challenges (Perun currently do some stashing behind the scene, and it might hinder your code changes):

    cd challenges
    git init; git commit --allow-empty -m "root"

To measure a performance profile run the following:

    perun collect -c "./generate <STRING>" kperf
    perun collect -c "./generate cat" kperf
    perun collect -c "./generate tacocat" kperf

The first command runs our perf-based collector on `./generate` binary with
workload from `inputs` directory, it runs the measurement only once, and
performs no warmups. The resulting profiles are stored in `.perun/jobs`
directory. You can also run `perun status` to see which profiles are registered
and can be used as tags (in form of `i@p`). Alternatively, you can add `-o`
parameter (`perun collect -o out.perf ... kperf`) to save the profile outside of
Perun scope (you will have to specify the profiles manually then).

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison-of-cat-vs-tacocat

This will take two latest profiles and generates interactive report in `diffs` directory. You can also set absolute paths or use the precollected profiles in `profiles` directory.

    perun showdiff --offline profiles/bad-tacocat.perf profiles/good-tacocat.perf report --minimize -o diffs/comparison-of-good-vs-bad
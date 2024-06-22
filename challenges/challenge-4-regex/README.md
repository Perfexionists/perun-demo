## Challenge 4: The Evil Expressions

  - **Difficulty**: easy
  - **Goal**: Find the problematic regular expressions.
  - **Description**: Oh boy, you got another JIRA ticket to fix. It seems that some of the regular expressions on the client side lead to huge latencies. And certain "friendly competitors" noticed as well and are now ReDoSing your customers. Try to sort out which regular expressions are fine and which are screwing your customers.
  - **Usage**: `./match_regex <regex_file> <input_file>`
  <details>
    <summary>Hint</summary>
    The gist of the ReDoS attack is that it forces badly implemented regular expression engines to backtrack quadratic-times in case of a mismatch. 
  </details>

## More details

The program takes as an argument two source files. The first contains a regular expression (using classic notation), the other contains a lines where each is matched by the given regular expression.

There are four regular expressions:

    1. `classname-regex-{1,2}.txt` contains regular expression that matches the class name in Java notation, that correspond to camel case.
       - *matches*: Class.Class.Class, Class
       - *does not match*: myclass, myclass.MyClass 
    2. `email-regex-{1,2}.txt` contains regular expression that matches the email address.
       - *matches*: myemail@gmail.com
       - *does not match*: myemail#gmail.com

We also prepared in `inputs` several inputs that you can try:

    1. `classname-*` contains both matching and non-matching strings for classname regular expression.
    2. `email-*` contains both matching and non-matching strings for email regular expression.

## How to run

We assume, you have initialized Perun somewhere along the path with `perun init`.

To measure a performance profile run the following:

    perun collect -c "./match_regex regex/classname-regex-1.txt inputs/classname-seed.txt" kperf --repeat 1 --warmup 0
    perun collect -c "./match_regex regex/classname-regex-1.txt inputs/classname-bad-1.txt" kperf --repeat 1 --warmup 0

The first command runs our perf-based collector on `./sort_file` binary with workload from `inputs` directory, it runs the measurement only once, and performs no warmups. The resulting profiles are stored in `.perun/jobs` directory. You can also run `perun status` to see which profiles are registered and can be used as tags.

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison-of-match-vs-non-match

This will take two latest profiles and generates interactive report in `diffs` directory. You can also set absolute paths or use the precollected profiles in `profiles` directory.

    perun showdiff --offline profiles/kperf-[match_regex]-[email-seed.txt].perf profiles/kperf-[email-bad-2.txt]-[].perf report --minimize -o diffs/comparison-of-all-vs-quicksort
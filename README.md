# Demonstration of using Perun on various performance aspects

This repository contains a various challenges and test projects meant for demonstration of the
capabilities of Perun tool suite (or other performance suites).

You might need to install the following dependencies:

  - cmake
  - perf
  - g++
  - python-devel
  - glibc-static


We recommend using `venv` and `Python 3.11` to avoid any issues (especially with dependencies):

    pip3 install virtualenv
    python3 -m venv <venv-name>
    source <venv-name>/bin/activate

To start with this demonstration, clone this repository, and install Perun.

    pip3 install perun-toolsuite

We recommend to start with empty git repo in challenges (Perun currently do some stashing behind the scene, and it might hinder your code changes):

    cd challenges
    git init; git commit --allow-empty -m "root"

Perun is similar to git: it needs a Perun instance initialized for your project. Either you can init Perun for each challenge individually:

    cd challenges/challenge-1-sorts/
    perun init
    ...

Generated profiles will be stored in `./challenges/challenge-1-sorts/.perun/jobs`

Alternatively, you can init Perun for all challenges.

    cd challenges/
    perun init
    ...

The profiles will be stored in `./challenges/.perun/jobs`.

Challenge 1-6 should be easily installable using single `make`; Challenges 7+
are harder, and might require more initializations or using a virtual machine.

Both the repository as well as Perun might still contain bugs and issues. We
apologize, for any inconvenience. You might have trouble installing Perun, as it
has lots of dependencies and lots of modules that might break some things. We
are aware of some of the issues (issues with new release of `numpy`, issues with
`jinja2` templates and editable install); also we have yet to solve the wheel
installation for pip releases, hence the install might fail for some
dependencies.

## Troubleshooting

  1. You cannot see the function in the generated graphs? Maybe it is simply so small, that it is omitted? Check the tabular results or the profiles themselves.
  2. You got `[ERROR] unexpected error: AttributeError: 'GitRepository' object has no attribute 'git_repo'`: you have to have some git repository; run `git init`
  3. You got `[ERROR] unexpected error: perun.utils.exceptions.VersionControlSystemException: parameter 'HEAD' could not be found: Ref 'HEAD' did not resolve to an object`: you have to have some commit; run `git commit --allow-empty -m "root"`.
  4. You see some `[unknown]` in the results? This is due to the fact, that some parts of dependencies/kernel were not compiled with frame pointer (`-fno-omit-frame-pointer`); this should not happen to the crutial parts of the challenges, though, and there is not much we can do about it.

## Generic guide

To collect the data use `perun collect` as follows:

    perun collect -c "<COMMAND>" kperf

This will measure the data using perf-based collector, runs single repeat (it
should be enough) and no warm-ups before them. For more complex commands you
have to specify them in string. The resulting profile is stored in `.perun/jobs`
directory.

Run several such commands. Then you can compare these using our diff views:

    perun showdiff --offline <PROFILE1> <PROFILE2> report --minimize -o <OUTPUTNAME>

The `--offline` parameter generates self-contained HTML files (otherwise, the
visualizations require internet connection because of dependencies). The
`--minimize` parameter is recommended, as it folds generic templates (the
resulting names are huge) as well as some minor minimizations of the results for
better brevity. You can omit the `-o` parameter; Perun automatically generates
suitable name (but it is looooooong).

We also recommend to run `perun status`; this will show all registered profiles
in your perun instance. You can then use tags, such as `0@p` to refer to last
collected profile.

## Challenge 1: The Sorting Hat

  - **Difficulty**: easy
  - **Goal**: Sort the complexities
  - **Description**: You used AI and several interns to generate some sorting
  algorithms, that will sort the numbers that are logged by your customers. Now
  you need to pick *one* of those algorithms to integrate it in practice. While,
  you sure could analyze their code, your boss needs to see some hard data, why
  it is performing good on your customer's data. Your program takes an input
  file with list of numbers (delimited by space) and sorts them using the
  selected algorithm. You can also run each of them separately by specifying
  their name. Try to find the best performing algorithm.
  - **Usage**: `./sort_file <input> | <input> <alg1> ... <algn>`
  <details>
    <summary>Hint</summary>
    Though, some algorithms are bundled together as having the same complexity,
    some of them are impostors: their quadratic behaviour might be forced, when it has
    to sort already or reversely-sorted inputs.
  </details>

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

## Challenge 4: The Evil Expressions

  - **Difficulty**: easy
  - **Goal**: Find the problematic regular expressions.
  - **Description**: Oh boy, you got another JIRA ticket to fix. It seems that some of the regular expressions on the client side lead to huge latencies. And certain "friendly competitors" noticed as well and are now ReDoSing your customers. Try to sort out which regular expressions are fine and which are screwing your customers.
  - **Usage**: `./match_regex <regex_file> <input_file>`
  <details>
    <summary>Hint</summary>
    The gist of the ReDoS attack is that it forces badly implemented regular expression engines to backtrack quadratic-times in case of a mismatch. 
  </details>


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

## Challenge 7: The CPython Regression

  - **Difficulty**: hard
  - **Goal**: Fix the bug
  - **Description**: This is a reproduction of the known (and now fixed bug) in CPython implementation. Our methods of automatic regression analysis could actually detect this. But you can also use a manual inspection and our interpretation to inspect it as well. Try to find out what is the problem of this bug. We can give you a hint (since CPython is really huge) that the problem is in `ctypes`.
  <details>
    <summary>Hint</summary>
    It takes a single line to fix unnecessarily repeated initialization.
  </details>

## Challenge 8: Linux Kernel

  - **Difficulty**: hard
  - **Goal**: Just have fun, try to find what is the root of the performance problems.
  - **Description**: This is an open challenge: we know there are some performance issues in kernel for which we do not know the root cause yet. In this challenge, we provide multiple sub-problems that you can dive into. Some of the problems come with pre-collected profiles (as they require setting up and measuring multiple custom kernels), while others will let you measure the kernel by yourselves.
  - **Problems**:
    1. Kernel 6.1 introduced a new Maple Tree data structure for memory management. Although developed with performance in mind, it seems to cause performance regressions on some specific kernels.
    2. Security-Enhanced Linux (SELinux) is a Linux kernel security module. Try to turn it on and off (Don't forget to turn it on afterwards!) and see whether you can spot some notable performance issues.
    3. Spectre and Meltdown security vulnerabilities mandated the implementation of software mitigations within the kernel. Try to turn them on and off and observe the performance results.

  <details>
    <summary>Hint</summary>
    No hint, enjoy your dive into the kernel madness! We have no idea what is wrong.
  </details>

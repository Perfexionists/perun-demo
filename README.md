# Demonstration of using Perun on various performance aspects

This repository contains a various challenges and test projects meant for demonstration of the
capabilities of perun tool suite.

You might need to install the following dependencies:

  - cmake
  - perf

To start with this demonstration, clone this repository, and install Perun.

    pip3 install perun-toolsuite

Perun is similar to git: it needs a Perun instance initialized for your project. Either you can init Perun for each challenge individually, as follows:

    cd challenges/challenge-1-sorts/
    perun init
    ...

The profiles will be stored in `./challenges/challenge-1-sorts/.perun/jobs`

Alternatively, you can init Perun for all challenges.

    cd challenges/
    perun init
    ...

The profiles will be stored in `./challenges/.perun/jobs`.

We recommned using `venv` and `Python 3.11` to avoid any issues (especially with dependencies).

Challenge 1-6 should be easily installable using `make`; Challenges 7+ are harder, and might require more initializations or using a virtual machine.

Both the repository as well as Perun might still contain bugs and issues. We apologize, for any inconvenience. You might have trouble installing Perun, as it has lots of dependencies and lots of modules that might break some things. We are aware of some of the issues (issues with new release of `numpy`, issues with `jinja2` templates and editable install); also we have yet to solve the wheel installation for pip releases, hence the install might fail for some dependencies.

## Generic guide

To collect the data use `perun collect` as follows:

    perun collect -c "<COMMAND>" kperf --repeat 1

This will measure the data using perf-based collector, runs single repeat (it should be enough) and few warm-ups before them. The resulting profile is stored in `.perun/jobs` directory.

Run several such commands. Then you can compare these using our diff views:

    perun showdiff --offline <PROFILE1> <PROFILE2> report --minimize -o <OUTPUTNAME>

The `--offline` parameter generates self-contained HTML files (otherwise, the visualizations require internet connection because of dependencies). The `--minimize` parameter is recommended, as it folds generic templates (the resulting names are huge) as well as some minor minimizations of the results for better brevity. You can omit the `-o` parameter; Perun automatically generates suitable name (but looooooong).

We also recommend to run `perun status` or `perun status --short`; this will show all registered profiles in your perun instance. You can then use tags, such as `0@p` to refer to last collected profile.

## Challenge 1: The Sorting Hat

  - **Difficulty**: easy
  - **Goal**: Sort the complexities
  - **Description**: You used AI and several interns to generate several sorting algorithm, that will sort the numbers that are obtained from your customer. Now you need to pick *two* of those algorithms to integrate them in practice. While, you sure could analyze their code, your boss needs to see some hard data. Your program takes input file with list of numbers and sorts them using each of the algorithm. You can also run each of them separately by specifying their name. 
  - **Usage**: `./sort_file <input> | <input> <alg1> ... <algn>`
  <details>
    <summary>Hint</summary>
    Though, some algorithms are bundled together as having the same complexity, one of them is an impostor: its quadratic behaviour is forced, when it has to sort already or reversely-sorted inputs.
  </details>

## Challenge 2: The Hashing Words

  - **Difficulty**: easy
  - **Goal**: Find the best hashing function
  - **Description**: Your boss gave you a JIRA ticket for implementation of the count of the words in the file. Your mentor recommended you to use hash tables. However, the ChatGPT gave you several different hash functions, and you have no idea which one is the best. Try to find the best hash function out of the three, that will count the examples file from your customer the fastest.
  - **Usage**: `./wordcount <djb|java|original> <input>`
  <details>
    <summary>Hint</summary>
    Hashing functions are by-construction constant and extremely fast, you will not see any degradations there. However, they do affect the distribution of the elements in the table, right?
  </details>


## Challenge 3: The Skipping Lists

  - **Difficulty**: easy
  - **Goal**: Optimize the parameters of skiplists
  - **Description**: You "inherited" a legacy code from your previous colleauge. He has been using single link lists to implement a queue of requests. The requests are processed in sorted order, however, sometimes requests with certain id are cancelled, so the whole list has to be searched. You decided to optimize this process: you heard about the amazing skip-list structure for faster lookup. You implemented them, but you are not satisfied with the performance. You have to fine-tune two of its parameters: the height and the probability.
  - **Usage**: `./search <input> <height> <probability>`
  <details>
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

  <details>
    <summary>Hint</summary>
    The gist of the ReDoS attack is that it forces badly implemented regular expression engines to backtrack quadratic-times in case of a mismatch. 
  </details>


## Challenge 5: The Bad Recursion

  - **Difficulty**: medium
  - **Goal**: Find and fix the bug
  - **Description**: Your boss has assigned you a project to work on. One customer wants a suggester of a palindromes based on his username or string, or whatever. You do not question your boss and so you delegate this to your fresh intern. He implemented the code, tested it on tacocat, and it worked. But the customer called `amazing_tacocat` has experienced some issues with the code. You should fix the issue and make the palindrome generator great again.
  <details>
    <summary>Hint</summary>
    How do parameteres in C++ work again? Is it by reference or by value?
  </details>

## Challenge 6: The Messy Traces

  - **Difficulty**: medium
  - **Goal**: Optimize the code 
  - **Description**: We finally leave the artificial problems and go for something real. This is a problem, that we have been facing when analysing kernel for some time. The kernel is quite evolving project, with each release, hundreds of functions are changed, hundreds are removed, and hundreds are added. When performance analysts check the code, they not only want to find the functions that might have changed (in terms of performance), but one usually needs some other trace to compare the performance against. This is needed both for automatic and manual analysis. The project contains an AI-generated code for finding good match in previous results (so called baseline) for traces from newly generated data (so called targed). The code is quite inefficient. Try to make it more efficient. There are no limits to your imagination. However, since the code is quite complex, we recommend you to look at the computing cost of two traces: there are lots of recursive calls, right?
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
    It takes a single line to fix a forgotten initialization.
  </details>

## Challenge 8

  - **Difficulty**: hard
  - **Goal**: Just have fun, try to find, what is the problem with the performance.
  - **Description**: This challenge is an open challenge: we know there are some issues with the Maple Trees structure, which were tailored specifically for kernel. You have to install, two kernels: one that has maple trees and one that does not (we suggest to try the same version with backport of Maple Trees). Then compare the results. Since this is quite a hard challenge, we also provide lots of precollected profiles as well as generated differences. You can check these out, if you have problem running the challenge. The kernel versions were, however, censored.
  - **Alternative challenges**:
    1. Try to turn mitigations on or off and observe the results (to turn the mitigations off, you have to run the following: `grubby --update-kernel ALL --args mitigations=off` and then reboot the kernel `rhts-reboot`) 
    2. Try to turn on or off your selinux (don't forget to turn it on afterwards!). To turn the selinux on/off run the following: `grubby --update-kernel ALL --args selinux=0` and reboot your kernel with `rhts-reboot`; to turn the selinux back on, run the following: `grubby --update-kernel ALL --remove-args selinux`.
  <details>
    <summary>Hint</summary>
    No hint, enjoy your dive into kernel madness! We have no idea what is wrong.
  </details>

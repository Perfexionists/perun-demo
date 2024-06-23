## Challenge 7: The CPython Regression

  - **Difficulty**: hard
  - **Goal**: Fix the bug
  - **Description**: This is a reproduction of the known (and now fixed bug) in CPython implementation. Our methods of automatic regression analysis could actually detect this. But you can also use a manual inspection and our interpretation to inspect it as well. Try to find out what is the problem of this bug. We can give you a hint (since CPython is really huge) that the problem is in `ctypes`.
  <details>
    <summary>Hint</summary>
    It takes a single line to fix unnecessarily repeated initialization.
  </details>

## More details

CPython introduced a regression in its 3.11.0a7 version of the `ctypes` implementation
compared to the 3.10.4 version. A new pyperformance benchmark was implemented as part
of the fix so that the issue could be reproduced in the future. We include the slightly
modified benchmark so that you can see the regression for yourself before you dive into
analysing and fixing it.

You can either use the prepared VM where the challenge is already set up and prepared,
in which case you can skip right to the [How to Run](#how-to-run) section. Otherwise
you must first set up the CPython project and benchmark as described in the next
section.

## Setup

First, you will likely need to install the `libffi-devel` dependency on your machine to
use `ctypes` in Python.

Second, you will need to clone, build and install both CPython versions so you can
measure and compare them. The script `clone_cpython.sh` clones a treeless CPython
repository, and the script `build_cpython.sh` builds and installs both CPython versions
in their respective folders `python3.10.4` and `python3.11.0a7`. Both versions are build
in a debug mode with frame pointers enabled so that stack traces are correctly obtained.

Next, you must prepare the `ctypes` benchmark using the `prepare_cmodule.sh` script. The
`prepare_cpython` script automates all of those steps in a single script file for
convenience. 

Lastly, you need to initialize Perun (`perun init`) in the `cpython` directory from
which we will measure the benchmarks.

After all three steps are done, you should have everything set up for the
analysis.

## How to run

If you are using the demonstration VM, all of the steps in the [Setup]($setup) section
were already done for you in the challenge 7 directory.

First of all, you should check whether the ctypes degradation can actually be reproduced
in your environment. Run the `run_benchmark.sh` script that runs the ctypes benchmark
in both CPython versions. The result should like something like this:

    [-] Run the ctypes benchmark in CPython v3.10.4.
    .....................
    ctypes: Mean +- std dev: 1.96 us +- 0.09 us
    [-] Run the ctypes benchmark in CPython v3.11.0a7.
    .....................
    ctypes: Mean +- std dev: 2.32 us +- 0.07 us

After you have confirmed that the degradation indeed manifests on your machine, it is
time to dive deeper into the issue using Perun.

Make sure you have activated your virtual environment with Perun installed, if you are
using one (or use the prepared Python 3.12 venv with pre-installed Perun on the VM).

To measure a performance profile for the 3.10.4 version, run the following:

    cd cpython
    git checkout v3.10.4 
    perun collect -c "../python3.10.4/bin/python3.10" -w "../bm_ctypes/ctypes_benchmark.py" kperf --repeat 3 --warmup 1

The Perun command runs our perf-based collector on the Python 3.10.4 binary with
workload being the ctypes benchmark. We repeat the measurement three times and do a
warmup run beforehand as well. The `ctypes_benchmark.py` file itself actually runs the
ctypes benchmark around 20 times, so the total number of repetitions is 60. This is so
that perf gets a representative number of samples, as the benchmark is quite small.

The resulting profile is stored in `.perun/jobs` directory. You can also run `perun status` to see which profiles are registered and can be used as tags. Note that the
`git checkout` is needed so that Perun knows which CPython version to associate with
the resulting profile.

Now repeat the same process for the 3.11.0a7 version:

    git checkout v3.11.0a7 
    perun collect -c "../python3.11.0a7/bin/python3.11" -w "../bm_ctypes/ctypes_benchmark.py" kperf --repeat 3 --warmup 1

After you have both profiles ready, you can start analysing their differences:

    perun showdiff --offline 1@p 0@p report --minimize -o diffs/comparison

This will take two latest profiles and generate an interactive report in the `diffs`
directory. You can also set absolute paths or use the precollected profiles in the
`profiles` directory.

    perun showdiff --offline profiles/kperf-3.10.perf profiles/kperf-3.11.perf report --minimize -o diffs/comparison-of-cpython-versions

When analysing the root of the issue in the diff report, focus on `_ctypes` functions. 


## Fixing the bug

After you have found the culprit of the issue and have a fix ready, create a new branch
with a commit that contains the fix (make sure you branched from the v3.11.0a7
version). Next, build the new CPython version using the script `./build_fix.sh` that
will, upon a successful compilation, create a directory `python_hotfix` (alongside the
already compile pythons) containing a custom CPython binary `python3.11` with your fix
in `python_hotfix/bin/`.

Now repeat the Perun measurement for your new fixed version and generate a new diff
report to see whether you managed to fix the bug.

Good luck!
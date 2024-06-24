# Challenge 1: The Sorting Hat

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

## More details

The program takes as an argument source file with integers delimited by spaces. It converts them to vector and then runs sorting algorithms on the vector.

You can select the following algorithms:

  1. InsertSort: classic algorithm that for each element finds its place in the already sorted structure and inserts it there.
  2. HeapSort: efficient sort based on specialized heap structure, and is considered to be one of the best performing algorithms (or is it?);
  3. QuickSort: recursive implementation of quicksort based on chosing a pivot and dividing the structure in two segments that are then recursively sorted; it is also considered to be one of the best performing algorithms and is widely used in practice;
  4. QuickSortAlt: an alternative implementation of the quick sort, differs in the way, the vectors are partitioned (does it matter?).

We also prepared directory `inputs` with several inputs that you can try:

  1. Randomly sorted input numbers.
  2. Sorted numbers input numbers.
  3. Reversely sorted input numbers.

You can think how each of the algorithm should behave on these inputs, and
whether they could impact the performance.

## How to run

The program is compilable using make:

    make

We assume, you have initialized Perun somewhere along the path with `perun init` as well as some git (we recommend to create an empty git for these experiments).

To measure a performance profile run the following:

    perun collect -c "./sort_file inputs/<INPUT>" kperf
    perun collect -c "./sort_file inputs/medium-random.txt quicksort" kperf

The first command runs our perf-based collector on `./sort_file` binary with
workload from `inputs` directory, it runs the measurement only once, and
performs no warmups. The resulting profiles are stored in `.perun/jobs`
directory. You can also run `perun status` to see which profiles are registered
and can be used as tags (in form of `i@p`). Alternatively, you can add `-o`
parameter (`perun collect -o out.perf ... kperf`) to save the profile outside of
Perun scope (you will have to specify the profiles manually then).

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison-of-all-vs-quicksort

This will take two latest profiles (in the Perun scope) and generates
interactive report in `diffs` directory. You can also set absolute paths or use
the precollected profiles in `profiles` directory.

    perun showdiff --offline profiles/kperf-insertsort-medium-sorted.perf profiles/kperf-heapsort-medium-sorted.perf report --minimize -o diffs/comparison-of-insertsort-vs-heapsort
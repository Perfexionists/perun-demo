# Challenge 1: The Sorting Hat

  - **Difficulty**: easy
  - **Goal**: Sort the complexities
  - **Description**: You used AI and several interns to generate several sorting algorithm, that will sort the numbers that are obtained from your customer. Now you need to pick *two* of those algorithms to integrate them in practice. While, you sure could analyze their code, your boss needs to see some hard data. Your program takes input file with list of numbers and sorts them using each of the algorithm. You can also run each of them separately by specifying their name. 
  - **Usage**: `./sort_file <input> | <input> <alg1> ... <algn>`
  <details>
    <summary>Hint</summary>
    Though, some algorithms are bundled together as having the same complexity, one of them is an impostor: its quadratic behaviour is forced, when it has to sort already or reversely-sorted inputs.
  </details>

## More details

The program takes as an argument source file with integers delimited by spaces. It converts them to vector and then run sorting algorithms over them.

You can use the following algorithms:

  1. InsertSort: classic algorithm that finds place in already sorted structure and inserts new element.
  2. HeapSort: efficient sort based on heap structure;
  3. QuickSort: recursive implementation of quicksort based on chosing a pivot and dividing the structure in two parts that are recursively sorted.
  4. QuickSortAlt: alternative implementation of the quick sort.

We also prepared in `inputs` several inputs that you can try:

  1. Randomly sorted input numbers.
  2. Sorted numbers input numbers.
  3. Reversely sorted input numbers.

You can think how each of the algorithm should behave on these inputs.

## How to run

We assume, you have initialized Perun somewhere along the path with `perun init`.

To measure a performance profile run the following:

    perun collect -c "./sort_file inputs/<INPUT>" kperf --repeat 1 --warmup 0
    perun collect -c "./sort_file inputs/<INPUT> quicksort" kperf --repeat 1 --warmup 0

The first command runs our perf-based collector on `./sort_file` binary with workload from `inputs` directory, it runs the measurement only once, and performs no warmups. The resulting profiles are stored in `.perun/jobs` directory. You can also run `perun status` to see which profiles are registered and can be used as tags.

You can now compare the two profiles that you generated as follows:

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/comparison-of-all-vs-quicksort

This will take two latest profiles and generates interactive report in `diffs` directory. You can also set absolute paths or use the precollected profiles in `profiles` directory.

    perun showdiff --offline profiles/kperf-[medium-sorted.txt_quicksort]-[].perf profiles/kperf-[medium-sorted.txt_quicksort2]-[].perf report --minimize -o diffs/comparison-of-all-vs-quicksort
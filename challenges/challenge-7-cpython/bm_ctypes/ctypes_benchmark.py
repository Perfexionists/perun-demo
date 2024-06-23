"""
Test the function call overhead of ctypes.

Courtesy of https://github.com/python/pyperformance/pull/197

We use the benchmark from the pull request, but we avoid the pyperformance
dependency to reduce profiling overhead.
"""
import ctypes
from pathlib import Path

import pyperf


ext = ctypes.cdll.LoadLibrary(f"{Path(__file__).parent.resolve()}/cmodule-ctypes.so")

def benchmark_argtypes(loops):
    void_foo_void = ext.void_foo_void
    void_foo_void.argtypes = []
    void_foo_void.restype = None

    int_foo_int = ext.void_foo_int
    int_foo_int.argtypes = [ctypes.c_int]
    int_foo_int.restype = ctypes.c_int

    void_foo_int = ext.void_foo_int
    void_foo_int.argtypes = [ctypes.c_int]
    void_foo_int.restype = None

    void_foo_int_int = ext.void_foo_int_int
    void_foo_int_int.argtypes = [ctypes.c_int, ctypes.c_int]
    void_foo_int_int.restype = None

    void_foo_int_int_int = ext.void_foo_int_int_int
    void_foo_int_int_int.argtypes = [ctypes.c_int, ctypes.c_int, ctypes.c_int]
    void_foo_int_int_int.restype = None

    void_foo_int_int_int_int = ext.void_foo_int_int_int_int
    void_foo_int_int_int_int.argtypes = [
        ctypes.c_int,
        ctypes.c_int,
        ctypes.c_int,
        ctypes.c_int,
    ]
    void_foo_int_int_int_int.restype = None

    void_foo_constchar = ext.void_foo_constchar
    void_foo_constchar.argtypes = [ctypes.c_char_p]
    void_foo_constchar.restype = None

    return benchmark(loops)


def benchmark(loops):
    void_foo_void = ext.void_foo_void
    int_foo_int = ext.int_foo_int
    void_foo_int = ext.void_foo_int
    void_foo_int_int = ext.void_foo_int_int
    void_foo_int_int_int = ext.void_foo_int_int_int
    void_foo_int_int_int_int = ext.void_foo_int_int_int_int
    void_foo_constchar = ext.void_foo_constchar

    # Test calling the functions using the implied arguments mechanism
    t0 = pyperf.perf_counter()

    for i in range(loops):
        void_foo_void()
        int_foo_int(1)
        void_foo_int(1)
        void_foo_int_int(1, 2)
        void_foo_int_int_int(1, 2, 3)
        void_foo_int_int_int_int(1, 2, 3, 4)
        void_foo_constchar(b"bytes")

        void_foo_void()
        int_foo_int(1)
        void_foo_int(1)
        void_foo_int_int(1, 2)
        void_foo_int_int_int(1, 2, 3)
        void_foo_int_int_int_int(1, 2, 3, 4)
        void_foo_constchar(b"bytes")

        void_foo_void()
        int_foo_int(1)
        void_foo_int(1)
        void_foo_int_int(1, 2)
        void_foo_int_int_int(1, 2, 3)
        void_foo_int_int_int_int(1, 2, 3, 4)

    return pyperf.perf_counter() - t0


def add_cmdline_args(cmd, args):
    if args.argtypes:
        cmd.append("--argtypes")


if __name__ == "__main__":
    runner = pyperf.Runner(add_cmdline_args=add_cmdline_args)
    runner.metadata["description"] = "ctypes function call overhead benchmark"

    runner.argparser.add_argument("--argtypes", action="store_true")
    options = runner.parse_args()

    if options.argtypes:
        runner.bench_time_func("ctypes_argtypes", benchmark_argtypes, inner_loops=3)
    else:
        runner.bench_time_func("ctypes", benchmark, inner_loops=3)

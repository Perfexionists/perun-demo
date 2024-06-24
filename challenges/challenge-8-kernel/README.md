## Challenge 8: Linux Kernel

  - **Difficulty**: hard
  - **Goal**: Just have fun, try to find what is the root of the performance problems.
  - **Description**: This is an open challenge: we know there are some performance issues in kernel for which we do not know the root cause yet. In this challenge, we provide multiple sub-problems that you can dive into. Some of the problems come with pre-collected profiles (as they require setting up and measuring multiple custom kernels), while others will let you measure the kernel by yourselves.

  <details>
    <summary>Hint</summary>
    No hint, enjoy your dive into the kernel madness! We have no idea what is wrong.
  </details>

## General instructions

Each of the following challenges expects that you already have activated a virtual environment with installed Perun, and that you either initialized Perun (`perun init`) in the challenge directory or in some of its parent directory.

For the SELinux and Mitigations challenges, you will also need to download a benchmark to use as a workload for Perun kperf collector. As the benchmark is not available to the general public, you will need to download it from a RH server at http://reports.perfqe.tpb.lab.eng.brq.redhat.com/testing/sched/perun/perun-demo.

## Maple Trees

Kernel 6.1 introduced a new Maple Tree data structure for memory management. Although developed specifically to improve the performance, it seems to cause performance regressions on some specific kernels.

For this challenge, we provide two pre-collected profiles in the `maple_trees_profiles` directory. The profiles were measured of the same kernel version except one of them has a maple trees backport. Note the exact kernel versions were censored.

To generate a diff report that you can inspect, run the following command:

    perun showdiff --offline ./maple_trees_profiles/kperf-sng-no-maple-trees.perf ./maple_trees_profiles/kperf-sng-maple-trees-backport.perf report --minimize -o diffs/maple_trees.html

  <details>
    <summary>Hint</summary>
    You can spot maple tree functions by their typical 'mtree' or 'mas_' prefix
  </details>


## SELinux

Security-Enhanced Linux (SELinux) is a Linux kernel security module. Try to turn it on and off (Don't forget to turn it on afterwards!) and see whether you can spot some notable performance issues.

To turn the selinux off run the following: `grubby --update-kernel ALL --args selinux=0` and reboot your kernel with `reboot`; to turn the selinux back on, run the following: `grubby --update-kernel ALL --remove-args selinux`.

Measure the benchmark on both kernel configurations, e.g.:

    perun collect -c "<benchmark>" kperf --with-sudo --repeat 3 --warmup 1

After you have a collected profile for both configurations, generate a diff file

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/selinux.html

and see whether you can spot some performance issues.

The `selinux_profiles` directory contains pre-collected profiles for both configurations measured on the demo VM in case you are not able to measure it. Also, the `diffs` directory contains a pre-generated diff file if the diff generator fails for some reason.

## Mitigations

Spectre and Meltdown security vulnerabilities mandated the implementation of software mitigations within the kernel. Try to turn them on and off and observe the performance results.

To turn the mitigations off, you have to run the following: `grubby --update-kernel ALL --args mitigations=off` and then reboot the kernel `reboot`. To turn them back on, run the following: `grubby --update-kernel ALL --remove-args mitigations`.

Measure the benchmark on a kernel with both mitigations on and off, e.g.:

    perun collect -c "<benchmark>" kperf --with-sudo --repeat 3 --warmup 1

After you have a collected profile for both configurations, generate a diff file

    perun showdiff --offline 0@p 1@p report --minimize -o diffs/mitigations.html

and see whether you can find some interesting performance changes.

The `mitigations_profiles` directory contains pre-collected profiles for both configurations measured on the demo VM in case you are not able to measure it. Also, the `diffs` directory contains a pre-generated diff file if the diff generator fails for some reason.
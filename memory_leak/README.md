# Introduction
- The files in this directory is used to learn 5 typical memory leaks and the tool *valgrind* that is used to detect memory leak.
- The full notes is in [here](https://hackmd.io/@Cg9G-UQmRMyh-L6Jvkq_Gw/B1XkJaZ51e/https%3A%2F%2Fhackmd.io%2F%40Cg9G-UQmRMyh-L6Jvkq_Gw%2Fmemory_leak_analysis_with_valgrind).

- Memory leak types:
    1. *definitely lost*: program is leaking memory.
    2. *indirectly lost*: program is leaking memory in a pointer-based structure. If you fix the *definetly lost* leaks. the *indirectly lost* leaks should go away.
    3. *possibly lost*: program is leaking memory, unless you're doing unusual things with pointers that could cause them to point into the middle of an allocated block.
    4. *still reachable*: program is probably ok - it didn't free some memory it could have. This is quite common and often readable.
    5. *suppressed*: means that a leak error has been suppressed. There are some suppressions in the default suppression files. You can ignore suppressed errors.

# Implementation
## Definetly Lost
- The error message without the `free(buff)` statement is shown as below.
    ```shell=
    HEAP SUMMARY:
        in use at exit: 10 bytes in 1 block
        total heap usage: 1 allocs, 0 frees, 10 bytes allocated
    LEAK SUMMARY:
        definitely lost: 10 bytes in 1 blocks
    ```
- The result with the `free(buff)` statement is shown as below.
    ```
    HEAP SUMMARY:
        in use at exit: 0 bytes in 0 blocks
        total heap usage: 1 allocs, 1 frees, 10 bytes allocated
    All heap blocks were free -- no leak are possible
    ```
## Indirectly Lost
- Without free `root`. `root->left` and `root->right` will cause both *definetly lost* and *indirectly lost* leaks.
- Additionally, the memory size of *indirectly lost* is twice that of *definetly lost* due to the left and right sub-nodes.
    ```shell=
    HEAP SUMMARY:
        in use at exit: 72 bytes in 3 blocks
        total heap usage: 3 allocs, 0 frees, 72 bytes allocated
    LEAK SUMMARY:
        definitely lost: 24 bytes in 1 blocks
        indirectly lost: 48 bytes in 2 blocks
    ```
- If I free only the the root node or both the right and left child nodes, the memory remaining is *definitely lost*.
    ```shell=
    HEAP SUMMARY:
        in use at exit: 48 bytes in 2 blocks
        total heap usage: 3 allocs, 1 frees, 72 bytes allocated
    LEAK SUMMARY:
        definitely lost: 48 bytes in 2 blocks
        indirectly lost: 0 bytes in 0 blocks
    ```
## Possibly Lost
- The `free(p)` statement will not be executed because the program terminals at `abort()` statement.
    ```shell=
    Process terminating with default action of signal 6 (SIGABRT)
        at 0x490EB2C: __pthread_kill_implementation (pthread_kill.c:44)
        by 0x490EBC2: __pthread_kill_internal (pthread_kill.c:78)
        by 0x490EBC2: pthread_kill@@GLIBC)2.34 (pthread_kill.c:89)
        by 0x48B527D: raise (raise.c:26)
        by 0x48988FE: abort (abort.c:79)
        by 0x1091A0: main (possLoss.c:7)
    
    HEAPSUMMARY:
        in use at exit: 7 bytes in 1 blocks
        total heap usage: 1 allocas, 0 frees, 7 bytes allocated
    
    7 bytes in 1 blocks are possibly lost in loss record 1 of 1
        at 0x4846828: malloc (in/usr/libexec/valgrind/vgpreload_memcheck-amd64-linux.so)
        by 0x492435E: strdup (strdup.c:42)
        by 0x109192: main (possLost.c:7)
    
    LEAK SUMMARY:
        possibly lost: 7 bytes in 0 blocks
    ```
# Reference
- [The Valgrind Quick Start Guide](https://valgrind.org/docs/manual/quick-start.html)
- [Valgrind Frequently Asked Questions](https://valgrind.org/docs/manual/faq.html#faq.deflost)
- [Valgrind: can possibly lost be treated as definitely lost?](https://stackoverflow.com/questions/3537713/valgrind-can-possibly-lost-be-treated-as-definitely-lost)
- [C語言的記憶體洩漏(Memory Leak)偵測 - Valgrind](http://blog.yslin.tw/2014/03/c-valgrind.html)
- [Valgrind + 自動測試程式](https://hackmd.io/@sysprog/linux2023-lab0/%2F%40sysprog%2Flinux2023-lab0-b)

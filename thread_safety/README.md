# Introduction
- This directory is used to analyze thread safety, mutex lock and atomic operation in C standard library.
- The full note is at [here](https://hackmd.io/@Cg9G-UQmRMyh-L6Jvkq_Gw/thread_safety_analysis).
# Implementation
- Environment Setting:
    - Ubuntu Linux: 24.04.1 LTS
    - gcc: 13.3.0
- Compile a file into an executable.
    ```shell=
    gcc -g -Wall -v filename.c -o filename
    ```
- Run the executable.
    ```shell=
    ./filename
    ```

# Reference
- [深入理解 Linux 程式設計：從應用到核心](https://www.tenlong.com.tw/products/9789864764167)
- [gfreewind](https://github.com/gfreewind/aple_codes/blob/master/chapter0/0.4.3/0_4_3_threads_cnt.c)


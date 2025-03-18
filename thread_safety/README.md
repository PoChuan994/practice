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
- Disassemble the executable
    ```shell=
    $ objdump -d threads_counter > disassebly.txt
    $ vim disassembly.txt
    ```
- Use GDB to obtain the assembly code.
    ```shell=
    # Activate GDB
    $ gdb threads_counter

    # Set the break point
    $ break thread

    # Execute the process
    $ run

    # Generate the assembly code as the thread is paused
    $ disassemble thread
    ```
## Race condition
- Both threads in the `threads.c` access the static variable counter without any protection against race conditions.
- The expected value of `counter`  variable is to be 20,000,000 but the actual value of is significantly lower.
    ```c=
    'Counter is 11769728 by thread'
    # expected output is
    # 'Counter is 20000000 by thread'
    ```
- After disassemble `threads`, we can observe that the `counter` variable is modified by the following three assembly instructions. This is a typical race condition problem: both threads access counter almost simutaneously, only the last completed the operation is stored into the 'counter'.
    ```shell=
    11be:	8b 05 50 2e 00 00    	mov    0x2e50(%rip),%eax        # 4014 <counter>
    11c4:	83 c0 01             	add    $0x1,%eax
    11c7:	89 05 47 2e 00 00    	mov    %eax,0x2e47(%rip)        # 4014 <counter>
    ```
# Reference
- [深入理解 Linux 程式設計：從應用到核心](https://www.tenlong.com.tw/products/9789864764167)
- [gfreewind](https://github.com/gfreewind/aple_codes/blob/master/chapter0/0.4.3/0_4_3_threads_cnt.c)


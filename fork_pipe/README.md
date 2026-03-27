Parallel Array Summation (C/Linux)

A high-performance demonstration of Inter-Process Communication (IPC) using the fork() system call and Unix pipes.
🚀 Overview

This project tackles the classic "Divide and Conquer" problem by splitting a linear array summation into three parallel tasks. Each task runs in its own isolated process memory space, with results aggregated through a synchronous pipe relay.
🏗️ Architecture: The Relay Logic

Unlike a standard parallel sum where all children talk to the parent simultaneously, this project implements a sequential daisy-chain:

    Child 1: Calculates the first 1/3 of the array → Writes to Pipe.

    Child 2: Reads from Child 1 → Adds the middle 1/3 → Writes to Pipe.

    Parent: Calculates the final 1/3 → Reads the accumulated total from the Pipe → Prints result.

🛠️ Technical Concepts Used

    Process Management: Utilizing fork() to create a controlled process tree.

    IPC (Pipes): Using pipe(), read(), and write() for data transmission across process boundaries.

    Synchronization: Implementing wait() to prevent "zombie processes" and ensure data integrity.

    Boundary Management: Dynamic "step" calculation to handle arrays of any length without data loss.

⚠️ Lessons Learned: The Deadlock Challenge

During development, we encountered a synchronization challenge regarding the order of wait() and read(). In this relay-style architecture, the Parent must wait() for the children to finish their calculation cycle before reading the final result to ensure the pipe buffer is fully flushed and the sequence is maintained.

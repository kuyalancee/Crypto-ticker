# Crypto Ticker

## What is it?

A simple C++ program that ingests real-time crypto trade data from Coinbase via
WebSockets and is visualized at user's terminal.  
Created to get more familiar with multithreading, C++ logic, and benchmarking  

## Build & Run
```bash
mkdir build && cd build
cmake ..
make
./ticker        # For the main app
./bench_ticker  # For benchmarks
```

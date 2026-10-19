#pragma once

#include <chrono>
#include <fstream>
#include <iostream>
#include <vector>

struct BenchmarkEntry {
    long long totalElapsed;
    long long splitTime;
};

class Benchmarking {
public:
    Benchmarking(const std::string& outputFilename = "benchmark_results.csv");
    ~Benchmarking();
    void flush();
    void startTimer();
    void timestamp();
    void printElapsedTime();

private:
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point endTime;
    std::chrono::high_resolution_clock::time_point currentTime;
    std::vector<BenchmarkEntry> benchmarks;
    //std::chrono::high_resolution_clock::duration elapsedTime;
    std::ofstream outputFile;
};
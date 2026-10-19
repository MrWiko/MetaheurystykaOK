#include "benchmarking.h"

Benchmarking::Benchmarking(const std::string& outputFilename) {
    outputFile.open(outputFilename, std::ios::out | std::ios::app);
    if (!outputFile.is_open()) {
        std::cerr << "Error opening file: " << outputFilename << std::endl;
    } else {
        outputFile << "Timestamp,Elapsed Time (ns)" << std::endl; // Write CSV header
    }
    benchmarks.reserve(1000);
}
Benchmarking::~Benchmarking() {
    if (outputFile.is_open()) {
        for(auto& entry : benchmarks) {
            outputFile << entry.splitTime << "," << entry.totalElapsed << std::endl; // Write benchmark entries to file
        }
        outputFile.close();
    }
}
void Benchmarking::startTimer() {
    startTime = std::chrono::high_resolution_clock::now();
    currentTime = startTime; // Initialize currentTime to startTime
  //  outputFile << std::chrono::duration_cast<std::chrono::milliseconds>(startTime - startTime).count() << ",";
//    outputFile << std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - startTime).count() << std::endl; // Placeholder for elapsed time
    benchmarks.push_back({0, 0}); // Add a new benchmark entry with default values
}

void Benchmarking::flush() {
    if (outputFile.is_open()) {
        for(auto& entry : benchmarks) {
            outputFile << entry.splitTime << "," << entry.totalElapsed << "\n"; // Write benchmark entries to file
        }
        benchmarks.clear(); // Clear the benchmarks vector after flushing to file
        outputFile.flush();
    }
  //  outputFile.flush(); // Ensure all data is written to the file
}

void Benchmarking::timestamp() {
    endTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    auto timestamp = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - currentTime).count();
    currentTime = endTime; // Update currentTime to endTime for next timestamp
   benchmarks.push_back({elapsedTime, timestamp}); // Store the benchmark entry in the vector
}


void Benchmarking::printElapsedTime() {
    endTime = std::chrono::high_resolution_clock::now();
    auto elapsedTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endTime - startTime).count();
    std::cout << "Elapsed time: " << elapsedTime << " ms" << std::endl;
}
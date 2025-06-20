#include "result.h"

#include <limits>
#include <fstream>

// Load results from a file
Result Result::loadResults(std::string& filename) {
    std::ifstream results_file(filename); // Open the file for reading
    Result results;                       // Create an empty Result object

    size_t size;
    results_file >> size;                 // Read the number of results

    // Read each result until the end of file or the specified size is reached
    while (!results_file.eof() && size-- != 0) {
        size_t iteration;
        int result;
        results_file >> iteration >> result;                   // Read iteration and result value
        results.addResult(iteration, static_cast<ResultValue>(result)); // Add the result to the Result object
    }

    return results; // Return the populated Result object
}

// Save results to a file
void Result::saveResults(const std::string& filename) const {
    std::ofstream results_file(filename); // Open the file for writing

    results_file << results.size();       // Write the number of results

    // Write each result as "iteration result"
    for (const auto& result : results) {
        results_file << '\n' << result.first << ' ' << result.second;
    }

    results_file.close(); // Close the file
}
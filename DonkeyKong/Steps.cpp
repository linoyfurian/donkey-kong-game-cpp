#include "Steps.h"

// Load Steps from a file
Steps Steps::loadSteps(std::string& filename) {
    Steps steps;
    std::ifstream steps_file(filename); // Open the file for reading
    steps_file >> steps.randomSeed;     // Read the random seed value

    size_t size;
    steps_file >> size;                 // Read the number of steps

    // Read each step until the end of file or the specified size is reached
    while (!steps_file.eof() && size-- != 0) {
        size_t iteration;
        char step;
        steps_file >> iteration >> step; // Read iteration and step
        steps.addStep(iteration, step);  // Add the step to the Steps object
    }

    steps_file.close(); // Close the file
    return steps;       // Return the populated Steps object
}

// Save Steps to a file
void Steps::saveSteps(const std::string& filename) const {
    std::ofstream steps_file(filename); // Open the file for writing
    steps_file << randomSeed << '\n'    // Write the random seed value
        << steps.size();         // Write the number of steps

    // Write each step as "iteration step"
    for (const auto& step : steps) {
        steps_file << '\n' << step.first << ' ' << step.second;
    }

    steps_file.close(); // Close the file
}
#pragma once

#ifndef __RESULT_H
#define __RESULT_H

#include <list>
#include "iostream"

// Class that represents the results in the game, including their iterations and outcome (explosion, victory, or no result)
class Result
{
public:
    // Enum that defines possible result values for the game
    enum ResultValue { explosion, victory, noResult };

private:
    // List to store results, where each result is represented by a pair (iteration, result type)
    std::list<std::pair<size_t, ResultValue>> results;

public:

    // Method to add a new result with a specific iteration number and result type (explosion, victory, etc.)
    void addResult(size_t iteration, ResultValue result) {
        results.push_back({ iteration, result }); // Add the result to the list
    }
    static Result loadResults(std::string& filename); // Static method to load the results from a file into a Result object
    void saveResults(const std::string& filename) const;  // Method to save the current results to a specified file
    // Method to clear all results from the list
    void clearResult() {
        results.clear(); // Remove all results from the list
    }
    // Getter method to retrieve the list of results
    std::list<std::pair<size_t, ResultValue>>& getList() {
        return results; // Return the list of results
    }

};

#endif
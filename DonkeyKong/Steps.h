#pragma once

#ifndef __STEPS_H
#define __STEPS_H

#include <list>
#include <string>
#include <fstream>

// Class that represents the steps in the game, including their iterations and the actions taken at each step.
class Steps
{
    long randomSeed = 0; // Variable to store the random seed for the game
    std::list<std::pair<size_t, char>> steps; // List to store steps, where each step is represented by a pair (iteration, step action)

public:

    static Steps loadSteps(std::string& filename); // Static method to load the steps from a file into a Steps object
    void saveSteps(const std::string& filename) const;// Method to save the steps to a specified file
    // Getter method to retrieve the random seed
    long getRandomSeed() const {
        return randomSeed;
    }
    // Setter method to set the random seed
    void setRandomSeed(long seed) {
        randomSeed = seed;
    }
    // Method to add a new step with a specific iteration number and action
    void addStep(size_t iteration, char step) {
        steps.push_back({ iteration, step }); // Add the step to the list of steps
    }
    // Method to clear all the steps from the list
    void clearSteps() {
        steps.clear(); // Remove all steps from the list
    }
    // Getter method to retrieve the list of steps
    std::list<std::pair<size_t, char>>& getList() {
        return steps; // Return the list of steps
    }
};

#endif
#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <climits>
#include <chrono>


using namespace std;

class UniformCost {
public:
    // Constructor
    UniformCost(int numCities, const vector<vector<int>>& distances)
        : numCities(numCities), distances(distances) {}

    // Method to solve the problem
    void solve() {
        // Priority queue for the states
        priority_queue<State, vector<State>, greater<State>> pq;

        // Initialize the search with the starting city
        pq.push({ 0, 1 << 0, 0, {0} });

        while (!pq.empty()) {
            State state = pq.top();
            pq.pop();

            // If all cities are visited and we return to the start city
            if (state.visitedMask == (1 << numCities) - 1) {
                state.maxEdgeCost = max(state.maxEdgeCost, distances[state.currentCity][0]);
                if (state.maxEdgeCost < minLongestDistance) {
                    minLongestDistance = state.maxEdgeCost;
                    bestRoute = state.route;
                    bestRoute.push_back(0); // Return to the start city
                }
                continue;
            }

            // Explore the next cities
            for (int nextCity = 0; nextCity < numCities; nextCity++) {
                if (!(state.visitedMask & (1 << nextCity))) {
                    int nextVisitedMask = state.visitedMask | (1 << nextCity);
                    int nextMaxEdgeCost = max(state.maxEdgeCost, distances[state.currentCity][nextCity]);

                    vector<int> nextRoute = state.route;
                    nextRoute.push_back(nextCity);

                    pq.push({ nextCity, nextVisitedMask, nextMaxEdgeCost, nextRoute });
                }
            }
        }
    }

    // Method to print the solution
    void printSolution() const {
        cout << "Minimum longest distance: " << minLongestDistance << endl;
        cout << "Best route: ";
        for (int city : bestRoute) {
            cout << city << " ";
        }
        cout << endl;
    }

    struct State {
        int currentCity;
        int visitedMask;
        int maxEdgeCost;
        vector<int> route;

        bool operator>(const State& other) const {
            return maxEdgeCost > other.maxEdgeCost;
        }
    };

    double measure_runtime() {
        auto start = chrono::high_resolution_clock::now();

        solve(); // Call the solve method

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        return duration.count(); // Return duration in seconds
    }

    void calculateTotalCost() {
        int totalCost = 0;
        for (size_t i = 0; i < bestRoute.size() - 1; ++i) {
            totalCost += distances[bestRoute[i]][bestRoute[i + 1]];
        }
        cout << "The total cost is " << totalCost << endl;
    }

private:
    int numCities;
    vector<vector<int>> distances;
    int minLongestDistance = INT_MAX;
    vector<int> bestRoute;

};

#pragma once
#include <iostream>
#include <fstream>
#include <cmath>
#include <string>
#include <cstring>
#include <vector>
#include <queue>
#include <chrono>


using namespace std;

struct State {
    int currentCity;
    int visitedMask;
    int maxEdgeCost;
    vector<int> route;

    bool operator>(const State& other) const {
        return maxEdgeCost > other.maxEdgeCost;
    }
};

class BFS {
public:
    BFS(int numCities, const vector<vector<int>>& distances)
        : numCities(numCities), distances(distances) {}

    void solve() {
        queue<State> q;

        // Initialize the search with the starting city
        q.push({ 0, 1 << 0, 0, {0} });

        while (!q.empty()) {
            State state = q.front();
            q.pop();

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

            for (int nextCity = 0; nextCity < numCities; nextCity++) {
                if (!(state.visitedMask & (1 << nextCity))) {
                    int nextVisitedMask = state.visitedMask | (1 << nextCity);
                    int nextMaxEdgeCost = max(state.maxEdgeCost, distances[state.currentCity][nextCity]);
                    vector<int> nextRoute = state.route;
                    nextRoute.push_back(nextCity);

                    q.push({ nextCity, nextVisitedMask, nextMaxEdgeCost, nextRoute });
                }
            }
        }
    }

    void printSolution() const {
        cout << "Minimum longest distance: " << minLongestDistance << endl;
        cout << "Best route: ";
        for (int city : bestRoute) {
            cout << city << " ";
        }
        cout << endl;
    }

    void calculateTotalCost() {
        int totalCost = 0;
        for (size_t i = 0; i < bestRoute.size() - 1; ++i) {
            totalCost += distances[bestRoute[i]][bestRoute[i + 1]];
        }
        cout << "The total cost is " << totalCost << endl;
    }

    double measure_runtime() {
        auto start = chrono::high_resolution_clock::now();

        solve(); // Call the solve method

        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> duration = end - start;

        return duration.count(); // Return duration in seconds
    }
private:
    int numCities;
    vector<vector<int>> distances;
    int minLongestDistance = INT_MAX;
    vector<int> bestRoute;
};

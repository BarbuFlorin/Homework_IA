#include <iostream>
#include <vector>
#include <iomanip>

#include "BFS.h"
#include "UCS.h"
#include "AStarS.h"

using namespace std;

int main() {
    int numCities = 4;
    vector<vector<int>> distances = {
            {0, 10, 15, 20},
            {10, 0, 35, 25},
            {15, 35, 0, 30},
            {20, 25, 30, 0}
    };

    cout << "BFS\n\n";

    BFS bfs(numCities, distances);
    bfs.solve();
    bfs.printSolution();
    bfs.calculateTotalCost();
    double runtime1 = bfs.measure_runtime();
    cout << "BFS Time taken: " << std::fixed << std::setprecision(6) << runtime1 << " seconds" << endl;

    cout << "\n------------------------------------------------------------------------\n\n";
    cout << "UNIFORM COST\n\n";

    UniformCost uniformCost(numCities, distances);
    uniformCost.solve();
    uniformCost.printSolution();
    uniformCost.calculateTotalCost();
    double runtime2 = uniformCost.measure_runtime();
    cout << "Uniform Cost Time taken: " << std::fixed << std::setprecision(6) << runtime2 << " seconds" << endl;

    cout << "\n------------------------------------------------------------------------\n\n";
    cout << "A* SEARCH\n\n";

    ASearch aSearch(numCities, distances);
    aSearch.solve();
    aSearch.printSolution();
    aSearch.calculateTotalCost();
    double runtime3 = uniformCost.measure_runtime();
    cout << "A* Search Time taken: " << std::fixed << std::setprecision(6) << runtime3 << " seconds" << endl;

    return 0;
}
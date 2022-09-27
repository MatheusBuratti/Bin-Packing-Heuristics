#include <iostream>
#include <string>
#include <vector>

#include "greedy.cpp"
#include "localSearch.cpp"
#include "problem.hpp"

/* ========== TODO ==========
**
** ==========================
*/

int main(int argc, char *argv[]) {
    if (argc > 1) {
        // ---------- LEITURA DA ENTRADA ----------
        std::string OPT = argv[1];
        std::vector<Problem> problems;
        if (OPT == "J") {
            int NoP;
            std::cin >> NoP;
            for (int j = 0; j < NoP; j++) {
                Problem P;
                std::cin >> P.identifier;
                std::cin >> P.binCapacity;
                std::cin >> P.n;
                std::cin >> P.bestSolution;
                for (int i = 0; i < P.n; i++) {
                    int item;
                    std::cin >> item;
                    P.items.push_back(item);
                }
                problems.push_back(P);
            }
        } else if (OPT == "S") {
            Problem P;
            P.identifier = "Scholl";
            std::cin >> P.n;
            std::cin >> P.binCapacity;
            P.bestSolution = 0;
            for (int i = 0; i < P.n; i++) {
                int item;
                std::cin >> item;
                P.items.push_back(item);
            }
            problems.push_back(P);
        } else {
            std::cout << "Input error" << std::endl;
            return 0;
        }
        std::vector<Solution> nextFitDecreasing, localSearch;

        for (auto it = problems.begin(); it != problems.end(); it++) {
            Solution greedySol = Greedy::nextFitDecreasing(*it);
            nextFitDecreasing.push_back(greedySol);
            localSearch.push_back(LocalSearch::reconstructBins(*it, greedySol));

            // Print temporário:
            std::cout << "Problem identifier: " << it->identifier << std::endl;
            std::cout << "NFD greedy solution: " << (nextFitDecreasing.end() - 1)->bins.size() << std::endl;
            std::cout << "Local Search solution: " << (localSearch.end() - 1)->bins.size() << std::endl;
            std::cout << "Best solution: " << it->bestSolution << std::endl
                      << "=============================" << std::endl;
        }
    }
    return 0;
}
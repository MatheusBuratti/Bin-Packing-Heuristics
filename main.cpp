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
        if (OPT == "F") {
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
        std::vector<Solution> nextFit, nextFitDecreasing, localSearch1, localSearch2;

        for (auto it = problems.begin(); it != problems.end(); it++) {
            Solution naiveFit = Greedy::naiveFit(*it);
            Solution simpleFit = Greedy::simpleFit(*it);
            Solution nextFitDec = Greedy::nextFitDecreasing(*it);

            // Print temporário:
            std::cout << "Problem identifier: " << it->identifier << std::endl;
            std::cout << "Naive solution: " << naiveFit.bins.size() << std::endl;
            std::cout << "Local Search Naive: " << LocalSearch::reconstructBins(*it, naiveFit).bins.size() << std::endl;
            std::cout << "NF Solution: " << simpleFit.bins.size() << std::endl;
            std::cout << "Local Search NF: " << LocalSearch::reconstructBins(*it, simpleFit).bins.size() << std::endl;
            std::cout << "NFD greedy solution: " << nextFitDec.bins.size() << std::endl;
            std::cout << "Local Search NFD: " << LocalSearch::reconstructBins(*it, nextFitDec).bins.size() << std::endl;
            std::cout << "Best solution: " << it->bestSolution << std::endl
                      << "=============================" << std::endl;
        }
    }
    return 0;
}
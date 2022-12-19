#include <iostream>
#include <string>
#include <vector>

#include "greedy.cpp"
#include "localSearch.cpp"
#include "metaheuristic.cpp"
#include "problem.cpp"

/*
        "-O3",
        "-ffast-math",
*/

int main(int argc, char *argv[]) {
    // Multiple Inputs
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
                    P.items_weights.push_back(item);
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
                P.items_weights.push_back(item);
            }
            problems.push_back(P);
        } else {
            std::cout << "Input error" << std::endl;
            return 0;
        }

        for (auto it = problems.begin(); it != problems.end(); it++) {
            // Print temporário:
            std::cout << "Problem identifier: " << it->identifier << std::endl;
            Solution Sol = Greedy::nextFit(*it);
            std::cout << "NF Solution: " << Sol.bins_list.size() << std::endl;
            Sol = Greedy::nextFit(*it);
            std::cout << "HillClimb NF: " << LocalSearch::HillClimb(*it, Sol).bins_list.size() << std::endl;
            Sol = Greedy::nextFit(*it);
            std::cout << "Annealing NF: " << Metaheuristics::WeightAnnealing(*it, Sol).bins_list.size() << std::endl;
            Sol = Greedy::nextFitDecreasing(*it);
            std::cout << "NFD greedy solution: " << Sol.bins_list.size() << std::endl;
            Sol = Greedy::nextFit(*it);
            std::cout << "HillClimb NFD: " << LocalSearch::HillClimb(*it, Sol).bins_list.size() << std::endl;
            Sol = Greedy::nextFit(*it);
            std::cout << "Annealing NFD: " << Metaheuristics::WeightAnnealing(*it, Sol).bins_list.size() << std::endl;
            std::cout << "Best solution: " << it->bestSolution << std::endl
                      << "=============================" << std::endl;
        }
    } else {
        Problem P;
        std::cin >> P.identifier;
        std::cin >> P.binCapacity;
        std::cin >> P.n;
        std::cin >> P.bestSolution;
        for (int i = 0; i < P.n; i++) {
            int item;
            std::cin >> item;
            P.items_weights.push_back(item);
        }
        // Print temporário:
        std::cout << "Problem identifier: " << P.identifier << std::endl;
        Solution Sol = Greedy::nextFit(P);
        std::cout << "NF Solution: " << Sol.bins_list.size() << std::endl;
        Sol = Greedy::nextFit(P);
        std::cout << "HillClimb NF: " << LocalSearch::HillClimb(P, Sol).bins_list.size() << std::endl;
        Sol = Greedy::nextFit(P);
        std::cout << "Annealing NF: " << Metaheuristics::WeightAnnealing(P, Sol).bins_list.size() << std::endl;
        Sol = Greedy::nextFitDecreasing(P);
        std::cout << "NFD greedy solution: " << Sol.bins_list.size() << std::endl;
        Sol = Greedy::nextFitDecreasing(P);
        std::cout << "HillClimb NFD: " << LocalSearch::HillClimb(P, Sol).bins_list.size() << std::endl;
        Sol = Greedy::nextFitDecreasing(P);
        std::cout << "Annealing NFD: " << Metaheuristics::WeightAnnealing(P, Sol).bins_list.size() << std::endl;
        std::cout << "Best solution: " << P.bestSolution << std::endl
                  << "=============================" << std::endl;
    }
    return 0;
}
#include <chrono>
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
    std::chrono::steady_clock::time_point begin, end;
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
            begin = std::chrono::steady_clock::now();
            Solution Sol = Greedy::nextFit(*it);
            end = std::chrono::steady_clock::now();
            std::cout << "NF Solution: " << Sol.bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
            begin = std::chrono::steady_clock::now();
            Sol = Greedy::nextFit(*it);
            end = std::chrono::steady_clock::now();
            std::cout << "HillClimb NF: " << LocalSearch::HillClimb(*it, Sol).bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
            begin = std::chrono::steady_clock::now();
            Sol = Greedy::nextFit(*it);
            end = std::chrono::steady_clock::now();
            std::cout << "Annealing NF: " << Metaheuristics::WeightAnnealing(*it, Sol).bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
            begin = std::chrono::steady_clock::now();
            Sol = Greedy::nextFitDecreasing(*it);
            end = std::chrono::steady_clock::now();
            std::cout << "NFD greedy solution: " << Sol.bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
            begin = std::chrono::steady_clock::now();
            Sol = Greedy::nextFitDecreasing(*it);
            end = std::chrono::steady_clock::now();
            std::cout << "HillClimb NFD: " << LocalSearch::HillClimb(*it, Sol).bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
            begin = std::chrono::steady_clock::now();
            Sol = Greedy::nextFitDecreasing(*it);
            end = std::chrono::steady_clock::now();
            std::cout << "Annealing NFD: " << Metaheuristics::WeightAnnealing(*it, Sol).bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
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
        // Print temporário:
        std::cout << "Problem identifier: " << P.identifier << std::endl;
        begin = std::chrono::steady_clock::now();
        Solution Sol = Greedy::nextFit(P);
        end = std::chrono::steady_clock::now();
        std::cout << "NF Solution: " << Sol.bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        // begin = std::chrono::steady_clock::now();
        // Sol = Greedy::nextFit(P);
        // Sol = LocalSearch::HillClimb(P, Sol);
        // end = std::chrono::steady_clock::now();
        // std::cout << "HillClimb NF: " << Sol.bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        // begin = std::chrono::steady_clock::now();
        // Sol = Greedy::nextFit(P);
        // Sol = Metaheuristics::WeightAnnealing(P, Sol);
        // end = std::chrono::steady_clock::now();
        // std::cout << "Annealing NF: " << Sol.bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        begin = std::chrono::steady_clock::now();
        Sol = Greedy::nextFitDecreasing(P);
        end = std::chrono::steady_clock::now();
        std::cout << "NFD greedy solution: " << Sol.bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << "[µs]" << std::endl;
        begin = std::chrono::steady_clock::now();
        Sol = Greedy::nextFitDecreasing(P);
        Sol = LocalSearch::HillClimb(P, Sol);
        end = std::chrono::steady_clock::now();
        std::cout << "HillClimb NFD: " << Sol.bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        begin = std::chrono::steady_clock::now();
        Sol = Greedy::nextFitDecreasing(P);
        Sol = Metaheuristics::WeightAnnealing(P, Sol);
        end = std::chrono::steady_clock::now();
        std::cout << "Annealing NFD: " << Sol.bins_list.size() << " Time: " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << "[ms]" << std::endl;
        std::cout << "Best solution: " << P.bestSolution << std::endl
                  << "=============================" << std::endl;
    }
    return 0;
}
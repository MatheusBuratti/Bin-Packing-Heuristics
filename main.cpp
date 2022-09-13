#include <iostream>
#include <vector>

#include "problem.h"
#include "greedy.cpp"

/* ========== TODO ==========
** Resolver alguns na mão pra ver se    
**  não fiz nada de errado no greedy.
**
** ==========================
*/ 

int main(void){

    // ---------- LEITURA DA ENTRADA ----------
    int NoP;
    std::cin >> NoP;
    std::vector<Problem> problems;
    for(int j=0; j<NoP; j++){
        Problem P;
        std::cin >> P.identifier;
        std::cin >> P.binCapacity;
        std::cin >> P.n;
        std::cin >> P.bestSolution;
        for(int i=0; i<P.n; i++){
            int item;
            std::cin >> item;
            P.items.push_back(item);
        }
        // Organiza o vetor
        std::sort(P.items.begin(), P.items.end(), std::greater<int>());

        problems.push_back(P);
    }

    std::vector<std::vector<int>> fastGreedySolution, searchGreedySolution;
    
    for(auto it = problems.begin(); it != problems.end(); it++){
        fastGreedySolution.push_back(fastGreedySolver(*it));
        searchGreedySolution.push_back(searchGreedySolver(*it));

        //Print temporário:
        std::cout << "Problem identifier: " << it->identifier << std::endl;
        std::cout << "Fast greedy solution: " << (fastGreedySolution.end()-1)->size() << std::endl;
        std::cout << "Search greedy solution: " << (searchGreedySolution.end()-1)->size() << std::endl;
        std::cout << "Best solution: " << it->bestSolution << std::endl << "=============================" << std::endl;
    }
    return 0;
}
#include <iostream>

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
    Problem *problems = new Problem[NoP];
    for(int j=0; j<NoP; j++){
        std::cin >> problems[j].identifier;
        std::cin >> problems[j].binCapacity;
        std::cin >> problems[j].n;
        std::cin >> problems[j].bestSolution;
        problems[j].items = new int[problems[j].n];
        for(int i=0; i<problems[j].n; i++){
            std::cin >> problems[j].items[i];
        }
    }
    std::vector<int> greedySolution = greedySolver(problems[0]);
    for(auto i = greedySolution.begin(); i != greedySolution.end(); i++){
        std::cout << *i << ' ';
    }
    std::cout << std::endl << std::endl;
    std::cout << "Solution: " << greedySolution.size() << std::endl;
    std::cout << "Best Sol: " << problems[0].bestSolution << std::endl;
    return 0;
}
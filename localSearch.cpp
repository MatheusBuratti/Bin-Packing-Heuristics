#pragma once
#include <algorithm>
#include <ctime>
#include <vector>

#include "greedy.cpp"
#include "problem.hpp"
class LocalSearch {
   public:
    static Solution reconstructBins(Problem P, Solution startSol) {
        // Pegando parte final do vetor de items (tamanho aleatório)
        srand((unsigned)time(0));
        int N = (rand() % (P.n * 3 / 4)) + P.n / 4;  // vai reconstruir de N até o fim

        // Removendo os items das bins
        std::vector<ItemSol>::iterator it_items = startSol.item.begin();
        for (std::advance(it_items, N); it_items != startSol.item.end(); it_items++) {
            startSol.bins.at(it_items->bin_index) -= it_items->weight;
            it_items->bin_index = -1;
        }

        // Agora aplicando a estratégia de Best Fit
        it_items = startSol.item.begin();
        for (std::advance(it_items, N); it_items != startSol.item.end(); it_items++) {
            std::vector<int>::iterator bestFit = startSol.bins.end();
            for (std::vector<int>::iterator it_bins = startSol.bins.begin(); it_bins != startSol.bins.end(); it_bins++) {
                if ((P.n - *it_bins) > it_items->weight) {                        // Se o espaço na bin cabe o item
                    if (bestFit == startSol.bins.end() || *it_bins > *bestFit) {  // Se a bin estiver mais cheia
                        bestFit = it_bins;
                    }
                }
            }
            if (bestFit == startSol.bins.end()) {  // Caso não tenha nenhuma bin que caiba o item cria uma nova
                startSol.bins.push_back(it_items->weight);
                it_items->bin_index = startSol.bins.end() - startSol.bins.begin() - 1;
            } else {  // Caso encontre o bestFit, adiciona o item a essa bin
                *bestFit += it_items->weight;
                it_items->bin_index = bestFit - startSol.bins.begin();
            }
        }
        return startSol;
    }

    /*
         Fitness eq1. [Hyde(2010)]:
         Fitness = 1 - sum((fullness/capacity)²)/numbins
    */
    static int _calcFitness(Problem P, Solution S) {
        int result = 0;
        for (auto it = S.bins.begin(); it != S.bins.end(); it++) {
            result += (*it / P.binCapacity) * (*it / P.binCapacity);  // (fullness/capacity)²
        }
        result /= S.bins.size();  //    sum/numbins
        return (1 - result);
    }
};
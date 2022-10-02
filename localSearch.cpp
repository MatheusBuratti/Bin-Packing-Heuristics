#pragma once
#include <algorithm>
#include <ctime>
#include <vector>

#include "greedy.cpp"
#include "problem.hpp"

class LocalSearch {
   public:
    static Solution reconstructBins(Problem P, Solution startSolution) {
        // Pegando parte final do vetor de items de tamanho aleatório
        srand((unsigned)time(0));
        int N = (rand() % P.n / 2) + P.n / 2;  // vai reconstruir de N até o fim

        // Removendo os items das bins
        std::vector<ItemSolution>::iterator it_items = startSolution.item.begin();
        for (it_items += N; it_items != startSolution.item.end(); it_items++) {
            if (*(it_items->bin_index) == it_items->weight)     // Se for o último item da bin
                startSolution.bins.erase(it_items->bin_index);  // Remove a bin
            else
                *(it_items->bin_index) -= it_items->weight;
            it_items->bin_index = startSolution.bins.end();  // Flag para item não alocado a uma bin
        }

        // Agora aplicando a estratégia de Best Fit
        it_items = startSolution.item.begin();
        for (it_items += N; it_items != startSolution.item.end(); it_items++) {
            std::list<int>::iterator bestFit = startSolution.bins.end();
            for (std::list<int>::iterator it_bins = startSolution.bins.begin(); it_bins != startSolution.bins.end(); it_bins++) {
                // Se o espaço na bin cabe o item e (se a bin estiver mais cheia ou for a primeira que cabe)
                if ((P.n - *it_bins) >= it_items->weight && (bestFit == startSolution.bins.end() || *it_bins > *bestFit))
                    bestFit = it_bins;
            }
            if (bestFit == startSolution.bins.end()) {  // Caso não tenha nenhuma bin que caiba o item cria uma nova
                startSolution.bins.push_back(it_items->weight);
                it_items->bin_index = std::prev(startSolution.bins.end());
            } else {  // Caso encontre o bestFit, adiciona o item a essa bin
                *bestFit += it_items->weight;
                it_items->bin_index = bestFit;
            }
        }
        return startSolution;
    }

    /*
         Fitness eq1. [Hyde(2010)]:
         Fitness = 1 - sum((fullness/capacity)²)/numbins
         AINDA NÃO É USADO PRA NADA
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
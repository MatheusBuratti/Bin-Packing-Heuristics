#pragma once
#include <algorithm>
#include <ctime>
#include <vector>

#include "greedy.cpp"
#include "problem.hpp"

class LocalSearch {
   public:
    //  Swaps baseados em Kok-HuaLoh, Bruce Golden, Edward Wasil [2006]
    static bool _swap10(Problem P, Solution &S, item A0, int B0_index) {
        return true;
    }
    static bool _swap11(Problem P, Solution &S, item A0, item B0) {
        return true;
    }
    static bool _swap12(Problem P, Solution &S, item A0, item B0, item B1) {
        return true;
    }
    static bool _swap22(Problem P, Solution &S, item A0, item A1, item B0, item B1) {
        return true;
    }

    static Solution HillDescent(Problem P, Solution startSolution) {
        // Tenta fazer swaps em todos os pares de items baseado no ganho de fitness
        // Lembrando que a ideia é minimizar fitness -> delta_fitness < 0
        return startSolution;
    }

    static Solution reconstructBins(Problem P, Solution startSolution) {
        // Pegando parte final do vetor de items de tamanho aleatório
        srand((unsigned)time(0));

        int N = (rand() % (P.n * 1 / 4)) + P.n * 3 / 4;  // vai reconstruir de N até o fim

        // Removendo os items das ultimas N bins
        std::vector<item>::iterator it_items = startSolution.items_vector.begin();
        for (it_items += N; it_items != startSolution.items_vector.end(); it_items++) {
            if (it_items->assignedBin->fullness == it_items->weight)   // Se for o último item da bin
                startSolution.bins_list.erase(it_items->assignedBin);  // Remove a bin
            else
                it_items->assignedBin->rmItem(it_items);
            it_items->assignedBin = startSolution.bins_list.end();  // Flag para item não alocado a uma bin
        }

        // Agora aplicando a estratégia de Best Fit
        it_items = startSolution.items_vector.begin();
        for (it_items += N; it_items != startSolution.items_vector.end(); it_items++) {
            std::list<bin>::iterator bestFit = startSolution.bins_list.end();
            for (std::list<bin>::iterator it_bins = startSolution.bins_list.begin(); it_bins != startSolution.bins_list.end(); it_bins++) {
                // Se o espaço na bin cabe o item e (se a bin estiver mais cheia ou for a primeira que cabe)
                if ((P.binCapacity - it_bins->fullness) >= it_items->weight && (bestFit == startSolution.bins_list.end() || it_bins->fullness > bestFit->fullness))
                    bestFit = it_bins;
            }
            if (bestFit == startSolution.bins_list.end()) {  // Caso não tenha nenhuma bin que caiba o item, cria uma nova
                startSolution.bins_list.push_back(bin(it_items));
                it_items->assignedBin = std::prev(startSolution.bins_list.end());
            } else {  // Caso encontre o bestFit, adiciona o item a essa bin
                bestFit->addItem(it_items);
                it_items->assignedBin = bestFit;
            }
        }
        return startSolution;
    }

    /*
         Fitness eq1. [Hyde(2010)]:
         Fitness = 1 - sum((fullness/capacity)²)/numbins
    */
    static int _calcFitness(Problem P, Solution S) {
        int result = 0;
        for (auto it = S.bins_list.begin(); it != S.bins_list.end(); it++) {
            result += it->fullness * it->fullness / (P.binCapacity * P.binCapacity);  // (fullness/capacity)²
        }
        result /= S.bins_list.size();  //    sum/numbins
        return (1 - result);
    }

    static int _deltaFitness(Problem P, Solution S, item A0, int B0_index) {
        return 0;
    }
    static int _deltaFitness(Problem P, Solution S, item A0, item B0) {
        return 0;
    }
    static int _deltaFitness(Problem P, Solution S, item A0, item B0, item B1) {
        return 0;
    }
    static int _deltaFitness(Problem P, Solution S, int binA, int binB) {
        return 0;
    }
};
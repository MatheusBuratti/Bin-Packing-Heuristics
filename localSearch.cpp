#pragma once
#include <math.h>

#include <algorithm>
#include <vector>

#include "problem.cpp"

class LocalSearch {
   public:
    /*static Solution reconstructBins(Problem P, Solution startSolution) {
        // Pegando parte final do vetor de items de tamanho aleatório
        srand((unsigned)time(0));

        int N = (rand() % (P.n * 1 / 10)) + P.n * 9 / 10;  // vai reconstruir de N até o fim
        std::cout << "N: " << N << std::endl;
        // Removendo os items das ultimas N bins
        std::vector<item>::iterator it_items = startSolution.items_vector.begin();
        std::advance(it_items, N);
        while (it_items != startSolution.items_vector.end()) {
            it_items->assignedBin->fullness -= (it_items)->weight;
            it_items->assignedBin->storedItems.remove(&(*it_items));
            if (it_items->assignedBin->fullness == 0)                  // Se for o último item da bin
                startSolution.bins_list.erase(it_items->assignedBin);  // Remove a bin
            it_items->assignedBin = startSolution.bins_list.end();     // Flag para item não alocado a uma bin
            it_items++;
        }

        // Agora aplicando a estratégia de Best Fit
        it_items = startSolution.items_vector.begin();
        std::advance(it_items, N);
        while (it_items != startSolution.items_vector.end()) {
            std::list<bin>::iterator bestFit = startSolution.bins_list.end();
            for (std::list<bin>::iterator it_bins = startSolution.bins_list.begin(); it_bins != startSolution.bins_list.end(); it_bins++) {
                // Se o espaço na bin cabe o item e (se a bin estiver mais cheia ou for a primeira que cabe)
                if ((P.binCapacity - it_bins->fullness) >= it_items->weight && (bestFit == startSolution.bins_list.end() || it_bins->fullness > bestFit->fullness))
                    bestFit = it_bins;
            }
            if (bestFit == startSolution.bins_list.end()) {  // Caso não tenha nenhuma bin que caiba o item, cria uma nova
                startSolution.bins_list.push_back(bin(&(*it_items)));
                it_items->assignedBin = std::prev(startSolution.bins_list.end());
            } else {  // Caso encontre o bestFit, adiciona o item a essa bin
                bestFit->storedItems.push_back(&(*it_items));
                bestFit->fullness += it_items->weight;
                it_items->assignedBin = bestFit;
            }
            it_items++;
        }
        return startSolution;
    }
    */
    static Solution HillClimb(Problem P, Solution &startSolution) {
        // Tenta fazer swaps até não ter mais ganho de fitness
        // Lembrando que a ideia é maximizar fitness -> sum(bin_load²)
        bool fitGain = true;
        while (fitGain) {
            fitGain = false;
            for (std::list<bin>::iterator alfa = startSolution.bins_list.begin(); alfa != std::prev(startSolution.bins_list.end(), 2); std::advance(alfa, 1)) {
                for (std::list<bin>::iterator beta = std::next(alfa); beta != startSolution.bins_list.end(); std::advance(beta, 1)) {
                    std::list<item *>::iterator it_itemsA = alfa->storedItems.begin();
                    while (it_itemsA != alfa->storedItems.end()) {
                        if (_deltaFitness(P, **it_itemsA, *beta)) {
                            fitGain = true;
                            alfa->fullness -= (*it_itemsA)->weight;
                            alfa->storedItems.remove(*it_itemsA);
                            beta->storedItems.push_back(*it_itemsA);
                            beta->fullness += (*it_itemsA)->weight;
                            (*it_itemsA)->assignedBin = beta;
                            it_itemsA = alfa->storedItems.begin();
                        } else {
                            std::list<item *>::iterator it_itemsB = beta->storedItems.begin();
                            while (it_itemsB != beta->storedItems.end()) {
                                if (_deltaFitness(P, **it_itemsA, **it_itemsB)) {
                                    fitGain = true;
                                    alfa->fullness -= (*it_itemsA)->weight;
                                    beta->fullness -= (*it_itemsB)->weight;
                                    alfa->storedItems.remove(*it_itemsA);
                                    beta->storedItems.remove(*it_itemsB);
                                    alfa->storedItems.push_back(*it_itemsB);
                                    beta->storedItems.push_back(*it_itemsA);
                                    alfa->fullness += (*it_itemsB)->weight;
                                    beta->fullness += (*it_itemsA)->weight;
                                    (*it_itemsA)->assignedBin = beta;
                                    (*it_itemsB)->assignedBin = alfa;
                                    it_itemsB = beta->storedItems.begin();
                                    it_itemsA = alfa->storedItems.begin();
                                } else
                                    it_itemsB++;
                            }
                            it_itemsA++;
                        }
                    }
                }
            }
        }
        startSolution.bins_list.remove_if([](bin A) { return A.fullness == 0; });
        return startSolution;
    }
};
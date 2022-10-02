#pragma once
#include <algorithm>
#include <vector>

#include "problem.hpp"
class Greedy {
   public:
    static Solution naiveFit(Problem P) {
        Solution S(P);
        for (auto it = S.item.begin(); it != S.item.end(); it++) {
            S.bins.push_back(it->weight);
            it->bin_index = std::prev(S.bins.end());
        }
        return S;
    }

    static Solution simpleFit(Problem P) {
        Solution S(P);

        std::vector<ItemSolution>::iterator it_items = S.item.begin();
        S.bins.push_back(it_items->weight);
        it_items->bin_index = std::prev(S.bins.end());
        for (it_items++; it_items != S.item.end(); it_items++) {
            if (it_items->weight > (P.binCapacity - S.bins.back()))
                S.bins.push_back(it_items->weight);
            else
                S.bins.back() += (it_items->weight);
            it_items->bin_index = std::prev(S.bins.end());
        }
        return S;
    }

    static Solution
    nextFitDecreasing(Problem P) {
        Solution S(P);

        // Sort decrescente dos items
        std::sort(S.item.begin(), S.item.end(), greaterItemSolution());

        std::vector<ItemSolution>::iterator it_items;
        for (it_items = S.item.begin(); it_items != S.item.end(); it_items++) {
            if (it_items->bin_index == S.bins.end()) {  // Item não associado a uma bin

                S.bins.push_back(it_items->weight);  // Abre uma bin nova
                it_items->bin_index = std::prev(S.bins.end());

                // Parte onde procura o próximo item que cabe no restante da bin
                int freeSpace = P.binCapacity - S.bins.back();
                std::vector<ItemSolution>::iterator it_nextFit;
                it_nextFit = std::lower_bound(it_items, S.item.end(), freeSpace, [](ItemSolution A, int B) { return A.weight > B; });

                while (it_nextFit != S.item.end()) {  // Procura repetidamente caso apenas um item não tenha completado a bin

                    // Item já associado a uma bin
                    if (it_nextFit->bin_index != S.bins.end())
                        it_nextFit++;

                    // Item não associado a uma bin
                    else {
                        S.bins.back() += it_nextFit->weight;
                        freeSpace -= it_nextFit->weight;
                        it_nextFit->bin_index = std::prev(S.bins.end());  // Associa o item à bin atual
                        it_nextFit++;
                        it_nextFit = std::lower_bound(it_nextFit, S.item.end(), freeSpace, [](ItemSolution A, int B) { return A.weight > B; });
                    }
                }
            }
        }
        return S;
    }
};

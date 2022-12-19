#pragma once
#include <algorithm>
#include <vector>

#include "problem.cpp"

class Greedy {
   public:
    static Solution nextFit(Problem P) {
        Solution S(P);
        std::vector<item>::iterator it_items = S.items_vector.begin();
        S.bins_list.push_back(bin(&(*it_items)));
        it_items->assignedBin = std::prev(S.bins_list.end());
        for (std::advance(it_items, 1); it_items != S.items_vector.end(); it_items++) {
            if (it_items->weight > (P.binCapacity - S.bins_list.back().fullness)) {
                S.bins_list.push_back(bin(&*(it_items)));
                it_items->assignedBin = std::prev(S.bins_list.end());
            } else {
                S.bins_list.back().storedItems.push_back(&(*it_items));
                S.bins_list.back().fullness += it_items->weight;
                it_items->assignedBin = std::prev(S.bins_list.end());
            }
        }
        return S;
    }

    static Solution nextFitDecreasing(Problem P) {
        Solution S(P);

        // Sort decrescente dos items
        std::sort(S.items_vector.begin(), S.items_vector.end(), [](item A, item B) { return A.weight > B.weight; });

        std::vector<item>::iterator it_items;
        for (it_items = S.items_vector.begin(); it_items != S.items_vector.end(); it_items++) {
            if (it_items->assignedBin == S.bins_list.end()) {  // Item não associado a uma bin

                S.bins_list.push_back(bin(&(*it_items)));  // Abre uma bin nova
                it_items->assignedBin = std::prev(S.bins_list.end());

                // Parte onde procura o próximo items_vector que cabe no restante da bin
                int freeSpace = P.binCapacity - S.bins_list.back().fullness;
                std::vector<item>::iterator it_nextFit;
                it_nextFit = std::lower_bound(it_items, S.items_vector.end(), freeSpace, [](item A, int B) { return A.weight > B; });

                while (it_nextFit != S.items_vector.end()) {  // Procura repetidamente caso apenas um items_vector não tenha completado a bin

                    // Item já associado a uma bin
                    if (it_nextFit->assignedBin != S.bins_list.end())
                        it_nextFit++;
                    // Item não associado a uma bin
                    else {
                        S.bins_list.back().storedItems.push_back(&(*it_nextFit));
                        S.bins_list.back().fullness += it_nextFit->weight;
                        freeSpace -= it_nextFit->weight;
                        it_nextFit->assignedBin = std::prev(S.bins_list.end());  // Associa o items_vector à bin atual
                        it_nextFit = std::lower_bound(++it_nextFit, S.items_vector.end(), freeSpace, [](item A, int B) { return A.weight > B; });
                    }
                }
            }
        }
        return S;
    }
};

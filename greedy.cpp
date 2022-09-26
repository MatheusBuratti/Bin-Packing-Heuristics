#include <algorithm>
#include <list>
#include <vector>

#include "problem.hpp"
class GreedySolver {
   public:
    static Solution nextFitDecreasing(Problem P) {                       // P.items deve estar ordenado
        std::sort(P.items.begin(), P.items.end(), std::greater<int>());  // Decreasing sort
        Solution S;
        std::fill_n(S.bins_index.begin(), P.n, -1);  // -1 vai servir como flag para item que não foi colocado em nenhuma bin

        std::vector<int>::iterator it_items;
        for (it_items = P.items.begin(); it_items != P.items.end(); it_items++) {
            S.bins.push_back(*it_items);
            S.bins_index.at((it_items - P.items.begin())) = (S.bins.end() - 1 - S.bins.begin());

            int freeSpace = P.binCapacity - *(S.bins.end() - 1);
            std::vector<int>::iterator it_nextFit = std::lower_bound(it_items, P.items.end(), freeSpace, std::greater<int>());
            while (it_nextFit != P.items.end()) {
                if (S.bins_index.at(it_nextFit - P.items.begin()) != -1)  // Item já associado a uma bin
                    it_nextFit++;
                else {
                    *(S.bins.end() - 1) += *it_nextFit;
                    freeSpace -= *it_nextFit;
                    S.bins_index.at(it_nextFit - P.items.begin()) = S.bins.end() - 1 - S.bins.begin();  // Associa o item à bin atual
                    it_nextFit = std::lower_bound(it_nextFit + 1, P.items.end(), freeSpace, std::greater<int>());
                }
            }
        }
        return S;
    }
};

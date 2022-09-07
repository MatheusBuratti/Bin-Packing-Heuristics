#include <algorithm>
#include <vector>

#include "problem.h"

std::vector<int> greedySolver(Problem P){
    std::sort(P.items, P.items+P.n, [](int a, int b){return a > b;});
    std::vector<int> bins;
    int itemIterL = 0, itemIterR = P.n-1, binIter = 0;
    while(itemIterL <= itemIterR){
        bins.push_back(P.items[itemIterL++]);
        while(itemIterL <= itemIterR && bins[binIter]+P.items[itemIterL] <= P.binCapacity)
            bins[binIter] += P.items[itemIterL++];
        while(itemIterL <= itemIterR && bins[binIter]+P.items[itemIterR] <= P.binCapacity)
            bins[binIter] += P.items[itemIterR--];
        binIter++;
    }
    return bins;
}
#include <string>
#include <vector>

#ifndef PROBLEMH
#define PROBLEMH

typedef struct Problem{
    std::string identifier;
    int binCapacity;
    int n;
    int bestSolution;
    std::vector<int> items;
}Problem;

#endif // !PROBLEMH

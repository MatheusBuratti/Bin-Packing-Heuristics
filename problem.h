#include <string>

#ifndef PROBLEMH
#define PROBLEMH

typedef struct Problem{
    std::string identifier;
    int binCapacity;
    int n;
    int bestSolution;
    int *items;
}Problem;

#endif // !PROBLEMH

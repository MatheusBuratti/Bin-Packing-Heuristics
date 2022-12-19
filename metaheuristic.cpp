#pragma once

#include <algorithm>
#include <vector>

#include "problem.cpp"

class Metaheuristics {
   public:
    static Solution WeightAnnealing(Problem P, Solution &startSolution) {
        double scaling = 0.005, T = 1, Tred = 0.5;  // Hiperparmetros
        int TTL = 10;
        int adv = 1;
        for (int i = 0; i < TTL; i++) {
            for (std::list<bin>::iterator alfa = startSolution.bins_list.begin(); alfa != std::prev(startSolution.bins_list.end(), 2); std::advance(alfa, adv)) {
                adv = 1;
                double tempA = pow((1 + scaling * (P.binCapacity - alfa->fullness)), T);
                for (std::list<bin>::iterator beta = std::next(alfa); beta != startSolution.bins_list.end(); std::advance(beta, 1)) {
                    double tempB = pow((1 + scaling * (P.binCapacity - beta->fullness)), T);
                    std::list<item *>::iterator it_itemsA = alfa->storedItems.begin();
                    bool swap = false;
                    while (it_itemsA != alfa->storedItems.end() && !swap) {
                        (*it_itemsA)->assignedBin = alfa;
                        if (_deltaFitness(P, **it_itemsA, *beta, tempA)) {
                            alfa->fullness -= (*it_itemsA)->weight;
                            alfa->storedItems.remove(*it_itemsA);
                            beta->storedItems.push_back(*it_itemsA);
                            beta->fullness += (*it_itemsA)->weight;
                            (*it_itemsA)->assignedBin = beta;
                            if (alfa->fullness == 0) {
                                alfa = startSolution.bins_list.erase(alfa);
                                adv = 0;
                            }
                            swap = true;
                            it_itemsA = alfa->storedItems.begin();
                        } else {
                            std::list<item *>::iterator it_itemsB = beta->storedItems.begin();
                            while (it_itemsB != beta->storedItems.end() && !swap) {
                                (*it_itemsB)->assignedBin = beta;
                                if (_deltaFitness(P, **it_itemsA, **it_itemsB, tempA, tempB)) {
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
                                    swap = true;
                                }
                                it_itemsB++;
                            }
                            it_itemsA++;
                        }
                    }
                }
            }
            T *= Tred;
            startSolution.bins_list.remove_if([](bin A) { return A.fullness == 0; });
        }
        return startSolution;
    }
};
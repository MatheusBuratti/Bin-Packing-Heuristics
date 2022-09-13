#include <algorithm>
#include <vector>
#include <list>

#include "problem.h"

std::vector<int> fastGreedySolver(Problem P){
    std::vector<int> bins;
    int itemIterL = 0, itemIterR = P.n-1, binIter = 0;
    // 3 indíces para iterar:
    //      itemIterL: começa no início de items
    //      itemIterR: começa no fim de items
    //      binIter: itera pelo vetor de bins conforme ele vai sendo "criado"
    while(itemIterL <= itemIterR){
        bins.push_back(P.items[itemIterL++]); // "Cria" uma nova bin no fim do vetor
        while(itemIterL <= itemIterR && bins[binIter]+P.items[itemIterL] <= P.binCapacity)
            bins[binIter] += P.items[itemIterL++];
            // Enquanto houverem itens na esquerda (ou seja, itens grandes) que cabem vai colocando
        while(itemIterL <= itemIterR && bins[binIter]+P.items[itemIterR] <= P.binCapacity)
            // Agora olha os itens do final do vetor para completar, se possível
            bins[binIter] += P.items[itemIterR--];
        binIter++;
    }
    return bins;
}

std::vector<int> searchGreedySolver(Problem P){
    std::list<int> Items(P.items.begin(),P.items.end());
    std::vector<int> bins;
    while(Items.size() > 0){
        bins.push_back(*Items.begin()); // "Cria" uma nova bin no fim do vetor e adiciona o primeiro item da lista
        int freeSpace = P.binCapacity - *Items.begin(); // Resto de espaço na bin depois de adicionar o primeiro item
        Items.erase(Items.begin()); // Remove o primeiro item

        std::list<int>::iterator it = std::upper_bound(Items.begin(), Items.end(), freeSpace, std::greater<int>());
        // Procura o próximo item com tamanho <= ao espaço sobrando na bin
        
        while(*it <= freeSpace && it != Items.end()){
            *(bins.end()-1) += *it;
            freeSpace -= *it;
            it = Items.erase(it);
            if(it != Items.end())
                it = std::upper_bound(it, Items.end(), freeSpace, std::greater<int>());
        }
    }
    return bins;
}

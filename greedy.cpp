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
    std::list<int> Items(P.items.begin(),P.items.end()); // Copia do vetor de items em uma lista
    std::vector<int> bins; // Vetor de bins
    while(Items.size() > 0){
        bins.push_back(*Items.begin()); // "Cria" uma nova bin no fim do vetor e adiciona o primeiro item da lista
        int freeSpace = P.binCapacity - *Items.begin(); // Resto de espaço na bin depois de adicionar o primeiro item
        Items.pop_front(); // Remove o primeiro item

        std::list<int>::iterator it; // Próximo item com tamanho <= ao espaço sobrando na bin
        it = std::upper_bound(Items.begin(), Items.end(), freeSpace, std::greater<int>());
        // Upper_bound é uma busca sequencial e não binária nesse caso por causa da estrutura escolhida ser do 
        // tipo list, porém essa desvantagem é compensada por causa das remoções dos items ser O(1).
        
        while(*it <= freeSpace && it != Items.end()){
            *(bins.end()-1) += *it; // Adiciona à última bin o maior valor encontrado que cabe.
            freeSpace -= *it;
            it = Items.erase(it); // Remove da lista o item e retorna o próximo
            if(it != Items.end()) // se o próximo não for o fim, busca por mais para continuar preenchendo o espaço restante
                it = std::upper_bound(it, Items.end(), freeSpace, std::greater<int>());
        }
    }
    return bins;
}

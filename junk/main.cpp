#include <iostream>
#include <string>   // para o uso de strings
using namespace std;

void arvoreAnalise(string str) {
    std::cout << "\tImplementar arvoreAnalise()" + str << std::endl;
}

void analisadorLL(string str) {
    std::cout << "\tImplementar analisadorLL()" + str << std::endl;
}

int main() {
    std::cout << "Main" << std::endl;
    string exemploA("aaba");

    // Arvore de Analise
    arvoreAnalise(exemploA);
    
    // Analisador LL
    analisadorLL(exemploA);

    return 0;
}

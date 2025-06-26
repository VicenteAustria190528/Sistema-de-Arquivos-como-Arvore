// ============================================================================
// Arquivo: nodo.hpp
// Finalidade: Definir a estrutura de dados que representa cada nó da árvore,
//             seja ele um arquivo ou um diretório.
// ============================================================================
#ifndef NODO_HPP
#define NODO_HPP

#include <string>                      // Para manipulação de nomes e caminhos
#include <vector>                      // Para armazenar múltiplos filhos
#include <memory>                      // Para uso de ponteiros inteligentes (shared_ptr)

// ============================================================================
// Estrutura: Nodo
// Objetivo: Representa um nó da árvore de arquivos e pastas.
// ============================================================================
struct Nodo {
    std::string caminho;  // Caminho completo (absoluto ou relativo) do arquivo/pasta
    std::string nome;     // Nome simples do arquivo ou diretório (sem o caminho)
    std::string tipo;     // Tipo do nó: "arquivo" ou "pasta"
    uintmax_t tamanho;    // Tamanho em bytes. Se for pasta, soma dos tamanhos dos filhos

    // Vetor de ponteiros para os filhos deste nó (apenas se o nó for uma pasta)
    std::vector<std::shared_ptr<Nodo>> filhos;
};

#endif // NODO_HPP

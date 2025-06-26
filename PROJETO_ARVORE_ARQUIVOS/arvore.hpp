// ============================================================================
// Arquivo: arvore.hpp
// Finalidade: Declarar as funções responsáveis por construir a árvore de
//             diretórios e arquivos e exibir sua estrutura hierárquica.
// ============================================================================
#ifndef ARVORE_HPP
#define ARVORE_HPP

#include <memory>                     // Para std::shared_ptr
#include <filesystem>                 // Para std::filesystem::path
#include "nodo.hpp"                   // Estrutura de dados Nodo

// ============================================================================
// Função: construirArvore
// Objetivo: Percorre o sistema de arquivos a partir de um caminho fornecido
//           e constrói recursivamente uma árvore representando a hierarquia.
// Entrada: Caminho inicial (std::filesystem::path)
// Saída:   Ponteiro para o nó raiz da árvore construída (std::shared_ptr<Nodo>)
// ============================================================================
std::shared_ptr<Nodo> construirArvore(const std::filesystem::path& caminho);

// ============================================================================
// Função: exibirArvore
// Objetivo: Exibe no terminal a árvore de diretórios/arquivos com indentação.
// Entrada: Ponteiro para o nó raiz da árvore (Nodo) e nível de indentação (int)
// ============================================================================
void exibirArvore(const std::shared_ptr<Nodo>& nodo, int nivel = 0);

#endif // ARVORE_HPP

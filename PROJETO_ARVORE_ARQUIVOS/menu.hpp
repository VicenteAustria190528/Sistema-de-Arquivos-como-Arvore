// ============================================================================
// Arquivo: menu.hpp
// Finalidade: Declara a função do menu principal interativo que permite ao
//             usuário interagir com as funcionalidades da árvore de arquivos.
// ============================================================================
#ifndef MENU_HPP
#define MENU_HPP

#include <memory>       // Para std::shared_ptr
#include "nodo.hpp"     // Estrutura de nó da árvore (Nodo)

// ============================================================================
// Função: menuInterativo
// Objetivo: Exibir um menu interativo no terminal com opções para o usuário.
// Entrada: Ponteiro para o nó raiz da árvore de arquivos
// ============================================================================
void menuInterativo(const std::shared_ptr<Nodo>& raiz);

#endif // MENU_HPP

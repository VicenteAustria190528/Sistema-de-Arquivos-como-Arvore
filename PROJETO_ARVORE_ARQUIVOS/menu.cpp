// ============================================================================
// Arquivo: menu.cpp
// Finalidade: Implementa o menu interativo principal do programa.
//            Permite ao usuário interagir com a árvore carregada, visualizar,
//            exportar e realizar pesquisas.
// ============================================================================

#include "menu.hpp"            // Declara menuInterativo()
#include "arvore.hpp"          // Declara construirArvore(), exibirArvore()
#include "pesquisas.hpp"       // Declara menuPesquisas()
#include "html_export.hpp"     // Declara exportarParaHTML()
#include <iostream>            // Para std::cin, std::cout

// ============================================================================
// Função: menuInterativo
// Objetivo: Exibir opções ao usuário e redirecionar para as funcionalidades.
// Entrada: Ponteiro para a raiz da árvore (construída previamente).
// ============================================================================
void menuInterativo(const std::shared_ptr<Nodo>& raiz) {
    int opcao = -1;

    do {
        std::cout << "\n========== MENU PRINCIPAL ==========\n";
        std::cout << "1. Exibir a árvore completa\n";
        std::cout << "2. Exportar árvore para HTML\n";
        std::cout << "3. Pesquisas\n";
        std::cout << "0. Sair\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opcao;

        switch (opcao) {
            case 1:
                std::cout << "\n--- Árvore do sistema de arquivos ---\n";
                exibirArvore(raiz);
                break;

            case 2:
                // Gera o arquivo "arvore.html" na pasta atual
                exportarParaHTML(raiz, "arvore.html");
                break;

            case 3:
                menuPesquisas(raiz);
                break;

            case 0:
                std::cout << "Encerrando o programa.\n";
                break;

            default:
                std::cout << "Opção inválida. Tente novamente.\n";
        }
    } while (opcao != 0);
}

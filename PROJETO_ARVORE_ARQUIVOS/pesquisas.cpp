// ============================================================================
// Arquivo: pesquisas.hpp
// Finalidade: Declaração das funções para executar buscas na árvore de arquivos
// e apresentar ao usuário os resultados de acordo com critérios como maior arquivo,
// arquivos acima de um determinado tamanho, etc.
// ============================================================================
#ifndef PESQUISAS_HPP
#define PESQUISAS_HPP

#include <memory>
#include "nodo.hpp"

// ============================================================================
// Função: menuPesquisas
// Objetivo: Exibir um menu de opções de pesquisa para o usuário, receber
//          parâmetros (quando necessário) e chamar as funções de busca
//          correspondentes.
// Entrada: Ponteiro para o nó raiz da árvore de arquivos.
// ============================================================================
void menuPesquisas(const std::shared_ptr<Nodo>& raiz);

#endif // PESQUISAS_HPP



// ============================================================================
// Arquivo: pesquisas.cpp
// Finalidade: Implementação das funções de busca na árvore de arquivos,
//            como encontrar o(s) maior(es) arquivo(s), arquivos maiores que
//            um tamanho N, pasta com mais filhos, arquivos por extensão,
//            e pastas vazias.
// ============================================================================
#include "pesquisas.hpp"
#include <iostream>
#include <vector>
#include <algorithm>
#include <filesystem>

namespace fs = std::filesystem;

// ----------------------------------------------------------------------------
// Função auxiliar: recolhe todos os nós de arquivos na árvore
// ----------------------------------------------------------------------------
static void coletarArquivos(const std::shared_ptr<Nodo>& nodo,
                             std::vector<std::shared_ptr<Nodo>>& arquivos) {
    if (!nodo) return;
    if (nodo->tipo == "arquivo") {
        arquivos.push_back(nodo);
    } else {
        for (const auto& filho : nodo->filhos) {
            coletarArquivos(filho, arquivos);
        }
    }
}

// ----------------------------------------------------------------------------
// Função auxiliar: recolhe todas as pastas na árvore
// ----------------------------------------------------------------------------
static void coletarPastas(const std::shared_ptr<Nodo>& nodo,
                           std::vector<std::shared_ptr<Nodo>>& pastas) {
    if (!nodo) return;
    if (nodo->tipo == "pasta") {
        pastas.push_back(nodo);
        for (const auto& filho : nodo->filhos) {
            coletarPastas(filho, pastas);
        }
    }
}

// ----------------------------------------------------------------------------
// 1. Maior(es) arquivo(s)
// ----------------------------------------------------------------------------
static void buscarMaiorArquivo(const std::shared_ptr<Nodo>& raiz) {
    std::vector<std::shared_ptr<Nodo>> arquivos;
    coletarArquivos(raiz, arquivos);
    if (arquivos.empty()) {
        std::cout << "Nenhum arquivo encontrado.\n";
        return;
    }
    // Encontra o tamanho máximo
    uintmax_t maxTam = 0;
    for (const auto& a : arquivos) {
        if (a->tamanho > maxTam) maxTam = a->tamanho;
    }
    // Lista todos com tamanho == maxTam
    std::cout << "Maior(es) arquivo(s):\n";
    for (const auto& a : arquivos) {
        if (a->tamanho == maxTam) {
            std::cout << a->caminho << " (" << a->tamanho << " bytes)\n";
        }
    }
}

// ----------------------------------------------------------------------------
// 2. Arquivos com mais do que N bytes
// ----------------------------------------------------------------------------
static void buscarArquivosMaiorQue(const std::shared_ptr<Nodo>& raiz) {
    std::cout << "Informe o valor de N (bytes): ";
    uintmax_t N;
    std::cin >> N;
    std::vector<std::shared_ptr<Nodo>> arquivos;
    coletarArquivos(raiz, arquivos);
    std::cout << "Arquivos com mais do que N bytes (N=" << N << "):\n";
    for (const auto& a : arquivos) {
        if (a->tamanho > N) {
            std::cout << a->caminho << " (" << a->tamanho << " bytes)\n";
        }
    }
}

// ----------------------------------------------------------------------------
// 3. Pasta com mais filhos diretos
// ----------------------------------------------------------------------------
static void buscarPastaMaisArquivos(const std::shared_ptr<Nodo>& raiz) {
    std::vector<std::shared_ptr<Nodo>> pastas;
    coletarPastas(raiz, pastas);
    if (pastas.empty()) {
        std::cout << "Nenhuma pasta encontrada.\n";
        return;
    }
    // Encontra o número máximo de filhos
    size_t maxFilhos = 0;
    for (const auto& p : pastas) {
        if (p->filhos.size() > maxFilhos) maxFilhos = p->filhos.size();
    }
    // Lista todas as pastas com filhos == maxFilhos
    std::cout << "Pasta(s) com mais arquivos diretos:\n";
    for (const auto& p : pastas) {
        if (p->filhos.size() == maxFilhos) {
            std::cout << p->caminho << " (" << p->filhos.size() << " filhos, "
                      << p->tamanho << " bytes)\n";
        }
    }
}

// ----------------------------------------------------------------------------
// 4. Arquivos por extensão
// ----------------------------------------------------------------------------
static void buscarArquivosPorExtensao(const std::shared_ptr<Nodo>& raiz) {
    std::cout << "Informe a extensão (ex: .txt): ";
    std::string ext;
    std::cin >> ext;
    std::vector<std::shared_ptr<Nodo>> arquivos;
    coletarArquivos(raiz, arquivos);
    std::cout << "Arquivos por extensão (" << ext << "):\n";
    for (const auto& a : arquivos) {
        if (fs::path(a->caminho).extension() == ext) {
            std::cout << a->caminho << " (" << a->tamanho << " bytes)\n";
        }
    }
}

// ----------------------------------------------------------------------------
// 5. Pastas vazias
// ----------------------------------------------------------------------------
static void buscarPastasVazias(const std::shared_ptr<Nodo>& raiz) {
    std::vector<std::shared_ptr<Nodo>> pastas;
    coletarPastas(raiz, pastas);
    std::cout << "Pastas vazias:\n";
    for (const auto& p : pastas) {
        if (p->filhos.empty()) {
            std::cout << p->caminho << "\n";
        }
    }
}

// ----------------------------------------------------------------------------
// Função: menuPesquisas
// Descrição: Exibe o submenu de pesquisas e chama cada função de busca.
// ----------------------------------------------------------------------------
void menuPesquisas(const std::shared_ptr<Nodo>& raiz) {
    int opc;
    do {
        std::cout << "\n--- MENU DE PESQUISAS ---\n";
        std::cout << "1. Maior(es) arquivo(s)\n";
        std::cout << "2. Arquivos com mais do que N bytes\n";
        std::cout << "3. Pasta com mais arquivos diretos\n";
        std::cout << "4. Arquivos por extensão\n";
        std::cout << "5. Pastas vazias\n";
        std::cout << "0. Voltar\n";
        std::cout << "Escolha uma opção: ";
        std::cin >> opc;

        switch (opc) {
            case 1: buscarMaiorArquivo(raiz); break;
            case 2: buscarArquivosMaiorQue(raiz); break;
            case 3: buscarPastaMaisArquivos(raiz); break;
            case 4: buscarArquivosPorExtensao(raiz); break;
            case 5: buscarPastasVazias(raiz); break;
            case 0: std::cout << "Retornando ao menu principal...\n"; break;
            default: std::cout << "Opção inválida! Tente novamente.\n";
        }
    } while (opc != 0);
}

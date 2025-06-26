// ============================================================================
// Arquivo: arvore.cpp
// Finalidade: Implementa as funções responsáveis por construir e exibir
//             a árvore de diretórios e arquivos.
// ============================================================================

#include "arvore.hpp"           // Protótipos das funções e definição de Nodo
#include <iostream>             // Para saída no terminal (std::cout)
#include <filesystem>           // Para leitura do sistema de arquivos

namespace fs = std::filesystem; // Alias para facilitar a escrita

// ============================================================================
// Função: construirArvore
// Objetivo: Construir recursivamente uma árvore de diretórios/arquivos
// Entrada: Caminho inicial (std::filesystem::path)
// Retorno: Ponteiro para o nó da árvore correspondente ao caminho
// ============================================================================
std::shared_ptr<Nodo> construirArvore(const fs::path& caminho) {
    // Ignora links simbólicos e caminhos inexistentes
    if (!fs::exists(caminho) || fs::is_symlink(caminho))
        return nullptr;

    // Cria um novo nó para o caminho atual
    auto nodo = std::make_shared<Nodo>();
    nodo->caminho = caminho.string();
    nodo->nome = caminho.filename().string();
    nodo->tamanho = 0;

    if (fs::is_regular_file(caminho)) {
        // Caso seja um arquivo comum
        nodo->tipo = "arquivo";
        nodo->tamanho = fs::file_size(caminho);
    }
    else if (fs::is_directory(caminho)) {
        // Caso seja um diretório
        nodo->tipo = "pasta";
        for (const auto& entry : fs::directory_iterator(caminho)) {
            // Chamada recursiva para construir os filhos
            auto filho = construirArvore(entry.path());
            if (filho) {
                nodo->filhos.push_back(filho);
                nodo->tamanho += filho->tamanho; // Soma os tamanhos dos filhos
            }
        }
    } else {
        // Ignora outros tipos (dispositivos, sockets, etc.)
        return nullptr;
    }

    return nodo;
}

// ============================================================================
// Função: exibirArvore
// Objetivo: Exibir a árvore de arquivos no terminal com indentação hierárquica
// Entrada: Nodo atual (raiz ou subdiretório), nível de indentação (inicialmente 0)
// ============================================================================
void exibirArvore(const std::shared_ptr<Nodo>& nodo, int nivel) {
    if (!nodo) return;

    // Gera o prefixo de indentação de acordo com o nível
    std::string prefixo(nivel * 4, ' '); // 4 espaços por nível

    if (nodo->tipo == "arquivo") {
        // Imprime informações do arquivo
        std::cout << prefixo << "├── " << nodo->nome
                  << " (" << nodo->tamanho << " bytes)" << std::endl;
    } else {
        // Imprime informações do diretório
        std::cout << prefixo << "├── " << nodo->nome
                  << " (" << nodo->filhos.size() << " filhos, "
                  << nodo->tamanho << " bytes)" << std::endl;

        // Imprime recursivamente os filhos com maior indentação
        for (const auto& filho : nodo->filhos) {
            exibirArvore(filho, nivel + 1);
        }
    }
}

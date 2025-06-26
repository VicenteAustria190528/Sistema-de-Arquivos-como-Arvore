// ============================================================================
// Arquivo: html_export.cpp
// Finalidade: Implementação da exportação da árvore de arquivos em formato HTML.
// ============================================================================
#include "html_export.hpp"
#include <fstream>
#include <iostream>
#include <filesystem>

namespace fs = std::filesystem;

// Função recursiva que escreve no HTML a árvore, mantendo indentação
static void escreverHtml(const std::shared_ptr<Nodo>& nodo,
                         std::ofstream& out,
                         int nivel) {
    if (!nodo) return;
    // cria indentação com espaços
    std::string prefixo(nivel * 4, ' ');
    if (nodo->tipo == "arquivo") {
        out << prefixo
            << "├── " << nodo->nome << " (" << nodo->tamanho << " bytes)\n";
    } else {
        out << prefixo
            << "├── " << nodo->nome
            << " (" << nodo->filhos.size() << " filhos, "
            << nodo->tamanho << " bytes)\n";
        for (auto& filho : nodo->filhos) {
            escreverHtml(filho, out, nivel + 1);
        }
    }
}

void exportarParaHTML(const std::shared_ptr<Nodo>& raiz, const std::string& nomeArquivo) {
    std::ofstream out(nomeArquivo);
    if (!out) {
        std::cerr << "[ERRO] Não foi possível criar o arquivo: " << nomeArquivo << "\n";
        return;
    }

    out << "<!DOCTYPE html>\n<html lang=\"pt-BR\">\n<head>\n"
        << "  <meta charset=\"UTF-8\">\n"
        << "  <title>Árvore de Arquivos</title>\n"
        << "</head>\n<body>\n"
        << "<pre>\n";

    escreverHtml(raiz, out, 0);

    out << "</pre>\n</body>\n</html>\n";
    out.close();

    std::cout << "[OK] Arquivo HTML gerado: " << nomeArquivo << "\n";
}

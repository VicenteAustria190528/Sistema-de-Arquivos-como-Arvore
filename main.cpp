#include <iostream>          // Biblioteca padrão para entrada e saída de dados (ex: cout)
#include <filesystem>        // Biblioteca para manipulação de arquivos e diretórios
#include <vector>            // Biblioteca para utilização de vetores dinâmicos (armazenar filhos)
#include <memory>            // Biblioteca para gerenciamento de ponteiros inteligentes (shared_ptr)

namespace fs = std::filesystem;  // Alias para facilitar o uso da biblioteca filesystem

// --------------------------------------------------
// Estrutura que representa um nó da árvore de arquivos
// --------------------------------------------------
struct Nodo {
    std::string caminho;                     // Caminho absoluto do arquivo ou diretório
    std::string nome;                        // Nome do arquivo ou diretório
    std::string tipo;                        // "arquivo" ou "pasta"
    uintmax_t tamanho;                       // Tamanho em bytes (diretório soma dos arquivos filhos)
    std::vector<std::shared_ptr<Nodo>> filhos;  // Vetor de filhos (somente se for diretório)
};

// ----------------------------------------------------------------------
// Função recursiva que constrói a árvore de arquivos a partir de um caminho
// ----------------------------------------------------------------------
std::shared_ptr<Nodo> construirArvore(const fs::path& caminho) {
    // Ignora caminhos inválidos ou links simbólicos (requisitos do projeto)
    if (!fs::exists(caminho) || fs::is_symlink(caminho)) return nullptr;

    // Criação do nó atual
    auto nodo = std::make_shared<Nodo>();
    nodo->caminho = caminho.string();
    nodo->nome = caminho.filename().string();
    nodo->tamanho = 0;

    // Caso seja um arquivo comum
    if (fs::is_regular_file(caminho)) {
        nodo->tipo = "arquivo";
        nodo->tamanho = fs::file_size(caminho);  // Obtém o tamanho em bytes
    }
    // Caso seja um diretório
    else if (fs::is_directory(caminho)) {
        nodo->tipo = "pasta";
        // Itera sobre os elementos do diretório
        for (const auto& entry : fs::directory_iterator(caminho)) {
            auto filho = construirArvore(entry.path());  // Chamada recursiva
            if (filho) {
                nodo->filhos.push_back(filho);            // Adiciona o filho ao vetor
                nodo->tamanho += filho->tamanho;          // Soma o tamanho de todos os filhos
            }
        }
    }
    else {
        // Ignora outros tipos como dispositivos ou sockets
        return nullptr;
    }

    return nodo;  // Retorna o ponteiro do nó construído
}

// ----------------------------------------------------------------
// Função que exibe a árvore com indentação para representar hierarquia
// ----------------------------------------------------------------
void exibirArvore(const std::shared_ptr<Nodo>& nodo, int nivel = 0) {
    if (!nodo) return;

    std::string prefixo(nivel * 4, ' ');  // Cria indentação com 4 espaços por nível

    if (nodo->tipo == "arquivo") {
        std::cout << prefixo << "├── " << nodo->nome
                  << " (" << nodo->tamanho << " bytes)" << std::endl;
    } else {
        std::cout << prefixo << "├── " << nodo->nome
                  << " (" << nodo->filhos.size() << " filhos, "
                  << nodo->tamanho << " bytes)" << std::endl;
        for (const auto& filho : nodo->filhos) {
            exibirArvore(filho, nivel + 1);  // Exibe os filhos com nível de indentação maior
        }
    }
}

// ------------------------------------------------------------
// Função principal: ponto de entrada do programa
// ------------------------------------------------------------
int main(int argc, char* argv[]) {
    // Define o caminho inicial a partir do argumento da linha de comando,
    // ou usa o diretório atual caso nenhum argumento seja passado
    fs::path caminho = (argc > 1) ? fs::path(argv[1]) : fs::current_path();

    // Constrói a árvore a partir do caminho inicial
    auto raiz = construirArvore(caminho);

    // Exibe a árvore construída no terminal
    exibirArvore(raiz);

    return 0;
}

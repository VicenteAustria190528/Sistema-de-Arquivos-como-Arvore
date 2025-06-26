// ============================================================================
// Arquivo: main.cpp
// Finalidade: Determinar o diretório raiz (por argumento ou via CWD),
//             carregar a estrutura em árvore e iniciar o menu.
// ============================================================================

#include <iostream>            // std::cout, std::cerr, std::endl
#include <filesystem>          // std::filesystem::path, exists, is_directory, current_path
#include "nodo.hpp"            // Estrutura Nodo (caminho, nome, tipo, tamanho, filhos)
#include "arvore.hpp"          // construirArvore(), exibirArvore()
#include "menu.hpp"            // menuInterativo()

namespace fs = std::filesystem; // Alias para facilitar o uso de filesystem

int main(int argc, char* argv[]) {
    // ------------------------------------------------------------------------
    // 1) Definir o diretório a ser carregado:
    //    - Usa argv[1] se fornecido.
    //    - Caso contrário, usa o diretório de trabalho atual + "esquema de pastas".
    // ------------------------------------------------------------------------
    fs::path esquemaDir = (argc > 1)
        ? fs::path(argv[1])
        : fs::current_path() / "esquema de pastas";

    // ------------------------------------------------------------------------
    // 2) Validação: checa se o caminho existe e é um diretório
    // ------------------------------------------------------------------------
    std::error_code ec;
    if (!fs::exists(esquemaDir, ec) || !fs::is_directory(esquemaDir, ec)) {
        std::cerr << "[ERRO] Diretório inválido: " << esquemaDir << std::endl;
        return 1;
    }

    // ------------------------------------------------------------------------
    // 3) Construir a árvore de arquivos em memória
    // ------------------------------------------------------------------------
    auto raiz = construirArvore(esquemaDir);

    // ------------------------------------------------------------------------
    // 4) Chamar o menu interativo, passando a árvore carregada
    // ------------------------------------------------------------------------
    menuInterativo(raiz);

    return 0;  // Fim do programa
}

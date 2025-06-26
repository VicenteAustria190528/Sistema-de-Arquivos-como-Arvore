# Sistema de Arquivos como Árvore

## Descrição do Projeto

Este projeto implementa um gerenciador de sistema de arquivos que carrega a estrutura real de diretórios e arquivos em memória, organizando-a como uma árvore genérica (n-ária). O usuário pode navegar por essa árvore, exportá-la para um arquivo HTML e realizar diversas pesquisas sobre arquivos e pastas. O código-fonte está completamente comentado para facilitar compreensão e manutenção.

**Funcionalidades obrigatórias:**

1. Carregamento inicial da árvore a partir de um diretório (argumento de linha de comando ou CWD + “esquema de pastas”).
2. Exibição interativa da árvore com detalhes:

   * Nome, tipo (arquivo ou pasta) e tamanho em bytes.
   * Para pastas: número de filhos diretos e tamanho total acumulado recursivamente.
3. Exportação da estrutura de árvore para um arquivo HTML (`arvore.html`).
4. Submenu de pesquisas:

   * Maior(es) arquivo(s).
   * Arquivos maiores que N bytes.
   * Pasta(s) com mais arquivos diretos.
   * Arquivos por extensão.
   * Pastas vazias.

---

## Organização do Repositório

```text
projeto-final/                   Raiz do projeto
├── .gitignore                  Ignora binários (.o), executável e HTML gerado
├── Makefile                    Script de build para compilar e linkar o código
├── README.md                   Documentação e instruções de uso
├── programa                    Executável principal (gerado pelo Makefile)
├── arvore.html                 Saída HTML da árvore (gerado pela opção 2)
├── esquema de pastas/          Diretório de teste com exemplo de árvore:
│   ├── pasta1/                contém arquivo1.txt e arquivo2.pdf e subpasta vazia
│   ├── pasta3/                contém teste.txt
│   └── arquivo3.bin           arquivo binário exemplo
└── PROJETO_ARVORE_ARQUIVOS/    Código-fonte modular em C++
    ├── nodo.hpp               Define a estrutura de dados Nodo (caminho, nome, tipo, tamanho, filhos)
    ├── arvore.hpp/.cpp        Protótipos e implementação de construirArvore() e exibirArvore()
    ├── menu.hpp/.cpp          Menu principal e integração com exportação e pesquisas
    ├── pesquisas.hpp/.cpp     Submenu e funções de busca na árvore
    ├── html_export.hpp/.cpp   Função que gera o arquivo HTML da árvore
    └── util.hpp/.cpp (opcional) Serviços auxiliares e conversões
```

---

## Pré-requisitos

* Compilador com suporte a **C++17** (e `<filesystem>`).
* **GNU Make** (ou compatível), Bash e utilitários padrão Linux.
* Sistema operacional GNU/Linux.

---

## Compilação

1. No terminal, navegue até a raiz do projeto:

   ```bash
   cd "~/Área de trabalho/projeto final"
   ```
2. Execute:

   ```bash
   make clean && make
   ```

   * Gera objetos (`*.o`) e linka em `programa`.

---

## Execução

1. Ainda na raiz, execute:

   ```bash
   ./programa
   ```
2. O programa exibe o **Menu Principal**:

   ```text
   ========== MENU PRINCIPAL ==========
   1. Exibir a árvore completa
   2. Exportar árvore para HTML
   3. Pesquisas
   0. Sair
   Escolha uma opção:
   ```

### 1. Exibir a árvore completa

```cpp
// main.cpp (linhas ~30–35)
std::cout << "--- Árvore do sistema de arquivos ---\n";
exibirArvore(raiz);
```

**Saída exemplo:**

```text
├── esquema de pastas (3 filhos, 4108 bytes)
│   ├── pasta1 (3 filhos, 1500 bytes)
│   │   ├── arquivo1.txt (500 bytes)
│   │   ├── arquivo2.pdf (1000 bytes)
│   │   └── pasta2 (0 filhos, 0 bytes)
│   ├── pasta3 (1 filho, 1304 bytes)
│   │   └── teste.txt (1304 bytes)
│   └── arquivo3.bin (1304 bytes)
```

### 2. Exportar árvore para HTML

```cpp
// menu.cpp (case 2)
exportarParaHTML(raiz, "arvore.html");
```

**Saída esperada:**

```text
[OK] Arquivo HTML gerado: arvore.html
```

### 3. Pesquisas

```cpp
// pesquisas.cpp: void menuPesquisas(const shared_ptr<Nodo>& raiz)
```

Menu de opções:

```text
1. Maior(es) arquivo(s)
2. Arquivos com mais do que N bytes
3. Pasta com mais arquivos diretos
4. Arquivos por extensão
5. Pastas vazias
0. Voltar
```

**Trechos de código:**

* **Maior arquivo**: `coletarArquivos()` + `max_element()` em (pesquisas.cpp:25–40)
* **> N bytes**: leitura de `N` + filtro em (pesquisas.cpp:42–60)
* **Mais arquivos diretos**: `coletarPastas()` + contador (pesquisas.cpp:62–82)
* **Por extensão**: uso de `fs::path::extension()` (pesquisas.cpp:84–100)
* **Pastas vazias**: `if (nodo->filhos.empty())` (pesquisas.cpp:102–115)

### 0. Sair

Digite `0` para encerrar.

---

## Boas Práticas e Documentação

### 1. Uso de `<filesystem>`

```cpp
#include <filesystem>                // main.cpp:3
namespace fs = std::filesystem;     // main.cpp:4
// Verificações sem exceção:
bool ok = fs::exists(path, ec);
```

*Biblioteca padrão C++17, portável e segura.*

### 2. `std::shared_ptr` para os nós

```cpp
// arvore.cpp:12
auto nodo = std::make_shared<Nodo>();
```

*Gerenciamento automático de memória via RAII, sem leaks.*

### 3. Include guards em headers

```cpp
// nodo.hpp:1–6
#ifndef NODO_HPP
#define NODO_HPP
#endif
```

*Evita múltiplas inclusões.*

### 4. Modularização e SRP

* Cada módulo (`arvore`, `menu`, `pesquisas`, `html_export`) tem responsabilidade única.
* Interface (.hpp) separada da implementação (.cpp).

### 5. Makefile genérico

```makefile
CXXFLAGS = -std=c++17 -Wall -I$(SRC_DIR)
SRCS    = main.cpp ... html_export.cpp
```

*Apenas `make` recompila incrementalmente.*

### 6. Estrutura de Dados e Conceitos C++

* **Árvore n-ária**: estrutura hierárquica, cada nó (`Nodo`) pode ter vetor de filhos (`std::vector<shared_ptr<Nodo>>`).
* **Complexidade**:

  * Construção e travessia recursiva têm custo O(N), onde N = número total de nós.
  * Pesquisas lineares em vetor: O(N).
* **Recursão**:

  * Função `construirArvore()` chama-se recursivamente para cada subdiretório.
  * Cuidado com profundidade máxima e stack overflow em árvores muito profundas.
* **std::vector**:

  * Armazena filhos contiguamente, cresce dinamicamente, acesso O(1).

### 7. Recursos C++17 e Avançados

* **Auto**: dedução de tipo em iteradores e smart pointers.
* **Raw string literals**: fácil manipulação de strings com barras e espaços (não utilizado, mas disponível).
* **Structured bindings**: não usado, mas aplicável em pares.
* **std::error\_code**: tratamento de erros sem exceções.

### 8. Versionamento e Histórico Git

* Evolução incremental com commits temáticos.
* Uso de `.gitignore` para manter repositório limpo.
* Branch principal `main`, merge de histórico remoto com `--allow-unrelated-histories`.

---

**Versão final do projeto** 

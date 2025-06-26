# Sistema de Arquivos como Árvore

## Descrição do Projeto

Este projeto implementa um gerenciador de sistema de arquivos que carrega a estrutura real de diretórios e arquivos em memória, organizando-a como uma árvore. O usuário pode navegar por essa árvore, exportá-la para um arquivo HTML e realizar diversas pesquisas sobre os arquivos e pastas.

**Funcionalidades obrigatórias:**

1. Carregamento inicial da árvore a partir de um diretório (argumento ou CWD + "esquema de pastas").
2. Exibição interativa da árvore com detalhes:

   * Nome, tipo (arquivo ou pasta), tamanho (bytes).
   * Para pastas: número de filhos diretos e tamanho total recursivo.
3. Exportação da estrutura de árvore para um arquivo HTML (`arvore.html`).
4. Submenu de pesquisas:

   * Maior(es) arquivo(s).
   * Arquivos maiores que N bytes.
   * Pasta(s) com mais arquivos diretos.
   * Arquivos por extensão.
   * Pastas vazias.

O código-fonte está completamente comentado para facilitar a compreensão e futura manutenção.

---

## Organização do Repositório

```text
projeto-final/                   Raiz do projeto
├── .gitignore                  Ignora binários (.o), executável e HTML gerado
├── Makefile                    Script de build para compilar e linkar o código
├── README.md                   Documentação e instruções de uso
├── programa                    Executável principal (gerado pelo Makefile)
├── arvore.html                 Saída HTML da árvore (gerado pela opção 2)
├── esquema de pastas/          Diretório de teste com estrutura de exemplo
│   ├── pasta1/                Pasta contendo arquivos e subpasta vazia
│   │   ├── arquivo1.txt       Arquivo de texto de exemplo (500 bytes)
│   │   ├── arquivo2.pdf       Arquivo PDF de exemplo (1000 bytes)
│   │   └── pasta2/            Subpasta vazia para teste
│   ├── pasta3/                Pasta com um arquivo de tamanho maior
│   │   └── teste.txt          Arquivo de teste (1304 bytes)
│   └── arquivo3.bin           Arquivo binário de exemplo (1304 bytes)
└── PROJETO_ARVORE_ARQUIVOS/    Código-fonte do gerenciador de arquivos
    ├── nodo.hpp               Declara a estrutura de dados Nodo
    ├── arvore.hpp             Protótipos das funções construirArvore() e exibirArvore()
    ├── arvore.cpp             Implementação do carregamento e exibição da árvore
    ├── menu.hpp               Protótipos do menu interativo
    ├── menu.cpp               Implementação do menu principal e chamadas de módulos
    ├── pesquisas.hpp          Protótipos do submenu de pesquisas
    ├── pesquisas.cpp          Implementação das buscas (maior arquivo, extensão, etc.)
    ├── html_export.hpp        Protótipos da função exportarParaHTML()
    └── html_export.cpp        Implementação da exportação em HTML
```

---

## Pré-requisitos

* **C++17** (compilador compatível com `<filesystem>`).
* **GNU Make** ou `make` compatível.
* Sistema operacional GNU/Linux.

---

## Compilação

1. Abra o terminal na pasta raiz do projeto:

   ```bash
   cd "~/Área de trabalho/projeto final"
   ```
2. Execute o comando:

   ```bash
   make clean && make
   ```

   Isso irá:

   * Compilar todos os módulos (`main.o`, `menu.o`, `arvore.o`, `pesquisas.o`, `html_export.o`).
   * Gerar o executável `programa` na raiz.

---

## Execução

No terminal, ainda na raiz do projeto, execute:

```bash
./programa
```

Ao iniciar, aparecerá o **Menu Principal**:

```
========== MENU PRINCIPAL ==========
1. Exibir a árvore completa
2. Exportar árvore para HTML
3. Pesquisas
0. Sair
Escolha uma opção:
```

### 1. Exibir a árvore completa

* Seleção: digite `1` e pressione <Enter>.
* Exemplo de saída:

  ```
  --- Árvore do sistema de arquivos ---
  ├── esquema de pastas (3 filhos, 4108 bytes)
      ├── pasta1 (3 filhos, 1500 bytes)
      │   ├── arquivo1.txt (500 bytes)
      │   ├── arquivo2.pdf (1000 bytes)
      │   └── pasta2 (0 filhos, 0 bytes)
      ├── pasta3 (1 filho, 1304 bytes)
      │   └── teste.txt (1304 bytes)
      └── arquivo3.bin (1304 bytes)
  ```

### 2. Exportar árvore para HTML

* Seleção: digite `2` e pressione <Enter>.
* Gere o arquivo `arvore.html` na pasta raiz.
* Saída esperada:

  ```
  [OK] Arquivo HTML gerado: arvore.html
  ```

### 3. Pesquisas

* Seleção: digite `3` e pressione <Enter>.
* Submenu de pesquisas:

  ```
  --- MENU DE PESQUISAS ---
  1. Maior(es) arquivo(s)
  2. Arquivos com mais do que N bytes
  3. Pasta com mais arquivos diretos
  4. Arquivos por extensão
  5. Pastas vazias
  0. Voltar
  Escolha uma opção:
  ```

#### 3.1 Maior(es) arquivo(s)

* Exibe todos os arquivos de maior tamanho.
* Exemplo:

  ```
  Maior(es) arquivo(s):
  /home/aluno/pasta3/teste.txt (1304 bytes)
  /home/aluno/arquivo3.bin (1304 bytes)
  ```

#### 3.2 Arquivos com mais do que N bytes

* Solicita `N`. Exemplo: `N = 999`.
* Exemplo de saída:

  ```
  Arquivos com mais do que N bytes (N=999):
  /home/aluno/pasta1/arquivo2.pdf (1000 bytes)
  /home/aluno/pasta3/teste.txt (1304 bytes)
  /home/aluno/arquivo3.bin (1304 bytes)
  ```

#### 3.3 Pasta com mais arquivos diretos

* Exibe pasta(s) com mais itens diretos.
* Exemplo:

  ```
  Pasta(s) com mais arquivos diretos:
  /home/aluno (3 filhos, 4108 bytes)
  /home/aluno/pasta1 (3 filhos, 1500 bytes)
  ```

#### 3.4 Arquivos por extensão

* Solicita extensão (ex: `.txt`).
* Exemplo:

  ```
  Arquivos por extensão (.txt):
  /home/aluno/pasta1/arquivo1.txt (500 bytes)
  /home/aluno/pasta3/teste.txt (1304 bytes)
  ```

#### 3.5 Pastas vazias

* Lista todas as pastas sem filhos.
* Exemplo:

  ```
  Pastas vazias:
  /home/aluno/pasta1/pasta2
  ```

### 0. Sair

* Seleção: digite `0` para encerrar o programa.

---

## Observações finais

* Todos os arquivos-fonte estão com comentários explicativos.
* O HTML gerado pode ser aberto em qualquer navegador para visualização estática da árvore.
* Use `make clean` para remover objetos e executável.

---

**Versão final do projeto** 🎉

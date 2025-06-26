// ============================================================================
// Arquivo: pesquisas.hpp
// Finalidade: Declaração das funções para executar buscas na árvore de arquivos
//            e apresentar ao usuário os resultados conforme critérios:
//              1) Maior(es) arquivo(s)
//              2) Arquivos maiores que N bytes
//              3) Pasta com mais arquivos diretos
//              4) Arquivos por extensão
//              5) Pastas vazias
// ============================================================================

#ifndef PESQUISAS_HPP
#define PESQUISAS_HPP

#include <memory>
#include "nodo.hpp"   // para std::shared_ptr<Nodo>

// ======================================
// Exibe o submenu de pesquisas e chama as
// funções correspondentes definidas em
// pesquisas.cpp.
// ======================================
void menuPesquisas(const std::shared_ptr<Nodo>& raiz);

#endif // PESQUISAS_HPP

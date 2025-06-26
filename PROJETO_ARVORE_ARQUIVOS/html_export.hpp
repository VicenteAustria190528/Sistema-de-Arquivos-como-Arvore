// ============================================================================
// Arquivo: html_export.hpp
// Finalidade: Declaração da função que exporta a árvore de arquivos para HTML.
// ============================================================================

#ifndef HTML_EXPORT_HPP
#define HTML_EXPORT_HPP

#include <memory>
#include <string>
#include "nodo.hpp"  // Estrutura Nodo usada para navegar na árvore

// ----------------------------------------------------------------------------
// Função: exportarParaHTML
// Objetivo: Receber a raiz da árvore de arquivos e gerar um arquivo HTML que
//           apresente a estrutura hierárquica em formato pré-formatado.
// Parâmetros:
//   - raiz: ponteiro para o nó raiz da árvore (std::shared_ptr<Nodo>)
//   - nomeArquivo: nome (ou caminho) do arquivo HTML de saída (std::string)
// Retorno: void (exibe mensagem de sucesso ou erro no terminal)
// ----------------------------------------------------------------------------
void exportarParaHTML(const std::shared_ptr<Nodo>& raiz,
                      const std::string& nomeArquivo);

#endif // HTML_EXPORT_HPP

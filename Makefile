# ====================================================================
# Makefile (na raiz: projeto final/)
# Objetivo: compilar o código-fonte dentro de PROJETO_ARVORE_ARQUIVOS
# e gerar o executável 'programa' na raiz.
# Como usar:
#   make        # compila tudo
#   make clean  # remove binários e objetos
# ====================================================================

# Nome da pasta onde está o código
SRC_DIR := PROJETO_ARVORE_ARQUIVOS

# Compilador e flags gerais
CXX      := g++
CXXFLAGS := -std=c++17 -Wall -I$(SRC_DIR)

# Executável final
TARGET := programa

# Listagem dos fontes (sem paths) — agora incluindo pesquisas.cpp e html_export.cpp
SRCS := main.cpp menu.cpp arvore.cpp pesquisas.cpp html_export.cpp

# Objetos gerados na raiz
OBJS := $(SRCS:.cpp=.o)

# Regra padrão: compila tudo
all: $(TARGET)

# Linkagem final: usa todos os objetos
$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regra para compilar cada .cpp dentro de SRC_DIR em .o na raiz
%.o: $(SRC_DIR)/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Remove objetos e executável
clean:
	rm -f $(OBJS) $(TARGET)

.PHONY: all clean

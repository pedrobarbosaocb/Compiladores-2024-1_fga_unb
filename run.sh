#!/bin/bash

# Compilar o código C
gcc -o output parseTree.c

# Verificar se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
  # Executar o programa
  ./output
else
  echo "Erro na compilação."
fi
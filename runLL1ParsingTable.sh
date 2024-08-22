#!/bin/bash

# Compilar o código C
gcc -o output LL-1-Parsing-Table/LL\(1\)_prsing_table.c 

# Verificar se a compilação foi bem-sucedida
if [ $? -eq 0 ]; then
  # Executar o programa
  ./output
else
  echo "Erro na compilação."
fi
#!/bin/bash

# Compilar el código C++
g++ -o needlman_wunsh needlman_wunsh.cpp

# Ejecutar el código con los parámetros de entrada
./needlman_wunsh $1 $2

# El resultado se guarda en alignment_results.txt

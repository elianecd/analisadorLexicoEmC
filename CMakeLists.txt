cmake_minimum_required(VERSION 3.10)
project(analisadorLexico)

# Definindo o padrão C para C11
set(CMAKE_C_STANDARD 11)

# Adicionar o executável e listar todos os arquivos de código-fonte
add_executable(analisadorLexico main.c lexer.c)

all:help
CC=gcc
help:
	@cat docs/Utilizacao.txt
classes:
	@g++ -o bin/pessoa src/Classe/Produto/Produto.h src/Classe/Produto/Produto.cpp src/Classe/Pessoa/Pessoa.h src/Classe/Pessoa/Pessoa.cpp testes/Classes/main.cpp testes/Classes/main.h
teoriaDosNumeros:
	@g++ -o bin/teoriaDosNumeros testes/"teoria dos números"/main.cpp src/teoriaDosNumeros/main.h src/teoriaDosNumeros/mdc.cpp src/teoriaDosNumeros/mmc.cpp 
duplamenteEncadeada:

listaContigua:
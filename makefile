all:help

help:
	@echo "a"
pessoa: 
	@g++ testes/Classes/main.cpp src/Classe/Pessoa/Pessoa.cpp -o bin/main
teoriaDosNumeros:
	@g++ testes/"teoria dos números"/main.cpp src/teoriaDosNumeros/main.h src/teoriaDosNumeros/mdc.cpp src/teoriaDosNumeros/mmc.cpp -o bin/main

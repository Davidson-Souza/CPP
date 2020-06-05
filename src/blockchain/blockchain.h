/**
 * Blockchain é uma estrutura de dados proposto em 1991 por Stuart Haber e W. Scott Stornetta. O objetivo
 * é criar um sistema confiável, que mantivesse as informações de maneira segura e descentralizada
 * A estrutura de uma blockchain é formada por blocos que se ligam em uma "cadeia", isto é, um depende
 * do outro
 * 
 * ┌────────────┐  	       ┌────────────┐  	        ┌────────────┐
 * │     Head   │   ┌─────>│     Head   │   ┌─────> │     Head   │   
 * |      Tx    │  	│      |      Tx    │  	│       |      Tx    │  	
 * │      Tx    │  	│      │      Tx    │  	│       │      Tx    │  	
 * │      Tx    │  	│      │      Tx    │  	│       │      Tx    │  	
 * │     Hash   │───┘      │     Hash   │───┘       │     Hash   │
 * └────────────┘          └────────────┘           └────────────┘
 * O bloco é formado por transações individuais, um cabeçálho e uma hash (ou assinatura) que depende, 
 * dentre outras coisas, do hash anterior.
 * 
 */
#ifndef BLOCKCHAIN
#define BLOCKCHAIN
class BlockChain
{

};

#endif


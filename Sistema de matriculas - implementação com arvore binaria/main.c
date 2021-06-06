#include "arvore.h"
#include "menu.h"

void main(void){
    int opcao;
    Arvore * arvore = inicializa_arvore();
    
    while(1){
        opcao = imprime_menu();
        executa_menu(opcao, &arvore);
    }
}
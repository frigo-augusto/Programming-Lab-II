#include <stdio.h>
#include <stdlib.h>

#include "menu.h"
#include "arvore.h"

int imprime_menu(){
    int opcao;
    do {
        printf("\n\n------- Menu de Opcoes -------");
        printf("\n[ 0 ] Inserir curso");
        printf("\n[ 1 ] Excluir curso");
        printf("\n[ 2 ] Imprimir arvore de cursos");
        printf("\n[ 3 ] Inserir aluno");
        printf("\n[ 4 ] Remover aluno");
        printf("\n[ 5 ] Imprimir lista de alunos");
        printf("\n[ 6 ] Imprimir vinculos");
        printf("\n[ 7 ] Sair do programa");
        printf("\nDigite sua opcao: ");
        scanf("%d", &opcao); 
    } while(opcao < 0 || opcao > 7);    
    return opcao;
}


void executa_menu(int opcao, Arvore** arvore){
    switch (opcao)
    {
    case 0:
        cadastra_curso(*(arvore));
        break;
    case 1:
        remove_curso(*(arvore));
        break;
    case 2:
        chama_arv_imprime(retorna_raiz(*(arvore)));
        break;
    case 3:
        aluno_insere(*(arvore));
        break;
    case 4:
        aluno_remove(*(arvore));
        break;
    case 5:
        aluno_imprime(*(arvore));
        break;
    case 6:
        vinculo_imprime(*(arvore));
        break;
    case 7:
        chama_libera_arvore(retorna_raiz(*(arvore)));
        exit(0);
        break;
    default:
        printf ("\nEntrada invalida!");    
        break;
    }
}
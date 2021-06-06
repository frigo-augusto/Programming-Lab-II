#include <stdio.h>
#include <stdlib.h>
#include "lista.h"
#include "menu.h"

int imprimeMenu(){
    int opcao = 10;
    do {
        printf("\n------- Menu de Opcoes -------");
        printf("\n[ 0 ] Cadastrar aluno");
        printf("\n[ 1 ] Cadastrar professor");
        printf("\n[ 2 ] Cadastrar projeto");
        printf("\n[ 3 ] Cadastrar vinculo");
        printf("\n[ 4 ] Remover vinculo");
        printf("\n[ 5 ] Listar alunos");
        printf("\n[ 6 ] Listar professores");
        printf("\n[ 7 ] Listar projetos");
        printf("\n[ 8 ] Sair do programa");
        printf("\nDigite sua opcao: ");
        scanf("%d", &opcao);
        setbuf(stdin, NULL);
    } while(opcao < 0 || opcao > 9);    
    return opcao;
}

void executa_opcao(Aluno** aluno, Professor** professor, Projeto** projeto, Vinculo** vinculo, int opcao){
    switch (opcao)
    {
    case 0:
        *aluno = cadastraAluno(*aluno);
        break;
    case 1:
        *professor = cadastraProfessor(*professor);
        break;
    case 2:
        *projeto = cadastraProjeto(*projeto, *professor);
        break;
    case 3:
        *vinculo = cadastraVinculo(*vinculo, *projeto, *aluno);
        break;
    case 4:
        *vinculo = removeVinculo(*vinculo, *projeto, *aluno);
        break;
    case 5:
        imprimeAluno(*aluno);
        break;
    case 6:
        imprimeProfessor(*professor);
        break;
    case 7:
        imprimeProjeto(*projeto, *vinculo);
        break;
    case 8:
        liberaAluno(aluno);
        liberaProfessor(professor);
        liberaProjeto(projeto);
        liberaVinculo(vinculo);
        exit(0);
        break;
    default:
        printf ("\nEntrada invalida!");
        break;
    }
}
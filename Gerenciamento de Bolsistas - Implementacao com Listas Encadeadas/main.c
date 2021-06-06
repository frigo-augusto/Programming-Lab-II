#include <stdio.h>
#include "lista.h"
#include "menu.h"

int main(void){
    introduz_programa();
    Aluno* aluno = criaAluno();
    Projeto* projeto = criaProjeto();
    Vinculo* vinculo = criaVinculo();
    Professor* professor = criaProfessor();

    while (1){
    int opcao = imprimeMenu(aluno, projeto, vinculo, professor);
    executa_opcao(&aluno, &professor, &projeto, &vinculo, opcao);
    }

}
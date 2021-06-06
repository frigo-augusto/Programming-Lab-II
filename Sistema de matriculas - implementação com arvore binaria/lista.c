#include <stdio.h>
#include <stdlib.h>

#include "lista.h"

struct lista{
    int matricula;
    char* nome;
    int ano;
    Lista* prox;
};

static Lista* busca_aluno(Lista* aluno, int matricula);
static Lista* encontra_menor(Lista* no, int mat);
static Lista* insere_aluno(Lista* no, int mat, char* nome, int ano);



//funcoes de criacao



static Lista* encontra_menor(Lista* no, int mat){
    Lista* aux = no;
    Lista* anterior = NULL;

    while (aux != NULL && aux->matricula < mat){
        anterior = aux;
        aux = aux->prox;
    }

    return anterior;
}


static Lista* busca_aluno(Lista* aluno, int matricula){
    Lista* aux = aluno;

    while (aux != NULL){
        if(aux->matricula == matricula){
            return aux;
        }
        
        aux = aux->prox;
    }

    return NULL;
}

////////

//funcoes de criacao


Lista* cria_lista(){
    Lista* lista = (Lista*) malloc(sizeof(Lista));
    lista = NULL;
    return lista;
}

////////////


///funcoes de insercao


static Lista* insere_aluno(Lista* no, int mat, char* nome, int ano){
    Lista* anterior = encontra_menor(no, mat);

    Lista* novo = (Lista*) malloc(sizeof (Lista));
    novo->matricula = mat;
    novo->nome = nome;
    novo->ano = ano;

    if(anterior == NULL){
        novo->prox = no;
        no = novo;
    } else {
        novo->prox = anterior->prox;
        anterior->prox = novo;
    }

    return no;
}



Lista* cadastra_aluno(Lista* aluno){
    char* nome = (char*) malloc(50* sizeof(char));
    int matricula, ano;
    
    printf("\nDigite a matricula do aluno(a): ");
    scanf("%d", &matricula);
    setbuf(stdin, NULL);

    if(busca_aluno(aluno, matricula) != NULL){
        printf("\nErro! Esse aluno(a) ja esta cadastrado(a) no curso! Retornando ao menu...");
        return aluno;        
    }

    printf("\nDigite o nome do aluno(a): ");
    scanf(" %50[^\n]", nome);

    printf("\nDigite o ano em que o aluno(a) ingressou no curso: ");
    scanf("%d", &ano);

    printf("\nAluno(a) cadastrado(a) com sucesso!");
    return insere_aluno(aluno, matricula, nome, ano);
}

////////////





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

void imprime_lista_inteira(Lista* no, char* nome, char* centro){
    Lista* aux = no;
    
    while (aux != NULL){
        printf("\n %-8d  | %-18s | %-50s | %s", aux->matricula, aux->nome, nome, centro);
        aux = aux->prox;
    }    
}


///funcoes de remocao


Lista* aluno_remove_lista(Lista* no, int matricula){
    Lista* ant = NULL;
    Lista* aux = no;

    while (aux != NULL && aux->matricula != matricula){
        ant = aux;
        aux = aux->prox;
    }
    
    if (aux == NULL){
        printf("Erro! Esse aluno nao esta cadastrado no sistema.");
        return no;
    }

    if (ant == NULL){
        no = aux->prox;
    } else {
        ant->prox = aux->prox;
    }

    free(aux->nome);
    free(aux);
    aux = NULL;

    return no;
}


/////////////////

///funcoes de liberacao



void libera_lista(Lista* lista){
    if (lista == NULL)
        return;
    
    Lista* aux = NULL;

    while (lista != NULL){
        aux = lista;
        lista = lista->prox;
        free(aux->nome);
        free(aux);
    }
    lista = NULL;
}





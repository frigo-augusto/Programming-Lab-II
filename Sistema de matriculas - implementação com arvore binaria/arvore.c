#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "arvore.h"
#include "lista.h"

struct no{
    int codigo;
    char* nome;
    char* centro;
    Lista* alunos;
    No* esq;
    No* dir;
    No* pai;
};

struct arvore{
    No* raiz;
};

static void remove_curso2(No** no, int codigo);
static void remove_curso3(No ** no);

static void arv_percorre (No* pai);
static void arv_imprime(No* pai);
static bool arv_vazia(Arvore* arvore);

static No* pergunta_curso(Arvore* arvore);
static No* aloca_no();
static No * cria_no(int codigo, char* nome, char* centro);
static No* busca_curso(No* no, int codigo);

static void insere_ordenado(Arvore * arvore, int codigo, char* nome, char* centro);
static void insere_ordenado_aux(No* no, int codigo, char* nome, char* centro);

static int pergunta_matricula();

static void libera_no(No* no);
static void libera_arvore(No* no);


//funcoes auxiliares gerais
static No* busca_curso(No* no, int codigo){
    static No* aux;
    if(no == NULL)
        return NULL;

    if (no->codigo == codigo)
        return no;

    if (codigo > no->codigo)
        aux = busca_curso(no->dir, codigo);
    
    if (codigo < no->codigo)
        aux = busca_curso(no->esq, codigo);
    
    return aux;

}



static void arv_percorre (No* pai){
    if (pai==NULL)
        return;
    arv_percorre(pai->esq);
    imprime_lista_inteira(pai->alunos, pai->nome, pai->centro);
    arv_percorre(pai->dir);
}



No* retorna_raiz(Arvore* arvore){
    return arvore->raiz;
}



static No * retorna_maior_no(No * no)
{
    if (no->dir==NULL)
        return no;

    return retorna_maior_no(no->dir);
}



static No * retorna_menor_no(No * no)
{
    if (no->esq==NULL)
        return no;

    return retorna_menor_no(no->esq);
}



static bool arv_vazia(Arvore* arvore){
    if (arvore->raiz == NULL)
        return 1;
    else
        return 0;
}



////////////////





//funcoes de inicializacao

Arvore * inicializa_arvore(){
    Arvore * arvore = (Arvore *) malloc(sizeof(Arvore));
    arvore->raiz = NULL;
    return arvore;
}




static No* aloca_no(){
    No* no = (No*) malloc(sizeof(No));
    no->esq = NULL;
    no->dir = NULL;
    no->pai = NULL;
    no->alunos = cria_lista();
    return no;
}



static No * cria_no(int codigo, char* nome, char* centro){
    No* no = aloca_no();
    no->codigo = codigo;
    no->nome = nome;
    no->centro = centro;
    return no;
}

////////////







//funcoes de insercao


static void insere_ordenado(Arvore * arvore, int codigo, char* nome, char* centro){
    if (arvore->raiz == NULL){
        No * novo = cria_no(codigo, nome, centro);
        arvore->raiz = novo;
        return;
    }
    
    insere_ordenado_aux(arvore->raiz, codigo, nome, centro);
}



static void insere_ordenado_aux(No* no, int codigo, char* nome, char* centro){
    if (no == NULL)
        return;
    
    if (codigo < no->codigo){
        if (no->esq == NULL){
            no->esq = cria_no(codigo, nome, centro);
            no->esq->pai = no;
            return;
        }
        insere_ordenado_aux(no->esq, codigo, nome, centro);
    }
    else{
        if(codigo == no->codigo){
            return; 
        }
        else{
            if(codigo > no->codigo){
                if (no->dir == NULL){
                    no->dir = cria_no(codigo, nome, centro);
                    no->dir->pai = no;
                    return;
                }
                insere_ordenado_aux(no->dir, codigo, nome, centro);
            }
        }
    }

}


void cadastra_curso(Arvore* arvore){
    char* nome = (char*) malloc(50* sizeof(char));
    char* centro = (char*) malloc(50*sizeof(char));
    int codigo, ano;
    
    printf("\nDigite o codigo do curso: ");
    scanf("%d", &codigo);
    setbuf(stdin, NULL);

    if(busca_curso(arvore->raiz, codigo) != NULL){
        printf("\nErro! Esse curso ja esta cadastrado no sistema! Retornando ao menu...");
        return;        
    }

    printf("\nDigite o nome do curso: ");
    scanf(" %50[^\n]", nome);

    printf("\nDigite o centro do curso: ");
    scanf(" %50[^\n]", centro);

    printf("\nCurso cadastrado com sucesso!");
    insere_ordenado(arvore, codigo, nome, centro);
}



void aluno_insere(Arvore* arvore){
    No* aux = pergunta_curso(arvore);
    if (aux == NULL){
        printf("\nErro! Este curso nao esta cadastrado! Retornando ao menu...");
        return;
    }
    aux->alunos = cadastra_aluno(aux->alunos);
}



/////////






//funcoes de impressao


void chama_arv_imprime(No* pai){
    printf("\nCursos cadastrados:\n");
    arv_imprime(pai);
}



static void arv_imprime(No* pai){
    if (pai==NULL)
        return;
    arv_imprime(pai->esq);
    printf("\n%d \t%s", pai->codigo, pai->nome);
    arv_imprime(pai->dir);
}


void aluno_imprime(Arvore* arvore){
    No* aux = pergunta_curso(arvore);
    if (aux == NULL){
        printf("\nErro! Este curso nao esta cadastrado! Retornando ao menu...");
        return;
    }
    imprime_lista(aux->alunos);
}

void vinculo_imprime(Arvore* arvore){
    printf("\n Matricula |        Nome        |                       Curso                        | Centro");
    arv_percorre(arvore->raiz);                 
}



/////////////

//funcoes de remocao


void remove_curso(Arvore* arvore){
    if (arvore->raiz == NULL)
        return;

    No* aux = pergunta_curso(arvore);
    if (aux == NULL){
        printf("\nErro! Este curso nao esta cadastrado! Retornando ao menu...");
        return;
    }   
    remove_curso2(&(arvore->raiz), aux->codigo);
}



static void remove_curso2(No** no, int codigo){

    if ((*no) == NULL)
        return;
    
    if ((*no)->codigo == codigo){
        remove_curso3(no);
    }
    else{
        if((*no)->codigo < codigo){
            remove_curso2(&((*no)->dir), codigo);
        }
        else{
            remove_curso2(&((*no)->esq), codigo);
        }
    }

}



static void remove_curso3(No ** no){
    if (no == NULL){
        printf("O curso a ser removido nao foi encontrado.");
        return;
    }

    if ((*no)->esq==NULL && (*no)->dir == NULL)
    {
        if ((*no)->pai==NULL){
            libera_lista((*no)->alunos);
            free((*no)->nome);
            free((*no)->centro);
            (*no) = NULL;
            printf("Curso removido com sucesso.");
            return;
        }
        if ((*no)->pai->esq==(*no)){
            (*no)->pai->esq = NULL;
        }
        else{
            (*no)->pai->dir = NULL;
        }
        free(*no);
        free((*no)->nome);
        free((*no)->centro);
        libera_lista((*no)->alunos);
        
        printf("\nCurso removido com sucesso!");
        return;
    }
    if ((*no)->esq!=NULL) {

        No * maior = retorna_maior_no((*no)->esq);
        (*no)->codigo = maior->codigo;
        (*no)->nome = maior->nome;
        (*no)->centro = maior->centro;
        (*no)->alunos = maior->alunos;

        remove_curso3(&maior);
        return;
    }
    else{

        No * menor = retorna_menor_no((*no)->dir);
        (*no)->codigo = menor->codigo;
        (*no)->nome = menor->nome;
        (*no)->centro = menor->centro;
        (*no)->alunos = menor->alunos;

        remove_curso3(&menor);
        return;
    }

}


void aluno_remove(Arvore* arvore){
    No* aux = pergunta_curso(arvore);
    if (aux == NULL){
        printf("\nErro! Este curso nao esta cadastrado! Retornando ao menu...");
        return;
    }
    int mat = pergunta_matricula();
    aluno_remove_lista(aux->alunos, mat);
    printf("\nAluno removido com sucesso!");
}



/////////











//funcoes de leitura

static No* pergunta_curso(Arvore* arvore){
    int aux;
    printf("\nDigite o codigo do curso: ");
    scanf("%d", &aux);
    return busca_curso(arvore->raiz, aux);
}



static int pergunta_matricula(){
    int matricula;
    printf("\nEntre a matricula do aluno a ser removido: ");
    scanf("%d", &matricula);
    return matricula;
}


//////////












///funcoes de liberacao




static void libera_no(No* no){
    if(no == NULL)
        return;
    free(no->nome);
    free(no->centro);
    libera_lista(no->alunos);
    free(no);
}



void chama_libera_arvore(No* no){
    printf ("\nSaindo do programa...");
    libera_arvore(no);
}



static void libera_arvore(No* no){
    if(no == NULL)
        return;

    libera_arvore(no->esq);
    libera_arvore(no->dir);
    libera_no(no);    
}

//////////////





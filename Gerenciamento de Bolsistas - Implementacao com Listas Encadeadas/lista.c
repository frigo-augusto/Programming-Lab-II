#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lista.h"
/*

Declaracao das structs

*/
struct aluno{
    char* matricula;
    char* nome;
    char* telefone;
    struct aluno* ant;
    struct aluno* prox;
};

struct projeto{
    char* codigo;
    char* descricao;
    char* tipo;
    float orcamento_total;
    float orcamento_atual;
    struct professor* professor;
    struct projeto* ant;
    struct projeto* prox;
};

struct vinculo{
    struct aluno* aluno;
    struct projeto* projeto;
    float bolsa_mensal;
    struct vinculo* ant;
    struct vinculo* prox;
};

struct professor{
    char* codigo;
    char* nome;
    char* depto;
    struct professor* ant;
    struct professor* prox;
};

/*

Funcoes auxiliares

*/

void introduz_programa(){
    printf("\n-------------------------\n");
    printf("Programa para controle de participacao\n");
    printf("de bolsistas em projetos.\n");
    printf("-------------------------\n");
    printf ("Atencao: entradas invalidas farao o\n");
    printf("programa solicita-las novamente. Em caso\n");
    printf ("de tentativas de cadastro de usuarios ja \n");
    printf("existentes, voce sera retornado ao menu.\n\n");
}


int procuraNumero(char* string){
    //essa funcao serve basicamente para ver se o usuario esta com o input correto
    //e nao colocando letras na matricula, por exemplo. O valor retornado corresponde
    //a que tipo de caracteres o usuario inseriu.
    int contN = 0, contL = 0, contE = 0;
    for(int i = 0; i < strlen(string); i++){
        if (string[i] >= '0' && string[i] <= '9'){
            contN++;
        } else if (string[i] >= 'A' && string[i] <= 'Z' || string[i] >= 'a' && string[i] <= 'z'){
            contL++;
        } else if (string[i] != ' '){
            contE++;
        }
    }
    if(contN == 0 && contL != 0 && contE == 0){
        //ha apenas numeros, retorna 0
        return 0;
    } else if (contL == 0 && contN != 0 && contE == 0){
        //ha apenas letras, retorna 1
        return 1;
    } else {
        //ha tipos variados de caracteres, retorna -1
        return -1;
    }
}




/*

Funcoes de criacao

*/
Aluno* criaAluno(){
    Aluno* aluno = (Aluno*) malloc(sizeof(Aluno));
    aluno = NULL;
    return aluno;
}

Professor* criaProfessor(){
    Professor* professor = (Professor*) malloc(sizeof(Professor));
    professor = NULL;
    return professor;
}

Projeto* criaProjeto(){
    Projeto* projeto = (Projeto*) malloc(sizeof(Projeto));
    projeto = NULL;
    return projeto;
}

Vinculo* criaVinculo(){
    Vinculo* vinculo = (Vinculo*) malloc(sizeof(Vinculo));
    vinculo = NULL;
    return vinculo;
}



/*

Funcoes de busca

*/

//Aqui sao feitas as buscas para ver se ha cadastro ou vinculo. Se nao houver, e retornado null.
Aluno* buscaAluno(Aluno* aluno, char* matricula){
    Aluno* aux = aluno;
    while(aux != NULL){
        if (strcmp(aux->matricula, matricula) == 0){
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

Professor* buscaProfessor(Professor* professor, char* codigo){
    Professor* aux = professor;
    while(aux != NULL){
        if (strcmp(aux->codigo, codigo) == 0){
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

Projeto* buscaProjeto(Projeto* projeto, char* codigo){
    Projeto* aux = projeto;
    while(aux != NULL){
        if (strcmp(aux->codigo, codigo) == 0){
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}

Vinculo* buscaVinculo(Vinculo* vinculo, char* codigo, char* matricula){
    Vinculo* aux = vinculo;
    while (aux != NULL){
        if (strcmp(aux->projeto->codigo, codigo) == 0 && strcmp(aux->aluno->matricula, matricula) == 0){
            return aux;
        }
        aux = aux->prox;
    }
    return NULL;
}


/*

Funcoes de impressao

*/


void imprimeAluno(Aluno* aluno){
    Aluno* aux = aluno;
    printf("\nAlunos:\n");
    while (aux != NULL){
        printf ("\nnome: %s\nmatricula: %s\ntelefone: %-12s\n", aux->nome, aux->matricula, aux->telefone);
        aux = aux->prox;
    }
    printf("\n");
}

void imprimeProfessor(Professor* professor){
    Professor* aux = professor;
    printf("\nProfessores:");
    while (aux != NULL){
        printf ("\nCodigo: %s", aux->codigo);
        printf ("\nNome: %s", aux->nome);
        printf ("\nDepartamento: %s", aux->depto);
        printf ("\n");
        aux = aux->prox;
    }
}


void imprimeVinculo(Vinculo* vinculo, char* codigo){
    int cont = 0;
    Vinculo* aux = vinculo;
    while (aux != NULL){
        if(strcmp(aux->projeto->codigo, codigo) == 0){
            printf ("%s\n", aux->aluno->nome);
            cont++;
        }
        aux = aux->prox;
    }
    if(cont == 0){
        printf (" Nao ha alunos vinculados a este projeto");
    }
}


void imprimeProjeto(Projeto* projeto, Vinculo* vinculo){
    Projeto* aux = projeto;
    printf("\nProjetos:\n");
    printf("\n--------------------");
    while (aux != NULL){
        printf ("\nCodigo do projeto: %s", aux->codigo);
        printf ("\nProjeto de %s, coordenado por %s", aux->tipo, aux->professor->nome);
        printf ("\nOrcamento atual disponivel de R$ %.2f", aux->orcamento_atual);
        printf ("\nAlunos vinculados:\n");
        imprimeVinculo(vinculo, aux->codigo);
        printf("\n--------------------");
        printf ("\n");
        aux = aux->prox;
    }
}


/*

Funcoes de insercao

*/

//Nessas funcoes sao feitas as manipulacoes nas listas para que a insercao seja correta.

Aluno* insereAluno(Aluno* aluno, char* matricula, char* telefone, char* nome){
    Aluno* aux = (Aluno*) malloc(sizeof(Aluno));
    aux->matricula = matricula;
    aux->nome = nome;
    aux->telefone = telefone;
    aux->prox = aluno;
    aux->ant = NULL;
    if (aluno != NULL){
        aluno->ant = aux;
    }
    return aux;
}

Professor* insereProfessor(Professor* professor, char* codigo, char* nome, char* depto){
    Professor* aux = (Professor*) malloc(sizeof(Professor));
    aux->codigo = codigo;
    aux->nome = nome;
    aux->depto = depto;
    aux->prox = professor;
    aux->ant = NULL;
    if (professor != NULL){
        professor->ant = aux;
    }
    return aux;
}

Projeto* insereProjeto(Projeto* projeto, char* codigo, char* descricao, float orcamento_total, int tipo, Professor* professor){
    Projeto* aux = (Projeto*) malloc(sizeof(Projeto));
    aux->codigo = codigo;
    aux->descricao = descricao;
    aux->orcamento_total = orcamento_total;
    aux->orcamento_atual = orcamento_total;
    switch (tipo) {
            case 0:
                aux->tipo = "ensino";
                break;
            case 1:
                aux->tipo = "pesquisa";
                break;
            default:
                aux->tipo = "extensao";
                break;
        }
    aux->professor = professor;
    aux->prox = projeto;
    aux->ant = NULL;
    if (projeto != NULL){
        projeto->ant = aux;
    }
    return aux;
}


Vinculo* insereVinculo(Vinculo* vinculo, Aluno* aluno, Projeto* projeto, float bolsa_mensal){
    Vinculo* aux = (Vinculo*) malloc(sizeof(Vinculo));
    aux->aluno = aluno;
    aux->projeto = projeto;
    aux->bolsa_mensal = bolsa_mensal;
    aux->prox = vinculo;
    aux->ant = NULL;
    if (vinculo != NULL){
        vinculo->ant = aux;
    }
    return aux;
}


/*

Funcoes auxiliares de cadastro

*/
//Aqui ha funcoes auxiliares as principais de cadastro.

char* leMatCod(char* matCodprint, char* tipoStruct){
    char* matricula = (char*) malloc(20* sizeof(char));
    do {
        printf("\nDigite %s do %s: ", matCodprint, tipoStruct);
        scanf(" %20[^\n]", matricula);
    } while (procuraNumero(matricula) != 1 || strlen(matricula) > 20 || strlen(matricula) <= 0); 
    return matricula;
}

char* leNome(char* auxImpressao){
    char* nome = (char*) malloc(100* sizeof(char));
    do {
        printf("\nDigite o nome do %s: ", auxImpressao);
        scanf(" %100[^\n]", nome);
    } while (procuraNumero(nome) != 0);
    return nome;
}

char* leTelefone(){
    char* telefone = (char*) malloc(12* sizeof(char));
    do {
        printf("\nDigite o telefone do aluno: ");
        scanf(" %12[^\n]", telefone);
    } while (procuraNumero(telefone) != 1 || strlen(telefone) > 12);
    return telefone;
}

char* leGenerico(char* texto, int tamanho){
    char* gen = (char*) malloc(tamanho* sizeof(char));
    do
    {
        printf("\n%s", texto);
        scanf(" %9999[^\n]", gen);
    } while (strlen(texto) >= tamanho);
    
    return gen;
}

int leTipo(){
    int tipo;
    printf("\nTipos de projeto:");
    printf("\n[0] - Ensino");
    printf("\n[1] - Pesquisa");
    printf("\n[2] - Extensao");  
    do {
        printf("\nDigite o numero correspondente ao tipo do projeto: ");
        scanf("%d", &tipo);
        setbuf(stdin, NULL);
    } while (tipo > 2 || tipo < 0); 
    return tipo;
}

float leFloat(char* texto){
    float generico;
    printf ("%s", texto);
    scanf ("%f", &generico);
    setbuf(stdin, NULL);
    return generico;
}

void NaoJaCadastrado(char* aux){
    printf("\nErro! Esse %s esta cadastrado no sistema! Retornando ao menu...", aux);
}

void cadastroBemSucedido(){
    printf ("Operacao bem sucedida.");
}

void orcamentoInsuficiente(){
    printf ("Orcamento insuficiente! Retornando ao menu...");
}


/*

Funcoes de cadastro

*/

//Aqui sao chamadas as funcoes de leitura,
//feitas as verificacoes e sao passados os valores
//para as funcoes de manipulacao de lista.

Aluno* cadastraAluno(Aluno* aluno){
    char* matricula = leMatCod("a matricula", "aluno");
    if (buscaAluno(aluno, matricula) != NULL) {
        NaoJaCadastrado("aluno ja");
        return aluno;
    }
    
    char* nome = leNome("aluno");
    char* telefone = leTelefone();
    cadastroBemSucedido();
    return insereAluno(aluno, matricula, telefone, nome);
}


Professor* cadastraProfessor(Professor* professor){
    char* codigo = leMatCod("o codigo", "professor");
    if(buscaProfessor(professor, codigo) != NULL){
        NaoJaCadastrado("professor ja");
        return professor;
    }
    
    char* nome = leNome("professor");
    char* depto = leGenerico("digite o depto do professor: ", 50);

    cadastroBemSucedido();
    return insereProfessor(professor, codigo, nome, depto);
}


Projeto* cadastraProjeto(Projeto* projeto, Professor* professor){
    float orcamento_total;
    int tipo;
    Professor* aux;
    
    char* codigoProj = leMatCod("o codigo", "projeto");
    if (buscaProjeto(projeto, codigoProj) != NULL){
        NaoJaCadastrado("projeto ja");
        return projeto;
    }

    char* codigoProf = leMatCod("o codigo", "professor coordenador");
    if(buscaProfessor(professor, codigoProf) == NULL){
        NaoJaCadastrado("professor nao");
        return projeto;
    }

    char* descricao = leGenerico("insira a descricao do projeto(max 100 caracteres): ", 100);
    orcamento_total = leFloat("\nDigite o orcamento total para o projeto: R$");  
    tipo = leTipo(); 
    cadastroBemSucedido();
    return insereProjeto(projeto, codigoProj, descricao, orcamento_total, tipo, professor);
}


Vinculo* cadastraVinculo(Vinculo* vinculo, Projeto* projeto, Aluno* aluno){
    float bolsa_mensal;
    Aluno* auxA;
    Projeto* auxP;

    char* matricula = leMatCod("a matricula", "aluno a ser vinculado");
    auxA = buscaAluno(aluno, matricula);
    if (auxA == NULL) {
        NaoJaCadastrado("aluno nao");
        return vinculo;
    }

    char* codigo = leMatCod("o codigo", "projeto a ser vinculado"); 
    auxP = buscaProjeto(projeto, codigo);
    if(auxP == NULL){
        NaoJaCadastrado("projeto nao");
        return vinculo;
    }

    
    bolsa_mensal = leFloat("insira a bolsa mensal do aluno: R$");
    if (auxP->orcamento_atual < (12 * bolsa_mensal)){
        orcamentoInsuficiente();
        return vinculo;
    };

    cadastroBemSucedido();
    auxP->orcamento_atual = auxP->orcamento_total - (12 * bolsa_mensal);
    return insereVinculo(vinculo, auxA, auxP, bolsa_mensal);
}


/*

Funcoes de remocao

*/
//Aqui o vinculo e removido por meio de uma funcao de leitura e
//uma auxiliar de manipulacao de listas.
Vinculo* removeVinculoLista(Vinculo* vinculo, Vinculo* auxV){
    if (auxV == vinculo){
        vinculo = auxV->prox;
    }
    else{
        auxV->ant->prox = auxV->prox;
    }

    if (auxV->prox != NULL){
        auxV->prox->ant = auxV->ant;
    }

    free(auxV);
    cadastroBemSucedido();
    return vinculo;
}


Vinculo* removeVinculo(Vinculo* vinculo, Projeto* projeto, Aluno* aluno){
    //aqui o vinculo e entre aluno e projeto e desfeito, arrumando o orcamento.
    int meses;
    float bolsa_restante;
    Aluno* auxA;
    Projeto* auxP;
    Vinculo* auxV;

    char* matricula = leMatCod("a matricula", "aluno que sera desvinculado");
    auxA = buscaAluno(aluno, matricula);
    if (auxA == NULL) {
        NaoJaCadastrado("aluno nao");
        return vinculo;
    }

    char* codigo = leMatCod("o codigo", "projeto que sera desvinculado");
    auxP = buscaProjeto(projeto, codigo);
    if(auxP == NULL){
        NaoJaCadastrado("projeto nao");
        return vinculo;
    }

    auxV = buscaVinculo(vinculo, codigo, matricula);
    if(auxV == NULL){
        NaoJaCadastrado("vinculo nao");
        return vinculo;
    }
    printf("\nDigite quantos meses o aluno ficou vinculado no projeto: ");
    scanf("%d", &meses);
    setbuf(stdin, NULL);

    bolsa_restante = 12 * auxV->bolsa_mensal - meses * auxV->bolsa_mensal;
    auxP->orcamento_atual += bolsa_restante;
    removeVinculoLista(vinculo, auxV);
}


/*

Funcoes de liberacao

*/


//Todas seguem o mesmo principio: utiliza-se duas variaveis auxiliares, uma para apontar para a struct
//e outra para salvar o endereco do proximo valor, limpando em loop. E necessario limpar os campos de
//dentro da struct pois todas as cadeias de caracteres receberam malloc.
void liberaAluno(Aluno** aluno){
    Aluno* aux = *aluno;
    while(aux != NULL){
        Aluno *p = aux->prox;
        free(aux->matricula);
        free(aux->nome);
        free(aux->telefone);
        free(aux);
        aux = p;
    }
}

void liberaProfessor(Professor** professor){
    Professor* aux = *professor;
    while(aux != NULL){
        Professor *p = aux->prox;
        free(aux->codigo);
        free(aux->depto);
        free(aux->nome);
        free(aux);
        aux = p;
    }
}

void liberaProjeto(Projeto** projeto){
    Projeto* aux = *projeto;
    while(aux != NULL){
        Projeto *p = aux->prox;
        free(aux->codigo);
        free(aux->descricao);
        free(aux->tipo);
        free(aux);
        aux = p;
    }
}

void liberaVinculo(Vinculo** vinculo){
    Vinculo* aux = *vinculo;
    while(aux != NULL){
        Vinculo *p = aux->prox;
        free(aux);
        aux = p;
    }
}
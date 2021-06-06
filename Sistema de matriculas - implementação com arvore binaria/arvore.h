typedef struct no No;
typedef struct arvore Arvore;

Arvore * inicializa_arvore();

void cadastra_curso(Arvore* arvore);
void remove_curso(Arvore* arvore);

No* retorna_raiz(Arvore* arvore);

void chama_arv_imprime (No* pai);
void vinculo_imprime(Arvore* arvore);

void aluno_insere(Arvore* arvore);
void aluno_imprime(Arvore* arvore);
void aluno_remove(Arvore* arvore);

void chama_libera_arvore(No* no);
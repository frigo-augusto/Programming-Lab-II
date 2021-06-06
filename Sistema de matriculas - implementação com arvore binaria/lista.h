typedef struct lista Lista;

Lista* cria_lista();

void imprime_lista(Lista* no);
void imprime_lista_inteira(Lista* no, char* nome, char* centro);

Lista* cadastra_aluno(Lista* aluno);
Lista* aluno_remove_lista(Lista* no, int matricula);

void libera_lista(Lista* lista);
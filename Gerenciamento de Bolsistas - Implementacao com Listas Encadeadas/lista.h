typedef struct aluno Aluno;
typedef struct projeto Projeto;
typedef struct vinculo Vinculo;
typedef struct professor Professor;

void introduz_programa();
Aluno* criaAluno();
Projeto* criaProjeto();
Vinculo* criaVinculo();
Professor* criaProfessor();

Aluno* cadastraAluno(Aluno* aluno);
Projeto* cadastraProjeto(Projeto* projeto, Professor* professor);
Vinculo* cadastraVinculo(Vinculo* vinculo, Projeto* projeto, Aluno* aluno);
Professor* cadastraProfessor(Professor* professor);

Vinculo* removeVinculo(Vinculo* vinculo, Projeto* projeto, Aluno* aluno);

void imprimeAluno(Aluno* aluno);
void imprimeProjeto(Projeto* projeto, Vinculo* vinculo);
void imprimeProfessor(Professor* professor);
void liberaAluno(Aluno** aluno);
void liberaVinculo(Vinculo** vinculo);
void liberaProjeto(Projeto** projeto);
void liberaProfessor(Professor** professor);

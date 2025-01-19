#include <stdlib.h>

typedef struct {
  int *dados;
  int maxcap;
  int inicio, fim;
} fila;

fila *criaFila(int n);
void liberaFila(fila *f);
int consultaFila(fila *f, int modo);
int enfilera(fila *f, int chave);
int desenfilera(fila *f);
int filaVazia(fila *f);
int filaCheia(fila *f);
int vaziosNaFila(fila *f);

/*
  Cria uma fila com capacidade n, caso n seja positivo

  n: Capacidade da fila

  return: Ponteiro para a fila criada ou NULL, caso n seja negativo
 */
fila *criaFila(int n) {
  if (n > 0) {
    fila *nova = (fila *) malloc(sizeof(fila));
    nova->dados = (int *) malloc(n * sizeof(int));
    nova->maxcap = n;
    nova->inicio = nova->fim = -1;

    return nova;
  }
  return NULL;
}

/*
  Libera a memoria reservada para a fila

  f: Fila a ser liberada
 */
void liberaFila(fila *f) {
  if (f != NULL) {
    free(f->dados);
    free(f);
  }
}

/*
  Consulta o inicio ou o fim da fila, de acordo com o modo
  escolhido.

  f: Fila a ser consultada
  modo: 0=inicio, 1=fim

  return: Inicio ou fim da fila, de acordo com o modo, ou -1,
  caso a fila nao exista ou esteja vazia
 */
int consultaFila(fila *f, int modo) {
  if (f != NULL) {
    if (modo == 0 && f->inicio != -1)
      return f->dados[f->inicio];

    if (modo == 1 && f->fim != -1)
      return f->dados[f->fim];

    return -1;
  }
  return -1;
}


/*
  Insere um elemento no final da fila

  Como implementada estaticamente, precisamos lidar com a
  fila de uma maneira circular

  f: Fila em que a chave ira entrar
  chave: Chave a ser inserida

  return: indice em que a chave foi inserida (atual final da
  fila), ou -1, caso a fila nao exista ou esteja cheia
 */
int enfilera(fila *f, int chave) {
  if (f != NULL) {
    int prov = (f->fim + 1) % f->maxcap;
    if (prov != f->inicio) {
      f->dados[prov] = chave;
      f->fim = prov;

      if (f->inicio == -1)
        f->inicio = 0;
      
      return prov;
    }
    return -1;
  }
  return -1;
}

/*
  Desenfilera a fila e retorna o valor que saiu dela

  f: Fila que sera desenfileirada

  return: Valor removido
 */
int desenfilera(fila *f) {
  if (f != NULL && f->inicio != -1) {
    int resp = f->dados[f->inicio];
    if (f->inicio == f->fim) {
      f->inicio = f->fim = -1;
    } else
      f->inicio = (f->inicio + 1) % f->maxcap;

    return resp;
  }
  return -1;
}

/*
  Diz se a fila esta ou nao vazia

  f: Fila a ser consultada

  return: 1 caso a fila esteja vazia, 0 caso nao esteja
  e -1, caso a fila nao exista
 */
int filaVazia(fila *f) {
  if (f != NULL) {
    return (f->inicio == -1);
  }
  return -1;
}

/*
  Diz se a fila esta ou nao cheia

  f: Fila a ser consultada

  return: 1 caso a fila esteja cheia, 0 caso nao esteja
  e -1, caso a fila nao exista
 */
int filaCheia(fila *f) {
  if (f != NULL) {
    return ((f->fim + 1) % f->maxcap == f->inicio);
  }
  return -1;
}

/*
  Informa a quantidade de elementos que podem ser inseridos
  na fila

  f: Fila a ser consultada

  return: Quantidade de elementos que podem entrar na fila,
  ou -1, caso a fila nao exista
 */
int vaziosNaFila(fila *f) {
  if (f != NULL) {
    if (f->inicio == -1)
      return f->maxcap;
    else if (f->fim >= f->inicio)
      return f->maxcap - (f->fim - f->inicio + 1);
    else
      return f->inicio - f->fim - 1;
  }
  return -1;
}

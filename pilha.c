#include <stdlib.h>

typedef struct {
  int *dados;
  int maxcap;
  int topo;
} pilha;

pilha *criaPilha(int n);
void liberaPilha(pilha *p);
int consultaPilha(pilha *p);
int pilhaVazia(pilha *p);
float capacidadeUsada(pilha *p);
int empilhar(pilha *p, int chave);
int desempilhar(pilha *p);

/*
  Cria uma pilha com capacidade n

  A funcao aloca a memoria pra nova pilha e seu vetor de
  dados, seta a capacidade para o parametro passado e o topo
  para -1 (pilha vazia)

  n: capacidade da pilha

  return: ponteiro para pilha criada ou NULL, caso n <= 0
 */
pilha *criaPilha(int n) {
  if (n > 0) {
    pilha *nova = (pilha *) malloc(sizeof(pilha));
    nova->dados = (int *) malloc(n * sizeof(int));
    nova->maxcap = n;
    nova->topo = -1;
    return nova;
  }
  return NULL;
}

/*
  Libera o espaco alocado na memora da pilha

  p: Pilha a ser liberada
 */
void liberaPilha(pilha *p) {
  if (p != NULL) {
    free(p->dados);
    free(p);
  }
}

/*
  Consulta o topo da pilha

  p: Pilha a ser consultada

  return: Topo da pilha ou -1, caso a pilha esteja
  vazia
 */
int consultaPilha(pilha *p) {
  if (p->topo != -1) {
    return p->dados[p->topo];
  }
  return -1;
}

/*
  Diz se a pilha esta vazia

  p: Pilha a ser testada

  return: 1 caso a pilha esteja vazia, 0 caso nao esteja
  vazia e -1 caso a pilha nao exista
 */
int pilhaVazia(pilha *p) {
  if (p != NULL) {
    if (p->topo == -1)
      return 1;
    return 0;
  }
  return -1;
}

/*
  Diz se a pilha esta cheia

  p: Pilha a ser testada

  return: 1 caso a pilha esteja cheia, 0 caso nao esteja
  cheia e -1 caso a pilha nao exista
 */
int pilhaCheia(pilha *p) {
  if (p != NULL) {
    if (p->topo == p->maxcap - 1)
      return 1;
    return 0;
  }
  return -1;
}

/*
  Retorna o percentual de uso da pilha

  p: Pilha a ser consultada

  return: percentual de uso da pilha ou -1, caso a pilha nao exista
 */
float capacidadeUsada(pilha *p) {
  if (p != NULL)
    return (float) (p->topo+1) / p->maxcap;
  return -1;
}

/*
  Empilha uma chave na pilha

  p: Pilha em que a chave sera inserido
  chave: Chave a ser inserida

  return: Novo indice do topo da pilha ou -1, caso nao haja como
  empilhar
 */
int empilhar(pilha *p, int chave) {
  if (p != NULL && p->topo != p->maxcap - 1) {
    p->topo++;
    p->dados[p->topo] = chave;
    return p->topo;
  }
  return -1;
}

/*
  Retorna topo da pilha e o remove dela

  p: Pilha a ser desempilhada

  return: Chave desempilhada ou -1, caso nao tenha como
  desempilhar
 */
int desempilhar(pilha *p) {
  if (p != NULL && p->topo != -1) {
    int resp = p->dados[p->topo];
    p->topo--;
    return resp;
  }
  return -1;
}

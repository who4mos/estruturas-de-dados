#include <stdio.h>
#include <stdlib.h>

typedef struct {
  int *dados;
  int maxcap;
  int total;
} listaLinear;

listaLinear *criaLista(int n);
void liberaLista(listaLinear *l);

int busca(listaLinear *l, int chave);
int insereLista(listaLinear *l, int chave);
int insereListaRepetido(listaLinear *l, int chave);
int removeLista(listaLinear *l, int chave);

int buscaBinaria(listaLinear *l, int chave);
int buscaBinAlt(listaLinear *l, int chave);
int insereListaOrdenado(listaLinear *l, int chave);
int removeListaOrdenado(listaLinear *l, int chave);

void imprimeLista(listaLinear *l);


/*
  Cria lista linear com capacidade n

  Caso n > 0, a funcao aloca memoria para a lista e para o vetor
  de dados dentro dela, seta a capacidade para n e o total para 0.
  Retorna um ponteiro para a lista criada, ou para NULL, caso n <= 0.

  n: Capacidade da lista

  return: Ponteiro para lista criada, ou NULL, caso n <= 0
 */
listaLinear *criaLista(int n) {
  if (n > 0) {
    listaLinear *novo = (listaLinear *)malloc(sizeof(listaLinear));
    novo->dados = (int *)malloc(n * sizeof(int));
    novo->maxcap = n;
    novo->total = 0;

    return novo;
  } else
    return NULL;
}

/*
  Libera o espaco de memoria reservado por uma lista linear

  A funcao recebe uma lista e, caso ela nao seja nula, libera o vetor
  de dados interno a ela e depois a lista propriamente dita.

  l: Lista linear a ser liberada
 */
void liberaLista(listaLinear *l) {
  if (l != NULL) {
    free(l->dados);
    free(l);
  }
}

/*
  Busca por chave na lista e retorna seu indice

  A funcao percorre a lista comparando o elemento atual com a chave,
  quando o elemento atual for igual a chave, retorna o indice no qual isso
  aconteceu. Caso a lista nao exista, esteja vazia ou a chave nao seja igual
  a nenhum elemento, retorna -1.

  l: Lista linear que sera percorrida
  chave: Chave a ser buscada

  return: Inteiro contendo o indice da chave na lista, ou -1,
  caso a chave nao seja encontrada
 */
int busca(listaLinear *l, int chave) {
  if (l != NULL && l->total > 0) {
    for (int i = 0; i < l->total; i++)
      if (l->dados[i] == chave)
        return i;

    return -1;
  }
  return -1;
}

/*
  Insere chave na lista l, caso chave nao esteja presente

  A funcao busca pela chave na lista, caso esta nao exista, insere a
  chave na proxima posicao disponivel e a retorna, incrementando o valor
  do total, que tambem eh a proxima posicao disponivel.

  Caso a lista nao exista, nao haja mais capacidade, ou a chave ja
  exista na lista, retorna -1.

  l: Lista linear em que a chave sera inserida
  chave: Chave a ser inserida

  return: Indice em que a chave foi inserida, ou -1, caso a insercao
  nao tenha acontecido
 */
int insereLista(listaLinear *l, int chave) {
  if (l != NULL && l->total < l->maxcap) {
    int pos = busca(l, chave);
    if (pos == -1) {
      l->dados[l->total] = chave;
      return l->total++;
    }
    return -1;
  }
  return -1;
}

/*
  Insere chave na lista l

  A funcao insere a chave na proxima posicao disponivel e a retorna,
  incrementando o valor do total, que tambem eh a proxima posicao
  disponivel.

  Caso a lista nao exista ou nao haja mais capacidade, retorna -1.

  l: Lista linear em que a chave sera inserida
  chave: Chave a ser inserida

  return: Indice em que a chave foi inserida, ou -1, caso a insercao
  nao tenha acontecido
 */
int insereListaRepetido(listaLinear *l, int chave) {
  if (l != NULL && l->total < l->maxcap) {
    l->dados[l->total] = chave;
    return l->total++;
  }
  return -1;
}

/*
  Remove chave da lista l

  A funcao busca pela chave na lista, caso ela exista, a funcao vai
  trocando o valor da posicao a ser removida com a proxima ate o final,
  removendo a chave e tampando os possiveis buracos formados.

  Caso a lista nao exista ou a chave nao exista na lista, retorna -1.

  l: Lista linear em que a remocao deve ocorrer
  chave: Chave a ser removida

  return: Dado removido, ou -1, caso a remocao nao tenha ocorrido
 */
int removeLista(listaLinear *l, int chave) {
  if (l != NULL) {
    int pos = busca(l, chave);
    if (pos == -1)
      return -1; /* elemento nao existe */

    int resp = l->dados[pos];
    
    for (int i = pos; i < l->total - 1; i++)
      l->dados[i] = l->dados[i + 1];
    l->total--;
    return resp;
  }
  return -1;
}

/*
  Busca chave na lista l e retorna seu indice

  A funcao recebe uma lista linear ordenada e realiza uma busca 
  binaria pela chave.

  l: Lista linear em que a chave sera buscada
  chave: Chave a ser buscada

  return: Indice da chave buscada, ou -1, caso a chave nao seja 
  encontrada
 */
int buscaBinaria(listaLinear *l, int chave) {
  if (l != NULL && l->total > 0) {
    int inicio, fim;
    inicio = 0;
    fim = l->total - 1;

    while (inicio <= fim) {
      int meio = (inicio + fim) / 2;

      if (chave == l->dados[meio])
	return meio;
      else if (chave < l->dados[meio])
        fim = meio - 1;
      else
        inicio = meio + 1;
    }

    return -1;
  }
  return -1;
}

/*
  Busca por chave na lista l e retorna o indice em que a
  chave esta ou estaria

  Utiliza o algoritmo da busca binaria para procurar a chave na lista,
  caso nao encontrada retorna onde deveria estar.

  l: Lista linear em que a chave sera buscada
  chave: Chave a ser buscada

  return: Indice em que a chave se encontra ou deveria estar, ou -1,
  caso a lista nao exista
 */
int buscaBinAlt(listaLinear *l, int chave) {
  if (l != NULL) {
    if (l->total == 0)
      return 0;
    
    int inicio, fim;
    inicio = 0;
    fim = l->total - 1;

    while (inicio <= fim) {
      int meio = (inicio + fim) / 2;

      if (chave == l->dados[meio])
        return meio;
      else if (chave < l->dados[meio])
        fim = meio - 1;
      else
        inicio = meio + 1;
    }
    return inicio;
  }
  return -1;
}

/*
  Insere elemento na posicao correta na lista

  A funcao usa a funcao buscaBinAlt para determinar onde a
  chave deveria se encontrar, caso ela ja esteja la, retorna -1.
  Caso contrario, vai do final ate a posicao copiando os elementos,
  para abrir espaco, popula a posicao com a chave e retorna o indice
  e o retorna.

  l: Lista linear em que a insercao ocorrera
  chave: Chave a ser inserida

  return: Indice em que a chave foi inserida ou -1, caso a chave ja
  esteja na lista, a lista esteja cheia ou nao exista
 */
int insereListaOrdenado(listaLinear *l, int chave) {
  if (l != NULL && l->total < l->maxcap) {
    int pos = buscaBinAlt(l, chave);

    if (l->dados[pos] != chave) {
      for (int i = l->total; i > pos; i--)
	l->dados[i] = l->dados[i-1];

      l->dados[pos] = chave;
      l->total++;
      return pos;
    }
    return -1;
  }
  return -1;
}

/*
  Remove chave da lista linear l

  A funcao pega a posicao em que chave deveria estar na lista,
  caso ela exista, percorre da posicao ate o final sobrescrevendo os
  valores da casa atual com a proxima, removendo o elemento. No final,
  decrementamos o total da lista e retornamos o valor removido.

  Caso a lista nao exista ou esteja vazia, retorna -1.

  l: Lista linear em que a remocao sera realizazda
  chave: Chave a ser removida

  return: Valor da chave removida ou -1, caso a remocao nao ocorra

 */
int removeListaOrdenado(listaLinear *l, int chave) {
  if (l != NULL && l->total != 0) {
    int pos = buscaBinAlt(l, chave);
    if (l->dados[pos] == chave) {
      int resp = l->dados[pos];
      for (int i = pos; i < l->total - 1; i++)
        l->dados[i] = l->dados[i + 1];
      l->total--;
      return resp;
    }
    return -1;
  }
  return -1;
}

/*
  Imprime uma lista linear

  Percorre a lista e imprime seus elementos, caso a lista
  nao exista ou esteja vazia, mensagens correspondentes sao
  impressas

  l: Lista a ser impressa
 */
void imprimeLista(listaLinear *l) {
  if (l != NULL) {
    if (l->total == 0) {
      puts("Lista vazia!");
      return;
    }
    for (int i = 0; i < l->total; i++) {
      printf("%d", l->dados[i]);
      if (i != l->total - 1)
        printf("->");
      else
	putchar('\n');
    }
  } else
    puts("Lista inexistente!");
}

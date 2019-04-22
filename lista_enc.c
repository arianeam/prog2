#include <stdio.h>
#include <stdlib.h>

#include "lista_enc.h"
#include "no.h"

#define DEBUG

struct listas_enc
{
    no_t *cabeca;   /*!< Referência da cabeça da lista encadeada: primeiro elemento. */
    no_t *cauda;    /*!< Referência da cauda da lista encadeada: último elemento. */
    int tamanho;    /*!< Tamanho atual da lista. */
};

/**
  * @brief  Cria uma nova lista encadeada vazia.
  * @param	Nenhum
  *
  * @retval lista_enc_t *: ponteiro (referência) da nova lista encadeada.
  */
lista_enc_t *criar_lista_enc (void)
{
    lista_enc_t *p = malloc(sizeof(lista_enc_t));

    if (p == NULL)
    {
        perror("cria_lista_enc:");
        exit(EXIT_FAILURE);
    }

    p->cabeca = NULL;
    p->cauda = NULL;
    p->tamanho = 0;

    return p;
}


/**
  * @brief  Obtém a referência do início (cabeça) da lista encadeada.
  * @param	lista: lista que se deseja obter o início.
  *
  * @retval no_t *: nó inicial (cabeça) da lista.
  */
no_t *obter_cabeca(lista_enc_t *lista)
{
    return lista->cabeca;
}

/**
  * @brief  Adiciona um nó de lista no final.
  * @param	lista: lista encadeada que se deseja adicionar.
  * @param  elemento: nó que será adicionado na cauda.
  *
  * @retval Nenhum
  */
void add_cauda(lista_enc_t *lista, no_t* elemento)
{
    if (lista == NULL || elemento == NULL)
    {
        fprintf(stderr,"add_cauda: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }

#ifdef DEBUG
    printf("Adicionando %p --- tamanho: %d\n", elemento, lista->tamanho);
#endif // DEBUG

    //lista vazia
    if (lista->tamanho == 0)
    {
#ifdef DEBUG
        printf("add_cauda: add primeiro elemento: %p\n", elemento);
#endif // DEBUG

        lista->cauda = elemento;
        lista->cabeca = elemento;
        lista->tamanho++;

        desligar_no(elemento);
    }
    else
    {
        // Remove qualquer ligacao antiga
        desligar_no(elemento);
        // Liga cauda da lista com novo elemento
        ligar_nos(lista->cauda, elemento);

        lista->cauda = elemento;
        lista->tamanho++;
    }
}

//------------------------

void add_cabeca(lista_enc_t *lista, no_t* elemento)
{
    if (lista == NULL || elemento == NULL)
    {
        fprintf(stderr,"add_cauda: ponteiros invalidos");
        exit(EXIT_FAILURE);
    }



#ifdef DEBUG
    printf("Adicionando %p --- tamanho: %d\n", elemento, lista->tamanho);
#endif // DEBUG

    //lista vazia
    if (lista->tamanho == 0)
    {
#ifdef DEBUG
        printf("add_cabeca: add primeiro elemento: %p\n", elemento);
#endif // DEBUG

        lista->cauda = elemento;
        lista->cabeca = elemento;
        lista->tamanho++;

        desligar_no(elemento);
    }
    else
    {
        // Liga cauda da lista com novo elemento
        ligar_nos(elemento, lista->cabeca);

        lista->cabeca = elemento;
        lista->tamanho++;
    }
}

//-----------------------------------------

void remover_cauda(lista_enc_t *lista)
{

    if (lista == NULL )
    {
        perror("remover_cauda: ");
        exit(EXIT_FAILURE);
    }

    no_t* elemento = obter_anterior(lista->cauda) ;
    lista->cauda = elemento;
    desligar_no_proximo(elemento);
    lista->tamanho--;


    if (lista->tamanho <= 0)
    {
        lista->cabeca = NULL;
        lista->cauda = NULL;
        lista->tamanho = 0;
    }


}

//--------------------------

void remover_cabeca(lista_enc_t *lista)
{

    if (lista == NULL )
    {
        perror("remover_cabeca: ");
        exit(EXIT_FAILURE);
    }

    no_t* elemento = obter_proximo(lista->cabeca) ;
    lista->cabeca = elemento;
    desligar_no_anterior(elemento);
    lista->tamanho--;


    if (lista->tamanho <= 0)
    {
        lista->cabeca = NULL;
        lista->cauda = NULL;
        lista->tamanho = 0;
    }


}

//-----------------------
int vazia (lista_enc_t* lista)
{
    if (lista->tamanho == 0)
    {
        printf("lista vazia");
        return 0;
    }
    else
        return lista->tamanho;
}

int tamanho(lista_enc_t* lista)
{
    int tamanho;
    tamanho = vazia (lista);
    return tamanho;

}
void remove_pos(int posicao, lista_enc_t* lista)
{
    int teste,n;
    teste = tamanho(lista);
    teste = teste/2;


    if(posicao<= teste)
    {
        no_t* elemento = lista->cabeca;

        for(n=1; n<posicao; n++)
        {
            elemento = obter_proximo(elemento);
        }
        no_t* elemento_anterior = obter_anterior(elemento);
        no_t* elemento_proximo = obter_proximo(elemento);
        desligar_no(elemento);
        lista->tamanho--;
        ligar_nos(elemento_anterior,elemento_proximo);


    }
    else
    {
        no_t* elemento = lista->cauda;
        for(n=tamanho(lista); n>posicao; n--)
        {
            elemento = obter_anterior(lista->cauda);
        }
        no_t* elemento_anterior = obter_anterior(elemento);
        no_t* elemento_proximo = obter_proximo(elemento);
        desligar_no(elemento);
        lista->tamanho--;
        ligar_nos(elemento_anterior,elemento_proximo);

    }
}


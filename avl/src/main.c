#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib.h"

typedef struct tnode
{
	char nome[32];
	int direita,esquerda,inicio,pDado;
}node;

typedef struct treg
{
	int  indice;
	char nome[30];
	char telefone[30];
}registro;

node carregar_no(FILE* arquivo,int posicao)
{
	node retorno;
	fseek ( arquivo , (posicao*sizeof(node)) , SEEK_SET );
	fread(&retorno, sizeof(node),1,arquivo);
	return retorno;
}

registro carregar_registro(FILE* arquivo,int posicao)
{
	registro retorno;
	fseek (arquivo, (posicao*sizeof(registro)), SEEK_SET);
	fread (&retorno, sizeof(registro),1,arquivo);
	return retorno;
}

void gravar_no(FILE* arquivo,int posicao,node *gravar)
{
	int m;

	fseek(arquivo, posicao, SEEK_END);
	fgetpos(arquivo,&m);
	if(m>=sizeof(node))
		gravar->inicio=m/sizeof(node);
	else
		gravar->inicio=0;
	fwrite(gravar, sizeof(node),1,arquivo);
}

void gravar_registro(FILE* arquivo,int posicao, registro *gravar)
{
	int m;
	
	fseek( arquivo , posicao , SEEK_END );
	fgetpos (arquivo,&m);
	if(m>=sizeof(registro))
		gravar->indice=m/sizeof(registro);
	else
		gravar->indice=0;
	fwrite(gravar, sizeof(registro),1,arquivo);
}


void inserir(FILE* arvore, FILE* dados)
{

	node pRaiz,pRaiz1;
	struct registro contato;
	char bContato[30];

	pRaiz.esquerda = -1;
	pRaiz.direita = -1;
	printf("digite o nome e o telefone\n");
	scanf("%s",pRaiz.nome);
	scanf("%s",contato.telefone);
	strcpy (contato.nome, pRaiz.nome);


	gravar_registro(dados,0,&contato);
	pRaiz.pDado=contato.indice;
	gravar_no(arvore,0,&pRaiz);
	pRaiz1=carregar_no(arvore,0);
	 // atualizando_No(arvore,pRaiz1, contato,pRaiz);

}

void inicializar(FILE *arvore)
{
	node inicio;

	////inicio.nome=("inicio");
	inicio.pDado=-1;
	inicio.esquerda=-1;
	inicio.direita=-1;
	gravar_no(arvore,0,&inicio);
}

int busca(FILE *arvore, int raiz, char *folha)
{
	node aux;
	int comp;

	aux = carregar_no(arvore, raiz);

	if(raiz==-1) {return aux.inicio;}

	else
	{
		if (comp = strcmp(aux.nome,*folha)==0) return (raiz);
		else if (comp = strcmp(aux.nome,*folha)>0) busca(arvore, aux.esquerda, folha);
		else if (comp = strcmp(aux.nome,*folha)<0) busca(FILE *arvore, aux.direita, folha);
	}
}

//COMO ASSIM ISSO AQUI TA SOLTO ????
	int aux,aux1,aux3;
	if(pRaiz==NULL)
		return;
	if((pRaiz->esquerda == -1)||(pRaiz->direita == -1))
	{
		if (pRaiz->esquerda == -1)
		{
			pRaiz->esquerda=add->inicio;
			gravar_no(arvore,pRaiz->inicio,pRaiz);
		}
		else
		{
			pRaiz->direita=add->inicio;
			gravar_no(arvore,pRaiz->inicio,pRaiz);
			return;
		}
	}

	else
	{
		aux3=strcmp (pRaiz->nome, contato.nome);
		if(aux3 > 0)
		{
			aux=(*pRaiz).esquerda;
			*pRaiz=carregar_no(arvore,aux);
			atualizando_No(arvore,pRaiz,contato,add);
		}
		else
		{
			aux1=(*pRaiz).direita;
			*pRaiz=carregar_no(arvore,aux);
			atualizando_No(arvore,pRaiz,contato,add);

		}

	  }
 }




int main()
{

	FILE *arvore,*dados;
	arvore=fopen("arvore.bin","a+b");
	dados=fopen("dados.bin","a+b");

	struct  registro contato;
	node variavel;
	int numero;

	inserir(arvore,dados);
	scanf("%d",&numero);
	variavel=carregar_no(arvore,numero);
	contato=carregar_registro(dados,variavel.pDado);
	printf("%s\n%d\n%d\n%d\n\n\%s\n\n%s",variavel.nome,variavel.inicio,variavel.direita,variavel.esquerda,contato.nome,contato.telefone);
	getchar();

}
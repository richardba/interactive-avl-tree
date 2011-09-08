#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef
  struct NO{
  char nome[33];
  int direita,esquerda,inicio,pDado;}
  NO;

  struct registro{
    int  indice;
    char nome[33];
    char telefone[33];
  }registro;

NO carregar_no(FILE* arquivo,int posicao){

NO retorno;
fseek ( arquivo , (posicao*sizeof(NO)) , SEEK_SET );
fread(&retorno, sizeof(NO),1,arquivo);
return retorno;
}

struct registro carregar_registro(FILE* arquivo,int posicao){

struct registro retorno;
fseek ( arquivo , (posicao*sizeof(struct registro)) , SEEK_SET );
fread(&retorno, sizeof(struct registro),1,arquivo);
return retorno;
}

void gravar_no(FILE* arquivo,int posicao,NO *gravar,int load){
 int m;

 if(load==0)
  rewind(arquivo);

  fseek ( arquivo , posicao*sizeof(NO) , load);
if(load!=0){
fgetpos (arquivo,&m);
  if(m>=sizeof(NO))
    gravar->inicio=m/sizeof(NO);
  else
    gravar->inicio=0;
}
fwrite(gravar, sizeof(NO),1,arquivo);
}

void gravar_registro(FILE* arquivo,int posicao,struct registro *gravar){
 long long m;

fseek ( arquivo , posicao , SEEK_END );
fgetpos (arquivo,&m);
  if(m>=sizeof(registro))
    gravar->indice=m/sizeof(registro);
  else
    gravar->indice=0;
fwrite(gravar, sizeof(registro),1,arquivo);
}


 void inserir(FILE* arvore,FILE* dados ){

  NO pRaiz,pRaiz1,apagar;
  struct registro contato;
  int aux,comp;

   pRaiz.inicio=0;
   pRaiz.esquerda = -1;
   pRaiz.direita = -1;
   printf("digite o nome e o telefone\n");
   fflush(stdin);
   scanf("%32[^\n]s",pRaiz.nome);
   fflush(stdin);
   scanf("%32[^\n]s",contato.telefone);
   strcpy (contato.nome, pRaiz.nome);

   pRaiz1=carregar_no(arvore,0);

   if((pRaiz1.direita!=-1)&&(pRaiz1.direita!=-1))
   aux=busca(arvore,pRaiz1.direita,contato.nome);
    else
      aux=-1;

  if(aux==-1) {

     gravar_registro(dados,0,&contato);
     pRaiz.pDado=contato.indice;
     gravar_no(arvore,0,&pRaiz,2);
     //pRaiz1=carregar_no(arvore,0);

     pRaiz1.esquerda=pRaiz.inicio;
     pRaiz1.direita=pRaiz.inicio;
     gravar_no(arvore,0,&pRaiz1,0);
  }
  else{
      if((comp=strcmp(pRaiz1.nome,contato.nome)) !=0)
   {
     gravar_registro(dados,0,&contato);
     pRaiz.pDado=contato.indice;
     gravar_no(arvore,0,&pRaiz,2);

     pRaiz1=carregar_no(arvore,aux);
   }
   if((comp=strcmp(pRaiz1.nome,contato.nome)) <0)
   {
     pRaiz1.esquerda=pRaiz.inicio;

     }
    else{
    if((comp=strcmp(pRaiz1.nome,contato.nome))>0)
     pRaiz1.direita=pRaiz.inicio;
     }
     gravar_no(arvore,pRaiz1.inicio,&pRaiz1,0);
  }

  }


void inicializar(FILE *arvore){
NO inicio;
strcpy(inicio.nome,"inicio");
inicio.inicio=0;
inicio.pDado=-1;
inicio.esquerda=-1;
inicio.direita=-1;
gravar_no(arvore,0,&inicio,0);
}



int busca(FILE *arvore, int raiz, char *folha){
NO aux;
int comp;

aux = carregar_no(arvore, raiz);
comp=strcmp(aux.nome,folha);
   if (comp==0)
    return (raiz);
   if ( comp<0){
       if(aux.esquerda==-1)
           return aux.inicio;
    else
        busca(arvore, aux.esquerda, folha);
   }
   if (comp>0){
         if(aux.direita==-1)
           return aux.inicio;
    else
     busca(arvore, aux.direita, folha);
   }
}


void pesquisa(FILE *arvore,FILE *dados){

int aux;
char nome[33];
NO pRaiz;
struct registro contato;
system("cls");
printf("BUSCA NA AGENDA\n\n\n");
printf("Digite o nome?\n");
fflush(stdin);
scanf("%32[^\n]s",&nome);
pRaiz=carregar_no(arvore,0);
aux=busca(arvore,pRaiz.direita,&nome);
pRaiz=carregar_no(arvore,aux);
if(strcmp(pRaiz.nome,nome)==0)
  {
  contato=carregar_registro(dados,pRaiz.pDado);
  printf("NOME: %s \n\nTELEFONE: %s \n",contato.nome,contato.telefone);
  }
else
  printf("NOME NAO ENCONTRADO NA AGENDA\n");

}



int main()
{
FILE *arvore,*dados;
int aux,n;
struct  registro contato;
NO variavel;


 arvore=fopen("arvore.bin","r+b");
 dados=fopen("dados.bin","r+b");


 variavel=carregar_no(arvore,0);
 if(!strcmp(variavel.nome,"inicio")==0)
  inicializar(arvore);



 int numero=30;
 n=0;
while(n!=4){
inserir(arvore,dados);
n++;}

//pesquisa(arvore,dados);
while(numero!=-1){
    scanf("%d",&numero);

variavel=carregar_no(arvore,numero);
contato=carregar_registro(dados,variavel.pDado);
printf("%s\n%d\n%d\n%d\n\n\%s\n\n%s\n________________________________\n",variavel.nome,variavel.inicio,variavel.direita,variavel.esquerda,contato.nome,contato.telefone);


}
getchar();


















}

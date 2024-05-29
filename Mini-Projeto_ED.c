#include <locale.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>

// Declarando a estrutura com typedef
typedef struct No {
    int RGM;
    char nome[100];
    struct No *esquerda, *direita;
} t_no;

// Função para criar um novo nó 
t_no* novoNo(int RGM, char *nome) {
    t_no* temp = (t_no*)malloc(sizeof(t_no));
    temp->RGM = RGM;
    strcpy(temp->nome, nome);
    temp->esquerda = temp->direita = NULL;
    return temp;
}

// Função para inserir um novo nó na árvore
t_no* inserir(t_no* no, int RGM, char *nome) {
    if (no == NULL) return novoNo(RGM, nome);
    if (RGM < no->RGM)
        no->esquerda = inserir(no->esquerda, RGM, nome);
    else if (RGM > no->RGM)
        no->direita = inserir(no->direita, RGM, nome);
    return no;
}

// Função para encontrar o nó de menor valor 
t_no* noMenor(t_no* no) {
    t_no* atual = no;
    while (atual && atual->esquerda != NULL)
        atual = atual->esquerda;
    return atual;
}

// Função para deletar um nó na árvore
t_no* deletar(t_no* raiz, int RGM) {
    if (raiz == NULL) return raiz;
    if (RGM < raiz->RGM) {
        raiz->esquerda = deletar(raiz->esquerda, RGM);
    } else if (RGM > raiz->RGM) {
        raiz->direita = deletar(raiz->direita, RGM);
    } else {
        if (raiz->esquerda == NULL) {
            t_no* temp = raiz->direita;
            free(raiz);
            return temp;
        } else if (raiz->direita == NULL) {
            t_no* temp = raiz->esquerda;
            free(raiz);
            return temp;
        }
        t_no* temp = noMenor(raiz->direita);
        raiz->RGM = temp->RGM;
        strcpy(raiz->nome, temp->nome);
        raiz->direita = deletar(raiz->direita, temp->RGM);
    }
    return raiz;
}

// Função para pesquisar um nó na árvore
t_no* pesquisar(t_no* raiz, int RGM) {
    if (raiz == NULL || raiz->RGM == RGM)
        return raiz;
    if (raiz->RGM < RGM)
        return pesquisar(raiz->direita, RGM);
    return pesquisar(raiz->esquerda, RGM);
}

// Função para percorrer a árvore(preOrdem)
void preOrdem(t_no* raiz) {
    if (raiz != NULL) {
        printf("%d %s\n", raiz->RGM, raiz->nome);
        preOrdem(raiz->esquerda);
        preOrdem(raiz->direita);
    }
}

// Função para percorrer a árvore(inOrdem)
void inOrdem(t_no* raiz) {
    if (raiz != NULL) {
        inOrdem(raiz->esquerda);
        printf("%d %s\n", raiz->RGM, raiz->nome);
        inOrdem(raiz->direita);
    }
}

// Função para percorrer a árvore(posOrdem)
void posOrdem(t_no* raiz) {
    if (raiz != NULL) {
        posOrdem(raiz->esquerda);
        posOrdem(raiz->direita);
        printf("%d %s\n", raiz->RGM, raiz->nome);
    }
}

// Função para ler dados do arquivoArmazenar e criar a árvore
t_no* lerArquivo(char *arquivoArmazenar) {
    FILE *arquivo = fopen(arquivoArmazenar, "r");
    if (arquivo == NULL) {
        printf("Erro ao abrir o arquivoArmazenar\n");
        return NULL;
    }
    t_no* raiz = NULL;
    int RGM;
    char nome[100];

    while (fscanf(arquivo, "%d %[^\n]", &RGM, nome) != EOF) {
        raiz = inserir(raiz, RGM, nome);
    }
    fclose(arquivo);
    return raiz;
}
    //Função para posicionar o cursor de texto.
    void gotoxy(int coluna, int linha) {
 
   COORD point;
   point.X = coluna;
   point.Y = linha;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), point);
}
    //Função para exibir graficamente usando um percuso pre-Ordem
    void exibirGraficamente(t_no* raiz, int col, int lin, int desloc) {

    
    if (raiz == NULL)
        return; // condicao de parada do procedimento recursivo
        
    gotoxy(col,lin);
    
    printf("%d - %s", raiz->RGM, raiz->nome);
    if (raiz->esquerda != NULL)
        exibirGraficamente(raiz->esquerda,col-desloc,lin+2,desloc/2+1);
        
    if (raiz->direita != NULL)
        exibirGraficamente(raiz->direita,col+desloc,lin+2,desloc/2+1);
}




int main() {
	setlocale(0, "Portuguese");
    t_no *raiz = NULL;
    int opcao, RGM;
    char nome[100];
    char arquivoArmazenar[] = "dados.txt"; 

    raiz = lerArquivo(arquivoArmazenar);

    do {
        printf("LUIZ SANTINO, PAULO MARIANO FERNANDES, TIAGO LEAL, LUCAS\n");
        printf("DISCIPLINA: ESTRUTURA DE DADOS I\n");
        printf("PROFESSOR: LEANDRO MELO\n\n");
        printf("EDITOR DE ARVORE\n\n");
        printf("1 - INSERIR - fornecer RGM e Nome:\n");
        printf("2 - REMOVER UM NO - fornecer o RGM a remover:\n");
        printf("3 - PESQUISAR - fornecer o RGM a pesquisar:\n");
        printf("4 - ESVAZIAR A ARVORE:\n");
        printf("5 - EXIBIR A ARVORE  -  quatro opcoes: PRE, IN , POS ou Graficamente:\n");
        printf("0 - SAIR:\n\n");
        printf("DIGITE SUA OPCAO: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                system("cls");
                printf("Digite o RGM: ");
                scanf("%d", &RGM);
                printf("Digite o Nome: ");
                scanf(" %[^\n]", nome);
                raiz = inserir(raiz, RGM, nome);
                system("cls");
                printf(" *** INSERÇÃO REALIZADA COM SUCESSO! ***\n\n");
                break;
            case 2:
                system("cls");
                printf("Digite o RGM a remover: ");
                scanf("%d", &RGM);
                raiz = deletar(raiz, RGM);
                system("cls");
                printf(" *** NÓ REMOVIDO COM SUCESSO! ***\n\n");
                break;
            case 3:
                system("cls");
                printf("Digite o RGM a pesquisar: ");
                scanf("%d", &RGM);
                t_no *resultado = pesquisar(raiz, RGM);
                if (resultado != NULL) {
                    system("cls");
                    printf("Aluno encontrado: %d - %s\n", resultado->RGM, resultado->nome);
                } else {
                    printf("Aluno não encontrado.\n");
                }
                break;
            case 4:
                system("cls");
                printf("Deseja realmente limpar a árvore? \n");
                printf("1-sim \n2-não\n");
                int op;
                scanf("%d",&op);
                if(op==1){
                while (raiz != NULL) {
                    raiz = deletar(raiz, raiz->RGM);
                }
                system("cls");
                printf("Arvore esvaziada.\n");}
                else if(op==2){
                    system("cls");
                    break;}
                else{
                        printf("Opção inválida!");}
                break;
            case 5:
                system("cls");
                printf("Escolha a opcao de exibicao (1-PRE, 2-IN, 3-POS, 4-GRAFICAMENTE): ");
                int exibirOpcao;
                scanf("%d", &exibirOpcao);
                if (exibirOpcao == 1) {
                    system("cls");
                    printf(" *** VISUALIZANDO EM PRÉ ORDEM ***\n\n");
                    preOrdem(raiz);
                } else if (exibirOpcao == 2) {
                    system("cls");
                    printf(" *** VISUALIZANDO EM IN ORDEM ***\n\n");
                    inOrdem(raiz);
                } else if (exibirOpcao == 3) {
                    system("cls");
                    printf(" *** VISUALIZANDO EM PÓS ORDEM ***\n\n");
                    posOrdem(raiz);
                }  else if (exibirOpcao == 4) {
                    system("cls");
                    printf(" *** VISUALIZANDO O DESENHO DA ARVORE ***\n\n");
                    exibirGraficamente(raiz, 10 , 5 , 10); printf("\n");  
                } else {
                    printf("Opcao invalida!\n");
                }
                break;
            case 0:
                printf("Obrigado por usar nossa aplicacao! SAINDO...\n");
                break;
            default:
                printf("Opcao invalida, tente novamente!\n");
        }
        printf("\n");
    } while (opcao != 0);

    return 0;
}

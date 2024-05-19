#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Declarando a estrutura com typedef
typedef struct Node {
    int RGM;
    char nome[100];
    struct Node *left, *right;
} Node;

// Função para criar um novo nó
Node* novoNode(int RGM, char *nome) {
    Node* temp = (Node*)malloc(sizeof(Node));
    temp->RGM = RGM;
    strcpy(temp->nome, nome);
    temp->left = temp->right = NULL;
    return temp;
}

// Função para inserir um novo nó na árvore
Node* inserir(Node* node, int RGM, char *nome) {
    if (node == NULL) return novoNode(RGM, nome);
    if (RGM < node->RGM)
        node->left = inserir(node->left, RGM, nome);
    else if (RGM > node->RGM)
        node->right = inserir(node->right, RGM, nome);
    return node;
}

// Função para encontrar o nó de menor valor (usado na remoção de nós)
Node* minValueNode(Node* node) {
    Node* current = node;
    while (current && current->left != NULL)
        current = current->left;
    return current;
}

// Deleta um nó da árvore
Node* deletar(Node* raiz, int RGM) {
    if (raiz == NULL) return raiz;
    if (RGM < raiz->RGM) {
        raiz->left = deletar(raiz->left, RGM);
    } else if (RGM > raiz->RGM) {
        raiz->right = deletar(raiz->right, RGM);
    } else {
        if (raiz->left == NULL) {
            Node* temp = raiz->right;
            free(raiz);
            return temp;
        } else if (raiz->right == NULL) {
            Node* temp = raiz->left;
            free(raiz);
            return temp;
        }
        Node* temp = minValueNode(raiz->right);
        raiz->RGM = temp->RGM;
        strcpy(raiz->nome, temp->nome);
        raiz->right = deletar(raiz->right, temp->RGM);
    }
    return raiz;
}

// Função para pesquisar um nó na árvore
Node* pesquisar(Node* raiz, int RGM) {
    if (raiz == NULL || raiz->RGM == RGM)
        return raiz;
    if (raiz->RGM < RGM)
        return pesquisar(raiz->right, RGM);
    return pesquisar(raiz->left, RGM);
}

// Funções para percorrer a árvore
void preOrder(Node* raiz) {
    if (raiz != NULL) {
        printf("%d %s\n", raiz->RGM, raiz->nome);
        preOrder(raiz->left);
        preOrder(raiz->right);
    }
}

void inOrder(Node* raiz) {
    if (raiz != NULL) {
        inOrder(raiz->left);
        printf("%d %s\n", raiz->RGM, raiz->nome);
        inOrder(raiz->right);
    }
}

void postOrder(Node* raiz) {
    if (raiz != NULL) {
        postOrder(raiz->left);
        postOrder(raiz->right);
        printf("%d %s\n", raiz->RGM, raiz->nome);
    }
}

// Função para ler dados do arquivo e criar a árvore
Node* loadTreeFromFile(char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("Erro ao abrir o arquivo\n");
        return NULL;
    }
    Node* raiz = NULL;
    int RGM;
    char nome[100];

    while (fscanf(file, "%d %[^\n]", &RGM, nome) != EOF) {
        raiz = inserir(raiz, RGM, nome);
    }
    fclose(file);
    return raiz;
}

// Função principal
int main() {
    Node *raiz = NULL;
    int opcao, RGM;
    char nome[100];
    char filename[] = "dados.txt"; // Nome do arquivo com os dados dos alunos

    raiz = loadTreeFromFile(filename);

    do {
        printf("LUIZ SANTINO, PAULO MARIANO, TIAGO LEAL, LUCAS\n");
        printf("DISCIPLINA: ESTRUTURA DE DADOS I\n");
        printf("PROFESSOR: LEANDRO MELO\n\n");
        printf("EDITOR DE ARVORE\n\n");
        printf("1 - INSERIR ... fornecer RGM e Nome:\n");
        printf("2 - REMOVER UM NO ... fornecer o RGM a remover:\n");
        printf("3 - PESQUISAR ... fornecer o RGM a pesquisar:\n");
        printf("4 - ESVAZIAR A ARVORE:\n");
        printf("5 - EXIBIR A ARVORE ... tres opcoes: PRE, IN ou POS:\n");
        printf("0 - SAIR:\n\n");
        printf("DIGITE SUA OPCAO: ");
        scanf("%d", &opcao);

        switch (opcao) {
            case 1:
                printf("Digite o RGM: ");
                scanf("%d", &RGM);
                printf("Digite o Nome: ");
                scanf(" %[^\n]", nome);
                raiz = inserir(raiz, RGM, nome);
                break;
            case 2:
                printf("Digite o RGM a remover: ");
                scanf("%d", &RGM);
                raiz = deletar(raiz, RGM);
                break;
            case 3:
                printf("Digite o RGM a pesquisar: ");
                scanf("%d", &RGM);
                Node *result = pesquisar(raiz, RGM);
                if (result != NULL) {
                    printf("Aluno encontrado: %d %s\n", result->RGM, result->nome);
                } else {
                    printf("Aluno não encontrado.\n");
                }
                break;
            case 4:
                while (raiz != NULL) {
                    raiz = deletar(raiz, raiz->RGM);
                }
                printf("Arvore esvaziada.\n");
                break;
            case 5:
                printf("Escolha a opcao de exibicao (1-PRE, 2-IN, 3-POS): ");
                int exibirOpcao;
                scanf("%d", &exibirOpcao);
                if (exibirOpcao == 1) {
                    preOrder(raiz);
                } else if (exibirOpcao == 2) {
                    inOrder(raiz);
                } else if (exibirOpcao == 3) {
                    postOrder(raiz);
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

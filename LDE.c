#include <stdio.h>
#include <stdlib.h>

typedef struct {
	struct lde *esq;
	float chave;
	struct lde *dir;
}lde;

// FUNÇÕES
void print_menu();
lde *insert_valor(lde *p, float valor);
void print_list(lde *p);
lde *search_valor(lde *p, float valor);
lde *remove_valor(lde *p, float valor);
int count_nodes(lde *p);
float *copy_to_vector(lde *p, int TAM);

int main()
{
	lde *lista = NULL;

	int option = 0;
	float valor;

	while(option != 7) {
		print_menu();
		scanf("%d", &option);
		switch(option) {
			case 1:
				printf("Inserir valor: ");
				scanf("%f", &valor);
				lista = insert_valor(lista, valor);
				break;
			case 2:
				print_list(lista);
				break;
			case 3:
				printf("Buscar valor: ");
				scanf("%f", &valor);
				search_valor(lista, valor);
				break;
			case 4:
				printf("Remover valor: ");
				scanf("%f", &valor);
				lista = remove_valor(lista, valor);
				printf("Lista: ");
				print_list(lista);
				break;
			case 5:
				printf("Número de nós: %d\n", count_nodes(lista));
				break;
			case 6:
				int TAM, i;
				float *v;
				TAM = count_nodes(lista);
				v = copy_to_vector(lista, TAM);
				for(i=0; i<TAM; i++)
					printf("%.2f\t", *(v + i));
				printf("\n");
				break;
			case 7:
				return 1;
			default:
				printf("Invalid Option. Try again.\n");
		}
		printf("\n");
	}

	return 0;
}

void print_menu() {
	printf("1-Insere valor\n2-Imprimir lista\n3-Buscar elemento\n4-Remover valor da lista\n5-Contar nós\n6-Gerar cópia da lista em vetor\n7-Sair\nEscolha sua opção: ");
}

lde *insert_valor(lde *p, float valor) {
	lde *new, *q;
	if(!p) {
		new = (lde *)malloc(sizeof(lde));
		new->chave = valor;
		new->esq = new->dir = NULL;
		return new;
	}
	q = p;
	while(q->dir)
		q = q->dir;
	new =(lde *)malloc(sizeof(lde));
	new->chave = valor;
	q->dir = new;
	new->esq = q;
	new->dir = NULL;
	return p;
}

void print_list(lde *p) {
	if(p) {
		while(p) {
			printf("%.2f\t", p->chave);
			p = p->dir;
		}
	}
	else
		printf("Lista vazia.");
	printf("\n");
}

lde *search_valor(lde *p, float valor) {
	if(!p) {
		printf("Lista vazia.\n");
		return NULL;
	}
	lde *q;
	q = p;
	while(q) {
		if(valor == q->chave){
			printf("Chave encontrada.\n");
			return q;
		}
		q = q->dir;
	}
	printf("Chave não encontrada.\n");
	return NULL;
}

lde *remove_valor(lde *p, float valor) {
	lde *q, *ant, *post;
	q = p;
	if(!p)
		return NULL;
	while(q) {
		ant = q->esq;
		post = q->dir;
		if(q->chave == valor) {
			if(!ant) {
				if(!post) {
					free(q);
					return NULL;
				}
				post->esq = NULL;
				p = post;
				free(q);
				return p;
			}
			if(!post) {
				ant->dir = NULL;
				free(q);
				return p;
			}
			ant->dir = post;
			post->esq = ant;
			free(q);
			return p;
		}
		q = q->dir;
	}
	printf("Valor não encontrado.\n");
	return p;
}

int count_nodes(lde *p) {
	int count = 0;
	while(p) {
		count++;
		p = p->dir;
	}
	return count;
}

float *copy_to_vector(lde *p, int TAM) {
	float *v;
	int i = 0;
	v = (float *)malloc(sizeof(float) * TAM);
	if(!v)
		printf("Vetor vazio.\n");
	while(p) {
		v[i] = p->chave;
		p = p->dir;
		i++;
	}
	return v;
}


#include <stdio.h>
#include <stdlib.h>
#define maxvertex 50

typedef struct graphnode
{
	int vertex;
	struct graphnode* link;
} graphnode;

typedef struct graphtype
{
	int n;
	graphnode* list[maxvertex];
} graphtype;

void graph_init(graphtype* g)
{
	g->n = 0;
	for (int v = 0; v < maxvertex; v++)
		g->list[v] = NULL;
}

void insert_vertex(graphtype* g, int v)
{
	if (((g->n) + 1) > maxvertex)
	{
		fprintf(stderr, "error");
		return;
	}
	g->n++;
}

void insert_edge(graphtype* g, int u, int v)
{
	graphnode* node;
	if (u >= g->n || v >= g->n)
	{
		fprintf(stderr, "error");
		return;
	}
	node = (graphnode*)malloc(sizeof(graphnode));
	node->vertex = v;
	node->link = g->list[u];
	g->list[u] = node;
}

#define stacksize 100
typedef int element;
typedef struct
{
	element stack[stacksize];
	int top;
} stacktype;

void init(stacktype* s)
{
	s->top = -1;
}

int is_empty(stacktype* s)
{
	return (s->top == -1);
}

int is_full(stacktype* s)
{
	return (s->top == (stacksize - 1));
}

void push(stacktype* s, element item)
{
	if(is_full(s))
	{
		fprintf(stderr, "error");
		return;
	}
	else s->stack[++(s->top)] = item;
}

element pop(stacktype* s)
{
	if (is_empty(s))
	{
		fprintf(stderr, "error");
		return;
	}
	else return s->stack[(s->top)--];
}


int topo_sort(graphtype* g)
{
	int i;
	stacktype s;
	graphnode* node;

	int* in_degree = (int*)malloc(g->n * sizeof(int));
	for (i = 0; i < g->n; i++)
		in_degree[i] = 0;
	for (i = 0; i < g->n; i++)
	{
		graphnode* node = g->list[i];
		while (node != NULL)
		{
			in_degree[node->vertex]++;
			node = node->link;
		}
	}

	init(&s);
	for (i = 0; i < g->n; i++)
	{
		if (in_degree[i] == 0)
			push(&s, i);
	}
	while (!is_empty(&s))
	{
		int w;
		w = pop(&s);
		printf("Á¤Á¡ %d -> ", w);
		node = g->list[w];
		while (node != NULL)
		{
			int u = node->vertex;
			in_degree[u]--;
			if (in_degree[u] == 0)
				push(&s, u);
			node = node->link;
		}
	}
	free(in_degree);
	printf('\n');
	return (i == g->n);
}

int main(void)
{
	graphtype g;
	graph_init(&g);
	insert_vertex(&g, 0); insert_vertex(&g, 1);
	insert_vertex(&g, 2); insert_vertex(&g, 3);
	insert_vertex(&g, 4); insert_vertex(&g, 5);
	insert_edge(&g, 0, 2); insert_edge(&g, 0, 3);
	insert_edge(&g, 1, 3); insert_edge(&g, 1, 4);
	insert_edge(&g, 2, 3); insert_edge(&g, 2, 5);
	insert_edge(&g, 3, 5);
	insert_edge(&g, 4, 5);
	topo_sort(&g);
	return 0;
}

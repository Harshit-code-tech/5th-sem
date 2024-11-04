#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct
{
  int u, v, w;
} Edge;

int parent[MAX], rank[MAX];
Edge edges[MAX], mst[MAX];
int n, m;

int find_set(int i)
{
  if (parent[i] != i)
    parent[i] = find_set(parent[i]);
  return parent[i];
}

void union_sets(int u, int v)
{
  int rootU = find_set(u);
  int rootV = find_set(v);

  if (rank[rootU] > rank[rootV])
    parent[rootV] = rootU;
  else if (rank[rootU] < rank[rootV])
    parent[rootU] = rootV;
  else
  {
    parent[rootV] = rootU;
    rank[rootU]++;
  }
}

int compare_edges(const void *a, const void *b)
{
  Edge *edgeA = (Edge *)a;
  Edge *edgeB = (Edge *)b;
  return edgeA->w - edgeB->w;
}

void kruskal()
{
  int mstWeight = 0;
  int mstEdges = 0;

  for (int i = 1; i <= n; i++)
  {
    parent[i] = i;
    rank[i] = 0;
  }

  qsort(edges, m, sizeof(Edge), compare_edges);

  for (int i = 0; i < m && mstEdges < n - 1; i++)
  {
    int u = edges[i].u;
    int v = edges[i].v;
    int w = edges[i].w;

    if (find_set(u) != find_set(v))
    {
      mst[mstEdges++] = edges[i];
      mstWeight += w;
      union_sets(u, v);
    }
  }

  printf("Edge \tCost\n");
  for (int i = 0; i < mstEdges; i++)
  {
    printf("%d--%d \t%d\n", mst[i].u, mst[i].v, mst[i].w);
  }
  printf("Total Weight of the Spanning Tree: %d\n", mstWeight);
}

int main()
{
  printf("Enter the number of vertices and edges: ");
  scanf("%d %d", &n, &m);

  printf("Enter the edges (u v w):\n");
  for (int i = 0; i < m; i++)
  {
    scanf("%d %d %d", &edges[i].u, &edges[i].v, &edges[i].w);
  }
  kruskal();
  printf("22052982: Harshit Ghosh\n");
  return 0;
}
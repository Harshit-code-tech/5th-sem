#include <stdio.h>
#include <stdlib.h>

typedef struct SYMBOL
{
  char alphabet;
  int frequency;
  struct SYMBOL *l, *r;
} S;

typedef struct MinHeap
{
  int size;
  int capacity;
  S **arr;
} Min;

S *createNode(char alphabet, int frequency)
{
  S *node = (S *)malloc(sizeof(S));
  node->alphabet = alphabet;
  node->frequency = frequency;
  node->l = node->r = NULL;
  return node;
}

Min *createHeap(int cap)
{
  Min *m = (Min *)malloc(sizeof(Min));
  m->size = 0;
  m->capacity = cap;
  m->arr = (S **)malloc(m->capacity * sizeof(S *));
  return m;
}

void swap(S **a, S **b)
{
  S *t = *a;
  *a = *b;
  *b = t;
}

void minHeapify(Min *m, int idx)
{
  int smallest = idx;
  int l = 2 * idx + 1;
  int r = 2 * idx + 2;

  if (l < m->size && m->arr[l]->frequency < m->arr[smallest]->frequency)
    smallest = l;
  if (r < m->size && m->arr[r]->frequency < m->arr[smallest]->frequency)
    smallest = r;

  if (smallest != idx)
  {
    swap(&m->arr[smallest], &m->arr[idx]);
    minHeapify(m, smallest);
  }
}

int issize(Min *m)
{
  return (m->size == 1);
}

S *extractMin(Min *m)
{
  S *temp = m->arr[0];
  m->arr[0] = m->arr[m->size - 1];
  --m->size;
  minHeapify(m, 0);
  return temp;
}

void insert(Min *m, S *node)
{
  ++m->size;
  int i = m->size - 1;

  while (i && node->frequency < m->arr[(i - 1) / 2]->frequency)
  {
    m->arr[i] = m->arr[(i - 1) / 2];
    i = (i - 1) / 2;
  }
  m->arr[i] = node;
}

void buildMinHeap(Min *m)
{
  int n = m->size - 1;
  for (int i = (n - 1) / 2; i >= 0; --i)
    minHeapify(m, i);
}

Min *createMinHeap(char alphabet[], int frequency[], int size)
{
  Min *m = createHeap(size);
  for (int i = 0; i < size; ++i)
    m->arr[i] = createNode(alphabet[i], frequency[i]);
  m->size = size;
  buildMinHeap(m);
  return m;
}

S *huff(char alphabet[], int frequency[], int size)
{
  S *l, *r, *t;
  Min *m = createMinHeap(alphabet, frequency, size);

  while (!issize(m))
  {
    l = extractMin(m);
    r = extractMin(m);
    t = createNode('$', l->frequency + r->frequency);
    t->l = l;
    t->r = r;
    insert(m, t);
  }
  return extractMin(m);
}

void inorder(S *root)
{
  if (root)
  {
    inorder(root->l);
    if (root->alphabet != '$')
      printf("%c ", root->alphabet);
    inorder(root->r);
  }
}

void printCodes(S *root, int arr[], int top)
{
  if (root->l)
  {
    arr[top] = 0;
    printCodes(root->l, arr, top + 1);
  }
  if (root->r)
  {
    arr[top] = 1;
    printCodes(root->r, arr, top + 1);
  }
  if (!(root->l) && !(root->r))
  {
    printf("%c: ", root->alphabet);
    for (int i = 0; i < top; i++)
      printf("%d", arr[i]);
    printf("\n");
  }
}

int main()
{
  int top = 0;
  int arr[100];
  int n;

  printf("Enter the number of alphabets: ");
  scanf("%d", &n);

  char alphabet[n];
  int frequency[n];

  printf("Enter alphabets: ");
  for (int i = 0; i < n; i++)
    scanf(" %c", &alphabet[i]); // Ensure space before %c to skip whitespace

  printf("Enter frequencies: ");
  for (int i = 0; i < n; i++)
    scanf("%d", &frequency[i]);

  S *root = huff(alphabet, frequency, n);

  printf("Leaf order traversal: ");
  inorder(root);
  printf("\n");

  printf("Huffman codes:\n");
  printCodes(root, arr, top);
  printf("22052982: Harshit Ghosh\n");

  return 0;
}

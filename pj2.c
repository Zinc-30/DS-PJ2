#include <stdio.h>
#include <string.h>

#define MaxN 100

/*	This is the data structure to store the tree. 
	For a node tree[i], i means the number of this node.
	If node i doesn't have any son, tree[i].firstSon is 0,
	otherwise, it is the number of its first son.
	If node i has more than one son, tree[i].nextSibling works
	like a linked list.
*/
struct Node
{
	int firstSon, nextSibling;
}tree[MaxN];

int n, m;									//	n, m have the same meaning with the description in the problem

/*	Using breadth-first search(BFS) to travel all the tree
	and count the total number of leaves at each level.
*/
void BFS(int root)
{
	int head, tail;							//	head, tail are the queue's head and tail pointers
	int leaves=0, nowLevel=0;				//	leaves stores the total number of leaves at the level which is being counted now
	int queue[MaxN], level[MaxN];			//	queue[] is used to do BFS, level[i] stores the level at which node i is
	/*	BFS begins	*/
	head = tail = 0;
	queue[head] = root;
	level[head] = 0;
	while (head <= tail)
	{
		if (nowLevel != level[head])		//	ALL nodes at a level have been processed
		{
			printf("%d ", leaves);
			leaves = 0;
			nowLevel = level[head];			//	change the level being counted
		}
		if (!tree[queue[head]].firstSon)	//	if node queue[head] doesn't have any son
			++leaves;						//	it is a leaf
		int i = tree[queue[head]].firstSon;
		while (i)							//	travel all the sons and put them into the queue
		{
			queue[++tail] = i;
			level[tail] = level[head]+1;
			i = tree[i].nextSibling;
		}
		++head;								//	process the next node in the queue
	}
	printf("%d\n", leaves);					//	the total number of leaves at the last level hasn't been printed
}

int main()
{
	scanf("%d%d", &n, &m);
	while (n)
	{
		/*	Initialization(building the tree)	*/
		memset(tree, 0, sizeof(tree));
		while (m--)
		{
			int father, p, son, lastSon;
			scanf("%d%d", &father, &p);
			while (p--)
			{
				scanf("%d", &son);
				if (!tree[father].firstSon)
					tree[father].firstSon = lastSon = son;
				else
				{
					tree[lastSon].nextSibling = son;
					lastSon = son;
				}
			}
		}
		/*	Working	*/
		BFS(1);
		scanf("%d%d", &n, &m);
	}
	
	return 0;
}
			

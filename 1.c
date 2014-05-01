#include <stdio.h>
#include <stdlib.h>

/*
%cat input.txt
	 4   16				// n = 4, m = 16
	10   15   20   25		// 오름차순으로 정렬된 n개의 정수
	 3    3    1    1		// p0= 3/m, p1= 3/m, p2= 1/m, p3= 1/m
  2    3    1    1    1		// q0= 2/m, q1= 3/m, q2= 1/m, q3= 1/m


%cat output.txt
OBST의 cost는 2입니다. 		// 32/m = 32/16 = 2	

CBT 1번 노드 = 15
CBT 2번 노드 = 10
CBT 3번 노드 = 20
CBT 7번 노드 = 25
*/
typedef struct revo obst;
struct revo
{
	int w;
	int c;
	int r;
};

void printTree(obst **tree, int i, int j, int *a, FILE *out, int ord)
{
	if(tree[i][j].r != 0 )
	{
		fprintf(out, "OBT %d번 노드  = %d\n", ord, a[tree[i][j].r]);
		printTree(tree, i, tree[i][j].r-1, a, out, ord*2);
		printTree(tree, tree[i][j].r, j, a, out, (ord*2)+1);
	}
}

int main()
{
	obst **table;

	int n, m, tmp = 0;
	int *a, *p, *q;
	int i, j, l, k, mm;

	FILE * in = fopen("input.txt", "r");
	FILE * out = fopen("output.txt", "w");

	fscanf(in, "%d %d", &n, &m);

	a = (int*)malloc(sizeof(int)*(n+1));
	p = (int*)malloc(sizeof(int)*(n+1));
	q = (int*)malloc(sizeof(int)*(n+1));

	for ( i = 1 ; i <= n ; i ++ )
	{
		fscanf(in, "%d", &a[i]);
	}

	for ( i = 1 ; i <= n ; i ++ )
	{
		fscanf(in, "%d", &p[i]);
		tmp += p[i];
	}

	for ( i = 0 ; i <= n ; i ++ )
	{
		fscanf(in, "%d", &q[i]);
		tmp += q[i];
	}

	if(tmp != m)
	{
		m = tmp;
	}//주어진 확률m과 실제 확률의 합이 다를 경우 실제로 구해진 확률의 합을 기준으로 한다.

	table = (obst**)malloc(sizeof(obst*)*(n+1));

	for ( i = 0 ; i <= n ; i ++ )
	{
		table[i] = (obst*)malloc(sizeof(obst)*(n+1));
	}

	//초기설정
	for ( i = 0 ; i <= n ; i ++ )
	{
		table[i][i].w = q[i];
		table[i][i].c = 0;
		table[i][i].r = 0;
	}
	//알고리즘 시작.
	//연산의 편의를 위해 가로축 i, 세로축 j로 한다.
	//T(i, j)... a(i+1) ~ a(j)
	for ( l = 1 ; l <= n ; l++)
	{
		for ( i = 0 ; i <= n - l ; i ++ )
		{
			j = i + l;

			table[i][j].w = table[i][j-1].w + p[j]+q[j];
			mm = i + 1;
			for ( k = i + 1 ; k <= j ; k ++ )
			{
				if( (table[i][k-1].c + table[k][j].c) < (table[i][mm-1].c + table[mm][j].c) )
				{
					mm = k;
				}
			}
			table[i][j].r = mm;
			table[i][j].c = table[i][j].w + table[i][mm-1].c + table[mm][j].c;
		}
	}
	/*
	for ( i = 0 ; i <= 4 ; i ++ )
	{
		for ( j = i ; j <= 4 ; j ++ )
		{
			printf("(%d|%d|%d) ",table[i][j].w, table[i][j].c, table[i][j].r);
		}
		printf("\n");
	}
	*/
	fprintf(out, "OBST의 cost는%d입니다\n\n", table[0][n].c/m);

	printTree(table, 0, n, a, out, 1);


	free(table);
	free(a);
	free(p);
	free(q);
	fclose(in);
	fclose(out);
	return 0;
}

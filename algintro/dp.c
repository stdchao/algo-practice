#include <limits.h>
#include "util.h"

#define DEBUG

void fastest_way(int l[2][5], int* minf, int* minl)
{	
	// question initial value
	int e1 = 2;
	int e2 = 4;
	int a[2][6] = {{7, 9, 3, 4, 8, 4}, {8, 5, 6, 4, 5, 7}};
	int t[2][5] = {{2, 3, 1, 3, 4}, {2, 1, 2, 2, 1}};
	int x1 = 3;
	int x2 = 2;
	
	// init table
	int f[2][6];
	//int l[2][5];

	// init value
	f[0][0] = e1 + a[0][0];
	f[1][0] = e2 + a[1][0];
#ifdef DEBUG
		printf("%d %d | 0 0 \n", f[0][0], f[1][0]);
#endif
	// fill array f
	for(int j = 1; j < 6; j++)
	{	
		// f[0]
		if(f[0][j-1] + a[0][j] <= f[1][j-1] + t[1][j-1] + a[0][j])
		{
			f[0][j] = f[0][j-1] + a[0][j];
			l[0][j-1] = 1;
		}
		else
		{
			f[0][j] = f[1][j-1] + t[1][j-1] + a[0][j];
			l[0][j-1] = 2;
		}
		
		// f[1]
		if(f[1][j-1] + a[1][j] <= f[0][j-1] + t[0][j-1] + a[1][j])
		{
			f[1][j] = f[1][j-1] + a[1][j];
			l[1][j-1] = 2;
		}
		else
		{
			f[1][j] = f[0][j-1] + t[0][j-1] + a[1][j];
			l[1][j-1] = 1;
		}
#ifdef DEBUG
		printf("%d %d | %d %d \n", f[0][j], f[1][j], l[0][j-1], l[1][j-1]);
#endif
	}

	// get fastest way
	if(f[0][5] + x1 <= f[1][5] + x2)
	{
		*minf = f[0][5] + x1;
		*minl = 1;
	}
	else
	{
		*minf = f[1][5] + x2;
		*minl = 2;
	}
}

/* matrix chain order in dynamic programming */
void matrix_chain_order(int row, int col, int s[row][col], int* p, int length)
{
	int n = length - 1;
	
	// table
	int64_t m[n][n];
	//int s[n][n];

	// init value
	for(int i = 0; i < n; i++)
		m[i][i] = 0;

	// fill table
	for(int l = 2; l <= n; l++)
	{
		printf("%d: ", l);
		for(int i = 0; i < n-l+1; i++)
		{
			int j = i+l-1;	
			m[i][j] = INT64_MAX;

			int k;
			for(k = i; k < j; k++)
			{
				int64_t cost = m[i][k] + m[k+1][j] + p[i]*p[k+1]*p[j+1];
				if(cost < m[i][j])
				{	
					m[i][j] = cost;
					s[i][j] = k;
				}
			}
#ifdef DEBUG
			printf("[%d,%d,%lld,%d] ", i, j, m[i][j], s[i][j]);
#endif
		}
#ifdef DEBUG
		printf("\n");
#endif
	}
}

// matrix chain order in memorized recursive
int64_t lookup_chain(int n, int64_t m[n][n], int s[n][n], int* p, int i, int j)
{
	if(m[i][j] < INT64_MAX)
		return m[i][j];

	if(i == j)
	{
		m[i][j] = 0;
		s[i][j] = 0;
	}

	for(int k = i; k < j; k++)
	{
		int64_t cost = lookup_chain(n, m, s, p, i, k) + 
					lookup_chain(n, m, s, p, k+1, j) + p[i]*p[k+1]*p[j+1];
		if(cost < m[i][j])
		{
			m[i][j] = cost;
			s[i][j] = k;
		}	
	}
#ifdef DEBUG
	printf("[%d,%d,%lld,%d] ", i, j, m[i][j], s[i][j]);
#endif
	return m[i][j];
}

void memorized_matrix_chain_order(int row, int col, int s[row][col], int* p, int length)
{
	int n = length - 1;
	// init table
	int64_t m[n][n];
	for(int i=0; i<n; i++)
		for(int j=0; j<n; j++)
			m[i][j] = INT64_MAX;
	//
	printf("\n");
	lookup_chain(n, m, s, p, 0, n-1);
}

// optimal way
void print_optimal_parens(int row, int col, int s[row][col], int i, int j)
{
	if(i == j)
		printf("A%d",i);
	else
	{
		printf("(");
		print_optimal_parens(row, col, s, i, s[i][j]);
		print_optimal_parens(row, col, s, s[i][j]+1, j);
		printf(")");
	}
}

/* longest common subsequence */
void lcs_length(char* x, char* y, int m, int n, int s[m+1][n+1])
{
	// init table
	int c[m+1][n+1];
	for(int i = 0; i <= m; i++)
		c[i][0] = 0;
	for(int j = 0; j <= n; j++)
		c[0][j] = 0;

	// fill table
	for(int i = 1; i <= m; i++)
	{
		for(int j = 1; j <= n; j++)
		{
			if(x[i-1] == y[j-1])
			{
				c[i][j] = c[i-1][j-1] + 1;
				s[i][j] = 1;
			}
			else
			{
				if(c[i-1][j] >= c[i][j-1])
				{
					c[i][j] = c[i-1][j];
					s[i][j] = 2;
				}
				else
				{
					c[i][j] = c[i][j-1];
					s[i][j] = 3;
				}
			}
#ifdef DEBUG
			printf("[%d,%d] ", c[i][j], s[i][j]);
#endif
		}
#ifdef DEBUG
		printf("\n");
#endif
	}
}

void lcs_print(char* x, int i, int j, int m, int n, int s[m+1][n+1])
{
	if(i == 0 || j == 0)
		return;
	
	if(s[i][j] == 1)
	{
		lcs_print(x, i-1, j-1, m, n, s);
		printf("%c ", x[i-1]);
	}
	else if(s[i][j] == 2)
	{
		lcs_print(x, i-1, j, m, n, s);
	}
	else
	{
		lcs_print(x, i, j-1, m, n, s);
	}
}

/* optimal binary search trees */

/* an activity-selection problem */
// dynamic programming solving
void selection_most(int* start, int* end, int n, int s[n][n])
{
	// init table
	int c[n][n];
	for(int i =0; i < n; i++)
		c[i][i] = 0;
	
	// fill table
	for(int len = 2; len <= n; len++)
	{
		for(int i = 0; i <= n - len ; i++)
		{
			int j = i + len - 1;
			// default value	
			c[i][j] = 0;
			s[i][j] = 0;
			// 
			for(int k = i+1; k < j; k++)
			{
				if(end[i] <= start[k] && end[k] <= start[j])
				{
					int num = c[i][k] + c[k][j] + 1;

					if(num > c[i][j])
					{
						c[i][j] = num;
						s[i][j] = k;
					}
				}
			}
#ifdef DEBUG
			printf("[%d,%d,%d,%d] ", i, j, c[i][j], s[i][j]);
#endif
		}
#ifdef DEBUG
			printf("\n");
#endif
	}
}

void print_selection(int i, int j, int n, int s[n][n])
{
	if(j-i+1 == n)
		printf("dynamic programming: a%d ", i);

	if(s[i][j] > 0)
	{
		printf("a%d ", s[i][j]);
		print_selection(i, s[i][j], n, s);
		print_selection(s[i][j], j, n, s);
	}

	if(j-i+1 == n)
		printf("a%d \n", j);
}

// greedy solving
void greedy_selection(int* start, int* end, int n)
{
	printf("greedy seletion: ");
	int first = 0;
	printf("a%d ", first);
	//
	for(int i = 1; i < n; i++)
	{
		if(start[i] > end[first])
		{
			first = i;
			printf("a%d ", first);
		}
	}
	//
	printf("\n");
}

/* knapsack 0-1 problem*/


/*------------------------main--------------------------*/
int main(int argc, char** argv)
{
	printf("=====Dynamic Programming=====\n");

	printf("\n=====1. Assembly-line scheduling:\n");
	int minf, minl;
	int l[2][5];
	fastest_way(l, &minf, &minl);
	printf("fastest way [%d,%d]\n", minf, minl);
	printArr(l[minl-1], sizeof(l[minl])/sizeof(int),-1);

	printf("\n=====2. Matrix-chain multiplication:\n");
	int p[7] = {30, 35, 15, 5, 10, 20, 25};
	int s[6][6];
	matrix_chain_order(6,6,s,p,7);
	print_optimal_parens(6,6,s, 0, 5);
	int s2[6][6];
	memorized_matrix_chain_order(6,6,s2,p,7);
	print_optimal_parens(6,6,s2,0,5);
	
	printf("\n\n=====3. Longest common subsequence :\n");
	char x[7] = {'A', 'B', 'C', 'B', 'D', 'A', 'B'};
	char y[6] = {'B', 'D', 'C', 'A', 'B', 'A'};
	int s3[8][7];
	lcs_length(x, y, 7, 6, s3);
	lcs_print(x, 7, 6, 7, 6, s3);

	printf("\n\n=====4. optimal binary search trees :\n");
	

	printf("=====Greedy algorithm=====\n");

	printf("\n\n===== 5. an activity-seletion problem :\n");
	int start[11] = {1, 3, 0, 5, 3, 5, 6, 8, 8, 2, 12};
	int final[11] = {4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; // ascend sort
	// dynamic programming solving
	int s5[11][11];
	selection_most(start, final, 11, s5);
	print_selection(0, 10, 11, s5);
	// greedy algorithm solving
	greedy_selection(start, final, 11);	
	return 0;
}

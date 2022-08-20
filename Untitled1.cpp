#include <stdio.h>
void CreateFibo(int F[], int n)
{
	F[0] = 0;
	F[1] = 1;
	for(int i = 2; i <= n; i++)
	{
		F[i] = F[i - 1] + F[i - 2];
	}
	
}
int main ()
{
	int n, f[200];
	scanf("%d", &n);
	CreateFibo(f, n);
	for(int i = 0; i < n; i++)
	{
		printf("%d ", f[i]);
	}
	
	return 0;
}
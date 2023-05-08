#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define N 100

void linspace(double v[], double start, double stop, int n)
{
    if(n == 0)
    {
        return;
    }
    else if(n == 1)
    {
        v[0] = start;
        return;
    }
    else{
        v[n]; 
        v[0] = start;
        v[n-1] = stop;
        double diff = (stop - start)/(n-1);
        for(int i = 1; i < n; i++){
        v[i]= v[i-1]+diff;
       }
       return;
    }
}

void add(double v1[], const double v2[], int n)
{
    for(int i = 0; i < n; i++)
    {
        v1[i] += v2[i];
    }
}

double dot_product(const double v1[], const double v2[], int n)
{
    double product = 0.0;
    for(int i = 0; i < n; i++)
    {   
        
        product += v1[i] * v2[i];
    }
    return product;
}
void multiply_by_scalar(double v[], int n, double s)
{
    for(int i = 0; i < n; i++)
    {
        v[i] = s*v[i];
    }
}
void range(double v[], int n, double start, double step)
{
    for(int i = 0; i < n; i++)
    {
        v[i] = start + step*i;
    }
}
// read double vector of size n
void read_vector(double v[], int n)
{
	double in;
    printf("[number]\n");
	for (int i = 0; i < n; i++)
	{
		scanf("%lf", &in);
		v[i] = in;
	}
}

// print double vector of size n (with 2 significant figures)
void print_vector(const double v[], int n)
{
	for (int i = 0; i < n; ++i)
	{
		printf("%.2f ", v[i]);
	}
	printf("\n");
}

int main(void)
{

	int to_do, n;
	double start, stop, step, scalar;
	double vector_1[N], vector_2[N];

    printf("1 - linspace\n2 - add\n3 - dot product\n4 - multiply by scalar\n5 - range\n");
	scanf("%d", &to_do);

	switch (to_do)
	{
	case 1: // linspace
        printf("[n][start][stop]\n");
		scanf("%d %lf %lf", &n, &start, &stop);
		linspace(vector_1, start, stop, n);
		print_vector(vector_1, n);
		break;
	case 2: // add
        printf("[n]\n");
		scanf("%d", &n);
		read_vector(vector_1, n);
		read_vector(vector_2, n);
		add(vector_1, vector_2, n);
		print_vector(vector_1, n);
		break;
	case 3: // dot product
        printf("[n]\n");
		scanf("%d", &n);
		read_vector(vector_1, n);
		read_vector(vector_2, n);
		printf("%.2f\n", dot_product(vector_1, vector_2, n));
		break;
	case 4: // multiply by scalar
        printf("[n][scalar]\n");
		scanf("%d %lf", &n, &scalar);
		read_vector(vector_1, n);
		multiply_by_scalar(vector_1, n, scalar);
		print_vector(vector_1, n);
		break;
	case 5: // range
        printf("[n][start][step]\n");
		scanf("%d %lf %lf", &n, &start, &step);
		range(vector_1, n, start, step);
		print_vector(vector_1, n);
		break;
	default:
		printf("Unknown operation! %d", to_do);
		break;
	}
	return 0;
}
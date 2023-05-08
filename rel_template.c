#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REL_SIZE 100
#define MAX_RANGE 100

typedef struct
{
	int first;
	int second;
} pair;

// Add pair to existing relation if not already there
int add_relation(pair *, int, pair);

int get_domain(pair *, int, int *);

// The relation R is reflexive if xRx for every x in X
int is_reflexive(pair *tab, int n)
{
	int domain[MAX_REL_SIZE];
	int n_domain = get_domain(tab, n, domain);
	int flag = 0;

	for (int i = 0; i < n_domain; i++)
	{
		int flag = 0;
		for (int j = 0; j < n; j++)
		{
			if (tab[j].first == tab[j].second && tab[j].first == domain[i])
				flag = 1;
		}
		if (flag == 0)
			return 0;
	}
	return 1;
}

// The relation R on the set X is called irreflexive
// if xRx is false for every x in X
int is_irreflexive(pair *tab, int n)
{
	int domain[MAX_REL_SIZE];
	int n_domain = get_domain(tab, n, domain);

	for (int i = 0; i < n_domain; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tab[j].first == tab[j].second && tab[j].first == domain[i])
				return 0;
		}
	}
	return 1;
}

// A binary relation R over a set X is symmetric if:
// for all x, y in X xRy <=> yRx
int is_symmetric(pair *tab, int n)
{

	for (int i = 0; i < n; i++)
	{
		int flag = 0;
		for (int j = 0; j < n; j++)
		{
			if (tab[i].first == tab[j].second && tab[j].first == tab[i].second)
				flag = 1;
		}
		if (flag == 0)
			return 0;
	}
	return 1;
}

// A binary relation R over a set X is antisymmetric if:
// for all x, y in X if xRy and yRx then x=y
int is_antisymmetric(pair *tab, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tab[i].first == tab[j].second && tab[j].first == tab[i].second)
			{
				if (tab[i].first != tab[j].first)
					return 0;
			}
		}
	}
	return 1;
}

// A binary relation R over a set X is asymmetric if:
// for all x,y in X if at least one of xRy and yRx is false
int is_asymmetric(pair *tab, int n)
{

	for (int i = 0; i < n; i++)
	{
		int flag = 1;
		for (int j = 0; j < n; j++)
		{
			if (tab[i].first == tab[j].second && tab[j].first == tab[i].second)
				flag = 0;
		}
		if (flag == 0)
			return 0;
	}
	return 1;
}

// A homogeneous relation R on the set X is a transitive relation if:
// for all x, y, z in X, if xRy and yRz, then xRz
int is_transitive(pair *tab, int n)
{
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (tab[i].second == tab[j].first)
			{
				int flag = 0;
				for (int k = 0; k < n; k++)
				{
					if (tab[k].first == tab[i].first && tab[k].second == tab[j].first)
						flag = 1;
				}
				if (flag == 0)
					return 0;
			}
		}
	}
	return 1;
}

// Case 2:

// A partial order relation is a homogeneous relation that is
// reflexive, transitive, and antisymmetric
int is_partial_order(pair *tab, int n)
{
	if (is_reflexive(tab, n) == 0)
		return 0;
	if (is_transitive(tab, n) == 0)
		return 0;
	if (is_antisymmetric(tab, n) == 0)
		return 0;
	return 1;
}

// Relation R is connected if for each x, y in X:
// xRy or yRx (or both)
int is_connected(pair *tab, int n)
{
	int domain[MAX_REL_SIZE];
	int n_domain = get_domain(tab, n, domain);

	int flag = 0;
	for (int i = 0; i < n_domain; i++)
	{

		for (int j = 0; j < n_domain; j++)
		{
			int flag = 0;
			for (int k = 0; k < n; k++)
			{
				if (domain[i] == tab[k].first && domain[j] == tab[k].second || domain[j] == tab[k].first && domain[i] == tab[k].second)
					flag = 1;
			}
			if (flag == 0)
				return 0;
		}
	}
	return 1;
}

// A total order relation is a partial order relation that is connected
int is_total_order(pair *tab, int n)
{
	if (is_reflexive(tab, n) == 0)
		return 0;
	if (is_transitive(tab, n) == 0)
		return 0;
	if (is_antisymmetric(tab, n) == 0)
		return 0;
	if (is_connected(tab, n) == 0)
		return 0;
	return 1;
}

int find_max_elements(pair *tab, int n, int *max_elements)
{
	int is_in = 0;
	int numbers_first[MAX_REL_SIZE];
	int numbers_second[MAX_REL_SIZE];
	int numbers_count_first = 1;
	int numbers_count_second = 1;
	numbers_first[0] = tab[0].first;
	numbers_second[0] = tab[0].second;

	for (int i = 0; i < n; i++)
	{
		is_in = 0;
		for (int j = 0; j < numbers_count_second; j++)
		{
			if (tab[i].second == numbers_second[j])
				is_in = 1;
		}
		if (is_in == 0)
		{
			numbers_second[numbers_count_second] = tab[i].second;
			numbers_count_second++;
		}
	}

	int maxes_count = 0;
	int flag = 1;

	for (int i = 0; i < numbers_count_second; i++)
	{
		flag = 1;
		for (int j = 0; j < n; j++)
		{
			if (numbers_second[i] == tab[j].first && tab[j].first != tab[j].second)
			{
				flag = 0;
			}
		}
		if (flag == 1)
		{
			max_elements[maxes_count] = numbers_second[i];
			maxes_count++;
		}
	}
	//	bubble sort
	for (int counter = 0; counter < maxes_count - 1; counter++)
	{
		for (int counter1 = 0; counter1 < maxes_count - counter - 1; counter1++)
		{
			if (max_elements[counter1] > max_elements[counter1 + 1])
			{
				int swap_var = max_elements[counter1];
				max_elements[counter1] = max_elements[counter1 + 1];
				max_elements[counter1 + 1] = swap_var;
			}
		}
	}

	return maxes_count;
}

int find_min_elements(pair *tab, int n, int *min_elements)
{
	int is_in = 0;
	int numbers_first[MAX_REL_SIZE];
	int numbers_second[MAX_REL_SIZE];
	int numbers_count_first = 1;
	int numbers_count_second = 1;
	numbers_first[0] = tab[0].first;
	numbers_second[0] = tab[0].second;

	for (int i = 0; i < n; i++)
	{
		is_in = 0;
		for (int j = 0; j < numbers_count_first; j++)
		{
			if (tab[i].first == numbers_first[j])
				is_in = 1;
		}
		if (is_in == 0)
		{
			numbers_first[numbers_count_first] = tab[i].first;
			numbers_count_first++;
		}
	}

	int mins_count = 0;
	int flag = 1;

	for (int i = 0; i < numbers_count_first; i++)
	{
		flag = 1;
		for (int j = 0; j < n; j++)
		{
			if (numbers_first[i] == tab[j].second && tab[j].first != tab[j].second)
			{
				flag = 0;
			}
		}
		if (flag == 1)
		{
			min_elements[mins_count] = numbers_first[i];
			mins_count++;
		}
	}
	// bubble sort
	for (int counter = 0; counter < mins_count - 1; counter++)
	{
		for (int counter1 = 0; counter1 < mins_count - counter - 1; counter1++)
		{
			if (min_elements[counter1] > min_elements[counter1 + 1])
			{
				int swap_var = min_elements[counter1];
				min_elements[counter1] = min_elements[counter1 + 1];
				min_elements[counter1 + 1] = swap_var;
			}
		}
	}
	return mins_count;
}

int get_domain(pair *tab, int n, int *domain)
{
	int is_in = 0;
	int numbers_count = 1;
	domain[0] = tab[0].first;
	for (int i = 0; i < n; i++)
	{
		is_in = 0;
		for (int j = 0; j < numbers_count; j++)
		{
			if (tab[i].first == domain[j])
				is_in = 1;
		}
		if (is_in == 0)
		{
			domain[numbers_count] = tab[i].first;
			numbers_count++;
		}
		is_in = 0;
		for (int j = 0; j < numbers_count; j++)
		{
			if (tab[i].second == domain[j])
				is_in = 1;
		}
		if (is_in == 0)
		{
			domain[numbers_count] = tab[i].second;
			numbers_count++;
		}
	}

	for (int counter = 0; counter < numbers_count - 1; counter++)
	{
		for (int counter1 = 0; counter1 < numbers_count - counter - 1; counter1++)
		{
			if (domain[counter1] > domain[counter1 + 1])
			{
				int swap_var = domain[counter1];
				domain[counter1] = domain[counter1 + 1];
				domain[counter1 + 1] = swap_var;
			}
		}
	}

	return numbers_count;
}

// Case 3:

int composition(pair *tab_1, int n_1, pair *tab_2, int n_2, pair *comps)
{
	int comps_count = 0;
	int repeated_count = 0;
	for (int i = 0; i < n_1; i++)
	{
		for (int j = 0; j < n_2; j++)
		{
			if (tab_1[i].second == tab_2[j].first)
			{
				pair new_pair;
				new_pair.first = tab_1[i].first;
				new_pair.second = tab_2[j].second;
				repeated_count += add_relation(comps, comps_count - repeated_count, new_pair);
				comps_count++;
			}
		}
	}
	return comps_count - repeated_count;
}

// // Comparator for pair
// int cmp_pair(const void *a, const void *b)
// {
// }

// int insert_int(int *tab, int n, int new_element)
// {
// }

// Add pair to existing relation if not already there
int add_relation(pair *tab, int n, pair new_pair)
{
	for (int i = 0; i < n; i++)
		if (tab[i].first == new_pair.first && tab[i].second == new_pair.second)
		{
			return 1;
		}
	tab[n].first = new_pair.first;
	tab[n].second = new_pair.second;
	return 0;
}

// Read number of pairs, n, and then n pairs of ints
int read_relation(pair *relation)
{
	int n;
	pair temp_pair;
	scanf("%d", &n);
	int counter = 0;
	for (int i = 0; i < n; i++)
	{
		scanf("%d %d", &temp_pair.first, &temp_pair.second);
		counter += add_relation(relation, i - counter, temp_pair);
	}
	return n - counter;
}

void print_int_array(int *array, int n)
{
	printf("%d\n", n);
	for (int i = 0; i < n; i++)
	{
		printf("%d ", array[i]);
	}
	printf("\n");
}

int main(void)
{
	int to_do;
	pair relation[MAX_REL_SIZE];
	pair relation_2[MAX_REL_SIZE];
	pair comp_relation[MAX_REL_SIZE];
	int domain[MAX_REL_SIZE];
	int max_elements[MAX_REL_SIZE];
	int min_elements[MAX_REL_SIZE];

	scanf("%d", &to_do);
	int size = read_relation(relation);
	int ordered, size_2, n_domain;

	switch (to_do)
	{
	case 1:
		printf("%d ", is_reflexive(relation, size));
		printf("%d ", is_irreflexive(relation, size));
		printf("%d ", is_symmetric(relation, size));
		printf("%d ", is_antisymmetric(relation, size));
		printf("%d ", is_asymmetric(relation, size));
		printf("%d\n", is_transitive(relation, size));
		break;
	case 2:
		ordered = is_partial_order(relation, size);
		n_domain = get_domain(relation, size, domain);
		printf("%d %d\n", ordered, is_total_order(relation, size));
		print_int_array(domain, n_domain);
		if (!ordered)
			break;
		int no_max_elements = find_max_elements(relation, size, max_elements);
		int no_min_elements = find_min_elements(relation, size, min_elements);
		print_int_array(max_elements, no_max_elements);
		print_int_array(min_elements, no_min_elements);
		break;
	case 3:
		size_2 = read_relation(relation_2);
		printf("%d\n", composition(relation, size, relation_2, size_2, comp_relation));
		break;
	default:
		printf("NOTHING TO DO FOR %d\n", to_do);
		break;
	}
	return 0;
}


// iterative
int length(List L)
{
	int n = 0;
	Node *cur;
	for (cur = L; cur != NULL; cur = cur->next) n++;
	return n;
}

// recursive
int length(List L)
{
	if (L == NULL)
		return 0;
	else
		return 1 + length(L->next);
}

// higher-order
// make a list, replacing values by 1, sum this list

int one(int x) { return 1; }
int length(List L)
{
	return sum(map(one,L));
}

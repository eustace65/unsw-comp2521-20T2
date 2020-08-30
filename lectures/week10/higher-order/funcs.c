// a bunch of example to illustrate ideas on higher-order functions

int sum(List L)
{
	if (empty(L))
		return 0;
	else
		return head(L) + sum(tail(L));
}

int product(List L)
{
	if (empty(L))
		return 1;
	else
		return head(L) * product(tail(L));
}

// return empty(L) ? 1 : (head(L) * product(tail(L)));

product([1,2,3])
	1 * product([2,3])
		2 * product([3])
			3 * product([])
				1
			3 * 1
		2 * 3 * 1
	1 * 2 * 3 * 1

int add(x,y){return x+y;}
int sum(List L) { return fold(add,0,L); }

int mul(int x, int y){return x*y;}
int product(List L) { return fold(mul,1,L); }

int  doublify(int x){return 2*x;}
List doubleAll(List L) { return map(doublify,L); }

mul = &mul

List map(int (*f)(int x), List L)
{
	if (empty(L))
		return new();
	else
		return insert(f(head(x)), map(f,tail(L)));
}

int fold(int (*f)(int x, int y), int id, List L)
{
	if (empty(L))
		return id;
	else
		return f(head(L), fold(f,id,tail*L));
}


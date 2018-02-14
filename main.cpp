#include <iostream>

using namespace std;

void visualize(int heap[], int place, int depth);
void add(int heap[], int toAdd);

int main()
{
	int heap[100] = {0};
	//cout << heap[0] << endl;
	add(heap, 5);
	//cout << heap[0] << endl;
	add(heap, 32);
	//cout << heap[0] << endl;
	add(heap, 56);
	//cout << heap[0] << endl;
	add(heap, 23);
	//cout << heap[0] << endl;
	add(heap, 35);
	//cout << heap[0] << endl;
	add(heap, 55);
	//cout << heap[0] << endl;
	add(heap, 232);
	//cout << heap[0] << endl;
	add(heap, 53);
	//cout << heap[0] << endl;
	add(heap, 7);
	//cout << heap[0] << endl;
	add(heap, 100);
	//cout << heap[0] << endl;
	int num = 1/2;
	//cout << "3/2=" << num << endl;
	visualize(heap, 1, 0);
	return 0;
}

//print out the tree in a simple form
void visualize(int heap[], int place, int depth)
{
	for(int i = 0; i < depth; i++)
	{
		cout << "   ";
	}
	
	cout << heap[place-1] << endl;
	
	int next = place * 2;
	if(heap[next-1] != 0)
	{
		visualize(heap, next, depth+1);
	}
	if(heap[next] != 0)
	{
		visualize(heap, next+1, depth+1);
	}
}

void add(int heap[], int toAdd)
{
	int added = -1;
	for(int i = 0; i < 100; i++)
	{
		if(heap[i] == 0)
		{
			heap[i] = toAdd;
			added = i;
			break;
		}
	}
	
	if(added != -1)
	{
		int place = added + 1;
		while(place != 0)
		{
			int above = place / 2;
			if(above != 0 && heap[above-1] < heap[place-1])
			{
				int temp = heap[above-1];
				heap[above-1] = heap[place-1];
				heap[place-1] = temp;
			}
			place = above;
		}
	}
}
#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>

using namespace std;

//print out the tree in a simple form
void visualize(int heap[], int place = 1, int depth = 0)
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

//add numbers to the heap and heapify
void add(int heap[], int toAdd)
{
	//add the number to the end of the heap
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
	
	//move the number that was added up until the right spot is found
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
			else
			{
				break;
			}
			place = above;
		}
	}
}

int main()
{
	int heap[100] = {0};
	
	//prompt the user for how numbers will be entered
	cout << "Would you like to enter numbers via MANUAL input or from FILE? \n";
	char* input = new char[8];
	cin >> input;
	
	//if the user wants to enter numbers manually
	if(!strcmp(input, "MANUAL") || !strcmp(input, "manual"))
	{
		//add numbers one by one until the user says they are done
		cout << "Enter integers from 1-1000 one at a time. Enter DONE when you are done adding numbers \n";
		cin >> input;
		while(strcmp(input, "DONE") && strcmp(input, "done"))
		{
			int toAdd = atoi(input);
			add(heap, toAdd);
			cin >> input;
		}
		
		visualize(heap);
	}
	
	//if the user wants to enter numbers from a file
	else if(!strcmp(input, "FILE") || !strcmp(input, "file"))
	{
		char* file = new char[32];
		char* list = new char[512];
		
		//prompt the user for the name of the file
		cout << "Enter the name of the file.\n";
		cin.get();
		cin.get(file, 32);
		cin.get();
		
		//open the file
		ifstream stream(file);
		if(stream.is_open())
		{
			//extract the text from the file
			stream.getline(list, 512);
			stream.close();
			cout << "list: " << list << endl;
			//extract the numbers from the text
			for(int i = 0; i < strlen(list); i++)
			{
				if(isdigit(list[i]))
				{
					//isolate the number into a separate char pointer
					int start = i;
					char* number;
					do number[i-start] = list[i];
					while(list[++i] != ' ' && i < strlen(list));
					number[i-start] = '\0';
					
					//convert the isolated char pointer into an integer
					int toAdd = atoi(number);
					add(heap, toAdd);
				}
			}
		}
		else
		{
			cout << "File not found\n";
		}
		
		visualize(heap);
	}
	return 0;
}
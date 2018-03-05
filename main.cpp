/* Author: Raveen Karnik
 * Date: February 16, 2018
 * This program asks the user to input a series of integers (up to 100) between 1 and 1000,
 * either manually or from a file, and creates a max heap from the data. It can then either
 * print out a visualization of the max heap or a list of the data from largest to smallest. */

#include <iostream>
#include <cstring>
#include <stdlib.h>
#include <fstream>

using namespace std;

//print out the tree in a simple form
void visualize(int heap[], int total, int place = 1, int depth = 0)
{	
	for(int i = 0; i < depth; i++)
	{
		cout << "   ";
	}
	
	cout << heap[place-1] << endl;
	
	int next = place * 2;
	if(heap[next] != 0 && next < total)
	{
		visualize(heap, total, next+1, depth+1);
	}
	if(heap[next-1] != 0 && next < total)
	{
		visualize(heap, total, next, depth+1);
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

//organize the heap, starting at the top, recursively
void heapify(int heap[], int place = 1)
{
	int temp = heap[place-1];
	if(temp < heap[place*2-1] || temp < heap[place*2])
	{
		if(heap[place*2-1] < heap[place*2])
		{
			heap[place-1] = heap[place*2];
			heap[place*2] = temp;
			heapify(heap, place*2+1);
		}
		else
		{
			heap[place-1] = heap[place*2-1];
			heap[place*2-1] = temp;
			heapify(heap, place*2);
		}
	}
}

//print out the organized list
void print(int heap[])
{
	//while there are numbers in the heap
	while(heap[0] != 0)
	{
		//print the topmost number, which is the max
		int place = -1;
		cout << heap[0] << " ";
		
		//find the last number in the list
		for(int i = 0; i < 100; i++)
		{
			if(heap[i] == 0)
			{
				place = i;
				break;
			}
		}
		if(place == -1)
			place = 100;
		
		//move the last number to the top and erase the top
		heap[0] = heap[place-1];
		heap[place-1] = 0;
		
		//reorganize the heap
		heapify(heap);
	}
}

int main()
{
	int heap[100] = {0};
	int numbers = 0;
	
	bool fileFound = true;
	
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
			numbers++;
			cin >> input;
		}
		
		visualize(heap, numbers);
	}
	//if the user wants to enter numbers from a file
	else if(!strcmp(input, "FILE") || !strcmp(input, "file"))
	{
		char* file = new char[32];
		char* list = new char[512];
		
		//prompt the user for the name of the file
		cout << "\nEnter the name of the file.\n";
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
			cout << endl << list << endl;
			//extract the numbers from the text
			for(int i = 0; i < strlen(list); i++)
			{
				if(isdigit(list[i]))
				{
					//isolate the number into a separate char pointer
					int start = i;
					char* number = new char[5];
					do number[i-start] = list[i];
					while(list[++i] != ' ' && i < strlen(list));
					number[i-start] = '\0';
					
					//convert the isolated char pointer into an integer
					int toAdd = atoi(number);
					add(heap, toAdd);
					numbers++;
				}
			}
		}
		else
		{
			cout << "File not found\n";
			fileFound = false;
		}
	}
	
	//if the user entered neither option, throw an error.
	else
	{
		cout << "Sorry I couldn't understand that.\n";
		fileFound = false;
	}
	
	//print out either the visalization, the organized list, or both
	if(fileFound)
	{
		char* info = new char[8];
		cout << "\nWould you like to see the TREE, the LIST from largest to smallest, or BOTH?\n";
		cin >> info;
		cout << endl;
		if(!strcmp(info, "TREE") || !strcmp(info, "tree"))
		{
			visualize(heap, numbers);
		}
		else if(!strcmp(info, "LIST") || !strcmp(info, "list"))
		{
			print(heap);
		}
		else if(!strcmp(info, "BOTH") || !strcmp(info, "both"))
		{
			cout << "Tree:\n";
			visualize(heap, numbers);
			cout << "\nList:\n";
			print(heap);	
		}
		else
		{
			cout << "Sorry I couldn't understand that.\n";
		}
	}
	return 0;
}
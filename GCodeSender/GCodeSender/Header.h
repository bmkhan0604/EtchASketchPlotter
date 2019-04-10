#include <stdio.h>
#include <iostream>
#include <tchar.h>
#include "SerialClass.h"	// Library described above
#include <string>
#include <fstream>
#include <iomanip>

typedef struct command *link;
std::string Data = "";
int dataLength = 255;
int readResult = 0;
char dataout[20];

struct command {
	char data[20];
	link nextptr = NULL;
};

int convert(int num,int i)
{
	char temp[10];
	int j = 10;
	while (num >= 0)
	{
		temp[j] = char(num % 10);
		j--;
		num = num / 10;
	}
	while (temp[j] != NULL)
	{
		dataout[i] = temp[j];
		i++;
		j++;
	}
	return i;
}

link readFile()
{
	link firstptr;
	link ptr = new struct command;
	char fname[20] = "Test.txt";
	std::ifstream file;
	std::cout << "Enter Name the name of your File: ";
	std::cin >> fname;
	file.open(fname);
	if (file.is_open() == false)
	{
		std::cout << "\nFile Failed to Open: " << fname;
		while (true);
	}
	else
	{
		std::cout << "\nFile opened: " << fname << '\n';
		firstptr = ptr;
		while (true)
		{
			std::cout << "Pointer Location: " << ptr;
			file.getline(ptr->data,20);
			std::cout << " Data: " << ptr->data << '\n';
			if (file.eof())
				break;
			ptr->nextptr = new struct command;
			ptr = ptr->nextptr;
		}
	}
	file.close();
	std::cout << "---------------------------\n\n\n";
	return firstptr;
}

int size(char *data, int n)
{
	for (int i = 0; i < n; i++)
	{
		if (data[i] == '\0')
			return i;
	}
	return NULL;
}

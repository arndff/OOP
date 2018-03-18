#ifndef _MENU_HEADER_INCLUDED_
#define _MENU_HEADER_INCLUDED_

#include "Shape.h"
#include "Point.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include "API.h"
#include <string>

const size_t CMD_LEN = 200;
const size_t PATH_LEN = 100;

template <typename T>
void allocate(T*& dest, size_t size)
{
	dest = new T[size];
}

template <typename T>
void free(T** dest, size_t size)
{
	for (size_t i = 0; i < size; ++i)
	{
		delete[] dest[i];
	}

	delete[] dest;
}

void normalizeFilePath(char * path);
size_t args(const char * cmd);
char ** cmdToArray(const char * cmd, size_t& sz);

int parseFileCmd(const char * cmd, char * path);
void fileUtils(API& obj);

void createCmd(char ** arr, size_t size, API& obj);
void translateCmd(char ** arr, size_t size, API& obj);
void withinCmd(char ** arr, size_t size, API& obj);
void parseFigCmd(const char * cmd, API& obj);

void menu();

#endif _MENU_HEADER_INCLUDED_
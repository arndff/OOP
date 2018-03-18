#include <iostream>
#include "WordGame.h"

Table::Table()
	: m_table(nullptr)
	, m_row(0)
	, m_col(0)
{}

Table::Table(int row, int col)
	: m_row(row)
	, m_col(col)
{
	init();

	//user input
	for (int i = 0; i < m_row; ++i)
	{
		for (int j = 0; j < m_col; ++j)
		{
			std::cout << "table[" << i << "][" << j << "] = ";
			std::cin >> m_table[i][j];
		}
	}
}

Table::~Table() 
{
	destroy();
}

void Table::print() const 
{
	std::cout << "\n";

	for (int i = 0; i < m_row; ++i)
	{
		for (int j = 0; j < m_col; ++j)
		{
			std::cout << m_table[i][j] << " ";
		}
		
		std::cout << "\n";
	}
}

int Table::leftToRight(const char* word, int x, int y) const 
{
	int count = 0;
	size_t size = strlen(word);

	for (int j = y, count = 0; 
	     j < m_col && count < size && m_table[x][j] == word[count]; 
	     ++j, ++count) 
	{
		if (count == size - 1)
		{
			return 1;
		}
	}

	return 0;
}

int Table::rightToLeft(const char* word, int x, int y) const 
{
	int count = 0;
	size_t size = strlen(word);

	for (int j = y, count = 0; 
		 j >= 0 && count < size && m_table[x][j] == word[count]; 
	     --j, --count) 
	{
		if (count == size - 1)
		{
			return 1;
		}
	}

	return 0;
}

int Table::upToDown(const char* word, int x, int y) const 
{
	int count = 0;
	size_t size = strlen(word);
	
	for (int i = x, count = 0; 
	     i < m_row && count < size && m_table[i][y] == word[count]; 
	     ++i, ++count) 
	{
		if (count == size - 1)
		{
			return 1;
		}
	}

	return 0;
}

int Table::downToUp(const char* word, int x, int y) const {
	int count = 0;
	size_t size = strlen(word);
	
	for (int i = x, count = 0; 
		 i >= 0 && count < size && m_table[i][y] == word[count]; 
		 --i, ++count) 
	{	
		if (count == size - 1)
		{
			return 1;
		}
	}

	return 0;
}

int Table::LtoRLeftDiagonals(const char* word, int x, int y) const {
	int count = 0;
	size_t size = strlen(word);
	
	for (int i = x, j = y, count = 0;
		 i < m_row && j < m_col && count < size && m_table[i][j] == word[count];
		 ++i, ++j, ++count) 
	{
		if (count == size - 1)
		{
			return 1;
		}
	}
	
	return 0;
}

int Table::RtoLLeftDiagonals(const char* word, int x, int y) const {
	int count = 0;
	size_t size = strlen(word);
	
	for (int i = x, j = y, count = 0;
		 i >= 0 && j >= 0 && count < size && m_table[i][j] == word[count];
		 --i, --j, ++count) 
	{
		if (count == size - 1)
		{
			return 1;
		}
	}

	return 0;
}

int Table::LtoRRightDiagonals(const char* word, int x, int y) const {
	int count = 0;
	size_t size = strlen(word);
	
	for (int i = x, j = y, count = 0;
		 i < m_row && j >= 0 && count < size && m_table[i][j] == word[count];
		 ++i, --j, ++count) 
	{
		if (count == size - 1)
		{
			return 1;
		}
	}
	
	return 0;
}

int Table::RtoLRightDiagonals(const char* word, int x, int y) const {
	int count = 0;
	size_t size = strlen(word);
	
	for (int i = x, j = y, count = 0;
		 i >= 0 && j < m_col && count < size && m_table[i][j] == word[count];
		 --i, ++j, ++count) {
		if (count == size - 1)
		{
			return 1;
		}
	}
	
	return 0;
}

void Table::findWord(const char* word) const
{
	if (!word)
	{
		std::cout << "Invalid word has been passed.\n";
		return;
	}

	int count = 0;

	for (int i = 0; i < m_row; ++i)
	{
		for (int j = 0; j < m_col; ++j)
		{
			if (m_table[i][j] == word[0]) 
			{
				count += leftToRight(word, i, j);
				count += rightToLeft(word, i, j);
				count += upToDown(word, i, j);
				count += downToUp(word, i, j);
				count += LtoRLeftDiagonals(word, i, j);
				count += RtoLLeftDiagonals(word, i, j);
				count += LtoRRightDiagonals(word, i, j);
				count += RtoLRightDiagonals(word, i, j);
			}
		}
	}

	std::cout << "\n" << count << "\n";
}

void Table::init()
{
	m_table = new char*[m_row];
	for (int i = 0; i < m_row; ++i)
	{
		try
		{
			m_table[i] = new char[m_col];
		}
		catch (std::bad_alloc&)
		{
			for (int j = 0; j < i; ++j)
			{
				delete[] m_table[j];
			}
			
			delete[] m_table;
			throw std::bad_alloc();
		}
	}
}

void Table::destroy() 
{
	for (int i = 0; i < m_row; ++i)
	{
		delete[] m_table[i];
		m_table[i] = nullptr;
	}
	
	delete[] m_table;
	m_table = nullptr;
}

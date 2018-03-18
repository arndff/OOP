#include "API.h"
#include "Circle.h"
#include "Rectangle.h"
#include "Line.h"
#include <fstream>
#include <string>

API::API()
	: data(nullptr)
	, size(INITIAL_SIZE)
	, capacity(INITIAL_CAPACITY)
	, filePath(nullptr)
{
	allocate(data, capacity);
}

API::~API()
{
	destroy();
}

void API::setPath(const char* filePath)
{
	if (!filePath)
	{
		throw std::runtime_error("Invalid file name has been passed.\n");
	}
	else
	{
		allocate(this->filePath, strlen(filePath) + 1);
		strcpy(this->filePath, filePath);
	}
}

const char * API::getFileName() const
{
	size_t filePathLen;
	if (!filePath)
	{
		filePathLen = 0;
		std::cout << "There's no open file at the moment.\n";
		return nullptr;
	}
	else
	{
		filePathLen = strlen(filePath);
	}
	
	size_t fileNameLen = 0;
	for (int i = filePathLen - 1; i >= 0; --i)
	{
		if (filePath[i] != '/')
		{
			++fileNameLen;
		}
		else
		{
			break;
		}
	}

	char * fileName;
	allocate(fileName, fileNameLen + 1);

	if (filePathLen == fileNameLen)
	{
		strcpy(fileName, filePath);
		fileName[fileNameLen] = '\0';
		return fileName;
	}
	else
	{
		for (int i = filePathLen - 1, j = fileNameLen - 1; ; --i, --j)
		{
			if (filePath[i] != '/')
			{
				fileName[j] = filePath[i];
			}
			else
			{
				break;
			}
		}

		fileName[fileNameLen] = '\0';
		return fileName;
	}
}

void API::open(const char* path)
{
	if (filePath)
	{
		if (strcmp(filePath, path) != 0)
		{
			close();
		}
		else
		{
			return;
		}
			
	}

	if (!path)
	{
		throw std::runtime_error("Invalid path has been passed.\n");
	}
	else
	{
		std::ifstream in(path);
		if (!in) 
		{ 
			std::cout << "Problem with opening the file for reading...\n"; 
			return; 
		}

		setPath(path);
		readData(in);
		in.close();
		std::cout << "Successfully opened " << getFileName() << "\n";
	}
}

void API::close()
{
	if (filePath)
	{
		std::cout << "Successfully closed " << getFileName() << "\n";
		destroy();
	}
}

void API::save()
{
	if (!filePath)
	{
		throw std::runtime_error("Something went wrong... Maybe you've already closed your file.\n");
	}
	else
	{
		std::ofstream out(filePath, std::ios::trunc);
		if (!out) { std::cout << "Problem with opening the file for writing...\n"; return; }
		out << "<?xml version=\"1.0\" standalone=\"no\"?>\n";
		out << "<!DOCTYPE svg PUBLIC \" -//W3C//DTD SVG 1.1//EN\"\n";
		out << "<svg>\n";
		writeData(out);
		out << "</svg>\n";
		out.close();
		std::cout << "Successfully saved the changes to " << getFileName() << "\n";
	}
}

void API::saveAs(const char* newPath)
{
	if (!newPath)
	{
		throw std::runtime_error("Invalid new path has been passed.\n");
	}
	else
	{
		setPath(newPath);
		save();
	}
}

void API::readData(std::ifstream& in)
{
	char buff[1024];
	char c = '\0';
	while (!in.eof())
	{
		in.getline(buff, sizeof(buff) - 1);
		if (isSVGOpened(buff))
		{
			//loop will end when svg tag is gettin' closed
			while (true)
			{
				char * figName = readString(in);
				if (strcmp(figName, "svg") == 0)
				{
					break;
				}

				while (!isLetter(c)) { c = in.get(); } //skip spaces

				if (strcmp(figName, "circle") == 0)
				{
					parseCircle(in);
				}
				else if (strcmp(figName, "rect") == 0)
				{
					parseRect(in);
				}
				else if (strcmp(figName, "line") == 0)
				{
					parseLine(in);
				}
				else
				{
					while (in.get() != '\n') {};
				}
			}

			break;
		}
	}
}

void API::writeData(std::ofstream& out) const
{
	for (size_t i = 0; i < size; ++i)
	{
		data[i]->writeToFile(out);
	}
}

void API::create(const Shape* figure)
{
	if (size == capacity)
	{
		resize(2*size);
	}

	data[size++] = figure->clone();

	std::cout << "Successfully created " << figure->getName() << "(" << size << ")\n";
}

void API::erase(size_t idx)
{
	if (idx >= size)
	{
		std::cout << "There is no figure number " << idx << "!\n";
		return;
	}

	char * deletedFigName;
	allocate(deletedFigName, strlen(data[idx - 1]->getName()) + 1);
	strcpy(deletedFigName, data[idx-1]->getName());

	Shape** tmpData;
	allocate(tmpData, capacity);
	size_t j = 0;

	for (size_t i = 0; i < size; ++i)
	{
		if (i != idx - 1)
		{
			tmpData[j++] = data[i];
		}
	}

	delete[] data;
	data = tmpData;
	--size;

	if (size + 1 == capacity / 2)
	{
		resize(capacity/2);
	}

	std::cout << "Erased a " << deletedFigName << " (" << idx << ")\n";
}

void API::print() const
{
	for (size_t i = 0; i < size; ++i)
	{
		std::cout << i + 1 << ". ";
		data[i]->print();
	}
}

void API::translate(const Point& vec)
{
	for (size_t i = 0; i < size; ++i)
	{
		data[i]->translate(vec);
	}

	std::cout << "Translated all figures\n";
}

void API::translate(const Point& vec, size_t idx)
{
	if (idx >= size)
	{
		std::cout << "There is no figure number " << idx << "!\n";
		return;
	}

	data[idx]->translate(vec);
}

void API::within(const Point& center, double radius) const
{
	size_t cnt = 0;

	for (size_t i = 0; i < size; ++i)
	{
		if (data[i]->within(center, radius))
		{
			++cnt;
			data[i]->print();
		}
	}

	if (cnt == 0) 
	{ 
		std::cout << "No figures are located within circle " << center << " " << radius << "\n"; 
	}
}

void API::within(const Point& bottomLeft, double width, double height) const
{
	size_t cnt = 0;

	for (size_t i = 0; i < size; ++i)
	{
		if (data[i]->within(bottomLeft, width, height))
		{
			++cnt;
			data[i]->print();
		}
	}

	if (cnt == 0) 
	{ 
		std::cout << "No figures are located within rectangle " << bottomLeft << " " << width << " " << height << "\n";
	}
}

void API::resize(size_t newCapacity)
{
	Shape** tmp;
	allocate(tmp, newCapacity);
	for (size_t i = 0; i < size; ++i)
	{
		tmp[i] = data[i];
	}

	delete[] data;
	data = tmp;
	capacity = newCapacity;
}

void API::destroy()
{
	for (size_t i = 0; i < size; ++i)
	{
		delete data[i];
		data[i] = nullptr;
	}

	delete[] data;
	delete[] filePath;
	
	data = nullptr;
	filePath = nullptr;
	
	size = capacity = 0;
}

bool API::isLetter(char c) const
{
	return (c >= 'a' && c <= 'z') ||
	       (c >= 'A' && c <= 'Z') ||
	       (c >= '0' && c <= '9');
}
void API::goToNextAttr(std::istream& in) const
{
	size_t quote_cnt = 0;
	char c;

	while (quote_cnt != 1)
	{
		c = in.get();
		if (c == '\"') { ++quote_cnt; }
	}
}

void API::skipTillEnd(std::ifstream& in) const
{
	char c = '\0';

	while (c != '\n') { c = in.get(); }
}

bool API::isSVGOpened(const char buff[]) const
{
	size_t buff_len = strlen(buff);
	for (size_t i = 0; i < buff_len - 4; ++i)
	{
		if (buff[i]     == '<' && 
		    buff[i + 1] == 's' && 
		    buff[i + 2] == 'v' &&
		    buff[i + 3] == 'g' &&
		    buff[i + 4] == '>')
		{
			return true;
		}
	}

	return false;
}

char* API::readString(std::ifstream& in) const
{
	char c = '\0';
	size_t i = 0;

	const size_t arr_len = 20;

	while (!isLetter(c)) { c = in.get(); }

	char * arr;
	allocate(arr, arr_len + 1);
	memset(arr, 0, arr_len);

	while (isLetter(c))
	{
		arr[i++] = c;
		c = in.get();
	}
	
	arr[arr_len] = '\0';

	return arr;
}

void API::extractValue(std::ifstream& in, double& val) const
{
	char c = '\0';

	while (c != '\"') { c = in.get(); }
	in >> val; // "eat" all whitespaces
}

void API::parseCircle(std::ifstream& in)
{
	double cx, cy, r;

	extractValue(in, cx);
	goToNextAttr(in);

	extractValue(in, cy);
	goToNextAttr(in);

	extractValue(in, r);
	goToNextAttr(in);

	char c = '\0';
	while (c != '\"') { c = in.get(); }

	char * fill = readString(in);

	Point center(cx, cy);
	Circle circle(fill, center, r);
	if (size == capacity) { resize(2*size); }
	data[size++] = circle.clone();

	delete[] fill;

	skipTillEnd(in);
}

void API::parseRect(std::ifstream& in)
{
	double x, y, width, height;

	extractValue(in, x);
	goToNextAttr(in);

	extractValue(in, y);
	goToNextAttr(in);

	extractValue(in, width);
	goToNextAttr(in);

	extractValue(in, height);
	goToNextAttr(in);

	char c = '\0';
	while (c != '\"') { c = in.get(); }

	char * fill = readString(in);

	Point bl(x, y);
	Rectangle rect(fill, bl, width, height);
	if (size == capacity) { resize(2*size); }
	data[size++] = rect.clone();

	delete[] fill;

	skipTillEnd(in);
}

void API::parseLine(std::ifstream& in)
{
	double x1, y1, x2, y2;

	extractValue(in, x1);
	goToNextAttr(in);

	extractValue(in, y1);
	goToNextAttr(in);

	extractValue(in, x2);
	goToNextAttr(in);

	extractValue(in, y2);
	goToNextAttr(in);

	char c = '\0';
	while (c != '\"') { c = in.get(); }

	char * fill = readString(in);

	Point a(x1, y1);
	Point b(x2, y2);
	Line line(fill, a, b);
	if (size == capacity) { resize(2*size); }
	data[size++] = line.clone();

	delete[] fill;

	skipTillEnd(in);
}

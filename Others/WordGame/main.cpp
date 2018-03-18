#include <iostream>
#include "WordGame.h"

/*
i v a n
e v n h
i n a v
m v i n
q r i t
*/

void test()
{
	Table t(5, 4);
	t.print();
	t.findWord("ivan");
}

int main()
{
	test();

	return 0;
}
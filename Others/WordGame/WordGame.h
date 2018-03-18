#ifndef WORD_GAME_HEADER_INCLUDED__
#define WORD_GAME_HEADER_INCLUDED__

class Table 
{
public:
	Table();
	Table(int, int);
	~Table();

	Table(const Table&) = delete;
	Table& operator=(const Table&) = delete;

public:	
	void findWord(const char*) const;
	void print() const;

private:
	int leftToRight(const char*, int, int) const;
	int rightToLeft(const char*, int, int) const;
	int upToDown(const char*, int, int) const;
	int downToUp(const char*, int, int) const;
	int LtoRLeftDiagonals(const char*, int, int) const;
	int RtoLLeftDiagonals(const char*, int, int) const;
	int LtoRRightDiagonals(const char*, int, int) const;
	int RtoLRightDiagonals(const char*, int, int) const;

private:
	void init();
	void destroy();

private:
	char** m_table;
	int m_row, m_col; //used for dimensions of the table
};

#endif // !WORD_GAME_HEADER_INCLUDED__
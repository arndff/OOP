#ifndef _SOLDIER_HEADER_
#define _SOLDIER_HEADER_

class Soldier
{
public:
	Soldier();
	Soldier(const char *, size_t, size_t, size_t);
	Soldier(const Soldier&);
	Soldier& operator=(const Soldier&);
	virtual ~Soldier();

public:
	void setName(const char *);
	void setAge(size_t);
	void setLevel(size_t);
	void setSalary(size_t);
	
	const char * getName() const { return name; }
	size_t getAge() const { return age; }
	size_t getLevel() const { return level; }
	size_t getSalary() const { return salary; }
	
protected:
	char * setNameHelper(const char *);

	void copy(const Soldier&);
	void destroy();

protected:
	char * name;
	size_t age;
	size_t level;
	size_t salary;
};

#endif // !_SOLDIER_HEADER_
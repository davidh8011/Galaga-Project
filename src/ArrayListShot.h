#pragma once
#include "Shot.h"
class ArrayListShot
{
	int length; //how many elements we have in the arraylist
	int capacity{}; //the real capacity of the dynamic array
	int cache{ 10 }; //how much to enlarge capacity each time
	Shot* data{}; //for creating dynamic array of chars
	void resize(); //if capacity is full, we enlarge it.
public:
	//ArrayList();
	void add(Shot);
	void add(int, Shot);
	void output();
	void clear();
	void remove(int index);
	Shot get(int);
	int getCapacity();
	int size();
	bool isEmpty();
	~ArrayListShot();
};
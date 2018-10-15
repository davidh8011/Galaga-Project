#pragma once
class ArrayList
{
	int length; //how many elements we have in the arraylist
	int capacity{}; //the real capacity of the dynamic array
	int cache{ 10 }; //how much to enlarge capacity each time
	int* data{}; //for creating dynamic array of chars
	void resize(); //if capacity is full, we enlarge it.
public:
	//ArrayList();
	void add(int);
	void add(int, int);
	void output();
	void clear();
	void remove(int index);
	int get(int);
	int getCapacity();
	int size();
	bool isEmpty();
	~ArrayList();
};
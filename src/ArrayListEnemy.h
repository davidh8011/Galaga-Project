#pragma once
#include "Enemy1.h"
class ArrayListEnemy
{
	int length; //how many elements we have in the arraylist
	int capacity{}; //the real capacity of the dynamic array
	int cache{ 10 }; //how much to enlarge capacity each time
	Enemy1* data{}; //for creating dynamic array of chars
	void resize(); //if capacity is full, we enlarge it.
public:
	//ArrayList();
	void add(Enemy1);
	void add(int, Enemy1);
	void output();
	void clear();
	void remove(int index);
	Enemy1& get(int);
	int getCapacity();
	int size();
	bool isEmpty();
	~ArrayListEnemy();
};
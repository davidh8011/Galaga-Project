#include "ArrayListEnemy.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

/*
ArrayList::ArrayList()
{
}
*/

void ArrayListEnemy::resize()
{
	if (data == nullptr)
	{
		capacity = cache;
		data = new Enemy1[capacity];
	}
	else if (length == capacity)
	{
		capacity += cache;
		Enemy1* temp{ data };//backup the original dynamic array to temp
		data = new Enemy1[capacity];//created a new empty enlarged dynamic array
		for (unsigned i{}; i != length; i++)
			data[i] = temp[i];
	}
}

void ArrayListEnemy::add(Enemy1 datum)
{
	resize();
	data[length] = datum;
	length++;
}

void ArrayListEnemy::add(int index, Enemy1 datum)
{
	if(index>=0 && index<=length)
	{
		resize();
		for (int i{ length }; i > index; i--)
			data[i] = data[i - 1];
		data[index] = datum;
		length++;
	}
	else
		cerr << "Invalid index add!\n";
}

void ArrayListEnemy::clear() {
	delete[] data;
	data = nullptr;
	capacity = length = 0;

}

void ArrayListEnemy::remove(int index) {
	if (index >= 0 && index <= length)
	{
		for (int i{index}; i != length - 1; i++)
			data[i] = data[i + 1];
		length--;
	}
	//else
		//cerr << "Invalid index remove!\n";

}

Enemy1& ArrayListEnemy::get(int index) {
	if(index >=0 && index < length)
		return data[index];
	else
	{
		//cerr << "Invalid index get\n";
		resize();
		return data[length];//null terminate character
	}
}

void ArrayListEnemy::output() {
	for (int i{}; i < length; i++)
	{
		//cout << data[i] << ' ';
	}
	cout << endl;
}

int ArrayListEnemy::getCapacity()
{
	return capacity;
}

int ArrayListEnemy::size()
{
	return length;
}

bool ArrayListEnemy::isEmpty()
{
	return length == 0;
}

ArrayListEnemy::~ArrayListEnemy()
{
	delete[] data;
	data = nullptr;
}
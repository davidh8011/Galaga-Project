#include "ArrayList2.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

/*
ArrayList::ArrayList()
{
}
*/

void ArrayList::resize()
{
	if (data == nullptr)
	{
		capacity = cache;
		data = new int[capacity];
	}
	else if (length == capacity)
	{
		capacity += cache;
		int* temp{ data };//backup the original dynamic array to temp
		data = new int[capacity];//created a new empty enlarged dynamic array
		for (unsigned i{}; i != length; i++)
			data[i] = temp[i];
	}
}

void ArrayList::add(int datum)
{
	resize();
	data[length] = datum;
	length++;
}

void ArrayList::add(int index, int datum)
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

void ArrayList::clear() {
	delete[] data;
	data = nullptr;
	capacity = length = 0;

}

void ArrayList::remove(int index) {
	if (index >= 0 && index <= length)
	{
		for (int i{index}; i != length - 1; i++)
			data[i] = data[i + 1];
		length--;
	}
	//else
	//	cerr << "Invalid index remove!\n";

}

int ArrayList::get(int index) {
	if(index >=0 && index < length)
		return data[index];
	else
	{
		//cerr << "Invalid index get\n";
		return '\0';//null terminate character
	}
}

void ArrayList::output() {
	for (int i{}; i < length; i++)
	{
		cout << data[i] << ' ';
	}
	cout << endl;
}

int ArrayList::getCapacity()
{
	return capacity;
}

int ArrayList::size()
{
	return length;
}

bool ArrayList::isEmpty()
{
	return length == 0;
}

ArrayList::~ArrayList()
{
	delete[] data;
	data = nullptr;
}
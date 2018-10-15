#include "ArrayListShot.h"
#include <iostream>

using std::cout;
using std::endl;
using std::cerr;

/*
ArrayList::ArrayList()
{
}
*/

void ArrayListShot::resize()
{
	if (data == nullptr)
	{
		capacity = cache;
		data = new Shot[capacity];
	}
	else if (length == capacity)
	{
		capacity += cache;
		Shot* temp{ data };//backup the original dynamic array to temp
		data = new Shot[capacity];//created a new empty enlarged dynamic array
		for (unsigned i{}; i != length; i++)
			data[i] = temp[i];
	}
}

void ArrayListShot::add(Shot datum)
{
	resize();
	data[length] = datum;
	length++;
}

void ArrayListShot::add(int index, Shot datum)
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

void ArrayListShot::clear() {
	delete[] data;
	data = nullptr;
	capacity = length = 0;

}

void ArrayListShot::remove(int index) {
	if (index >= 0 && index <= length)
	{
		for (int i{index}; i != length - 1; i++)
			data[i] = data[i + 1];
		length--;
	}
	else
		cerr << "Invalid index remove!\n";

}

Shot ArrayListShot::get(int index) {
	if(index >=0 && index < length)
		cerr << "Invalid index get\n";
	return data[index];
	//else
	//{
	//	cerr << "Invalid index get\n";
	//	return Ship();//null terminate character
	//}
}

void ArrayListShot::output() {
	for (int i{}; i < length; i++)
	{
		//cout << data[i] << ' ';
	}
	cout << endl;
}

int ArrayListShot::getCapacity()
{
	return capacity;
}

int ArrayListShot::size()
{
	return length;
}

bool ArrayListShot::isEmpty()
{
	return length == 0;
}

ArrayListShot::~ArrayListShot()
{
	delete[] data;
	data = nullptr;
}
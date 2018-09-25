#pragma once


#include <iostream>
#include <vector>
#include <string>


using namespace std;


template<typename T>
struct Node
{
	T value;
	Node *next = nullptr;
	Node(T value) : value(value) {}
};

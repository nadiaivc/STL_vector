#define _GNU_SOURCE
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <stdio.h>
#include <windows.h>
#include <algorithm>
#include <string>
#include "vector.h"
#include <vector>
using namespace std;

struct Item
{
	int a, b, c;
	Item() :a(0), b(0), c(0) {};
	Item(int a, int b, int c) :a(a), b(b), c(c) {}
};

void string_test()
{
	cout << "//////------------- STRING TEST --------------//////" << endl;
	myVector<std::string> check1;
	check1.push_back("Hello");
	check1.push_back("programmist");
	check1.push_back("i'm");
	check1.push_back("vector");
	myVector<std::string>::Iterator it;
	for (it = check1.begin(); it != check1.end(); it++)
	{
		std::cout << *it << std::endl;
	}
	cout << " " << endl;

	it = check1.begin();
	it += 3;
	cout << "Iterator before insert: " << *it << endl;
	myVector<string>::Iterator new_it = check1.insert(it, "super");
	cout << "Iterator after insert: " << *new_it << endl;

	cout << " " << endl;
	for (it = check1.begin(); it != check1.end(); ++it)
	{
		cout << *it << endl;
	}

	new_it = check1.begin() + 1;
	cout << "Iterator before erase: " << *new_it << endl;
	new_it = check1.erase(new_it);
	cout << "Iterator after erase: " << *new_it << endl;

	cout << " " << endl;
	for (it = check1.begin(); it != check1.end(); ++it)
	{
		cout << *it << endl;
	}

	check1.push_back("can");
	check1.push_back("it");
	check1.push_back("work");
	check1.push_back("well");
	check1.push_back("?");
	check1.push_back("it");
	check1.push_back("can");


	sort(check1.begin(), check1.end());

	cout << "Sorted: " << endl;
	for (it = check1.begin(); it != check1.end(); ++it)
	{
		cout << "Index: " << it.GetIndex() << " " << *it << endl;
	}
	cout << " " << endl;

	check1.resize(3);
	cout << "Resize(3):  ";
	for (int i = 0; i < check1.size(); i++)
		cout << check1[i] << " "; cout << endl;

	myVector<string> check2(3, "Hello");
	myVector<string>::Iterator itt = check2.begin();
	itt += 2;
	*itt = "vector";
	check2[1] = "i'm";
	for (itt = check2.begin(); itt != check2.end(); ++itt)
	{
		cout << "Index: " << itt.GetIndex() << " " << *itt << endl;
	}

	cout << " " << endl;
	if (check1 == check2)
	{
		cout << "Check1 == Check2" << endl;
	}

	check2.push_back("string");
	if (check1 != check2)
	{
		cout << "Check1 != Check2" << endl;
	}
	cout << endl;
	check2.clear();
	check2.push_back("It");
	check2.push_back("was");
	check2.push_back("clear");
	for (itt = check2.begin(); itt != check2.end(); ++itt)
	{
		cout << *itt << endl;
	}
}

void int_test() {
	cout << endl << endl;
	cout << "//////------------- INTEGER TEST --------------//////" << endl;
	myVector<int> check1;
	check1.push_back(1);
	check1.push_back(2);
	check1.push_back(3);
	cout << "check1:  ";
	myVector<int>::Iterator it;
	for (it = check1.begin(); it != check1.end(); it++)
	{
		cout << *it << "  ";
	}cout << endl << endl;

	it = check1.begin();
	it += 1;
	cout << "Iterator before insert: " << *it << endl;
	myVector<int>::Iterator new_it = check1.insert(it, 8);
	cout << "Iterator after insert: " << *new_it << endl;

	cout << "check1:  ";
	for (it = check1.begin(); it != check1.end(); it++)
	{
		cout << *it << "  ";
	}cout << endl << endl;

	myVector<int> check2(check1);
	if (check1 != check2)
		cout << "check1 != check2" << endl;
	if (check1 == check2)
		cout << "check1 == check2" << endl;
	if (check1 < check2)
		cout << "check1 < check2" << endl;
	if (check1 > check2)
		cout << "check1 > check2" << endl;

	check1.emplace_back(5);
	cout << "emplace_back(5)" << endl;
	for (it = check1.begin(); it != check1.end(); it++)
	{
		cout << *it << "  ";
	}cout << endl << endl;

	myVector<int>::reverse_Iterator it2;
	cout << "Reverse iterator" << endl;
	for (it2 = check1.rbegin(); it2 != check1.rend(); it2++)
	{
		cout << *it2 << "  ";
	}cout << endl << endl;
	

	check1.push_back(11);
	check1.push_back(55);
	sort(check1.begin(), check1.end());
	cout << "Sorted: " << endl;
	for (it = check1.begin(); it != check1.end(); ++it)
	{
		cout << "Index: " << it.GetIndex() << "   " << *it << endl;
	}
	cout << endl;

	check1.resize(3);
	cout << "Resize(3):  ";
	for (int i = 0; i < check1.size(); i++)
		cout << check1[i] << " "; cout << endl;
}


int main() {
	string_test();
	int_test();
	
	cout << endl << endl;
	cout << "//////------------- Struct Test (emplace / emplace_back) --------------//////" << endl;
	myVector<Item>::Iterator itt;
	myVector<Item> vecItem;
	vecItem.emplace_back(1, 2, 3);
	vecItem.emplace_back(4, 5, 6);
	cout << "emplace(++begin(), 9, 9, 9)" << endl;
	itt = vecItem.begin();
	itt++;
	vecItem.emplace(itt, 9, 9, 9);
	for (int i = 0; i < vecItem.size(); i++)//итератором пройти не выйдет тут
	{
		cout << vecItem[i].a <<", " << vecItem[i].b << ", " << vecItem[i].c << endl;
	}
	vecItem.clear();
	cout << "clear + emplace_back(11, 11, 11)" << endl;
	vecItem.emplace_back(11, 11, 11);
	for (int i = 0; i < vecItem.size(); i++)
	{
		cout << vecItem[i].a << ", " << vecItem[i].b << ", " << vecItem[i].c << endl;
	}

cout << endl << endl;
	cout << "//////------------- For crossword --------------//////" << endl;
	myVector<string> testString;
	testString.pushWithSort("helloo");
	testString.pushWithSort("you");
	testString.pushWithSort("can");
	testString.pushWithSort("check");
	testString.pushWithSort("myOnlyStringSort");
	for (int i = 0; i < testString.size(); i++)
	{
		cout << testString[i] << endl;
	}
	//myVector<int> error;
	//error.pushWithSort(1);
	return 0;
}
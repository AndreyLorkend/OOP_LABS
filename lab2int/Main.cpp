#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <string>
#include <iterator>
#include <set>
#include <random>
#include <locale>

using namespace std;

class BitComp {
public:
	bool operator() (const int & firstN, const int & secondN) const
	{
		return firstN < secondN;
	}
};

void addByFirst(set<int, BitComp>& container);
void setPrinter(set<int, BitComp>& container);
void fillSet(set<int, BitComp>& container, int numbersCount);
void valueDeleter(set<int, BitComp>& container, int value);
void positionDeleter(set<int, BitComp>& container, int position);

int main() {
	setlocale(0, "russian");
	int deletingValue;
	set<int, BitComp> numberContainer;
	fillSet(numberContainer, 10);
	cout << "\nМножество содержит: " << numberContainer.size() << " элементов\n";
	cout << "\nМножество до удаления элемента:\n";
	setPrinter(numberContainer);

	//cin >> deletingValue;

	//positionDeleter(numberContainer, deletingValue);
	addByFirst(numberContainer);
	//valueDeleter(numberContainer, deletingValue);
	cout << "\nМножество после удаления элемента:\n";
	setPrinter(numberContainer);
	return 0;
}

void setPrinter(set<int, BitComp>& container) {
	ofstream fileOut("output.txt");
	for (set<int>::iterator it = container.begin(); it != container.end(); it++)
	{
		cout << *it << "\n";
	}
	copy(container.begin(), container.end(), ostream_iterator<int>(fileOut, "\n"));
	cout << "\n";
}

void fillSet(set<int, BitComp>& container, int numbersCount)
{
	//random_device rd;
	//mt19937 generator(rd());
	for (int i = 0; i < numbersCount; i++) {
		container.insert(i*21+45);
	}
}

void valueDeleter(set<int, BitComp>& container, int value)
{
	container.erase(container.find(value));
}

void positionDeleter(set<int, BitComp>& container, int position) {
	if (position <= (container.size() - 1)) {
		set <int>::iterator deleter = container.begin();
		advance(deleter, position);
		container.erase(deleter);
	}
	else {
		cout << "Неверно введена позиция!\nПоследний элемент множества имеет позицию: " << container.size() - 1 << "\n";
	}
}

void addByFirst(set<int, BitComp>& container) {
	set<int, BitComp> tempSet;
	set <int>::iterator firstElement = container.begin();
	for (auto value : container) {
		tempSet.insert(value + *firstElement);
	}
	container.swap(tempSet);
}
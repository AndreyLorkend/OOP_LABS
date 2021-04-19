#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <string>
#include <iterator>
#include <map>
#include <random>
#include <functional>

using namespace std;

void mapPrinter(map<int, bitset<32>> & container);
void fillMap(map<int, bitset<32>> & container, int numbersCount);
bool bitComp(const pair<int, bitset<32> > & firstN, const pair<int, bitset<32> > & secondN);

int main() {
	map<int, bitset<32>> numbersContainer;
	fillMap(numbersContainer, 10);
	map<int, bitset<32>>::iterator result = max_element(numbersContainer.begin(), numbersContainer.end(), bitComp);
	auto lastElement = numbersContainer.rbegin()->first;
	mapPrinter(numbersContainer);
	cout << "Max element: " << static_cast<int>(result->second.to_ulong()) << "\n\n";
	numbersContainer.insert(make_pair(lastElement + 1, result->second));
	mapPrinter(numbersContainer);
	return 0;
}

void mapPrinter(map<int, bitset<32>> & container) {
	ofstream fileOut("output.txt");
	for (map<int, bitset<32>>::iterator it = container.begin(); it != container.end(); it++)
	{
		cout << it->first << " => " << static_cast<int>(it->second.to_ulong()) << "\n";
	}
	for (auto element : container) {
		fileOut << element.first <<  ": " << (int)(element.second.to_ulong()) << endl;
	}
	cout << "\n";
}

void fillMap(map<int, bitset<32>> & container, int numbersCount)
{
	random_device rd;
	mt19937 generator(rd());
	for (int i = 0; i < numbersCount; i++) {
		container.insert(make_pair(i, generator()));
	}
}

bool bitComp(const pair<int, bitset<32>> & firstN, const pair<int, bitset<32>> & secondN) {
	return static_cast<int>(firstN.second.to_ulong()) < static_cast<int>(secondN.second.to_ulong());
}
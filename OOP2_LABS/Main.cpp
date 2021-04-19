//15. Найти максимальный элемент и добавить его в конец контейнера.
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <bitset>

using namespace std;

bool bitComp(bitset<32> & first, bitset<32> & second);

void fillList(vector<bitset<32>> * numbersList, int numbersCount);

int main() {
	vector<bitset<32>> numbersList;

	fillList(&numbersList, 10);
	for (auto element : numbersList) {
		cout << static_cast<int>(element.to_ulong()) << "\n";
	}

	cout << "\n";
	auto result = max_element(numbersList.begin(), numbersList.end(), bitComp);
	numbersList.push_back(*result);
	cout << "Max element: " << static_cast<int>((*result).to_ulong()) << ", Index: " << distance(numbersList.begin(), result) << "\n\n";

	for (auto element : numbersList) {
		cout << static_cast<int>(element.to_ulong()) << "\n";
	}
	return 0;
}

void fillList(vector<bitset<32>>* numbersList, int numbersCount)
{
	random_device rd;
	mt19937 generator(rd());
	for (int i = 0; i < numbersCount; i++) {
		numbersList->push_back(generator());
	}
}

bool bitComp(bitset<32>& first, bitset<32>& second) {
	return static_cast<int>(first.to_ulong()) < static_cast<int>(second.to_ulong());
}
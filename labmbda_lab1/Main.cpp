//15. Найти максимальный элемент и добавить его в конец контейнера.
#include <iostream>
#include <algorithm>
#include <random>
#include <vector>
#include <bitset>
#include <iterator>

using namespace std;

class Print
{
public:
	Print(ostream& out) : pOut_(&out) {}
	void operator()(bitset<32>& d) 
	{ 
		(*pOut_) << static_cast<int>(d.to_ulong()) << endl; 
	}
private:
	ostream* pOut_;
};

int main() {
	vector<bitset<32>> numbersList;
	random_device rd;
	mt19937 generator(rd());

	generate_n(back_inserter(numbersList), 10, [&]() {
			return generator();
		});

	for_each(numbersList.begin(), numbersList.end(), [](bitset<32> value) {
			cout << static_cast<int>(value.to_ulong()) << "\n";
		});

	auto result = max_element(numbersList.begin(), numbersList.end(), [](bitset<32> first, bitset<32> second) {
			return static_cast<int>(first.to_ulong()) < static_cast<int>(second.to_ulong());
		});

	numbersList.push_back(*result);

	cout << "\nMax element: " << static_cast<int>((*result).to_ulong()) << ", Index: " << distance(numbersList.begin(), result) << "\n\n";

	try
	{
		if (static_cast<int>((*result).to_ulong()) > 1000000000000) {
			throw static_cast<int>((*result).to_ulong());
		}
	}
	catch (int)
	{
		cout << "Error\n\n";
	}

	for_each(numbersList.begin(), numbersList.end(), Print(cout));

	return 0;
}

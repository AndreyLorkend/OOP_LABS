#include <iostream>
#include <fstream>
#include <algorithm>
#include <bitset>
#include <string>
#include <iterator>
#include <set>
#include <random>
#include <locale>
#include <conio.h>

using namespace std;

class BitComp {
public:
	bool operator() (const bitset<32> & firstN, const bitset<32> & secondN) const
	{
		return static_cast<int>(firstN.to_ulong()) < static_cast<int>(secondN.to_ulong());
	}
};

void addByFirst(set<bitset<32>, BitComp>& container);
void setPrinter(set<bitset<32>, BitComp> & container);
void fillSet(set<bitset<32>, BitComp>& container, int numbersCount);
void valueDeleter(set<bitset<32>, BitComp>& container, int value);
void positionDeleter(set<bitset<32>, BitComp>& container, int position);
void openConsoleMenu();
void processTheChoice(int choice, set<bitset<32>, BitComp>& container);

int main() {
	setlocale(0, "russian");
	openConsoleMenu();
	return 0;
}

void setPrinter(set<bitset<32>, BitComp>& container) {
	for (set<bitset<32>>::iterator it = container.begin(); it != container.end(); it++)
	{
		cout << static_cast<int>(it->to_ulong()) << "\n";
	}
	cout << "\n";
}

void fillSet(set<bitset<32>, BitComp>& container, int numbersCount)
{
	random_device rd;
	mt19937 generator(rd());
	for (int i = 0; i < numbersCount; i++) {
		container.insert(generator());
	}
}

void valueDeleter(set<bitset<32>, BitComp>& container, int value)
{
	container.erase(container.find(value));
}

void positionDeleter(set<bitset<32>, BitComp>& container, int position) {
	if (position <= (container.size() - 1)) {
		set <bitset<32>>::iterator deleter = container.begin();
		advance(deleter, position);
		container.erase(deleter);
	} else {
		cout << "������� ������� �������!\n��������� ������� ��������� ����� �������: " << container.size() - 1 << "\n";
	}
}

void addByFirst(set<bitset<32>, BitComp>& container) {
	set<bitset<32>, BitComp> tempSet;
	set <bitset<32>>::iterator firstElement = container.begin();
	for (auto value : container) {
		tempSet.insert(static_cast<bitset<32>>(static_cast<int>(value.to_ulong()) + static_cast<int>(firstElement->to_ulong())));
	}
	container.swap(tempSet);
}

void openConsoleMenu() {
	int actionChoice = 0;
	set<bitset<32>, BitComp> numberContainer;
	fillSet(numberContainer, 10);
	while (actionChoice != 4) {
		system("CLS");
		cout << "===== �������� �������� =====\n";
		cout << "1) ������� ������� �� �������.\n";
		cout << "2) ������� ������� �� �������.\n";
		cout << "3) ��������� ��� �������� �� �������� ������� ��������.\n";
		cout << "4) �����.\n";
		cin >> actionChoice;
		if (cin.good()) {
			processTheChoice(actionChoice, numberContainer);
		} else {
			cout << "������������ ����� ��������!\n������� ����� �������, ����� ����������...\n";
			cin.clear();
			cin.ignore();
			_getch();
		}
	}
	ofstream fileOut("output.txt");
	copy(numberContainer.begin(), numberContainer.end(), ostream_iterator<bitset<32>>(fileOut, "\n"));
	cout << "������ �� ��������� numberContainer ���� �������� � ���� output.txt\n";
}

void processTheChoice(int choice, set<bitset<32>, BitComp>& container) {
	system("CLS");
	switch (choice)
	{
	case 1: {
		int deletingValue;
		cout << "\n��������� ��������: " << container.size() << " ���������\n";
		cout << "\n��������� �� �������� ��������:\n";
		setPrinter(container);
		cout << "������� ������� ���������� ��������.\n";
		cin >> deletingValue;
		positionDeleter(container, deletingValue);
		cout << "\n��������� ����� �������� ��������:\n";
		setPrinter(container);
	}
		break;
	case 2: {
		int deletingValue;
		cout << "\n��������� ��������: " << container.size() << " ���������\n";
		cout << "\n��������� �� �������� ��������:\n";
		setPrinter(container);
		cout << "������� �������� ���������� ��������.\n";
		cin >> deletingValue;
		valueDeleter(container, deletingValue);
		cout << "\n��������� ����� �������� ��������:\n";
		setPrinter(container);
	}
		break;
	case 3: {
		cout << "\n��������� ��������: " << container.size() << " ���������\n";
		cout << "\n��������� �� ����������� ������� �������� �� ����:\n";
		setPrinter(container);
		addByFirst(container);
		cout << "\n��������� ����� ����������� ������� �������� �� ����:\n";
		setPrinter(container);
	}
		break;
	default:
		cout << "�������� ��������!\n";
		break;
	}
	cout << "������� ����� �������, ����� ����������...\n";
	_getch();
}
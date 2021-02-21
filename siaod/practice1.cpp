// siaod.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <iostream>
#include <time.h>
#include <cstdlib>

void task1();
void task2();
void delFirstMetod(int*, int&, int);
void delOtherMetod(int*, int&, int);
void fillRandom(int*, int, int);
void printArray(int*, int);
void maxValue(int*, int);


int main() {
	setlocale(LC_ALL, "rus");
	srand(time(0));

	task2();
};


void task1() {
	int n = 100, key;
	int* x = new int[n];
	
	fillRandom(x, n, 0);
	printArray(x, n);
	
	std::cout << "Key -> "; std::cin >> key;
	
	//delFirstMetod(x, n, key);
	delOtherMetod(x, n, key);
	
	printArray(x, n);
	
	delete[] x;
}

void task2() {
	int n = 10;
	int* x = new int[n];

	//fillRandom(x, n, 10);
	//printArray(x, n);
	for (int i = 0; i < n; ++i) {
		x[i] = i;
	}
	printArray(x, n);

	maxValue(x, n);

	delete[] x;
}

void maxValue(int *x, int n) {
	int max = std::numeric_limits<int>::min(),
		maxAmount = 0, a = 0, b = 0, c = 0, d = 0;

	for (int i = 0; i < n; ++i) {
		++a;
		if (x[i] > max) {
			max = x[i];
			maxAmount = 1;
			++b;
		}
		else {
			++c;
			if (x[i] == max) {
				++maxAmount;
				++d;
			}
		}
	}

	std::cout << "Amount: " << maxAmount << "\n";
	std::cout << "a = " << a << "\nb = " << b << "\nc = " << c <<"\nd = " << d;
}

void delFirstMetod(int *x, int &n, int key) {
	int i = 0, comps = 0, dels = 0;

	while (i < n) {
		++comps;
		if (x[i] == key) {
			for (int j = i; j < n - 1; ++j) {
				x[j] = x[j + 1];
				++dels;
			}
			--n;
		}
		else {
			++i;
		}
	}

	std::cout << "Сравнений: " << comps << "\nУдалений: " << dels << "\n";
}

void delOtherMetod(int *x, int &n, int key) {
	int j = 0, comps = 0, dels = 0;

	for (int i = 0; i < n; ++i) {
		x[j] = x[i];
		++comps;
		if (x[i] != key) {
			++j;
			++dels;
		}
	}
	n = j;

	std::cout << "Сравнений: " << comps << "\nУдалений: " << dels << "\n";
}

void fillRandom(int* x, int n, int max) {
	for (int i = 0; i < n; ++i) {
		x[i] = rand() % (max + 1);
	}
}

void printArray(int* x, int n) {
	for (int i = 0; i < n; ++i) {
		std::cout << x[i] << " ";
	}
	std::cout << "\n";
}

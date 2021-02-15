#include <iostream>
#include <iostream>
#include <time.h>
#include <cstdlib>
/* run this program using the console pauser or add your own getch, system("pause") or input loop */
int delFirstMetod(int *, int, int);
int delOtherMetod(int *, int, int);
void fillRandom(int *, int, int);
void printArray(int *, int);

int main(int argc, char** argv) {
	srand(time(0));
	
	int n, key, max;
//	max - ìàêñèìàëüíîå ÷èñëî äëÿ ðàíäîìà
	std::cin >> n >> key >> max;
	int *x = new int[n];
	
//	for (int i = 0; i < n; ++i) {
//		std::cin >> x[i];
//		
//	}
	fillRandom(x, n, max);
	printArray(x, n);
	
//	n = delFirstMetod(x, n, key);
//	n = delOtherMetod(x, n, key);
	
	printArray(x, n);
};

int delFirstMetod(int *x, int n, int key) {
	int i = 0;
	while (i < n) {
		if (x[i] == key) {
			for (int j = i; j <= n-1; ++j) {
				x[j] = x[j+1];
			}
			n--;
		} else {
			i++;
		}
	}
	return n;
}

int delOtherMetod(int *x, int n, int key) {
	int j = 0;
	for (int i = 0; i < n; ++i) {
		x[j] = x[i];
		if (x[i] != key) j++;
	};
	return j;
}

void fillRandom(int *x, int n, int max) {
	for (int i = 0; i < n; ++i) {
		x[i] = rand() % (max + 1);
	}
}

void printArray(int *x, int n) {
	for(int i = 0; i < n; ++i) {
		std::cout << x[i] << " ";
	}
	std::cout << "\n";
}

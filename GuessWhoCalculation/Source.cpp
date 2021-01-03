#include <iostream>
#include <unordered_map>
#include <ctime>
#include <cstdlib>
#include <algorithm>
#include <random>

using namespace std;

static int counter = 0;

void askIt(int k) {
	if (k > 24)
		counter++;
}

int generateRandomPC(int playersNumber) {
	srand(time(NULL));
	return (1 + rand() % playersNumber);
}

int generateRandomUser(int playersNumber) {
	std::random_device rd;
	uniform_int_distribution<int> ud(1, playersNumber);
	mt19937 mt(rd());
	return ud(mt);
}

unordered_map<int, int> strategy1(int MAX, int playersNumber) {
	unordered_map<int, int> umap;
	int iterations = 0;
	while (iterations < MAX) {
		bool guessed = false;
		int randomPC = generateRandomPC(playersNumber);
		int falseAttempts = 0;
		while (!guessed) {
			int randomPlayer = generateRandomUser(playersNumber);
			if (randomPC == randomPlayer) {
				askIt(falseAttempts);
				umap[iterations] = falseAttempts;
				iterations++;
				guessed = true;
			}
			else {
				falseAttempts++;
			}
		}
	}
	return umap;
}

unordered_map<int, int> strategy2(int MAX, int playersNumber) {
	unordered_map<int, int> umap;
	int iterations = 0;
	while (iterations < MAX) {
		bool guessed = false;
		int falseAttempts = 0;
		while (!guessed) {
			int randomPC = generateRandomPC(playersNumber);
			int randomPlayer = generateRandomUser(playersNumber);
			if (randomPC == randomPlayer) {
				askIt(falseAttempts);
				umap[iterations] = falseAttempts;
				iterations++;
				guessed = true;
			}
			else {
				falseAttempts++;
			}
		}
	}
	return umap;
}

unordered_map<int, int> strategy3(int MAX, int playersNumber) {
	int helper = 0;
	unordered_map<int, int> umap;
	int iterations = 0;
	while (iterations < MAX) {
		int randomPC;
		bool guessed = false;
		int falseAttempts = 0;
		while (!guessed) {
			if(helper%3 == 0)
				randomPC = generateRandomPC(playersNumber);
			int randomPlayer = generateRandomUser(playersNumber);
			if (randomPC == randomPlayer) {
				askIt(falseAttempts);
				umap[iterations] = falseAttempts;
				iterations++;
				guessed = true;
			}
			else {
				falseAttempts++;
			}
		}
	}
	return umap;
}

unordered_map<int, int> strategy4(int MAX, int playersNumber) {
	int helper = 0;
	unordered_map<int, int> umap;
	int iterations = 0;
	while (iterations < MAX) {
		bool guessed = false;
		int falseAttempts = 0;
		int randomPC = generateRandomPC(playersNumber);
		while (!guessed) {
			int randomPlayer = generateRandomUser(playersNumber);
			if (randomPC == randomPlayer) {
				askIt(falseAttempts);
				umap[iterations] = falseAttempts;
				iterations++;
				guessed = true;
			}
			else {
				falseAttempts++;
				randomPC = randomPlayer;
			}
		}
	}
	return umap;
}
//proba
int main() {
	while (1) {
		int MAX;
		const int playersNumber = 24;
		int k;
		unordered_map<int, int> umap;
		cout << "Enter number of tries: ";
		cin >> MAX;
		cout << "Enter your strategy [1 2 3 4]: ";
		cin >> k;
		if (k == 1)
			umap = strategy1(MAX, playersNumber);
		else if (k == 2)
			umap = strategy2(MAX, playersNumber);
		else if (k == 3)
			umap = strategy3(MAX, playersNumber);
		else if (k == 4)
			umap = strategy4(MAX, playersNumber);

		cout << "Number of guesses that are over 24: " << counter << endl;

		double sum = 0;
		for (auto& it : umap) {
			sum += it.second;
		}
		cout << "Number of false attempts for " << MAX << " measures is: " << sum / MAX << " for strategy " << k;
		cout << endl;
		umap.clear();
	}
}
#include <iostream>
#include <cstdlib>
#include <vector>
#include <algorithm>
#include <random>
#include "../include/puzzle.h"

template <class numType>
void generatePuzzle(puzzle_t<numType> & puzz, uint64_t seed) {
	numType nullVal = puzz.getNullVal();
	size_t size = puzz.getSize();

	std::vector<numType> allNums(size);
	for (numType i = 0; i < size; i++) {
		allNums[i] = i+1;
	}
	std::vector<numType> shuff(size);

	int x = 0;
	int y = 0;
	while (y < size) {
		bool isSet = false;
		shuff = allNums;
		std::shuffle(shuff.begin(), shuff.end(), std::default_random_engine(seed + x + y * size));

		auto startLoc = shuff.begin();
		if (puzz.getValueAt(x, y) != nullVal) startLoc = std::find(shuff.begin(), shuff.end(), puzz.getValueAt(x, y)) + 1;
		for (; startLoc != shuff.end(); startLoc++) {
			if (puzz.isValid(x, y, *startLoc)) {
				puzz.setValueAt(x, y, *startLoc);
				isSet = true;
				break;
			}
		}
		if (isSet) {
			if (++x >= size) {
				++y;
				x = 0;
			}
		} else {
			puzz.setValueAt(x, y, nullVal);
			if (x == 0) {
				y--;
				x = size-1;
			} else {
				x--;
			}
		}
	}
}

int main(int argc, char** argv) {
	int32_t nullVal = 0;
	size_t seed = 100;
	size_t size = 9;

	for (int i = 0; i < 10; i++) {
		puzzle_t<int32_t> puzz(size, nullVal);
		generatePuzzle(puzz, i);
		puzz.print(std::cout);
		std::cout << "\n##\n\n";
	}

	return 0;
}

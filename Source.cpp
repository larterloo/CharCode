// Written by Kaath Kilo @Kaath_Kilo

#include <iostream>
#include <string>
#include <ctype.h>
#include <fstream>

std::string code;		// the path to the code to compile

int numLength;			// how many different integers to work with

std::string path = "code.txt";		// the path to read code from


int opNum(int i, bool returnLength = 0) {
	// how long the argument is
	int opLen = 0;

	// go through the code until it's no longer a number to get how long the number is
	for (int k = i; isdigit(code[k + 1]); k++) {
		opLen++;
	}

	// store the argument
	int op = stoi( code.substr(i + 1, opLen) );

	// if the index is out of the possible range, then bad things happen
	if (op < 0 || op >= numLength) {
		std::cout << "Tried to read index out of range";
	}

	// determine whether to return the length of the argument or the argument itself
	if (returnLength) {
		return opLen;
	}
	else {
		return op;
	}
	
}


int main(int argc, char* argv[]) {

	switch (argc) {
		case 1:		// no arguments, default path
			break;

		case 2:		// 1 argument, set the path
			path = argv[1];
			break;

		default:	// 2 or more, wrong usage
			std::cout << "Usage: [code path]";
			return 1;
	}
	
	int numLookStart = 0,		// the starting address the compiler will read
	
		numLookEnd = 0,			// how far the current number/operand is
		
		whichNum = 0;			// which integer index the code is currently talking about

	int* num;				// the array of integers for the code to work on

	std::ifstream read;		// the read stream to get the code


	// get the code from the text file
	read.open(path);
	read >> code;
	read.close();


	// if the code doesn't start with a number, then it's wrong, so end
	if (!isdigit(code[0])) {
		std::cout << "Must start with how many numbers you're working with";
		return 1;
	}

	// get how long the first number is, terminated with /
	for (int i = 0; code[i] != '/'; i++) 
		numLookEnd = i + 1;
	
	// get how many different integers to work with
	numLength = stoi( code.substr(numLookStart, numLookEnd) );

	// assign an array the size just determined to the integer array
	num = new int[numLength];

	// default initialisation of array
	for (int i = 0; i < numLength; i++)
		num[i] = 0;


	// if any initialisation is specified, populate. Otherwise, ignore
	if (isdigit(code[numLookEnd + 2])) {

		// enter all the integers from the code into the array
		for (int i = 0; i < numLength; i++) {

			// where the index starts is incremented by the length of the previous item
			numLookStart += numLookEnd + 1;

			// get how long the number is
			for (int k = 0; code[k + numLookStart] != '/'; k++) {
				numLookEnd = k + 1;
			}

			// if the character after the / is not a number, then we're finished with populating the array
			if (!isdigit(code[numLookEnd + 2]))
				break;

			// assign the number into the array
			num[i] = stoi(code.substr(numLookStart, numLookEnd));
		}
	}


	// go through every operand in the code, starting after the number assignments
	for (int i = numLookStart + numLookEnd + 1; i < code.size(); i++) {

		switch (code[i]) {

			case '+':	// increment/add

				// if the next symbol in the code is a number, it must be an index value, otherwise assume it's the current index
				if (isdigit(code[i + 1])) {
					num[whichNum] += num[opNum(i)];		// add the current index with the referenced index
					i += opNum(i, true);				// have the interpreter go to the next operand
				}
				else {
					num[whichNum]++;		// increment the current index
				}
				
				
				break;


			case '-':	// decrement/subtract

				// if the next symbol in the code is a number, it must be an index value, otherwise assume it's the current index
				if (isdigit(code[i + 1])) {
					num[whichNum] -= num[opNum(i)];		// subtract the referenced index from the current index
					i += opNum(i, true);				// have the interpreter go to the next operand
				}
				else {
					num[whichNum]--;		// decrement the current index
				}


				break;


			case '<':	// move index to the left

				// if we're at the first index, then we can't jump left
				if (whichNum <= 0) {
					std::cout << "Tried to move into negative index";
					return 0;
				}

				// decrement the index
				whichNum--;
				break;


			case '>':	// move index to the right

				// if we're at the last index, then we can't jump right
				if (whichNum >= numLength - 1) {
					std::cout << "Tried to move into index beyond allocated memory";
					return 0;
				}

				// increment the index
				whichNum++;
				break;


			case '|':	// jump to index

				// if the argument is invalid, terminate
				if (opNum(i) < 0 || opNum(i) > numLength) {
					std::cout << "Tried to move into index beyond allocated memory";
						return 0;
				}
				else {
					whichNum = opNum(i);		// change the index to the one specified in the argument
					i += opNum(i, true);		// have the interpreter go to the next operand
				}
				

				break;


			case '=':	// input

				std::cout << "Input to " << whichNum << ": ";	// prompt for input
				std::cin >> num[whichNum];						// put the input into the current address

				break;


			case '?':	// output

				std::cout << "Value of " << whichNum << ": " << num[whichNum] << "\n";

				break;



			default:		// if the operand is invalid, then terminate
				std::cout << "Unknown operand: " << code[i];	
				return 1;
		}

	}


	return 0;
}
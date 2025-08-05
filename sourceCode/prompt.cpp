#include "passGen.h"
#include <iostream>

char useNum() {
	std::cout << "Would you like the password to contain numbers? (y for Yes, n for No) ";

	char num{};
	std::cin >> num;
	return num;
}

char useChar() {
	std::cout << "Would you like the password to contain special characters? (y for Yes, n for No) ";
	
	char spec{};
	std::cin >> spec;
	return spec;	
}

char useCase() {
	std::cout << "Would you like the password to contain both Upper and Lower case? (y for Yes, n for No) ";

	char Case{};
	std::cin >> Case;
	return Case;
}

int len() {
	std::cout << "Enter length of Password: ";

	int len{};
	std::cin >> len;
	return len;
}


#include "passGen.h"
#include <cctype>
#include <string>

std::string lowercase(std::string input) {
	std::string output{};

	for (int i{}; i < input.size(); i++) {
		output = output + (char)tolower(input[i]);
	}

	return output;
}

std::string encrypt(std::string input) {
	std::string enc{};
	
	for (int i{}; i < input.size(); i++) {
		enc = enc + (char)((int)input[i]-20);
	}

	return enc;
}

std::string decrypt(std::string input) {
	std::string dec{};

	for (int i{}; i < input.size(); i++) {
		dec = dec + (char)((int)input[i]+20);
	}

	return dec;
}

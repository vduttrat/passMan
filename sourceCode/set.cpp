#include "passGen.h"
#include <cstdlib>
#include <ctime>
#include <string>

std::string genSet() {
	char Num{useNum()};
	char Char{useChar()};
	char Case{useCase()};

	std::string set{};
	
	if (Num=='y') {
		set.push_back('0');	
	}

	if (Char=='y') {
		set.push_back('1');	
	}	

	if (Case=='y') {
		set.push_back('2');	
	}

	set.push_back('3');
	
	return set;
}

char genChar(char digType) {

			char passchar{};

			if (digType == '0') {
				passchar = (char) ((rand()%10)+48);
			}
			if (digType == '1') {
				passchar = (char) ((rand()%15)+33);
			}
			if (digType == '2') {
				passchar = (char) ((rand()%26)+65);
			}
			if (digType == '3') {
				passchar = (char) ((rand()%26)+97);
			}

			return passchar;
}

std::string genCode() {

	std::string set{genSet()};
	srand(time(NULL));

	int passlen {len()};

	std::string password {};

	std::string temp {set};
	while (passlen--){
		

		if ((int) temp.size() != 0) {

			char digType{temp[(rand()%(temp.size()))]};
			char passchar {genChar(digType)};
			temp.erase(temp.find(digType,0),1);
			password.push_back(passchar);
			}

		else {

			char digType{set[(rand()%(set.size()))]};
			char passchar {genChar(digType)};
			password.push_back(passchar);
			}
	}
	return password;
	
}

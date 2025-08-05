#include "passGen.h"
#include <cstdio>
#include <string>
#include <fstream>
#include <iostream>
#include <cctype>

int main() {
	std::cout << "----- Password Manager -----\n\n";
	while (1) {
		std::cout << "Would you like to:\n\nAdd Password Manually (Enter 'add')\nGenerate password (Enter 'gen')\n"<<
			"List available Passwords (Enter 'list')\nView a Password (Enter 'view')\n"<< 
			"Edit Password (Enter 'edit')\nDelete Password (Enter 'del')\nExit Program (Enter 'exit')\n";

		std::string inp_choice{}, choice{};
		std::cin >> inp_choice;
		choice = lowercase(inp_choice);
		
		std::cin.ignore();
		std::cout << '\n';

		if (choice=="add") {
			
			std::string name{};
			std::cout << "Enter name for Password: ";
			std::getline(std::cin, name);

			std::string password{};
			std::cout << "Enter password: ";
			std::getline(std::cin,password);

			std::string enc{encrypt(password)};

			std::ofstream outfile("Password.txt", std::ios_base::app);
			outfile << name << ":::" << enc << '\n';
			std::cout << "Password successfully added!\nPress Enter to continue.\n\n";
			std::cin.get();
		}
		
		else if (choice == "gen") {

			std::string name{};
			std::cout << "Enter name for Password: ";
			std::getline(std::cin,name);

			std::string password {genCode()};
			
			std::ofstream outFile("Password.txt", std::ios_base::app);


			std::string enc{encrypt(password)};

			outFile << name << ":::" << enc << '\n' ;
			std::cout << "Password successfully generated!\nPress Enter to continue.\n\n";
			std::cin.ignore(); 				//cin was used in genCode() function for taking prompts
			std::cin.get();
		}
		
		else if (choice == "list") {
			
			std::ifstream passfile("Password.txt");
			std::string name{};

			
			std::cout << "Available passwords: \n";

			for (std::string line{}; std::getline(passfile, line); ) {
				
				std::string::size_type pos{line.find(":::", 0)};
				name = line.substr(0,pos);

				std::cout << name << '\n';
			}
			std::cout << "\nPress Enter to continue.\n";
			std::cin.get();
		}

		else if (choice == "view") {
				
				std::ifstream passfile("Password.txt");

				std::string temp{};
				std::cout << '\n' << "Which password would you like to view?: ";
				std::getline(std::cin, temp);

				std::string passname{lowercase(temp)};
				std::string name{}, code{};

				int counter{};

				for (std::string line{}; std::getline(passfile, line); ) {
					
					std::string::size_type pos{line.find(":::", 0)};
					code = line.substr(pos+3);
					name = line.substr(0,pos);

					temp = lowercase(name);

					if (passname==temp) {
						counter ++;
						std::string dec{decrypt(code)};
						std::cout << "Required password is: " << dec << '\n';	
						break;
				}
			}

				if (counter == 0) {std::cout << "Password not found.\n";}
				std::cout << "Press Enter to continue.\n";
				std::cin.get();
	}
		else if (choice == "edit") {

			std::ifstream passfile("Password.txt");
			std::string temp{};
			
			std::cout << "Which password would you like to edit (Enter password name): ";
			std::getline(std::cin, temp);

			std::string passname{lowercase(temp)};

			int counter {};
			std::string name{}, code{};

			std::ofstream tempfile("temp.txt");
			
			for (std::string line{}; std::getline(passfile, line); ) {

				std::string enc{};
				std::string::size_type pos{line.find(":::", 0)};
				name = line.substr(0,pos);

				temp = lowercase(name);

				if (temp == passname) {
					
					std::cout << "Would you like to enter the new password manually or assign a randomly generated password?\n"<<
						"(Enter 'add' to add new password manually and Enter 'gen' to assign randomly generated password.\n";
					std::cin >> inp_choice;
					std::cin.ignore();
					
					choice = lowercase(inp_choice);

					if (choice == "add") {
						std::cout << "Enter new password: ";
						std::getline(std::cin,code);
					}

					else if (choice == "gen") {
						code = genCode();
						std::cin.ignore();
					}

				counter++;

				enc = encrypt(code);

				}

				else {
					enc = line.substr(pos+3);
				}


			tempfile << name << ":::" << enc << '\n';
		}
			if (counter != 0) {std::cout << "Password changed.\n";}

			else if (counter == 0) {std::cout << "Password not found.\n";}

			
			passfile.close();
			tempfile.close();
				
			std::remove("Password.txt");
			std::rename("temp.txt","Password.txt");

			std::cout << "Press Enter to continue.\n";
			std::cin.get();
		
		
		}

		else if (choice == "del") {
			
			std::ifstream passfile("Password.txt");
			std::ofstream tempfile("temp.txt");

			int counter{};
			std::string temp{}, name{}, code{};
			
			std::cout << "Enter name of Password to delete: ";
			std::getline(std::cin, temp);

			std::string delname {lowercase(temp)};

			for (std::string line{}; std::getline(passfile, line); ) {
	
				std::string::size_type pos{line.find(":::", 0)};
				code = line.substr(pos+3);
				name = line.substr(0,pos);

				temp = lowercase(name);

				if (temp!=delname) {
					tempfile << name << ":::" << code << '\n';
				}

				else {counter++;}
			}
			
			passfile.close();
			tempfile.close();
				
			std::remove("Password.txt");
			std::rename("temp.txt","Password.txt");
			
			if (counter != 0) {
			std::cout << "Code deleted.\nPress Enter to continue.\n";}

			else if (counter == 0) {"Code not found.\n";}
			std::cin.get();
		}
		else if (choice == "exit") {
			break;
		}

		else {
			std::cout << "Please enter a valid choice.\n\n";
		}
	}
    	return 0;
}

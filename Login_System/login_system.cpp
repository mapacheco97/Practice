#include<iostream>
#include<fstream>
#include<string>
#include<Windows.h>


using namespace std;

bool isLoggedIn() {
	
	string username, password, un, pw;

	cout << "Enter username: "; cin >> username;
	cout << "Enter password: "; cin >> password;

	ifstream read("C:\\Users\\Miguel Pacheco\\OneDrive\\Desktop\\C++_Practice\\Login_System\\" + username + ".txt");
	getline(read, un);
	getline(read, pw);

	if (un == username && pw == password) {
		return true;
	}
	else {
		return false;
	}
}

int main() {
	int choice;

	cout << "1: Register\n2: Login\n3: Exit\nYour choice: "; cin >> choice;
	system("cls");

	if (choice == 1) {
		string username, password;

		cout << "Select a username  (No Spaces): "; cin >> username;
		cout << "Select a password: "; cin >> password;

		ofstream file;
		file.open("C:\\Users\\Miguel Pacheco\\OneDrive\\Desktop\\C++_Practice\\Login_System\\" + username + ".txt");
		file << username << endl << password;
		file.close();
		system("cls");

		main();
	}
	else if (choice == 2) {
		bool status = isLoggedIn();

		if (!status) {
			cout << "False Login!" << endl;
			Sleep(1000);
			system("cls");
			main();
		}
		else {
			system("cls");
			cout << "Successfully logged in!\nExitting Program. Goodbye!" << endl;
			Sleep(2000);
			exit(0);
		}
	}
	else if (choice == 3) {
		system("cls");
		cout << "Exiting Program\nGood Bye";
		Sleep(2000);
		exit(0);
	}
	return 0;
}

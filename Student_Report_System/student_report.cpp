#include<iostream>
#include<iomanip>
#include<fstream>
#include<Windows.h>
#include<string>

using namespace std;

class student {
private:
	int rollNo;
	char name[50];
	int eng_grade, math_grade, sci_grade, hist_grade, cs_grade;
	double average;
	char grade;

public:
	void getData();
	void showData() const;
	void calculate();
	int readRollNo();
};

void student::getData() {
	average = static_cast<double>(eng_grade + math_grade + sci_grade + hist_grade + cs_grade) / 5.0;
	cout << "Enter student's roll number: ";
	cin >> rollNo;
	cout << "\nEnter Student's Name: ";
	cin.ignore();
	cin.getline(name, 50);
	cout << "\nAll grades should be out of 100";
	cout << "\nEnter English grade: ";
	cin >> eng_grade;
	cout << "\nEnter Math grade: ";
	cin >> math_grade;
	cout << "\nEnter Science grade: ";
	cin >> sci_grade;
	cout << "\nEnter History grade: ";
	cin >> hist_grade;
	cout << "\nEnter Computer Science grade: ";
	cin >> cs_grade;
	calculate();
}

void student::calculate() {
	average = static_cast<double>(eng_grade + math_grade + sci_grade + hist_grade + cs_grade) / 5.0;
	if (average >= 90)
		grade = 'A';
	else if (average >= 80 && average < 90)
		grade = 'B';
	else if (average >= 70 && average < 80)
		grade = 'C';
	else if (average >= 60 && average < 70)
		grade = 'D';
	else
		grade = 'F';
}

void student::showData() const {
	cout << "\nRoll number of student: " << rollNo;
	cout << "\nName of Student: " << name;
	cout << "\nEnglish: " << eng_grade;
	cout << "\nMath: " << math_grade;
	cout << "\nScience: " << sci_grade;
	cout << "\nHistory: " << hist_grade;
	cout << "\nComputer Science: " << cs_grade;
	cout << "\nAverage Grade: " << average;
	cout << "\nStudent's Overall Grade: " << grade;
}

int student::readRollNo() {
	return rollNo;
}

//functions
void create_student();		
void display_student(int);		//display record
void display_all();			//display all records
void delete_student(int);	//delete record
void change_student(int);	//edit record

void create_student() {
	student stud;
	ofstream file;
	file.open("student.dat", ios::binary|ios::app);
	stud.getData();
	file.write(reinterpret_cast<char*> (&stud), sizeof(student));
	file.close();
	cout << "\nStudent has been created";
	cin.ignore();
	cin.get();
}

//read specific record based on roll number
void display_student(int n) {
	student stud;
	ifstream file;
	file.open("student.dat", ios::binary);
	if (!file) {
		cout << "\nFile could not be opened! Press any key to exit";
		cin.ignore();
		cin.get();
		return;
	}

	bool isHere = false;

	while (file.read(reinterpret_cast<char*> (&stud), sizeof(student))) {
		if (stud.readRollNo() == n) {
			stud.showData();
			isHere = true;
		}
	}

	file.close();

	if (isHere == false) {
		cout << "\n\nNo Record of Student";
		cin.ignore();
		cin.get();
	}
}

void display_all() {
	student stud;
	ifstream file;
	file.open("student.dat", ios::binary);
	if (!file) {
		cout << "\nFile could not be opened! Press any key to quit";
		cin.ignore();
		cin.get();
		return;
	}

	cout << "\n\n\t\tDISPLAYING ALL RECORDS\n\n";
	while (file.read(reinterpret_cast<char*> (&stud), sizeof(student))) {
		stud.showData();
		cout << "\n\n==========================================================\n";
	}

	file.close();
	cin.ignore();
	cin.get();
}

void delete_student(int n) {
	student stud;
	ifstream file;
	file.open("student.dat", ios::binary);
	if (!file) {
		cout << "\nFile could not be opened! Press any key to quit!";
		cin.ignore();
		cin.get();
		return;
	}
	
	cout << "\n\nAre you sure you want to delete student profile? ";
	string response = "";
	cin >> response;

	if (response == "Yes" || response == "yes" || response == "YES") {
		ofstream oFile;
		oFile.open("Temp.dat", ios::out);
		//from the beginning of the stream's buffer
		file.seekg(0, ios::beg);
		//reading the student file, and writing all records, except for deleting student
		while (file.read(reinterpret_cast<char*> (&stud), sizeof(student))) {
			if (stud.readRollNo() != n) {
				//writing to the temp file
				oFile.write(reinterpret_cast<char*> (&stud), sizeof(student));
			}
		}

		oFile.close();
		file.close();
		remove("student.dat");
		rename("Temp.dat", "student.dat");
		cout << "\n\n\tRecord Deleted";
		cin.ignore();
		cin.get();
	}

	else if(response == "NO" || response == "no" || response == "No") {
		cout << "\n\nRecord was not deleted";
		file.close();
		cin.ignore();
		cin.get();
	}

	else {
		cout << "\nNot a valid response";
		cout << "\nGoing Back to Main Menu...";
		file.close();
		cin.ignore();
		cin.get();
	}
}

void change_student(int n) {
	bool found = false;
	student stud;
	fstream file;
	file.open("student.dat", ios::binary | ios::in | ios::out);
	if (!file) {
		cout << "\nFile could not be opened! Press and Key to exit";
		cin.ignore();
		cin.get();
		return;
	}

	while (!file.eof() && found == false) {
		file.read(reinterpret_cast<char*> (&stud), sizeof(student));
		if (stud.readRollNo() == n) {
			stud.showData();
			cout << "\nEnter new student details: " << endl;
			stud.getData();
			//turns the unsigned result of sizeof operator into a signed number, * by -1
			int pos = (-1) * static_cast<int>(sizeof(stud));
			//seekp used to set postion of pointer int he output sequence to specified position
			//ios::cur is used to indicate that we are moving pointer from current position 
			file.seekp(pos, ios::cur);
			file.write(reinterpret_cast<char*> (&stud), sizeof(student));
			cout << "\n\n\t Record Updated";
			found = true;
		}
	}

	file.close();
	if (found == false)
		cout << "\n\nRecord Not Found";
	cin.ignore();
	cin.get();
}

int main() {
	int input, num;
	system("cls");
	while (1) {
		cout << "\n\n\n\tMENU";
		cout << "\n\n\t1. Create student record";
		cout << "\n\n\t2. Search student record";
		cout << "\n\n\t3. Display all students";
		cout << "\n\n\t4. Delete student record";
		cout << "\n\n\t5. Modify student record";
		cout << "\n\n\t6. Exit";
		cout << "\n\nEnter Choice: ";
		cin >> input;

		system("cls");
		switch (input) {
		case 1:
			create_student();
			break;

		case 2:
			cout << "\nEnter student roll number: ";
			cin >> num;
			display_student(num);
			break;

		case 3:
			display_all();
			break;

		case 4:
			cout << "\n\n\tEnter roll number: ";
			cin >> num;
			delete_student(num);
			break;

		case 5:
			cout << "\n\n\tEnter roll number: ";
			cin >> num;
			change_student(num);
			break;

		case 6:
			cout << "Exiting!";
			exit(0);
		default:
			cout << "Wrong input, try again!" << input << " was selected!";
			Sleep(1000);
		}
	}
	return 0;
}
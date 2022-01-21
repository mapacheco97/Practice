#include<string.h>
#include<iostream>
#include<stdio.h>

using namespace std;

class Book {
private:
	char *author, *title, *publisher;
	float *price;
	int *stock;
public:
	Book() {
		author = new char[40];
		title = new char[40];
		publisher = new char[40];
		price = new float;
		stock = new int;
	}
	void feedData();
	void editData();
	void showData();
	int search(char[], char[]);
	void buyBook();

};

void Book::feedData() {
	//cin.ignore used to ignore one or more characters
	cin.ignore();
	cout << "\nEnter Author Name: "; cin.getline(author, 40);
	cout << "\nEnter Title: ";	cin.getline(title, 40);
	cout << "\nEnter Publisher Name: "; cin.getline(publisher, 40);
	cout << "\nEnter Price: ";	cin >> *price;
	cout << "\nEnter Stock Postition: "; cin >> *stock;
}

void Book::editData() {
	cout << "\nEnter Author Name: "; cin.getline(author, 40);
	cout << "\nEnter Title: "; cin.getline(title, 40);
	cout << "\nEnter Publisher Name: "; cin.getline(publisher, 40);
	cout << "\nEnter Price: "; cin >> *price;
	cout << "\nEnter Stock Position: "; cin >> *stock;
}

void Book::showData() {
	cout << "\nAuthor Name: " << author;
	cout << "\nTitle: " << title;
	cout << "\nPublisher: " << publisher;
	cout << "\nPrice: " << *price;
	cout << "\nStock Position: " << *stock;
}

int Book::search(char title_buy[40], char author_buy[40]) {
	//strcmp compares the string arguments, comparing both the strings character by character
	if (strcmp(title_buy, title) == 0 && strcmp(author_buy, author) == 0) {
		return 1;
	}
	else
		return 0;
}

void Book::buyBook() {
	int count;
	cout << "\nEnter # of Books being purchased: ";
	cin >> count;

	if (count <= *stock) {
		*stock = *stock - count;
		cout << "\nBooks Bought Successfully!" << endl;
		cout << "Amount: " << (*price)*(count);
	}
	else {
		cout << "\nRequired copies not in stock";
	}
}

int main() {
	Book *b[40];
	int i=0, r, t, choice;
	char buy_title[40], buy_author[40], search_t[40], search_a[40];

	while (1) {
		cout << "\n\n\t\tMENU"
			<< "\n1. Enter New Book"
			<< "\n2. Buy Book(s)"
			<< "\n3. Search for Book"
			<< "\n4. Edit Book Details"
			<< "\n5. Exit"
			<< "\n\nEnter Choice: ";
		cin >> choice;

		switch (choice) {
		case 1:
			b[i] = new Book;
			b[i]->feedData();
			i++;
			break;

		case 2:
			cin.ignore();
			cout << "\nEnter Title of Book : "; cin.getline(buy_title, 40);
			cout << "\nEnter Author: "; cin.getline(buy_author, 40);
			for (t = 0; t < i; t++) {
				if (b[t]->search(buy_title, buy_author)) {
					b[t]->buyBook();
					break;
				}
			}
			if (t == 1)
				cout << "\nThis Book is NOT in Stock!";
			break;

		case 3:
			cin.ignore();
			cout << "\nEnter Book Title: "; cin.getline(search_t, 40);
			cout << "\nEnter Author: "; cin.getline(search_a, 40);

			for (t = 0; t < i; t++) {
				if (b[t]->search(search_t, search_a)) {
					cout << "Book Found Successfully!";
					b[t]->showData();
					break;
				}
			}
			if(t==i)
				cout << "This Book is not in stock!";
			break;

		case 4: 
			cin.ignore();
			cout << "\nEnter Book Title: "; cin.getline(search_t, 40);
			cout << "\nEnter Author: "; cin.getline(search_a, 40);

			for (t = 0; t < i; t++) {
				if (b[t]->search(search_t, search_a)) {
					cout << "\nBook Found Successfully!";
					b[t]->editData();
					break;
				}
			}
			if (t == i) {
				cout << "\nThis Book is not in Stock!";
			}
			break;

		case 5:
			exit(0);

		default:
			cout << "\nInvalid Choice! Try Again!";
		}
	}

	return 0;

}
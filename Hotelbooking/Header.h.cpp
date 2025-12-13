#include <iostream>
#include <vector>
#include "Header.h"
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;


int Roomrand() {
	int roomamount = rand() % 41 + 30;
	return roomamount;
}

int room::getroomprice() {

	int price = rand() % 21 + 80;
	return price;
}

int getbookingnum() {
	int bookingnum = rand() % 90000 + 10000;
	return bookingnum;
}

bool availability(vector<room> Rooms, int Room) {

	if (Rooms[Room].bookingnum > 0) {
		return false;
	}
	else {
		return true;
	}
}

int available_rooms_count(vector<room> Rooms, int amount) {

	int Count = 0;

	for (int i = 0; i < amount; ++i) {

		bool separator = availability(Rooms, i);

		if (separator == true) {
			Count++;
		}
	}
	return Count;
}


vector<room> createrooms(int amount) {

	vector<room> rooms;
	int Amount = amount;

	for (int i = 0; i < Amount; ++i) {
		rooms.push_back(room(i + 1));
	}
	return rooms;
}

void savefile(vector<room> Rooms, int amount) {

	ofstream file("Savefile.txt");

	if (file.is_open()) {
		
		file << amount << "\n";

		for (int i = 0; i < amount; ++i) {
			file << Rooms[i].roomnum << "\n";
			file << Rooms[i].guestname << "\n";
			file << Rooms[i].bookingnum << "\n";
			file << Rooms[i].price << "\n";
			file << Rooms[i].duration << "\n";
		}
		file.close();
	}
	else {
		cerr << "Error! Savefile was not opened succesfully!";
	}
}

void loadfile(vector<room> &Rooms, int &amount) {

	ifstream infile("Savefile.txt");

	if (infile.is_open()) {

		Rooms.clear();
		string line;
		(getline(infile, line));
		amount = stoi(line);
		Rooms = createrooms(amount);

		for (int i = 0; i < amount; ++i) {

			(getline(infile, line));
			int conversion = stoi(line);
			Rooms[i].roomnum = conversion;

			(getline(infile, line));
			Rooms[i].guestname = line;

			(getline(infile, line));
			conversion = stoi(line);
			Rooms[i].bookingnum = conversion;

			(getline(infile, line));
			conversion = stoi(line);
			Rooms[i].price = conversion;

			(getline(infile, line));
			conversion = stoi(line);
			Rooms[i].duration = conversion;
		}
		infile.close();
	}
	else {
		cerr << "Error! Savefile was not opened succesfully!";
	}
}


void check_available_rooms(vector<room> Rooms, int amount) {

	string input;

	do {
		cout << "**************************************\n";
		cout << "           AVAILABLE ROOMS           \n\n";

		for (int i = 0; i < amount; ++i) {

			bool available = availability(Rooms, i);
			if (available == true) {

				cout << "*Roomnro: " << Rooms[i].roomnum <<
					" _ Price for one night: " << Rooms[i].price << "$\n";

				this_thread::sleep_for(chrono::milliseconds(30));
			}
		}
		cout << "\n**************************************\n\n";

		system("pause");
		break;

	} while (true);

	system("cls");
	cout << "Quitting to main menu..\n\n";
	this_thread::sleep_for(chrono::milliseconds(500));
}


void room_booking(vector<room>& Rooms, int amount) {

	char input = '\0';
	const int Max_Len = 30;

	do {

		int roomnum;
		int price;
		int nights;
		int total;
		string name;
		int bookingnumber = getbookingnum();
		int available_rooms = available_rooms_count(Rooms, amount);

		if (available_rooms < 1) {
			system("cls");
			cout << "Every room is booked! Try again another time.\n\n";
			break;
			this_thread::sleep_for(chrono::milliseconds(500));
		}

		do {

			cout << "**************************************\n";
			cout << "                BOOKING                \n\n";

			cout << "Welcome to our hotel.\n\n" << "We have " << amount <<
				" rooms in total.\n" << available_rooms << " of them are free at the moment.\n\n" <<
				"Please pick a room you'd like to stay in: ";

			cin >> roomnum;

			if (cin.fail() || roomnum > amount || roomnum < 1) {

				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
				cout << "Invalid input! Use an integer between 1 - " << amount << " !\n\n";
				continue;
			}

			bool available = availability(Rooms, roomnum - 1);

			if (available == false) {
				system("cls");
				cout << "This room is already booked, try another room.\n\n";
			}
			else {
				break;
			}

		} while (1);

		price = Rooms[roomnum - 1].price;

		cout << "\nYou are staying in room: " << roomnum << "\n" <<
			"Price for one night is: " << price << "$\n\n" <<
			"How many nights would you like to stay?: ";

		cin >> nights;

		if (cin.fail() || nights > 100 || roomnum < 1) {

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");
			cout << "Invalid input! Use an integer between 1 - 99 !\n\n";
			continue;
		}

		total = price * nights;

		cout << "\nYour name for the booking: ";

		cin.ignore();
		getline(cin, name);

		if (name.empty()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");
			cout << "You can't leave the name section blank !\n\n";
			continue;
		}
		else if (name.length() > Max_Len) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");
			cout << "Name is too long !\n\n";
			continue;
		}

		system("cls");

		cout << "**************************************\n";
		cout << "           AVAILABLE ROOMS           \n\n";

		cout << "Is the information below correct?\n\n";
		cout << "Name: " << name << "\n";
		cout << "Roomnumber: " << roomnum << "\n";
		cout << "Duration of stay: " << nights << "\n";
		cout << "Total price " << total << "$" << "\n";
		cout << "Booking number: " << bookingnumber << "\n";
		cout << "(y/n): ";

		cin >> input;

		if (input == 'y' || input == 'Y') {

			Rooms[roomnum - 1].guestname = name;
			Rooms[roomnum - 1].bookingnum = bookingnumber;
			Rooms[roomnum - 1].price = total;
			Rooms[roomnum - 1].duration = nights;

			cout << "\nThank you for your booking.\n\n" <<
				"Would you like to make another booking?\n" <<
				"(y/n)";
			cin >> input;

			if (input == 'y' || input == 'Y') {
				system("cls");
			}
			else if (input == 'n' || input == 'N') {
				system("cls");
				cout << "Quitting to main menu..\n\n";
				this_thread::sleep_for(chrono::milliseconds(500));
			}
			else {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
				cout << "Faulty input! use Y,y or N,n.\n\n";
			}
		}
		else if (input == 'n' || input == 'N') {
			system("cls");
			cout << "Quitting to main menu..\n\n";
			this_thread::sleep_for(chrono::milliseconds(500));
		}
		else {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");
			cout << "Faulty input! use Y,y or N,n.\n\n";
		}
	} while (input != 'n' && input != 'N');
}
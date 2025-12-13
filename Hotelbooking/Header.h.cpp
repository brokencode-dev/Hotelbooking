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

int getroomprice() {

	int price = rand() % 21 + 80;
	return price;
}

int getbookingnum() {
	int bookingnum = rand() % 90000 + 10000;
	return bookingnum;
}

void reset_prices(vector<room>& Rooms, int amount) {

	for (int i = 0; i < amount; ++i) {
		Rooms[i].price = getroomprice();
	}
}

bool availability(vector<room> Rooms, int Room) {

	if (Rooms[Room].bookingnum > 0) {
		return false;
	}
	else {
		return true;
	}
}


void show_room_info(vector<room> Rooms, int amount) {

	cout << "Roomnumber: " << Rooms[amount].roomnum << "\n";
	cout << "Booked by: " << Rooms[amount].guestname << "\n";
	cout << "Bookingnumber: " << Rooms[amount].bookingnum << "\n";
	cout << "current price: " << Rooms[amount].price << "$ for one night\n";
	cout << "Total price: " << Rooms[amount].bookingprice << "$\n";
	cout << "Booked for: " << Rooms[amount].duration << " nights\n";
}

void delete_booking(vector<room>& Rooms, int amount) {
	Rooms[amount].guestname.clear();
	Rooms[amount].price = getroomprice();
	Rooms[amount].bookingprice = 0;
	Rooms[amount].bookingnum = 0;
	Rooms[amount].duration = 0;
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
			file << Rooms[i].bookingprice << "\n";
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
			Rooms[i].bookingprice = conversion;

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

void check_booked_rooms(vector<room> Rooms, int amount) {
	cout << "**************************************\n";
	cout << "             BOOKED ROOMS           \n\n";

	for (int i = 0; i < amount; ++i) {

		bool available = availability(Rooms, i);
		if (available == false) {

			cout << "*Roomnro: " << Rooms[i].roomnum <<
				" _ Price for one night: " << Rooms[i].price << "$\n";

			this_thread::sleep_for(chrono::milliseconds(30));
		}
	}
	cout << "\n**************************************\n\n";
}


void search_by_number(vector<room>& Rooms, int amount) {

	char input = '\0';

	do {
		char quit;
		int numsearch;
		string search;
		vector<int> searchresult;

		check_booked_rooms(Rooms, amount);

		cout << "\nSearch by number: ";
		cin >> search;

		for (int i = 0; i < amount; ++i) {

			if (to_string(Rooms[i].bookingnum).find(search) != string::npos) {

				searchresult.push_back(i);
			}
		}

		int size = searchresult.size();

		system("cls");
		cout << "The search resulted in: " << size << " matches\n";

		if (size < 1) {
			cout << "Try again\n" << "Press 'n' to exit!";

			cin >> input;

			if (input == 'n' || input == 'N') {
				system("cls");
				cout << "Closing search..\n\n";
				this_thread::sleep_for(chrono::milliseconds(500));
			}

			else {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
			}

		}

		else {

			for (int i = 0; i < size; ++i) {

				int result = searchresult[i];

				cout << "Room number: " << result + 1 << "\n";
			}

			cout << "\nPick one of the results to see reservation info: \n";
			cin >> numsearch;

			if (cin.fail() || numsearch > amount || numsearch < 1) {

				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
				cout << "Invalid input! Use an integer between 1 - " << amount << " !\n\n";
				continue;
			}
			system("cls");
			show_room_info(Rooms, numsearch - 1);

			cout << "\nDo you want to delete the booking?\n";
			cout << "(y/n): ";

			cin >> input;

			if (input == 'y' || input == 'Y') {
				delete_booking(Rooms, numsearch - 1);

				system("cls");
				cout << "\nBooking deleted\n";


				cout << "Would you like to search by name again?\n";
				cout << "(y/n): ";

				if (input == 'y' || input == 'Y') {
					system("cls");
				}
				else if (input == 'n' || input == 'N') {
					system("cls");
					cout << "Quitting to search menu..\n\n";
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
		}
	} while (input != 'n' && input != 'N');
}

void search_by_name(vector<room>& Rooms, int amount) {

	char input = '\0';

	do {
		char quit;
		int numsearch;
		string search;
		vector<int> searchresult;

		check_booked_rooms(Rooms, amount);

		cout << "\nSearch by name: ";

		cin.ignore();
		getline(cin, search);

		for (int i = 0; i < amount; ++i) {

			if (Rooms[i].guestname.find(search) != string::npos) {

				searchresult.push_back(i);
			}
		}

		int size = searchresult.size();

		system("cls");
		cout << "The search resulted in: " << size << " matches\n";

		if (size < 1) {
			cout << "Try again\n" << "Press 'n' to exit!";

			cin >> input;

			if (input == 'n' || input == 'N') {
				system("cls");
				cout << "Closing search..\n\n";
				this_thread::sleep_for(chrono::milliseconds(500));
			}

			else { 
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
			}

		}

		else {

			for (int i = 0; i < size; ++i) {

				int result = searchresult[i];

				cout << "Room number: " << result + 1 << "\n";
			}

			cout << "\nPick one of the results to see reservation info: \n";
			cin >> numsearch;

			if (cin.fail() || numsearch > amount || numsearch < 1) {

				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
				cout << "Invalid input! Use an integer between 1 - " << amount << " !\n\n";
				continue;
			}
			system("cls");
			show_room_info(Rooms, numsearch - 1);

			cout << "\nDo you want to delete the booking?\n";
			cout << "(y/n): ";

			cin >> input;

			if (input == 'y' || input == 'Y') {
				delete_booking(Rooms, numsearch - 1);

				system("cls");
				cout << "\nBooking deleted\n";
				

				cout << "Would you like to search by name again?\n";
				cout << "(y/n): ";

				if (input == 'y' || input == 'Y') {
					system("cls");
				}
				else if (input == 'n' || input == 'N') {
					system("cls");
					cout << "Quitting to search menu..\n\n";
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
		}
	} while (input != 'n' && input != 'N');
}


void booking_search(vector<room>& Rooms, int amount) {

	int input;

	do {

		cout << "**************************************\n";
		cout << "            BOOKING SEARCH            \n\n";
		cout << "1. Search by name\n";
		cout << "2. Search by bookingnumber\n";
		cout << "3. Exit to main menu\n\n";
		cout << "**************************************\n\n";
		cout << "Enter your choice: ";
		cin >> input;

		if (cin.fail()) {

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");
			cout << "Invalid input! Choose an integer from 1 to 3!\n\n";
			this_thread::sleep_for(chrono::milliseconds(500));
		}

		else {

			switch (input) {

			case 1:

				system("cls");
				search_by_name(Rooms, amount);

				break;

			case 2:

				system("cls");
				search_by_number(Rooms, amount);

				break;

			case 3:

				system("cls");
				cout << "Exiting to main menu..\n";
				this_thread::sleep_for(chrono::milliseconds(500));
				break;

			default:

				system("cls");
				cout << "Invalid input! Choose an integer from 1 to 3!\n\n";
			}

		}
	} while (input != 3);
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
			Rooms[roomnum - 1].bookingprice = total;
			Rooms[roomnum - 1].duration = nights;

			reset_prices(Rooms, amount);

			cout << "\nThank you for your booking.\n\n" <<
				"Would you like to make another booking?\n" <<
				"(y/n): ";
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
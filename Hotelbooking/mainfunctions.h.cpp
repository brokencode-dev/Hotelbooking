//Elias Laitala
#include "classfunctions.h"
#include "mainfunctions.h"
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

//this file contains the logic for all the main functions

int Roomrand() {
	int roomamount = rand() % 41 + 30;
	return roomamount;
}
//simple generator returns 30-70


vector<room> createrooms(int amount) {

	vector<room> rooms;
	int Amount = amount;

	for (int i = 0; i < Amount; ++i) {
		rooms.push_back(room(i + 1));
	}
	return rooms;
}
//creates a vector of type room, and configures the default variable values
//the amount is determinend in main.cpp room_numbers


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
//opens/creates a text file called savefile.txt and simply
//writes line by line every rooms information
//the first line is reserved for the amount of rooms, cause we need that info
//in order to load the file


void loadfile(vector<room>& Rooms, int& amount) {

	ifstream infile("Savefile.txt");

	if (infile.is_open()) {

		Rooms.clear();
		string line;
		(getline(infile, line));
		amount = stoi(line);
		Rooms = createrooms(amount);
		//this bit of code clears the vector created in main, gets the first line from savefile.txt,
		//converts string to int and stores it in main.cpp room_numbers and stores that amount of
		//default rooms inside the vector

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
		//converts string to int when required and stores the saved room info to vector
	}
	else {
		cerr << "Error! Savefile was not opened succesfully!";
	}
}


void room_booking(vector<room>& Rooms, int amount) {

	char input = '\0';
	const int Max_Len = 30;
	const int Min_Len = 5;
	//char for user input (Y/N)?
	//int for restricting name length

	do {

		int roomnum;
		int price;
		int nights;
		int total;
		string name;
		//declaring variables used

		int bookingnumber = getbookingnum();
		int available_rooms = available_rooms_count(Rooms, amount);
		//using and storing the values of random bookingnum and
		//counting the amount of available rooms

		if (available_rooms < 1) {
			system("cls");
			cout << "Every room is booked! Try again another time.\n\n";
			break;
			this_thread::sleep_for(chrono::milliseconds(500));
		}
		//bit in case every room is booked, otherwise loop would be impossible to break

		do {

			cout << "**************************************\n";
			cout << "                BOOKING                \n\n";

			cout << "Welcome to our hotel.\n\n" << "We have " << amount <<
				" rooms in total.\n" << available_rooms <<
				" of them are free at the moment.\n\n" <<
				"Please pick a room you'd like to stay in: ";

			//prints a litle menu bit up top and prints the amount of rooms
			//and the amount of available rooms
			//the available rooms are visible in main.cpp menu option 4
			//check_available_rooms

			cin >> roomnum;

			if (cin.fail() || roomnum > amount || roomnum < 1) {

				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
				cout << "Invalid input! Use an integer between 1 - " << amount << " !\n\n";
				continue;
			}//basic input validation

			bool available = availability(Rooms, roomnum - 1);

			if (available == false) {
				system("cls");
				cout << "This room is already booked, try another room.\n\n";
			}//checks if the chosen room is available

			else {
				break;
			}

		} while (1); //this loops does not break unless available room is chosen

		price = Rooms[roomnum - 1].price;
		//the "-1" are ugly but vector goes from 0, 1, 2, so for the sake of simplicity
		//and user experience i've done this

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
		}// basic input validation

		total = price * nights;

		cout << "\nYour full name for the booking: ";

		//cin ignore ignores the single \n in buffer
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
		else if (name.length() < Min_Len) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");
			cout << "Name is too short, type your first and last name !\n\n";
			continue;
		}//the three ifs are for input validation, only sets min and max length
		 //and checks that the input is not emmpty

		system("cls");

		cout << "**************************************\n";
		cout << "                BOOKING                \n\n";

		cout << "Is the information below correct?\n\n";
		cout << "Name: " << name << "\n";
		cout << "Roomnumber: " << roomnum << "\n";
		cout << "Duration of stay: " << nights << "\n";
		cout << "Total price " << total << "$" << "\n";
		cout << "Booking number: " << bookingnumber << "\n";
		cout << "(y/n): ";

		cin >> input;
		//asks user to confirm the information of the booking

		if (input == 'y' || input == 'Y') {

			Rooms[roomnum - 1].guestname = name;
			Rooms[roomnum - 1].bookingnum = bookingnumber;
			Rooms[roomnum - 1].bookingprice = total;
			Rooms[roomnum - 1].duration = nights;

			reset_prices(Rooms, amount);
			//yes sets the variables of chosen room and resets prices of all rooms
			//all room prices are randomized already when the program boots

			cout << "\nThank you for your booking.\n\n" <<
				"Would you like to make another booking?\n" <<
				"(y/n): ";
			cin >> input;
			//you can make bookings like this until the hotel is full

			if (input == 'y' || input == 'Y') {
				system("cls");
			}
			else if (input == 'n' || input == 'N') {
				system("cls");
				cout << "Quitting to main menu..\n\n";
				this_thread::sleep_for(chrono::milliseconds(500));
			}//input only accepts y,Y,n or N
			else {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
				cout << "Faulty input! use Y,y or N,n.\n\n";
			}//else is for input validation
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
		}//else is for input validation

	} while (input != 'n' && input != 'N');
}


void check_available_rooms(vector<room> Rooms, int amount) {



	cout << "**************************************\n";
	cout << "           AVAILABLE ROOMS           \n\n";

	for (int i = 0; i < amount; ++i) {

		bool available = availability(Rooms, i);
		if (available == true) {
		//checks what rooms are available

			cout << "*Roomnro: " << Rooms[i].roomnum <<
				" _ Price for one night: " << 
				Rooms[i].price << "$\n";

			this_thread::sleep_for(chrono::milliseconds(30));
		}
	}
	cout << "\n**************************************\n\n";

	system("pause");
	//the prompt simply pauses for a while and continues after user input

	system("cls");
	cout << "Quitting to main menu..\n\n";
	this_thread::sleep_for(chrono::milliseconds(500));
}

//this whole bit is so you can check available rooms, first of all to know what number to pick
//and secondly you can scout the cheapest price from the list before making a booking



void booking_search_menu(vector<room>& Rooms, int amount) {

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
		//prints a similiar menu as the menu in main.cpp

		if (cin.fail()) {

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");
			cout << "Invalid input! Choose an integer from 1 to 3!\n\n";
			this_thread::sleep_for(chrono::milliseconds(500));
		}//input validation

		else {

			//a basic switch case same as main.cpp
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
			}//default is input validation

		}
	} while (input != 3);//again exiting with last integer
}
#include <iostream>
#include <vector>
#include "classfunctions.h"
#include <fstream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;



int getroomprice() {

	int price = rand() % 21 + 80;
	return price;
}
//returns a number between 80 - 100;



int getbookingnum() {
	int bookingnum = rand() % 90000 + 10000;
	return bookingnum;
}
//returns a random int between 10000 - 99999



void reset_prices(vector<room>& Rooms, int amount) {

	for (int i = 0; i < amount; ++i) {
		Rooms[i].price = getroomprice();
	}
}
//loop that randomizes room prices



bool availability(vector<room> Rooms, int Room) {

	if (Rooms[Room].bookingnum > 0) {
		return false;
	}
	else {
		return true;
	}
}
//returns true/false depending on the booking number, by default booking number is 0
// 0 = true = the room is unbooked



void show_room_info(vector<room> Rooms, int amount) {

	cout << "Roomnumber: " << Rooms[amount].roomnum << "\n";
	cout << "Booked by: " << Rooms[amount].guestname << "\n";
	cout << "Bookingnumber: " << Rooms[amount].bookingnum << "\n";
	cout << "current price: " << Rooms[amount].price << "$ for one night\n";
	cout << "Total price: " << Rooms[amount].bookingprice << "$\n";
	cout << "Booked for: " << Rooms[amount].duration << " nights\n";
}
//couts all info of the specified room



void delete_booking(vector<room>& Rooms, int amount) {
	Rooms[amount].guestname.clear();
	Rooms[amount].price = getroomprice();
	Rooms[amount].bookingprice = 0;
	Rooms[amount].bookingnum = 0;
	Rooms[amount].duration = 0;
}
//sets a specified room to default state



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
//loop that counts every available room, and returns the final value



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
//makes a list of all the booked rooms, shows roomnumbers and prices of the rooms
//sleep_for function is used simply to make the app more nostalgic and cool



void search_by_number(vector<room>& Rooms, int amount) {

	char input = '\0';

	do {

		//declaring the variables required
		int numsearch;
		string search;
		vector<int> searchresult;

		//using the previous function to print a list of booked numbers
		check_booked_rooms(Rooms, amount);

		cout << "\nSearch by number: ";
		cin >> search;

		//no feed validation because it's a search, i didn't deem it necessary
		for (int i = 0; i < amount; ++i) {

			if (to_string(Rooms[i].bookingnum).find(search) != string::npos) {

				searchresult.push_back(i);
			}
		}
		//search is case sensitive, but works fine, the values from the loop counter i are saved
		//to a vector, therefore saving the rooms that match the search

		int size = searchresult.size();
		//declaring a variable that saves the vectors size

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
			//providing an option to exit if there were no results
			//sleep_for again just for added coolness

			else {
				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
			}//simple feed validation for the quit option

		}

		else {

			for (int i = 0; i < size; ++i) {

				int result = searchresult[i];

				cout << "Room number: " << result + 1 << "\n";
			}//prints the roomnumbers that matched the search

			cout << "\nPick one of the results to see reservation info: \n";
			cin >> numsearch;

			bool result = availability(Rooms, numsearch - 1);
			if (cin.fail() || numsearch > amount || numsearch < 1) {

				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
				cout << "Invalid input! Use an integer between 1 - " << amount << " !\n\n";
				continue;
			}	//feed validation
			else if (result == true) {

				cin.clear();
				cin.ignore(INT_MAX, '\n');
				system("cls");
				cout << "The room you chose is not booked, try again !\n\n";
				continue;
			}
			//stops the search from showing info of an unbooked room

			system("cls");
			show_room_info(Rooms, numsearch -1);
			//shows the info of the chosen room

			cout << "\nDo you want to delete the booking?\n";
			cout << "(y/n): ";
			//option for deleting the chosen booking

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

			}//after the last comment to here the code is just a lot of feed validation
		}    //and confirmations to go again or exit

	} while (input != 'n' && input != 'N');
}
//searches from vector by number



//the search by name works mostly in the same way as search by number
//so i'll only comment on the things that are different



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

		if (search.empty()) {
			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");
			cout << "You can't search by blank !\n\n";
		}
		//input with getline is the difference here, also the necessity to add
		//an input validation, for not showing all the rooms when you only press enter

		else {
			for (int i = 0; i < amount; ++i) {

				if (Rooms[i].guestname.find(search) != string::npos) {

					searchresult.push_back(i);
				}
			}
			//searching for a string already so we don't need to convert int to string

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

				bool result = availability(Rooms, numsearch -1);
				if (cin.fail() || numsearch > amount || numsearch < 1) {

					cin.clear();
					cin.ignore(INT_MAX, '\n');
					system("cls");
					cout << "Invalid input! Use an integer between 1 - " << amount << " !\n\n";
					continue;
				}
				else if (result == true) {
					
					cin.clear();
					cin.ignore(INT_MAX, '\n');
					system("cls");
					cout << "The room you chose is not booked, try again !\n\n";
					continue;
				}
				system("cls");
				show_room_info(Rooms, numsearch-1);

				cout << "\nDo you want to delete the booking?\n";
				cout << "(y/n): ";

				cin >> input;

				if (input == 'y' || input == 'Y') {
					delete_booking(Rooms, numsearch-1);

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
		}
	}while (input != 'n' && input != 'N');
}
//searches from vector by number

//a lot if the code is the same as search by number, in retrospect i should've made a function
//so the whole last part would've been unnecessary to write two seperate times

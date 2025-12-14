//Elias Laitala
//3p tehtävä.
#include <iostream>
#include "classfunctions.h"
#include "mainfunctions.h"
#include <vector>
#include <chrono>
#include <thread>
using namespace std;



int main() {
	srand(time(NULL));
	//seeding the random number generator

	int menuchoice;
	int room_numbers = Roomrand();
	//declaring variables used
	//room_numbers = 30-70

	vector<room> rooms =
		createrooms(room_numbers);
	//creating the vector of rooms that we'll me modifying in the code

	do {

		cout << "**************************************\n";
		cout << "                 MENU                 \n\n";
		cout << "1. Save file\n";
		cout << "2. Load file\n";
		cout << "3. Book a room\n";
		cout << "4. Show available rooms\n";
		cout << "5. Search for a booking\n";
		cout << "6. Exit\n\n";

		cout << "**************************************\n\n";
		cout << "Enter your choice: ";
		cin >> menuchoice;
		//Printed a beautiful menu for the user

		if (cin.fail()) {

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");
			cout << "Invalid input! Choose an integer from 1 to 6!\n\n";
			this_thread::sleep_for(chrono::milliseconds(500));
		}//basic input validation

		else {

			switch (menuchoice) {

			case 1:

				system("cls");
				savefile(rooms, room_numbers);
				cout << "File saved succesfully!\n\n";
				//all cases just run one of the predetermined main functions

				break;

			case 2:

				system("cls");
				loadfile(rooms, room_numbers);
				cout << "File loaded succesfully!\n\n";

				break;

			case 3:

				system("cls");
				room_booking(rooms, room_numbers);

				break;

			case 4:

				system("cls");
				check_available_rooms(rooms, room_numbers);

				break;

			case 5:

				system("cls");
				booking_search_menu(rooms, room_numbers);

				break;

			case 6:
				system("cls");
				cout << "Exiting program...\n";
				this_thread::sleep_for(chrono::milliseconds(500));

				break;

			default:

				system("cls");
				cout << "Invalid input! Choose an integer from 1 to 6!\n\n";
				//default validates the number input as well
			}
		}
	} while (menuchoice != 6);
	//exit with option 6

	return 0;
}
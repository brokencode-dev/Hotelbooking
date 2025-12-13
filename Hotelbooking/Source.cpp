//Elias Laitala
//3p tehtävä.
#include <iostream>
#include "Header.h"
#include <vector>
#include <chrono>
#include <thread>

using namespace std;



int main() {
	srand(time(NULL));

	int menuchoice;
	int room_numbers = Roomrand();

	vector<room> rooms =
		createrooms(room_numbers);

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

		if (cin.fail()) {

			cin.clear();
			cin.ignore(INT_MAX, '\n');
			system("cls");
			cout << "Invalid input! Choose an integer from 1 to 6!\n\n";
			this_thread::sleep_for(chrono::milliseconds(500));
		}

		else {

			switch (menuchoice) {

			case 1:

				system("cls");
				savefile(rooms, room_numbers);
				cout << "File saved succesfully!\n\n";

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
				booking_search(rooms, room_numbers);

				break;

			case 6:
				system("cls");
				cout << "Exiting program...\n";
				this_thread::sleep_for(chrono::milliseconds(500));

				break;

			default:

				system("cls");
				cout << "Invalid input! Choose an integer from 1 to 6!\n\n";

			}
		}
	} while (menuchoice != 6);

	return 0;
}
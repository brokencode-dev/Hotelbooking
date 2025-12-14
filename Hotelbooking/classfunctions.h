#pragma once
#include <iostream>
#include <vector>
using namespace std;


int getroomprice();
//returns a number between 80 - 100

class room
{
public:

	int roomnum;
	string guestname;
	int bookingnum;
	int price;
	int bookingprice;
	int duration;
	//specifying all the variables i need in this class

	room(int Roomnum) {
		roomnum = Roomnum;
		price = getroomprice();
		bookingprice = 0;
		bookingnum = 0;
		duration = 0;
	}
	//the constrictor configures a default state for all newly created rooms
};


bool availability(vector<room> Rooms, int Room);
//returns true/false is the specified room is booked

int available_rooms_count(vector<room> Rooms, int amount);
//returns all the available rooms in total

int getbookingnum();
//returns a random int between 10000 - 99999

void reset_prices(vector<room>& Rooms, int amount);
//randomizes all room prices

void check_booked_rooms(vector<room> Rooms, int amount);
//shows a list of all the booked rooms

void show_room_info(vector<room> Rooms, int amount);
//prints all the info of the specified room

void delete_booking(vector<room>& Rooms, int amount);
//resets the room variables to default and randomizes the price again

void search_by_name(vector<room>& Rooms, int amount);
//searches booked rooms by name

void search_by_number(vector<room>& Rooms, int amount);
//searches booked rooms by number


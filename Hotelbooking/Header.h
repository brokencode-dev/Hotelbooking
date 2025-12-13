#pragma once
#include <iostream>
#include <vector>
using namespace std;

const int price_per_night = 100;

int getroomprice();

class room
{
public:

	int roomnum;
	string guestname;
	int bookingnum;
	int price;
	int bookingprice;
	int duration;


	room(int Roomnum) {
		roomnum = Roomnum;
		price = getroomprice();
		bookingprice = 0;
		bookingnum = 0;
		duration = 0;
	}
};

int Roomrand();
vector<room> createrooms(int amount);

void booking_search(vector<room>& Rooms, int amount);
void savefile(vector<room> Rooms, int amount);
void loadfile(vector<room>& Rooms, int& amount);

bool availability(vector<room> Rooms, int Room);
int available_rooms_count(vector<room> Rooms, int amount);

int getbookingnum();
void reset_prices(vector<room>& Rooms, int amount);
void room_booking(vector<room> &Rooms, int amount);

void check_available_rooms(vector<room> Rooms, int amount);
void check_booked_rooms(vector<room> Rooms, int amount);

void show_room_info(vector<room> Rooms, int amount);
void delete_booking(vector<room>& Rooms, int amount);
void search_by_name(vector<room>& Rooms, int amount);
void search_by_number(vector<room>& Rooms, int amount);


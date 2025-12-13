#pragma once
#include <iostream>
#include <vector>
using namespace std;

const int price_per_night = 100;

class room
{
public:

	int roomnum;
	string guestname;
	int bookingnum;
	int price;
	int duration;

	room(int Roomnum) {
		roomnum = Roomnum;
		price = price_per_night;
		bookingnum = 0;
		duration = 0;
	}
};

int Roomrand();
vector<room> createrooms(int amount);

void savefile(vector<room> Rooms, int amount);
void loadfile(vector<room>& Rooms, int& amount);

bool availability(vector<room> Rooms, int Room);
int available_rooms_count(vector<room> Rooms, int amount);

int getroomprice();
int getbookingnum();

void room_booking(vector<room> &Rooms, int amount);



//Elias Laitala
#pragma once
#include <vector>
#include "classfunctions.h"
using namespace std;

//This header file contains the functions called in the main function

int Roomrand();
//randomizes a number from 30 to 70

vector<room> createrooms(int amount);
//creates a vector of type room, and configures the default variable values

void savefile(vector<room> Rooms, int amount);
//saves file to savefile.txt

void loadfile(vector<room>& Rooms, int& amount);
//loads file from savefile.txt

void room_booking(vector<room>& Rooms, int amount);
//function for making bookings

void check_available_rooms(vector<room> Rooms, int amount);
//makes a list of all available rooms, and their current prices

void booking_search_menu(vector<room>& Rooms, int amount);
//a small menu for searching through bookings, can also delete bookings
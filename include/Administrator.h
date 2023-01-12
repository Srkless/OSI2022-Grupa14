#pragma once
#include<string>
#include<iostream>
#include<vector>  
#include "Ride.h"      

bool is_equal(std::string name);
bool modify(std::string,std::ofstream& file);

class Administrator
{
public:
	void generatingTravelOrder(const std::string& travelOrderFileName, const Ride& ride) const noexcept(false); /// podaci naloga, putanja
	void ViewUserAccount();
	bool SuspendingUserAccount();
	bool CreateCodeBook();
	bool DeleteCodeBook();
	bool ModificationCodeBoks();

};


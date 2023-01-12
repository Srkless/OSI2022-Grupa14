#include "Ride.h"

Ride::Ride()
	: m_Driver(""), m_StartTime(std::string()), m_EndTime(std::string()), m_StartLocation(""), m_PathLocations{}, m_EndLocation("") {}

Ride::Ride(std::string rideID, std::string driver, std::string startTime, std::string endTime, std::string startLocation, std::vector<std::string> pathLocations, std::string endLocation)
	: m_RideID(rideID), m_Driver(driver), m_StartTime(startTime), m_EndTime(endTime), m_StartLocation(startLocation), m_PathLocations(pathLocations), m_EndLocation(endLocation) {}

void Ride::setRideID(std::string RideID)
{
	m_RideID = RideID;
}

void Ride::setDriver(std::string driver)
{
	m_Driver = driver;
}

void Ride::setStartTime(std::string startTime)
{
	m_StartTime = startTime;
}

void Ride::setEndTime(std::string endTime)
{
	m_EndTime = endTime;
}

void Ride::setStartLocation(std::string startLocation)
{
	m_StartLocation = startLocation;
}

void Ride::setEndLocation(std::string endLocation)
{
	m_EndLocation = endLocation;
}

void Ride::setPathLocationos(std::vector<std::string> pathLocations)
{
	m_PathLocations = pathLocations;
}

std::string Ride::getRideID() const
{
	return m_RideID;
}

std::string Ride::getDriver() const
{
	return m_Driver;
}

std::string Ride::getStartTime() const
{
	return m_StartTime;
}

std::string Ride::getEndTime() const
{
	return m_EndTime;
}

std::string Ride::getStartLocation() const
{
	return m_StartLocation;
}

std::vector<std::string> Ride::getPathLocations() const
{
	return m_PathLocations;
}

std::string Ride::geEndLocation() const
{
	return m_EndLocation;
}

std::istream& operator>>(std::istream& is, Ride& ride)
{
	std::string line;
	std::getline(is, line);
	std::stringstream sstream(line);
	std::vector<std::string> items;
	std::vector<std::string> pathLocationItems;
	std::string item;
	size_t count = 0;
	while (std::getline(sstream, item, '#') && count < 5)
	{
		items.push_back(item);
		count++;
	}
	while (std::getline(sstream, item, '!'))
	{
		pathLocationItems.push_back(item);
	}

	std::getline(sstream, item, '#');

	ride.m_RideID = items[0];
	ride.m_Driver = items[1];
	ride.m_StartTime = items[2];
	ride.m_EndTime = items[3];
	ride.m_StartLocation = items[4];
	ride.m_EndLocation = item;
	ride.m_PathLocations = pathLocationItems;

	return is;
}

std::ostream& operator<<(std::ostream& os, const Ride& ride)
{
	os << ride.m_RideID << "#" << ride.m_Driver << "#" << ride.m_StartTime << "#" << ride.m_EndLocation << "#" << ride.m_StartLocation << "#" << ride.m_EndLocation << "#";
	for (size_t i = 0; i < ride.m_PathLocations.size(); i++)
	{
			os << ride.m_PathLocations[i] << "!";
	}
	os << ride.m_EndLocation;
	return os;
}

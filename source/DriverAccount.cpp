#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <unordered_map>
#include "DriverAccount.h"
#include "Ride.h"
#include "Report.h"
#include "ProblemReport.h"
#include "database.h"

inline bool checkName(std::string fileDirectory, std::string fileArray, std::string fileName)
{
	std::vector<std::string> fileData;
	std::filesystem::path path1 = std::filesystem::current_path();
	path1 += "\\data";
	std::filesystem::create_directories(path1);
	path1 += fileDirectory;
	path1 += fileArray;
	std::string word;
	std::ifstream file(path1);

	while (file >> word)
	{
		fileData.push_back(word);
	};

	file.close();
	std::string name;
	for (int i = 0; i < fileData.size(); i++)
	{
		if (fileName == fileData[i])
			return true;
	}
	return false;
}

Ride& DriverAccount::routeOverview(const std::string& fileName, std::unordered_map<std::string, Ride>& map) const noexcept(false)
{
	return map[fileName];
}

void DriverAccount::writeReport(const std::string& fileName, Report& report) const noexcept(false)
{
	std::ofstream file;
	std::filesystem::path path1 = std::filesystem::current_path();
	path1 += "\\data\\reports\\";
	std::filesystem::create_directories(path1);
	path1 += fileName;
	file.open(path1);

	std::ofstream fileArray;
	std::filesystem::path path2 = std::filesystem::current_path();
	path2 += "\\data\\reports";
	path2 += "\\AllReports.txt";
	fileArray.open(path2, std::ios::app); 

	if (fileArray.good() && file.good())    // rideID, username, startTime, endTime, startLocation, pathLocations, endLocation
	{
		if (!checkName("\\reports\\", "AllReports.txt", fileName))
		{
			fileArray << fileName << std::endl;
			file << report;
		}
		fileArray.close();
		file.close();
	}
}

void DriverAccount::problemReport(const std::string& fileName, ProblemReport& report) const noexcept(false)
{
	std::ofstream file;
	std::filesystem::path path1 = std::filesystem::current_path();
	path1 += "\\data\\problemReports\\";
	std::filesystem::create_directories(path1);
	path1 += fileName;
	file.open(path1);

	std::ofstream fileArray;
	std::filesystem::path path2 = std::filesystem::current_path();
	path2 += "\\data\\problemReports";
	path2 += "\\AllProblemReports.txt";
	fileArray.open(path2, std::ios::app);


	if (fileArray.good() && file.good())    // rideID, username, startTime, endTime, startLocation, pathLocations, endLocation
	{
		if (!checkName("problemReports\\", "AllProblemReports.txt", fileName))
		{
			fileArray << fileName << std::endl;
			file << report;
		}
	}
}

std::unordered_map<std::string, Report> DriverAccount::overviewReports() const noexcept(false)
{
	return db::loadReportsFromFile();
}

std::unordered_map<std::string, ProblemReport> DriverAccount::overviewProblemReports() const noexcept(false)
{
	return db::loadProblemReportsFromFile();
}

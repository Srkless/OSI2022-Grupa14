#pragma once
#include <unordered_map>
#include <iostream>
#include <memory>
#include <concepts>
#include <functional>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <type_traits>
#include "Ride.h"
#include "Bus.h"
#include "UserAccount.h"
#include "Schedule.h"
#include "Report.h"
#include "ProblemReport.h"

namespace db
{

	inline void createSafetyCopy(const std::filesystem::path& destination)
	{
		std::filesystem::path source = "data\\";
		std::filesystem::create_directories(destination);
		for (auto& file : std::filesystem::recursive_directory_iterator(source))
		{
			std::filesystem::path currentFile = file.path();
			std::filesystem::path newFile = destination / currentFile.relative_path();
			if (std::filesystem::is_directory(currentFile))
			{
				std::filesystem::create_directories(newFile);
			}
			else
			{
				std::filesystem::create_directories(newFile.parent_path());
				std::ifstream  src(currentFile, std::ios::binary);
				std::ofstream  dst(newFile, std::ios::binary);
				dst << src.rdbuf();
			}
		}
	}

	inline std::unordered_map<std::string, bus> readBusFromFile()
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\codebooks";
		std::filesystem::create_directories(path);
		path += "\\Bus.txt";
		std::ifstream iFile(path);
		std::unordered_map<std::string, bus> busMap;

		if (std::filesystem::exists(path))
		{
			iFile.seekg(0, std::ios::beg);
			if (iFile.peek() == std::ifstream::traits_type::eof())
			{
				return busMap;
			}
			else
			{
				while (!iFile.eof())
				{
					path = std::filesystem::current_path();
					path += "\\data\\codebooks\\";

					std::string name;
					std::getline(iFile, name);
					path += (name + ".txt");

					bus tmpBus;

					std::ifstream iFile2(path);
					iFile2 >> tmpBus;

					busMap[tmpBus.getRegistraion()] = tmpBus;
					iFile2.close();
				}
			}
			iFile.close();
		}
		return busMap;
	}

	inline std::unordered_map<std::string, std::vector<std::string>> readTourFromFile()
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\codebooks";
		std::filesystem::create_directories(path);
		path += "\\Tour.txt";
		std::ifstream iFile(path);

		if (std::filesystem::exists(path))
		{
			iFile.seekg(0, std::ios::beg);
			if (iFile.peek() == std::ifstream::traits_type::eof())
			{
				std::unordered_map<std::string, std::vector<std::string>> tourMap;
				return tourMap;
			}
			else
			{
				std::unordered_map<std::string, std::vector<std::string>> tourMap;
				int count = 0;
				while (!iFile.eof())
				{

					path = std::filesystem::current_path();
					path += "\\data\\codebooks\\";

					std::string name;
					std::getline(iFile, name);
					path += (name + ".txt");

					std::vector<std::string> tmpTour;
					std::string tmpString;
					std::ifstream iFile2(path);
					std::getline(iFile2, tmpString);
					iFile2.close();

					std::stringstream ss(tmpString);
					std::string item;
					while (getline(ss, item, '#'))
						tmpTour.push_back(item);

					tourMap[tmpTour[0]] = tmpTour;
				}
				iFile.close();
				return tourMap;
			}
		}
	}

	// used to make sure no duplicates exist
	inline bool checkName(std::string fileDirectory, std::string fileArray, std::string fileName)
	{
		std::vector<std::string> fileData;
		std::filesystem::path path1 = std::filesystem::current_path();
		path1 += "\\data\\";
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

	inline void writeScheduleToFile(Schedule& schedule)
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\rides\\schedule.txt";
		std::ofstream oFile(path);
		oFile << schedule;
		oFile.close();
	}

	inline Schedule readScheduleFromFile()
	{
		std::filesystem::path schedulePath = std::filesystem::current_path();
		schedulePath += "\\data\\rides\\schedule.txt";
		Schedule tmp;
		if (std::filesystem::exists(schedulePath))
		{
			
			std::ifstream iFile(schedulePath);
			if (iFile.peek() == std::ifstream::traits_type::eof())
			{
				return tmp;
			}
			else
			{
				while (!iFile.eof())
				{
					std::string rideID;
					iFile >> rideID;
					tmp.addRideToSchedule(rideID);
				}
			}
		}
		return tmp;
	}

	inline void editScheduleFile(const std::string rideID)
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\rides";
		std::filesystem::create_directories(path);
		path += "\\schedule.txt";
		std::ofstream oFile;
		oFile.open(path, std::ios::app);

		oFile.seekp(0, std::ios::end);
		if (oFile.tellp() == 0)
		{
			oFile << rideID;
		}
		else
		{
			oFile << std::endl << rideID;
		}
		oFile.close();
	}

	// read rides from file into an unordered map
	inline std::unordered_map<std::string, Ride> loadRidesFromFile()
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\rides";
		std::filesystem::create_directories(path);
		path += "\\allRides.txt";
		std::unordered_map<std::string, Ride> rides;

		if (std::filesystem::exists(path))
		{
			std::ifstream iFile;
			iFile.open(path);
			while (!iFile.eof())
			{
				path = std::filesystem::current_path();
				path += "\\data\\rides\\";

				std::string name;
				std::getline(iFile, name);
				path += name;

				std::ifstream iFile2(path);
				Ride newRide;

				iFile2 >> newRide;
				rides[newRide.getRideID()] = newRide;
				iFile2.close();
			}
			iFile.close();
		}
		return rides;
	}

	// add Ride to a file
	inline void addRideToFile(const Ride& ride)
	{
		std::ofstream oFile;
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\rides";
		std::filesystem::create_directories(path);
		path += "\\allRides.txt";
		oFile.open(path, std::ios::app);

		std::ofstream oFile2;
		path = std::filesystem::current_path();
		path += "\\data\\rides\\";
		path += ride.getRideID();
		path += ".txt";

		oFile.seekp(0, std::ios::end);
		if (oFile.tellp() == 0)
		{
			oFile << ride.getRideID() << ".txt";
			oFile2.open(path);
			oFile2 << ride;
			oFile2.close();
		}
		else
		{
			std::string cmpName = ride.getRideID() + ".txt";
			if (!checkName("rides", "\\allRides.txt", cmpName))
			{
				oFile << std::endl << ride.getRideID() << ".txt";
				oFile2.open(path);
				oFile2 << ride;
				oFile2.close();
			}
		}
		oFile.close();
	}

	inline void rewriteExistingRide(const Ride& ride)
	{
		std::ofstream file;
		std::filesystem::path path = std::filesystem::current_path();
		path = std::filesystem::current_path();
		path += "\\data\\rides\\";
		path += ride.getRideID();
		path += ".txt";


		std::string cmpName = ride.getRideID() + ".txt";
		if (checkName("rides", "\\allRides.txt", cmpName))
		{
			file.open(path, std::ios::out);
			file << ride;
			file.close();
		}
	}

	inline std::unordered_map<std::string, UserAccount> loadUsersFromFile()
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\users";
		std::filesystem::create_directories(path);
		path += "\\userData.txt";
		std::ifstream iFile(path);
		std::unordered_map<std::string, UserAccount> users;

		while (!iFile.eof())
		{
			UserAccount acc;
			iFile >> acc;
			users[acc.getUsername()] = acc;
		}
		iFile.close();
		return users;
	}

	inline std::unordered_map<std::string, Report> loadReportsFromFile()
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\reports";
		std::filesystem::create_directories(path);
		path += "\\allReports.txt";
		std::ifstream iFile(path);
		std::unordered_map<std::string, Report> reports;

		if (std::filesystem::exists(path))
		{
			while (!iFile.eof())
			{
				std::filesystem::path path = std::filesystem::current_path();
				path += "\\data\\reports\\";

				std::string name;
				std::getline(iFile, name);
				path += name;
				path += ".txt";

				Report rep;

				std::ifstream iFile2(path);
				iFile2 >> rep;

				reports[rep.getRideID()] = rep;
				iFile2.close();
			}
			iFile.close();
		}

		return reports;
	}

	inline std::unordered_map<std::string, ProblemReport> loadProblemReportsFromFile()
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\problemReports";
		std::filesystem::create_directories(path);
		path += "\\allProblemReports.txt";
		std::unordered_map<std::string, ProblemReport> problemReports;

		if (std::filesystem::exists(path))
		{
			std::ifstream iFile(path);
			while (!iFile.eof())
			{
				std::filesystem::path path = std::filesystem::current_path();
				path += "\\data\\problemReports\\";

				std::string name;
				std::getline(iFile, name);
				path += name;
				path += ".txt";

				ProblemReport probRep;

				std::ifstream iFile2(path);
				iFile2 >> probRep;

				problemReports[probRep.getRideID()] = probRep;
				iFile2.close();
			}
			iFile.close();
		}

		return problemReports;
	}

	// adds user to database
	// should only be used during registration 

	inline void addUserToFile(const UserAccount& usr)
	{
		std::ofstream oFile;
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\users";
		std::filesystem::create_directories(path);
		path += "\\userData.txt";
		oFile.open(path, std::ios::app);

		oFile << std::endl << usr;
		oFile.close();
	}

	// write users to database
	inline void writeUsersToFile(std::unordered_map<std::string, UserAccount>& map)
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\users";
		std::filesystem::create_directories(path);
		path += "\\userData.txt";

		std::ofstream oFile(path);
		bool flag = false;

		for (auto& user : map)
		{
			if (user.second.getUsername() != "")
			{
				if(flag == false)
				{
					oFile.seekp(0, std::ios::end);
					if (oFile.tellp() == 0)
						if (!(user.second.getUsername() == ""))
							oFile << user.second;
					flag = true;
				}
				else
					if (!(user.second.getUsername() == ""))
						oFile << std::endl << user.second;
			}
		}
		oFile.close();
	}

	template<typename T>
	concept Readable = requires(std::istream & is, T & a)
	{
		{is >> a} ->std::convertible_to<std::istream&>;
	};

	inline std::unordered_map<std::string, UserAccount> loadDriversFromFile()
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\users";
		std::filesystem::create_directories(path);
		path += "\\userData.txt";
		std::ifstream iFile(path);
		std::unordered_map<std::string, UserAccount> drivers;

		while (!iFile.eof())
		{
			UserAccount acc;
			iFile >> acc;
			if (acc.getAccountType() == "driver")
			{
				drivers[acc.getUsername()] = acc;
			}

		}
		iFile.close();
		return drivers;
	}

	inline std::unordered_map<std::string, Ride> loadDriverRides(std::string driverName)
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\rides";
		std::filesystem::create_directories(path);
		path += "\\allRides.txt";

		std::unordered_map<std::string, Ride> rides;
		std::ifstream iFile;

		
		if (std::filesystem::exists(path))
		{
			iFile.open(path);
			while (!iFile.eof())
			{
				path = std::filesystem::current_path();
				path += "\\data\\rides\\";

				std::string name;
				std::getline(iFile, name);
				path += name;

				std::ifstream iFile2(path);
				Ride newRide;

				iFile2 >> newRide;
				if (newRide.getDriver() == driverName)
					rides[newRide.getRideID()] = newRide;

				iFile2.close();
			}
		}
		iFile.close();

		return rides;
	}

	inline std::unordered_map<std::string, Report> loadDriverReports(std::string driverName)
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\reports";
		std::filesystem::create_directories(path);
		path += "\\allReports.txt";

		std::unordered_map<std::string, Report> reportMap;
		std::ifstream allReports;

		allReports.open(path);
		if (std::filesystem::exists(path))
		{
			while (!allReports.eof())
			{
				path = std::filesystem::current_path();
				path += "\\data\\reports\\";

				std::string name;
				std::getline(allReports, name);
				path += name;
				path += ".txt";

				std::ifstream report(path);
				Report newReport;

				report >> newReport;
				if (newReport.getAuthor() == driverName)
					reportMap[newReport.getRideID()] = newReport;

				report.close();
			}
		}
		allReports.close();

		return reportMap;
	}

	inline std::unordered_map<std::string, ProblemReport> loadDriverProblemReports(std::string driverName)
	{
		std::filesystem::path path = std::filesystem::current_path();
		path += "\\data\\problemReports";
		std::filesystem::create_directories(path);
		path += "\\allProblemReports.txt";

		std::unordered_map<std::string, ProblemReport> reportMap;
		std::ifstream allReports;

		allReports.open(path);
		if (std::filesystem::exists(path))
		{
			while (!allReports.eof())
			{
				path = std::filesystem::current_path();
				path += "\\data\\problemReports\\";

				std::string name;
				std::getline(allReports, name);
				path += name;
				path += ".txt";

				std::ifstream report(path);
				ProblemReport newReport;

				report >> newReport;
				if (newReport.getAuthor() == driverName)
					reportMap[newReport.getRideID()] = newReport;

				report.close();
			}
		}
		allReports.close();

		return reportMap;
	}
};
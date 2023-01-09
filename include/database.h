#pragma once
#include <iostream>
#include <concepts>
#include <functional>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>
#include <type_traits>

namespace db
{
	template<typename T>
	concept Readable = requires(std::istream & is, T & a)
	{
		{is >> a} ->std::convertible_to<std::istream&>;
	};

	// function for reading a specified type from a file
	// assumes that the '#' symbol terminates the data type
	// default type is string
	template<typename T = std::string>
	requires Readable<T> && (std::copy_constructible<T> || std::copyable<T>)
	T readItem(std::ifstream& is)
	{
		std::string line;
		std::getline(is, line, '#');
		
		std::stringstream stream(line);

		T tmp;

		stream >> tmp;

		return tmp;
	}

	// function for reading the whole file
	// can only read one type of data, specified by T
	// accepts two std::function wrappers
	// the first argument takes the path of the file which will be read from
	// the second argument takes a function which will define what will be done with the output
	// the third argument takes a function which defines the method of reading from the file and can be omitted - by default will read one string from the file
	// here is an example of how to call this function from main
	// 
	// this will print out the first word from the test.txt file located in the Documents folder
	// 
	// db::readFileCustom<std::string>("C:/Users/urnm/Documents/test.txt", [](std::string str) {std::cout << str; });
	//
	// template parameters:
	// T is the type of data being read from file
	// O is the return type of the specified work function, if the function returns nothing, shoule be void
	//
	template<typename T, typename O = void>
	O readFileCustom(std::filesystem::path path, std::function<O(T& a)> outputFunction, std::function<T(std::ifstream& is)> inputFunction = [](std::ifstream& is) {return readItem<T>(is); })
	{
		std::ifstream inputFile(path);
		T workData;
		workData = inputFunction(inputFile);
		O returnVal = outputFunction(workData);
		inputFile.close();
		return O;
	}

	
}

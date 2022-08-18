// ItemListConverter.cpp : This file contains the 'main' function. Program execution begins and ends there.
// by OverDestiny 
// Customize SeiTbNao
//

#include <Windows.h>
#include <iostream>
#include <memory>
#include "WYDCsv2BinConverter.h"
#include "WYDBin2CsvConverter.h"

int main(int argc, char* argv[])
{
	if (argc != 2)
	{
		std::cout << "Correct usage: <[bin2csv][csv2bin]>";

		return 0;
	}

	try
	{
		std::unique_ptr<WYDConverter> converter;
		std::string command{ argv[1] };
		if (command == "csv2bin")
			converter = std::make_unique<WYDCsv2BinConverter>();
		else if (command == "bin2csv")
			converter = std::make_unique<WYDBin2CsvConverter>();

		if (!(bool)converter)
		{
			MessageBoxA(NULL, "Correct usage: <[bin2csv][csv2bin]>", "Error", MB_OK);

			return 0;
		}

		converter->Convert();
	}
	catch (std::exception& e)
	{
		MessageBoxA(NULL, e.what(), "ERROR", MB_OK);
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file

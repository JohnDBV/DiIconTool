#include "CommandLineArguments.h"
#include <iostream>
#include "DiLib/DiFileInfo.h"

CommandLineArguments::CommandLineArguments(int argc, char* argv[])
{
	command = Command::None;
	processCommandLineArguments(argc, argv);
}

CommandLineArguments::~CommandLineArguments()
{
}

void CommandLineArguments::displayHelp()
{
	std::cout << "Usage :" << std::endl
		<< argv0 << " [/h] [--help] <unpack-sample> (it will dump some sample pictures on disk)" << std::endl
		<< argv0 << " [/h] [--help] <unpack> <iconFileName.ico>" << std::endl
		<< argv0 << " [/h] [--help] <pack> <destinationIconFileName.ico> <imageFile1.png|bmp> [imageFile2.png|bmp] ... ";
}

ErrorCodes CommandLineArguments::generateData()
{
	switch (command)
	{
		case Command::UnpackSample:
		{
			if (0 == mandatoryParamsCount)
			{
				performUnpackSample();
				return ErrorCodes::NoError;
			}
			else
			{
				std::cout << "Too many parameters !";
				return ErrorCodes::TooManyParameters;
			}
		}break;

		case Command::UnpackFile:
		{
			if (mandatoryParamsCount > 0)
			{
				if (mandatoryParamsCount > 1)
				{
					std::cout << "Too many parameters !";
					return ErrorCodes::TooManyParameters;
				}
				else
				{//exactly one mandatory parameter
					performUnpackFile();
					return ErrorCodes::NoError;
				}
			}
			else
			{
				std::cout << "Not enough parameters !";
				return ErrorCodes::NotEnoughParameters;
			}
		}break;

		case Command::PackFile:
		{
			if (mandatoryParamsCount > 1)
			{//at least two parameters
				performPackFile();
				return ErrorCodes::NoError;
			}
			else
			{
				std::cout << "Not enough parameters !";
				return ErrorCodes::NotEnoughParameters;
			}
		}break;

		default :
		{
			if (!isHelpDisplayed)
			{
				std::cout << "Unknown command !";
				return ErrorCodes::NotEnoughParameters;
			}
		}break;
	}


	return ErrorCodes::UnknownError;
}

void CommandLineArguments::processCommandLineArguments(int argc, char* argv[])
{
	argv0 = std::string(argv[0]);

	if (1 == argc)
	{
		displayHelp();
		isHelpDisplayed = true;
	}
	else
	{
		for (int i = 1; i < argc; ++i)
		{
			if ((std::string(argv[i]) == "/h") || (std::string(argv[i]) == "--help"))
			{
				if (!isHelpDisplayed)
				{//we can use both "/h" and "--help". Do it only ONCE !
					displayHelp();
					isHelpDisplayed = true;
				}
			}
			else
			{
				//search for the command first

				if (std::string(argv[i]) == "unpack-sample")
				{//use the current app path as a reference to unpack the pictures in the same directory
					command = Command::UnpackSample;
					srcFiles.push_back(argv[0]);
					break;
				}
				else
					if (std::string(argv[i]) == "unpack")
					{//use the argument path as a reference to unpack the pictures in the same directory
						command = Command::UnpackFile;
						continue;
					}
					else
						if (std::string(argv[i]) == "pack")
						{
							if (command != Command::PackFile)
							{//found the file name of the icon, to pack data on
								command = Command::PackFile;
								destFilePath = argv[i];
							}
							continue;
						}
						else
						{//just some file name here
							srcFiles.push_back(argv[i]);
							mandatoryParamsCount++;
						}
			}
		}

	}
}

ErrorCodes CommandLineArguments::performUnpackSample()
{
	return ErrorCodes();
}

ErrorCodes CommandLineArguments::performUnpackFile()
{
	return ErrorCodes();
}

ErrorCodes CommandLineArguments::performPackFile()
{
	return ErrorCodes();
}

#include "CommandLineArguments.h"
#include <iostream>
#include "DiLib/DiIconFile.h"
#include "SampleIconFilePng.h"

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
		<< argv0 << " [/h] [--help] <create-sample> (it will dump a sample icon file on disk)" << std::endl
		<< argv0 << " [/h] [--help] <unpack> <iconFileName.ico>" << std::endl
		<< argv0 << " [/h] [--help] <pack> <destinationIconFileName.ico> <imageFile1.png|bmp> [imageFile2.png|bmp] ... ";
}

ErrorCodes CommandLineArguments::generateData()
{
	switch (command)
	{
		case Command::DumpSample:
		{
			if (0 == mandatoryParamsCount)
			{
				performDumpSample();
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

				if (std::string(argv[i]) == "create-sample")
				{//use the current app path as a reference to unpack the pictures in the same directory
					command = Command::DumpSample;
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
								command = Command::PackFile;
							continue;
						}
						else
						{
							if ((0 == srcFiles.size()) &&
								(0 == destFilePath.size()) &&
								(Command::PackFile == command))
							{//found the destionation icon file path
								destFilePath = argv[i];
								mandatoryParamsCount++;
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
}

ErrorCodes CommandLineArguments::performDumpSample()
{
	//We need a DiBinaryFile and some DiFileData class filled with data.

	//1. Create the binary file
	di::file::DiBinaryFile binaryFile{ "SampleIconPngFormat.ico" }; //the file may not exist, if so it will not be automatically-read (as the behaviour of DiBinaryFile does)

	//2. Create the FileData empty object
	di::file::internal::DiFileData fileData;

	//2.1 : Set the binary data length
	fileData.binaryData.first = pngIconFileLength;

	//2.2 : Copy the binary data of the resource here(for demo purposes)
	// 
	//2.2.1 : Create a "garbage filled" buffer of the proper size
	std::unique_ptr<uint8_t[]> buff = std::make_unique<uint8_t[]>(pngIconFileLength);
	
	//2.2.2 : Copy all the resource's bytes on this buff
	memcpy(buff.get(), pngIconFileData.data(), pngIconFileLength);
	
	////2.2.3 : Move the unique_ptr array ownership
	fileData.binaryData.second = std::move(buff);

	//3. Write the data
	binaryFile.setFileContent(fileData);

	return ErrorCodes::NoError;
}

ErrorCodes CommandLineArguments::performUnpackFile()
{
	di::image::DiIconFile iconFile{srcFiles[0]};
	std::cout << "The icon file \"" << iconFile.getFileInfo().getFileNameWithoutExtension() << "\" contains " << iconFile.getImagesCount() << " images." << std::endl;

	std::cout << "Extracting images..." << std::endl;
	iconFile.extractImagesToCurrentFolder();
	
	std::cout << "Done !";

	return ErrorCodes::NoError;
}

ErrorCodes CommandLineArguments::performPackFile()
{
	di::image::DiIconFile iconFile{""};

	std::cout << "Adding image files to an empty icon file..." << std::endl;

	for (auto& imagePath : srcFiles)
	{
		di::file::DiFileInfo fi(imagePath);

		std::cout << "Adding picture : " << fi.getFileNameWithExtension() << std::endl;
		iconFile.addPicture(imagePath);
	}

	iconFile.getFileInfo().setFilePathTo(destFilePath);
	iconFile.getFileInfo().setFileExtensionTo("ico");

	std::cout << "The icon file \"" << iconFile.getFileInfo().getFileNameWithoutExtension() << "\" contains now " << iconFile.getImagesCount() << " images." << std::endl;

	std::cout << "Writing icon file as : " << std::endl
			  << iconFile.getFileInfo().getFilePath() << std::endl;

	iconFile.exportImagesToIconFile();

	std::cout << "Done !";

	return ErrorCodes::NoError;
}

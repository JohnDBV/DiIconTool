#ifndef __COMMAND_LINE_ARGUMENTS_H__
#define __COMMAND_LINE_ARGUMENTS_H__

#include <string>
#include <vector>

enum class Command
{
	None,
	UnpackSample,
	UnpackFile,
	PackFile
};

enum ErrorCodes
{
	NoError = 0,
	NotEnoughParameters,
	TooManyParameters,
	UnknownError
};

class CommandLineArguments
{
public:
	CommandLineArguments() = delete;
	CommandLineArguments(int argc, char * argv[]);

	//Rule of five : 
	CommandLineArguments(const CommandLineArguments& other) = delete;
	CommandLineArguments& operator = (const CommandLineArguments& other) = delete;
	CommandLineArguments(const CommandLineArguments&& other) = delete;
	CommandLineArguments& operator = (const CommandLineArguments&& other) = delete;
	~CommandLineArguments();

	[[noreturn]] void displayHelp();
	ErrorCodes generateData();

	Command command;

private :

	[[noreturn]] void processCommandLineArguments(int argc, char* argv[]);

	ErrorCodes performUnpackSample();
	ErrorCodes performUnpackFile();
	ErrorCodes performPackFile();

	std::string argv0;//the argv[0] path copy
	int mandatoryParamsCount = 0;
	std::vector<std::string> srcFiles;
	std::string destFilePath;
	bool isHelpDisplayed = false;

};

#endif
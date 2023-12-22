#include <iostream>
#include "CommandLineArguments.h"

int main(int argc, char* argv[])
{
	CommandLineArguments arguments{ argc, argv };
	return arguments.generateData();
}
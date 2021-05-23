#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <Windows.h>
#include "commands.h"

class Options {
public:
	Options();

	void ParseCommandLine(int argc, char* argv[]);
	void ParseConfigFile(std::string configFile);

	void PrintUsage() const noexcept;

	commandIds GetCommandId() const noexcept;

	std::wstring GetObsPath() const noexcept;
	std::wstring GetObsDirectory() const noexcept;
	std::wstring GetObsFilename() const noexcept;

private:
	commandIds commandId;

	std::wstring obsPath;
	std::wstring obsDirectory;
	std::wstring obsFilename;
};
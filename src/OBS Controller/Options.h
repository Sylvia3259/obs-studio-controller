#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include "commands.h"

class Options {
private:
	commandIds commandId;
	std::wstring obsPath;
	std::wstring obsDirectory;
	std::wstring obsFilename;

public:
	Options();

	void ParseCommandLine(int argc, char* argv[]);
	void ParseConfigFile(std::wstring configFile);

	commandIds GetCommandId() const noexcept;
	std::wstring GetObsPath() const noexcept;
	std::wstring GetObsDirectory() const noexcept;
	std::wstring GetObsFilename() const noexcept;
};
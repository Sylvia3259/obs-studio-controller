#include "Options.h"

Options::Options() {
	commandId = commandIds(-1);

	obsPath = L"C:\\Program Files\\obs-studio\\bin\\64bit\\obs64.exe";
	obsDirectory = L"C:\\Program Files\\obs-studio\\bin\\64bit";
	obsFilename = L"obs64.exe";
}

void Options::ParseCommandLine(int argc, char* argv[]) {
	if (argc != 2) {
		std::cout << "Invaild arguments" << std::endl;
		return;
	}

	const auto command = commands.find(argv[1]);
	if (command != commands.end())
		commandId = command->second;
	else
		std::cout << "Invaild arguments" << std::endl;
}

void Options::ParseConfigFile(std::wstring configFile) {
	std::wifstream file(configFile);
	if (file.is_open()) {
		std::getline(file, obsPath);

		const size_t position = std::wstring(obsPath).find_last_of(L"\\/");
		obsDirectory = std::wstring(obsPath).substr(0, position);
		obsFilename = std::wstring(obsPath).substr(position + 1);

		file.close();
	}
}

commandIds Options::GetCommandId() const noexcept {
	return commandId;
}

std::wstring Options::GetObsPath() const noexcept {
	return obsPath;
}

std::wstring Options::GetObsDirectory() const noexcept {
	return obsDirectory;
}

std::wstring Options::GetObsFilename() const noexcept {
	return obsFilename;
}
#include "Options.h"

Options::Options() {
	commandId = commandIds(-1);

	obsPath = L"C:\\Program Files\\obs-studio\\bin\\64bit\\obs64.exe";
	obsDirectory = L"C:\\Program Files\\obs-studio\\bin\\64bit";
	obsFilename = L"obs64.exe";
}

void Options::ParseCommandLine(int argc, char* argv[]) {
	if (argc != 2)
		throw "Invaild arguments";

	const auto command = commands.find(argv[1]);
	if (command != commands.end())
		commandId = command->second;
	else
		throw "Invaild arguments";
}

void Options::ParseConfigFile(std::string configFile) {
	std::wifstream file(configFile);
	if (file.is_open()) {
		std::getline(file, obsPath);

		const size_t position = obsPath.find_last_of(L"\\/");
		obsDirectory = obsPath.substr(0, position);
		obsFilename = obsPath.substr(position + 1);

		file.close();
	}
}

void Options::PrintUsage() const noexcept {
	CHAR buffer[MAX_PATH] = {};
	GetModuleFileNameA(NULL, buffer, MAX_PATH);

	size_t position;
	std::string progname = buffer;
	position = progname.find_last_of("\\/");
	progname = progname.substr(position + 1);
	position = progname.find_last_of(".");
	progname = progname.substr(0, position);

	std::cout << "Usage: " << progname << " <command>" << std::endl;
	for (const auto& line : description)
		std::cout << line << std::endl;
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
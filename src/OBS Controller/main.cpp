#include <iostream>
#include <fstream>
#include <BlackBone/Process/Process.h>
#include <BlackBone/Misc/Utils.h>
#include "constants.h"
#include "macros.h"
using namespace std;
using namespace blackbone;

int main(int argc, char* argv[]) {
	if (argc != 2) {
		cout << "Invaild arguments" << endl;
		return 1;
	}

	commandIds commandId;
	auto command = commands.find(argv[1]);
	if (command != commands.end())
		commandId = command->second;
	else {
		cout << "Invaild arguments" << endl;
		return 1;
	}

	wstring obsPath, obsDirectory, obsFilename;
	wifstream file(Utils::GetExeDirectory() + L"\\obs-studio.txt");
	if (file.is_open()) {
		getline(file, obsPath);
		obsDirectory = Utils::GetParent(obsPath);
		obsFilename = Utils::StripPath(obsPath);
		file.close();
	}
	else {
		cout << "Failed to open the file" << endl;
		return 1;
	}

	Process process;
	NTSTATUS status;
	if (commandId == commandIds::OBS_STUDIO_START) {
		status = process.CREATE(obsPath, obsDirectory.c_str());
		if (!NT_SUCCESS(status)) {
			cout << hex << uppercase;
			cout << "Cannot create process (0x" << status << ")" << endl;
			return 1;
		}
		process.Detach();
		return 0;
	}
	else if (commandId == commandIds::OBS_STUDIO_STOP) {
		status = process.Attach(obsFilename.c_str());
		if (!NT_SUCCESS(status)) {
			cout << hex << uppercase;
			cout << "Cannot attach to process (0x" << status << ")" << endl;
			return 1;
		}
		SetLastNtStatus(STATUS_SUCCESS);
		status = process.Terminate();
		if (!NT_SUCCESS(status)) {
			cout << hex << uppercase;
			cout << "Failed to terminate the process (0x" << status << ")" << endl;
			return 1;
		}
		process.Detach();
		return 0;
	}

	status = process.Attach(obsFilename.c_str());
	if (!NT_SUCCESS(status)) {
		cout << hex << uppercase;
		cout << "Cannot attach to process (0x" << status << ")" << endl;
		return 1;
	}
	switch (commandId) {
	case commandIds::STREAMING_START:
		REMOTE_CALL(process, obs_frontend_streaming_start);
		break;
	case commandIds::STREAMING_STOP:
		REMOTE_CALL(process, obs_frontend_streaming_stop);
		break;

	case commandIds::RECORDING_START:
		REMOTE_CALL(process, obs_frontend_recording_start);
		break;
	case commandIds::RECORDING_STOP:
		REMOTE_CALL(process, obs_frontend_recording_stop);
		break;
	case commandIds::RECORDING_RESUME:
		REMOTE_CALL(process, obs_frontend_recording_pause, false);
		break;
	case commandIds::RECORDING_PAUSE:
		REMOTE_CALL(process, obs_frontend_recording_pause, true);
		break;

	case commandIds::REPLAY_BUFFER_START:
		REMOTE_CALL(process, obs_frontend_replay_buffer_start);
		break;
	case commandIds::REPLAY_BUFFER_STOP:
		REMOTE_CALL(process, obs_frontend_replay_buffer_stop);
		break;
	case commandIds::REPLAY_BUFFER_SAVE:
		REMOTE_CALL(process, obs_frontend_replay_buffer_save);
		break;
	}
	process.Detach();
	return 0;
}
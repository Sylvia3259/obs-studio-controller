#include <iostream>
#include <string>
#include <map>
#include <Windows.h>
#include <BlackBone/Process/Process.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>
#include "constants.h"
#include "macros.h"
using namespace std;
using namespace blackbone;

int main(int argc, char* argv[]) {
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	if (argc != 2) {
		MessageBox(NULL, _T("Invaild arguments"), _T("Error"), MB_ICONERROR);
		return 1;
	}

	commandIds commandId;
	auto command = commands.find(argv[1]);
	if (command != commands.end())
		commandId = command->second;
	else {
		MessageBox(NULL, _T("Invaild arguments"), _T("Error"), MB_ICONERROR);
		return 1;
	}

	Process process;
	auto status = process.Attach(L"obs64.exe");
	if (!NT_SUCCESS(status)) {
		MessageBox(NULL, _T("Cannot attach to process"), _T("Error"), MB_ICONERROR);
		return 1;
	}

	switch (commandId) {
	case commandIds::STREAMING_START:
		REMOTE_CALL(obs_frontend_streaming_start);
		break;

	case commandIds::STREAMING_STOP:
		REMOTE_CALL(obs_frontend_streaming_stop);
		break;

	case commandIds::RECORDING_START:
		REMOTE_CALL(obs_frontend_recording_start);
		break;
	case commandIds::RECORDING_STOP:
		REMOTE_CALL(obs_frontend_recording_stop);
		break;
	case commandIds::RECORDING_RESUME:
		REMOTE_CALL(obs_frontend_recording_pause, false);
		break;
	case commandIds::RECORDING_PAUSE:
		REMOTE_CALL(obs_frontend_recording_pause, true);
		break;

	case commandIds::REPLAY_BUFFER_START:
		REMOTE_CALL(obs_frontend_replay_buffer_start);
		break;
	case commandIds::REPLAY_BUFFER_STOP:
		REMOTE_CALL(obs_frontend_replay_buffer_stop);
		break;
	case commandIds::REPLAY_BUFFER_SAVE:
		REMOTE_CALL(obs_frontend_replay_buffer_save);
		break;
	}

	process.Detach();

	return 0;
}
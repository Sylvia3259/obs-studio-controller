#include <iostream>
#include <string>
#include <map>
#include <Windows.h>
#include <BlackBone/Process/Process.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>
#include "constants.h"
using namespace std;
using namespace blackbone;

int main(int argc, char* argv[]) {
	ShowWindow(GetConsoleWindow(), SW_HIDE);

	if (argc != 2) {
		MessageBox(NULL, _T("Invaild arguments"), _T("Error"), MB_ICONERROR);
		return 1;
	}

	auto command = commands.find(argv[1]);
	int commandId;
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
	case commandIds::STREAMING_START: {
		auto procedure = process.modules().GetExport(L"obs-frontend-api.dll", "obs_frontend_streaming_start");
		RemoteFunction<decltype(obs_frontend_streaming_start)> streaming_start(process, procedure->procAddress);
		streaming_start.Call();
		break;
	}
	case commandIds::STREAMING_STOP: {
		auto procedure = process.modules().GetExport(L"obs-frontend-api.dll", "obs_frontend_streaming_stop");
		RemoteFunction<decltype(obs_frontend_streaming_stop)> streaming_stop(process, procedure->procAddress);
		streaming_stop.Call();
		break;
	}

	case commandIds::RECORDING_START: {
		auto procedure = process.modules().GetExport(L"obs-frontend-api.dll", "obs_frontend_recording_start");
		RemoteFunction<decltype(obs_frontend_recording_start)> recording_start(process, procedure->procAddress);
		recording_start.Call();
		break;
	}
	case commandIds::RECORDING_STOP: {
		auto procedure = process.modules().GetExport(L"obs-frontend-api.dll", "obs_frontend_recording_stop");
		RemoteFunction<decltype(obs_frontend_recording_stop)> recording_stop(process, procedure->procAddress);
		recording_stop.Call();
		break;
	}
	case commandIds::RECORDING_RESUME: {
		auto procedure = process.modules().GetExport(L"obs-frontend-api.dll", "obs_frontend_recording_pause");
		RemoteFunction<decltype(obs_frontend_recording_pause)> recording_pause(process, procedure->procAddress);
		recording_pause.Call(false);
		break;
	}
	case commandIds::RECORDING_PAUSE: {
		auto procedure = process.modules().GetExport(L"obs-frontend-api.dll", "obs_frontend_recording_pause");
		RemoteFunction<decltype(obs_frontend_recording_pause)> recording_pause(process, procedure->procAddress);
		recording_pause.Call(true);
		break;
	}

	case commandIds::REPLAY_BUFFER_START: {
		auto procedure = process.modules().GetExport(L"obs-frontend-api.dll", "obs_frontend_replay_buffer_start");
		RemoteFunction<decltype(obs_frontend_replay_buffer_start)> replay_buffer_start(process, procedure->procAddress);
		replay_buffer_start.Call();
		break;
	}
	case commandIds::REPLAY_BUFFER_STOP: {
		auto procedure = process.modules().GetExport(L"obs-frontend-api.dll", "obs_frontend_replay_buffer_stop");
		RemoteFunction<decltype(obs_frontend_replay_buffer_stop)> replay_buffer_stop(process, procedure->procAddress);
		replay_buffer_stop.Call();
		break;
	}
	case commandIds::REPLAY_BUFFER_SAVE: {
		auto procedure = process.modules().GetExport(L"obs-frontend-api.dll", "obs_frontend_replay_buffer_save");
		RemoteFunction<decltype(obs_frontend_replay_buffer_save)> replay_buffer_save(process, procedure->procAddress);
		replay_buffer_save.Call();
		break;
	}
	}

	process.Detach();

	return 0;
}
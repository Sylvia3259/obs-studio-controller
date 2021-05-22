#pragma once
#include <map>
#include <string>

const enum commandIds {
	OBS_STUDIO_START,
	OBS_STUDIO_STOP,

	STREAMING_START,
	STREAMING_STOP,

	RECORDING_START,
	RECORDING_STOP,
	RECORDING_RESUME,
	RECORDING_PAUSE,

	REPLAY_BUFFER_START,
	REPLAY_BUFFER_STOP,
	REPLAY_BUFFER_SAVE,
};

const std::map<std::string, commandIds> commands = {
	{"--start-obs-studio", commandIds::OBS_STUDIO_START},
	{"--stop-obs-studio", commandIds::OBS_STUDIO_STOP},

	{"--start-streaming", commandIds::STREAMING_START},
	{"--stop-streaming", commandIds::STREAMING_STOP},

	{"--start-recording", commandIds::RECORDING_START},
	{"--stop-recording", commandIds::RECORDING_STOP},
	{"--resume-recording", commandIds::RECORDING_RESUME},
	{"--pause-recording", commandIds::RECORDING_PAUSE},

	{"--start-replay-buffer", commandIds::REPLAY_BUFFER_START},
	{"--stop-replay-buffer", commandIds::REPLAY_BUFFER_STOP},
	{"--save-replay-buffer", commandIds::REPLAY_BUFFER_SAVE},
};
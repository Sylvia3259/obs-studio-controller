#pragma once

void(*obs_frontend_streaming_start)(void);
void(*obs_frontend_streaming_stop)(void);
bool(*obs_frontend_streaming_active)(void);

void(*obs_frontend_recording_start)(void);
void(*obs_frontend_recording_stop)(void);
bool(*obs_frontend_recording_active)(void);
void(*obs_frontend_recording_pause)(bool pause);
bool(*obs_frontend_recording_paused)(void);

void(*obs_frontend_replay_buffer_start)(void);
void(*obs_frontend_replay_buffer_save)(void);
void(*obs_frontend_replay_buffer_stop)(void);
bool(*obs_frontend_replay_buffer_active)(void);

const enum commandIds {
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
	{"--streaming-start", commandIds::STREAMING_START},
	{"--streaming-stop", commandIds::STREAMING_STOP},

	{"--recording-start", commandIds::RECORDING_START},
	{"--recording-stop", commandIds::RECORDING_STOP},
	{"--recording-resume", commandIds::RECORDING_RESUME},
	{"--recording-pause", commandIds::RECORDING_PAUSE},

	{"--replay-buffer-start", commandIds::REPLAY_BUFFER_START},
	{"--replay-buffer-stop", commandIds::REPLAY_BUFFER_STOP},
	{"--replay-buffer-save", commandIds::REPLAY_BUFFER_SAVE},
};
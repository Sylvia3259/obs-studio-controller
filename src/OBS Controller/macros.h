#pragma once

#define REMOTE_CALL(func, ...) {\
	MakeRemoteFunction<decltype(func)>(\
		process, L"obs-frontend-api.dll", #func\
	).Call(__VA_ARGS__);\
}
#pragma once
#include <tchar.h>
#include <Windows.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>

#define ERROR(message) {\
	MessageBox(NULL, _T(message), _T("Error"), MB_ICONERROR);\
}

#define REMOTE_CALL(process, func, ...) {\
	blackbone::MakeRemoteFunction<decltype(func)>(\
		process, L"obs-frontend-api.dll", #func\
	).Call(__VA_ARGS__);\
}
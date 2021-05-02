#pragma once
#include <tchar.h>
#include <Windows.h>
#include <BlackBone/Process/Process.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>

#define ERROR_MESSAGE(message)\
	MessageBox(NULL, _T(message), _T("Error"), MB_ICONERROR)

#define CREATE(path, dir)\
	CreateAndAttach(path, false, true, L"", dir, nullptr)

#define REMOTE_CALL(process, func, ...)\
	blackbone::MakeRemoteFunction<decltype(func)>(\
		process, L"obs-frontend-api.dll", #func\
	).Call(__VA_ARGS__)
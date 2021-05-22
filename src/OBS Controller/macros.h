#pragma once
#include <BlackBone/Process/Process.h>
#include <BlackBone/Process/RPC/RemoteFunction.hpp>
#include <obs-frontend-api.h>

#define CREATE(path, dir)\
	CreateAndAttach(path, false, true, L"", dir, nullptr)

#define REMOTE_CALL(process, func, ...)\
	blackbone::MakeRemoteFunction<decltype(&func)>(\
		process, L"obs-frontend-api.dll", #func\
	).Call(__VA_ARGS__)
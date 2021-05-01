#pragma once
#include <BlackBone/Process/RPC/RemoteFunction.hpp>

#define REMOTE_CALL(func, ...) {\
	MakeRemoteFunction<decltype(func)>(\
		process, L"obs-frontend-api.dll", #func\
	).Call(__VA_ARGS__);\
}
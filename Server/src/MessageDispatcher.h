#pragma once
#include <yojimbo.h>
#include "Messages.h"

class MessageDispatcher {
public:
	MessageDispatcher(yojimbo::Server& server);
	//~MessageDispatcher() = default; deleted bc of reference

	void DispatchMessage(uint32_t clientIndex, yojimbo::Message* message);
private:
	yojimbo::Server& m_Server;
	bool m_bInitialized = false;
};
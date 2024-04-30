#include "MessageDispatcher.h"

MessageDispatcher::MessageDispatcher(yojimbo::Server& server) :
	m_Server(server)
{
	m_bInitialized = true;
}

void MessageDispatcher::DispatchMessage(uint32_t clientIndex, yojimbo::Message* message) {
    
}
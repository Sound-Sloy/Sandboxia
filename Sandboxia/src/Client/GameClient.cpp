#include "GameClient.h"

ClientAdapter::ClientAdapter(GameClient* client) :
	m_GameClient(client)
{
}

yojimbo::MessageFactory* ClientAdapter::CreateMessageFactory(yojimbo::Allocator& allocator) {
    return YOJIMBO_NEW(allocator, GameMessageFactory, allocator);
}
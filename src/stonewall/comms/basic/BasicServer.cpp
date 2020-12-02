#pragma once

#include "BasicServer.h"
#include "BasicConnection.h"

#include "IServerSocket.h"
#include "ISerializer.h"
#include "IParser.h"

#include <unordered_map>
#include <unordered_map>

void AddParser(IParser& Parser)
{
    
}

void AddSerializer(ISerializer& Serializer)
{
    
}


int Bind(string Host, string Port)
{
    return 0;
}

int Listen()
{
    return 0;
}

int AcceptConnection(BasicConnection& OutConnection)
{
    return 0;
}

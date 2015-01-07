#include <RakNet\BitStream.h>

#include "RakClient.h"
#include "HookedRakClient.h"

#include "../CLog.h"

HookedRakClientInterface::HookedRakClientInterface(RakClient * rakclient) : client(rakclient)
{

}

HookedRakClientInterface::~HookedRakClientInterface()
{
	delete client;
}

bool HookedRakClientInterface::Connect( const char* host, unsigned short serverPort, unsigned short clientPort, unsigned int depreciated, int threadSleepTimer )
{
	return client->GetRakClientInterface()->Connect( host, serverPort, clientPort, depreciated, threadSleepTimer );
}

void HookedRakClientInterface::Disconnect( unsigned int blockDuration, unsigned char orderingChannel )
{
	client->GetRakClientInterface()->Disconnect(blockDuration, orderingChannel);
}

void HookedRakClientInterface::InitializeSecurity( const char *privKeyP, const char *privKeyQ )
{
	client->GetRakClientInterface()->InitializeSecurity(privKeyP, privKeyQ);
}

void HookedRakClientInterface::SetPassword( const char *_password )
{
	client->GetRakClientInterface()->SetPassword(_password);
}

bool HookedRakClientInterface::HasPassword( void ) const
{
	return client->GetRakClientInterface()->HasPassword();
}

bool HookedRakClientInterface::Send( const char *data, const int length, int priority, int reliability, char orderingChannel )
{
	return client->GetRakClientInterface()->Send( data, length, (PacketPriority)priority, (PacketReliability)reliability, orderingChannel );
}

bool HookedRakClientInterface::Send( RakNet::BitStream * bitStream, int priority, int reliability, char orderingChannel )
{

	// use this if you wanna log outgoing packets
	/*BYTE packetId;
	bitStream->Read( packetId );
	Log( "< [Packet Send] %d, len: %d", packetId, bitStream->GetNumberOfBytesUsed() );*/

	CLog log = CLog("send.txt");

	BYTE packetId;
	bitStream->Read(packetId);
	log.Write("< [Packet Send] %d, len: %d", packetId, bitStream->GetNumberOfBytesUsed());

	return client->GetRakClientInterface()->Send( bitStream, (PacketPriority)priority, (PacketReliability)reliability, orderingChannel );
}

Packet* HookedRakClientInterface::Receive( void )
{
	return client->GetRakClientInterface()->Receive();
}

void HookedRakClientInterface::DeallocatePacket( Packet *packet )
{
	client->GetRakClientInterface()->DeallocatePacket( packet );
}

void HookedRakClientInterface::PingServer( void )
{
	client->GetRakClientInterface()->PingServer();
}

void HookedRakClientInterface::PingServer( const char* host, unsigned short serverPort, unsigned short clientPort, bool onlyReplyOnAcceptingConnections )
{
	client->GetRakClientInterface()->PingServer( host, serverPort, clientPort, onlyReplyOnAcceptingConnections );
}

int HookedRakClientInterface::GetAveragePing( void )
{
	return client->GetRakClientInterface()->GetAveragePing();
}

int HookedRakClientInterface::GetLastPing( void ) const
{
	return client->GetRakClientInterface()->GetLastPing();
}

int HookedRakClientInterface::GetLowestPing( void ) const
{		
	return client->GetRakClientInterface()->GetLowestPing();
}

int HookedRakClientInterface::GetPlayerPing( const PlayerID playerId )
{
	return client->GetRakClientInterface()->GetPlayerPing( playerId );
}

void HookedRakClientInterface::StartOccasionalPing( void )
{
	client->GetRakClientInterface()->StartOccasionalPing();
}

void HookedRakClientInterface::StopOccasionalPing( void )
{
	client->GetRakClientInterface()->StopOccasionalPing();
}

bool HookedRakClientInterface::IsConnected( void ) const
{
	return client->GetRakClientInterface()->IsConnected();
}

unsigned int HookedRakClientInterface::GetSynchronizedRandomInteger( void ) const
{
	return client->GetRakClientInterface()->GetSynchronizedRandomInteger();
}

bool HookedRakClientInterface::GenerateCompressionLayer( unsigned int inputFrequencyTable[ 256 ], bool inputLayer )
{
	return client->GetRakClientInterface()->GenerateCompressionLayer( inputFrequencyTable, inputLayer );
}

bool HookedRakClientInterface::DeleteCompressionLayer( bool inputLayer )
{
	return client->GetRakClientInterface()->DeleteCompressionLayer( inputLayer );
}

void HookedRakClientInterface::RegisterAsRemoteProcedureCall( int* uniqueID, void ( *functionPointer ) ( RPCParameters *rpcParms ) )
{
	client->GetRakClientInterface()->RegisterAsRemoteProcedureCall( uniqueID, functionPointer );
}

void HookedRakClientInterface::RegisterClassMemberRPC( int* uniqueID, void *functionPointer )
{
	client->GetRakClientInterface()->RegisterClassMemberRPC( uniqueID, functionPointer );
}

void HookedRakClientInterface::UnregisterAsRemoteProcedureCall( int* uniqueID )
{
	client->GetRakClientInterface()->UnregisterAsRemoteProcedureCall( uniqueID );
}

bool HookedRakClientInterface::RPC( int* uniqueID, const char *data, unsigned int bitLength, int priority, int reliability, char orderingChannel, bool shiftTimestamp )
{
	return client->GetRakClientInterface()->RPC(uniqueID, data, bitLength, (PacketPriority)priority, (PacketReliability)reliability, orderingChannel, shiftTimestamp);
}

bool HookedRakClientInterface::RPC( int* uniqueID, RakNet::BitStream *parameters, int priority, int reliability, char orderingChannel, bool shiftTimestamp )
{	
	// use this if you wanna log outgoing RPCs
	/*if ( *uniqueID != RPC_UpdateScoresPingsIPs )
	{
		int len = parameters ? parameters->GetNumberOfBytesUsed() : 0;
		Log( "< [RPC Send] %d, len: %d", *uniqueID, len );
	}*/

	return client->GetRakClientInterface()->RPC(uniqueID, parameters, (PacketPriority)priority, (PacketReliability)reliability, orderingChannel, shiftTimestamp);
}

void HookedRakClientInterface::SetTrackFrequencyTable( bool b )
{
	client->GetRakClientInterface()->SetTrackFrequencyTable( b );
}

bool HookedRakClientInterface::GetSendFrequencyTable( unsigned int outputFrequencyTable[ 256 ] )
{
	return client->GetRakClientInterface()->GetSendFrequencyTable( outputFrequencyTable );
}

float HookedRakClientInterface::GetCompressionRatio( void ) const 
{
	return client->GetRakClientInterface()->GetCompressionRatio();
}

float HookedRakClientInterface::GetDecompressionRatio( void ) const
{
	return client->GetRakClientInterface()->GetDecompressionRatio();
}

void HookedRakClientInterface::AttachPlugin( void *messageHandler )
{
	client->GetRakClientInterface()->AttachPlugin(messageHandler);
}

void HookedRakClientInterface::DetachPlugin( void *messageHandler )
{
	client->GetRakClientInterface()->DetachPlugin(messageHandler);
}

RakNet::BitStream * HookedRakClientInterface::GetStaticServerData(void)
{
	return client->GetRakClientInterface()->GetStaticServerData();
}

void HookedRakClientInterface::SetStaticServerData( const char *data, const int length )
{
	client->GetRakClientInterface()->SetStaticServerData( data, length );
}

RakNet::BitStream * HookedRakClientInterface::GetStaticClientData(const PlayerID playerId)
{	
	return client->GetRakClientInterface()->GetStaticClientData( playerId );
}

void HookedRakClientInterface::SetStaticClientData( const PlayerID playerId, const char *data, const int length )
{
	client->GetRakClientInterface()->SetStaticClientData( playerId, data, length );
}

void HookedRakClientInterface::SendStaticClientDataToServer( void )
{
	client->GetRakClientInterface()->SendStaticClientDataToServer();
}

PlayerID HookedRakClientInterface::GetServerID( void ) const
{
	return client->GetRakClientInterface()->GetServerID();
}

PlayerID HookedRakClientInterface::GetPlayerID( void ) const
{
	return client->GetRakClientInterface()->GetPlayerID();
}

PlayerID HookedRakClientInterface::GetInternalID( void ) const
{
	return client->GetRakClientInterface()->GetInternalID();
}

const char* HookedRakClientInterface::PlayerIDToDottedIP( const PlayerID playerId ) const
{
	return client->GetRakClientInterface()->PlayerIDToDottedIP( playerId );
}

void HookedRakClientInterface::PushBackPacket( Packet *packet, bool pushAtHead )
{
	client->GetRakClientInterface()->PushBackPacket(packet, pushAtHead);
}

void HookedRakClientInterface::SetRouterInterface( void *routerInterface )
{
	client->GetRakClientInterface()->SetRouterInterface(routerInterface);
}
void HookedRakClientInterface::RemoveRouterInterface( void *routerInterface )
{
	client->GetRakClientInterface()->RemoveRouterInterface(routerInterface);
}

void HookedRakClientInterface::SetTimeoutTime( RakNetTime timeMS )
{
	client->GetRakClientInterface()->SetTimeoutTime( timeMS );
}

bool HookedRakClientInterface::SetMTUSize( int size )
{
	return client->GetRakClientInterface()->SetMTUSize( size );
}

int HookedRakClientInterface::GetMTUSize( void ) const
{
	return client->GetRakClientInterface()->GetMTUSize();
}

void HookedRakClientInterface::AllowConnectionResponseIPMigration( bool allow )
{
	client->GetRakClientInterface()->AllowConnectionResponseIPMigration( allow );
}

void HookedRakClientInterface::AdvertiseSystem( const char *host, unsigned short remotePort, const char *data, int dataLength )
{
	client->GetRakClientInterface()->AdvertiseSystem( host, remotePort, data, dataLength );
}

RakNetStatisticsStruct* const HookedRakClientInterface::GetStatistics( void )
{
	return client->GetRakClientInterface()->GetStatistics();
}

void HookedRakClientInterface::ApplyNetworkSimulator( double maxSendBPS, unsigned short minExtraPing, unsigned short extraPingVariance)
{
	client->GetRakClientInterface()->ApplyNetworkSimulator( maxSendBPS, minExtraPing, extraPingVariance );
}

bool HookedRakClientInterface::IsNetworkSimulatorActive( void )
{
	return client->GetRakClientInterface()->IsNetworkSimulatorActive();
}

PlayerIndex HookedRakClientInterface::GetPlayerIndex( void )
{
	return client->GetRakClientInterface()->GetPlayerIndex();
}

void HookedRakClientInterface::Pad( void )
{

}
#pragma once

#include <stdint.h>
#include <string>
#include <vector>

#include "CryCommon/CryNetwork/INetworkService.h"

struct HTTPClientResult;

class ServerBrowser : public IServerBrowser
{
	struct Server
	{
		uint32_t ip = 0;
		uint16_t port = 0;
		std::string master;
	};

	std::vector<Server> m_servers;
	IServerListener *m_pListener = nullptr;

	size_t m_pendingQueryCount = 0;
	size_t m_contract = 0;

	bool OnServerList(HTTPClientResult & result, const std::string & master);
	bool OnServerInfo(HTTPClientResult & result, int serverID);

public:
	ServerBrowser();
	~ServerBrowser();

	// INetworkInterface
	bool IsAvailable() const override;

	// IServerBrowser
	void Start(bool browseLAN) override;
	void SetListener(IServerListener *pListener) override;
	void Stop() override;
	void Update() override;
	void UpdateServerInfo(int id) override;
	void BrowseForServer(unsigned int ip, unsigned short port) override;
	void BrowseForServer(const char *address, unsigned short port) override;
	void SendNatCookie(unsigned int ip, unsigned short port, int cookie) override;
	void CheckDirectConnect(int id, unsigned short port) override;
	int GetServerCount() override;
	int GetPendingQueryCount() override;
};

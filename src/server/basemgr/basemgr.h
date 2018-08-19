
#ifndef KBE_BASEMGR_H
#define KBE_BASEMGR_H
	
// common include	
#include "server/kbemain.h"
#include "server/serverapp.h"
#include "server/idallocate.h"
#include "server/serverconfig.h"
#include "server/forward_messagebuffer.h"
#include "common/timer.h"
#include "network/endpoint.h"
#include "network/udp_packet_receiver.h"
#include "network/common.h"
#include "network/address.h"
//#include "logwatcher.h"
#include "baseapp.h"

//#define NDEBUG
#include <map>	
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#else
// linux include
#endif
	
namespace KBEngine{


class BaseMgrApp:	public ServerApp, 
	public Singleton<BaseMgrApp>
{
public:
	enum TimeOutType
	{
		TIMEOUT_TICK = TIMEOUT_SERVERAPP_MAX + 1
	};

	BaseMgrApp(Network::EventDispatcher& dispatcher,
		Network::NetworkInterface& ninterface, 
		COMPONENT_TYPE componentType,
		COMPONENT_ID componentID);

	~BaseMgrApp();
	
	bool run();
	
	virtual bool initializeWatcher();

	void handleTimeout(TimerHandle handle, void * arg);
	void handleTick();

	/* ��ʼ����ؽӿ� */
	bool initializeBegin();
	bool inInitialize();
	bool initializeEnd();
	void finalise();

	virtual void onChannelDeregister(Network::Channel * pChannel);
	virtual void onAddComponent(const Components::ComponentInfos* pInfos);

	std::map< COMPONENT_ID, Baseapp >& baseapps();

	/** ����ӿ�
	����baseapp�����
	*/
	void updateBaseapp(Network::Channel* pChannel, COMPONENT_ID componentID,
		ENTITY_ID numBases, ENTITY_ID numProxices, float load);
	/** ����ӿ�
	baseappͬ���Լ��ĳ�ʼ����Ϣ
	startGlobalOrder: ȫ������˳�� �������ֲ�ͬ���
	startGroupOrder: ��������˳�� ����������baseapp�еڼ���������
	*/
	void onBaseappInitProgress(Network::Channel* pChannel, MemoryStream& s);


	COMPONENT_ID findFreeBaseapp();
	void updateBestBaseapp();

	virtual bool canShutdown();

	void sendAllocatedBaseappAddr(Network::Channel* pChannel,
		std::string& loginName, std::string& accountName, const std::string& addr, uint16 port);
	//=============================================
	void onRegisterPendingAccount(Network::Channel* pChannel, MemoryStream& s);
	void onRegisterPendingAccountEx(Network::Channel* pChannel, MemoryStream& s);
	void onPendingAccountGetBaseappAddr(Network::Channel* pChannel, MemoryStream& s);

protected:
	TimerHandle													gameTimer_;
	ForwardAnywhere_MessageBuffer								forward_baseapp_messagebuffer_;
	COMPONENT_ID												bestBaseappID_;
	std::map< COMPONENT_ID, Baseapp >							baseapps_;
	KBEUnordered_map< std::string, COMPONENT_ID >				pending_logins_;
	float														baseappsInitProgress_;
};

}

#endif // KBE_BASEMGR_H

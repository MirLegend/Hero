/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2017 KBEngine.

KBEngine is free software: you can redistribute it and/or modify
it under the terms of the GNU Lesser General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

KBEngine is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
GNU Lesser General Public License for more details.
 
You should have received a copy of the GNU Lesser General Public License
along with KBEngine.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "baseapp.h"
#include "proxy.h"
#include "proxy_forwarder.h"
//#include "data_download.h"
#include "network/channel.h"

#include "proto/cb.pb.h"
#include "proto/bmb.pb.h"
#include "../../server/basemgr/basemgr_interface.h"
#include "proto/basedb.pb.h"
#include "../../server/dbmgr/dbmgr_interface.h"

#ifndef CODE_INLINE
#include "proxy.inl"
#endif

namespace KBEngine{
	
//-------------------------------------------------------------------------------------
Proxy::Proxy(ENTITY_ID id):
Base(id, true),
rndUUID_(KBEngine::genUUID64()),
addr_(Network::Address::NONE),
entitiesEnabled_(false),
encryptionKey(),
pProxyForwarder_(NULL),
clientComponentType_(UNKNOWN_CLIENT_COMPONENT_TYPE),
loginDatas_(),
createDatas_()
{
	BaseApp::getSingleton().incProxicesCount();

	pProxyForwarder_ = new ProxyForwarder(this);
}

//-------------------------------------------------------------------------------------
Proxy::~Proxy()
{
	BaseApp::getSingleton().decProxicesCount();
	kick();
	SAFE_RELEASE(pProxyForwarder_);
}

//-------------------------------------------------------------------------------------
void Proxy::kick()
{
	// 如果被销毁频道仍然存活则将其关闭
	Network::Channel* pChannel = BaseApp::getSingleton().networkInterface().findChannel(addr_);
	//if(pChannel && !pChannel->isDestroyed())
	//{
	//	Network::Bundle* pBundle = Network::Bundle::createPoolObject();
	//	(*pBundle).newMessage(ClientInterface::onKicked);
	//	ClientInterface::onKickedArgs1::staticAddToBundle(*pBundle, SERVER_ERR_PROXY_DESTROYED);
	//	//pBundle->send(BaseApp::getSingleton().networkInterface(), pChannel);
	//	this->sendToClient(ClientInterface::onKicked, pBundle);
	//	this->sendToClient();
	//	pChannel->condemn();
	//}
}

//-------------------------------------------------------------------------------------
void Proxy::onEntitiesEnabled(void)
{
	entitiesEnabled_ = true;
}

//-------------------------------------------------------------------------------------
int32 Proxy::onLogOnAttempt(const char* addr, uint32 port, const char* password)
{
	int32 ret = LOG_ON_REJECT;

	return ret;
}

//-------------------------------------------------------------------------------------
void Proxy::onClientDeath(void)
{
	DEBUG_MSG(fmt::format("Proxy::onClientDeath: {}.\n", 
		 this->id()));

	addr(Network::Address::NONE);

	entitiesEnabled_ = false;

	this->onDestroyEntity(true, true);
	this->destroyEntity();

}

//-------------------------------------------------------------------------------------
void Proxy::onGetWitness()
{

}

//-------------------------------------------------------------------------------------
double Proxy::getRoundTripTime() const
{
	Network::Channel* pChannel = Components::getSingleton().pNetworkInterface()->findChannel(addr_);
	if (!pChannel)
	{
		return 0.0;
	}
	return double(pChannel->pEndPoint()->getRTT()) / 1000000.0;
}

void Proxy::InitDatas(const std::string datas)
{
	MemoryStream playerData;
	playerData.append(datas);
	

	playerData >> serverid_;
	playerData.readBlob(nickName_);
	//>> nickName
	playerData >> lastsetnametime_
		>> avatar_
		>> level_
		>> exp_
		>> money_
		>> gem_
		>> arena_point_
		>> crusade_point_
		>> guild_point_
		>> last_midas_time_
		>> today_midas_times_
		>> total_online_time_
		>> tutorialstep_
		>> rechargegem_
		>> facebook_follow_;

	INFO_MSG(fmt::format("Proxy::InitDatas: user={}, dbid={}, entityID={},serverid={}, nickName={}, level={}, exp={}, money={}, rechargegem={}\n",
		accountName(), dbid(), id(), serverid_, nickName_, level_, exp_, money_, rechargegem_));
}

//-------------------------------------------------------------------------------------
double Proxy::getTimeSinceHeardFromClient() const
{
	const Network::Channel* pChanel = Components::getSingleton().pNetworkInterface()->findChannel(addr_);
	return double(timestamp() - pChanel->lastReceivedTime()) / stampsPerSecondD();
}


//-------------------------------------------------------------------------------------
bool Proxy::hasClient() const
{
	return Components::getSingleton().pNetworkInterface()->findChannel(addr_) !=NULL;
}

//-------------------------------------------------------------------------------------
Network::Channel* Proxy::pChannel()
{
	return Components::getSingleton().pNetworkInterface()->findChannel(addr_);
}

//-------------------------------------------------------------------------------------
bool Proxy::pushBundle(Network::Bundle* pBundle)
{
	Network::Channel* pChannel = this->pChannel();
	if(!pChannel)
		return false;

	//pChannel->send(pBundle);

	pBundle->pChannel(pChannel);
	pBundle->finiMessage(true);
	pChannel->pushBundle(pBundle);

	{
		// 如果数据大量阻塞发不出去将会报警
		//AUTO_SCOPED_PROFILE("pushBundleAndSendToClient");
		//pChannel->send(pBundle);
	}

	return true;
}

//-------------------------------------------------------------------------------------
bool Proxy::sendToClient(Network::Bundle* pBundle)
{
	if(pushBundle(pBundle))
		return true;

	ERROR_MSG(fmt::format("Proxy::sendToClient: {} pBundles is NULL, not found channel.\n", id()));
	Network::Bundle::reclaimPoolObject(pBundle);
	return false;
}

//-------------------------------------------------------------------------------------
bool Proxy::sendToClient(bool expectData)
{
	Network::Channel* pChannel = this->pChannel();
	if(!pChannel)
		return false;

	if(expectData)
	{
		if(pChannel->bundles().size() == 0)
		{
			WARNING_MSG("Proxy::sendToClient: no data!\n");
			return false;
		}
	}

	{
		// 如果数据大量阻塞发不出去将会报警

		pChannel->send();
	}

	return true;
}

//-------------------------------------------------------------------------------------
void Proxy::sendUserDownInfo()
{
	Network::Bundle* pBundle = Network::Bundle::createPoolObject();
	pBundle->newMessage(91, 6);
	client_baseserver::login_reply loginreply;
	loginreply.set__result(client_baseserver::result::success);
	loginreply.set__time_zone("china");
	//发送玩家数据
	client_baseserver::user* pUserData = loginreply.mutable__user();
	pUserData->set__userid(id());

	//nameCard
	client_baseserver::name_card* pNameCard = pUserData->mutable__name_card();
	pNameCard->set__name(nickName_);
	pNameCard->set__last_set_name_time(0);
	pNameCard->set__avatar(0);

	pUserData->set__level(level_);
	pUserData->set__exp(exp_);
	pUserData->set__money(money_);
	pUserData->set__rmb(gem_);

	//userpoint
	client_baseserver::user_point* pUserPoint = pUserData->add__points();
	pUserPoint->set__type(client_baseserver::user_point_user_point_type::user_point_user_point_type_arenapoint);
	pUserPoint->set__value(100);

	client_baseserver::user_point* pUserPoint = pUserData->add__points();
	pUserPoint->set__type(client_baseserver::user_point_user_point_type::user_point_user_point_type_crusadepoint);
	pUserPoint->set__value(100);

	client_baseserver::user_point* pUserPoint = pUserData->add__points();
	pUserPoint->set__type(client_baseserver::user_point_user_point_type::user_point_user_point_type_guildpoint);
	pUserPoint->set__value(100);

	//Usermidas
	client_baseserver::usermidas* pUserMidas = pUserData->mutable__usermidas();
	pUserMidas->set__last_change(0);
	pUserMidas->set__today_times(0);

	//vitality
	client_baseserver::vitality* pVitality = pUserData->mutable__vitality();
	pVitality->set__current(100);
	pVitality->set__lastbuy(0);
	pVitality->set__lastchange(0);
	pVitality->set__todaybuy(0);

	//heros info
	//client_baseserver::hero* pHero = pUserData->add__heroes();

	//items info
	//pUserData->add__items(0);

	client_baseserver::skilllevelup* pSkillInfo = pUserData->mutable__skill_level_up();
	pSkillInfo->set__skill_levelup_chance(5);
	pSkillInfo->set__skill_levelup_cd(0);
	pSkillInfo->set__reset_times(0);
	pSkillInfo->set__last_reset_date(0);

	//玩家关卡相关信息
	client_baseserver::userstage* pUserStage = pUserData->mutable__userstage();
	pUserStage->set__elite_reset_time(0);
	pUserStage->set__act_reset_time(0);
	client_baseserver::sweep* psweep = pUserStage->mutable__sweep();
	psweep->set__last_reset_time(0);
	psweep->set__today_free_sweep_times(0);

	//shop info
	//client_baseserver::user_shop* pUserShop = pUserData->add__shop();

	//tutorial info  新手引导的内容
	//pUserData->add__tutorial(0);

	//task info
	//client_baseserver::usertask* pTask = pUserData->add__task();

	//finish job  已经完成的任务链记录
	//pUserData->add__task_finished(0);

	//daily job info  每日任务
	//client_baseserver::dailyjob* pJob = pUserData->add__dailyjob();

	//tavern info 酒馆记录
	//client_baseserver::tavern_record* pTavernRecord = pUserData->add__tavern_record();

	//daily_login
	client_baseserver::daily_login* pDailyLogin = pUserData->mutable__daily_login();
	pDailyLogin->set__frequency(0);
	pDailyLogin->set__last_login_date(0);
	pDailyLogin->set__status(client_baseserver::daily_login::dailylogin_status::daily_login_dailylogin_status_nothing);


	ADDTOBUNDLE((*pBundle), loginreply)
		this->sendToClient(pBundle);
}

//-------------------------------------------------------------------------------------
}

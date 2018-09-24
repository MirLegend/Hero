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
#include "GameModule/HeroManager.h"
#include "GameModule/GameModule.h"
#include "GameModule/TavernManager.h"

//#include "proto/cb.pb.h"
#include "proto/bmb.pb.h"
#include "../../server/basemgr/basemgr_interface.h"
#include "proto/basedb.pb.h"
#include "../../server/dbmgr/dbmgr_interface.h"

#include "proto/cb.pb.h"
//#include "proto/up.pb.h"

#ifndef CODE_INLINE
#include "proxy.inl"
#endif

namespace KBEngine{
	
	SCRIPT_METHOD_DECLARE_BEGIN(Proxy)
		SCRIPT_METHOD_DECLARE("sendDataToClient", pySendDataToClient, METH_VARARGS, 0)
		SCRIPT_METHOD_DECLARE_END()

		SCRIPT_MEMBER_DECLARE_BEGIN(Proxy)
		SCRIPT_MEMBER_DECLARE_END()

		SCRIPT_GETSET_DECLARE_BEGIN(Proxy)
		SCRIPT_GETSET_DECLARE_END()
		BASE_SCRIPT_INIT(Proxy, 0, 0, 0, 0, 0)

//-------------------------------------------------------------------------------------
Proxy::Proxy(ENTITY_ID id):
Base(id, getScriptType(), true),
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

	DEBUG_MSG(fmt::format("Proxy::Proxy()"));
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
	this->setDirty(true);
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

	//gameUserdata_.Clear();

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

	std::string protodata;
	playerData.readBlob(protodata);
	//if (protodata.size()>0)
	//{
	//}
	//else
	//{
	//	//初始化角色
	//	onInitPlayerDatas();
	//}

	PyObject* pData = PyBytes_FromStringAndSize(protodata.c_str(), protodata.size());
	SCRIPT_OBJECT_CALL_ARGS1(this, const_cast<char*>("onInitDatas")
		, const_cast<char*>("O"), pData, true);
	S_RELEASE(pData);

	//INFO_MSG(fmt::format("Proxy::InitDatas: user={}, dbid={}, entityID={},serverid={}, nickName={}, level={}, exp={}, money={}, rechargegem={}, gamedatas_size={}\n",
	//	accountName(), dbid(), id(), serverid_, nickName_, level_, exp_, money_, rechargegem_, gameUserdata_.ByteSize()));
	
	
}

//-------------------------------------------------------------------------------------
double Proxy::getTimeSinceHeardFromClient() const
{
	const Network::Channel* pChanel = Components::getSingleton().pNetworkInterface()->findChannel(addr_);
	return double(timestamp() - pChanel->lastReceivedTime()) / stampsPerSecondD();
}

//-------------------------------------------------------------------------------------
//void Proxy::addPersistentsDataToStream(uint32 flags, MemoryStream* s)
//{
//	MemoryStream& ss = *s;
//	ss << 3;
//	ss.appendBlob(nickName_);
//
//	ss << 6;
//	ss << level_;
//
//	ss << 7;
//	ss << exp_;
//
//	ss << 8;
//	ss << money_;
//
//	ss << 9;
//	ss << gem_;
//
//	ss << 10;
//	ss << arena_point_;
//
//	ss << 11;
//	ss << crusade_point_;
//
//	ss << 19;
//	//ss.appendBlob(gameUserdata_.SerializeAsString());
//}

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
void Proxy::onUserLogonOn()
{
	SCRIPT_OBJECT_CALL_ARGS0(this, const_cast<char*>("onUserLogonOn"), true);
}

//-------------------------------------------------------------------------------------
//void Proxy::sendUserDownInfo()
//{
//	time_t timestap = time(0);
//	Network::Bundle* pBundle = Network::Bundle::createPoolObject();
//	pBundle->newMessage(91, 6);
//	client_baseserver::down_msg downmsg;
//	printf("before downmsg size:%d \n", downmsg.ByteSize());
//	client_baseserver::login_reply& loginreply = *(downmsg.mutable__login_reply());
//	loginreply.set__result(0);
//	loginreply.set__time_zone("china");
//
//	downmsg.set__svr_time(timestap); //服务器当前时间戳
//	//发送玩家数据
//	client_baseserver::user* pUserData = loginreply.mutable__user();
//	//*pUserData = gameUserdata_;
//	//pUserData->set__userid(id());
//
//	//downmsg.set__svr_time(timestap); //服务器当前时间戳
//
//	////nameCard
//	//client_baseserver::name_card* pNameCard = pUserData->mutable__name_card();
//	//pNameCard->set__name(nickName_);
//	//pNameCard->set__last_set_name_time(timestap);
//	//pNameCard->set__avatar(0);
//
//	//pUserData->set__level(level_);
//	//pUserData->set__exp(exp_);
//	//pUserData->set__money(money_);
//	//pUserData->set__rmb(gem_);
//	//pUserData->set__recharge_sum(0);
//
//
//	////userpoint
//	//client_baseserver::user_point* pUserPoint = pUserData->add__points();
//	//pUserPoint->set__type(1);
//	//pUserPoint->set__value(100);
//
//	//client_baseserver::user_point* pUserPoint1 = pUserData->add__points();
//	//pUserPoint1->set__type(2);
//	//pUserPoint1->set__value(100);
//
//	//client_baseserver::user_point* pUserPoint2 = pUserData->add__points();
//	//pUserPoint2->set__type(3);
//	//pUserPoint2->set__value(100);
//
//	////Usermidas
//	//client_baseserver::usermidas* pUserMidas = pUserData->mutable__usermidas();
//	//pUserMidas->set__last_change(timestap);
//	//pUserMidas->set__today_times(0);
//
//	////vitality
//	//client_baseserver::vitality* pVitality = pUserData->mutable__vitality();
//	//pVitality->set__current(100);
//	//pVitality->set__lastbuy(0);
//	//pVitality->set__lastchange(timestap);
//	//pVitality->set__todaybuy(0);
//
//	////heros info
//	////client_baseserver::hero* pHero = pUserData->add__heroes();
//
//	////items info
//	////pUserData->add__items(0);
//
//	//client_baseserver::skilllevelup* pSkillInfo = pUserData->mutable__skill_level_up();
//	//pSkillInfo->set__skill_levelup_chance(5);
//	//pSkillInfo->set__skill_levelup_cd(0);
//	//pSkillInfo->set__reset_times(0);
//	//pSkillInfo->set__last_reset_date(0);
//
//	////玩家关卡相关信息
//	//client_baseserver::userstage* pUserStage = pUserData->mutable__userstage();
//	//pUserStage->set__elite_reset_time(timestap);
//	//pUserStage->set__act_reset_time(timestap);
//	//client_baseserver::sweep* psweep = pUserStage->mutable__sweep();
//	//psweep->set__last_reset_time(timestap);
//	//psweep->set__today_free_sweep_times(0);
//
//	////shop info
//	////client_baseserver::user_shop* pUserShop = pUserData->add__shop();
//
//	////tutorial info  新手引导的内容
//	////pUserData->add__tutorial(0);
//
//	////task info
//	////client_baseserver::usertask* pTask = pUserData->add__task();
//
//	////finish job  已经完成的任务链记录
//	////pUserData->add__task_finished(0);
//
//	////daily job info  每日任务
//	////client_baseserver::dailyjob* pJob = pUserData->add__dailyjob();
//
//	////tavern info 酒馆记录
//	////client_baseserver::tavern_record* pTavernRecord = pUserData->add__tavern_record();
//
//	////daily_login
//	//client_baseserver::daily_login* pDailyLogin = pUserData->mutable__daily_login();
//	//pDailyLogin->set__frequency(0);
//	//pDailyLogin->set__last_login_date(0);
//	//pDailyLogin->set__status(0);
//
//	//client_baseserver::user_guild* pGuid = pUserData->mutable__user_guild();
//	//pGuid->set__id(0);
//	//pGuid->set__name("asdf");
//
//	//client_baseserver::chat* pChat = pUserData->mutable__chat();
//	//pChat->set__world_chat_times(timestap);
//	//pChat->set__last_reset_world_chat_time(timestap);
//
//	printf("downmsg size:%d, %d \n", downmsg.ByteSize(), loginreply.ByteSize());
//	ADDTOBUNDLE((*pBundle), downmsg)
//		this->sendToClient(pBundle);
//}

void Proxy::OnProcessClientUpMsg(MemoryStream& s)
{
	std::string ss;	
	s.readBlob(ss);
	s.done();
	PyObject* pData = PyBytes_FromStringAndSize(ss.data(), ss.size());
	SCRIPT_OBJECT_CALL_ARGS1(this, const_cast<char*>("OnProcessClientUpMsg")
		, const_cast<char*>("O"), pData, true);
	S_RELEASE(pData);
	//client_baseup::up_msg upCmd;
	//client_baseserver::down_msg downmsg;
	//PARSEBUNDLE(s, upCmd)

	//bool breply = false;

	///////////////////32 新手引导/////////////////////
	//if (upCmd.has__tutorial()) //新手引导
	//{
	//	breply |= this->OnTutorial(upCmd._tutorial(), downmsg);
	//}

	///////////////////50 魂匣/////////////////////
	//if (upCmd.has__ask_magicsoul())
	//{
	//	breply |= this->OnAskMagicsoul(upCmd._ask_magicsoul(), downmsg);
	//}

	///////////////////26 tavern/////////////////////
	//if (upCmd.has__tavern_draw())
	//{
	//	breply |= this->OnTavernDraw(upCmd._tavern_draw(), downmsg);
	//}

	//if (breply)
	//{
	//	time_t timestap = time(0);
	//	Network::Bundle* pBundle = Network::Bundle::createPoolObject();
	//	pBundle->newMessage(91, 6);
	//	downmsg.set__svr_time(timestap); //服务器当前时间戳
	//	ADDTOBUNDLE((*pBundle), downmsg)
	//		this->sendToClient(pBundle);
	//}
}

void Proxy::SendDataToClient(uint8 mainCmd, uint8 subCmd, const char* senbuff, uint32 sendSize)
{
	Network::Bundle* pBundle = Network::Bundle::createPoolObject();
	pBundle->newMessage(91, 6);
	pBundle->appendBlob(senbuff, sendSize);
	this->sendToClient(pBundle);
}

PyObject* Proxy::__py_pySendDataToClient(PyObject* self, PyObject* args, PyObject* kwds)
{
	PY_METHOD_ARG_uint8_ARG arg1;
	PY_METHOD_ARG_uint8_ARG arg2;
	PY_METHOD_ARG_PyObject_ptr_ARG arg3;

	const uint8 argsSize = 3;
	uint16 currargsSize = (uint16)PyTuple_Size(args);
	ThisClass* pobj = static_cast<ThisClass*>(self);

	if (currargsSize == argsSize)
	{
		if (!PyArg_ParseTuple(args, PY_METHOD_ARG_uint8_PYARGTYPE "|"
			PY_METHOD_ARG_uint8_PYARGTYPE "|"
			PY_METHOD_ARG_PyObject_ptr_PYARGTYPE,
			&arg1, &arg2, &arg3))
		{
			PyErr_Format(PyExc_TypeError, "%s: args(%s, %s, %s) is error!\n", __FUNCTION__, "uint8", "uint8", "PyObject_ptr");
			PyErr_PrintEx(0);
			S_Return;
		}
		if (!PyBytes_Check(arg3))
		{
			PyErr_Format(PyExc_TypeError, "PyMemoryStream::append: val is not BLOB!");
			PyErr_PrintEx(0);
			S_Return;
		}
		char *buffer;
		Py_ssize_t length;

		if (PyBytes_AsStringAndSize(arg3, &buffer, &length) < 0)
		{
			SCRIPT_ERROR_CHECK();
			S_Return;
		}
		pobj->SendDataToClient(arg1, arg2, buffer, length);

	}
	else
	{
		PyErr_Format(PyExc_AssertionError, "%s: args require %d args(%s, %s, %s), gived %d! is script[%s].\n",
			__FUNCTION__, argsSize, "uint8", "uint8", "PyObject_ptr", currargsSize, pobj->scriptName());

		PyErr_PrintEx(0);

		S_Return;
	}
	S_Return;
}

//更新新手引导消息
//bool Proxy::OnTutorial(const client_baseup::tutorial& tutorialmsg, client_baseserver::down_msg& downmsg)
//{
//	DEBUG_MSG(fmt::format("OnTutorial id:{}", this->id()));
//
//	/*for (size_t i = 0; i < tutorialmsg._record_size(); i++)
//	{
//	printf("OnTutorial i:%d, v:%d  \n", i, tutorialmsg._record(i));
//	}*/
//	//gameUserdata_._tutorial.CopyFrom(tutorialmsg);
//	//client_baseserver::tutorial_reply* preply = downmsg.mutable__tutorial_reply();
//	//preply->set__result(0);
//	return true;
//}

//请求魔法召唤消息
//bool Proxy::OnAskMagicsoul(const client_baseup::ask_magicsoul& ask_magicsoulmsg, client_baseserver::down_msg& downmsg)
//{
//	DEBUG_MSG(fmt::format("OnAskMagicsoul id:{}", this->id()));
//
//	/*for (size_t i = 0; i < tutorialmsg._record_size(); i++)
//	{
//	printf("OnTutorial i:%d, v:%d  \n", i, tutorialmsg._record(i));
//	}*/
//
//	//client_baseserver::ask_magicsoul_reply* preply = downmsg.mutable__ask_magicsoul_reply();
//	//preply->set__result(0);
//	return false;
//}

//抽奖消息
//bool Proxy::OnTavernDraw(const client_baseup::tavern_draw& tavern_drawmsg, client_baseserver::down_msg& downmsg)
//{
//	DEBUG_MSG(fmt::format("OnTavernDraw id:{}", this->id()));
//	uint32 boxtype = tavern_drawmsg._box_type();
//	uint32 drawtype = tavern_drawmsg._draw_type();
//	const GlobalParam& globalparam = GameModule::getSingleton().getGlobalParam();
//	int cost = 0;
//	int costtype = coin;
//	int cdtime = 0;
//	std::string drawkey = "Bronze";
//
//	if (green == boxtype)
//	{
//		cdtime = globalparam.tavern_bronze_cd;
//		costtype = coin;
//		std::string drawkey = "Bronze";
//	}
//	else if (purple == boxtype)
//	{
//		cdtime = globalparam.tavern_magic_cd;
//		costtype = gems;
//		std::string drawkey = "Gold";
//	}
//	else
//	{
//		return false;
//	}
//
//	return false;
//}

void Proxy::onInitPlayerDatas()
{
	//time_t timestap = time(0);
	//client_baseserver::user* pUserData  ;//=&gameUserdata_;
	////gameUserdata_.set__userid(id());
	////nameCard
	//client_baseserver::name_card* pNameCard = pUserData->mutable__name_card();
	//pNameCard->set__name(nickName_);
	//pNameCard->set__last_set_name_time(timestap);
	//pNameCard->set__avatar(1); //玩家头像

	//pUserData->set__level(level_);
	//pUserData->set__recharge_sum(0);
	//pUserData->set__exp(exp_);
	//pUserData->set__money(money_);
	//pUserData->set__rmb(gem_);
	//
	////vitality 体力
	//client_baseserver::vitality* pVitality = pUserData->mutable__vitality();
	//pVitality->set__current(100);
	//pVitality->set__lastbuy(0);
	//pVitality->set__lastchange(timestap);
	//pVitality->set__todaybuy(0);

	////heros info  送个船长
	////client_baseserver::hero* pHero = pUserData->add__heroes();
	//this->addPlayerHero(1, 1);

	////物品背包
	////pUserData->add__items(0);

	////技能升级信息
	//client_baseserver::skilllevelup* pSkillInfo = pUserData->mutable__skill_level_up();
	//pSkillInfo->set__skill_levelup_chance(5);
	//pSkillInfo->set__skill_levelup_cd(timestap);
	//pSkillInfo->set__reset_times(0);
	//pSkillInfo->set__last_reset_date(timestap);

	////玩家关卡相关信息
	//client_baseserver::userstage* pUserStage = pUserData->mutable__userstage();
	//pUserStage->set__elite_reset_time(0);
	//pUserStage->set__act_reset_time(timestap);
	//client_baseserver::sweep* psweep = pUserStage->mutable__sweep();
	//psweep->set__last_reset_time(timestap);
	//psweep->set__today_free_sweep_times(0);

	////商店信息
	////client_baseserver::user_shop* pUserShop = pUserData->add__shop();

	////新手引导的内容
	//for (int i = 0; i < 95; i++)
	//{
	//	pUserData->add__tutorial(0);
	//}

	////任务记录
	////client_baseserver::usertask* pTask = pUserData->add__task();

	////已经完成的任务链记录
	////pUserData->add__task_finished(0);

	////每日任务
	////client_baseserver::dailyjob* pJob = pUserData->add__dailyjob();

	////酒馆记录
	////client_baseserver::tavern_record* pTavernRecord = pUserData->add__tavern_record();

	////点金手
	//client_baseserver::usermidas* pUserMidas = pUserData->mutable__usermidas();
	//pUserMidas->set__last_change(timestap);
	//pUserMidas->set__today_times(0);

	////每日登陆
	//client_baseserver::daily_login* pDailyLogin = pUserData->mutable__daily_login();
	//pDailyLogin->set__frequency(1);
	//pDailyLogin->set__last_login_date(timestap);
	//pDailyLogin->set__status(3);

	////玩家消耗点数
	////enum user_point_type {
	////    arenapoint      = 1;        // pvp点数
	////    crusadepoint    = 2;        // 远征点数
	////    guildpoint      = 3;        // 公会币
	////}
	//client_baseserver::user_point* pUserPoint = pUserData->add__points();
	//pUserPoint->set__type(1);
	//pUserPoint->set__value(100);

	//client_baseserver::user_point* pUserPoint1 = pUserData->add__points();
	//pUserPoint1->set__type(2);
	//pUserPoint1->set__value(100);

	//client_baseserver::user_point* pUserPoint2 = pUserData->add__points();
	//pUserPoint2->set__type(3);
	//pUserPoint2->set__value(100);

	////用户公会数据
	//client_baseserver::user_guild* pGuid = pUserData->mutable__user_guild();
	//pGuid->set__id(0);
	//pGuid->set__name("asdf");

	//client_baseserver::chat* pChat = pUserData->mutable__chat();
	//pChat->set__world_chat_times(0);
	//pChat->set__last_reset_world_chat_time(timestap);

	////体力值相关数据
	//client_baseserver::vitality* pvitality = pUserData->mutable__shadow_runes();
	//pvitality->set__current(200);
	//pvitality->set__lastchange(timestap);
	//pvitality->set__todaybuy(0);
	//pvitality->set__lastbuy(0);
}

bool Proxy::addPlayerHero(uint32 heroId, uint32 reason)
{
	//HeroConfig* pHeroConfig = HeroManager::getSingleton().getHeroConfig(heroId);
	//if (!pHeroConfig)
	//{
	//	return false;
	//}
	//for (int i = 0; i < gameUserdata_._heroes_size();i++)
	//{
	//	const client_baseserver::hero& heroData = gameUserdata_._heroes(i);
	//	if (heroData._tid() == heroId) //已经有相同的英雄了
	//	{
	//		return false;
	//	}
	//}
	//client_baseserver::hero* heroData = gameUserdata_.add__heroes();
	//if (!heroData)
	//{
	//	return false;
	//}
	//heroData->set__tid(heroId);
	//heroData->set__level(1);
	//heroData->set__exp(0);
	//heroData->set__rank(pHeroConfig->InitialRank);
	//heroData->set__stars(pHeroConfig->InitialStars);
	//heroData->set__state(hero_status_idle);

	//for (int i = 0; i < 4; i++)
	//{
	//	const HeroSkillConfig& skillcfg = pHeroConfig->skillConfig[i];
	//	heroData->add__skill_levels(skillcfg.InitLevel);
	//}

	////装备曹初始化
	//for (int i = 0; i < 6; i++)
	//{
	//	client_baseserver::hero_equip* pheroEquip = heroData->add__items();
	//	pheroEquip->set__index(i);
	//	pheroEquip->set__item_id(0);
	//	pheroEquip->set__exp(0);
	//}

	//heroData->set__gs(100); //英雄战力

	return true;
}

//-------------------------------------------------------------------------------------
}

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

#include "proto/bmb.pb.h"
#include "../../server/basemgr/basemgr_interface.h"
#include "proto/basedb.pb.h"
#include "../../server/dbmgr/dbmgr_interface.h"

#include "proto/cb.pb.h"

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

void Proxy::OnProcessClientUpMsg(MemoryStream& s)
{
	std::string ss;	
	s.readBlob(ss);
	s.done();
	PyObject* pData = PyBytes_FromStringAndSize(ss.data(), ss.size());
	SCRIPT_OBJECT_CALL_ARGS1(this, const_cast<char*>("OnProcessClientUpMsg")
		, const_cast<char*>("O"), pData, true);
	S_RELEASE(pData);
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

void Proxy::onInitPlayerDatas()
{
}
//-------------------------------------------------------------------------------------
}

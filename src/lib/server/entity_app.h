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

#ifndef KBE_ENTITY_APP_H
#define KBE_ENTITY_APP_H

// common include
#include "pyhal/py_gc.h"
#include "pyhal/script.h"
#include "pyhal/pyprofile.h"
#include "pyhal/pyprofile_handler.h"
#include "common/common.h"
#include "math/math.h"
#include "common/timer.h"
#include "common/smartpointer.h"
#include "helper/debug_helper.h"
#include "helper/script_loglevel.h"
#include "helper/profile.h"
#include "server/kbemain.h"	
#include "entities.h"
//#include "server/script_timers.h"
#include "server/idallocate.h"
#include "server/serverconfig.h"
//#include "server/globaldata_client.h"
#include "server/globaldata_server.h"
//#include "server/callbackmgr.h"	
#include "network/message_handler.h"
#include "resmgr/resmgr.h"
//#include "helper/console_helper.h"
#include "server/serverapp.h"

#if KBE_PLATFORM == PLATFORM_WIN32
#pragma warning (disable : 4996)
#endif

	
namespace KBEngine{

template<class E>
class EntityApp : public ServerApp
{
public:
	enum TimeOutType
	{
		TIMEOUT_GAME_TICK = TIMEOUT_SERVERAPP_MAX + 1,
		TIMEOUT_ENTITYAPP_MAX
	};

public:
	EntityApp(Network::EventDispatcher& dispatcher, 
		Network::NetworkInterface& ninterface, 
		COMPONENT_TYPE componentType,
		COMPONENT_ID componentID);

	~EntityApp();
	
	/** 
		��ش���ӿ� 
	*/
	virtual void handleTimeout(TimerHandle handle, void * arg);
	virtual void handleGameTick();

	/**
		ͨ��entityIDѰ�ҵ���Ӧ��ʵ�� 
	*/
	E* findEntity(ENTITY_ID entityID);

	/** 
		ͨ��entityID����һ��entity 
	*/
	virtual bool destroyEntity(ENTITY_ID entityID, bool callScript);

	KBEngine::script::Script& getScript(){ return script_; }
	PyObjectPtr getEntryScript(){ return entryScript_; }

	void registerScript(PyTypeObject*);
	int registerPyObjectToScript(const char* attrName, PyObject* pyObj);
	int unregisterPyObjectToScript(const char* attrName);

	bool installPyScript();
	virtual bool installPyModules();
	virtual void onInstallPyModules() {};
	virtual bool uninstallPyModules();
	bool uninstallPyScript();
	virtual bool installEntityDef();
	bool loadUnitScriptType(const char* unitName);

	PyTypeObject* findUnitScriptType(const char* unitName);
	
	virtual bool initializeWatcher();

	virtual void finalise();
	virtual bool inInitialize();
	virtual bool initialize();

	virtual void onSignalled(int sigNum);
	
	Entities<E>* pEntities() const{ return pEntities_; }
	ArraySize entitiesSize() const { return (ArraySize)pEntities_->size(); }

	EntityIDClient& idClient(){ return idClient_; }

	/**
		����һ��entity 
	*/
	E* createEntity(const char* entityType, ENTITY_ID eid = 0, bool isInitializeScript = true);

	virtual E* onCreateEntity(PyObject* pyEntity, ENTITY_ID eid);

	/** ����ӿ�
		�������һ��ENTITY_ID�εĻص�
	*/
	void onReqAllocEntityID(Network::Channel* pChannel, ENTITY_ID startID, ENTITY_ID endID);

	/** ����ӿ�
		dbmgr���ͳ�ʼ��Ϣ
		startID: ��ʼ����ENTITY_ID ����ʼλ��
		endID: ��ʼ����ENTITY_ID �ν���λ��
		startGlobalOrder: ȫ������˳�� �������ֲ�ͬ���
		startGroupOrder: ��������˳�� ����������baseapp�еڼ���������
	*/
	void onDbmgrInitCompleted(Network::Channel* pChannel, 
		GAME_TIME gametime, ENTITY_ID startID, ENTITY_ID endID, COMPONENT_ORDER startGlobalOrder, 
		COMPONENT_ORDER startGroupOrder, const std::string& digest);

	/** ����ӿ�
		dbmgr�㲥global���ݵĸı�
	*/
	void onBroadcastGlobalDataChanged(Network::Channel* pChannel, KBEngine::MemoryStream& s);

	/**
	����ű�assert�ײ�
	*/
	static PyObject* __py_assert(PyObject* self, PyObject* args);

	/**
	���ýű��������ǰ׺
	*/
	static PyObject* __py_setScriptLogType(PyObject* self, PyObject* args);

	/**
	ͨ�����·����ȡ��Դ��ȫ·��
	*/
	static PyObject* __py_getResFullPath(PyObject* self, PyObject* args);

	/**
	ͨ�����·���ж���Դ�Ƿ����
	*/
	static PyObject* __py_hasRes(PyObject* self, PyObject* args);

	/**
	open�ļ�
	*/
	static PyObject* __py_kbeOpen(PyObject* self, PyObject* args);

	/**
	�г�Ŀ¼�������ļ�
	*/
	static PyObject* __py_listPathRes(PyObject* self, PyObject* args);

	/**
	ƥ�����·�����ȫ·��
	*/
	static PyObject* __py_matchPath(PyObject* self, PyObject* args);

	/**
		���¸������
	*/
	int tickPassedPercent(uint64 curr = timestamp());
	float getLoad() const { return load_; }
	void updateLoad();
	virtual void onUpdateLoad(){}
	virtual void calcLoad(float spareTime);
	uint64 checkTickPeriod();

protected:
	typedef std::map<std::string, PyTypeObject*>::iterator  SCRIPTUNITMAPITER;
	KBEngine::script::Script								script_;
	std::vector<PyTypeObject*>								scriptBaseTypes_;
	std::map<std::string, PyTypeObject*>					scriptUnitTypes_;

	PyObjectPtr												entryScript_;

	EntityIDClient											idClient_;

	// �洢���е�entity������
	Entities<E>*											pEntities_;

	TimerHandle												gameTimer_;

	// globalData
	//GlobalDataClient*										pGlobalData_;

	//PY_CALLBACKMGR											pyCallbackMgr_;

	uint64													lastTimestamp_;

	// ���̵�ǰ����
	float													load_;
};


template<class E>
EntityApp<E>::EntityApp(Network::EventDispatcher& dispatcher, 
					 Network::NetworkInterface& ninterface, 
					 COMPONENT_TYPE componentType,
					 COMPONENT_ID componentID):
ServerApp(dispatcher, ninterface, componentType, componentID),
script_(),
scriptBaseTypes_(),
entryScript_(),
idClient_(),
pEntities_(NULL),
gameTimer_(),
//pGlobalData_(NULL),
lastTimestamp_(timestamp()),
load_(0.f)
{
	idClient_.pApp(this);
}

template<class E>
EntityApp<E>::~EntityApp()
{
	SAFE_RELEASE(pEntities_);
}

template<class E>
bool EntityApp<E>::inInitialize()
{
	if (!installPyScript())
		return false;

	if (!installPyModules())
		return false;

	return installEntityDef();
}

template<class E>
bool EntityApp<E>::initialize()
{
	bool ret = ServerApp::initialize();
	if(ret)
	{
		gameTimer_ = this->dispatcher().addTimer(1000000 / g_kbeSrvConfig.gameUpdateHertz(), this,
								reinterpret_cast<void *>(TIMEOUT_GAME_TICK));
	}

	lastTimestamp_ = timestamp();
	return ret;
}

template<class E>
bool EntityApp<E>::initializeWatcher()
{
	//WATCH_OBJECT("entitiesSize", this, &EntityApp<E>::entitiesSize);
	return true;// ServerApp::initializeWatcher();
}

template<class E>
void EntityApp<E>::finalise(void)
{
	gameTimer_.cancel();

	//WATCH_FINALIZE;

	if(pEntities_)
		pEntities_->finalise();

	uninstallPyScript();

	ServerApp::finalise();
}

template<class E>
bool EntityApp<E>::installEntityDef()
{
	return true;
}


template<class E>
int EntityApp<E>::registerPyObjectToScript(const char* attrName, PyObject* pyObj)
{
	return script_.registerToModule(attrName, pyObj);
}

template<class E>
int EntityApp<E>::unregisterPyObjectToScript(const char* attrName)
{
	return script_.unregisterToModule(attrName);
}

template<class E>
bool EntityApp<E>::loadUnitScriptType(const char* unitName)
{
	PyObject *pyEntryScriptFileName = PyUnicode_FromString(unitName);
	PyObject *unitScriptModule = PyImport_Import(pyEntryScriptFileName);

	if (PyErr_Occurred())
	{
		INFO_MSG(fmt::format("EntityApp::installPyModules: importing scripts/{}.py...\n", unitName));

		PyErr_PrintEx(0);
	}

	S_RELEASE(pyEntryScriptFileName);
	if (unitScriptModule == NULL)
	{
		ERROR_MSG(fmt::format("EntityDef::loadUnitScriptType: Could not find ComponentClass[{}.py]\n",
			unitName));
		return false;
	}
	PyObject* pyClass =
		PyObject_GetAttrString(unitScriptModule, const_cast<char *>(unitName));

	S_RELEASE(unitScriptModule);

	if (pyClass == NULL)
	{
		ERROR_MSG(fmt::format("EntityDef::loadUnitScriptType: Could not find Class[{}]\n",
			unitName));
		return false;
	}
	else
	{
		DEBUG_MSG(fmt::format("EntityDef::loadUnitScriptType: ComponentClass[{}.py], Successfully!!!\n",
			unitName));
		scriptUnitTypes_[unitName] = (PyTypeObject*)pyClass;
	}
	
	return true;
}

template<class E>
PyTypeObject* EntityApp<E>::findUnitScriptType(const char* unitName)
{
	SCRIPTUNITMAPITER it = scriptUnitTypes_.find(unitName);
	if (it != scriptUnitTypes_.end())
	{
		return it->second;
	}
	return NULL;
}

template<class E>
bool EntityApp<E>::installPyScript()
{
	if (Resmgr::getSingleton().respaths().size() <= 0 ||
		Resmgr::getSingleton().getPySysResPath().size() == 0)
	{
		KBE_ASSERT(false && "EntityApp::installPyScript: KBE_RES_PATH is error!\n");
		return false;
	}

	std::wstring user_scripts_path = L"";
	wchar_t* tbuf = KBEngine::strutil::char2wchar(const_cast<char*>(Resmgr::getSingleton().getPySysResPath().c_str()));
	if (tbuf != NULL)
	{
		user_scripts_path += tbuf;
		user_scripts_path += L"scripts/";
		free(tbuf);
	}
	else
	{
		KBE_ASSERT(false && "EntityApp::installPyScript: KBE_RES_PATH error[char2wchar]!\n");
		return false;
	}

	std::wstring pyPaths = user_scripts_path + L"common;";
	pyPaths += user_scripts_path + L"data;";

	switch (componentType_)
	{
	case BASEAPP_TYPE:
		pyPaths += user_scripts_path + L"server_common;";
		pyPaths += user_scripts_path + L"base;";
		pyPaths += user_scripts_path + L"base/interfaces;";
		break;
	case CELLAPP_TYPE:
		pyPaths += user_scripts_path + L"server_common;";
		pyPaths += user_scripts_path + L"cell;";
		pyPaths += user_scripts_path + L"cell/interfaces;";
		break;
	case DBMGR_TYPE:
		pyPaths += user_scripts_path + L"server_common;";
		pyPaths += user_scripts_path + L"db;";
		break;
	default:
		pyPaths += user_scripts_path + L"client;";
		pyPaths += user_scripts_path + L"client/interfaces;";
		pyPaths += user_scripts_path + L"client/components;";
		break;
	};

	std::string kbe_res_path = Resmgr::getSingleton().getPySysResPath();
	kbe_res_path += "scripts/pyCommonLib";

	tbuf = KBEngine::strutil::char2wchar(const_cast<char*>(kbe_res_path.c_str()));
	bool ret = getScript().install(tbuf, pyPaths, "KBEngine", componentType_);
	free(tbuf);
	return ret;
}

template<class E>
void EntityApp<E>::registerScript(PyTypeObject* pto)
{
	scriptBaseTypes_.push_back(pto);
}

template<class E>
bool EntityApp<E>::uninstallPyScript()
{
	return uninstallPyModules() && getScript().uninstall();
}

template<class E>
bool EntityApp<E>::installPyModules()
{
	Entities<E>::installScript(NULL);
	EntityGarbages<E>::installScript(NULL);
	//Entity::installScript(g_script.getModule());

	pEntities_ = new Entities<E>();
	registerPyObjectToScript("entities", pEntities_);

	// ���pywatcher֧��
	//if (!initializePyWatcher(&this->getScript()))
	//	return false;

	//// ���globalData, globalBases֧��
	//pGlobalData_ = new GlobalDataClient(DBMGR_TYPE, GlobalDataServer::GLOBAL_DATA);
	//registerPyObjectToScript("globalData", pGlobalData_);

	// ע�ᴴ��entity�ķ�����py
	// ����assert�ײ㣬���ڵ��Խű�ĳ��ʱ��ʱ�ײ�״̬
	//APPEND_SCRIPT_MODULE_METHOD(getScript().getModule(), kbassert, __py_assert, METH_VARARGS, 0);

	//// ��ű�ע��app����״̬
	//APPEND_SCRIPT_MODULE_METHOD(getScript().getModule(), publish, __py_getAppPublish, METH_VARARGS, 0);

	// ע�����ýű��������
	//APPEND_SCRIPT_MODULE_METHOD(getScript().getModule(), scriptLogType, __py_setScriptLogType, METH_VARARGS, 0);

	// �����Դȫ·��
	//APPEND_SCRIPT_MODULE_METHOD(getScript().getModule(), getResFullPath, __py_getResFullPath, METH_VARARGS, 0);

	// �Ƿ����ĳ����Դ
	//APPEND_SCRIPT_MODULE_METHOD(getScript().getModule(), hasRes, __py_hasRes, METH_VARARGS, 0);

	// ��һ���ļ�
	//APPEND_SCRIPT_MODULE_METHOD(getScript().getModule(), open, __py_kbeOpen, METH_VARARGS, 0);

	// �г�Ŀ¼�������ļ�
	//APPEND_SCRIPT_MODULE_METHOD(getScript().getModule(), listPathRes, __py_listPathRes, METH_VARARGS, 0);

	// ƥ�����·�����ȫ·��
	//APPEND_SCRIPT_MODULE_METHOD(getScript().getModule(), matchPath, __py_matchPath, METH_VARARGS, 0);

	//// ��ȡwatcherֵ
	//APPEND_SCRIPT_MODULE_METHOD(getScript().getModule(), getWatcher, __py_getWatcher, METH_VARARGS, 0);

	//// ��ȡwatcherĿ¼
	//APPEND_SCRIPT_MODULE_METHOD(getScript().getModule(), getWatcherDir, __py_getWatcherDir, METH_VARARGS, 0);

	// debug׷��kbe��װ��py�������
	//APPEND_SCRIPT_MODULE_METHOD(getScript().getModule(), debugTracing, script::PyGC::__py_debugTracing, METH_VARARGS, 0);

	if (PyModule_AddIntConstant(this->getScript().getModule(), "LOG_TYPE_NORMAL", log4cxx::ScriptLevel::SCRIPT_INT))
	{
		ERROR_MSG("EntityApp::installPyModules: Unable to set KBEngine.LOG_TYPE_NORMAL.\n");
	}

	if (PyModule_AddIntConstant(this->getScript().getModule(), "LOG_TYPE_INFO", log4cxx::ScriptLevel::SCRIPT_INFO))
	{
		ERROR_MSG("EntityApp::installPyModules: Unable to set KBEngine.LOG_TYPE_INFO.\n");
	}

	if (PyModule_AddIntConstant(this->getScript().getModule(), "LOG_TYPE_ERR", log4cxx::ScriptLevel::SCRIPT_ERR))
	{
		ERROR_MSG("EntityApp::installPyModules: Unable to set KBEngine.LOG_TYPE_ERR.\n");
	}

	if (PyModule_AddIntConstant(this->getScript().getModule(), "LOG_TYPE_DBG", log4cxx::ScriptLevel::SCRIPT_DBG))
	{
		ERROR_MSG("EntityApp::installPyModules: Unable to set KBEngine.LOG_TYPE_DBG.\n");
	}

	if (PyModule_AddIntConstant(this->getScript().getModule(), "LOG_TYPE_WAR", log4cxx::ScriptLevel::SCRIPT_WAR))
	{
		ERROR_MSG("EntityApp::installPyModules: Unable to set KBEngine.LOG_TYPE_WAR.\n");
	}

	if (PyModule_AddIntConstant(this->getScript().getModule(), "NEXT_ONLY", KBE_NEXT_ONLY))
	{
		ERROR_MSG("EntityApp::installPyModules: Unable to set KBEngine.NEXT_ONLY.\n");
	}

	for (int i = 0; i < SERVER_ERR_MAX; i++)
	{
		if (PyModule_AddIntConstant(getScript().getModule(), SERVER_ERR_STR[i], i))
		{
			ERROR_MSG(fmt::format("EntityApp::installPyModules: Unable to set KBEngine.{}.\n", SERVER_ERR_STR[i]));
		}
	}

	// ��װ���ģ��
	std::string entryScriptFileName = "";
	if (componentType() == BASEAPP_TYPE)
	{
		ENGINE_COMPONENT_INFO& info = g_kbeSrvConfig.getBaseApp();
		entryScriptFileName = "heromain"/*info.entryScriptFile*/;
	}
	else if (componentType() == CELLAPP_TYPE)
	{
		ENGINE_COMPONENT_INFO& info = g_kbeSrvConfig.getCellApp();
		entryScriptFileName = "heromain";// info.entryScriptFile;
	}

	if (entryScriptFileName.size() > 0)
	{
		PyObject *pyEntryScriptFileName = PyUnicode_FromString(entryScriptFileName.c_str());
		entryScript_ = PyImport_Import(pyEntryScriptFileName);

		if (PyErr_Occurred())
		{
			INFO_MSG(fmt::format("EntityApp::installPyModules: importing scripts/{}{}.py...\n",
				(componentType() == BASEAPP_TYPE ? "base/" : "cell/"),
				entryScriptFileName));

			PyErr_PrintEx(0);
		}

		S_RELEASE(pyEntryScriptFileName);

		if (entryScript_.get() == NULL)
		{
			ERROR_MSG(fmt::format("entryScript Import Error!"));
			return false;
		}
	}

	onInstallPyModules();
	return true;
}

template<class E>
bool EntityApp<E>::uninstallPyModules()
{
	// script::PyGC::set_debug(script::PyGC::DEBUG_STATS|script::PyGC::DEBUG_LEAK);
	// script::PyGC::collect();
	unregisterPyObjectToScript("globalData");
	//S_RELEASE(pGlobalData_);

	S_RELEASE(pEntities_);
	unregisterPyObjectToScript("entities");

	Entities<E>::uninstallScript();
	EntityGarbages<E>::uninstallScript();
	//Entity::uninstallScript();
	//EntityDef::uninstallScript();

	for (SCRIPTUNITMAPITER it = scriptUnitTypes_.begin(); it != scriptUnitTypes_.end(); it++)
	{
		S_RELEASE(it->second);
	}
	scriptUnitTypes_.clear();
	script::PyGC::debugTracing();
	return true;
}

template<class E>
E* EntityApp<E>::createEntity(const char* entityType, ENTITY_ID eid, bool isInitializeScript)
{
	// ���ID�Ƿ��㹻, ���㷵��NULL
	if(eid <= 0 && idClient_.size() == 0)
	{
		return NULL;
	}
	
	/*ScriptDefModule* sm = EntityDef::findScriptModule(entityType);
	if(sm == NULL)
	{
		PyErr_Format(PyExc_TypeError, "EntityApp::createEntity: entityType [%s] not found! Please register in entities.xml and implement a %s.def and %s.py\n",
			entityType, entityType, entityType);

		PyErr_PrintEx(0);
		return NULL;
	}
	else if(componentType_ == CELLAPP_TYPE ? !sm->hasCell() : !sm->hasBase())
	{
		PyErr_Format(PyExc_TypeError, "EntityApp::createEntity: cannot create %s(%s=false)! Please check the setting of the entities.xml and the implementation of %s.py\n",
			entityType,
			(componentType_ == CELLAPP_TYPE ? "hasCell()" : "hasBase()"),
			entityType);

		PyErr_PrintEx(0);
		return NULL;
	}

	PyObject* obj = sm->createObject();*/
	PyTypeObject* pObjType = findUnitScriptType(entityType);
	if (!pObjType)
	{
		PyErr_Format(PyExc_TypeError, "EntityApp::createEntity: entityType [%s] not found! Please register in entities.xml and implement a %s.def and %s.py\n",
			entityType, entityType, entityType);

		PyErr_PrintEx(0);
		return NULL;
	}

	PyObject * obj = PyType_GenericAlloc(pObjType, 0);
	if (obj == NULL)
	{
		PyErr_Print();
		ERROR_MSG("ScriptDefModule::createObject: GenericAlloc is failed.\n");
		return NULL;
	}

	// �ж��Ƿ�Ҫ����һ���µ�id
	ENTITY_ID id = eid;
	if(id <= 0)
		id = idClient_.alloc();
	
	E* entity = onCreateEntity(obj, id);

	//if(initProperty)
	//	entity->initProperty();

	// ��entity����entities
	pEntities_->add(id, entity); 

	// ��ʼ���ű�
	if (isInitializeScript)
	{
		if (PyObject_HasAttrString(obj, "__init__"))
		{
			PyObject* pyResult = PyObject_CallMethod(obj, const_cast<char*>("__init__"),
				const_cast<char*>(""));
			if (pyResult != NULL)
				Py_DECREF(pyResult);
			else
				SCRIPT_ERROR_CHECK();
		}
	}

	SCRIPT_ERROR_CHECK();

	INFO_MSG(fmt::format("EntityApp::createEntity: new {0} {1}\n", entityType, id));

	return entity;
}

template<class E>
E* EntityApp<E>::onCreateEntity(PyObject* pyEntity, ENTITY_ID eid)
{
	// ִ��Entity�Ĺ��캯��
	return new(pyEntity) E(eid);
	//return new E(eid);
}

template<class E>
void EntityApp<E>::onSignalled(int sigNum)
{
	this->ServerApp::onSignalled(sigNum);
	
	switch (sigNum)
	{
	case SIGQUIT:
		CRITICAL_MSG(fmt::format("Received QUIT signal. This is likely caused by the "
				"{}Mgr killing this {} because it has been "
					"unresponsive for too long. Look at the callstack from "
					"the core dump to find the likely cause.\n",
				COMPONENT_NAME_EX(componentType_), 
				COMPONENT_NAME_EX(componentType_)));
		
		break;
	default: 
		break;
	}
}

template<class E>
void EntityApp<E>::handleTimeout(TimerHandle handle, void * arg)
{
	switch (reinterpret_cast<uintptr>(arg))
	{
		case TIMEOUT_GAME_TICK:
			this->handleGameTick();
			break;
		default:
			break;
	}

	ServerApp::handleTimeout(handle, arg);
}

template<class E>
void EntityApp<E>::handleGameTick()
{
	// time_t t = ::time(NULL);
	// DEBUG_MSG("EntityApp::handleGameTick[%"PRTime"]:%u\n", t, time_);

	++g_kbetime;
	threadPool_.onMainThreadTick();
	handleTimers();
	
	{
		//AUTO_SCOPED_PROFILE("processRecvMessages");
		networkInterface().processChannels(KBEngine::Network::MessageHandlers::pMainMessageHandlers);
	}
}

template<class E>
bool EntityApp<E>::destroyEntity(ENTITY_ID entityID, bool callScript)
{
	PyObjectPtr entity = pEntities_->erase(entityID);
	if(entity != NULL)
	{
		static_cast<E*>(entity.get())->destroy(callScript);
		return true;
	}

	ERROR_MSG(fmt::format("EntityApp::destroyEntity: not found {}!\n", entityID));
	return false;
}

template<class E>
E* EntityApp<E>::findEntity(ENTITY_ID entityID)
{
	//AUTO_SCOPED_PROFILE("findEntity");
	return pEntities_->find(entityID);
}

template<class E>
void EntityApp<E>::onReqAllocEntityID(Network::Channel* pChannel, ENTITY_ID startID, ENTITY_ID endID)
{
	if(pChannel->isExternal())
		return;
	
	// INFO_MSG("EntityApp::onReqAllocEntityID: entityID alloc(%d-%d).\n", startID, endID);
	idClient_.onAddRange(startID, endID);
}

template<class E>
void EntityApp<E>::onDbmgrInitCompleted(Network::Channel* pChannel, 
						GAME_TIME gametime, ENTITY_ID startID, ENTITY_ID endID, 
						COMPONENT_ORDER startGlobalOrder, COMPONENT_ORDER startGroupOrder, 
						const std::string& digest)
{
	if(pChannel->isExternal())
		return;
	
	INFO_MSG(fmt::format("EntityApp::onDbmgrInitCompleted: entityID alloc({}-{}), startGlobalOrder={}, startGroupOrder={}, digest={}.\n",
		startID, endID, startGlobalOrder, startGroupOrder, digest));

	//startGlobalOrder_ = startGlobalOrder;
	//startGroupOrder_ = startGroupOrder;
	//g_componentGlobalOrder = startGlobalOrder;
	//g_componentGroupOrder = startGroupOrder;

	idClient_.onAddRange(startID, endID);
	g_kbetime = gametime;

	/*setEvns();*/

}

template<class E>
void EntityApp<E>::onBroadcastGlobalDataChanged(Network::Channel* pChannel, KBEngine::MemoryStream& s)
{
	if(pChannel->isExternal())
		return;
	
	std::string key, value;
	bool isDelete;
	
	s >> isDelete;
	s.readBlob(key);

	if(!isDelete)
	{
		s.readBlob(value);
	}

	//if(isDelete)
	//{
	//	if(pGlobalData_->del(pyKey))
	//	{
	//		// ֪ͨ�ű�
	//	}
	//}
	//else
	//{
	//	
	//}
}

template<class E>
int EntityApp<E>::tickPassedPercent(uint64 curr)
{
	// �õ���һ��tick�����������ŵ�ʱ��
	uint64 pass_stamps = (curr - lastTimestamp_) * uint64(1000) / stampsPerSecond();

	// �õ�ÿHertz�ĺ�����
	static int expected = (1000 / g_kbeSrvConfig.gameUpdateHertz());

	// �õ���ǰ���ŵ�ʱ��ռһ��ʱ�����ڵĵİٷֱ�
	return int(pass_stamps) * 100 / expected;
}

template<class E>
uint64 EntityApp<E>::checkTickPeriod()
{
	uint64 curr = timestamp();
	int percent = tickPassedPercent(curr);

	if (percent > 200)
	{
		WARNING_MSG(fmt::format("EntityApp::checkTickPeriod: tick took {0}% ({1:.2f} seconds)!\n",
					percent, (float(percent)/1000.f)));
	}

	uint64 elapsed = curr - lastTimestamp_;
	lastTimestamp_ = curr;
	return elapsed;
}


template<class E>
void EntityApp<E>::updateLoad()
{
	uint64 lastTickInStamps = checkTickPeriod();

	// ��ÿ���ʱ�����
	double spareTime = 1.0;
	if (lastTickInStamps != 0)
	{
		spareTime = double(dispatcher_.getSpareTime()) / double(lastTickInStamps);
	}

	dispatcher_.clearSpareTime();

	// �������ʱ�����С��0 ���ߴ���1�������ʱ��׼ȷ
	if ((spareTime < 0.f) || (1.f < spareTime))
	{
		if (g_timingMethod == RDTSC_TIMING_METHOD)
		{
			CRITICAL_MSG(fmt::format("EntityApp::handleGameTick: "
						"Invalid timing result {:.3f}.\n"
						"Please change the environment variable KBE_TIMING_METHOD to [rdtsc|gettimeofday|gettime](curr = {1})!",
						spareTime, getTimingMethodName()));
		}
		else
		{
			CRITICAL_MSG(fmt::format("EntityApp::handleGameTick: Invalid timing result {:.3f}.\n",
					spareTime));
		}
	}

	calcLoad((float)spareTime);
	onUpdateLoad();
}

template<class E>
void EntityApp<E>::calcLoad(float spareTime)
{
	// ���ص�ֵΪ1.0 - ����ʱ�����, ������0-1.f֮��
	float load = KBEClamp(1.f - spareTime, 0.f, 1.f);

	// �˴��㷨��server_operations_guide.pdf����loadSmoothingBias��
	// loadSmoothingBias �������θ���ȡ���һ�θ��ص�loadSmoothingBiasʣ����� + ��ǰ���ص�loadSmoothingBias����
	static float loadSmoothingBias = 0.01f;// g_kbeSrvConfig.loadSmoothingBias;
	load_ = (1 - loadSmoothingBias) * load_ + loadSmoothingBias * load;
}
}

#endif // KBE_ENTITY_APP_H

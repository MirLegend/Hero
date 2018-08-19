#include "server/kbemain.h"
#include "dbmgr.h"

#undef DEFINE_IN_INTERFACE
#undef KBE_SERVER_INTERFACE_MACRO_H //����Ҫ�������
#include "login/login_interface.h"
#define DEFINE_IN_INTERFACE
#include "login/login_interface.h"

#undef DEFINE_IN_INTERFACE
#undef KBE_SERVER_INTERFACE_MACRO_H //����Ҫ�������
#include "logger/logger_interface.h"
#define DEFINE_IN_INTERFACE
#include "logger/logger_interface.h"

#undef DEFINE_IN_INTERFACE
#undef KBE_SERVER_INTERFACE_MACRO_H //����Ҫ�������
#include "cellmgr/cellmgr_interface.h"
#define DEFINE_IN_INTERFACE
#include "cellmgr/cellmgr_interface.h"

#undef DEFINE_IN_INTERFACE
#undef KBE_SERVER_INTERFACE_MACRO_H //����Ҫ�������
#include "cellapp/cellapp_interface.h"
#define DEFINE_IN_INTERFACE
#include "cellapp/cellapp_interface.h"

#undef DEFINE_IN_INTERFACE
#undef KBE_SERVER_INTERFACE_MACRO_H //����Ҫ�������
#include "baseapp/baseapp_interface.h"
#define DEFINE_IN_INTERFACE
#include "baseapp/baseapp_interface.h"

#undef DEFINE_IN_INTERFACE
#undef KBE_SERVER_INTERFACE_MACRO_H //����Ҫ�������
#include "basemgr/basemgr_interface.h"
#define DEFINE_IN_INTERFACE
#include "basemgr/basemgr_interface.h"

using namespace KBEngine;
int KBENGINE_MAIN(int argc, char* argv[])
{
	ENGINE_COMPONENT_INFO& info = g_kbeSrvConfig.getDBMgr();
	return kbeMainT<DBMgrApp>(argc, argv, DBMGR_TYPE, -1, -1, "", info.port, info.ip.c_str());
}

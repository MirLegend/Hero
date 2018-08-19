/*
This source file is part of KBEngine
For the latest info, see http://www.kbengine.org/

Copyright (c) 2008-2016 KBEngine.

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

#ifndef KBE_DB_INTERFACE_REDIS_H
#define KBE_DB_INTERFACE_REDIS_H

#include "common.h"
#include "common/common.h"
#include "common/singleton.h"
#include "common/memorystream.h"
#include "helper/debug_helper.h"
#include "db_interface/db_interface.h"

#include "hiredis.h"
#if KBE_PLATFORM == PLATFORM_WIN32
#ifdef _DEBUG
#pragma comment (lib, "hiredis_d.lib")
#else
#pragma comment (lib, "hiredis.lib")
#endif
#endif

namespace KBEngine { 

/*
	���ݿ�ӿ�
*/
class DBInterfaceRedis : public DBInterface
{
public:
	DBInterfaceRedis();
	virtual ~DBInterfaceRedis();

	static bool initInterface(DBInterface* dbi);
	
	bool ping(redisContext* pRedisContext = NULL);
	
	/**
		��黷��
	*/
	virtual bool checkEnvironment();
	
	/**
		������ �Դ�������ݽ��о���
		����������ɹ�����ʧ��
	*/
	virtual bool checkErrors();

	/**
		��ĳ�����ݿ����
	*/
	virtual bool attach(const char* databaseName = NULL);
	virtual bool detach();

	/**
		��ȡ���ݿ����еı���
	*/
	virtual bool getTableNames( std::vector<std::string>& tableNames, const char * pattern);

	/**
		��ȡ���ݿ�ĳ�������е��ֶ�����
	*/
	virtual bool getTableItemNames(const char* tableName, std::vector<std::string>& itemNames);

	/**
		��ѯ��
	*/
	virtual bool query(const char* cmd, uint32 size, bool showExecInfo = true, MemoryStream * result = NULL);

	void write_query_result(redisReply* r, MemoryStream * result);
	void write_query_result_element(redisReply* r, MemoryStream * result);
		
	/**
		��������ӿڵ�����
	*/
	virtual const char* c_str();

	/** 
		��ȡ����
	*/
	virtual const char* getstrerror();

	/** 
		��ȡ������
	*/
	virtual int getlasterror();

	/**
		����һ��entity�洢��
	*/
	virtual EntityTable* createEntityTable();

	/** 
		�����ݿ�ɾ��entity��
	*/
	virtual bool dropEntityTableFromDB(const char* tableName);

	/** 
		�����ݿ�ɾ��entity���ֶ�
	*/
	virtual bool dropEntityTableItemFromDB(const char* tableName, const char* tableItemName);

	/**
		��ס�ӿڲ���
	*/
	virtual bool lock();
	virtual bool unlock();

	/**
		�����쳣
	*/
	virtual bool processException(std::exception & e);
	
protected:
	redisContext* pRedisContext_;
	bool hasLostConnection_;
};


}

#endif // KBE_DB_INTERFACE_REDIS_H

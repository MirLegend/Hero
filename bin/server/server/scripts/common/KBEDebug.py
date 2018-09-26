# -*- coding: utf-8 -*-
import sys
import KBEngine

def printMsg(args, isPrintPath):
	for m in args:print (m)

def TRACE_MSG(*args): 
	KBEngine.scriptLogType(KBEngine.LOG_TYPE_NORMAL)
	printMsg(args, False)
	
def DEBUG_MSG(*args): 
	if True:
		KBEngine.scriptLogType(KBEngine.LOG_TYPE_DBG)
		printMsg(args, True)
	
def INFO_MSG(*args): 
	if True:
		KBEngine.scriptLogType(KBEngine.LOG_TYPE_INFO)
		printMsg(args, False)
	
def WARNING_MSG(*args): 
	KBEngine.scriptLogType(KBEngine.LOG_TYPE_WAR)
	printMsg(args, True)

def ERROR_MSG(*args): 
	KBEngine.scriptLogType(KBEngine.LOG_TYPE_ERR)
	printMsg(args, True)

# -*- coding: utf-8 -*-
import time
import random
import KBEngine
from KBEDebug import *
from Manager.StageManager import stageManager
import GlobalDefine
#import d_parameters
#import d_itemgroups

class StageItem:
	"""
	关卡单位
	"""
	def __init__(self):
		pass
		

class StageContainer:
	"""
	关卡容器
	"""
	def __init__(self, player):
		self.player = player
		
		#t = int(time.time()) #时间戳
		self.userstage_elite_reset_time = 0
		self.userstage_sweep_last_reset_time = 0
		self.userstage_sweep_today_free_sweep_times = 0
		self.userstage_act_reset_time = 0
		
		self.normal_stage_stars=[]
		self.elite_stage_stars=[]
		
		self.curStageId = 0
		pass
		
	def reqEnterStage(self, stageid, enter_stage_reply):
		return stageManager.reqEnterStage(self, stageid, enter_stage_reply)
		
	def reqExitStage(self, exit_up, exit_stage_reply):
		return stageManager.reqExitStage(self, exit_up, exit_stage_reply)
	
	def ParseFromProtoData(self, protoData):
		self.userstage_elite_reset_time = protoData._elite_reset_time
		self.userstage_sweep_last_reset_time = protoData._sweep._last_reset_time
		self.userstage_sweep_today_free_sweep_times = protoData._sweep._today_free_sweep_times
		self.userstage_act_reset_time = protoData._act_reset_time
		
		for v in protoData._normal_stage_stars:
			self.normal_stage_stars.append(v)
			
		for v in protoData._elite_stage_stars:
			self.elite_stage_stars.append(v)
		
	def SerializeToProtoData(self, protoData):
		protoData._elite_reset_time = self.userstage_elite_reset_time
		protoData._sweep._last_reset_time = self.userstage_sweep_last_reset_time
		protoData._sweep._today_free_sweep_times = self.userstage_sweep_today_free_sweep_times
		protoData._act_reset_time = self.userstage_act_reset_time
		
		for v in self.normal_stage_stars:
			protoData._normal_stage_stars.append(v)
			
		for v in self.elite_stage_stars:
			protoData._elite_stage_stars.append(v)


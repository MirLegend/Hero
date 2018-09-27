# -*- coding: utf-8 -*-
import KBEngine
from KBEDebug import *
import d_stage

MAX_MINE_STAGE_ID = -18
MAX_CRUSADE_STAGE_ID = -3
MAX_NORMAL_STAGE_ID = 10000
MAX_ELITE_STAGE_ID = 20000
MAX_ACT_STAGE_ID = 30000

CRUSADE_STAGE = -3
GUIDE_STAGE = -2
ARENA_STAGE = -1
NORMAL_STAGE = 1
ELITE_STAGE = 2
ACT_STAGE = 3
MINE_STAGE = 4

class StageManager:
	"""
	关卡管理
	"""
	def __init__(self):
		pass
		
	def getStageType(self, stageId):
		if stageId <= MAX_MINE_STAGE_ID:
			return MINE_STAGE
		elif stageId <= MAX_CRUSADE_STAGE_ID :
			return CRUSADE_STAGE
		elif stageId <= GUIDE_STAGE:
			return GUIDE_STAGE
		elif stageId <= ARENA_STAGE :
			return ARENA_STAGE
		elif stageId < MAX_NORMAL_STAGE_ID :
			return NORMAL_STAGE
		elif stageId < MAX_ELITE_STAGE_ID :
			return ELITE_STAGE
		elif stageId < MAX_ACT_STAGE_ID :
			return ACT_STAGE
		elif stageId < MAX_MINE2_STAGE_ID :
			return MINE_STAGE
		elif stageId < MAX_RAID_STAGE_ID :
			return RAID_STAGE
		else :
			return MINE_STAGE
			
	def reqEnterStage(self, stageContainer, stageId, enter_stage_reply):
		stageType = self.getStageType(stageId)
		if stageType != NORMAL_STAGE and stageType != ELITE_STAGE:
			ERROR_MSG("OnEnterStage stage not normal or elite type!")
			return False
			
		stageconfig = d_stage.datas.get(str(stageId))
		if stageconfig is None:
			ERROR_MSG("OnEnterStage stage id not defined!")
			return False
			
		reqStage = int(stageconfig["Require Stage"])
		regStageType = self.getStageType(stageId)
		reqSeq = 0
		isFirstDown = True
		#if regStageType == NORMAL_STAGE:
		#	tbStage = self.getNormalStageTable()
		#	reqSeq = reqStage - 1
		#else:
		#	tbStage = self.getEliteStageTable()
		#	reqSeq = reqStage - MAX_NORMAL_STAGE_ID - 1
			
		#if reqStage > 0:
		#	if tbStage.getMaxStageId() < reqStage:
		#		ERROR_MSG("OnEnterStage require stage not pass stageid:%i"%(tbStage.getMaxStageId()))
		#		return False
		#["Vit Return"] = 5,
		returnVit = int(stageconfig["Vit Return"])
		#["Vitality Cost"] = 6,
		costVit = int(stageconfig["Vitality Cost"])
		
		stageContainer.curStageId = stageId
		
		enter_stage_reply._rseed = 1
		loot = (3<<13 | 1<<10 | 157)
		enter_stage_reply._loots.append(loot)
		return True
		
	def reqExitStage(self, stageContainer, exitup, exit_stage_reply):
		exit_stage_reply._result = 1
		return True
		
		
stageManager = StageManager()

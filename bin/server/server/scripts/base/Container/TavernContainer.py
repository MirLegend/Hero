# -*- coding: utf-8 -*-
import time
import random
import KBEngine
from KBEDebug import *
import GlobalDefine
import d_parameters
import d_itemgroups

class TavernItem:
	"""
	酒馆单位
	"""
	def __init__(self, box_type, left_cnt, last_get_time, has_first_draw):
		self.boxType = box_type
		self.leftCnt = left_cnt
		self.lastGetTime = last_get_time
		self.oneDrawTimes=has_first_draw>>16
		self.tenDrawTimes=(has_first_draw<<16)>>16
		if left_cnt == 0 and has_first_draw == 0:
			if box_type == GlobalDefine.box_type_green:
				self.leftCnt = d_parameters.datas['tavern_bronze_chance']
			elif box_type == GlobalDefine.box_type_blue:
				self.leftCnt = d_parameters.datas['tavern_silver_chance']
			elif box_type == GlobalDefine.box_type_purple:
				self.leftCnt = d_parameters.datas['tavern_magic_chance']
		
		#t = int(time.time()) #时间戳
		#if last_get_time + d_parameters.datas['tavern_bronze_cd'] <= t:
		#	self.lastGetTime  = t
		#	self.leftCnt += 1
		

class TavernContainer:
	"""
	酒馆容器
	"""
	def __init__(self, player):
		self.player = player
		self.tavernDatas = {}
		pass
		
	def getTavernTableInfoByBoxType(self, boxtype):
		if boxtype in self.tavernDatas:
			return self.tavernDatas[boxtype]
		else:
			tavern = TavernItem(boxtype, 0, 0, 0)
			self.tavernDatas[boxtype] = tavern
			return tavern

	def reqTavernDraw(self, drawtype, boxtype, tavern_draw_reply):
		"""
		酒馆抽奖
		"""
		if drawtype is None:
			drawtype = GlobalDefine.draw_type_single
			
		drawtype = GlobalDefine.draw_type_single
			
		if boxtype is None:
			boxtype = GlobalDefine.box_type_green
			
		boxtype = GlobalDefine.box_type_green
			
		#消耗货币数量
		cost = 0
		costType = GlobalDefine.cost_type_coin
		cdtime = 0
		drawKey_ = 'Bronze'
		
		if boxtype == GlobalDefine.box_type_green:
			cdtime = d_parameters.datas['tavern_bronze_cd']
			costType = GlobalDefine.cost_type_coin
			drawKey_ = 'Bronze'
		elif boxtype == GlobalDefine.box_type_purple:
			cdtime = d_parameters.datas['tavern_gold_cd']
			costType = GlobalDefine.cost_type_gems
			drawKey_ = 'Gold'
		elif boxtype == GlobalDefine.box_type_magicsoul:
			cdtime = d_parameters.datas['tavern_magic_cd']
			costType = GlobalDefine.cost_type_gems
			drawKey_ = 'MagicSoul'
			
		isTen = False
		if drawtype != GlobalDefine.draw_type_single:
			isTen = True
			
		playerTavern = self.getTavernTableInfoByBoxType(boxtype)
		
		t = int(time.time()) #时间戳
		rewardArr = {1:[], 2:[]} # 1: 英雄  2: 物品
		if boxtype == GlobalDefine.box_type_green: #绿箱子
			if drawtype == GlobalDefine.draw_type_single and playerTavern.leftCnt>0 and playerTavern.lastGetTime + cdtime <= t: #免费的
				cost = 0
				playerTavern.leftCnt -= 1
				playerTavern.lastGetTime = t
				if playerTavern.oneDrawTimes == 0: #第一次抽奖 给火女
					rewardArr[1].append(3)
				elif playerTavern.oneDrawTimes == 1: #再次抽取给小鹿的灵魂石
					##rewardArr[2].append([157, 1])
					rewardArr[1].append(2)
				else: #随机一个物品
					itemgroup = d_itemgroups.datas.get('101')
					if itemgroup is None:
						rewardArr[2].append([157, 1])
					else:
						itemconfigs = itemgroup.keys()
						ran = random.randint(0,len(itemconfigs)-1)
						itemr = itemgroup[itemconfigs[ran]]
						if itemr['type'] == 'item':
							rewardArr[2].append([itemr['id'], itemr['amout']])
						elif itemr['type'] == 'hero':
							rewardArr[1].append(itemr['id'])
				playerTavern.oneDrawTimes += 1
			elif drawtype == GlobalDefine.draw_type_single: #单次付费
				cost = -10
				if playerTavern.oneDrawTimes == 1: #再次抽取给小鹿的灵魂石
					#rewardArr[2].append([157, 1])
					rewardArr[1].append(2)
				else: #随机一个物品
					itemgroup = d_itemgroups.datas.get('101')
					if itemgroup is None:
						rewardArr[2].append([157, 1])
					else:
						itemconfigs = itemgroup.keys()
						ran = random.randint(0,len(itemconfigs)-1)
						itemr = itemgroup[itemconfigs[ran]]
						if itemr['type'] == 'item':
							rewardArr[2].append([itemr['id'], itemr['amout']])
						elif itemr['type'] == 'hero':
							rewardArr[1].append(itemr['id'])
				playerTavern.oneDrawTimes += 1
			else: #十连抽付费
				rewardArr[2].append([157, 1])
				playerTavern.oneDrawTimes += 1
		
		if cost > 0:
			if not self.player.addUserCurrency(costType, cost, GlobalDefine.CURRENCY_LOG_tavernDraw):
				return False
		for v in rewardArr[1]: #添加英雄
			self.player.addPlayerHero(v, GlobalDefine.ITEM_LOG_tavernDraw)
			protoHero = tavern_draw_reply._new_heroes.add()
			self.player.heroContainer.SerializeHeroById(v, protoHero)
			tavern_draw_reply._item_ids.append((1<<10) | v)
			
		for v in rewardArr[2]: #添加物品
			self.player.addPlayerItem(v[0], v[1], GlobalDefine.ITEM_LOG_tavernDraw)
			tavern_draw_reply._item_ids.append((v[1]<<10) | v[0])

		return True
		
	def ParseFromProtoData(self, protoData):
		for v in protoData:
			tavern = TavernItem(v._box_type, v._left_cnt, v._last_get_time, v._has_first_draw)
			self.tavernDatas[v._box_type] = tavern
		pass
		
	def SerializeToProtoData(self, protoData):
		for k, v in self.tavernDatas.items():
			tavern = protoData.add()
			tavern._box_type = v.boxType
			tavern._left_cnt = v.leftCnt
			tavern._last_get_time = v.lastGetTime
			tavern._has_first_draw = (v.oneDrawTimes<<16) | v.tenDrawTimes
		pass


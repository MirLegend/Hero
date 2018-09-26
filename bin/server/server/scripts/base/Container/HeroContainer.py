# -*- coding: utf-8 -*-
import KBEngine
from KBEDebug import *
import GlobalDefine
import d_heros
import d_skillgroup

class HeroEquipItem:
	"""
	英雄装备
	"""
	def __init__(self, itemid, exp):
		self.itemId = itemid
		self.exp = exp

class HeroItem:
	"""
	英雄单位
	"""
	def __init__(self, heroId, level, exp, rank, stars, state, skillconfig):
		self.tid = heroId
		self.level = level
		self.exp = exp
		if rank is None:
			self.rank = 1
		else:
			self.rank = rank
			
		if stars is None:
			self.stars = 1
		else:
			self.stars = stars
		
		self.state = state
		
		self.gs = 100
		
		#=====技能
		self.heroSkills = []
		for i in range (4):
			skilllevel = skillconfig[str(i+1)]["Init Level"]
			if skilllevel is None:
				skilllevel = 1
			self.heroSkills.append(skilllevel)
		pass
		#=====装备
		self.heroEquips = []
		for i in range (6):
			self.heroEquips.append(HeroEquipItem(0, 0))
		pass
	
	def setHeroEquip(self, index, equiptid, exp):
		self.heroEquips[index].itemId = equiptid
		self.heroEquips[index].exp = exp

class HeroContainer:
	"""
	玩家英雄容器
	"""
	def __init__(self, player):
		self.player = player
		self.heroDatas = {}
		pass

	
	def addPlayerHero(self, heroId, addReason):
		"""
		添加一个英雄，参数: 英雄id， 添加原因
		"""
		heroconfig = d_heros.datas.get(str(heroId))
		if heroconfig is None:
			ERROR_MSG("addPlayerHero error heroconfig not found heroid:%i"%(heroId))
			return
			
		skillconfig = d_skillgroup.datas.get(str(heroId))
		if skillconfig is None:
			ERROR_MSG("addPlayerHero error skillconfig not found heroid:%i"%(heroId))
			return
			
		if heroId in self.heroDatas:
			ERROR_MSG("addPlayerHero hero is allready in herodatas heroid:%i"%(heroId))
			return
			
		hero = HeroItem(heroId, 1, 0, heroconfig['Initial Rank'], heroconfig['Initial Stars'], GlobalDefine.Hero_status_idle, skillconfig)
		self.heroDatas[heroId] = hero
		ERROR_MSG("addPlayerHero successfully  heroid:%i"%(heroId))
		pass
	
	#required uint32 _tid                  = 1;
    #optional uint32 _rank                 = 2;   // 英雄阶级
    #required uint32 _level                = 3;   // 英雄等级
    #required uint32 _stars                = 4;   // 进化等级
    #required uint32 _exp                  = 5;
    #required uint32 _gs                   = 6;
    #required uint32 _state           = 7;   // 英雄状态，标识英雄正在干的事
    #repeated uint32 _skill_levels         = 8;   // 技能等级
    #repeated hero_equip _items            = 9;   // 当前的装备列表
	def ParseFromProtoData(self, protoData):
		for v in protoData:
			skills = {}
			#for skillv in protoData._skill_levels:
			for i in range(len(v._skill_levels)):
				skills[str(i+1)] = {"Init Level" : v._skill_levels[i]}
			hero = HeroItem(v._tid, v._level, v._exp, v._rank, v._stars, v._state, skills)
			self.heroDatas[v._tid] = hero
			for ev in (v._items):
				hero.setHeroEquip(ev._index-1, ev._item_id, ev._exp)
		pass
		
	def SerializeToProtoData(self, protoData):
		for k, v in self.heroDatas.items():
			heroProto = protoData.add()
			heroProto._tid = v.tid
			heroProto._rank = v.rank
			heroProto._level= v.level
			heroProto._stars= v.stars
			heroProto._exp= v.exp
			heroProto._gs= v.gs
			heroProto._state=v.state
			for i in range (4):
				heroProto._skill_levels.append(v.heroSkills[i])
			for i in range (6):
				heproto = heroProto._items.add()
				heproto._index = i+1
				heproto._item_id = v.heroEquips[i].itemId
				heproto._exp = v.heroEquips[i].exp
		pass
		
	def SerializeHeroById(self, heroId, heroProto):
		if heroId not in self.heroDatas:
			ERROR_MSG("SerializeHeroById hero is not in herodatas heroid:%i"%(heroId))
			return
		heroitem = self.heroDatas[heroId]
		heroProto._tid = heroitem.tid
		heroProto._rank = heroitem.rank
		heroProto._level= heroitem.level
		heroProto._stars= heroitem.stars
		heroProto._exp= heroitem.exp
		heroProto._gs= heroitem.gs
		heroProto._state=heroitem.state
		for i in range (4):
			heroProto._skill_levels.append(heroitem.heroSkills[i])
		for i in range (6):
			heproto = heroProto._items.add()
			heproto._index = i+1
			heproto._item_id = heroitem.heroEquips[i].itemId
			heproto._exp = heroitem.heroEquips[i].exp

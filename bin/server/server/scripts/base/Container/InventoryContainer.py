# -*- coding: utf-8 -*-
import time
import random
import KBEngine
from KBEDebug import *
import GlobalDefine

class InventoryItem:
	"""
	物品单位
	"""
	def __init__(self, itemId, itemNum):
		self.itemId = itemId
		self.itemNum = itemNum
	
	def packetToProto(self):
		return (self.itemNum << 10) | self.itemId
		pass
		
	def unpacketToItem(self, protodata):
		self.itemNum = protodata >> 10
		self.itemId = protodata % 9999999
		

class InventoryContainer:
	"""
	物品容器
	"""
	def __init__(self, player):
		self.player = player
		self.itemDatas = {}
		pass
		
	def addinventoryItem(self, itemId, itemNum, reason):
		if itemId <=0 or itemNum <= 0:
			return
		if itemId in self.itemDatas:
			item = self.itemDatas[itemId]
			item.itemNum += itemNum
		else:
			item = InventoryItem(itemId, itemNum)
			self.itemDatas[itemId] = item
	
	def ParseFromProtoData(self, protoData):
		for v in protoData:
			item = InventoryItem(0, 0)
			item.unpacketToItem(v)
			self.itemDatas[item.itemId] = item
		pass
		
	def SerializeToProtoData(self, protoData):
		for k, v in self.itemDatas.items():
			protoData.append(v.packetToProto())
		pass


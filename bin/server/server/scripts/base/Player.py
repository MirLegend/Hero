import time
import KBEngine
from KBEDebug import *
import GlobalDefine
from Container.HeroContainer import HeroContainer
from Container.TavernContainer import TavernContainer
import down_pb2 as cbproto
import up_pb2 as upproto

arenapoint = 1
crusadepoint = 2
guildpoint = 3

class Player(KBEngine.Proxy):
	def __init__(self):
		KBEngine.Proxy.__init__(self)
		DEBUG_MSG("Player::init id:%i"%(self.id))
		#英雄容器
		self.heroContainer = HeroContainer(self)
		#酒馆容器
		self.tavernContainer = TavernContainer(self)
		self.tutorial = []
		
	def addUserCurrency(self, type, mount, reason):
		if cost_type_coin == type:
			if self.money + mount < 0:
				return False
			else:
				self.money = self.money + mount
				return True
		elif cost_type_gems == type:
			if self.rmb + mount < 0:
				return False
			else:
				self.rmb = self.rmb + mount
				return True
		return False
		
	def addPlayerHero(self, heroId, reason):
		self.heroContainer.addPlayerHero(heroId, reason)
		
	def addPlayerItem(self, itemId, itemNum, reason):
		#self.heroContainer.addPlayerHero(heroId, reason)
		pass
		
	def onInitDatas(self, initData):
		"""
		从数据库中初始化数据
		"""
		user = cbproto.user()
		user.ParseFromString(initData)
		if not user.IsInitialized():
			self.InitPlayerData() #初始化玩家数据
			return
			
		self.playerName = user._name_card._name
		self.last_set_name_time = user._name_card._last_set_name_time
		self.avatar = user._name_card._avatar
		
		self.level = user._level
		self.recharge_sum = user._recharge_sum
		self.exp = user._exp
		self.money = user._money
		self.rmb = user._rmb
		
		self.vitality_current = user._vitality._current
		self.vitality_lastchange = user._vitality._lastchange
		self.vitality_todaybuy = user._vitality._todaybuy
		self.vitality_lastbuy = user._vitality._lastbuy
		
		self.skill_levelup_chance = user._skill_level_up._skill_levelup_chance
		self.skill_levelup_cd = user._skill_level_up._skill_levelup_cd
		self.skill_levelup_reset_times = user._skill_level_up._reset_times
		self.skill_levelup_last_reset_date = user._skill_level_up._last_reset_date
		
		self.userstage_elite_reset_time = user._userstage._elite_reset_time
		self.userstage_sweep_last_reset_time = user._userstage._sweep._last_reset_time
		self.userstage_sweep_today_free_sweep_times = user._userstage._sweep._today_free_sweep_times
		self.userstage_act_reset_time = user._userstage._act_reset_time
		
		self.usermidas_last_charge = user._usermidas._last_change
		self.usermidas_today_times = user._usermidas._today_times

		self.daily_login_frequency = user._daily_login._frequency
		self.daily_login_lastlogin_date = user._daily_login._last_login_date
		self.daily_login_status = user._daily_login._status
		
		self.guid_id = user._user_guild._id
		self.guid_name = user._user_guild._name
		
		self.world_chat_times = user._chat._world_chat_times
		self.world_chat_last_rest_time = user._chat._last_reset_world_chat_time
		
		self.user_point = {}
		for item in user._points:
			self.user_point[item._type] = item._value
			
		for v in user._tutorial:
			self.tutorial.append(v)
			
		self.heroContainer.ParseFromProtoData(user._heroes)
		DEBUG_MSG("Player::onInitDatas id:%i, level:%i, name:%s"%(self.id, user._level, user._name_card._name))
		
	def InitPlayerData(self):
		"""
		新角色数据初始化
		"""
		DEBUG_MSG("Player::InitPlayerData id:%i"%(self.id))
		t = int(time.time()) #时间戳
		self.playerName = "not set"
		self.last_set_name_time = 0
		self.avatar = 1
		
		self.level = 1
		self.recharge_sum = 0
		self.exp = 0
		self.money = 1000
		self.rmb = 0
		
		self.vitality_current = 100
		self.vitality_lastchange = t
		self.vitality_todaybuy = 0
		self.vitality_lastbuy = 0
		
		self.skill_levelup_chance = 5
		self.skill_levelup_cd = t
		self.skill_levelup_reset_times = 0
		self.skill_levelup_last_reset_date = t
		
		self.userstage_elite_reset_time = 0
		self.userstage_sweep_last_reset_time = t
		self.userstage_sweep_today_free_sweep_times = 0
		self.userstage_act_reset_time = t
		
		self.usermidas_last_charge = t
		self.usermidas_today_times = 0
		
		self.daily_login_frequency = 1
		self.daily_login_lastlogin_date = t
		self.daily_login_status = 3
		
		self.guid_id = 0
		self.guid_name = "sdf"
		
		self.world_chat_times = 0
		self.world_chat_last_rest_time = t
		
		self.user_point = {}
		self.user_point[arenapoint] = 100
		self.user_point[crusadepoint] = 100
		self.user_point[guildpoint] = 100
		#crusadepoint = person.phones.add() user_point
		
		##heros info  送个船长
		self.heroContainer.addPlayerHero(1, GlobalDefine.ITEM_LOG_INITGIVE)

	def onUserLogonOn(self):
		"""
		玩家登陆通知
		"""
		DEBUG_MSG("Player::onUserLogonOn id:%i"%(self.id))
		downmsg = cbproto.down_msg()
		downmsg._login_reply._result = 0
		self.packetUserDataToProto(downmsg._login_reply._user)
		downmsg._login_reply._time_zone = "china"
		self.sendDataToClient(91, 6, downmsg.SerializeToString())
		
	def OnProcessClientUpMsg(self, upData):
		"""
		玩家消息处理 这个流程是移植过来的，有点奇怪吧。
		"""
		DEBUG_MSG("Player::OnProcessClientUpMsg id:%i"%(self.id))
		upProto = upproto.up_msg()
		upProto.ParseFromString(upData)
		
		bRespCmd = False
		downmsg = cbproto.down_msg()
		
		#-----------------新手引导------------------------
		if upProto.HasField('_tutorial'):
			ERROR_MSG("OnProcessClientUpMsg ---- _tutorial")
			self.tutorial = []
			for v in upProto._tutorial._record:
				self.tutorial.append(v)
		
		#-----------------进阶的英雄------------------------
		if upProto.HasField('_hero_upgrade'):
			ERROR_MSG("OnProcessClientUpMsg ---- hero_upgrade")
			
		#-----------------合成的装备------------------------
		if upProto.HasField('_equip_synthesis'):
			ERROR_MSG("OnProcessClientUpMsg ---- _equip_synthesis")
		
		#-----------------英雄穿装备------------------------
		if upProto.HasField('_wear_equip'):
			ERROR_MSG("OnProcessClientUpMsg ---- _wear_equip")
			
		#-----------------吃经验丹------------------------
		if upProto.HasField('_consume_item'):
			ERROR_MSG("OnProcessClientUpMsg ---- _consume_item")
			
		#-----------------刷新商店------------------------
		if upProto.HasField('_shop_refresh'):
			ERROR_MSG("OnProcessClientUpMsg ---- _shop_refresh")
			
		#-----------------购买物品------------------------
		if upProto.HasField('_shop_consume'):
			ERROR_MSG("OnProcessClientUpMsg ---- _shop_consume")
			
		#-----------------技能升级------------------------
		if upProto.HasField('_skill_levelup'):
			ERROR_MSG("OnProcessClientUpMsg ---- _skill_levelup")
			
		#-----------------物品出售------------------------
		if upProto.HasField('_sell_item'):
			ERROR_MSG("OnProcessClientUpMsg ---- _sell_item")
			
		#-----------------碎片合成------------------------
		if upProto.HasField('_fragment_compose'):
			ERROR_MSG("OnProcessClientUpMsg ---- _fragment_compose")
			
		#-----------------英雄身上的装备进阶------------------------
		if upProto.HasField('_hero_equip_upgrade'):
			ERROR_MSG("OnProcessClientUpMsg ---- _hero_equip_upgrade")
			
		#-----------------触发任务------------------------
		if upProto.HasField('_trigger_task'):
			ERROR_MSG("OnProcessClientUpMsg ---- _trigger_task")
			
		#-----------------请求任务奖励------------------------
		if upProto.HasField('_require_rewards'):
			ERROR_MSG("OnProcessClientUpMsg ---- _require_rewards")
			
		#-----------------触发每日活动------------------------
		if upProto.HasField('_trigger_job'):
			ERROR_MSG("OnProcessClientUpMsg ---- _trigger_job")
			
		#-----------------每日活动奖励------------------------
		if upProto.HasField('_job_rewards'):
			ERROR_MSG("OnProcessClientUpMsg ---- _job_rewards")
			
		#-----------------精英关卡重置------------------------
		if upProto.HasField('_reset_elite'):
			ERROR_MSG("OnProcessClientUpMsg ---- _reset_elite")
			
		#-----------------关卡扫荡------------------------
		if upProto.HasField('_sweep_stage'):
			ERROR_MSG("OnProcessClientUpMsg ---- _sweep_stage")
			
		#-----------------购买体力------------------------
		if upProto.HasField('_buy_vitality'):
			ERROR_MSG("OnProcessClientUpMsg ---- _buy_vitality")
			
		
		#-----------------重置技能强化点数------------------------
		if upProto.HasField('_buy_skill_stren_point'):
			ERROR_MSG("OnProcessClientUpMsg ---- _buy_skill_stren_point")
			
		#-----------------酒馆抽奖------------------------
		if upProto.HasField('_tavern_draw'):
			ERROR_MSG("OnProcessClientUpMsg ---- _tavern_draw")
			bRespCmd = self.tavernContainer.reqTavernDraw(upProto._tavern_draw._draw_type, upProto._tavern_draw._box_type, downmsg._tavern_draw_reply) or bRespCmd
			
		#-----------------查询玩家数据------------------------
		if upProto.HasField('_query_data'):
			ERROR_MSG("OnProcessClientUpMsg ---- _query_data")
			
		#-----------------英雄进化------------------------
		if upProto.HasField('_hero_evolve'):
			ERROR_MSG("OnProcessClientUpMsg ---- _hero_evolve")
			
		#-----------------进入活动关卡------------------------
		if upProto.HasField('_enter_act_stage'):
			ERROR_MSG("OnProcessClientUpMsg ---- _enter_act_stage")
			
		#-----------------同步体力值------------------------
		if upProto.HasField('_sync_vitality'):
			ERROR_MSG("OnProcessClientUpMsg ---- _sync_vitality")
			
		#-----------------客户端关闭日志------------------------
		if upProto.HasField('_suspend_report'):
			ERROR_MSG("OnProcessClientUpMsg ---- _suspend_report")
			
		#-----------------pvp天梯------------------------
		if upProto.HasField('_ladder'):
			ERROR_MSG("OnProcessClientUpMsg ---- _ladder")
			
		#-----------------设置玩家名字------------------------
		if upProto.HasField('_set_name'):
			ERROR_MSG("OnProcessClientUpMsg ---- _set_name")
			
		#-----------------点金手------------------------
		if upProto.HasField('_midas'):
			ERROR_MSG("OnProcessClientUpMsg ---- _midas")
			
		#-----------------花钱打开神秘商店------------------------
		if upProto.HasField('_open_shop'):
			ERROR_MSG("OnProcessClientUpMsg ---- _open_shop")
			
		#-----------------充值------------------------
		if upProto.HasField('_charge'):
			ERROR_MSG("OnProcessClientUpMsg ---- _charge")
			
		#-----------------sdk登陆消息------------------------
		if upProto.HasField('_sdk_login'):
			ERROR_MSG("OnProcessClientUpMsg ---- _sdk_login")
			
		#-----------------设置头像------------------------
		if upProto.HasField('_set_avatar'):
			ERROR_MSG("OnProcessClientUpMsg ---- _set_avatar")
			
		#-----------------每日登陆------------------------
		if upProto.HasField('_ask_daily_login'):
			ERROR_MSG("OnProcessClientUpMsg ---- _ask_daily_login")
			
		#-----------------燃烧的远征------------------------
		if upProto.HasField('_tbc'):
			ERROR_MSG("OnProcessClientUpMsg ---- _tbc")
			
		#-----------------获取所有邮件------------------------
		if upProto.HasField('_get_maillist'):
			ERROR_MSG("OnProcessClientUpMsg ---- _get_maillist")
			
		#-----------------通知服务器处理某封邮件：领取附件，删除邮件------------------------
		if upProto.HasField('_read_mail'):
			ERROR_MSG("OnProcessClientUpMsg ---- _read_mail")
			
		#-----------------获取服务器时间------------------------
		if upProto.HasField('_get_svr_time'):
			ERROR_MSG("OnProcessClientUpMsg ---- _get_svr_time")
			
		#-----------------获取vip礼包------------------------
		if upProto.HasField('_get_vip_gift'):
			ERROR_MSG("OnProcessClientUpMsg ---- _get_vip_gift")
			
		#-----------------重要数据的MD5------------------------
		if upProto.HasField('_important_data_md5'):
			ERROR_MSG("OnProcessClientUpMsg ---- _important_data_md5")
			
		#-----------------聊天------------------------
		if upProto.HasField('_chat'):
			ERROR_MSG("OnProcessClientUpMsg ---- _chat")
			
		#-----------------兑换码------------------------
		if upProto.HasField('_cdkey_gift'):
			ERROR_MSG("OnProcessClientUpMsg ---- _cdkey_gift")
			
		#-----------------公会------------------------
		if upProto.HasField('_guild'):
			ERROR_MSG("OnProcessClientUpMsg ---- _guild")
			
		#-----------------魂匣------------------------
		if upProto.HasField('_ask_magicsoul'):
			ERROR_MSG("OnProcessClientUpMsg ---- _ask_magicsoul")
			
		#-----------------查询返利活动------------------------
		if upProto.HasField('_ask_activity_info'):
			ERROR_MSG("OnProcessClientUpMsg ---- _ask_activity_info")
			
		#-----------------宝藏------------------------
		if upProto.HasField('_excavate'):
			ERROR_MSG("OnProcessClientUpMsg ---- _excavate")
			
		#-----------------推送初始化------------------------
		if upProto.HasField('_push_notify'):
			ERROR_MSG("OnProcessClientUpMsg ---- _push_notify")
			
		#-----------------系统设置------------------------
		if upProto.HasField('_system_setting'):
			ERROR_MSG("OnProcessClientUpMsg ---- _system_setting")
			
		#-----------------查询英雄分解活动信息------------------------
		if upProto.HasField('_query_split_data'):
			ERROR_MSG("OnProcessClientUpMsg ---- _query_split_data")
			
		if bRespCmd:
			self.sendDataToClient(91, 6, downmsg.SerializeToString())

	def packetUserDataToProto(self, user):
		"""
		将玩家数据赋到protobuf数据中
		"""
		user._userid = self.id
		#user._name_card = cbproto.name_card()
		user._name_card._name = self.playerName
		user._name_card._last_set_name_time = self.last_set_name_time
		user._name_card._avatar = self.avatar
		
		user._level = self.level
		user._recharge_sum = self.recharge_sum
		user._exp = self.exp
		user._money = self.money
		user._rmb = self.rmb
		#user._vitality = cbproto.vitality()
		user._vitality._current = self.vitality_current
		user._vitality._lastchange = self.vitality_lastchange
		user._vitality._todaybuy = self.vitality_todaybuy
		user._vitality._lastbuy = self.vitality_lastbuy
		
		#user._skill_level_up = cbproto.skilllevelup()
		user._skill_level_up._skill_levelup_chance = self.skill_levelup_chance
		user._skill_level_up._skill_levelup_cd = self.skill_levelup_cd
		user._skill_level_up._reset_times = self.skill_levelup_reset_times
		user._skill_level_up._last_reset_date = self.skill_levelup_last_reset_date
		
		#user._userstage = cbproto.userstage()
		user._userstage._elite_reset_time = self.userstage_elite_reset_time
		#user._userstage._sweep = cbproto.sweep()
		user._userstage._sweep._last_reset_time = self.userstage_sweep_last_reset_time
		user._userstage._sweep._today_free_sweep_times = self.userstage_sweep_today_free_sweep_times
		user._userstage._act_reset_time = self.userstage_act_reset_time
		
		#user._usermidas = cbproto.usermidas()
		user._usermidas._last_change = self.usermidas_last_charge
		user._usermidas._today_times = self.usermidas_today_times
		
		#user._daily_login = cbproto.daily_login()
		user._daily_login._status = self.daily_login_status
		user._daily_login._frequency = self.daily_login_frequency
		user._daily_login._last_login_date = self.daily_login_lastlogin_date
		
		#user._user_guild = cbproto.user_guild()
		user._user_guild._id=self.guid_id
		user._user_guild._name=self.guid_name
		
		#user._chat = cbproto.chat()
		user._chat._world_chat_times = self.world_chat_times
		user._chat._last_reset_world_chat_time = self.world_chat_last_rest_time
		
		for k, v in self.user_point.items():
			point = user._points.add()
			DEBUG_MSG("user_point type:%s, value:%i"%(k, v))
			point._type = k
			point._value = v
			
		self.heroContainer.SerializeToProtoData(user._heroes)
		
		for v in self.tutorial:
			user._tutorial.append(v)

	def addPersistentsDataToStream(self):
		"""
		给C++调用，将数据序列化成protobuf给底层
		"""
		user = cbproto.user()
		self.packetUserDataToProto(user)
		return user.SerializeToString()
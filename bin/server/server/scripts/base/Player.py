import time
import KBEngine
import down_pb2 as cbproto

arenapoint = 1
crusadepoint = 2
guildpoint = 3

class Player(KBEngine.Proxy):
	def __init__(self):
		KBEngine.Proxy.__init__(self)
		print("Player::init id:%i"%(self.id))
		
		
	#def setViewRadius(self, type):
	#	return 100
	
	def onInitDatas(self, initData):
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
		for item in user.user_point:
			self.user_point[item._type] = item._value
		print("Player::onInitDatas id:%i, level:%i, name:%s"%(self.id, user._level, user._name_card._name))
		
	def InitPlayerData(self):
		print("Player::InitPlayerData id:%i"%(self.id))
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

	def onUserLogonOn(self):
		print("Player::onUserLogonOn id:%i"%(self.id))
		downmsg = cbproto.down_msg()
		downmsg._login_reply._result = 0
		self.packetUserDataToProto(downmsg._login_reply._user)
		downmsg._login_reply._time_zone = "china"
		self.sendDataToClient(91, 6, downmsg.SerializeToString())
		
		
	def OnProcessClientUpMsg(self, upData):
		print("Player::OnProcessClientUpMsg id:%i"%(self.id))
		
		
	#def sendDataToClient(self, mainCmd, subCmd, sendData):
	
	def packetUserDataToProto(self, user):
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
			print("user_point type:%s, value:%i"%(k, v))
			point._type = k
			point._value = v

	def addPersistentsDataToStream(self):
		user = cbproto.user()
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
			point._type = k
			point._value = v
		
		return user.SerializeToString()
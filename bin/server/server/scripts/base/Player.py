import KBEngine

class Player(KBEngine.Proxy):
	def __init__(self):
		KBEngine.Proxy.__init__(self)
		print("Player::init id:%i"%(self.id))
		
	#def setViewRadius(self, type):
	#	return 100
	
	def onInitDatas(self, initData):
		print("Player::onInitDatas id:%i"%(self.id))

	def onUserLogonOn(self):
		print("Player::onUserLogonOn id:%i"%(self.id))
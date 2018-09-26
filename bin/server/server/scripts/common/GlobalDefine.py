# -*- coding: utf-8 -*-

"""
"""
# ------------------------------------------------------------------------------
# costType
# ------------------------------------------------------------------------------
cost_type_coin           = 1    # 金币
cost_type_gems           = 2    # 钻石

# ------------------------------------------------------------------------------
# item reason
# ------------------------------------------------------------------------------
ITEM_LOG_INITGIVE	=1
ITEM_LOG_tavernDraw = 2

# ------------------------------------------------------------------------------
# currency reason
# ------------------------------------------------------------------------------
CURRENCY_LOG_tavernDraw	=1


# ------------------------------------------------------------------------------
# hero_status
# ------------------------------------------------------------------------------
Hero_status_idle = 0    # 空闲
Hero_status_hire = 1    #  雇佣兵
Hero_status_mining = 2    #  守矿

# ------------------------------------------------------------------------------
# draw_type
# ------------------------------------------------------------------------------
draw_type_single = 0   # 单抽
draw_type_combo = 1   # 十连抽
draw_type_stone = 3   # 灵魂石抽奖
draw_type_drfree = 4   # 免费单抽

# ------------------------------------------------------------------------------
# box_type
# ------------------------------------------------------------------------------
box_type_green           = 1    # 绿箱子
box_type_blue            = 2    # 蓝箱子
box_type_purple          = 3    # 紫箱子
box_type_magicsoul       = 4    # 神秘宝箱 抽法为combo
box_type_stone_green     = 5    # 星际商人 抽法为combo
box_type_stone_blue      = 6    # 星际商人 抽法为combo
box_type_stone_purple    = 7    # 星际商人 抽法为combo

# ------------------------------------------------------------------------------
# entity state
# ------------------------------------------------------------------------------
ENTITY_STATE_UNKNOW										= -1
ENTITY_STATE_FREE										= 0
ENTITY_STATE_DEAD										= 1
ENTITY_STATE_REST										= 2
ENTITY_STATE_FIGHT										= 3
ENTITY_STATE_MAX    									= 4

# sub state
ENTITY_SUB_STATE_NORMAL									= 0
ENTITY_SUB_STATE_RANDOM_STROLL							= 1
ENTITY_SUB_STATE_GO_BACK								= 2
ENTITY_SUB_STATE_CHASE_TARGET							= 3
ENTITY_SUB_STATE_FLEE									= 4

# entity的一些行为禁止标志
FORBID_NO												= 0x00000000
FORBID_MOTION											= 0x00000001
FORBID_CHAT												= 0x00000002
FORBID_SPELL											= 0x00000004
FORBID_TRADE											= 0x00000008
FORBID_EQUIP											= 0x00000010
FORBID_INTONATE											= 0x00000020
FORBID_ATTACK_PHY_NEAR									= 0x00000040
FORBID_ATTACK_PHY_FAR									= 0x00000080
FORBID_ATTACK_MAGIC										= 0x00000080
FORBID_YAW												= 0x00008000

FORBID_ATTACK_PHY = FORBID_ATTACK_PHY_NEAR | FORBID_ATTACK_PHY_FAR
FORBID_ATTACK_MAG = FORBID_ATTACK_MAGIC
FORBID_ATTACK = FORBID_ATTACK_PHY | FORBID_ATTACK_MAG
FORBID_MOTION_YAW = FORBID_MOTION | FORBID_YAW

FORBID_ALL = [
	FORBID_MOTION,
	FORBID_YAW,
	FORBID_CHAT,
	FORBID_ATTACK,
	FORBID_SPELL,
	FORBID_TRADE,
	FORBID_EQUIP,
	FORBID_INTONATE,
	FORBID_ATTACK_PHY_NEAR,
	FORBID_ATTACK_PHY_FAR,
	FORBID_ATTACK_MAGIC,
]

FORBID_ACTIONS = {
	ENTITY_STATE_UNKNOW  : 0,
	ENTITY_STATE_FREE    : FORBID_NO,
	ENTITY_STATE_DEAD    : FORBID_MOTION_YAW | FORBID_TRADE | FORBID_ATTACK | FORBID_SPELL | FORBID_EQUIP,
	ENTITY_STATE_REST    : FORBID_MOTION_YAW | FORBID_TRADE | FORBID_ATTACK | FORBID_SPELL | FORBID_EQUIP,
	ENTITY_STATE_FIGHT   : FORBID_EQUIP | FORBID_TRADE,
	}

for f in FORBID_ALL: FORBID_ACTIONS[ENTITY_STATE_UNKNOW] |= f

# ------------------------------------------------------------------------------
# 定义对话相关
# ------------------------------------------------------------------------------
DIALOG_TYPE_NORMAL			= 0 # 普通对话
DIALOG_TYPE_QUEST			= 1 # 任务对话

# ------------------------------------------------------------------------------
# 技能相关
# ------------------------------------------------------------------------------
# 技能对象类别
SKILL_OBJECT_TYPE_UNKNOWN	= 0
SKILL_OBJECT_TYPE_ENTITY	= 1
SKILL_OBJECT_TYPE_POSITION	= 2

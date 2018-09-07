
#ifndef KBE_HeroManager_H
#define KBE_HeroManager_H
	
// common include	
#include <stdarg.h> 
#include "xml/xml.h"	
#include "common/smartpointer.h"
#include "common/timer.h"
#include "common/singleton.h"

#include "../proxy.h"

//#define NDEBUG
#include <map>	
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#else
// linux include
#endif
	
namespace KBEngine{

	enum hero_status {
		hero_status_idle = 0,    // ¿ÕÏÐ
		hero_status_hire = 1,    // ¹ÍÓ¶±ø
		hero_status_mining = 2,    // ÊØ¿ó
	};

	struct HeroSkillConfig
	{
		uint32 skillid;
		bool Awake;
		uint16 BasicGrowth;// : 12,
		uint16 CasterID;// : 1,
		//CasterName;// : "Coco",
		uint16 CD;// : 0,
		//DisplayName;// : "GUILDAVATAR.GHOST_SHIP",
		//Growth1Field;// : "Basic Num",
		uint16 Growth1Multiplier;// : 1,
		//Growth1Popup;// : "SKILLGROUP.DAMAGE_+_#",
		//Growth1Summary;// : "SKILLGROUP.INCREASE_#_DAMAGE",
		uint16 Growth1Value;// : 15,
		//Growth2Field;//: "Script Arg6",
		uint16 Growth2Multiplier;// : 1,
		//Growth2Popup;// : "SKILLGROUP.HIT_RATE_INCREASED",
		//Growth2Summary;// : "SKILLGROUP.STUN_RATE_INCREASES_WITH_LEVEL_WILL_DEFINITELY_HIT_ENEMIES_OF_LEVEL_#_OR_LOWER",
		uint16 Growth2Value;// : 1,
		uint16 Growth3Multiplier;// : 0,
		uint16 Growth3Value;// : 0,
		uint16 Growth4Multiplier;// : 0,
		uint16 Growth4Value;// : 0,
		uint16 HeroType;// : "STR",
		bool HideOnCard;// : false,
		//Icon;//: "UI/ITEM/s10.png",
		uint8 InitLevel;// : 1,
		bool Interruptable;// : false,
		uint16 LevelupGS;// : 4,
		uint16 MAXVALUE;// : 1277,
		uint16 Priority;// : 3,
		uint16 fRatio;// : 1.25,
		uint16 SkillGroupID;// : 10,
		//SkillName;// : "Coco_ult",
		//SkillTags;// : 
		uint16 Slot;// : 1,
		uint16 Unlock;// : 1,
		uint16 UnlockForMonster;// : 1,

		HeroSkillConfig()
		{
			skillid = 0;
		}
	};

	struct HeroConfig
	{
		uint16 fAGIs[5]; //float * 100
		uint16 fINTs[5]; //float * 100
		uint16 fSTRs[5]; //float * 100

		uint16 fAD;
		uint16 fAGI;
		uint16 AP;
		int16  fARM;
		uint16 ARMP;
		uint16 BasicSkill;
		bool CanAwake;
		bool CanFly;
		uint16 CDR;
		uint16 CollideRadius;
		uint16 CRIT;
		uint16 DODG;
		uint16 DPSStatisticsRatio;
		bool Enable;
		uint8 Gender; //0 male 1: 
		uint16 HEAL;
		uint8 HeroType;  //STRENGTH Á¦Á¿¡¢ÖÇÁ¦¡¢Ãô½Ý
		uint32 HP;
		uint16 HPS;
		uint32 ID;
		uint16  InitialRank;// : 1,
		uint8	InitialStars;// : 1,
		uint16	fINT;// : 16,
		uint16	InterruptHPRatio;// : 0,
		uint16	LFS;// : 0,
		uint8	MainAttrib;// : "STR",
		uint8	MaxStars;// : 5,
		uint16	MCRIT;// : 0,
		uint32  MP;// : 1000,
		uint32  MPGainRate;// : 800,
		uint8	MPType;// : "Rage",
		uint16	MPS;// : 0,
		uint16	MR;// : 0,
		uint16	MRI;// : 0,
		std::string Name;// : "Coco",
		//"Narrative";// : "UNIT.IF_I_SAY_HELLO_TO_YOU_FROM_FAR_AROUND_THAT_MEANS_YOU_WILL_FLY_UP",
		uint8	PeriodGroup;// : 0,
		//"Portrait";// : "UI/HERO/Coco.png",
		//"Portrait Switch";// : "UI/HERO/SwitchCoco.png",
		uint8	PositionType;// : "UNIT.FRONT_ROW",
		//"Puppet";// : "Coco.cha",
		//"Puppet Switch";// : "Coco2.cha",
		//"Script";// : "battle/heroes/Coco",
		uint16	fSTR;// : 21,
		uint8	UnitType;// : "Hero",
		//"Voice Artist";// : "Unit.2.0.1.001",
		//"Voice atk";// : "sound_menu/heroes_voice/voice_Coco_atk.mp3",
		//"Voice atk2";// : "sound_menu/heroes_voice/voice_Coco_atk2.mp3",
		//"Voice Move";// : "sound_menu/heroes_voice/voice_Coco_Walk.mp3",
		//"Voice Ready";// : "sound_menu/heroes_voice/voice_Coco_Ready.mp3",
		//"Voice ult";// : "sound_menu/heroes_voice/voice_Coco_ult.mp3",
		//"Voice Upgrade";// : "sound_menu/heroes_voice/voice_Coco_Cheer.mp3",
		uint16	WalkSpeed;// : 120

		HeroSkillConfig skillConfig[6];
		//std::map<uint32, HeroSkillConfig> skillConfigs;
	};

class HeroManager : public Singleton<HeroManager>
{
public:

	HeroManager();

	~HeroManager();
	
	bool loadConfig(const std::string& configPath);

	HeroConfig* getHeroConfig(DWORD heroId);
	
protected:
	std::map<uint32, HeroConfig> allHerosConfig;
};

}

#endif // KBE_HeroManager_H

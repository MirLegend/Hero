
#ifndef KBE_GameModule_H
#define KBE_GameModule_H
	
// common include	
#include <stdarg.h> 
#include "xml/xml.h"	
#include "common/smartpointer.h"
#include "common/timer.h"
#include "common/singleton.h"

//#define NDEBUG
#include <map>	
// windows include	
#if KBE_PLATFORM == PLATFORM_WIN32
#else
// linux include
#endif
	
namespace KBEngine{
	enum costType {
		coin = 0,   // 金币
		gems = 1,   // 钻石
	};
	struct GlobalParam //全局游戏参数
	{
		uint16 sync_vitality_gap; // = 360,
		uint16 default_normal_sweep_times;// : 10,
		uint16 default_elite_sweep_times;// : 3,
		uint16 pay_sweep_unit_price;// : 1,
		uint16 skill_level_up_chance_cd;// : 300,
		uint16 hero_max_star;// : 5,
		uint16 hero_max_rank;// : 10,
		uint16 tavern_bronze_chance;// : 5,
		uint16 tavern_silver_chance;// : 1,
		uint16 tavern_gold_chance;// : 1,
		uint16 tavern_magic_chance;// : 1,
		uint16 tavern_bronze_cd;// : 600,
		uint32 tavern_silver_cd;// : 86400,
		uint32 tavern_gold_cd;// : 165600,
		uint32 tavern_magic_cd;// : 432000,
		uint16 tavern_magic_month_soul_id;// : 466,
		uint16 universal_fragment_id;// : 335,
		uint16 team_level_max;// : 80,
		uint16 sweep_coin_id;// : 390,
		uint16 stren_health_ratio;// : 19,
		uint16 join_excavate_hero_level_limit;// : 35,
	};
class GameModule : public Singleton<GameModule>
{
public:

	GameModule();

	~GameModule();
	
	bool InitModule();
	bool loadGlobalParam(const std::string& configPath);

	const GlobalParam& getGlobalParam();
protected:
	GlobalParam globalParam_;
};

}

#endif // KBE_GameModule_H

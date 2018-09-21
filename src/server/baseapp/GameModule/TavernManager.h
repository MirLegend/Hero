
#ifndef KBE_TavernManager_H
#define KBE_TavernManager_H
	
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
	enum draw_type {
		single = 0,   // 单抽
		combo = 1,   // 十连抽
		stone = 3,   // 灵魂石抽奖
		drfree = 4,   // 免费单抽
	};
	enum box_type {
	    green           = 1,    // 绿箱子
	    blue            = 2,    // 蓝箱子
	    purple          = 3,    // 紫箱子
	    magicsoul       = 4,    // 神秘宝箱 抽法为combo
	    stone_green     = 5,    // 星际商人 抽法为combo
	    stone_blue      = 6,    // 星际商人 抽法为combo
	    stone_purple    = 7,    // 星际商人 抽法为combo
	};

class TavernManager: public Singleton<TavernManager>
{
public:

	TavernManager();

	~TavernManager();
	
	bool loadConfig(const std::string& filename);
	
protected:
	
};

}

#endif // KBE_TavernManager_H

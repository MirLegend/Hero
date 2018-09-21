
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
		single = 0,   // ����
		combo = 1,   // ʮ����
		stone = 3,   // ���ʯ�齱
		drfree = 4,   // ��ѵ���
	};
	enum box_type {
	    green           = 1,    // ������
	    blue            = 2,    // ������
	    purple          = 3,    // ������
	    magicsoul       = 4,    // ���ر��� �鷨Ϊcombo
	    stone_green     = 5,    // �Ǽ����� �鷨Ϊcombo
	    stone_blue      = 6,    // �Ǽ����� �鷨Ϊcombo
	    stone_purple    = 7,    // �Ǽ����� �鷨Ϊcombo
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

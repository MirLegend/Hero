#include "HeroManager.h"
#include <sstream>
#include "json/json.h"

namespace KBEngine{
KBE_SINGLETON_INIT(HeroManager);

//-------------------------------------------------------------------------------------
HeroManager::HeroManager()
{
}

//-------------------------------------------------------------------------------------
HeroManager::~HeroManager()
{
}

bool HeroManager::loadConfig(const std::string& configPath)
{
	std::string filename = configPath + "Unit.json";
	Json::Reader reader;// 解析json用Json::Reader   
	Json::Value root; // Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array         

	std::ifstream is;
	is.open(filename, std::ios::binary);
	if (reader.parse(is, root, FALSE))
	{
		std::string code;
		
		int hero_size = root.size();  // 得到"files"的数组个数
		printf("HeroManager::loadConfig %d\n", hero_size);
		Json::Value::Members members = root.getMemberNames();
		for (int i = 0; i < hero_size; ++i)  // 遍历数组  
		{
			uint32 heroid = atoi(members[i].c_str());
			Json::Value& hero = root[members[i].c_str()];
			
			HeroConfig& heroConfig = allHerosConfig[heroid];
			heroConfig.InitialStars = hero.get("Initial Stars", "1").asInt();
			heroConfig.InitialRank = hero.get("Initial Rank", "1").asInt();
			
			printf("HeroManager::heroid %d, artname:%s,  initstars:%d  \n", heroid, hero.get("Art Name", "default").asString().c_str()
				, heroConfig.InitialStars);
			/*heroConfig.
			Json::Value val_image = root[i]["images"];
			int image_size = val_image.size();
			for (int j = 0; j < image_size; ++j)
			{
			std::string type = val_image[j]["type"].asString();
			std::string url = val_image[j]["url"].asString();
			printf("type : %s, url : %s \n", type.c_str(), url.c_str());
			}*/
		}
	}
	else
	{
		ERROR_MSG(fmt::format("HeroManager.loadConfig error file:{}", filename));
		is.close();
		return false;
	}
	is.close();

	filename = configPath + "SkillGroup.json";
	is.open(filename, std::ios::binary);
	if (reader.parse(is, root, FALSE))
	{
		std::string code;

		int hero_size = root.size();  // 得到"files"的数组个数
		printf("HeroManager::skillgroups %d\n", hero_size);
		Json::Value::Members members = root.getMemberNames();
		for (int i = 0; i < hero_size; ++i)  // 遍历数组  
		{
			uint32 heroid = atoi(members[i].c_str());
			Json::Value& heroskills = root[members[i].c_str()];
			HeroConfig* pHeroConfig = getHeroConfig(heroid);
			if (!pHeroConfig)
			{
				continue;
			}
			int skill_size = heroskills.size();  // 得到"files"的数组个数
			//printf("HeroManager::skillgroups %d\n", heroskills);
			int j = 0;
			for (; j < skill_size && j<4; j++)
			{
				Json::Value::Members skillmembers = heroskills.getMemberNames();
				uint32 skillid = atoi(skillmembers[j].c_str());
				Json::Value& heroskill = heroskills[skillmembers[j].c_str()];
				HeroSkillConfig& skillConfig = pHeroConfig->skillConfig[j];
				skillConfig.skillid = skillid;
				///
				skillConfig.InitLevel = heroskill.get("Init Level", "1").asInt();
			}
			printf("HeroManager::hero:%d, skillsize:%d\n", heroid, j);
		}
	}
	else
	{
		ERROR_MSG(fmt::format("HeroManager.loadConfig error file:{}", filename));
		is.close();
		return false;
	}
	is.close();
	return true;
}

//-------------------------------------------------------------------------------------
HeroConfig* HeroManager::getHeroConfig(DWORD heroId)
{
	std::map<uint32, HeroConfig>::iterator it = allHerosConfig.find(heroId);
	if (allHerosConfig.end() == it)
	{
		return NULL;
	}
	return &it->second;
}

//-------------------------------------------------------------------------------------
}

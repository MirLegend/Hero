
#include "GameModule.h"
#include <sstream>
#include "resmgr/resmgr.h"
#include "TavernManager.h"
#include "HeroManager.h"
#include "json/json.h"

namespace KBEngine{
	KBE_SINGLETON_INIT(GameModule);

//-------------------------------------------------------------------------------------
GameModule::GameModule()
{
}

//-------------------------------------------------------------------------------------
GameModule::~GameModule()
{
}

bool GameModule::InitModule()
{
	std::string configPath = Resmgr::getSingleton().getPySysResPath() + "gamemodule/";

	if (!loadGlobalParam(configPath))
	{
		return false;
	}

	new TavernManager();
	if (!TavernManager::getSingleton().loadConfig(configPath))
	{
		return false;
	}
	
	new HeroManager();
	if (!HeroManager::getSingleton().loadConfig(configPath))
	{
		return false;
	}
	return true;
}

bool GameModule::loadGlobalParam(const std::string& configPath)
{
	std::string filename = configPath + "parameterTable.json";
	Json::Reader reader;// 解析json用Json::Reader   
	Json::Value root; // Json::Value是一种很重要的类型，可以代表任意类型。如int, string, object, array         

	std::ifstream is;
	is.open(filename, std::ios::binary);
	if (reader.parse(is, root, FALSE))
	{
		globalParam_.sync_vitality_gap = root.get("sync_vitality_gap", "360").asInt();
		globalParam_.default_normal_sweep_times = root.get("default_normal_sweep_times", "10").asInt();
		globalParam_.default_elite_sweep_times = root.get("default_elite_sweep_times", "3").asInt();
		globalParam_.pay_sweep_unit_price = root.get("pay_sweep_unit_price", "1").asInt();
		globalParam_.skill_level_up_chance_cd = root.get("skill_level_up_chance_cd", "300").asInt();
		globalParam_.hero_max_star = root.get("hero_max_star", "5").asInt();
		globalParam_.hero_max_rank = root.get("hero_max_rank", "10").asInt();
		globalParam_.tavern_bronze_chance = root.get("tavern_bronze_chance", "5").asInt();
		globalParam_.tavern_silver_chance = root.get("tavern_silver_chance", "1").asInt();
		globalParam_.tavern_gold_chance = root.get("tavern_gold_chance", "1").asInt();
		globalParam_.tavern_magic_chance = root.get("tavern_magic_chance", "1").asInt();
		globalParam_.tavern_bronze_cd = root.get("tavern_bronze_cd", "600").asInt();
		globalParam_.tavern_silver_cd = root.get("tavern_silver_cd", "86400").asInt();
		globalParam_.tavern_gold_cd = root.get("tavern_gold_cd", "165600").asInt();
		globalParam_.tavern_magic_cd = root.get("tavern_magic_cd", "432000").asInt();
		globalParam_.tavern_magic_month_soul_id = root.get("tavern_magic_month_soul_id", "466").asInt();
		globalParam_.universal_fragment_id = root.get("universal_fragment_id", "335").asInt();
		globalParam_.team_level_max = root.get("team_level_max", "80").asInt();
		globalParam_.sweep_coin_id = root.get("sweep_coin_id", "390").asInt();
		globalParam_.stren_health_ratio = root.get("stren_health_ratio", "19").asInt();
		globalParam_.join_excavate_hero_level_limit = root.get("join_excavate_hero_level_limit", "35").asInt();
	}
	else
	{
		ERROR_MSG(fmt::format("GameModule::loadGlobalParam error file:{}", filename));
		is.close();
		return false;
	}
	is.close();
	return true;
}

const GlobalParam& GameModule::getGlobalParam()
{
	return globalParam_;
}

//-------------------------------------------------------------------------------------
}

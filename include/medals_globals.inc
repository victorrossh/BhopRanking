#define USE_RANKING 0

#if USE_RANKING
#include <ranking>
#endif

#define DEBUG 0

#define MAX_CATEGORIES 34
#define TASK_ID 4832

#define MENU_PREFIX "\r[FWO] \d- \w"

new bronze[3] = {205, 127, 50};
new silver[3] = {192, 192, 192};
new gold[3]   = {255, 215, 0};

enum eMedalInfo{
	iMedalCategory,
	Float:fMedalTime,
	iMedalType,
	iMedalReward
};

enum eMedalCompleted{
	bool:bMedalBronze = 0,
	bool:bMedalSilver,
	bool:bMedalGold,
}

new Array:g_aMedals;

new g_bMedalsCompleted[MAX_PLAYERS][MAX_CATEGORIES][eMedalCompleted];

new Float:g_fStartTime[MAX_PLAYERS];

new bool:g_bMedalsEnabled;

new g_szMapName[64];

new g_iVault;
new g_iHudSync;
new bool:g_bShowHud[MAX_PLAYERS];

new Trie:g_tMedalsText;

stock format_time_float(output[], len, Float:time)
{
	new minutes, seconds, centiseconds;

	minutes = floatround(time / 60.0, floatround_floor);
	seconds = floatround(time, floatround_floor) % 60;

	centiseconds = floatround((time - floatround(time, floatround_floor)) * 100.0);

	formatex(output, len, "%02d:%02d.%02d", minutes, seconds, centiseconds);
}


stock get_medal_name(id, buffer[], length)
{
	switch(id)
	{
		case 0: formatex(buffer, length, "%L", LANG_PLAYER, "MEDAL_BRONZE");
		case 1: formatex(buffer, length, "%L", LANG_PLAYER, "MEDAL_SILVER");
		case 2: formatex(buffer, length, "%L", LANG_PLAYER, "MEDAL_GOLD");
	}
}
public CategoriesMenu(id)
{
	if(!g_bMedalsEnabled){
		CC_SendMessage(id, "%L", id, "NO_MAP_MEDALS");
		return PLUGIN_HANDLED;
	}

	new title[128];
	new temp_medal[eMedalInfo];
	new bool:catItem[MAX_CATEGORIES];
	new catName[32];
	new szData[4];
	new size = ArraySize(g_aMedals);

	formatex(title, charsmax(title), "%L", id, "MEDALS_MAIN_MENU_TITLE", MENU_PREFIX, g_szMapName);
	new menu = menu_create(title, "categories_menu_handler");
	
	for(new i=0;i<size;i++){
		ArrayGetArray(g_aMedals, i, temp_medal);
		if(catItem[temp_medal[iMedalCategory]]) continue;

		get_category_name(temp_medal[iMedalCategory], catName, charsmax(catName));
		format(szData, charsmax(szData), "%d", temp_medal[iMedalCategory]);
		menu_additem(menu, catName, szData, 0);

		catItem[temp_medal[iMedalCategory]] = true;
	}

	formatex(title, charsmax(title), "%L", id, "MENU_BACK");
	menu_setprop(menu, MPROP_BACKNAME, title);

	formatex(title, charsmax(title), "%L", id, "MENU_NEXT");
	menu_setprop(menu, MPROP_NEXTNAME, title);

	formatex(title, charsmax(title), "%L", id, "MENU_EXIT");
	menu_setprop(menu, MPROP_EXITNAME, title);
	
	menu_display(id, menu, 0);
	return PLUGIN_HANDLED;
}

public categories_menu_handler(id, menu, item)
{
	if (item == MENU_EXIT)
	{
		menu_destroy(menu);
		return PLUGIN_CONTINUE;
	}


	new cat;
	new itemInfo[4], szItemName[12];
	new _access, item_callback;

	menu_item_getinfo( menu, item, _access, itemInfo, charsmax( itemInfo ), szItemName ,charsmax( szItemName ), item_callback );
	cat = str_to_num(itemInfo);

	MedalsMenu(id, cat);
	
	menu_destroy( menu );
	return PLUGIN_HANDLED;
}

public MedalsMenu(id, cat)
{
	new temp_medal[eMedalInfo], size, medal_name[32];
	size = ArraySize(g_aMedals);
	new text[128];
	new time[16];
	new title[128];

	new catName[32];
	get_category_name(cat, catName, charsmax(catName));

	formatex(title, charsmax(title), "%L", id, "MEDALS_MENU_TITLE", MENU_PREFIX, g_szMapName, catName);
	
	new menu = menu_create(title, "menu_handler");

	for(new i=0;i<size;i++){
		ArrayGetArray(g_aMedals, i, temp_medal);
		if(temp_medal[iMedalCategory] != cat) continue;
		
		format_time_float(time, charsmax(time), temp_medal[fMedalTime]);
		get_medal_name(temp_medal[iMedalType], medal_name, charsmax(medal_name));

		//Formatex bugged, need fix later
		formatex(text, charsmax(text), "%L", id, "MEDAL_MENU_ITEM", medal_name, time, temp_medal[iMedalReward], g_bMedalsCompleted[id][cat][temp_medal[iMedalType]] ? "%L" : "", id, "MEDAL_MENU_COMPLETED");
		menu_additem(menu, text, "", 0);
	}
	formatex(title, charsmax(title), "%L", id, "MENU_BACK");
	menu_setprop(menu, MPROP_EXITNAME, title);
	
	menu_display(id, menu, 0);
	return PLUGIN_HANDLED;
}

public menu_handler(id, menu, item)
{
	if (item == MENU_EXIT)
	{
		menu_destroy(menu);
		CategoriesMenu(id);
		return PLUGIN_CONTINUE;
	}

	menu_destroy( menu );
	return PLUGIN_HANDLED;
}
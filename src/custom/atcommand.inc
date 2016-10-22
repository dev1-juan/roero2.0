// Copyright (c) Athena Dev Teams - Licensed under GNU GPL
// For more information, see LICENCE in the main folder

/**
 * Custom Atcommands
 * Place the body of custom atcommands in this file.
 * Format:
 *	ACMD_FUNC(command_name)
 *	{
 *		<code>;
 *	}
 **/

//ACMD_FUNC(newcommand)
//{
//	clif_displaymessage(fd, "It works!");
//	clif_specialeffect(&sd->bl, 343, AREA);
//	return 0;
//}

ACMD_FUNC(emotion)
{
	struct s_mapiterator* iter;
	char map_name[MAP_NAME_LENGTH_EXT];
	unsigned short mapindex;
	int m = -1,emotion=0;

	if (!message || !*message ||
		(sscanf(message, "%d %15s", &emotion, map_name) < 2)) {		 
			clif_displaymessage(fd, "Please, enter a emotion and a map (usage: @emotion <emotion number> <map name>).");
			return -1;
	}

	mapindex = mapindex_name2id(map_name);
	if (mapindex)
		m = map_mapindex2mapid(mapindex);


	iter = mapit_getallusers();
	while( true )
	{
		struct map_session_data* sd2 = (struct map_session_data*)mapit_next(iter);
		if( sd2 == NULL)
			break;// no more users

		if(sd2->bl.m != m)
			continue;

		clif_emotion(&sd2->bl, emotion);
	}
	mapit_free(iter);
	clif_displaymessage(fd,"Emotion sent to all players in the map");
	return 0;
}


/*==========================================
* @afk / @logout
*------------------------------------------*/
ACMD_FUNC(logout) {
 
        nullpo_retr(-1, sd);
				
				if(sd->bl.m == map_mapname2mapid("poring_w02")) {
				clif_displaymessage(fd, "@afk is not allowed on this map.");
				return 0;
				}
				
				if( pc_isdead(sd) ) {
				clif_displaymessage(fd, "Cannot @afk if you are dead.");
				return -1;
				}

                if( map[sd->bl.m].flag.autotrade == battle_config.autotrade_mapflag )
                {

                if(map[sd->bl.m].flag.pvp  || map[sd->bl.m].flag.gvg){
                clif_displaymessage(fd, "You may not use the @afk maps PVP or GVG.");
                return -1;}

                        sd->state.autotrade = 1;
                        sd->state.monster_ignore = 1;
			 			 pc_setsit(sd);
                        skill_sit(sd,1);
                        clif_sitting(&sd->bl);
                        clif_specialeffect(&sd->bl, 234,AREA);                       
                        clif_authfail_fd(fd, 15);
                } else
                        clif_displaymessage(fd, "@afk is not allowed on this map.");
        return 0; 
}
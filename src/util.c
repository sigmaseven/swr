#include <sys/types.h>
#include <sys/time.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include "mud.h"

int get_stat_bonus(int stat)
{
	if(stat < 2)
		return(0);
	if(stat < 4)
		return(1);
	if(stat < 6)
		return(2);
	if(stat < 8)
		return(3);
	if(stat < 10)
		return(4);
	if(stat < 12)
		return(5);
	if(stat < 14)
		return(6);
	if(stat < 16)
		return(7);
	if(stat < 18)
		return(8);
	if(stat < 20)
		return(9);
	if(stat > 20)
		return(10);

	return(0);
}

int get_character_defence(CHAR_DATA *ch)
{
	// Make sure character is awake
	if((ch)->position > POS_SLEEPING)
	{
		int dex_modifier = get_stat_bonus(ch->perm_agi);
		int equipment_defense = ch->armor;

		return(10 + dex_modifier + equipment_defense);
	}
	else
	{
		return(0);
	}
}

int count_room_objects(ROOM_INDEX_DATA *room)
{
	OBJ_DATA *object;
	int count = 0;
	for(object = room->first_content; object; object = object->next_content)
	{
		count += object->count;
	}
	return count;
}

int count_room_mobs(ROOM_INDEX_DATA *room)
{
	int count = 0;
	CHAR_DATA *ch;
	for(ch = room->first_person; ch; ch = ch->next_in_room)
	{
		if(IS_NPC(ch))
		{
			count++;
		}
	}
	return count;
}

int count_room_players(ROOM_INDEX_DATA *room)
{
	int count = 0;
	CHAR_DATA *ch;
	for(ch = room->first_person; ch; ch = ch->next_in_room)
	{
		if(!IS_NPC(ch))
		{
			count++;
		}
	}
	return count;
}

int count_area_rooms(AREA_DATA *area)
{
	ROOM_INDEX_DATA *room;
	int count = 0;

	for(room = area->first_room; room; room = room->next_aroom)
	{
		count++;
	}

	return count;
}
int count_area_mobs(AREA_DATA *area)
{
	ROOM_INDEX_DATA *room;
	int count = 0;
	for(room = area->first_room; room; room = room->next_aroom)
	{
		count += count_room_mobs(room);
	}
	return count;
}

int count_area_objects(AREA_DATA *area)
{
	ROOM_INDEX_DATA *room;
	int count = 0;
	for(room = area->first_room; room; room = room->next_aroom)
	{
		count += count_room_objects(room);
	}
	return count;
}

int count_area_players(AREA_DATA *area)
{
	ROOM_INDEX_DATA *room;
	int count = 0;
	for(room = area->first_room; room; room = room->next_aroom)
	{
		count += count_room_players(room);
	}
	return count;
}

void generate_random_loot(ROOM_INDEX_DATA *room)
{
	int object_count = count_room_objects(room);
	printf("Loot randomizer: counted %d items in room %d.\n", object_count, room->vnum);
	if(object_count <= 10)
	{
		int num_items = 10 - object_count;
		int i;

		for(i = 0; i < num_items; i++)
		{
			printf("Creating object in room %d.\n", room->vnum);
			int roll = 0;
			roll = number_range( 1, 20 );
			OBJ_DATA *tmp_obj;
			tmp_obj = create_object(get_obj_index(50),0);
			obj_to_room(tmp_obj, room);
//			switch(roll)
//			{
//				case 19:
//				case 20:
//			}
		}
	}
}

int get_area_low_mob_vnum(AREA_DATA *area)
{
	return area->low_m_vnum;
}

int get_area_high_mob_vnum(AREA_DATA *area)
{
	return area->hi_m_vnum;
}

void generate_random_mobs(AREA_DATA *area)
{
	int low_vnum  = get_area_low_mob_vnum(area);
	int high_vnum = get_area_high_mob_vnum(area);
	int num_mobs  = number_range(0, 2);
	int x;
	ROOM_INDEX_DATA *room;

	for(room = area->first_room; room; room = room->next_aroom)
	{

		for(x = 0; x < num_mobs; x++)
		{
			int roll = number_range(low_vnum, high_vnum);
			printf("got vnum %d", roll);
		}
	}
}

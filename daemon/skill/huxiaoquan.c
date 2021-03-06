// huxiaoquan.c 【虎啸皇拳】

#include <ansi.h>

inherit SKILL;

mapping *action = ({
	([	"action":		"$N一抖手，使出一招"HIR"「一啸红尘惊」"NOR"，瞬间刺出三十六指，$n顿时手忙脚乱，分不清虚实",
		"dodge":		10,
		"parry":		10,
		"force":		160,
		"damage_type":	"刺伤",
                        "weapon":		"右手食指",
	]),
	([	"action": 		"$N一掌击向$n，使出一招"HIC"「再啸湖海翻」"NOR"，$n急忙向旁边一闪，\n不料$N一运劲儿，手突然弯了过来，转而击向$n的$l",
		"dodge":		5,
		"parry":		-15,
		"force":		180,
		"damage_type":	"内伤",
                        "weapon":		"右手",
	]),
	([	"action":		"$N左手连续划出几个光环，一阵吸力带得$n向前踏出一步，$N左手剑指已刺向$n的$l，正是一招"HIB"「三啸鬼神辟」"NOR,
		"dodge":		5,
		"parry":		10,
		"force":		100,
		"damage_type":	"刺伤",
                        "weapon":		"左手食指",
	]),
	([  	"action": 		HIR"第四招"HIW"「绝啸穹苍灭」"HIW"，$N一转身，背向$n，手从腋下反手刺向$n的$l"NOR,
                "dodge":                -50,
                "parry":                -50,
                "force":                220,
                "damage_type":  "内伤",
                        "weapon":		"左手食指",
	 ]),
});

int valid_learn(object me)
{
	
	if( me->query_temp("weapon") || me->query_temp("secondary_weapon") )
		return notify_fail("练虎啸皇拳必须空手。\n");
	return 1;
}

int valid_enable(string usage)
{
	return usage=="unarmed";
}

mapping query_action(object me, object weapon)
{
	return action[random(sizeof(action))];
}

int practice_skill(object me)
{
        if( (int)me->query("kee") < 100
        ||      (int)me->query("force") < 30 )
                return notify_fail("你的内力或气不够，没有办法练习虎啸皇拳。\n");
        me->receive_damage("kee", 30);
        me->add("force", -5);
//        write("你按着所学练了一遍虎啸皇拳。\n");
        return 1;

}

string perform_action_file(string func)
{
return CLASS_D("sanjie") + "/huxiaoquan/" + func;
}

int stage(int level)
{
	if( level <60 ) return 1;
	else if ( level < 120 ) return 2;
	else if ( level < 180 ) return 3;
	else return 4;
}

string level_description(int level)
{
	if ( stage(level) < 1 )
		return HIR "第"+chinese_number( stage(level) )+"层　" NOR;
	else if ( stage(level) < 2 )
		return HIC "第"+chinese_number( stage(level) )+"层　" NOR;
	else if ( stage(level) < 3 )
		return HIB "第"+chinese_number( stage(level) )+"层　" NOR;
	else 
		return HIW "第"+chinese_number( stage(level) )+"层　" NOR;
}

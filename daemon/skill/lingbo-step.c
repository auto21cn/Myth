//【凌波微步】
// lingbo-step.c

#include <ansi.h>
inherit SKILL; 

string type() { return "dodge"; }
string *dodge_msg = ({
     "$n一招"BLINK" + "HIW"「轻衣胜雪踏凌波」"NOR"，$N只觉一个影子晃过，却不见了$n的身影。\n",
     "$n一招"BLINK" + "CYN"「弹剑击筑且作歌」"NOR"，身体微微前倾，轻笑间已避开了$N这一招。\n",
     "只见$n脚下快步不停，一招"BLINK" + "HIR"「三千红尘青丝断」"NOR"，$N眼睛一花，站在原地不知道如何是好。\n",
     "$n可是$n一个"BLINK" + "HIM"「长安道上对月酌」"NOR"，长袖翻飞，躲过$N这一招。\n",
     "$n息气上升，意存玉枕，一招"BLINK" + "HIB"「永夜拋人何处去」"NOR"，身子飘然而起。\n",
     "$n微微一笑，一招"BLINK" + "HIY"「苦求乐土坠尘穹」"NOR"，身如幻影，快如旋风，瞬间已站在了$N身后。\n",
     "$n一招"BLINK" + "MAG"「犹带昭阳日影来」"NOR"，凌空一个跟头翻身落在$N身后。\n",});

int valid_enable(string usage) { return (usage=="dodge"); }

int valid_learn(object me)
{
        if( (int)me->query("spi") < 20 )
             return notify_fail("你的灵性不够。\n");

        return 1;
}

string query_dodge_msg(string limb)
{
        return dodge_msg[random(sizeof(dodge_msg))];
}

int practice_skill(object me)
{
        if( (int)me->query("sen") < 20 )
                return notify_fail(WHT"你的精神太差了，不能练【凌波微步】。\n"NOR);
        me->add("sen", -15); 
        me->add("qi",-5);        return 1;
}




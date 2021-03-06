// lianxin-force.c  【怜心心法】by cigar 2002.01

#include <ansi.h>

inherit FORCE;

int valid_enable(string usage) { return usage=="force"; }

int valid_learn(object me) { return 1; }

int practice_skill(object me)
{
        return notify_fail("怜心心法只能向师父学，或是从运用(exert)中增加熟练度。\n");
}
string exert_function_file(string func)
{
        return CLASS_D("youning") + "/lianxin-force/" + func;
}

int stage(int level)
{
        if( level <61 ) return 1;
        else if ( level < 100 ) return 2;
        else if ( level < 160 ) return 3;
        else if ( level < 220 ) return 4;
        else if ( level < 300 ) return 5;
        else if ( level < 400 ) return 6;
        else if ( level < 520 ) return 7;
        else if ( level < 660 ) return 8;
        else return 9;
}

string level_description(int level)
{
        if ( stage(level) < 3 )
                return BLU "第"+chinese_number( stage(level) )+"层　" NOR;
        else if ( stage(level) < 5 )
                return HIB "第"+chinese_number( stage(level) )+"层　" NOR;
        else if ( stage(level) < 7 )
                return YEL "第"+chinese_number( stage(level) )+"层　" NOR;
        else if ( stage(level) < 9 )
                return CYN "第"+chinese_number( stage(level) )+"层　" NOR;
        else 
                return HIW "第"+chinese_number( stage(level) )+"层　" NOR;
}

void skill_improved(object me)
{
        //if stage increased, give bonus...?
        int level = (int)me->query_skill("lianxin-force", 1);
        if ( stage(level) == stage(level-1) + 1)
        {
                //this is to prevent ppls from abondoning skill to get bonus.
                if( (int)me->query("lianxin-force_bonus") < stage(level) )
                {
                        me->set("lianxin-force_bonus", stage(level));
                        me->set("max_force", (int)me->query("max_force") + stage(level)*50 );
                        // mon 12/13/98
                        me->set("maximum_force", 
                                (int)me->query("maximum_force") 
                                + stage(level)*50 );
                        me->save();
                        log_file("lianxin-force-bonus", ctime( time() )+": "
                                +me->query("name")+"("+me->query("id")+")"
                                +" got neili "+(stage(level)*50)+".\n");
                        message_vision(HIB "$N突然觉得心中无盼，飘飘然。原来是$N的怜心心法进入了第"+chinese_number(stage(level))+"层境界！\n" NOR, me);

                }
        }
                        
}

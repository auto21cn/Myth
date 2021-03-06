//hellupdate.c
#include <skill.h>

inherit F_CLEAN_UP;
mapping hskill=([
                    "sword":"剑术", "blade":"刀法",
                    "hammer":"大锤法","staff":"魔杖术",
                    "whip":"鞭术","axe":"大斧术",
                    "fork":"叉术","spear":"枪术",
                    "mace":"锏法","stick":"棍术",
                    "unarmed":"拳腿术","dodge":"敏捷术",
 ]);
void create() { seteuid(getuid()); }
     


int main(object me, string skill)
{
        
        
        int  my_skill, cost,upper,amount;

        if(!skill) return notify_fail
                    ("指令格式：hellupdate <技能>\n");

       if(sscanf(skill, "check %s", skill)==1 ) 
           {
                 if(undefinedp(hskill[skill]))
                      return notify_fail ("没有这个技能！\n");
              my_skill =me->query("hell_skill/"+skill);
              cost=(my_skill*my_skill+20)*5;
              return notify_fail  ("如果你升一级"+hskill[skill]+"，此升级需要"+cost+"点技能升级点！\n");
           
           }
        if(undefinedp(hskill[skill])) 
            return notify_fail ("没有这个技能！\n");
       
        if( me->is_fighting() )
                return notify_fail("临阵磨枪？来不及啦。\n");

        if(me->is_busy())
            return notify_fail("你正忙着呢。\n");

        amount=me->query("hell_pot");
        
           if(amount<=0)
                return notify_fail("你的技能升级点已经使用完了，没有办法再升级了。\n");
        my_skill =me->query("hell_skill/"+skill);
        cost=(my_skill*my_skill+20)*5;
        if(my_skill>100) cost =cost*3;
        if(amount<cost)
                return notify_fail  ("你的技能升级点不足于升级"+hskill[skill]+"，此升级需要"+cost+"点技能升级点！\n");
        upper=(my_skill * my_skill  +10)*50;
        if(me->query("hell_exp")<upper)
                     return notify_fail
                     ("你的地狱经验不足于升级"+hskill[skill]+"，此升级需要"+upper+"点经验！\n");

        me->add("hell_skill/"+skill,1);
        me->add("hell_pot",- cost);
        me->start_busy(5);
         return notify_fail("你的"+hskill[skill]+"升了一级！\n");
}

int help(object me)
{
        write(@HELP
指令格式 : hellupdate <技能>         查看格式： hellupdate check <技能>
 
这个指令可以让你升级地狱火的一些基本技能的指令。需要一定的地狱火技能升级点。

至于如何知道你想了解升级那些什么技能，可以用 hellscore 指令直接查看，建议第
一次升级dodge。

其他相关指令 : hellscore
HELP
        );
        return 1;
}



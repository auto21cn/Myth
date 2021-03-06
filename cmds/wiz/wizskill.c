// wizskill.c
// by mudring

inherit F_CLEAN_UP;
#include <ansi.h>

int main(object me, string arg)
{
    string objname, family;
    object obj;
    int level;
    object weapon;

    if (!SECURITY_D->valid_grant(me, "(wizard)")) 
         return 0; 

    seteuid(getuid());

    if (!arg)
        return notify_fail("指令格式：wizskill <物件> <级别> <门派>\n");

    if (sscanf(arg, "%s %d %s", objname, level, family) != 3)
        return notify_fail("指令格式：wizskill <物件> <级别> <门派>\n");

    obj = present(objname, environment(me));
    if (!obj) obj = find_player(objname);
    if (!obj) obj = find_living(objname);
    if (!obj) return notify_fail("没有这个人！\n");

    if (!userp(obj))
        return notify_fail("你没有直接呼叫这个物件的函数的权力。\n");

    if (userp(obj) && !wizardp(obj))
        return notify_fail("你没有直接呼叫这个物件的函数的权力。\n");

    if ((obj != me) && !is_root(me))
        return notify_fail("你没有直接呼叫这个物件的函数的权力。\n");

    if (!STATU_D->valid_family(family))
        return notify_fail("请先检验有没有这个门派。\n");

    STATU_D->set_npc_skill(obj, level, family);
    weapon = STATU_D->family_weapon(family);
    weapon->move(obj);
    weapon->wield();
    write(WHT "wizskill " + getuid(obj) + " " + level +" " + family + " ok!\n"NOR);
    if (me == obj)
        message_vision(HIY "$N" HIY "口中念念有词：天灵灵地怜怜"
            "搞了半天不如检个破风铃。\n" NOR, me);
    else
        message_vision(HIY "$N" HIY "口中念念有词：天灵灵地怜怜"
            "搞了半天不如检个破风铃。\n" NOR, me, obj);

    seteuid(getuid(me));
    return 1;
}

int help(object me)
{
write(@HELP
指令格式 : wizskill <物件> <级别> <门派>

HELP
    );
    return 1;
}


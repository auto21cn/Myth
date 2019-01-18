//龙影枪
//by junhyun@SK

#include <weapon.h>
//  inherit F_UNIQUE;

inherit SPEAR;
#include <ansi.h>
void create()
{
        set_name(HIG"龙影枪"NOR, ({"longying qiang","spear","qiang"}));
        set_weight(5000);
if( clonep() )
                set_default_object(__FILE__);
        else {
set("long","一把刻有龙纹的银枪。\n");
                set("unit", "根");
                set("value", 12000);
                set("wield_msg",HIW "$N从枪套中抽出一根闪闪发光的银枪\n"NOR);
                set("unwield_msg",HIW "$N将手中的龙影枪插入枪套.\n");
                set("no_sell","你大脑有问题吧？这东西你都敢卖？\n"); 
                set("no_drop","去垃圾堆丢吧，乱扔会污染环境!\n"); 

                set("weapon_prop/courage", 20);
                }
        init_spear(120);
        setup();
}
mixed hit_ob(object me, object victim)
{
    int damage_bonus = 0;
    
    if( (string)me->query("family/family_name") == "将军府"
                && me->query_skill("bawang-qiang",1) > 1)
    damage_bonus = me->query_skill("bawang-qiang",1);
    damage_bonus = (damage_bonus+random(damage_bonus))/2;

    victim->receive_wound("kee",damage_bonus);
    return HIB"龙影枪上隐隐显出一条龙形。\n" NOR;

}


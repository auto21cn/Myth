//���½�
//by junhyun@SK

#include <weapon.h>
//  inherit F_UNIQUE;

inherit SWORD;
#include <ansi.h>
void create()
{
        set_name(HIG"���½�"NOR, ({"lingyue sword","sword","jian"}));
        set_weight(5000);
if( clonep() )
                set_default_object(__FILE__);
        else {
set("long","����ң��������\n");
                set("unit", "��");
                set("value", 12000);
                set("wield_msg",HIG "$N�ӱ�����һ����������ı�����\n"NOR);
                set("unwield_msg",HIW "$N΢΢һЦ,��������ر���Ľ�����.\n");
                set("no_sell","�����������ɣ��ⶫ���㶼������\n"); 
                set("no_drop","ȥ�����Ѷ��ɣ����ӻ���Ⱦ����!\n"); 

                set("weapon_prop/courage", 20);
                }
        init_sword(120);
        setup();
}
mixed hit_ob(object me, object victim)
{
    int damage_bonus = 0;
    
    if( (string)me->query("family/family_name") == "��ɽ����"
                && me->query_skill("shushan-jianfa",1) > 1)
    damage_bonus = me->query_skill("shushan-jianfa",1);
    damage_bonus = (damage_bonus+random(damage_bonus))/2;

    victim->receive_wound("kee",damage_bonus);
    return HIG"���½���ɢ���������鶯֮����\n" NOR;

}


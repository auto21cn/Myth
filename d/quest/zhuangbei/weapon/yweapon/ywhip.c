#include <weapon.h>
inherit WHIP;
#include <ansi.h>

void setname() 
{ 
        mapping name;
        name=__DIR__"name"->random_name("whip");
        set_name(HIY+name["name"]+NOR, name["id"]);  
} 

void create()
{
        string str = "";
        setname(); 
        set_weight(4500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "条");
                set("value", 10000);
                set("wield_msg", "$N左手一甩，一条蛇型皮鞭绕腰而出！\n");
                set("unwield_msg", "$N把手中$n缠回腰间。\n");                
                if(random(10)>6)
                        set("weapon_prop/sen", 200+random(500));
                if(random(10)<2)
                        add("weapon_prop/armor_vs_force",10+random(10));
                if(random(20)>15)
                        set("weapon_prop/kee", 200+random(500));                
                set("level_quest",50);
        }
        set("inset_hole",2);
        init_whip(100+random(60));
        if(random(10)>8)
                add("weapon_prop/damage",this_object()->query("weapon_prop/damage")/4);
        if(this_object()->query("inset_hole"))
                str += "一条长长的鞭子，上面沾满了血，装备等级50。\n"+"它身上有"+this_object()->query("inset_hole")+"个可镶嵌宝石的孔。\n"; 
        else
                str += "一条长长的鞭子，上面沾满了血，装备等级50。\n"+"它身上没有可镶嵌宝石的孔。\n"; 
        if(this_object()->query("weapon_prop/sen"))
                str += "装备它可增加"+this_object()->query("weapon_prop/sen")+"点精神。\n";
        if(this_object()->query("weapon_prop/armor_vs_force")) 
                str += "增加"+this_object()->query("weapon_prop/armor_vs_force")+"点内功抵抗力。\n";
        if(this_object()->query("weapon_prop/kee")) 
                str += "增加"+this_object()->query("weapon_prop/kee")+"点气血。\n";
        set("long",str);
        setup();
}

void init()
{
        add_action("do_wield","wield");
}

int do_wield(string arg) 
{  
        object ob = this_object();
        object me = this_player();
        if(arg == ob->query("id") || arg == "whip" ){
                if(me->query("level")<50){
                        write("你的等级不够，无法装备这件兵器。\n");
                        return 1;
                }  
        }   
        return 0;  
}   

mixed hit_ob(object me, object victim, int damage_bonus)
{
        int diff;
        if( damage_bonus < 0 ) return 0;
        diff = random((int)me->query("force_factor")+1) - random((int)victim->query("force_factor")/2+1);

        if(diff > 0){
                victim->apply_condition("lvbo_poison", 2*(diff + (int)victim->query_condition("lvbo_poison")) );
                message_vision("$N只觉身上一凉，发现已然中了对手一记危险的攻击。\n", victim);
        }
        else 
                message_vision("$N觉得一阵寒意袭来，好险，差点被对手命中要害！\n", victim);
}

int query_autoload() 
{ 
        object me = this_player();
        if(me->query("level") >= this_object()->query("level_quest"))
        return 1; 
}  

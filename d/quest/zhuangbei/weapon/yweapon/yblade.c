#include <weapon.h>
inherit BLADE;
#include <ansi.h>

void setname() 
{ 
        mapping name;
        name=__DIR__"name"->random_name("blade");
        set_name(HIY+name["name"]+NOR, name["id"]);              
} 

void create()
{
        string str = "";
        setname(); 
        set_weight(6000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 10000);
                set("material", "gold");
                set("wield_msg", "$N「唰」地一声抽出一把$n握在手中，顿时一股寒气扑面而来！\n");
                set("unwield_msg", "$N将手中的$n插入刀鞘。\n");                
                if(random(20)>10)
                add("weapon_prop/kee", 200+random(500));         
                if(random(10)<2)
                        add("weapon_prop/intelligence",3);
                if(random(20)>15)
                add("weapon_prop/sen", 200+random(500));
                if(random(10)>7)
                        add("weapon_prop/attack",10+random(10));
                set("level_quest",50);
        }
        set("inset_hole",2);
        init_blade(100+random(60));
        if(random(10)>8)
                add("weapon_prop/damage",this_object()->query("weapon_prop/damage")/4);
        if(this_object()->query("inset_hole"))
                str += "一把寒光闪闪的圆头长刀，刀把上镶嵌有白玉，装备等级50。\n"+"它身上有"+this_object()->query("inset_hole")+"个可镶嵌宝石的孔。\n"; 
        else
                str += "一把寒光闪闪的圆头长刀，刀把上镶嵌有白玉，装备等级50。\n"+"它身上没有可镶嵌宝石的孔。\n"; 
        if(this_object()->query("weapon_prop/kee"))
                str += "装备它可增加"+this_object()->query("weapon_prop/kee")+"点气血。\n";
        if(this_object()->query("weapon_prop/intelligence")) 
                str += "增加"+this_object()->query("weapon_prop/intelligence")+"点悟性。\n";
        if(this_object()->query("weapon_prop/sen")) 
                str += "增加"+this_object()->query("weapon_prop/sen")+"点精神。\n";
        if(this_object()->query("weapon_prop/attack")) 
                str += "增加"+this_object()->query("weapon_prop/attack")+"点命中。\n";
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
        if(arg == ob->query("id") || arg == "blade" ){
                if(me->query("level")<50){
                        write("你的等级不够，无法装备这件兵器。\n");
                        return 1;
                }  
        }   
        return 0;  
}   

int query_autoload() 
{ 
        object me = this_player();
        if(me->query("level") >= this_object()->query("level_quest"))
        return 1; 
}  

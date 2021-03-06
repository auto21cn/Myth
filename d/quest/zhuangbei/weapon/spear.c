#include <weapon.h>
inherit SPEAR;
#include <ansi.h>

void setname() 
{ 
        mapping name;
        name=__DIR__"name"->random_name("spear");
        set_name(HIB+name["name"]+NOR, name["id"]);          
} 

void create()
{
        string str = "";
        setname(); 
        set_weight(5500);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "杆");
                set("value", 5000);
                set("material", "steel");
                set("level_quest", 5);
                set("wield_msg", "$N提起$n握在手中，威风凛凛。\n");
                set("unwield_msg", "$N舞了一朵枪花，将手中之物收了起来。\n");                
                if(random(20)>10)
                        set("weapon_prop/kee",200+random(500));
                if(random(10)>6)
                        add("weapon_prop/dodge",10+random(10));
                if(random(10)<2)
                        add("weapon_prop/spiritual",3);
                set("level_quest",5); 
        }
        set("inset_hole",1);
        init_spear(40+random(60));
        if(this_object()->query("inset_hole"))
                str += "一杆精钢打制的枪，装备等级5。\n"+"它身上有"+this_object()->query("inset_hole")+"个可镶嵌宝石的孔。\n"; 
        else
                str += "一杆精钢打制的枪，装备等级5。\n"+"它身上没有可镶嵌宝石的孔。\n"; 
        if(this_object()->query("weapon_prop/kee"))
                str += "装备它可增加"+this_object()->query("weapon_prop/kee")+"点气血。\n";
        if(this_object()->query("weapon_prop/dodge"))
                str += "装备它可增加"+this_object()->query("weapon_prop/dodge")+"点躲避。\n";
        if(this_object()->query("weapon_prop/spiritual"))
                str += "装备它可增加"+this_object()->query("weapon_prop/spiritual")+"点灵性。\n";
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
        if(arg == ob->query("id") || arg == "spear" ){
                if(me->query("level")<5){
                        write("你的等级不够，无法装备这件兵器。\n");
                        return 1;
                }  
        }   
        return 0;  
}

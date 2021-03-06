// Created by kuku@sjsh 2003.3

#include <armor.h>
inherit WAIST;
#include <ansi.h>

void setname() 
{ 
        mapping name;
        name=__DIR__"name"->random_name("waist");
        set_name(HIB+name["name"]+NOR, name["id"]);                  
} 

void create()
{
        string str = "";
        setname(); 
        set_weight(5000);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("value", 5000);
                set("material", "metal");
                set("level_quest", 5);
                set("armor_prop/armor", 25);
                if(random(20)>10)
                        set("armor_prop/unarmed",10+random(10));
                if(random(10)>6)
                        add("armor_prop/composure",3);
                set("armor_prop/parry", -10);
                set("inset_hole",1);
                set("level_quest",5); 
        }
        if(this_object()->query("armor_prop/unarmed") && this_object()->query("armor_prop/composure"))
                str += "一只亮闪闪的护心镜，装备等级5。\n"
                +"装备它可增加"+this_object()->query("armor_prop/unarmed")+"点扑击格斗有效等级。\n"
                +"增加"+this_object()->query("armor_prop/composure")+"点定力。\n";
        else if(this_object()->query("armor_prop/unarmed")) 
                str += "一只亮闪闪的护心镜，装备等级5。\n"
                +"增加"+this_object()->query("armor_prop/unarmed")+"点扑击格斗有效等级。\n";
        else if(this_object()->query("armor_prop/composure"))
                str += "一只亮闪闪的护心镜，装备等级5。\n"
                +"增加"+this_object()->query("armor_prop/composure")+"点定力。\n";
        else 
                str += "一只亮闪闪的护心镜，装备等级5。\n";
        set("long",str);
        setup();
}

void init()
{
        add_action("do_wear","wear");
}

int do_wear(string arg) 
{  
        object ob = this_object();
        object me = this_player();
        if(arg == ob->query("id") || arg == "waist" ){
                if(me->query("level")<5){
                        write("你的等级不够，无法穿上这只护心镜。\n");
                        return 1;
                }  
        }   
        return 0;  
}   


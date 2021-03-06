// Created by kuku@sjsh 2003.3

#include <armor.h>
inherit HANDS;
#include <ansi.h>

void setname() 
{ 
        mapping name;
        name=__DIR__"name"->random_name("hands");
        set_name(HIB+name["name"]+NOR, name["id"]);                            
} 

void create()
{
        string str = "";
        setname(); 
        set_weight(1000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "对");
                set("material", "silver");
                set("level_quest", 5);
                set("value", 5000);
                set("no_zm",1);
                set("armor_prop/armor", 30);
                if(random(20)>10)
                        set("armor_prop/dodge",10+random(10));
                if(random(10)>6)
                set("inset_hole",1);
                set("level_quest",5); 
        }
        if(this_object()->query("armor_prop/dodge") && this_object()->query("armor_prop/composure"))
                str += "一对护掌，装备等级5。\n"
                +"装备它可增加"+this_object()->query("armor_prop/dodge")+"点躲避。\n"
                +"增加"+this_object()->query("armor_prop/composure")+"点定力。\n";
        else if(this_object()->query("armor_prop/dodge")) 
                str += "一对护掌，装备等级5。\n"
                +"增加"+this_object()->query("armor_prop/dodge")+"点躲避。\n";
        else if(this_object()->query("armor_prop/composure"))
                str += "一对护掌，装备等级5。\n"
                +"增加"+this_object()->query("armor_prop/composure")+"点定力。\n";
        else 
                str += "一对护掌，装备等级5。\n";
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
        if(arg == ob->query("id") || arg == "hands" ){
                if(me->query("level")<5){
                        write("你的等级不够，无法戴上这对护掌。\n");
                        return 1;
                }  
        }   
        return 0;  
}   

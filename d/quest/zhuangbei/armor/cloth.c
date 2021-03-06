// Created by kuku@sjsh 2003.3

#include <armor.h>
inherit CLOTH;
#include <ansi.h>

void setname() 
{ 
        mapping name;
        name=__DIR__"name"->random_name("cloth");
        set_name(HIB+name["name"]+NOR, name["id"]);                              
} 

void create()
{
        string str = "";
        setname(); 
        set_weight(4000);
        if( clonep() )
                set_default_object(__FILE__);
        else{
                set("material", "cloth");
                set("unit", "件");
                set("level_quest", 5);
                set("value", 5000);
                set("armor_prop/armor", 90);
                if(random(20)>10)                       
                        set("armor_prop/dodge", 20+random(20)); 
                if(random(10)>6)
                        add("armor_prop/karma",3);
                set("armor_prop/parry", -20);
                set("inset_hole",1);
                set("level_quest",5); 
        }
        if(this_object()->query("armor_prop/dodge") && this_object()->query("armor_prop/karma"))
                str += "一件护身神袍，装备等级5。\n"
                +"装备它可增加"+this_object()->query("armor_prop/dodge")+"点躲避。\n"
                +"增加"+this_object()->query("armor_prop/karma")+"点福缘。\n";
        else if(this_object()->query("armor_prop/dodge")) 
                str += "一件护身神袍，装备等级5。\n"
                +"增加"+this_object()->query("armor_prop/dodge")+"点躲避。\n";
        else if(this_object()->query("armor_prop/karma"))
                str += "一件护身神袍，装备等级5。\n"
                +"增加"+this_object()->query("armor_prop/karma")+"点福缘。\n";
        else 
                str += "一件护身神袍，装备等级5。\n";
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
        if(arg == ob->query("id") || arg == "cloth" ){
                if(me->query("level")<5){
                        write("你的等级不够，无法穿上这件衣服。\n");
                        return 1;
                }  
        }   
        return 0;  
}   


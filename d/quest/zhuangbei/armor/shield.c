#include <armor.h>
inherit SHIELD;
#include <ansi.h>

void setname() 
{ 
        mapping name;
        name=__DIR__"name"->random_name("shield");
        set_name(HIB+name["name"]+NOR, name["id"]);                 
} 

void create()
{
        string str = "";
        setname(); 
        set_weight(1000);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "件");
                set("value", 5000);
                set("no_zm",1);
                set("material", "skin");
                set("level_quest", 5);
                set("armor_prop/armor", 150 );
                if(random(20)>10)
                        set("armor_prop/parry",10+random(10));
                if(random(10)>6)
                        set("armor_prop/defense",10+random(10));
                set("armor_prop/dodge", -10);
                set("inset_hole",1);
                set("level_quest",5); 
        }
        if(this_object()->query("armor_prop/parry") && this_object()->query("armor_prop/defense"))
                str += "一件厚厚的盾牌，装备等级5。\n"
                +"装备它可增加"+this_object()->query("armor_prop/parry")+"点招架。\n"
                +"增加"+this_object()->query("armor_prop/defense")+"点防御。\n";
        else if(this_object()->query("armor_prop/parry")) 
                str += "一件厚厚的盾牌，装备等级5。\n"
                +"增加"+this_object()->query("armor_prop/parry")+"点招架。\n";
        else if(this_object()->query("armor_prop/defense"))
                str += "一件厚厚的盾牌，装备等级5。\n"
                +"增加"+this_object()->query("armor_prop/defense")+"点防御。\n";
        else 
                str += "一件厚厚的盾牌，装备等级5。\n";
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
        if(arg == ob->query("id") || arg == "shield" ){
                if(me->query("level")<5){
                        write("你的等级不够，无法拿上这件盾牌。\n");
                        return 1;
                }  
        }   
        return 0;  
}   

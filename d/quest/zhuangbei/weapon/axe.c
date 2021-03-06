#include <weapon.h>
inherit AXE;
#include <ansi.h>

void setname() 
{ 
        mapping name;
        name=__DIR__"name"->random_name("axe");
        set_name(HIB+name["name"]+NOR, name["id"]);                  
} 

void create()
{
        string str = "";
        setname(); 
        set_weight(9000);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "把");
                set("value", 5000);
                set("material", "iron");
                set("level_quest",5);
                set("wield_msg", "$N拿出一把$n握在手中，眼前闪过一道寒光！\n");
                set("unwield_msg", "$N放下手中的$n。\n");                
                if(random(20)>10)
                        set("weapon_prop/force",10+random(10));
                if(random(10)>6)
                        add("weapon_prop/attack",10+random(10));
                if(random(10)<2)
                        add("weapon_prop/constitution",3);
                set("level_quest",5); 
        }
        set("inset_hole",1);
        init_axe(40+random(60));
        if(this_object()->query("inset_hole"))
                str += "这是把沉重的大斧，有八尺多长，锋利无比，装备等级5。\n"+"它身上有"+this_object()->query("inset_hole")+"个可镶嵌宝石的孔。\n"; 
        else
                str += "这是把沉重的大斧，有八尺多长，锋利无比，装备等级5。\n"+"它身上没有可镶嵌宝石的孔。\n"; 
        if(this_object()->query("weapon_prop/force"))
                str += "装备它可增加"+this_object()->query("weapon_prop/force")+"点内功有效等级。\n";
        if(this_object()->query("weapon_prop/attack")) 
                str += "增加"+this_object()->query("weapon_prop/attack")+"点命中。\n";
        if(this_object()->query("weapon_prop/constitution")) 
                str += "增加"+this_object()->query("weapon_prop/constitution")+"点根骨。\n";
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
        if(arg == ob->query("id") || arg == "axe" ){
                if(me->query("level")<5){
                        write("你的等级不够，无法装备这件兵器。\n");
                        return 1;
                }  
        }   
        return 0;  
}   

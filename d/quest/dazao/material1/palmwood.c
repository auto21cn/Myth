//palmwood.c 打造武器材料--花榈木
// Created by kuku@sjsh 2003.2.13

#include <ansi.h>
inherit ITEM;  
void create() 
{
         set_name("花榈木",({"palm wood", "wood"}));
        set_weight(20000);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "根");
                set("no_drop","不要乱丢，这东西打到人痛！\n");
                set("long", "这是一根花榈木。\n");
        }
        setup();
}


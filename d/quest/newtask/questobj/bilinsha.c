#include <weapon.h>
#include <ansi.h>
inherit THROWING;
void create()
{
        set_name(HIG"碧磷砂"NOR, ({ "bilin sha" }) );
        set_weight(30); 
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "些");
                       set("material", "iron");
 set("long", "碧目真人花信风数年行走深山大岭，取古墓中死人的白骨磷火，混合五金精华，制炼而成的暗器。\n");
                  }
           setup();
}

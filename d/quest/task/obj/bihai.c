//By waiwai@mszj 2000/12/02

inherit ITEM;
#include <ansi.h>
#include <task.h>

void create()
{
        set_name(HIG"碧海叉"NOR, ({"aoguang seafork","seafork"}));
        set_weight(80);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("long", "一把蹈海大圣专用的武器。\n");
                set("unit", "把");
               set("owner_name","敖广");
               set("owner_id","ao guang");
        }
}


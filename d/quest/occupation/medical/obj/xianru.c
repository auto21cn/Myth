// xianru.c ��ʯ����  
// Created by kuku@sjsh 2003.2

#include <ansi.h>
inherit ITEM;  

void create() 
{
        set_name(HIW"��ʯ����"NOR,({"lingshi xianru"}));
        set_weight(100);
        if ( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "Щ");
                set("no_drop",1);
                set("no_put",1);
                set("long", "����ҽʦ����ҩ�ĵ�ԭ�ϡ�\n");
        }
        setup();
}

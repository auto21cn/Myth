//Cracked by Roath
// �����硤���μǡ��汾��������
/* <SecCrypt CPL V3R05> */
inherit ITEM;
#include <ansi.h>
#include <task.h>
void create()
{
    set_name(HIW"ζ����֤"NOR, ({ "weixian" }) );
    set_weight(1);
    if( clonep() )
            set_default_object(__FILE__);
    else {
            set("long", "���ǳ�͢���͵�һ���������������֤��\n");
            set("unit", "��"); 
            set("owner_name", "��ڸ�");
          set("owner_id", "wan koufu");
          }

    setup();
}

//Cracked by Kafei
// rose.c
#include <ansi.h>

inherit COMBINED_ITEM;

int value() { return query_amount() * (int)query("base_value"); }

void create()
{
	set_name(HIY "�����" NOR, ({"jinyu cao", "jin"}));
	if (clonep())
		set_default_object(__FILE__);
	else {
		set("long", "����һ�仨�ͱ��£�������΢Ц�Ľ���ݣ������н����࣬���˵�ͷ��\n");
		set("unit", "��");
		set("value", 25);
		set("base_unit", "��");
        set("base_weight", 100);
	set("flower_w",1);
			}
	set_amount(1);
}
#include "flower.h"
// 胡缨枪 by ffff
#include <weapon.h>
#include <ansi.h>

inherit SPEAR;

void create()
{
  set_name(HIY"胡缨枪" NOR, ({ "huying spear","qiang","spear" }));
  set_weight(10);
  if( clonep() )
    set_default_object(__FILE__);
  else {
    set("unit", "杆");
    set("value", 1000);
    set("material", "gold");
    set("long", HIR"赵客缦胡缨，吴钩霜雪明。银鞍照白马，疯沓如流星。
    十步杀一人，千里不留行。事了拂衣去，深藏身与名。\n"NOR);
    set("wield_msg", "$N抄起一杆$n，顺手抖了个枪花,搞的天地都为之动摇。\n");
  }
  init_spear(500);
  setup();
}


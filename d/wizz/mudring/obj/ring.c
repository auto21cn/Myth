// Item: /d/wizz/mudring/obj/ring.c
// By mudring@sjsh for xianzi......

#include <ansi.h>
#include <net/dns.h>
#include <armor.h>
inherit F_AUTOLOAD;

inherit FINGER;

int do_coupletalk(string msg);
void create()
{
        string color;
        object ob = this_player();
        if ( ! ob->query("color") ) color = MAG;
        else color = ob->query("color");
        set_name( color + "水晶钻戒" NOR, ({ "wedding ring", "ring" }) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "只");
                set("value", 100000);
            set("no_sell", "这你也要卖？不如把你自己卖了！"); 
                set("material", "gold");
 //               set("armor_type", "married");
 //               set("armor_prop/armor",1);
                set("no_give","这个也给人？");
                set("no_drop",1);
                set("no_get",1);
        }
        setup();
}

int query_autoload()
{
        return 1;
}

void init()
{
            object ob = environment(); 

                if ( (!ob->query("couple/id") || !ob->query("couple/name")) && !wizardp(ob) ) {
                        ob->delete("married");
                        call_out("lost", 1);
                        return;
                }
                set("long", "这是你"
                        + (ob->query("gender") == "女性"?"相公":"娘子")
                        + "送给你的定情信物，上面"
// 50                          + (ob->query("gender") == "女性"?"刻":"绣")
                        + "刻着一行小字：「"
                        + (ob->query("gender") == "女性"?"海枯石烂 ":"此心不变 ")
                        + ob->query("couple/name") + "」。\n");
                wear();
add_action("do_coupletalk", "me");
}

void lost()
{
        object ob = environment();

        if (userp(ob))
                tell_object(ob, HIB "\n你隐约觉得有一样很重要的东西丢失了！\n\n" NOR);
        destruct(this_object());
}

int unequip()
{
        object ob = environment();

        if (userp(ob) && ob->query("couple/id") && ob->query("couple/name"))
                return notify_fail("你不能卸下你的定情信物。\n");

        return ::unequip();
}

int do_coupletalk(string msg)
  {
        object me, obj;
        string arg;
        me = this_player();
        if(!me->query("married")) return notify_fail("你结婚了吗？\n");
        obj = find_player(me->query("couple/id"));
        if(!obj || (!wizardp(me) && !me->visible(obj)))
                return notify_fail("你的伴侣现在不在....\n");
        if( !msg )
        {
                tell_object(me,sprintf(HIM"你总得说点什么吧？\n" NOR));
        }
        else
        {
                write(HIM "你悄悄告诉你的" + me->query("couple/name") + "：" + msg + "\n" NOR);
                tell_object(obj, sprintf( HIM "你的%s悄悄告诉你：%s\n" NOR,obj->query("couple/name"), msg)); 
        }
        return 1;
}

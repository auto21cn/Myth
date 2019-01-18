#include <ansi.h>
inherit BANK;

void reset_balance(object me);

void create ()
{
        set ("short","四海钱庄" );
        set ("long", @LONG

四海钱庄乃洛阳城最大的钱庄。也是非常有名的老字号。老板正是中
国第一巨贾，红顶商人胡雪源，乃山西人氏，这家钱庄从他的爷爷的爷爷
的爷爷的爷爷那辈开始办起，一直传到他手里，声誉非常好，在全国各地
都有分店。它发行的银票通行全国。钱庄的门口挂有一块牌子(paizi)。
LONG);
        set("item_desc", ([
                "paizi": @TEXT
这里是钱庄，目前我们提供的服务有：

account         查帐。
deposit         存款。
withdraw        取款。
convert         兑换钱币。

TEXT
        ]) );

        set("exits", ([
                "north" : __DIR__"wroad1",
        ]));

        set("objects", ([
                __DIR__"npc/hu" : 1
        ]));

        set("no_clean_up", 0);
        setup();
}

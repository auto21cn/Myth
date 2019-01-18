// Room: /u/mes/kitchen.c

inherit ROOM;

void create ()
{
  set ("short", "厨房");
  set ("long", @LONG

厨房里支起了数口大锅，灶下烈火熊熊，整日不息。蒸笼里传出的香
气却甚是古怪，看来这包子里大有文章。墙上有张告示(gaoshi)，油
渍斑斑，字迹颇为模糊。
LONG);

  set("valid_startroom", 1);
  set("item_desc", ([ /* sizeof() == 1 */
  "gaoshi" : "近来缺乏新鲜人肉，各洞小仙若有擒获，请速送厨房。
",
]));
  set("exits", ([ /* sizeof() == 1 */
  "east" : __DIR__"dong2",
]));
  set("resource", ([ /* sizeof() == 1 */
  "water" : 1,
]));

  set("objects", ([ /* sizeof() == 1 */


//cut yanshu .因为这里存在一个大bug!
//一个新的newbie,拜了wdd,要了新人礼物后，
//get 一个zhang men(主要是zhang men代码出问题，连带这里出问题)
//然后sell,得到的包子:/d/qujing/wudidong/npc/obj/renroubao.c
//eat rou baozi后:eat rou baozi 
//黎叔拿起肉包子，有滋有味地吃了下去。> 你突然感到身体有些变化，似乎将包子馅活着时的道行吸收了一些！
//┃〖 道行 〗一万七千二百四十七年二十天三时辰                          ┃
// 在zhang men问题没解决之前，这个连带bug 先cut
//由lian这个player提供操作方法，seng@2005-1-26

// 28    __DIR__"npc/yanshu": 1,
]) );
  setup();
    call_other("/obj/board/wudidong_b", "???");
}
void init()
{
    add_action("do_save", "save");
}
int do_save(string arg)
{
    object me=this_player();
    if (arg) return 0;
    if (me->query("family/family_name")!="陷空山无底洞")
    {
        me->save();
        tell_object(me, "档案储存完毕。\n");
        return 1;
    }
    return 0;
}

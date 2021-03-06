//Cracked by Roath
// Room: /moon/ontop.c
//cglaem...12/13/96.

inherit ROOM;

void create ()
{
  set ("short", "御花园");
  set ("long", @LONG

这里是皇宫的后院 - "御花园",这里四季长青,其中最显眼的就是
花园中间的那棵"千紫藤(qianzi teng)",它高耸入云,一眼看不到
顶.据说曾经有人试着爬过,但是没到一半就返回了,尽管这样也花
了好多天,不过你也可以试试爬上去,据说如果拿到这藤最顶上的一
件宝物并交给皇帝的话可以得到赏赐,你可以使用(climb)试试 ...
LONG);

  set("item_desc", ([ /* sizeof() == 1 */
  "qianzi teng" : "一株高耸入云的紫色树藤 。上面开着无数的小花
正散发出阵阵清香,你可以(climb tree)试试能不能爬上去。
",
]));
  set("objects", ([ /* sizeof() == 2 */
  "/d/calvin/lanling/npc/shouhu" : 1,
  "/d/calvin/npc/gonggong" : 1,
]));

  set("outdoors", 2);
  set("exits", ([ /* sizeof() == 3 */
   "north" : "/d/calvin/lanling/entrance",
//   "east" : "/d/calvin/lanling/midao",
]));

  setup();
}
void init()
{
  add_action("do_climb", "climb");
  add_action("do_kan", "kan");
}


int valid_leave(object me, string dir)
{
        object wuyou;
//    if ( !wizardp(me) && dir == "south" && dir == "south") {
    if ( dir == "east" && dir == "south") {
        if(objectp(wuyou=present("wu you", environment(me))) && living(wuyou) )

            return notify_fail("御花园突然出现吴刚，伸出一把大板斧拦住你,你跑进去想干什么？\n");
    }
    return ::valid_leave(me, dir);
}

int do_climb(string arg)
{
	object wugang;
  object me=this_player();
 
  if( (!arg) || !((arg == "tree") || (arg == "桂树")))
    return notify_fail("爬什么？\n");
  if (me->is_busy()) return notify_fail("你现在正忙着呢。");
  if( me->query("kee") < (int)(me->query("max_kee")/3)){
    me->receive_damage("kee",(int)me->query("max_kee")*20/100);
    return notify_fail("你身子发虚，一头栽了下来，哎呀！\n");
}
  if (!((string)me->query("family/family_name")=="平民")
	 && objectp(wugang=present("wu gang", environment(me))) && living(wugang) )
    {
      message_vision("守护者拦道：此间并非戏耍之处，请立即离开!\n", me);
    }
  else
    {
      if ((int)me->query_skill("dodge", 1)<40 && (int)me->query_skill("moondance", 1) < 80)
        {
	  message_vision("$N小心翼翼的往上爬了一点，觉得头晕眼花，就赶紧爬了下来．\n", me);
          me->improve_skill("dodge", 40-me->query("str"));
          tell_object(me, "你领悟出一些基本轻功方面的窍门。\n");
        }
      else
        {
          message_vision("$N轻轻地一腾就上了树藤,一会便消失在无尽的香花之中了。\n", me);
                 me->move("/d/calvin/lanling/yi.c");
        }
    }
  me->receive_damage("kee", (int)me->query("max_kee")*10/100);
  return 1;
}

int do_kan(string arg)
{
  object me=this_player();
  object ob; 
  object wugang;
  if( (!arg) || !((arg == "tree") || (arg == "千紫藤")))
    return notify_fail("你要砍什么？\n");
    if (me->is_busy()) return notify_fail("你现在正忙着呢。");
   if( !(ob = me->query_temp("weapon"))|| (string)ob->query("skill_type") != "axe")
    return notify_fail("先去找把斧头吧！\n");
  if( me->query("kee") < (int)(me->query("max_kee")/3))
    return notify_fail("再砍下去手都要磨破了！\n");
  if (!((string)me->query("family/family_name")=="平民" )&&
	objectp(wugang = present("wugang", environment(me))) && living(wugang))
    {
      message_vision("守护者拦道：此间并非戏耍之处，请立即离开!\n", me);
    }
  else
    {
      message_vision("$N朝千紫藤使劲儿砍了几下．\n", me);
      if ((int)me->query_skill("unarmed", 1)< 50 )
        {
          me->improve_skill("unarmed", me->query("str"));
          tell_object(me, "累得个快死，你总算领悟出一些运劲使力方面的窍门。\n");
        }
      else {
	tell_object(me, "你试着砍了几下，不明白为什么有人会做这种傻事。\n"); 
	}

    }
  me->receive_damage("kee", (int)me->query("max_kee")*10/100);
  return 1;
}

//int valid_leave(object me, string dir)
//{
//        object a;
//   if (dir == "climb" ) {
//                if(objectp(a=present("guard", environment(me))) &&
//living(a) )
//        return notify_fail("吴忧拦住你说道：九重天极其危险，死了不要怪人，还是不要上去为好。\n");
//        }   
//        return ::valid_leave(me, dir);
//}

//Created by aeddy@2001/03/23
//Last modified by aeddy@2002/12/05
//四季(春夏秋冬)以及天气(晴雨风雪)

#include <allcity.h>
string long_desc();
inherit ROOM;
#include <ansi.h>

void create ()
{
  set ("short","白虎大街");
        set ("long", @LONG

这里已是白虎大街的西段，北面小巷里隐约看到一座大的草堂，堂外
挂一蓝布幌子，上写一个“卦”字。南面巷中一行歪柳，处处民宅，
几个小同在巷中玩耍。
LONG);

        //set("item_desc", ([" *** " : " *** ", ]));

        set("exits", 
        ([ //sizeof() == 4
		"south" : __DIR__"beiyin1",
                "north" : __DIR__"caotang",
                "west" : __DIR__"ximen",
                "east" : __DIR__"baihu-w2",
        ]));

        set("objects", 
        ([ //sizeof() == 1
//                __DIR__"npc/libai" : 1,
        ]));


       set("tsj_exst","west");
        set("outdoors", "changan");
	set("no_book", 1);
	set("outdoors", "长安城");
	set("no_clean_up", 1);
        setup();
	replace_program(ROOM);
}



string long_desc() 
{
       string msg, season;

	//调用天气而不是季节(非模糊方式)
	season = NATURE_D->check_seasonF();

	//首先是夜晚的判断
       if (day_event() == "event_night" || day_event() == "event_midnight") {

	if(season == "SpringA-Sun" ||  season == "SpringB-Sun" ||
	season == "SpringC-Sun")
msg="
春夜晴朗的夜晚。朱雀大街显得格外的安静。大多的店家已经
打烊了。只有不远处东临的南城客栈依然有人在高谈阔论着。
那些亲身经历的和道听途说的话题似乎总是无法完结的可以谈
论。或者谈论自己，或者谈论别人，活着如果没有谈论了，或
许就可以死去了罢！\n";

	if(season == "SpringA-Rain" || season == "SpringB-Rain" ||
	season == "SpringC-Rain")
msg="
春夜有雨的夜晚。朱雀大街被雨水冲刷的格外地干净。透过南
城客栈照出来的灯光，路面显得分外的明亮，小雨淅淅沥沥地
下着在这样的一个春夜，似乎在讲述着一个千年的故事。在这
样一个夜晚听着雨声沙沙的入梦该是怎样的一种难有的心境啊。\n";

	if(season == "SpringA-Wind" || season == "SpringB-Wind" ||
	season == "SpringC-Wind")
msg="
春日有风的夜晚。朱雀大街似乎也被微风吹醉，冬天已经过去
了春风仍在唧唧喳喳的讲述着在冬天里面那年年诉说的不同的
故事就象人生一样，再雷同的今天也将是一个不同的昨天。\n";

	if(season == "SummerA-Sun" || season == "SummerB-Sun" ||
	season == "SummerC-Sun")
msg="
晴朗的夏夜时光总是惬意的。长街上有许多纳凉的人，摇一把
蒲扇，饮一壶清茶，共邀几聚乡邻闲心的谈天说地一番。谈谈
过去，谈谈快乐过的那过去了的美好日子，其乐融融的场景似
乎弥漫了整个长安城。\n";

	if(season == "SummerA-Rain" || season == "SummerB-Rain" ||
	season == "SummerC-Rain")
msg="
夏日有雨的夜晚。长街上经常有许多没有雨伞的人奔跑而过。
或者回家或者大多的都奔进了南城客栈。更有个别的人却悠闲
的漫步在雨中，似乎别有一番感觉在心头。江湖或许就是这样，
有循规蹈矩的人，也有不谙世俗的人。活着似乎就是该庆幸的
一件事了。\n";

	if(season == "SummerA-Wind" || season == "SummerB-Wind" ||
	season == "SummerC-Wind")
msg="
夏日有风的夜晚。长街上乘凉的人开始多了起来。这样的夜晚
似乎分外的惬意和舒畅。走过长街到处飘散着茶香，茶香过处
欢笑阵阵。大唐今日的长安是自古以来少有的兴旺和富足。百
姓的日子也是格外地红火。\n";

	if(season == "AutumnA-Sun" || season == "AutumnB-Sun" ||
	season == "AutumnC-Sun")
msg="
秋日晴朗的夜晚。秋日的夜晚总是静谧的。酣睡的孩童在梦里
都会开心的笑。四处静谧而不燥热的秋夜去睡一个香甜的觉，
做一个酣美的梦，又该是怎样的一种幸福啊朱雀大街上已经少
有人行了，似乎都是为了追寻一个美好的梦境而早早的进入了
梦乡。\n";

	if(season == "AutumnA-Rain" || season == "AutumnB-Rain" ||
	season == "AutumnC-Rain")
msg="
秋日有雨的夜晚。秋雨淅沥地下着。似乎在讲述着一个遥远的
故事。老人说过：一场秋雨一场寒。虽然这样一个秋雨的夜晚
是美好的，但是冬天也一步步的来临了。似乎业可以说这样一
句话：秋天来了，冬天已经不远了。\n";

	if(season == "AutumnA-Wind" || season == "AutumnB-Wind" ||
	season == "AutumnC-Wind")
msg="
秋日有风的夜晚。秋风微送着惬意的沁凉，给人以特别爽肤的
感觉，微风过处，酣睡的孩童在梦里都会开心的笑。带着美好
的思绪，在这样一个秋风爽肤的夜晚，入梦！\n";

	if(season == "WinterA-Sun" || season == "WinterB-Sun" ||
	season == "WinterC-Sun")
msg="
冬日晴朗的夜晚。前日刚下过夜的大雪仍铺积在房顶上，街角
处。在寒冷的冬夜里似乎没有风没有雪的晴天就该是一件首要
幸福的事情了。不远处南城客栈把酒谈天的人今天也多了起来。
出出进进的人脸上都挂着笑，相互寒暄着，问着冷暖虚寒。\n";

	if(season == "WinterA-Snow" || season == "WinterB-Snow" ||
	season == "WinterC-Snow")
msg="
冬日有雪的夜晚。冬夜的大街铺满了积雪。雪紧一阵慢一阵的
下个不停。雪花默默地飘落着，似乎在不停地诉说着一个关于
冬季的不为人知的故事。在这样一个夜晚，天地的舞台是属于
它们的，它们在尽情地飘舞着演绎着一曲动人的乐章。\n";

	if(season == "WinterA-Wind" || season == "WinterB-Wind" ||
	season == "WinterC-Wind")
msg="
冬日有风的夜晚。屋檐上铺的积雪被冷风吹的四处飘散，象是
在下另一场雪似的。大街上风卷着角落处的雪在旋舞着。偶而
有行路的人都包裹的严严实实的，看不清谁是谁了。这样的夜
晚给人的感觉就是家不管是如何的破败和寒酸都是温暖的。\n";

	if(season == "Default-Sun")
msg="
晴朗的夜晚。天上星星在眨着眼睛。没有人知道星星为什么要
眨眼睛，就象没有人可以知道人究竟是为什么而生一样。或许
人只是为死而生罢了，因为人生来的宿命无论是如何的辉煌度
过都难免一死。没有说为死而生的人。\n";

	} else {

	if(season == "SpringA-Sun" ||  season == "SpringB-Sun" ||
	season == "SpringC-Sun")
msg="
春日晴朗的白天。春天终于来临了，寒冷的冬天已经远去了。
冬天的寒冷已经是昨天的梦。似乎没有半点痕迹了。长安的春
日年复一年的依旧是繁华和忙碌的。人们把冬日里积攥的希望
开始去释放，去实现，有人说春天是做梦的季节或许该说春天
是开始去实现梦想的季节。\n";

	if(season == "SpringA-Rain" || season == "SpringB-Rain" ||
	season == "SpringC-Rain")
msg="
春日有雨的白天。在这样的一个日子里面总是会让人想到许多
的感怀的诗句，什么春雨贵如油啦，什么春来江水绿如蓝，能
不忆江南啦。。。感怀的季节总是让人随时随地地想抒发一下
情怀，无论是在忙碌还是在忙碌的暇隙之时。\n";

	if(season == "SpringA-Wind" || season == "SpringB-Wind" ||
	season == "SpringC-Wind")
msg="
春日有风的白天。春天的风里总会让人不禁有着许多的希望的
骐骥和缅怀之情。春风拂面，感怀一季。大街上来来往往的人
脸上都挂着开心的笑容春风满面的感觉恰如其份。在春天里面
伤感的人应该说是最不幸的罢。既然寒冷的冬天都可以度过，
有什么还不能让人释怀而希冀呢？\n";

	if(season == "SummerA-Sun" || season == "SummerB-Sun" ||
	season == "SummerC-Sun")
msg="
夏日晴朗的白天。夏日的长安，知了在路旁树杈上拼命地嚎叫着。
忙碌的小贩都裹着毛巾不停地擦着汗水。人们为了生活仍然不能
停止奔忙，再富足的日子也不可能完全得以清闲的。忙碌的人生
是永恒的主题。就象天上飘动的白云，你说是风动，还是云动？\n";

	if(season == "SummerA-Rain" || season == "SummerB-Rain" ||
	season == "SummerC-Rain")
msg="
夏日有雨的白天。夏日的雨水或许是该多一些的，至少可以稍微
的浇凉些热戾之气。雨水洗刷着街道，也洗刷着人们的疲惫和烦
心。旁边南城客栈的小二在给来往的客人整理着雨伞，似乎格外
地忙碌的样子。不远处几个顽童在雨中快乐地嬉戏着，追逐着，
每个人都象只湿淋淋的小落汤鸡似的。\n";

	if(season == "SummerA-Wind" || season == "SummerB-Wind" ||
	season == "SummerC-Wind")
msg="
夏日有风的白天。有风的日子在夏日里应该算是幸福的罢。许多
人在相互谈论着舒畅的感觉。风在这个季节里面好象是被赞颂的
的最多的时候吧，比起在冬天里的人们冷眼的那种「遭遇」来说，
它也是该高兴的了。有风的夏日里面街头的小贩的叫卖声似乎也
格外地洪亮和卖力呢。\n";

	if(season == "AutumnA-Sun" || season == "AutumnB-Sun" ||
	season == "AutumnC-Sun")
msg="
秋日晴朗的白天。秋日似锦的时光，时常有落叶随秋风而起。每
到傍晚的时候经常有雅兴诗人踯躅而过。夏日的燥热情怀已经不
复存在了云淡风轻的秋天是该好好体味生活的季节，也是该收获
辛劳果实的季节。\n";

	if(season == "AutumnA-Rain" || season == "AutumnB-Rain" ||
	season == "AutumnC-Rain")
msg="
秋日有雨的白天。秋雨淅沥地下个不停。在秋雨的日子里面，最
惬意的事情该是冲一壶清香的桂香铁观音，邀知己同饮，把杯谈
心。那春天的故事，夏日的序曲，还有不远的将要来临的冬日的
情怀都将在茶香里体会得淋漓尽致的。\n";

	if(season == "AutumnA-Wind" || season == "AutumnB-Wind" ||
	season == "AutumnC-Wind")
msg="
秋日有风的白天。秋风送爽的日子，时常有落叶随秋风而起，旋
舞着，飘落着。那是一种精灵之舞，生命之舞。倘若人可以在秋
天有风的日子里面与落叶一同旋舞着死去，或许也该是一种幸福
的事罢。\n";

	if(season == "WinterA-Sun" || season == "WinterB-Sun" ||
	season == "WinterC-Sun")
msg="
冬日晴朗的白天。冬日里的长街上，人们大多行色匆匆而过。或
者寻求店家投宿，或者匆忙的买卖购物而过。家，在这个季节里
面总是温暖的。\n";

	if(season == "WinterA-Snow" || season == "WinterB-Snow" ||
	season == "WinterC-Snow")
msg="
冬日有雪的白天。雪花洋洋洒洒地飘落着，人们大多行色匆匆而
过。街头小贩的叫卖声也只能偶而的听到了。银装素裹的长安城
在这个时候似乎显得比常日里面更加的安静。\n";

	if(season == "WinterA-Wind" || season == "WinterB-Wind" ||
	season == "WinterC-Wind")
msg="
冬日有风的白天。风在这个季节里面总是受到很多的责骂声，比
起夏日里来说，它已经成了最不受欢迎的了。冬日里的寒风刮到
猛烈时总给人以生命极至的感觉。许多人暮年之时在这样的日子
里面都没能捱得过去而匆忙的走了。这样的日子让人体会最深的
是活着的不易和艰辛。\n";

	if(season == "Default-Sun")
msg="
晴朗的白天。朱雀长街上熙熙攘攘的热闹非凡。长安历来是商甲
聚集之处。特别是唐皇盛世的现在就是更加的繁荣和热闹富足。
朱雀大街更成了一条最不会寂寞的长街了。\n";
	}
       return msg; 
}

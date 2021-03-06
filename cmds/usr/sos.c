// Update by aeddy@2002/12/05

#define SOS_DIR       "/data/"
#define SOS_FILENAME  "sos"

#include <command.h>

inherit F_CLEAN_UP;
inherit F_SAVE;

mapping *notes;
int confirm(string yn, object me);

string query_save_file()
{
    return SOS_DIR + SOS_FILENAME ;
}

mixed query(string arg)
{
    if (arg && arg=="channel_id")
        return  "求救精灵";
    return 0;
}

void done_post(object me, mapping note, string text)
{
	int i;
	object where;
	note["msg"] = text;
	i = sizeof(notes);
	where = environment(me);

	for( ; i > 0; i-- ) 
	if( notes[i-1]["author"] == me->query("id") ) break;
	if( !pointerp(notes) || i > 0 )
	if(!sizeof(notes)) notes = ({ note });
	else {
	notes[i-1]["title"] = note["title"];
	notes[i-1]["author"] = note["author"];
	notes[i-1]["msg"] = note["msg"];
	notes[i-1]["time"] = note["time"];
	notes[i-1]["solve"] = "";
	notes[i-1]["solve_id"] = "";
	} else
	notes += ({ note });

	CHANNEL_D->do_channel(this_object(), "sys",
	log_id(me)+"在["+MISC_D->find_place(where)+COLOR_D->clean_color(where->query("short")) +
"]写了一个"HIR"SOS"NOR WHT"求救信息。。。\n"NOR);
        log_file("static/sos", sprintf("%s填写了一个sos信息 时间在：[%s]\n", log_id(me), log_time() ));

	tell_object(me, WHT "求救完毕。你的信息已经被加到巫师通知队列里。\n");
	tell_object(me, WHT "巫师正在处理其他玩家，请等待。。。\n");
	tell_object(me, WHT "请过一段时间后可以用sos read查看是否被解决。\n" NOR);
	save();
	return;
}

void list_bug(object me)
{
	int i;
	string str,s;

	if (sizeof(notes)<1) {
		write("没人发出 sos 求救信号。\n");
	return;
	} 

	s = sprintf("玩家已经发出未解决的sos列表如下(如要察看总表请用 sos list ):\n"
      "───────────────────────────────────────\n");
	for( i = 0; i<sizeof(notes); i++){
	if(notes[i]["solve_id"]=="") {
	str = sprintf("[%2d] %-40s%10s [%s] \n",
       i+1, notes[i]["title"], notes[i]["solve_id"]==""?"尚未回复":"By "+notes[i]["solve_id"],
       BJTIME_CMD->chinese_time(7, ctime(notes[i]["time"])) );
	s = s + str;
	}
	}
	me->start_more(s);                
}

void list_bug_all(object me)
{
	int i;
	string str,s;

	if (sizeof(notes)<1) {
		write("没人发出 sos 求助信号。\n");
	return;
	} 

	s = sprintf("玩家已经发出的 sos 列表如下:\n"
      "───────────────────────────────────────\n");
	for( i = 0; i<sizeof(notes); i++){
	str = sprintf("[%d] %-40s %10s [%s] \n",
	i+1, notes[i]["title"], notes[i]["solve_id"]==""?"尚未回复":"By "+notes[i]["solve_id"],
       BJTIME_CMD->chinese_time(7, ctime(notes[i]["time"])) );
	s = s + str;
	}
	me->start_more(s);                
}

void do_read(object me, int i) 
{
	string s;
	if( i > sizeof(notes) || i < 1) {
		write("无此编号！！！\n");
	return;
	}

	s = sprintf("(%d) %-50s [%s]\n"
      "───────────────────────────────────────\n"
      "%s\n"
      U"处理意见:[ %s ]\n"NOR
      CYN"%s\n"NOR,
	i, notes[i-1]["title"], BJTIME_CMD->chinese_time(7, ctime(notes[i-1]["time"])), 
	notes[i-1]["msg"], notes[i-1]["solve_id"]==""?"尚未回复":"By "+notes[i-1]["solve_id"], 
	notes[i-1]["solve"] );
	me->start_more(s);
}

int search_id(string id)
{
	int i;
	if( !(i = sizeof(notes)) ) return 0;
	for( ; i > 0; i-- ) 
	if( notes[i-1]["author"] == id ) break;
	return i;
}

void done_re(object me, int i, string text)
{
	notes[i-1]["solve"] = text;
	notes[i-1]["solve_id"] = me->query("id");
	save();
	write("该 sos 信息已标志为解决。\n");
	return;
}

int do_re(object me, int i)
{
	if( i > sizeof(notes) || i < 1) {
		write("无此编号！！！\n");
		return 0;
	} 

	if ( notes[i-1]["solve_id"]!="" ) {
		write(notes[i-1]["solve_id"]+"已经标志！！\n");
	return 1;
	}

	write("请输入你的处理意见：\n");
	me->edit( (: done_re, me,i :) );
	return 1;
}

int main(object me, string arg)
{
    mapping note;
    object where;
    string s, str,arg1;
    int i,arg2;
    restore();

	if (!arg) {
	if(wiz_level(me)) {
         list_bug_all(me);
	} else {
         write(HIG"\n单纯阅读请使用sos read，每个人只能填写一份SOS信息\n"NOR);
         write(HIG"\n如果已经填写过信息，选择 "HIR"Y"HIG" 将覆盖你以前写过的SOS信息\n"NOR);
         write(HIG"\n你确定要写一份SOS信息吗？确认请输入"HIR"Y"HIC"。否则请输入任意退出！\n"NOR);

         input_to((: confirm :), me);
	}
	return 1;
	} 

	if( sscanf(arg, "%s %s", s, arg1) == 2 ) {
	if( !wiz_level(me) ) return notify_fail("格式不对，具体使用方法请参阅 help sos \n");
	if( s != "re" ) return notify_fail("格式不对，具体使用方法请参阅 help sos \n");

	i = search_id(arg1);
	if( i > 0 ) { 
	do_re( me, i );
	return 1;
	}
	}

	if( sscanf(arg, "%s %d", s, arg2) == 2 ) {
	if( !wiz_level(me) ) return notify_fail("格式不对，具体使用方法请参阅 help sos \n");
	if ( s != "re" ) return notify_fail("格式不对，具体使用方法请参阅 help sos \n");
	do_re( me, arg2 ); 
	return 1;
	}

	if ( sscanf(arg, "%s", s) == 1 ) 
	switch(arg){
	case "read":       
		if( !(i = sizeof(notes)) )
			return notify_fail("还没有人做过 sos 呼叫！\n");
		else {
			i = search_id( me->query("id") );
			do_read(me,i);
		}
		break;

	case "list":
		if( !wiz_level(me) ) return notify_fail("格式不对，具体使用方法请参阅 help sos \n");
		list_bug_all(me);
		break;

	case "del":
		if( !wiz_level(me) ) return notify_fail("格式不对，具体使用方法请参阅 help sos \n");
		if( !(i = sizeof(notes)) ) return notify_fail("没人发出 sos 求救信号。\n");
		for( ; i > 0; i-- ) 
		if( "" != notes[i-1]["solve_id"] ) {
		printf("%s的 sos 求助已被删除！！！\n", notes[i-1]["author"]);
		if( sizeof(notes) == 1 ) notes = ({});
			else if(i==1) notes = notes[1..sizeof(notes)-1];
			else if( i == sizeof(notes) ) notes = notes[0..sizeof(notes)-2];
			else notes = notes = notes[0..i-2] + notes[i..sizeof(notes)-1];
		}
		save();
		break;

	case "re":
		if( !wiz_level(me) ) return notify_fail("格式不对，具体使用方法请参阅 help sos \n");
		return notify_fail("格式: sos re <编号或玩家id>\n");
		break;

		default:
		if( !wiz_level(me) ) return notify_fail("格式不对，具体使用方法请参阅 help sos \n");
		if( sscanf(arg, "%d", i) == 1 )
			do_read( me, i );
		else if( sscanf( arg, "%s", str ) == 1 ) {
			i = search_id(str);
			if( i == 0 ) return notify_fail("无此玩家发出的 sos 求助信息！\n");
			do_read( me, i );
			}
		}
		else return notify_fail("格式不对，具体使用方法请参阅 help sos \n");
	return 1;
}

int confirm(string yn, object me)
{
    mapping note;
    object where;
    string s, str,arg1;
    int i,arg2;
    restore();

	if( upper_case(yn) == "Y" ) {

	if(!wiz_level(me)){
	tell_object(me, CYN "你正在" HIY MUD_NAME NOR CYN "里辛苦地挖着泥巴，突然发现一只大个的臭虫向你爬来。\n" NOR);
	tell_object(me, CYN "你赶紧向巫师们发出紧急求助信号：ＳＯＳ！！！\n" NOR);
	where = environment(me);
	if (!where ) 
	s=sprintf("%s求助",log_id(me));
	else
	s=sprintf("%s在[%s]求助", log_id(me), (string)where->query("short"));

//	s=sprintf("%s在%s(%s.c)求助", log_id(me), (string)where->query("short"),
//	(string)file_name(where));
	note = allocate_mapping(6);
	note["title"] = s;
	note["author"] = me->query("id"); 
	note["time"] = time();
	note["solve"] = "";
	note["solve_id"] = "";
	me->edit( (: done_post, me, note :) );
	} else {
	list_bug(me);
	}
	} else {
	write(HIW"您放弃了填写SOS信息。。。。\n"NOR);
	return 1;
	}
}

int help(object me)
{
    if (!wiz_level(me) )
 write(@HELP

指令格式 : 
           sos
           sos read
这个指令可以在系统出现bug时来向巫师求助。
输入该命令后，系统将提示你输入对 bug 的描述。玩家在这里应该将 bug
出现的情况和系统的提示尽量详细地进行说明，以便巫师修改该 bug。
每个玩家只能贴一条 sos，新的 sos 将覆盖以前的输入。
可以用 sos read 阅读自己贴出的 sos。
HELP
 );
    else 
 write(@HELP
指令格式 : 
           sos
           sos <号码或玩家id>
           sos list
           sos del
           sos re <号码或玩家id>
这个指令可以辅助巫师处理玩家提出的 bug 列表。sos 和 sos list 的功能一样，
都是将所有的 bug 信息进行列表。带参数的 sos 命令，根据参数的不同，将显示
对应号码或对应玩家的 bug 的详细信息。sos solve用来标志某个bug已经被解决了。
sos del 将删除所有已经标志为解决了的 bug。
HELP
 );
    return 1;
}

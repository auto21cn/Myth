// Fild：/d/npc/qujing.c
// Changed to heart_beat() by mudring@sjsh......

#include <ansi.h>

inherit F_DBASE;

string *families = ({
  "乌鸡国",
  "宝象国",
  "天竺国",
  "女儿国",
  "玉华县",
  "金平府",
  "五庄观",
  "祭赛国",
  "钦法国",
  "比丘国",
  "朱紫国",
  "车迟国",
  "江洲国",
  "高老庄",
  });

void create()
{
        seteuid(getuid());
        set("channel_id","");

}

void choose_npc()
{
        int i, j ,k,ppl;
        object *list, newob;
        string str;
        object ts,swk,zbj,shs;               

        k = random(sizeof(families));        
        ts = new(__DIR__"ts");
        ts->set("target",families[k]);
        ts->invocation(k);
        message_job( HIW+"如来佛祖"+HIG"：哈哈! 听说有唐三藏师徒已经来到"+families[k]+"了，相信不久就会到达灵山了。");
        reset_eval_cost();
}

  

// skilld.c
// for sjsh lib mudring Nov/24/2002

inherit F_DBASE;
inherit F_CLEAN_UP;


string *path = ({ // 可以使用的skills目录
    "/daemon/skill/",           // 大众skills目录
    "/daemon/skill/basic/",     // 基本skills目录
    "/daemon/skill/quest/",     // 解密skills目录
    "/daemon/skill/lunhui/",    // 轮回skills目录
    "/daemon/skill/other/",     // 其他skills目录
    "/daemon/skill/bonze/",     // 南海普陀山 bonze
    "/daemon/skill/dragon/",    // 东海龙宫 dragon
    "/daemon/skill/fighter/",   // 将军府 fighter
    "/daemon/skill/ghost/",     // 阎罗地府 ghost
    "/daemon/skill/gumu/",      // 轩辕古墓 gumu
    "/daemon/skill/kusong/",    // 火云洞 kusong
    "/daemon/skill/moon/",      // 月宫 moon
    "/daemon/skill/pansi/",     // 盘丝洞 pansi
    "/daemon/skill/puti/",      // 方寸山三星洞 puti
    "/daemon/skill/sanjie/",    // 三界山 sanjie
    "/daemon/skill/shushan/",   // 蜀山剑派 shushan 
    "/daemon/skill/wudidong/",  // 陷空山无底洞 wudidong
    "/daemon/skill/xueshan/",   // 大雪山 xueshan
    "/daemon/skill/zhenyuan/",  // 五庄观 zhenyuan
    "/daemon/skill/test/",      // 替补测试 test
});

mapping search = ([]);

void rehash(string path);

void create()
{
    int i;
    i = sizeof(path);
    set("no_clean_up",1);
    seteuid(geteuid());

    while (i--)
    {
        rehash(path[i]);
    }
}

void rehash(string dir)
{
    int i;
    string *cmds;

    if (dir[sizeof(dir) - 1] != '/')
        dir += "/";
    cmds = get_dir(dir);
    i = sizeof(cmds);
    while (i--)
        if (!sscanf(cmds[i], "%s.c", cmds[i]))
        {
            if (i == 0)
                cmds = cmds[1..sizeof(cmds)];
            else if (i == sizeof(cmds))
                cmds = cmds[0..<2];
            else
                cmds = cmds[0..i - 1] + cmds[i + 1..<1];
        }
    if (sizeof(cmds))
        search[dir] = cmds;
}

string find_skill(string skill)
{
    int i;

    i = sizeof(path);
    while (i--)
    {
        if (undefinedp(search[path[i]]))
            continue;
        if (member_array(skill, search[path[i]]) != -1)
            return path[i] + skill;
    }

    return 0;
}


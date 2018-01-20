#ifndef __STRUCT_AUTO0_H
#define __STRUCT_AUTO0_H

#include "utils.h"
#define CMDS_BASE	0
#define CMDC_BASE	0

#define CMDS_LOGIN	(CMDS_BASE+1)
#define CMDS_LIST	(CMDS_BASE+2)
#define CMDS_CREATE	(CMDS_BASE+3)
#define CMDS_ENTERINFO	(CMDS_BASE+4)
#define CMDS_DELETE	(CMDS_BASE+5)
#define CMDS_HEART	(CMDS_BASE+6)
#define CMDS_NOTIFY	(CMDS_BASE+7)
#define CMDS_ACTORINFO	(CMDS_BASE+8)
#define CMDS_ITEMUSE	(CMDS_BASE+9)
#define CMDS_ITEMPUT	(CMDS_BASE+10)
#define CMDS_ITEMSETTLE	(CMDS_BASE+11)
#define CMDS_LOSTITEM	(CMDS_BASE+12)
#define CMDS_GETITEM	(CMDS_BASE+13)
#define CMDS_ITEMLIST	(CMDS_BASE+14)
#define CMDS_ITEMINFO	(CMDS_BASE+15)
#define CMDS_ADDMAPUNIT	(CMDS_BASE+16)
#define CMDS_DELMAPUNIT	(CMDS_BASE+17)
#define CMDS_UPDATEMAPUNIT	(CMDS_BASE+18)
#define CMDS_MAPUNITSINGLE	(CMDS_BASE+19)
#define CMDS_WORLDMAPINFO	(CMDS_BASE+20)
#define CMDS_MAPUNITCORRDINATE	(CMDS_BASE+21)
#define CMDS_ADDMARCHROUTE	(CMDS_BASE+22)
#define CMDS_DELMARCHROUTE	(CMDS_BASE+23)
#define CMDS_AWARDINFOLIST	(CMDS_BASE+24)
#define CMDS_EXPERIENCE	(CMDS_BASE+25)
#define CMDS_BODY	(CMDS_BASE+26)
#define CMDS_BUILDINGLIST	(CMDS_BASE+27)
#define CMDS_CHANGELEVY	(CMDS_BASE+28)
#define CMDS_CHANGESILVER	(CMDS_BASE+29)
#define CMDS_CHANGEWOOD	(CMDS_BASE+30)
#define CMDS_CHANGEFOOD	(CMDS_BASE+31)
#define CMDS_CHANGEIRON	(CMDS_BASE+32)
#define CMDS_CHANGEPEOPLE	(CMDS_BASE+33)
#define CMDS_CHANGEPRESTIGE	(CMDS_BASE+34)
#define CMDS_CHANGEFRIENDSHIP	(CMDS_BASE+35)
#define CMDS_CHANGEVIP	(CMDS_BASE+36)
#define CMDS_CHANGTOKEN	(CMDS_BASE+37)
#define CMDS_EQUIP	(CMDS_BASE+38)
#define CMDS_EQUIPLIST	(CMDS_BASE+39)
#define CMDS_EQUIPGET	(CMDS_BASE+40)
#define CMDS_EQUIPLOST	(CMDS_BASE+41)
#define CMDS_HERO	(CMDS_BASE+42)
#define CMDS_HEROLIST	(CMDS_BASE+43)
#define CMDS_HEROEXP	(CMDS_BASE+44)
#define CMDS_HEROSOLDIERS	(CMDS_BASE+45)
#define CMDS_HEROSTATE	(CMDS_BASE+46)
#define CMDS_HEROREPLACE	(CMDS_BASE+47)
#define CMDS_BUILDINGUPGRADEINFO	(CMDS_BASE+48)
#define CMDS_BUILDING	(CMDS_BASE+49)
#define CMDS_BUILDINGBARRACKS	(CMDS_BASE+50)
#define CMDS_BUILDINGRES	(CMDS_BASE+51)
#define CMDS_WORKER	(CMDS_BASE+52)
#define CMDS_HEROGET	(CMDS_BASE+53)
#define CMDS_BUILDINGGET	(CMDS_BASE+54)
#define CMDS_BUILDINGBARRACKSGET	(CMDS_BASE+55)
#define CMDS_BUILDINGRESGET	(CMDS_BASE+56)
#define CMDS_SOLDIERS	(CMDS_BASE+57)
#define CMDS_TRAININFO	(CMDS_BASE+58)
#define CMDS_QUEST	(CMDS_BASE+59)
#define CMDS_QUESTLIST	(CMDS_BASE+60)
#define CMDS_QUESTAWARD	(CMDS_BASE+61)
#define CMDS_FUNCTION	(CMDS_BASE+62)
#define CMDS_CITYGUARD	(CMDS_BASE+63)
#define CMDS_CITYGUARDLIST	(CMDS_BASE+64)
#define CMDS_CITYGUARDSEC	(CMDS_BASE+65)
#define CMDS_BUILDINGSMITHY	(CMDS_BASE+66)
#define CMDS_CHANGENAME	(CMDS_BASE+67)
#define CMDS_BUILDINGACTION	(CMDS_BASE+68)
#define CMDS_LEVYINFO	(CMDS_BASE+69)
#define CMDS_CHAT	(CMDS_BASE+70)
#define CMDS_CHATLIST	(CMDS_BASE+71)
#define CMDS_SYSTALKID	(CMDS_BASE+72)
#define CMDS_SYSTALK	(CMDS_BASE+73)
#define CMDS_BATTLEPOWER	(CMDS_BASE+74)
#define CMDS_TECHCHANGE	(CMDS_BASE+75)
#define CMDS_CITYEVENTLIST	(CMDS_BASE+76)
#define CMDS_OFFICIALHIRECHANGE	(CMDS_BASE+77)
#define CMDS_CITYPROTECT	(CMDS_BASE+78)
#define CMDS_HEROEQUIP	(CMDS_BASE+79)
#define CMDS_HEROWASH	(CMDS_BASE+80)
#define CMDS_HEROCOLORUP	(CMDS_BASE+81)
#define CMDS_CITYATTR	(CMDS_BASE+82)
#define CMDS_EQUIPWASH	(CMDS_BASE+83)
#define CMDS_MATERIALLIST	(CMDS_BASE+84)
#define CMDS_MATERIALWILLLIST	(CMDS_BASE+85)
#define CMDS_STORYLIST	(CMDS_BASE+86)
#define CMDS_STORYRANK	(CMDS_BASE+87)
#define CMDS_STORYSTATE	(CMDS_BASE+88)
#define CMDS_STORYRANKNUM	(CMDS_BASE+89)
#define CMDS_STORYRANKTIME	(CMDS_BASE+90)
#define CMDS_MAPZONECHANGE	(CMDS_BASE+91)
#define CMDS_MAPZONEUNITLIST	(CMDS_BASE+92)
#define CMDS_MAPZONEUNIT	(CMDS_BASE+93)
#define CMDS_ARMYSPEEDUPDATE	(CMDS_BASE+94)
#define CMDS_BATTLELIST	(CMDS_BASE+95)
#define CMDS_BATTLEINFO	(CMDS_BASE+96)
#define CMDS_MAPRESINFO	(CMDS_BASE+97)
#define CMDS_WEATHERCHANGE	(CMDS_BASE+98)
#define CMDS_MAIL	(CMDS_BASE+99)
#define CMDS_MAILOPRESULT	(CMDS_BASE+100)
#define CMDS_MAILFIGHT	(CMDS_BASE+101)
#define CMDS_MAILVIEW	(CMDS_BASE+102)
#define CMDS_CITYHELP	(CMDS_BASE+103)
#define CMDS_CITYHELPLIST	(CMDS_BASE+104)
#define CMDS_MAPCITYHELPLIST	(CMDS_BASE+105)
#define CMDS_CITYSTATE	(CMDS_BASE+106)
#define CMDS_CITYARMYGROUP	(CMDS_BASE+107)
#define CMDS_CITYARMYGROUPLIST	(CMDS_BASE+108)
#define CMDS_MAPTOWNINFO	(CMDS_BASE+109)
#define CMDS_TOWNARMYGROUP	(CMDS_BASE+110)
#define CMDS_TOWNARMYGROUPLIST	(CMDS_BASE+111)
#define CMDS_SYSTALKJSON	(CMDS_BASE+112)
#define CMDS_ROLLMSGJSON	(CMDS_BASE+113)
#define CMDS_ROLLMSG	(CMDS_BASE+114)
#define CMDS_TOWNOWNERASKLIST	(CMDS_BASE+115)
#define CMDS_TOWNFIGHTLIST	(CMDS_BASE+116)
#define CMDS_DIALOGUPDATE	(CMDS_BASE+117)
#define CMDS_MAPTOWNEXINFO	(CMDS_BASE+118)
#define CMDS_MAPZONETOWN	(CMDS_BASE+119)
#define CMDS_MAPZONETOWNLIST	(CMDS_BASE+120)
#define CMDS_MAPCENTERTOWN	(CMDS_BASE+121)
#define CMDS_MAPCENTERTOWNLIST	(CMDS_BASE+122)
#define CMDS_CITYWARINFO	(CMDS_BASE+123)
#define CMDS_CITYWARLIST	(CMDS_BASE+124)
#define CMDS_CITYWARDEL	(CMDS_BASE+125)
#define CMDS_WORLDQUEST	(CMDS_BASE+126)
#define CMDS_WORLDBOSS	(CMDS_BASE+127)
#define CMDS_LOSTREBUILD	(CMDS_BASE+128)
#define CMDS_KINGWARTOWN	(CMDS_BASE+129)
#define CMDS_KINGWARTOWNLIST	(CMDS_BASE+130)
#define CMDS_KINGWARACTIVITY	(CMDS_BASE+131)
#define CMDS_KINGWARNOTIFY	(CMDS_BASE+132)
#define CMDS_KINGWARNOTIFYLIST	(CMDS_BASE+133)
#define CMDS_KINGWARRANKLIST	(CMDS_BASE+134)
#define CMDS_KINGWARPK	(CMDS_BASE+191)
#define CMDS_KINGWARPOINT	(CMDS_BASE+192)
#define CMDS_TREASUREACTIVITY	(CMDS_BASE+193)
#define CMDS_TREASUREHAS	(CMDS_BASE+194)
#define CMDS_GOTOASYN	(CMDS_BASE+195)
#define CMDS_TREASUREACTORLIST	(CMDS_BASE+197)
#define CMDS_CHANGEAUTOBUILD	(CMDS_BASE+198)
#define CMDS_HEROVISITINFO	(CMDS_BASE+199)
#define CMDS_NATIONBASE	(CMDS_BASE+200)
#define CMDS_HEROVISITAWARD	(CMDS_BASE+202)
#define CMDS_FIGHTPLAY	(CMDS_BASE+203)
#define CMDS_STORYSWEEPRESULT	(CMDS_BASE+205)
#define CMDS_QUESTTALK	(CMDS_BASE+206)
#define CMDS_RANKLIST	(CMDS_BASE+209)
#define CMDS_FRIENDLIST	(CMDS_BASE+212)
#define CMDS_ACTORSEARCH	(CMDS_BASE+214)
#define CMDS_BLACKINFO	(CMDS_BASE+215)
#define CMDS_BLACKLIST	(CMDS_BASE+216)
#define CMDS_BLACKLISTID	(CMDS_BASE+217)
#define CMDS_NATIONEQUIP	(CMDS_BASE+218)
#define CMDS_SHOPLIST	(CMDS_BASE+220)
#define CMDS_PAYSTORE	(CMDS_BASE+222)
#define CMDS_GOODSINFO	(CMDS_BASE+223)
#define CMDS_PAYSTOREACTIVITY	(CMDS_BASE+224)
#define CMDS_PAYORDER	(CMDS_BASE+225)
#define CMDS_VIPSHOP	(CMDS_BASE+227)
#define CMDS_VIPBAG	(CMDS_BASE+228)
#define CMDS_BUFFCHANGE	(CMDS_BASE+229)
#define CMDS_CHANGEAUTOGUARD	(CMDS_BASE+230)
#define CMDS_ACTIVITYLIST	(CMDS_BASE+232)
#define CMDS_NATIONEQUIPLIST	(CMDS_BASE+233)
#define CMDS_NATIONINFO	(CMDS_BASE+234)
#define CMDS_NATIONTOWN	(CMDS_BASE+235)
#define CMDS_NATIONTOWNLIST	(CMDS_BASE+236)
#define CMDS_NATIONWARLIST	(CMDS_BASE+238)
#define CMDS_NATIONCITYWARLIST	(CMDS_BASE+240)
#define CMDS_NATIONQUESTLIST	(CMDS_BASE+242)
#define CMDS_NATIONMISSIONLIST	(CMDS_BASE+244)
#define CMDS_NATIONRANKLIST	(CMDS_BASE+246)
#define CMDS_NATIONOFFICIALLIST	(CMDS_BASE+248)
#define CMDS_NATIONCANDIDATELIST	(CMDS_BASE+250)
#define CMDS_WORLDDATAOPEN	(CMDS_BASE+251)
#define CMDS_NATIONREPLACELIST	(CMDS_BASE+253)

#define CMDC_USERAWARDED	(CMDC_BASE-4)
#define CMDC_GMLOCALCMD	(CMDC_BASE-3)
#define CMDC_LOGINED	(CMDC_BASE-2)
#define CMDC_TIMER	(CMDC_BASE-1)
#define CMDC_LOGIN	(CMDC_BASE+1)
#define CMDC_CREATE	(CMDC_BASE+2)
#define CMDC_LIST	(CMDC_BASE+3)
#define CMDC_ENTERGAME	(CMDC_BASE+4)
#define CMDC_DELETE	(CMDC_BASE+5)
#define CMDC_HEART	(CMDC_BASE+6)
#define CMDC_GMCMD	(CMDC_BASE+7)
#define CMDC_ASKINFO	(CMDC_BASE+9)
#define CMDC_ENTERCITY	(CMDC_BASE+10)
#define CMDC_CHAT	(CMDC_BASE+11)
#define CMDC_STORYBATTLE	(CMDC_BASE+12)
#define CMDC_WORLDMAPASK	(CMDC_BASE+13)
#define CMDC_WORLDMAPAREAINDEX	(CMDC_BASE+14)
#define CMDC_MAPBATTLE	(CMDC_BASE+15)
#define CMDC_MAILASK	(CMDC_BASE+16)
#define CMDC_MAILOP	(CMDC_BASE+17)
#define CMDC_MAILALLDEL	(CMDC_BASE+18)
#define CMDC_MAILSHARE	(CMDC_BASE+19)
#define CMDC_MAILSEND	(CMDC_BASE+20)
#define CMDC_MAILREPLY	(CMDC_BASE+21)
#define CMDC_WORLDBOSSBATTLE	(CMDC_BASE+22)
#define CMDC_HEROGUARDSORT	(CMDC_BASE+23)
#define CMDC_QUESTTALKNEXT	(CMDC_BASE+24)
#define CMDC_RANKLISTASK	(CMDC_BASE+25)
#define CMDC_FRIENDOP	(CMDC_BASE+26)
struct _slk_NetU_Logined {
	int m_result;	//用户服务器返回-登录返回值
	int m_client_index;	//用户服务器返回-角色索引
	int m_authid;	//用户服务器返回-认证ID
	char m_userid[21];	//用户服务器返回-用户ID
	char m_username[51];	//用户服务器返回-用户名
	short m_usertype;	//用户服务器返回-用户类型
	char m_checkflag;	//用户服务器返回-检测标记
	char m_isdeep;	//用户服务器返回-要防沉迷
	char m_access_token[65];	//用户服务器返回-360的用户令牌
	int m_expires_in;	//用户服务器返回-360的令牌有效期
	char m_refresh_token[65];	//用户服务器返回-360的刷新令牌
	char m_deviceid[65];	//用户服务器返回-传回的设备ID
};
typedef struct _slk_NetU_Logined SLK_NetU_Logined;	//用户服务器返回登陆

struct _slk_NetU_UserAwarded {
	int m_result;	//用户服务器返回-兑换结果返回值
	int m_client_index;	//用户服务器返回-角色索引
	int m_authid;	//用户服务器返回-认证ID
	short m_cdkey_index;	//用户服务器返回-兑换码存档索引
	int m_awardgroup;	//用户服务器返回-兑换码奖励组
	char m_cardnumber[32];	//用户服务器返回-兑换码卡号
};
typedef struct _slk_NetU_UserAwarded SLK_NetU_UserAwarded;	//用户服务器返回兑换奖励

struct _slk_NetU_Gmlocalcmd {
	short m_cmd;	//指令
	int m_value[4];	//数值参数
	short m_msglen;	//字符串长度
	char m_msg[1024];	//字符串参数
};
typedef struct _slk_NetU_Gmlocalcmd SLK_NetU_Gmlocalcmd;	//本地GM信息

int struct_NetU_Logined_send( char **pptr, int *psize, SLK_NetU_Logined *pValue );
int struct_NetU_Logined_recv( char **pptr, int *psize, SLK_NetU_Logined *pValue );
int struct_NetU_UserAwarded_send( char **pptr, int *psize, SLK_NetU_UserAwarded *pValue );
int struct_NetU_UserAwarded_recv( char **pptr, int *psize, SLK_NetU_UserAwarded *pValue );
int struct_NetU_Gmlocalcmd_send( char **pptr, int *psize, SLK_NetU_Gmlocalcmd *pValue );
int struct_NetU_Gmlocalcmd_recv( char **pptr, int *psize, SLK_NetU_Gmlocalcmd *pValue );

#endif

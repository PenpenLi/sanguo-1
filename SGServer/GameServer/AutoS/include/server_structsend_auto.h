#ifndef __STRUCTSEND0_AUTO_H
#define __STRUCTSEND0_AUTO_H
#include "server_struct_auto.h"

struct _slk_NetS_Login {
	int m_result;	//����������-����ֵ
	short m_username_length;	//����������-�û�������
	char m_username[51];	//����������-�û���
	short m_token_length;	//����������-token����
	char m_token[256];	//����������-token
	short m_usertype;	//����������-�û�����
};
typedef struct _slk_NetS_Login SLK_NetS_Login;	//�������˷��͵�¼������ͻ���

struct _slk_ListInfo {
	int m_actorid;	//��ɫID
	char m_name[22];	//��ɫ����
	char m_nation;	//��ɫ����
	short m_level;	//��ɫ�ȼ�
	char m_offset;	//��ɫλ��
	char m_lockstat;	//����״̬
	int m_delete_stoptime;	//ɾ��ʱ��
	int m_lock_endtime;	//����ʱ��
};
typedef struct _slk_ListInfo SLK_ListInfo;	//������ɫ���б���Ϣ

struct _slk_NetS_List {
	char m_actor_num;	//����˷���-��ɫ����
	SLK_ListInfo m_listinfo[8];	//����˷���-��ɫ����
};
typedef struct _slk_NetS_List SLK_NetS_List;	//�������˷��ͽ�ɫ�б�

struct _slk_NetS_Create {
	char m_result;	//����˷���-������ɫ�Ľ��
	int m_actorid;	//����˷���-������ɫ�ı��
	int m_createtime;	//����˷���-������ɫ��ʱ��
};
typedef struct _slk_NetS_Create SLK_NetS_Create;	//���������ش�����ɫ���

struct _slk_NetS_EnterInfo {
	int m_actorid;	//����˷���-������Ϸ��ɫID
	int m_data_int;	//����˷���-������Ϸ��������[����]
	short m_data_short;	//����˷���-������Ϸ��������[����]
	char m_data_char;	//����˷���-������Ϸ��������[����]
	short m_serverid;	//����˷���-����ķ�����ID
	int m_servertime;	//����˷���-����ķ�����ʱ���
	int m_createtime;	//����˷���-������ɫʱ��
};
typedef struct _slk_NetS_EnterInfo SLK_NetS_EnterInfo;	//���������ؽ�����Ϸ�����Ϣ

struct _slk_NetS_Delete {
	int m_result;	//����������-ɾ������ֵ
	int m_actorid;	//����������-ɾ���Ľ�ɫ���
};
typedef struct _slk_NetS_Delete SLK_NetS_Delete;	//����������ɾ����ɫ

struct _slk_NetS_Heart {
	int m_value[2];	//����-��ֵ
};
typedef struct _slk_NetS_Heart SLK_NetS_Heart;	//����

struct _slk_NetS_Notify {
	short m_msgid;	//����������-����ϢID
	short m_valuenum;	//����������-����Ϣ��������
	int m_value[10];	//����������-����Ϣ��ֵ����
	short m_msg_length;	//����������-����Ϣ�ַ�����Ϣ����
	char m_msg[256];	//����������-����Ϣ�ַ�������
};
typedef struct _slk_NetS_Notify SLK_NetS_Notify;	//ͨ�ö���Ϣ

struct _slk_NetS_Building {
	char m_kind;	//��ͨ����-����
	char m_offset;	//��ͨ����-λ��
	char m_level;	//��ͨ����-�ȼ�
	int m_sec;	//��ͨ����-����ʣ��ʱ��
	int m_needsec;	//
	char m_quick;	//��ͨ����-�Ƿ��м���(�Ƽ���)
};
typedef struct _slk_NetS_Building SLK_NetS_Building;	//��ͨ������Ϣ

struct _slk_NetS_BuildingBarracks {
	char m_kind;	//��Ӫ����-����
	char m_offset;	//��Ӫ����-λ��
	char m_level;	//��Ӫ����-�ȼ�
	int m_sec;	//��Ӫ����-ļ��ʣ��ʱ��
	int m_needsec;	//
	char m_quick;	//��Ӫ����-�Ƿ��м���
};
typedef struct _slk_NetS_BuildingBarracks SLK_NetS_BuildingBarracks;	//��Ӫ������Ϣ

struct _slk_NetS_BuildingRes {
	char m_kind;	//��Դ����-����
	char m_offset;	//��Դ����-����(��Ӧָ���ؿ�)
	char m_level;	//��Դ����-�ȼ�
};
typedef struct _slk_NetS_BuildingRes SLK_NetS_BuildingRes;	//��Դ������Ϣ

struct _slk_NetS_BuildingList {
	short m_building_count;	//����������-��ͨ��������
	SLK_NetS_Building m_building[8];	//����������-��ͨ�����б�
	short m_barracks_count;	//����������-��Ӫ��������
	SLK_NetS_BuildingBarracks m_barracks[8];	//����������-��Ӫ�����б�
	short m_res_count;	//����������-��Դ��������
	SLK_NetS_BuildingRes m_res[64];	//����������-��Դ�����б�
	char m_levynum;	//����������-��ǰ�����մ���
	char m_worker_kind;	//����������-������������
	char m_worker_offset;	//���������ͽ�����������
	char m_worker_op;	//����������-�������н�������
	int m_worker_sec;	//����������-��������ʣ��ʱ��
	int m_worker_needsec;	//
	char m_worker_kind_ex;	//����������-������������(����)
	char m_worker_offset_ex;	//����������-������������(����)
	char m_worker_op_ex;	//����������-�������в���(����)
	int m_worker_sec_ex;	//����������-��������ʣ��ʱ��(����)
	int m_worker_needsec_ex;	//
	int m_worker_expire_ex;	//����������-���ý�����е���ʱ��
	int m_function;	//����������-�����Ƿ���
};
typedef struct _slk_NetS_BuildingList SLK_NetS_BuildingList;	//�����б�

struct _slk_NetS_ActorInfo {
	int m_actorid;	//������������һ�����Ϣ-��ɫ���
	char m_name[22];	//������������һ�����Ϣ-��ɫ����
	char m_nation;	//������������һ�����Ϣ-����
	char m_shape;	//������������һ�����Ϣ-����
	short m_level;	//������������һ�����Ϣ-����
	int m_exp;	//������������һ�����Ϣ-����
	int m_exp_max;	//������������һ�����Ϣ-��������
	int m_token;	//������������һ�����Ϣ-��ʯ
	char m_viplevel;	//������������һ�����Ϣ-VIP�ȼ�
	int m_vipexp;	//������������һ�����Ϣ-VIP����
	int m_vipexp_max;	//������������һ�����Ϣ-VIP��������
	short m_body;	//������������һ�����Ϣ-����
	char m_place;	//������������һ�����Ϣ-��λ
	char m_official;	//������������һ�����Ϣ-��ְ
	short m_zone;	//������������һ�����Ϣ-����
	int m_battlepower;	//������������һ�����Ϣ-ս��
	short m_silver;	//������������һ�����Ϣ-����
	short m_wood;	//������������һ�����Ϣ-ľ��
	short m_food;	//������������һ�����Ϣ-��ʳ
	short m_iron;	//������������һ�����Ϣ-����
	int m_infantry_num;	//������������һ�����Ϣ-������
	int m_cavalry_num;	//������������һ�����Ϣ-�����
	int m_archer_num;	//������������һ�����Ϣ-������
	short m_mokilllv;	//������������һ�����Ϣ-��ɱҰ����߼���
	int m_sflag;	//������������һ�����Ϣ-��־λ
};
typedef struct _slk_NetS_ActorInfo SLK_NetS_ActorInfo;	//��ɫ������Ϣ

struct _slk_Corrdinate {
	short m_posx;	//����
	short m_posy;	//����
};
typedef struct _slk_Corrdinate SLK_Corrdinate;	//����

struct _slk_NetS_ItemUse {
	short m_itemoffset;	//��Ʒλ��
	short m_usenum;	//ʹ�ø�����װ��λ��
	int m_effres;	//Ӱ�죬һ��������Ч��ʾ
};
typedef struct _slk_NetS_ItemUse SLK_NetS_ItemUse;	//����ʹ��

struct _slk_NetS_ItemPut {
	short m_res_offset;	//��ƷԴ
	short m_res_num;	//��ƷԴ����
	short m_target_offset;	//��ƷĿ��
	short m_target_num;	//Ŀ�����
};
typedef struct _slk_NetS_ItemPut SLK_NetS_ItemPut;	//���߷���|ж��

struct _slk_NetS_ItemSettle {
	short m_itemnum;	//�������ĸ���
	short m_itemoffset[100];	//���õ���Ʒλ��
};
typedef struct _slk_NetS_ItemSettle SLK_NetS_ItemSettle;	//��������

struct _slk_NetS_LostItem {
	short m_itemoffset;	//��Ʒλ��
	short m_itemnum;	//����
	int m_targetid;	//����Ķ���id
	short m_path;	//;��
};
typedef struct _slk_NetS_LostItem SLK_NetS_LostItem;	//��ʧ����

struct _slk_NetS_GetItem {
	short m_itemoffset;	//��Ʒλ��
	short m_kind;	//��Ʒ����
	short m_type;	//��Ʒ����
	char m_color;	//��ɫ
	short m_num;	//����
	int m_targetid;	//����Ķ���id
	short m_path;	//;��
	unsigned char m_situation;	//ʹ��״̬
};
typedef struct _slk_NetS_GetItem SLK_NetS_GetItem;	//��õ���

struct _slk_ItemSmpInfo {
	short m_offset;	//��Ʒλ��
	short m_kind;	//��Ʒ����
	short m_num;	//����
	unsigned char m_situation;	//ʹ��״̬
	char m_color_level;	//��ɫ
};
typedef struct _slk_ItemSmpInfo SLK_ItemSmpInfo;	//���߼�����Ϣ

struct _slk_NetS_ItemList {
	char m_itemext;	//��չ�ĸ���
	short m_kindnum;	//��Ʒ����
	SLK_ItemSmpInfo m_item[300];	//��Ʒ
};
typedef struct _slk_NetS_ItemList SLK_NetS_ItemList;	//�����б�

struct _slk_ItemAttr {
	short m_type;	//��Ʒ������������
	short m_ability;	//��Ʒ����
	int m_value;	//��Ʒ����
	int m_addvalue;	//��Ʒ��������
};
typedef struct _slk_ItemAttr SLK_ItemAttr;	//��������

struct _slk_NetS_ItemInfo {
	short m_itemoffset;	//��Ʒλ��
	short m_itemkind;	//װ��kind,У��
	short m_type;	//��Ʒ����
	short m_level;	//һ��ȼ�
	char m_color_level;	//��ɫ�ּ�
	int m_price;	//�ۼ�
	short m_attr_num;	//���Ը���
	SLK_ItemAttr m_attr[10];	//����
};
typedef struct _slk_NetS_ItemInfo SLK_NetS_ItemInfo;	//������Ϣ

struct _slk_WalkPath {
	short m_pathx[100];	//·����ṹ
	short m_pathy[100];	//·����ṹ
	short m_len;	//·����ṹ
};
typedef struct _slk_WalkPath SLK_WalkPath;	//�ƶ�·��

struct _slk_NetS_AddMapUnit {
	char m_type;	//��ͼ��Ԫ-����
	char m_state;	//��ͼ��Ԫ-״̬
	short m_posx;	//��ͼ��Ԫ-��ǰ����
	int m_unit_index;	//��ͼ��Ԫ-���
	short m_posy;	//��ͼ��Ԫ-��ǰ����
	char m_namelen;	//��ͼ��Ԫ-���Ƴ���
	char m_name[32];	//��ͼ��Ԫ-����
	char m_char_value_count;	//��ͼ��Ԫ-ͨ���ֶγ���
	char m_char_value[16];	//��ͼ��Ԫ-ͨ���ֶ�
	char m_short_value_count;	//��ͼ��Ԫ-ͨ���ֶγ���
	short m_short_value[8];	//��ͼ��Ԫ-ͨ���ֶ�
	char m_int_value_count;	//��ͼ��Ԫ-ͨ���ֶγ���
	int m_int_value[8];	//��ͼ��Ԫ-ͨ���ֶ�
	char m_prefixlen;	//��ͼ��Ԫ-�ƺų���
	char m_prefix[22];	//��ͼ��Ԫ-�ƺ�
};
typedef struct _slk_NetS_AddMapUnit SLK_NetS_AddMapUnit;	//��ʾ��Ԫ�����ͼ

struct _slk_NetS_DelMapUnit {
	int m_unit_index;	//��ͼ��Ԫ-���
};
typedef struct _slk_NetS_DelMapUnit SLK_NetS_DelMapUnit;	//��ʾ��Ԫ�뿪��ͼ

struct _slk_NetS_WorldMapInfo {
	short m_map_width;	//�����ͼ��С����������
	short m_map_height;	//�����ͼ��С����������
	char m_area_width;	//�����С��һ�����򼸸���ͼ���ӣ�
	char m_area_height;	//�����С��һ�����򼸸���ͼ���ӣ�
	short m_map_area_xnum;	//һ����ͼ�ж�������
	short m_map_area_ynum;	//һ����ͼ�ж�������
	short m_my_city_posx;	//�ҵĳǳ�λ��
	short m_my_city_posy;	//�ҵĳǳ�λ��
	int m_my_city_unit_index;	//�ҵĳǳص�ͼ��Ԫ-���
	char m_citystate;	//�ҵĳǳ�״̬
	short m_target_posx;	//Ŀ�ĵ�
	short m_target_posy;	//Ŀ�ĵ�
};
typedef struct _slk_NetS_WorldMapInfo SLK_NetS_WorldMapInfo;	//�����ͼ��Ϣ

struct _slk_NetS_MapUnitCorrdinate {
	int m_unit_index;	//��ͼ��Ԫ-���
	short m_posx;	//��ͼ��Ԫ-��ǰ����
	short m_posy;	//��ͼ��Ԫ-��ǰ����
};
typedef struct _slk_NetS_MapUnitCorrdinate SLK_NetS_MapUnitCorrdinate;	//��ͼ��ʾ��Ԫλ��

struct _slk_NetS_AddMarchRoute {
	char m_from_type;	//�о�·��-������Ԫ����
	short m_from_posx;	//�о�·��-����λ��
	short m_from_posy;	//�о�·��-����λ��
	char m_to_type;	//�о�·��-���ﵥԪ����
	short m_to_posx;	//�о�·��-����λ��
	short m_to_posy;	//�о�·��-����λ��
	char m_state;	//�о�·��-״̬
	int m_from_actorid;	//�о�·��-����
	int m_from_clubid;	//�о�·��-����
	int m_to_actorid;	//�о�·��-Ŀ�����
	int m_to_clubid;	//�о�·��-Ŀ������
	int m_army_index;	//�о�·��-��������
	char m_action;	//�о�·��-��Ϊ
};
typedef struct _slk_NetS_AddMarchRoute SLK_NetS_AddMarchRoute;	//�о�·��

struct _slk_NetS_DelMarchRoute {
	int m_army_index;	//ɾ����-��������
};
typedef struct _slk_NetS_DelMarchRoute SLK_NetS_DelMarchRoute;	//ɾ���о�·��

struct _slk_NetS_UpdateMapUnit {
	SLK_NetS_AddMapUnit m_info;	//���µ�ͼ��ʾ��Ԫ��Ϣ
};
typedef struct _slk_NetS_UpdateMapUnit SLK_NetS_UpdateMapUnit;	//���µ�ͼ��ʾ��Ԫ��Ϣ

struct _slk_NetS_Equip {
	short m_offset;	//װ������
	short m_kind;	//װ������
	short m_washid[4];	//ϴ������
};
typedef struct _slk_NetS_Equip SLK_NetS_Equip;	//װ��

struct _slk_NetS_EquipList {
	short m_equipext;	//װ������չ
	short m_count;	//װ������
	SLK_NetS_Equip m_list[100];	//װ��
};
typedef struct _slk_NetS_EquipList SLK_NetS_EquipList;	//װ���б�

struct _slk_NetS_EquipGet {
	int m_offset;	//���һ��װ��
	short m_kind;	//���һ��װ��
	short m_path;	//���һ��װ��
};
typedef struct _slk_NetS_EquipGet SLK_NetS_EquipGet;	//���һ��װ��

struct _slk_NetS_EquipLost {
	int m_offset;	//����һ��װ��
	short m_kind;	//����һ��װ��
	short m_path;	//����һ��װ��
};
typedef struct _slk_NetS_EquipLost SLK_NetS_EquipLost;	//����һ��װ��

struct _slk_NetS_AwardInfo {
	int m_kind;	//����
	int m_num;	//����
};
typedef struct _slk_NetS_AwardInfo SLK_NetS_AwardInfo;	//������Ϣ

struct _slk_NetS_AwardInfoList {
	short m_count;	//��������
	SLK_NetS_AwardInfo m_list[32];	//�����б�
	short m_callback_code;	//�ĸ�ϵͳҪ��ʾ���ش�
};
typedef struct _slk_NetS_AwardInfoList SLK_NetS_AwardInfoList;	//������Ϣ�б�

struct _slk_NetS_Experience {
	int m_addexp;	//����������-��ȡ����
	int m_curexp;	//����������-��ȡ����
	char m_isup;	//����������-��ȡ����
	short m_path;	//����������-��ȡ����
	short m_level;	//����������-��ȡ����
	int m_expmax;	//����������-��ȡ����
};
typedef struct _slk_NetS_Experience SLK_NetS_Experience;	//�ı侭��

struct _slk_NetS_Body {
	short m_total;	//����
	short m_add;	//��ȡ����
	short m_path;	//;��
};
typedef struct _slk_NetS_Body SLK_NetS_Body;	//�ı�����

struct _slk_NetS_Levy {
	short m_total;	//�ı����մ���
	short m_add;	//�ı����մ���
	short m_max;	//�ı����մ���
	int m_sec;	//�ı����մ���
	short m_path;	//�ı����մ���
};
typedef struct _slk_NetS_Levy SLK_NetS_Levy;	//�ı����մ���

struct _slk_NetS_Silver {
	int m_total;	//�ı�����
	int m_add;	//�ı�����
	short m_path;	//�ı�����
};
typedef struct _slk_NetS_Silver SLK_NetS_Silver;	//�ı�����

struct _slk_NetS_Wood {
	int m_total;	//�ı�ľ��
	int m_add;	//�ı�ľ��
	short m_path;	//�ı�ľ��
};
typedef struct _slk_NetS_Wood SLK_NetS_Wood;	//�ı�ľ��

struct _slk_NetS_Food {
	int m_total;	//�ı���ʳ
	int m_add;	//�ı���ʳ
	short m_path;	//�ı���ʳ
};
typedef struct _slk_NetS_Food SLK_NetS_Food;	//�ı���ʳ

struct _slk_NetS_Iron {
	int m_total;	//�ı�����
	int m_add;	//�ı�����
	short m_path;	//�ı�����
};
typedef struct _slk_NetS_Iron SLK_NetS_Iron;	//�ı�����

struct _slk_NetS_People {
	int m_total;	//�ı��˿�
	int m_add;	//�ı��˿�
	short m_path;	//�ı��˿�
};
typedef struct _slk_NetS_People SLK_NetS_People;	//�ı��˿�

struct _slk_NetS_Prestige {
	int m_total;	//�ı�����ֵ
	int m_add;	//�ı�����ֵ
	short m_path;	//�ı�����ֵ
};
typedef struct _slk_NetS_Prestige SLK_NetS_Prestige;	//�ı�����ֵ

struct _slk_NetS_Friendship {
	int m_total;	//�ı��������
	int m_add;	//�ı��������
	short m_path;	//�ı��������
};
typedef struct _slk_NetS_Friendship SLK_NetS_Friendship;	//�ı��������

struct _slk_NetS_Vip {
	int m_addexp;	//�ı�VIP����
	int m_curexp;	//�ı�VIP����
	int m_expmax;	//�ı�VIP����
	char m_isup;	//�ı�VIP����
	char m_level;	//�ı�VIP����
	short m_path;	//�ı�VIP����
};
typedef struct _slk_NetS_Vip SLK_NetS_Vip;	//�ı�VIP����

struct _slk_NetS_Token {
	int m_total;	//�ı���ʯ
	int m_add;	//�ı���ʯ
	short m_path;	//�ı���ʯ
};
typedef struct _slk_NetS_Token SLK_NetS_Token;	//�ı���ʯ

int struct_NetS_Login_send( char **pptr, int *psize, SLK_NetS_Login *pValue );
int struct_ListInfo_send( char **pptr, int *psize, SLK_ListInfo *pValue );
int struct_NetS_List_send( char **pptr, int *psize, SLK_NetS_List *pValue );
int struct_NetS_Create_send( char **pptr, int *psize, SLK_NetS_Create *pValue );
int struct_NetS_EnterInfo_send( char **pptr, int *psize, SLK_NetS_EnterInfo *pValue );
int struct_NetS_Delete_send( char **pptr, int *psize, SLK_NetS_Delete *pValue );
int struct_NetS_Heart_send( char **pptr, int *psize, SLK_NetS_Heart *pValue );
int struct_NetS_Notify_send( char **pptr, int *psize, SLK_NetS_Notify *pValue );
int struct_NetS_Building_send( char **pptr, int *psize, SLK_NetS_Building *pValue );
int struct_NetS_BuildingBarracks_send( char **pptr, int *psize, SLK_NetS_BuildingBarracks *pValue );
int struct_NetS_BuildingRes_send( char **pptr, int *psize, SLK_NetS_BuildingRes *pValue );
int struct_NetS_BuildingList_send( char **pptr, int *psize, SLK_NetS_BuildingList *pValue );
int struct_NetS_ActorInfo_send( char **pptr, int *psize, SLK_NetS_ActorInfo *pValue );
int struct_Corrdinate_send( char **pptr, int *psize, SLK_Corrdinate *pValue );
int struct_NetS_ItemUse_send( char **pptr, int *psize, SLK_NetS_ItemUse *pValue );
int struct_NetS_ItemPut_send( char **pptr, int *psize, SLK_NetS_ItemPut *pValue );
int struct_NetS_ItemSettle_send( char **pptr, int *psize, SLK_NetS_ItemSettle *pValue );
int struct_NetS_LostItem_send( char **pptr, int *psize, SLK_NetS_LostItem *pValue );
int struct_NetS_GetItem_send( char **pptr, int *psize, SLK_NetS_GetItem *pValue );
int struct_ItemSmpInfo_send( char **pptr, int *psize, SLK_ItemSmpInfo *pValue );
int struct_NetS_ItemList_send( char **pptr, int *psize, SLK_NetS_ItemList *pValue );
int struct_ItemAttr_send( char **pptr, int *psize, SLK_ItemAttr *pValue );
int struct_NetS_ItemInfo_send( char **pptr, int *psize, SLK_NetS_ItemInfo *pValue );
int struct_WalkPath_send( char **pptr, int *psize, SLK_WalkPath *pValue );
int struct_NetS_AddMapUnit_send( char **pptr, int *psize, SLK_NetS_AddMapUnit *pValue );
int struct_NetS_DelMapUnit_send( char **pptr, int *psize, SLK_NetS_DelMapUnit *pValue );
int struct_NetS_WorldMapInfo_send( char **pptr, int *psize, SLK_NetS_WorldMapInfo *pValue );
int struct_NetS_MapUnitCorrdinate_send( char **pptr, int *psize, SLK_NetS_MapUnitCorrdinate *pValue );
int struct_NetS_AddMarchRoute_send( char **pptr, int *psize, SLK_NetS_AddMarchRoute *pValue );
int struct_NetS_DelMarchRoute_send( char **pptr, int *psize, SLK_NetS_DelMarchRoute *pValue );
int struct_NetS_UpdateMapUnit_send( char **pptr, int *psize, SLK_NetS_UpdateMapUnit *pValue );
int struct_NetS_Equip_send( char **pptr, int *psize, SLK_NetS_Equip *pValue );
int struct_NetS_EquipList_send( char **pptr, int *psize, SLK_NetS_EquipList *pValue );
int struct_NetS_EquipGet_send( char **pptr, int *psize, SLK_NetS_EquipGet *pValue );
int struct_NetS_EquipLost_send( char **pptr, int *psize, SLK_NetS_EquipLost *pValue );
int struct_NetS_AwardInfo_send( char **pptr, int *psize, SLK_NetS_AwardInfo *pValue );
int struct_NetS_AwardInfoList_send( char **pptr, int *psize, SLK_NetS_AwardInfoList *pValue );
int struct_NetS_Experience_send( char **pptr, int *psize, SLK_NetS_Experience *pValue );
int struct_NetS_Body_send( char **pptr, int *psize, SLK_NetS_Body *pValue );
int struct_NetS_Levy_send( char **pptr, int *psize, SLK_NetS_Levy *pValue );
int struct_NetS_Silver_send( char **pptr, int *psize, SLK_NetS_Silver *pValue );
int struct_NetS_Wood_send( char **pptr, int *psize, SLK_NetS_Wood *pValue );
int struct_NetS_Food_send( char **pptr, int *psize, SLK_NetS_Food *pValue );
int struct_NetS_Iron_send( char **pptr, int *psize, SLK_NetS_Iron *pValue );
int struct_NetS_People_send( char **pptr, int *psize, SLK_NetS_People *pValue );
int struct_NetS_Prestige_send( char **pptr, int *psize, SLK_NetS_Prestige *pValue );
int struct_NetS_Friendship_send( char **pptr, int *psize, SLK_NetS_Friendship *pValue );
int struct_NetS_Vip_send( char **pptr, int *psize, SLK_NetS_Vip *pValue );
int struct_NetS_Token_send( char **pptr, int *psize, SLK_NetS_Token *pValue );

#endif

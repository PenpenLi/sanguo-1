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
	char m_nation_award;	//����˷���-�ĸ������н���
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

struct _slk_NetS_OfficialHire {
	short m_ofkind;	//��Ӷ��
	int m_ofsec;	//��Ӷ��
	int m_offree;	//��Ӷ��
	int m_ofquick;	//��Ӷ��
};
typedef struct _slk_NetS_OfficialHire SLK_NetS_OfficialHire;	//��Ӷ��

struct _slk_NetS_Building {
	char m_kind;	//��ͨ����-����
	char m_offset;	//��ͨ����-λ��
	char m_level;	//��ͨ����-�ȼ�
	int m_sec;	//��ͨ����-����ʣ��ʱ��
	int m_needsec;	//��ͨ����-������Ҫʱ��
	char m_quick;	//��ͨ����-�Ƿ��м���(�Ƽ���)
	int m_overvalue;	//��ͨ����-��ɺ��ֵ
	int m_value;	//��ͨ����-δ���ֵ
};
typedef struct _slk_NetS_Building SLK_NetS_Building;	//��ͨ������Ϣ

struct _slk_NetS_BuildingBarracks {
	char m_kind;	//��Ӫ����-����
	char m_offset;	//��Ӫ����-λ��
	char m_level;	//��Ӫ����-�ȼ�
	int m_sec;	//��Ӫ����-ļ��ʣ��ʱ��
	int m_needsec;	//��Ӫ����-ļ����Ҫʱ��
	char m_quick;	//��Ӫ����-�Ƿ��м���
	int m_overvalue;	//��Ӫ����-��ɺ������
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
	int m_worker_needsec;	//����������-����������Ҫʱ��
	char m_worker_free;	//����������-�����������ʱ��
	char m_worker_kind_ex;	//����������-������������(����)
	char m_worker_offset_ex;	//����������-������������(����)
	char m_worker_op_ex;	//����������-�������в���(����)
	int m_worker_sec_ex;	//����������-��������ʣ��ʱ��(����)
	int m_worker_needsec_ex;	//����������-����������Ҫʱ��(����)
	char m_worker_free_ex;	//����������-�����������ʱ��(����)
	int m_worker_expire_ex;	//����������-���ý�����е���ʱ��
	int m_function;	//����������-�����Ƿ���
	short m_forgingkind;	//����������-������
	int m_forgingsec;	//����������-������
	int m_forgingsec_need;	//����������-������
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
	int m_silver;	//������������һ�����Ϣ-����
	int m_wood;	//������������һ�����Ϣ-ľ��
	int m_food;	//������������һ�����Ϣ-��ʳ
	int m_iron;	//������������һ�����Ϣ-����
	int m_infantry_num;	//������������һ�����Ϣ-������
	int m_cavalry_num;	//������������һ�����Ϣ-�����
	int m_archer_num;	//������������һ�����Ϣ-������
	short m_mokilllv;	//������������һ�����Ϣ-��ɱҰ����߼���
	int m_sflag;	//������������һ�����Ϣ-��־λ
	char m_autobuild;	//������������һ�����Ϣ-�Զ�����
	char m_autobuildopen;	//������������һ�����Ϣ-�Զ�����
	short m_techlevel[40];	//������������һ�����Ϣ-�Ƽ��ȼ�
	short m_techprogress[40];	//������������һ�����Ϣ-�Ƽ�����
	SLK_NetS_OfficialHire m_officialhire[3];	//������������һ�����Ϣ-��Ӷ��
	int m_ptsec;	//������������һ�����Ϣ-����ʱ��
	short m_forgingkind;	//������������һ�����Ϣ-����
	int m_forgingsec;	//������������һ�����Ϣ-����
	int m_actor_sflag;	//������������һ�����Ϣ-��ҽṹ��־
	short m_bodysec;	//������������һ�����Ϣ-�����ָ�ʱ��
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

struct _slk_NetS_HeroEquip {
	short m_herokind;	//Ӣ��װ��
	short m_count;	//Ӣ��װ��
	SLK_NetS_Equip m_list[6];	//Ӣ��װ��
};
typedef struct _slk_NetS_HeroEquip SLK_NetS_HeroEquip;	//Ӣ��װ��

struct _slk_NetS_Hero {
	short m_kind;	//
	char m_color;	//
	short m_level;	//
	char m_corps;	//
	int m_exp;	//
	int m_exp_max;	//
	int m_soldiers;	//
	char m_state;	//
	short m_attack_base;	//
	short m_attack_wash;	//
	short m_defense_base;	//
	short m_defense_wash;	//
	short m_troops_base;	//
	short m_troops_wash;	//
	int m_attack;	//
	int m_defense;	//
	int m_troops;	//
	int m_attack_increase;	//
	int m_defense_increase;	//
	short m_offset;	//
};
typedef struct _slk_NetS_Hero SLK_NetS_Hero;	//Ӣ����Ϣ

struct _slk_NetS_HeroList {
	short m_count;	//Ӣ�۷�������
	SLK_NetS_Hero m_list[32];	//Ӣ���б�
	char m_type;	//0����Ӣ��1����Ӣ��
};
typedef struct _slk_NetS_HeroList SLK_NetS_HeroList;	//Ӣ���б�

struct _slk_NetS_HeroExp {
	short m_kind;	//Ӣ������
	int m_exp;	//Ӣ�۵�ǰ����
	int m_exp_max;	//Ӣ�۾�������
	short m_add;	//Ӣ�ۻ�ȡ����
	char m_isup;	//�Ƿ�����
	short m_level;	//Ӣ�۵ȼ�
	short m_path;	//;��
};
typedef struct _slk_NetS_HeroExp SLK_NetS_HeroExp;	//Ӣ�۾���ı�

struct _slk_NetS_HeroSoldiers {
	short m_kind;	//Ӣ������
	int m_add;	//��ӱ�����
	int m_soldiers;	//��ǰ����
	int m_soldiers_max;	//��������
	short m_path;	//;��
};
typedef struct _slk_NetS_HeroSoldiers SLK_NetS_HeroSoldiers;	//Ӣ�۱���

struct _slk_NetS_HeroState {
	short m_kind;	//Ӣ������
	char m_state;	//Ӣ��״̬
};
typedef struct _slk_NetS_HeroState SLK_NetS_HeroState;	//Ӣ��״̬

struct _slk_NetS_HeroReplace {
	short m_up_kind;	//�����佫
	short m_down_kind;	//�����佫
};
typedef struct _slk_NetS_HeroReplace SLK_NetS_HeroReplace;	//Ӣ���������滻

struct _slk_NetS_HeroGet {
	short m_kind;	//��ȡ���佫
	short m_path;	//;��
	SLK_NetS_Hero m_hero;	//��ȡ��Ӣ����Ϣ
};
typedef struct _slk_NetS_HeroGet SLK_NetS_HeroGet;	//Ӣ�ۻ�ȡ

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
	short m_bodysec;	//�����ظ�ʱ��
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

struct _slk_NetS_BuildingUpgradeInfo {
	short m_citylevel;	//������������ٸ��ȼ�
	short m_actorlevel;	//���������������ǵȼ�
	int m_silver;	//����������������
	int m_wood;	//����ľ�Ľ�������
	int m_food;	//������������ʳ��
	int m_iron;	//����������������
	int m_sec;	//������������ʱ��
	char m_maxlevel;	//�������ȼ�
};
typedef struct _slk_NetS_BuildingUpgradeInfo SLK_NetS_BuildingUpgradeInfo;	//����������Ϣ

struct _slk_NetS_Worker {
	char m_worker_kind;	//����������-������������
	char m_worker_offset;	//���������ͽ�����������
	char m_worker_op;	//����������-�������н�������
	int m_worker_sec;	//����������-��������ʣ��ʱ��
	int m_worker_needsec;	//����������-����������Ҫʱ��
	char m_worker_free;	//����������-�����������ʱ��
	char m_worker_kind_ex;	//����������-������������(����)
	char m_worker_offset_ex;	//����������-������������(����)
	char m_worker_op_ex;	//����������-�������в���(����)
	int m_worker_sec_ex;	//����������-��������ʣ��ʱ��(����)
	int m_worker_needsec_ex;	//����������-����������Ҫʱ��(����)
	char m_worker_free_ex;	//����������-�����������ʱ��(����)
	int m_worker_expire_ex;	//����������-���ý�����е���ʱ��
};
typedef struct _slk_NetS_Worker SLK_NetS_Worker;	//����������Ϣ

struct _slk_NetS_BuildingGet {
	short m_path;	//��ȡ����
	SLK_NetS_Building m_building;	//��ȡ����
};
typedef struct _slk_NetS_BuildingGet SLK_NetS_BuildingGet;	//��ͨ������ȡ

struct _slk_NetS_BuildingBarracksGet {
	short m_path;	//��ȡ����
	SLK_NetS_BuildingBarracks m_barracks;	//��ȡ����
};
typedef struct _slk_NetS_BuildingBarracksGet SLK_NetS_BuildingBarracksGet;	//��Ӫ������ȡ

struct _slk_NetS_BuildingResGet {
	short m_path;	//��ȡ����
	SLK_NetS_BuildingRes m_res;	//��ȡ����
};
typedef struct _slk_NetS_BuildingResGet SLK_NetS_BuildingResGet;	//��Դ������ȡ

struct _slk_NetS_Soldiers {
	char m_corps;	//���ڱ����ı�
	int m_soldiers;	//���ڱ����ı�
	int m_add;	//���ڱ����ı�
	short m_path;	//���ڱ����ı�
};
typedef struct _slk_NetS_Soldiers SLK_NetS_Soldiers;	//�����仯

struct _slk_NetS_TrainInfo {
	int m_soldiers;	//��Ӫ����
	int m_soldiers_max;	//��Ӫ����
	int m_trainnum;	//��ǰѵ��ʿ����
	int m_trainsec;	//��ǰѵ��ʣ��ʱ��(��)
	int m_trainsec_need;	//��ǰѵ����Ҫʱ��(��)
	int m_queuenum[16];	//����
	char m_queue;	//����
	char m_trainlong;	//ļ����ʱ
	int m_train_confnum;	//ÿ�����ѵ��ʿ����
	int m_train_confsec;	//��ļ���ʱ��ʱ��
	int m_train_conffood;	//��������
};
typedef struct _slk_NetS_TrainInfo SLK_NetS_TrainInfo;	//ѵ��ʿ��

struct _slk_NetS_Quest {
	short m_questid;	//���
	char m_flag;	//��ɱ��
	char m_datatype;	//��������
	short m_datakind;	//��������
	char m_dataoffset;	//������
	int m_value;	//ֵ
	int m_needvalue;	//��Ҫֵ
	int m_awardkind[5];	//����
	int m_awardnum[5];	//����
	int m_nameid;	//����ID
};
typedef struct _slk_NetS_Quest SLK_NetS_Quest;	//����

struct _slk_NetS_QuestList {
	short m_count;	//�����б�
	SLK_NetS_Quest m_list[6];	//�����б�
};
typedef struct _slk_NetS_QuestList SLK_NetS_QuestList;	//�����б�

struct _slk_NetS_QuestAward {
	short m_questid;	//������
	char m_count;	//��������
	SLK_NetS_AwardInfo m_list[5];	//������
	char m_datatype;	//��������
	short m_datakind;	//��������
	char m_dataoffset;	//������
	int m_value;	//ֵ
	int m_needvalue;	//��Ҫֵ
	int m_nameid;	//����ID
	char m_type;	//����
};
typedef struct _slk_NetS_QuestAward SLK_NetS_QuestAward;	//������

struct _slk_NetS_Function {
	int m_function;	//�����Ĺ����б�
	char m_openoffset;	//�����Ĺ����б�
	short m_path;	//;��
};
typedef struct _slk_NetS_Function SLK_NetS_Function;	//�����Ĺ����б�

struct _slk_NetS_CityGuard {
	char m_corps;	//��������
	char m_color;	//������ɫ
	char m_shape;	//��������
	short m_level;	//�����ȼ�
	int m_soldiers;	//��������
	int m_troops;	//��������
	char m_offset;	//��������
};
typedef struct _slk_NetS_CityGuard SLK_NetS_CityGuard;	//����

struct _slk_NetS_CityGuardList {
	short m_count;	//��������
	SLK_NetS_CityGuard m_list[32];	//�����б�
	short m_guardsec;	//�����ٻ���ȴ
};
typedef struct _slk_NetS_CityGuardList SLK_NetS_CityGuardList;	//�����б�

struct _slk_NetS_CityGuardSec {
	short m_guardsec;	//������ȴ���
};
typedef struct _slk_NetS_CityGuardSec SLK_NetS_CityGuardSec;	//������ȴ����

struct _slk_NetS_BuildingSmithy {
	short m_forgingkind;	//����������-������
	int m_forgingsec;	//����������-������
	int m_forgingsec_need;	//����������-������
};
typedef struct _slk_NetS_BuildingSmithy SLK_NetS_BuildingSmithy;	//������

struct _slk_NetS_ChangeName {
	short m_name_length;	//�޸�����
	char m_name[32];	//�޸�����
};
typedef struct _slk_NetS_ChangeName SLK_NetS_ChangeName;	//����

struct _slk_NetS_BuildingAction {
	short m_kind;	//��������
	short m_offset;	//��������
	short m_action;	//ִ�ж���
};
typedef struct _slk_NetS_BuildingAction SLK_NetS_BuildingAction;	//��������

struct _slk_NetS_LevyInfo {
	int m_base[4];	//����
	int m_tech[4];	//�Ƽ��ӳ�
	int m_weather[4];	//�����ӳ�
	int m_activity[4];	//��ӳ�
	int m_offical[4];	//��ְ�ӳ�
	int m_sec;	//��ȴ����ʱ
};
typedef struct _slk_NetS_LevyInfo SLK_NetS_LevyInfo;	//������Ϣ

struct _slk_NetS_Chat {
	int m_actorid;	//������Ϣ-��ɫid
	char m_shape;	//������Ϣ-����
	short m_level;	//������Ϣ-�ȼ�
	char m_namelen;	//������Ϣ-����
	char m_name[32];	//������Ϣ-����
	char m_frame;	//������Ϣ-����
	char m_zone;	//������Ϣ-����
	char m_place;	//������Ϣ-ְλ
	short m_msglen;	//������Ϣ-��Ϣ
	char m_msg[128];	//������Ϣ-��Ϣ
	int m_optime;	//������Ϣ-ʱ��
	char m_channel;	//������Ϣ-Ƶ��
	char m_nation;	//������Ϣ-����
};
typedef struct _slk_NetS_Chat SLK_NetS_Chat;	//������Ϣ

struct _slk_NetS_ChatList {
	char m_count;	//�����б�
	SLK_NetS_Chat m_list[10];	//�����б�
	char m_channel;	//�����б�
};
typedef struct _slk_NetS_ChatList SLK_NetS_ChatList;	//������Ϣ�б�

struct _slk_NetS_SystalkidValue {
	char m_vlen;	//ϵͳ��Ϣƴ�Ӵ�����
	char m_v[64];	//ϵͳ��Ϣƴ�Ӵ�
};
typedef struct _slk_NetS_SystalkidValue SLK_NetS_SystalkidValue;	//���ֱ�ϵͳ��Ϣ

struct _slk_NetS_Systalkid {
	char m_count;	//ϵͳ��Ϣ
	SLK_NetS_SystalkidValue m_msglist[8];	//ϵͳ��Ϣ
	int m_textid;	//���ֱ�ID
	int m_optime;	//ʱ��
};
typedef struct _slk_NetS_Systalkid SLK_NetS_Systalkid;	//���ֱ�ϵͳ��Ϣ

struct _slk_NetS_Systalk {
	short m_msglen;	//ֱ�����ֵ�ϵͳ��Ϣ
	char m_msg[1024];	//ֱ�����ֵ�ϵͳ��Ϣ
	int m_optime;	//ʱ��
};
typedef struct _slk_NetS_Systalk SLK_NetS_Systalk;	//ֱ������ϵͳ��Ϣ

struct _slk_NetS_Battlepower {
	int m_total;	//�ı�ս��
	short m_path;	//�ı�ս��
};
typedef struct _slk_NetS_Battlepower SLK_NetS_Battlepower;	//�ı�ս��

struct _slk_NetS_TechChange {
	char m_kind;	//�Ƽ��仯
	char m_level;	//�Ƽ��仯
	char m_progress;	//�Ƽ��仯
};
typedef struct _slk_NetS_TechChange SLK_NetS_TechChange;	//�Ƽ��仯

struct _slk_NetS_CityEvent {
	char m_type;	//�����¼�
	short m_kind;	//�����¼�
	int m_value;	//�����¼�
	int m_optime;	//�����¼�
};
typedef struct _slk_NetS_CityEvent SLK_NetS_CityEvent;	//�ǳ��¼�

struct _slk_NetS_BattleEvent {
	char m_type;	//�����¼�
	char m_name[22];	//�����¼�
	char m_value;	//�����¼�
	int m_optime;	//�����¼�
	unsigned int m_mailid;	//�����¼�
};
typedef struct _slk_NetS_BattleEvent SLK_NetS_BattleEvent;	//�����¼�

struct _slk_NetS_EventList {
	short m_cevent_count;	//�¼��б�
	SLK_NetS_CityEvent m_cevent_list[4];	//�¼��б�
	short m_bevent_count;	//�¼��б�
	SLK_NetS_BattleEvent m_bevent_list[4];	//�¼��б�
};
typedef struct _slk_NetS_EventList SLK_NetS_EventList;	//�����¼��б�

struct _slk_NetS_OfficialHireChange {
	char m_type;	//��Ӷ����Ϣ�仯
	SLK_NetS_OfficialHire m_info;	//��Ӷ����Ϣ�仯
};
typedef struct _slk_NetS_OfficialHireChange SLK_NetS_OfficialHireChange;	//��Ա�仯

struct _slk_NetS_CityProtect {
	int m_total;	//�ı䱣��ʱ��
	int m_add;	//�ı䱣��ʱ��
	short m_path;	//�ı䱣��ʱ��
};
typedef struct _slk_NetS_CityProtect SLK_NetS_CityProtect;	//

int struct_NetS_Login_send( char **pptr, int *psize, SLK_NetS_Login *pValue );
int struct_ListInfo_send( char **pptr, int *psize, SLK_ListInfo *pValue );
int struct_NetS_List_send( char **pptr, int *psize, SLK_NetS_List *pValue );
int struct_NetS_Create_send( char **pptr, int *psize, SLK_NetS_Create *pValue );
int struct_NetS_EnterInfo_send( char **pptr, int *psize, SLK_NetS_EnterInfo *pValue );
int struct_NetS_Delete_send( char **pptr, int *psize, SLK_NetS_Delete *pValue );
int struct_NetS_Heart_send( char **pptr, int *psize, SLK_NetS_Heart *pValue );
int struct_NetS_Notify_send( char **pptr, int *psize, SLK_NetS_Notify *pValue );
int struct_NetS_OfficialHire_send( char **pptr, int *psize, SLK_NetS_OfficialHire *pValue );
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
int struct_NetS_HeroEquip_send( char **pptr, int *psize, SLK_NetS_HeroEquip *pValue );
int struct_NetS_Hero_send( char **pptr, int *psize, SLK_NetS_Hero *pValue );
int struct_NetS_HeroList_send( char **pptr, int *psize, SLK_NetS_HeroList *pValue );
int struct_NetS_HeroExp_send( char **pptr, int *psize, SLK_NetS_HeroExp *pValue );
int struct_NetS_HeroSoldiers_send( char **pptr, int *psize, SLK_NetS_HeroSoldiers *pValue );
int struct_NetS_HeroState_send( char **pptr, int *psize, SLK_NetS_HeroState *pValue );
int struct_NetS_HeroReplace_send( char **pptr, int *psize, SLK_NetS_HeroReplace *pValue );
int struct_NetS_HeroGet_send( char **pptr, int *psize, SLK_NetS_HeroGet *pValue );
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
int struct_NetS_BuildingUpgradeInfo_send( char **pptr, int *psize, SLK_NetS_BuildingUpgradeInfo *pValue );
int struct_NetS_Worker_send( char **pptr, int *psize, SLK_NetS_Worker *pValue );
int struct_NetS_BuildingGet_send( char **pptr, int *psize, SLK_NetS_BuildingGet *pValue );
int struct_NetS_BuildingBarracksGet_send( char **pptr, int *psize, SLK_NetS_BuildingBarracksGet *pValue );
int struct_NetS_BuildingResGet_send( char **pptr, int *psize, SLK_NetS_BuildingResGet *pValue );
int struct_NetS_Soldiers_send( char **pptr, int *psize, SLK_NetS_Soldiers *pValue );
int struct_NetS_TrainInfo_send( char **pptr, int *psize, SLK_NetS_TrainInfo *pValue );
int struct_NetS_Quest_send( char **pptr, int *psize, SLK_NetS_Quest *pValue );
int struct_NetS_QuestList_send( char **pptr, int *psize, SLK_NetS_QuestList *pValue );
int struct_NetS_QuestAward_send( char **pptr, int *psize, SLK_NetS_QuestAward *pValue );
int struct_NetS_Function_send( char **pptr, int *psize, SLK_NetS_Function *pValue );
int struct_NetS_CityGuard_send( char **pptr, int *psize, SLK_NetS_CityGuard *pValue );
int struct_NetS_CityGuardList_send( char **pptr, int *psize, SLK_NetS_CityGuardList *pValue );
int struct_NetS_CityGuardSec_send( char **pptr, int *psize, SLK_NetS_CityGuardSec *pValue );
int struct_NetS_BuildingSmithy_send( char **pptr, int *psize, SLK_NetS_BuildingSmithy *pValue );
int struct_NetS_ChangeName_send( char **pptr, int *psize, SLK_NetS_ChangeName *pValue );
int struct_NetS_BuildingAction_send( char **pptr, int *psize, SLK_NetS_BuildingAction *pValue );
int struct_NetS_LevyInfo_send( char **pptr, int *psize, SLK_NetS_LevyInfo *pValue );
int struct_NetS_Chat_send( char **pptr, int *psize, SLK_NetS_Chat *pValue );
int struct_NetS_ChatList_send( char **pptr, int *psize, SLK_NetS_ChatList *pValue );
int struct_NetS_SystalkidValue_send( char **pptr, int *psize, SLK_NetS_SystalkidValue *pValue );
int struct_NetS_Systalkid_send( char **pptr, int *psize, SLK_NetS_Systalkid *pValue );
int struct_NetS_Systalk_send( char **pptr, int *psize, SLK_NetS_Systalk *pValue );
int struct_NetS_Battlepower_send( char **pptr, int *psize, SLK_NetS_Battlepower *pValue );
int struct_NetS_TechChange_send( char **pptr, int *psize, SLK_NetS_TechChange *pValue );
int struct_NetS_CityEvent_send( char **pptr, int *psize, SLK_NetS_CityEvent *pValue );
int struct_NetS_BattleEvent_send( char **pptr, int *psize, SLK_NetS_BattleEvent *pValue );
int struct_NetS_EventList_send( char **pptr, int *psize, SLK_NetS_EventList *pValue );
int struct_NetS_OfficialHireChange_send( char **pptr, int *psize, SLK_NetS_OfficialHireChange *pValue );
int struct_NetS_CityProtect_send( char **pptr, int *psize, SLK_NetS_CityProtect *pValue );

#endif

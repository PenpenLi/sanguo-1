# SQL-Front 5.1  (Build 4.16)

/*!40101 SET @OLD_SQL_MODE=@@SQL_MODE */;
/*!40101 SET SQL_MODE='STRICT_TRANS_TABLES,NO_ENGINE_SUBSTITUTION' */;
/*!40111 SET @OLD_SQL_NOTES=@@SQL_NOTES */;
/*!40103 SET SQL_NOTES='ON' */;


# Host: 119.29.56.213    Database: sg_dev_autoconfig
# ------------------------------------------------------
# Server version 5.6.36-log

#
# Source for table net_struct
#

CREATE TABLE `net_struct` (
  `structid` int(11) NOT NULL AUTO_INCREMENT,
  `name` varbinary(32) NOT NULL DEFAULT '',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `struct_type` tinyint(3) NOT NULL DEFAULT '0' COMMENT '1server,2client,3logined',
  `sortindex` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`structid`)
) ENGINE=MyISAM AUTO_INCREMENT=91 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table net_struct
#

INSERT INTO `net_struct` VALUES (1,'NetC_Login','�ͻ��������¼',2,0);
INSERT INTO `net_struct` VALUES (2,'NetU_Logined','�û����������ص�½',3,0);
INSERT INTO `net_struct` VALUES (3,'NetS_Login','�������˷��͵�¼������ͻ���',1,0);
INSERT INTO `net_struct` VALUES (4,'ListInfo','������ɫ���б���Ϣ',1,0);
INSERT INTO `net_struct` VALUES (5,'NetS_List','�������˷��ͽ�ɫ�б�',1,0);
INSERT INTO `net_struct` VALUES (6,'NetC_Create','�ͻ������󴴽���ɫ',2,0);
INSERT INTO `net_struct` VALUES (7,'NetS_Create','���������ش�����ɫ���',1,0);
INSERT INTO `net_struct` VALUES (8,'NetS_EnterInfo','���������ؽ�����Ϸ�����Ϣ',1,0);
INSERT INTO `net_struct` VALUES (9,'NetS_Delete','����������ɾ����ɫ',1,0);
INSERT INTO `net_struct` VALUES (10,'NetC_Heart','����',2,0);
INSERT INTO `net_struct` VALUES (11,'NetS_Heart','����',1,0);
INSERT INTO `net_struct` VALUES (12,'NetC_Gmcmd','GMָ��',2,0);
INSERT INTO `net_struct` VALUES (13,'NetS_Notify','ͨ�ö���Ϣ',1,0);
INSERT INTO `net_struct` VALUES (14,'NetU_UserAwarded','�û����������ضһ�����',3,0);
INSERT INTO `net_struct` VALUES (15,'NetU_Gmlocalcmd','����GM��Ϣ',3,0);
INSERT INTO `net_struct` VALUES (16,'NetC_AskInfo','�ͻ��˷��Ͷ�����',2,0);
INSERT INTO `net_struct` VALUES (17,'NetC_EnterCity','�������ǳ�������Ϣ',2,0);
INSERT INTO `net_struct` VALUES (25,'NetS_Building','��ͨ������Ϣ',1,0);
INSERT INTO `net_struct` VALUES (26,'NetS_BuildingBarracks','��Ӫ������Ϣ',1,0);
INSERT INTO `net_struct` VALUES (27,'NetS_BuildingRes','��Դ������Ϣ',1,0);
INSERT INTO `net_struct` VALUES (28,'NetS_BuildingList','�����б�',1,0);
INSERT INTO `net_struct` VALUES (29,'NetS_ActorInfo','��ɫ������Ϣ',1,0);
INSERT INTO `net_struct` VALUES (30,'Corrdinate','����',1,0);
INSERT INTO `net_struct` VALUES (31,'NetS_ItemUse','����ʹ��|װ��',1,0);
INSERT INTO `net_struct` VALUES (32,'NetS_ItemPut','���߷���|ж��',1,0);
INSERT INTO `net_struct` VALUES (33,'NetS_ItemSettle','��������',1,0);
INSERT INTO `net_struct` VALUES (34,'NetS_LostItem','��ʧ����',1,0);
INSERT INTO `net_struct` VALUES (35,'NetS_GetItem','��õ���',1,0);
INSERT INTO `net_struct` VALUES (36,'ItemSmpInfo','���߼�����Ϣ',1,0);
INSERT INTO `net_struct` VALUES (37,'NetS_ItemList','�����б�',1,0);
INSERT INTO `net_struct` VALUES (38,'ItemAttr','��������',1,0);
INSERT INTO `net_struct` VALUES (39,'NetS_ItemInfo','������Ϣ',1,0);
INSERT INTO `net_struct` VALUES (40,'WalkPath','�ƶ�·��',1,0);
INSERT INTO `net_struct` VALUES (44,'NetS_AddMapUnit','��ʾ��Ԫ�����ͼ',1,0);
INSERT INTO `net_struct` VALUES (45,'NetS_DelMapUnit','��ʾ��Ԫ�뿪��ͼ',1,0);
INSERT INTO `net_struct` VALUES (46,'NetS_WorldMapInfo','�����ͼ��Ϣ',1,0);
INSERT INTO `net_struct` VALUES (47,'NetS_MapUnitCorrdinate','��ͼ��ʾ��Ԫλ��',1,0);
INSERT INTO `net_struct` VALUES (48,'NetS_AddMarchRoute','�о�·��',1,0);
INSERT INTO `net_struct` VALUES (49,'NetS_DelMarchRoute','ɾ���о�·��',1,0);
INSERT INTO `net_struct` VALUES (50,'NetS_UpdateMapUnit','���µ�ͼ��ʾ��Ԫ��Ϣ',1,0);
INSERT INTO `net_struct` VALUES (77,'NetS_AwardInfo','������Ϣ',1,0);
INSERT INTO `net_struct` VALUES (78,'NetS_AwardInfoList','������Ϣ�б�',1,0);
INSERT INTO `net_struct` VALUES (79,'NetS_Experience','�ı侭��',1,0);
INSERT INTO `net_struct` VALUES (80,'NetS_Body','�ı�����',1,0);
INSERT INTO `net_struct` VALUES (81,'NetS_Levy','�ı����մ���',1,0);
INSERT INTO `net_struct` VALUES (82,'NetS_Silver','�ı�����',1,0);
INSERT INTO `net_struct` VALUES (83,'NetS_Wood','�ı�ľ��',1,0);
INSERT INTO `net_struct` VALUES (84,'NetS_Food','�ı���ʳ',1,0);
INSERT INTO `net_struct` VALUES (85,'NetS_Iron','�ı�����',1,0);
INSERT INTO `net_struct` VALUES (86,'NetS_People','�ı��˿�',1,0);
INSERT INTO `net_struct` VALUES (87,'NetS_Prestige','�ı�����ֵ',1,0);
INSERT INTO `net_struct` VALUES (88,'NetS_Friendship','�ı��������',1,0);
INSERT INTO `net_struct` VALUES (89,'NetS_Vip','�ı�VIP����',1,0);
INSERT INTO `net_struct` VALUES (90,'NetS_Token','�ı���ʯ',1,0);

#
# Source for table net_struct_conf
#

CREATE TABLE `net_struct_conf` (
  `dataid` int(11) NOT NULL AUTO_INCREMENT,
  `structid` int(11) DEFAULT NULL,
  `offset` smallint(6) NOT NULL DEFAULT '0',
  `name` varbinary(32) NOT NULL DEFAULT '',
  `data_type` smallint(6) NOT NULL DEFAULT '0',
  `data_count` smallint(6) NOT NULL DEFAULT '0',
  `data_size` smallint(6) NOT NULL DEFAULT '0',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `notsave` tinyint(4) NOT NULL DEFAULT '0',
  `kind` tinyint(4) NOT NULL DEFAULT '0',
  `m_fix` tinyint(3) NOT NULL DEFAULT '1',
  PRIMARY KEY (`dataid`)
) ENGINE=MyISAM AUTO_INCREMENT=90003 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table net_struct_conf
#

INSERT INTO `net_struct_conf` VALUES (1000,1,0,'username_length',-2,0,0,'�ͻ�������-�û�������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (1001,1,1,'username',-1,-1,51,'�ͻ�������-�û���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (1002,1,2,'password_length',-2,0,0,'�ͻ�������-���볤��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (1003,1,3,'password',-1,-1,256,'�ͻ�������-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (1004,1,4,'deviceid_length',-2,0,0,'�ͻ�������-�豸��ʾ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (1005,1,5,'deviceid',-1,-1,65,'�ͻ�������-�豸��ʾ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (1006,1,6,'isnew',-2,0,0,'�ͻ�������-�Ƿ����û�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (1007,1,7,'ipcountry_length',-2,0,0,'�ͻ�������-IP��ַ���ڹ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (1008,1,8,'ipcountry',-1,-1,16,'�ͻ�������-IP��ַ���ڹ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2000,2,0,'result',-3,0,0,'�û�����������-��¼����ֵ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2001,2,1,'client_index',-3,0,0,'�û�����������-��ɫ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2002,2,2,'authid',-3,0,0,'�û�����������-��֤ID',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2003,2,3,'userid',-1,21,0,'�û�����������-�û�ID',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2004,2,4,'username',-1,51,0,'�û�����������-�û���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2005,2,5,'usertype',-2,0,0,'�û�����������-�û�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2006,2,6,'checkflag',-1,0,0,'�û�����������-�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2007,2,7,'isdeep',-1,0,0,'�û�����������-Ҫ������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2008,2,8,'access_token',-1,65,0,'�û�����������-360���û�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2009,2,9,'expires_in',-3,0,0,'�û�����������-360��������Ч��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2010,2,10,'refresh_token',-1,65,0,'�û�����������-360��ˢ������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (2011,2,11,'deviceid',-1,65,0,'�û�����������-���ص��豸ID',0,0,1);
INSERT INTO `net_struct_conf` VALUES (3000,3,0,'result',-3,0,0,'����������-����ֵ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (3001,3,1,'username_length',-2,0,0,'����������-�û�������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (3002,3,2,'username',-1,-1,51,'����������-�û���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (3003,3,3,'token_length',-2,0,0,'����������-token����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (3004,3,4,'token',-1,-1,256,'����������-token',0,0,1);
INSERT INTO `net_struct_conf` VALUES (3005,3,5,'usertype',-2,0,0,'����������-�û�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (4000,4,0,'actorid',-3,0,0,'��ɫID',0,0,1);
INSERT INTO `net_struct_conf` VALUES (4001,4,1,'name',-1,22,0,'��ɫ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (4002,4,2,'nation',-1,0,0,'��ɫ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (4003,4,3,'level',-2,0,0,'��ɫ�ȼ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (4004,4,4,'offset',-1,0,0,'��ɫλ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (4005,4,5,'lockstat',-1,0,0,'����״̬',0,0,1);
INSERT INTO `net_struct_conf` VALUES (4006,4,6,'delete_stoptime',-3,0,0,'ɾ��ʱ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (4007,4,7,'lock_endtime',-3,0,0,'����ʱ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (5000,5,0,'actor_num',-1,0,0,'����˷���-��ɫ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (5001,5,1,'listinfo',4,-1,8,'����˷���-��ɫ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (6000,6,0,'nation',-1,0,0,'�ͻ�������-�����Ľ�ɫ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (6001,6,1,'name_length',-2,0,0,'�ͻ�������-�����Ľ�ɫ���Ƴ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (6002,6,2,'name',-1,-1,22,'�ͻ�������-�����Ľ�ɫ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (7000,7,0,'result',-1,0,0,'����˷���-������ɫ�Ľ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (7001,7,1,'actorid',-3,0,0,'����˷���-������ɫ�ı��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (7002,7,2,'createtime',-3,0,0,'����˷���-������ɫ��ʱ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (8000,8,0,'actorid',-3,0,0,'����˷���-������Ϸ��ɫID',0,0,1);
INSERT INTO `net_struct_conf` VALUES (8001,8,1,'data_int',-3,0,0,'����˷���-������Ϸ��������[����]',0,0,1);
INSERT INTO `net_struct_conf` VALUES (8002,8,2,'data_short',-2,0,0,'����˷���-������Ϸ��������[����]',0,0,1);
INSERT INTO `net_struct_conf` VALUES (8003,8,3,'data_char',-1,0,0,'����˷���-������Ϸ��������[����]',0,0,1);
INSERT INTO `net_struct_conf` VALUES (8004,8,4,'serverid',-2,0,0,'����˷���-����ķ�����ID',0,0,1);
INSERT INTO `net_struct_conf` VALUES (8005,8,5,'servertime',-3,0,0,'����˷���-����ķ�����ʱ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (8006,8,6,'createtime',-3,0,0,'����˷���-������ɫʱ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (9000,9,0,'result',-3,0,0,'����������-ɾ������ֵ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (9001,9,1,'actorid',-3,0,0,'����������-ɾ���Ľ�ɫ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (10000,10,0,'value',-3,2,0,'����-��ֵ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (11000,11,0,'value',-3,2,0,'����-��ֵ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (12000,12,0,'cmd',-2,0,0,'�ͻ��˷���-GMָ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (12001,12,1,'value',-3,4,0,'�ͻ��˷���-GMָ����ֵ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (12002,12,2,'msg_length',-2,0,0,'�ͻ��˷���-GMָ���ַ�������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (12003,12,3,'msg',-1,-1,256,'�ͻ��˷���-GMָ���ַ�������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (13000,13,0,'msgid',-2,0,0,'����������-����ϢID',0,0,1);
INSERT INTO `net_struct_conf` VALUES (13001,13,1,'valuenum',-2,0,0,'����������-����Ϣ��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (13002,13,2,'value',-3,-1,10,'����������-����Ϣ��ֵ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (13003,13,3,'msg_length',-2,0,0,'����������-����Ϣ�ַ�����Ϣ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (13004,13,4,'msg',-1,-1,256,'����������-����Ϣ�ַ�������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (14000,14,0,'result',-3,0,0,'�û�����������-�һ��������ֵ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (14001,14,1,'client_index',-3,0,0,'�û�����������-��ɫ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (14002,14,2,'authid',-3,0,0,'�û�����������-��֤ID',0,0,1);
INSERT INTO `net_struct_conf` VALUES (14003,14,3,'cdkey_index',-2,0,0,'�û�����������-�һ���浵����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (14004,14,4,'awardgroup',-3,0,0,'�û�����������-�һ��뽱����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (14005,14,5,'cardnumber',-1,32,0,'�û�����������-�һ��뿨��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (15000,15,0,'cmd',-2,0,0,'ָ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (15001,15,1,'value',-3,4,0,'��ֵ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (15002,15,2,'msglen',-2,0,0,'�ַ�������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (15003,15,3,'msg',-1,-1,1024,'�ַ�������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (16000,16,0,'msgid',-2,0,0,'�ͻ��˷���-������ID',0,0,1);
INSERT INTO `net_struct_conf` VALUES (16001,16,1,'valuenum',-2,0,0,'�ͻ��˷���-�������������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (16002,16,2,'value',-3,-1,10,'�ͻ��˷���-���������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (16003,16,3,'msg_length',-2,0,0,'�ͻ��˷���-�������ַ�������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (16004,16,4,'msg',-1,-1,256,'�ͻ��˷���-�������ַ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (17001,17,0,'value',-1,0,0,'�ͻ��˷���-���ѳ�ʼ���ã������������Ϣ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (25000,25,0,'kind',-1,0,0,'��ͨ����-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (25001,25,1,'offset',-1,0,0,'��ͨ����-λ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (25002,25,2,'level',-1,0,0,'��ͨ����-�ȼ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (25003,25,3,'sec',-3,0,0,'��ͨ����-����ʣ��ʱ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (25004,25,4,'quick',-1,0,0,'��ͨ����-�Ƿ��м���(�Ƽ���)',0,0,1);
INSERT INTO `net_struct_conf` VALUES (26000,26,0,'kind',-1,0,0,'��Ӫ����-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (26001,26,1,'offset',-1,0,0,'��Ӫ����-λ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (26002,26,2,'level',-1,0,0,'��Ӫ����-�ȼ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (26003,26,3,'sec',-3,0,0,'��Ӫ����-ļ��ʣ��ʱ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (26004,26,4,'quick',-1,0,0,'��Ӫ����-�Ƿ��м���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (27000,27,0,'kind',-1,0,0,'��Դ����-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (27001,27,1,'offset',-1,0,0,'��Դ����-����(��Ӧָ���ؿ�)',0,0,1);
INSERT INTO `net_struct_conf` VALUES (27002,27,2,'level',-1,0,0,'��Դ����-�ȼ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28000,28,0,'building_count',-2,0,0,'����������-��ͨ��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28001,28,1,'building',25,-1,8,'����������-��ͨ�����б�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28002,28,2,'barracks_count',-2,0,0,'����������-��Ӫ��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28003,28,3,'barracks',26,-1,8,'����������-��Ӫ�����б�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28004,28,4,'res_count',-2,0,0,'����������-��Դ��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28005,28,5,'res',27,-1,64,'����������-��Դ�����б�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28006,28,6,'levynum',-1,0,0,'����������-��ǰ�����մ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28007,28,7,'worker_kind',-1,0,0,'����������-������������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28008,28,8,'worker_offset',-1,0,0,'���������ͽ�����������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28009,28,9,'worker_op',-1,0,0,'����������-�������н�������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28010,28,10,'worker_sec',-3,0,0,'����������-��������ʣ��ʱ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28011,28,11,'worker_kind_ex',-1,0,0,'����������-������������(����)',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28012,28,12,'worker_offset_ex',-1,0,0,'����������-������������(����)',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28013,28,13,'worker_op_ex',-1,0,0,'����������-�������в���(����)',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28014,28,14,'worker_sec_ex',-3,0,0,'����������-��������ʣ��ʱ��(����)',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28015,28,15,'worker_expire_ex',-3,0,0,'����������-���ý�����е���ʱ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (28016,28,16,'function',-3,0,0,'����������-�����Ƿ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29000,29,0,'actorid',-3,0,0,'������������һ�����Ϣ-��ɫ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29001,29,1,'name',-1,22,0,'������������һ�����Ϣ-��ɫ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29002,29,2,'nation',-1,0,0,'������������һ�����Ϣ-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29003,29,3,'shape',-1,0,0,'������������һ�����Ϣ-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29004,29,4,'level',-2,0,0,'������������һ�����Ϣ-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29005,29,5,'exp',-4,0,0,'������������һ�����Ϣ-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29006,29,6,'exp_max',-4,0,0,'������������һ�����Ϣ-��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29008,29,8,'token',-3,0,0,'������������һ�����Ϣ-��ʯ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29009,29,9,'viplevel',-1,0,0,'������������һ�����Ϣ-VIP�ȼ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29010,29,10,'vipexp',-3,0,0,'������������һ�����Ϣ-VIP����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29011,29,11,'vipexp_max',-3,0,0,'������������һ�����Ϣ-VIP��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29012,29,12,'body',-2,0,0,'������������һ�����Ϣ-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29013,29,13,'place',-1,0,0,'������������һ�����Ϣ-��λ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29014,29,14,'official',-1,0,0,'������������һ�����Ϣ-��ְ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29015,29,15,'zone',-2,0,0,'������������һ�����Ϣ-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29016,29,16,'battlepower',-3,0,0,'������������һ�����Ϣ-ս��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29017,29,17,'silver',-2,0,0,'������������һ�����Ϣ-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29018,29,18,'wood',-2,0,0,'������������һ�����Ϣ-ľ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29019,29,19,'food',-2,0,0,'������������һ�����Ϣ-��ʳ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29020,29,20,'iron',-2,0,0,'������������һ�����Ϣ-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29022,29,22,'infantry_num',-3,0,0,'������������һ�����Ϣ-������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29023,29,23,'cavalry_num',-3,0,0,'������������һ�����Ϣ-�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29024,29,24,'archer_num',-3,0,0,'������������һ�����Ϣ-������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29025,29,25,'mokilllv',-2,0,0,'������������һ�����Ϣ-��ɱҰ����߼���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (29026,29,26,'sflag',-3,0,0,'������������һ�����Ϣ-��־λ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (30000,30,0,'posx',-2,0,0,'����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (30001,30,1,'posy',-2,0,0,'����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (31000,31,0,'itemoffset',-2,0,0,'��Ʒλ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (31001,31,1,'usenum',-2,0,0,'ʹ�ø�����װ��λ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (31002,31,2,'effres',-3,0,0,'Ӱ�죬һ��������Ч��ʾ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (32000,32,0,'res_offset',-2,0,0,'��ƷԴ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (32001,32,1,'res_num',-2,0,0,'��ƷԴ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (32002,32,2,'target_offset',-2,0,0,'��ƷĿ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (32003,32,3,'target_num',-2,0,0,'Ŀ�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (33000,33,0,'itemnum',-2,0,0,'�������ĸ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (33001,33,1,'itemoffset',-2,-1,100,'���õ���Ʒλ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (34000,34,0,'itemoffset',-2,0,0,'��Ʒλ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (34001,34,1,'itemnum',-2,0,0,'����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (34002,34,2,'targetid',-3,0,0,'����Ķ���id',0,0,1);
INSERT INTO `net_struct_conf` VALUES (34003,34,3,'path',-2,0,0,';��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (35000,35,0,'itemoffset',-2,0,0,'��Ʒλ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (35001,35,1,'kind',-2,0,0,'��Ʒ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (35002,35,2,'type',-2,0,0,'��Ʒ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (35003,35,3,'color',-1,0,0,'��ɫ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (35004,35,4,'num',-2,0,0,'����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (35005,35,5,'targetid',-3,0,0,'����Ķ���id',0,0,1);
INSERT INTO `net_struct_conf` VALUES (35006,35,6,'path',-2,0,0,';��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (35007,35,7,'situation',-11,0,0,'ʹ��״̬',0,0,1);
INSERT INTO `net_struct_conf` VALUES (36000,36,0,'offset',-2,0,0,'��Ʒλ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (36001,36,1,'kind',-2,0,0,'��Ʒ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (36002,36,2,'num',-2,0,0,'����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (36003,36,3,'situation',-11,0,0,'ʹ��״̬',0,0,1);
INSERT INTO `net_struct_conf` VALUES (36004,36,4,'color_level',-1,0,0,'��ɫ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (37000,37,0,'itemext',-1,0,0,'��չ�ĸ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (37001,37,1,'kindnum',-2,0,0,'��Ʒ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (37002,37,2,'item',36,-1,300,'��Ʒ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (38000,38,0,'type',-2,0,0,'��Ʒ������������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (38001,38,1,'ability',-2,0,0,'��Ʒ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (38002,38,2,'value',-3,0,0,'��Ʒ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (38003,38,3,'addvalue',-3,0,0,'��Ʒ��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (39000,39,0,'itemoffset',-2,0,0,'��Ʒλ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (39001,39,1,'itemkind',-2,0,0,'װ��kind,У��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (39002,39,2,'type',-2,0,0,'��Ʒ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (39003,39,3,'level',-2,0,0,'һ��ȼ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (39004,39,4,'color_level',-1,0,0,'��ɫ�ּ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (39005,39,5,'price',-3,0,0,'�ۼ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (39006,39,6,'attr_num',-2,0,0,'���Ը���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (39007,39,7,'attr',38,-1,10,'����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (40000,40,0,'pathx',-2,100,0,'·����ṹ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (40001,40,1,'pathy',-2,100,0,'·����ṹ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (40002,40,2,'len',-2,0,0,'·����ṹ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44000,44,4,'unit_index',-3,0,0,'��ͼ��Ԫ-���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44001,44,1,'type',-1,0,0,'��ͼ��Ԫ-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44002,44,2,'state',-1,0,0,'��ͼ��Ԫ-״̬',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44003,44,3,'posx',-2,0,0,'��ͼ��Ԫ-��ǰ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44004,44,4,'posy',-2,0,0,'��ͼ��Ԫ-��ǰ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44005,44,5,'namelen',-1,0,0,'��ͼ��Ԫ-���Ƴ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44006,44,6,'name',-1,-1,32,'��ͼ��Ԫ-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44007,44,7,'char_value_count',-1,0,0,'��ͼ��Ԫ-ͨ���ֶγ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44008,44,8,'char_value',-7,-1,16,'��ͼ��Ԫ-ͨ���ֶ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44009,44,9,'short_value_count',-1,0,0,'��ͼ��Ԫ-ͨ���ֶγ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44010,44,10,'short_value',-2,-1,8,'��ͼ��Ԫ-ͨ���ֶ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44011,44,11,'int_value_count',-1,0,0,'��ͼ��Ԫ-ͨ���ֶγ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44012,44,12,'int_value',-3,-1,8,'��ͼ��Ԫ-ͨ���ֶ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44013,44,13,'prefixlen',-1,0,0,'��ͼ��Ԫ-�ƺų���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (44014,44,14,'prefix',-1,-1,22,'��ͼ��Ԫ-�ƺ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (45000,45,0,'unit_index',-3,0,0,'��ͼ��Ԫ-���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46000,46,0,'map_width',-2,0,0,'�����ͼ��С����������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46001,46,1,'map_height',-2,0,0,'�����ͼ��С����������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46002,46,2,'area_width',-1,0,0,'�����С��һ�����򼸸���ͼ���ӣ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46003,46,3,'area_height',-1,0,0,'�����С��һ�����򼸸���ͼ���ӣ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46004,46,4,'map_area_xnum',-2,0,0,'һ����ͼ�ж�������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46005,46,5,'map_area_ynum',-2,0,0,'һ����ͼ�ж�������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46006,46,6,'my_city_posx',-2,0,0,'�ҵĳǳ�λ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46007,46,7,'my_city_posy',-2,0,0,'�ҵĳǳ�λ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46008,46,8,'my_city_unit_index',-3,0,0,'�ҵĳǳص�ͼ��Ԫ-���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46010,46,10,'citystate',-1,0,0,'�ҵĳǳ�״̬',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46011,46,11,'target_posx',-2,0,0,'Ŀ�ĵ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (46012,46,12,'target_posy',-2,0,0,'Ŀ�ĵ�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (47000,47,0,'unit_index',-3,0,0,'��ͼ��Ԫ-���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (47001,47,1,'posx',-2,0,0,'��ͼ��Ԫ-��ǰ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (47002,47,2,'posy',-2,0,0,'��ͼ��Ԫ-��ǰ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48000,48,0,'from_type',-1,0,0,'�о�·��-������Ԫ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48001,48,1,'from_posx',-2,0,0,'�о�·��-����λ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48002,48,2,'from_posy',-2,0,0,'�о�·��-����λ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48003,48,3,'to_type',-1,0,0,'�о�·��-���ﵥԪ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48004,48,4,'to_posx',-2,0,0,'�о�·��-����λ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48005,48,5,'to_posy',-2,0,0,'�о�·��-����λ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48006,48,6,'state',-1,0,0,'�о�·��-״̬',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48007,48,7,'from_actorid',-3,0,0,'�о�·��-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48008,48,8,'from_clubid',-3,0,0,'�о�·��-����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48009,48,9,'to_actorid',-3,0,0,'�о�·��-Ŀ�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48010,48,10,'to_clubid',-3,0,0,'�о�·��-Ŀ������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48011,48,11,'army_index',-3,0,0,'�о�·��-��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (48012,48,12,'action',-1,0,0,'�о�·��-��Ϊ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (49000,49,0,'army_index',-3,0,0,'ɾ����-��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (50000,50,0,'info',44,0,0,'���µ�ͼ��ʾ��Ԫ��Ϣ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (77000,77,0,'kind',-3,0,0,'����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (77001,77,1,'num',-3,0,0,'����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (78000,78,0,'count',-2,0,0,'��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (78001,78,1,'list',77,-1,32,'�����б�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (78002,78,2,'callback_code',-2,0,0,'�ĸ�ϵͳҪ��ʾ���ش�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (79000,79,0,'addexp',-3,0,0,'����������-��ȡ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (79001,79,1,'curexp',-4,0,0,'����������-��ȡ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (79002,79,2,'isup',-1,0,0,'����������-��ȡ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (79003,79,4,'path',-2,0,0,'����������-��ȡ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (79004,79,5,'level',-2,0,0,'����������-��ȡ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (79005,79,6,'expmax',-3,0,0,'����������-��ȡ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (80000,80,0,'total',-2,0,0,'����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (80001,80,1,'add',-2,0,0,'��ȡ����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (80002,80,2,'path',-2,0,0,';��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (81000,81,0,'total',-2,0,0,'�ı����մ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (81001,81,1,'add',-2,0,0,'�ı����մ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (81002,81,2,'max',-2,0,0,'�ı����մ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (81003,81,3,'sec',-3,0,0,'�ı����մ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (81004,81,4,'path',-2,0,0,'�ı����մ���',0,0,1);
INSERT INTO `net_struct_conf` VALUES (82000,82,0,'total',-3,0,0,'�ı�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (82001,82,1,'add',-3,0,0,'�ı�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (82002,82,2,'path',-2,0,0,'�ı�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (83000,83,0,'total',-3,0,0,'�ı�ľ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (83001,83,1,'add',-3,0,0,'�ı�ľ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (83002,83,2,'path',-2,0,0,'�ı�ľ��',0,0,1);
INSERT INTO `net_struct_conf` VALUES (84000,84,0,'total',-3,0,0,'�ı���ʳ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (84001,84,1,'add',-3,0,0,'�ı���ʳ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (84002,84,2,'path',-2,0,0,'�ı���ʳ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (85000,85,0,'total',-3,0,0,'�ı�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (85001,85,1,'add',-3,0,0,'�ı�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (85002,85,2,'path',-2,0,0,'�ı�����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (86000,86,0,'total',-3,0,0,'�ı��˿�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (86001,86,1,'add',-3,0,0,'�ı��˿�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (86002,86,2,'path',-2,0,0,'�ı��˿�',0,0,1);
INSERT INTO `net_struct_conf` VALUES (87000,87,0,'total',-3,0,0,'�ı�����ֵ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (87001,87,1,'add',-3,0,0,'�ı�����ֵ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (87002,87,2,'path',-2,0,0,'�ı�����ֵ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (88000,88,0,'total',-3,0,0,'�ı��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (88001,88,1,'add',-3,0,0,'�ı��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (88002,88,2,'path',-2,0,0,'�ı��������',0,0,1);
INSERT INTO `net_struct_conf` VALUES (89000,89,0,'addexp',-3,0,0,'�ı�VIP����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (89001,89,1,'curexp',-3,0,0,'�ı�VIP����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (89002,89,2,'expmax',-3,0,0,'�ı�VIP����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (89003,89,3,'isup',-1,0,0,'�ı�VIP����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (89004,89,4,'level',-1,0,0,'�ı�VIP����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (89005,89,5,'path',-2,0,0,'�ı�VIP����',0,0,1);
INSERT INTO `net_struct_conf` VALUES (90000,90,0,'total',-3,0,0,'�ı���ʯ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (90001,90,1,'add',-3,0,0,'�ı���ʯ',0,0,1);
INSERT INTO `net_struct_conf` VALUES (90002,90,2,'path',-2,0,0,'�ı���ʯ',0,0,1);

#
# Source for table netccmd
#

CREATE TABLE `netccmd` (
  `cmdid` int(11) NOT NULL AUTO_INCREMENT,
  `cmdstr` varbinary(32) NOT NULL DEFAULT '',
  `structid` int(11) NOT NULL DEFAULT '0',
  `target_type` tinyint(3) NOT NULL DEFAULT '0' COMMENT '1queue',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `unuse` tinyint(3) NOT NULL DEFAULT '0',
  PRIMARY KEY (`cmdid`)
) ENGINE=MyISAM AUTO_INCREMENT=11 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table netccmd
#

INSERT INTO `netccmd` VALUES (-4,'userawarded',14,0,'�û��������������Ľ���',0);
INSERT INTO `netccmd` VALUES (-3,'gmlocalcmd',15,0,'GM����ָ��',0);
INSERT INTO `netccmd` VALUES (-2,'logined',2,0,'�û����������͵�½��Ϣ',0);
INSERT INTO `netccmd` VALUES (-1,'timer',-1,0,'����������ʱ����Ϣ',0);
INSERT INTO `netccmd` VALUES (1,'login',1,0,'�����¼',0);
INSERT INTO `netccmd` VALUES (2,'create',6,1,'���󴴽���ɫ',0);
INSERT INTO `netccmd` VALUES (3,'list',-1,1,'�����ɫ�б�',0);
INSERT INTO `netccmd` VALUES (4,'entergame',-3,1,'������Ϸ',0);
INSERT INTO `netccmd` VALUES (5,'delete',-3,0,'ɾ����ɫ',0);
INSERT INTO `netccmd` VALUES (6,'heart',10,0,'����',0);
INSERT INTO `netccmd` VALUES (7,'gmcmd',12,0,'GMָ��',0);
INSERT INTO `netccmd` VALUES (9,'askinfo',16,0,'��������Ϣ',0);
INSERT INTO `netccmd` VALUES (10,'entercity',17,0,'����ǳ�������Ϣ',0);

#
# Source for table netgcmd
#

CREATE TABLE `netgcmd` (
  `cmdid` int(11) NOT NULL AUTO_INCREMENT,
  `cmdstr` varbinary(32) NOT NULL DEFAULT '',
  `structid` int(11) NOT NULL DEFAULT '0',
  `target_type` tinyint(3) NOT NULL DEFAULT '0' COMMENT '���Ϊ1��ʾ�Զ��еķ�ʽ��ͨ��Ϊ������ɫ�����ݲ���',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `unuse` tinyint(3) NOT NULL DEFAULT '0',
  PRIMARY KEY (`cmdid`)
) ENGINE=MyISAM DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table netgcmd
#


#
# Source for table netscmd
#

CREATE TABLE `netscmd` (
  `cmdid` int(11) NOT NULL AUTO_INCREMENT,
  `cmdstr` varbinary(32) NOT NULL DEFAULT '',
  `structid` int(11) NOT NULL DEFAULT '0',
  `target_type` tinyint(4) NOT NULL DEFAULT '0',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `nolua` tinyint(3) NOT NULL DEFAULT '0',
  `unuse` tinyint(3) NOT NULL DEFAULT '0',
  PRIMARY KEY (`cmdid`)
) ENGINE=MyISAM AUTO_INCREMENT=38 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table netscmd
#

INSERT INTO `netscmd` VALUES (1,'login',3,0,'��¼��Ϣ',0,0);
INSERT INTO `netscmd` VALUES (2,'list',5,0,'��ɫ�б�',0,0);
INSERT INTO `netscmd` VALUES (3,'create',7,0,'���ش�����ɫ��Ϣ',0,0);
INSERT INTO `netscmd` VALUES (4,'enterinfo',8,0,'������Ϸ����Ϣ',0,0);
INSERT INTO `netscmd` VALUES (5,'delete',9,0,'ɾ����ɫ',0,0);
INSERT INTO `netscmd` VALUES (6,'heart',11,0,'����',0,0);
INSERT INTO `netscmd` VALUES (7,'notify',13,0,'����Ϣ',0,0);
INSERT INTO `netscmd` VALUES (8,'actorinfo',29,0,'��ɫ������Ϣ',0,0);
INSERT INTO `netscmd` VALUES (9,'itemuse',31,0,'����ʹ��',0,0);
INSERT INTO `netscmd` VALUES (10,'itemput',32,0,'���߷���|ж��',0,0);
INSERT INTO `netscmd` VALUES (11,'itemsettle',33,0,'��������',0,0);
INSERT INTO `netscmd` VALUES (12,'lostitem',34,0,'��ʧ����',0,0);
INSERT INTO `netscmd` VALUES (13,'getitem',35,0,'��õ���',0,0);
INSERT INTO `netscmd` VALUES (14,'itemlist',37,0,'��Ʒ�б�',0,0);
INSERT INTO `netscmd` VALUES (15,'iteminfo',39,0,'������Ϣ',0,0);
INSERT INTO `netscmd` VALUES (16,'addmapunit',44,10,'��ʾ��Ԫ�����ͼ',0,0);
INSERT INTO `netscmd` VALUES (17,'delmapunit',45,10,'��ʾ��Ԫ�뿪��ͼ',0,0);
INSERT INTO `netscmd` VALUES (18,'updatemapunit',50,10,'���µ�ͼ��ʾ��Ԫ��Ϣ',0,0);
INSERT INTO `netscmd` VALUES (19,'mapunitsingle',44,0,'��ͼ��Ԫ ����һ����Ϣ',0,0);
INSERT INTO `netscmd` VALUES (20,'worldmapinfo',46,0,'�����ͼ��Ϣ',0,0);
INSERT INTO `netscmd` VALUES (21,'mapunitcorrdinate',47,10,'��ͼ��ʾ��Ԫλ��',0,0);
INSERT INTO `netscmd` VALUES (22,'addmarchroute',48,10,'����о�·��',0,0);
INSERT INTO `netscmd` VALUES (23,'delmarchroute',49,10,'ɾ���о�·��',0,0);
INSERT INTO `netscmd` VALUES (24,'awardinfolist',78,0,'������Ϣ�б�',0,0);
INSERT INTO `netscmd` VALUES (25,'experience',79,0,'��þ���',0,0);
INSERT INTO `netscmd` VALUES (26,'body',80,0,'����',0,0);
INSERT INTO `netscmd` VALUES (27,'buildinglist',28,0,'�����б�',0,0);
INSERT INTO `netscmd` VALUES (28,'changelevy',81,0,'���մ���',0,0);
INSERT INTO `netscmd` VALUES (29,'changesilver',82,0,'����',0,0);
INSERT INTO `netscmd` VALUES (30,'changewood',83,0,'ľ��',0,0);
INSERT INTO `netscmd` VALUES (31,'changefood',84,0,'��ʳ',0,0);
INSERT INTO `netscmd` VALUES (32,'changeiron',85,0,'����',0,0);
INSERT INTO `netscmd` VALUES (33,'changepeople',86,0,'�˿�',0,0);
INSERT INTO `netscmd` VALUES (34,'changeprestige',87,0,'����',0,0);
INSERT INTO `netscmd` VALUES (35,'changefriendship',88,0,'�������',0,0);
INSERT INTO `netscmd` VALUES (36,'changevip',89,0,'VIP',0,0);
INSERT INTO `netscmd` VALUES (37,'changtoken',90,0,'�ı���ʯ',0,0);

#
# Source for table scsrv_c_struct
#

CREATE TABLE `scsrv_c_struct` (
  `structid` int(11) NOT NULL AUTO_INCREMENT,
  `name` varbinary(64) NOT NULL DEFAULT '',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `limitcount` smallint(6) NOT NULL DEFAULT '0',
  `t1` tinyint(3) NOT NULL DEFAULT '0',
  `arg1` varbinary(32) NOT NULL DEFAULT '',
  `t2` tinyint(3) NOT NULL DEFAULT '0',
  `arg2` varbinary(32) NOT NULL DEFAULT '',
  `t3` tinyint(3) NOT NULL DEFAULT '0',
  `arg3` varbinary(32) NOT NULL DEFAULT '',
  `t4` tinyint(3) NOT NULL DEFAULT '0',
  `arg4` varbinary(32) NOT NULL DEFAULT '',
  `t5` tinyint(3) NOT NULL DEFAULT '0',
  `arg5` varbinary(32) NOT NULL DEFAULT '',
  `t6` tinyint(3) NOT NULL DEFAULT '0',
  `arg6` varbinary(32) NOT NULL DEFAULT '',
  `t7` tinyint(3) NOT NULL DEFAULT '0',
  `arg7` varbinary(32) NOT NULL DEFAULT '',
  `t8` tinyint(3) NOT NULL DEFAULT '0',
  `arg8` varbinary(32) NOT NULL DEFAULT '',
  `t9` tinyint(3) NOT NULL DEFAULT '0',
  `arg9` varbinary(32) NOT NULL DEFAULT '',
  `t10` tinyint(3) NOT NULL DEFAULT '0',
  `arg10` varbinary(32) NOT NULL DEFAULT '',
  `t11` tinyint(3) NOT NULL DEFAULT '0',
  `arg11` varbinary(32) NOT NULL DEFAULT '',
  `t12` tinyint(3) NOT NULL DEFAULT '0',
  `arg12` varbinary(32) NOT NULL DEFAULT '',
  `t13` tinyint(3) NOT NULL DEFAULT '0',
  `arg13` varbinary(32) NOT NULL DEFAULT '',
  `t14` tinyint(3) NOT NULL DEFAULT '0',
  `arg14` varbinary(32) NOT NULL DEFAULT '',
  `t15` tinyint(3) NOT NULL DEFAULT '0',
  `arg15` varbinary(32) NOT NULL DEFAULT '',
  `t16` tinyint(3) NOT NULL DEFAULT '0',
  `arg16` varbinary(32) NOT NULL DEFAULT '',
  PRIMARY KEY (`structid`)
) ENGINE=MyISAM AUTO_INCREMENT=211 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table scsrv_c_struct
#

INSERT INTO `scsrv_c_struct` VALUES (1,'c_item_name','��ȡ��Ʒ����',0,-3,'itemkind',9,'itemname',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (2,'c_item_hasone','�ж��Ƿ�ӵ��ĳ����',0,-3,'actor_index',-3,'itemkind',1,'rtn',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (3,'c_item_emptycount','��ÿ��౳������',0,-3,'actor_index',3,'count',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (4,'c_item_lost','������ҵĵ��ߣ�������Ʒkind��',3,-3,'actor_index',-3,'itemkind',-3,'count',-3,'path',3,'rtn',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (5,'c_item_lostitem','���������Ʒ�����ݱ���������',0,-3,'actor_index',-3,'itemoffset',-3,'count',-3,'path',3,'rtn',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (6,'c_item_getitem','��ȡ��Ʒ��ȫ������',0,-3,'actor_index',-3,'itemkind',-3,'count',-1,'color',-1,'path',3,'rtn',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (7,'c_item_get_base_ability','��ȡ����ָ��λ�õ����ԣ�������',0,-3,'itemkind',-1,'pos',2,'ability',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (8,'c_item_get_base_value','��ȡ����ָ��λ�õ���ֵ��������',0,-3,'itemkind',-1,'pos',3,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (9,'c_item_get_ability_value','����ability��ȡ����value������+��̬��',0,-3,'itemkind',-2,'ability',3,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (10,'c_item_set_abilityvalue_offset','���ݱ���������ȡ��Ʒ����',0,-3,'actor_index',-3,'item_offset',-1,'pos',-2,'ability',-3,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (11,'c_item_get_abilityvalue_offset','���ݱ�������������Ʒ����',0,-3,'actor_index',-3,'item_offset',-1,'pos',2,'rtn_ability',3,'rtn_value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (12,'c_item_getinfo','��ȡ��Ʒ��Ϣ',0,-3,'itemkind',9,'name',2,'level',1,'color',3,'price',3,'type',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (13,'c_actor_info','��ý�ɫ��Ϣ',0,-3,'actor_index',3,'actorid',3,'nation',3,'level',9,'name',2,'language',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (14,'c_actor_notify','��ʾ��Ϣ',2,-3,'actor_index',-9,'msg',-3,'msgid',0,'0',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (15,'c_actor_notify_value','��ʾ��Ϣ������',3,-3,'actor_index',-9,'msg',-3,'msgid',-3,'value1',-3,'value2',-3,'value3',-3,'value4',-3,'value5',-3,'value6',-3,'value7',-3,'value8',-3,'value9',-3,'value10',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (16,'c_actor_add_today_char_times','���ÿ����Ϣ(char)',0,-3,'actor_index',-2,'offset',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (17,'c_actor_get_today_char_times','���ÿ����Ϣ(char)',0,-3,'actor_index',-2,'offset',3,'rtn',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (18,'c_actor_set_today_char_times','����ÿ����Ϣ(char)',0,-3,'actor_index',-2,'offset',-3,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (19,'c_actor_add_today_int_times','���ÿ�մ���(int)',0,-3,'actor_index',-2,'offset',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (20,'c_actor_get_today_int_times','���ÿ�մ���(int)',0,-3,'actor_index',-2,'offset',3,'rtn',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (21,'c_actor_set_today_int_times','����ÿ�մ���(int)',0,-3,'actor_index',-2,'offset',-3,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (22,'c_actor_set_sflag','0,1�ı�־����',0,-3,'actor_index',-2,'offset',-2,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (23,'c_actor_get_sflag','0,1�ı�־����',0,-3,'actor_index',-2,'offset',2,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (24,'c_actor_set_uselimit_cd','�������CD����',0,-3,'actor_index',-1,'index',-3,'cdtime',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (25,'c_actor_get_uselimit_cd','������CD����',0,-3,'actor_index',-1,'index',3,'rtn',0,'0',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (26,'c_actor_add_week_times','������',0,-3,'actor_index',-3,'offset',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (27,'c_actor_get_week_times','������',0,-3,'actor_index',-3,'offset',3,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_c_struct` VALUES (60,'c_map_addobject','��ӵ�ͼ��������',0,-1,'type',-2,'posx',-2,'posy',-1,'unittype',3,'rtn',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (61,'c_map_delobject','ɾ����ͼ��������',0,-1,'type',-2,'posx',-2,'posy',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (62,'c_map_getrandpos','���һ���հ�λ��',0,-1,'type',2,'posx',2,'posy',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (190,'c_world_data_get','��������',0,-3,'id',3,'value',9,'strvalue',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (191,'c_world_data_set','��������',2,-3,'id',-3,'value',-9,'strvalue',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (200,'c_system_getruntime','��ȡ��������ʱ��',0,3,'time',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (201,'c_system_getopentime','��ȡ����ʱ��',0,3,'time',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (202,'c_system_getfday','��ȡ����',0,3,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (203,'c_system_gettoday','��ȡ������',0,3,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (204,'c_system_getweek','��ȡ������',0,3,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (205,'c_system_getmonth','��ȡ������',0,3,'value',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_c_struct` VALUES (210,'c_award_getaward','������',0,-3,'actor_index',-3,'kind',-3,'count',-1,'color',-1,'path',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');

#
# Source for table scsrv_in_struct
#

CREATE TABLE `scsrv_in_struct` (
  `structid` int(11) NOT NULL AUTO_INCREMENT,
  `name` varbinary(32) NOT NULL DEFAULT '',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `limitcount` smallint(6) NOT NULL DEFAULT '0',
  `t1` tinyint(3) NOT NULL DEFAULT '0',
  `arg1` varbinary(32) NOT NULL DEFAULT '',
  `t2` tinyint(3) NOT NULL DEFAULT '0',
  `arg2` varbinary(32) NOT NULL DEFAULT '',
  `t3` tinyint(3) NOT NULL DEFAULT '0',
  `arg3` varbinary(32) NOT NULL DEFAULT '',
  `t4` tinyint(3) NOT NULL DEFAULT '0',
  `arg4` varbinary(32) NOT NULL DEFAULT '',
  `t5` tinyint(3) NOT NULL DEFAULT '0',
  `arg5` varbinary(32) NOT NULL DEFAULT '',
  `t6` tinyint(3) NOT NULL DEFAULT '0',
  `arg6` varbinary(32) NOT NULL DEFAULT '',
  `t7` tinyint(3) NOT NULL DEFAULT '0',
  `arg7` varbinary(32) NOT NULL DEFAULT '',
  `t8` tinyint(3) NOT NULL DEFAULT '0',
  `arg8` varbinary(32) NOT NULL DEFAULT '',
  `t9` tinyint(3) NOT NULL DEFAULT '0',
  `arg9` varbinary(32) NOT NULL DEFAULT '',
  `t10` tinyint(3) NOT NULL DEFAULT '0',
  `arg10` varbinary(32) NOT NULL DEFAULT '',
  `t11` tinyint(3) NOT NULL DEFAULT '0',
  `arg11` varbinary(32) NOT NULL DEFAULT '',
  `t12` tinyint(3) NOT NULL DEFAULT '0',
  `arg12` varbinary(32) NOT NULL DEFAULT '',
  `t13` tinyint(3) NOT NULL DEFAULT '0',
  `arg13` varbinary(32) NOT NULL DEFAULT '',
  `t14` tinyint(3) NOT NULL DEFAULT '0',
  `arg14` varbinary(32) NOT NULL DEFAULT '',
  `t15` tinyint(3) NOT NULL DEFAULT '0',
  `arg15` varbinary(32) NOT NULL DEFAULT '',
  `t16` tinyint(3) NOT NULL DEFAULT '0',
  `arg16` varbinary(32) NOT NULL DEFAULT '',
  PRIMARY KEY (`structid`)
) ENGINE=MyISAM AUTO_INCREMENT=19 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table scsrv_in_struct
#

INSERT INTO `scsrv_in_struct` VALUES (1,'Script_Init','�ű���ʼ��',0,0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_in_struct` VALUES (2,'Script_Timer','�ű��߼�ÿ����һ��',0,0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_in_struct` VALUES (3,'Script_Command','�ű�GM����',0,-3,'nValue1',-3,'nValue2',-3,'nValue3',-3,'nValue4',-9,'pMsg',-3,'actor_index',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_in_struct` VALUES (4,'Script_Exec','�ű�ִ��',0,-3,'id',-3,'value1',-3,'value2',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_in_struct` VALUES (5,'Script_Hour','�ű��߼�ÿСʱһ��',0,0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_in_struct` VALUES (6,'OnClockProcess','����ִ��',0,-3,'hour',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_in_struct` VALUES (7,'ClientMsg','���Կͻ��˵Ľű�����',0,-3,'nPlayerIndex',-3,'nCmd',-3,'nValue1',-3,'nValue2',-3,'nValue3',-3,'nValue4',-9,'pMsg',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_in_struct` VALUES (8,'ActivityOnOpen','�����',0,-3,'activityid',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_in_struct` VALUES (9,'ActivityOnLogic','��߼�',0,-3,'activityid',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_in_struct` VALUES (10,'ActivityOnEnd','�����',0,-3,'activityid',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_in_struct` VALUES (11,'ActivityOnClose','��ر�',0,-3,'activityid',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_in_struct` VALUES (12,'UseItem','ʹ����Ʒ',0,-3,'nPlayerIndex',-3,'nMember',-3,'nItemIndex',-3,'nItemKind',-3,'nUseNum',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_in_struct` VALUES (13,'OnActorIn','����ɫ������Ϸ',0,-3,'nPlayerIndex',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'\"\"');
INSERT INTO `scsrv_in_struct` VALUES (14,'OnMailReadAttach','��ȡ����',0,-3,'nPlayerIndex',-9,'szAttach',3,'rtn',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_in_struct` VALUES (15,'TimeString','ʱ���ת��ʱ���ַ���',0,-3,'timestamp',9,'out',3,'len',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_in_struct` VALUES (16,'OnWorldMapInit','��ͼ��ʼ��',0,-3,'nMaxWidth',-3,'nMaxHeight',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_in_struct` VALUES (17,'OnWorldMapBlock','��ͼ�赲',0,-2,'posx',-2,'posy',3,'rtn',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');
INSERT INTO `scsrv_in_struct` VALUES (18,'OnWorldMapBrush','ˢ��ͼ',0,0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'',0,'');

#
# Source for table st_actor_conf
#

CREATE TABLE `st_actor_conf` (
  `dataid` int(11) NOT NULL AUTO_INCREMENT,
  `offset` int(11) NOT NULL DEFAULT '0',
  `name` varbinary(32) NOT NULL DEFAULT '',
  `data_type` smallint(6) NOT NULL DEFAULT '0',
  `data_count` smallint(6) NOT NULL DEFAULT '0',
  `data_size` smallint(6) NOT NULL DEFAULT '0',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `notsave` tinyint(4) NOT NULL DEFAULT '0',
  `kind` tinyint(4) NOT NULL DEFAULT '0',
  `m_fix` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`dataid`)
) ENGINE=MyISAM AUTO_INCREMENT=125 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table st_actor_conf
#

INSERT INTO `st_actor_conf` VALUES (1,1,'actorid',-3,0,0,'��ɫ���',0,1,0);
INSERT INTO `st_actor_conf` VALUES (2,2,'accountid',-3,0,0,'��½id',1,0,0);
INSERT INTO `st_actor_conf` VALUES (3,3,'userid',-4,0,0,'�˺ű��',3,0,0);
INSERT INTO `st_actor_conf` VALUES (4,4,'username',-1,51,0,'�˺���',3,0,0);
INSERT INTO `st_actor_conf` VALUES (5,5,'admin',-2,0,0,'����Ա����',2,0,0);
INSERT INTO `st_actor_conf` VALUES (6,6,'lastip',-1,16,0,'�ϴε�½ip',0,0,0);
INSERT INTO `st_actor_conf` VALUES (7,7,'createtime',-3,0,0,'����ʱ��',0,0,0);
INSERT INTO `st_actor_conf` VALUES (8,8,'forbidtime',-3,0,0,'����ʱ��',0,0,0);
INSERT INTO `st_actor_conf` VALUES (9,9,'savetime',-3,0,0,'�ϴα���ʱ��',1,0,0);
INSERT INTO `st_actor_conf` VALUES (10,10,'isexit',-11,0,0,'�Ƿ��뿪��Ϸ��',1,0,0);
INSERT INTO `st_actor_conf` VALUES (12,12,'view_areaindex',-2,0,0,'��ǰ�ӿڵĵ�ͼ����',1,0,0);
INSERT INTO `st_actor_conf` VALUES (13,13,'name',-1,22,0,'��ɫ����',0,0,0);
INSERT INTO `st_actor_conf` VALUES (14,14,'nation',-1,0,0,'��ɫ����',0,0,0);
INSERT INTO `st_actor_conf` VALUES (15,15,'shape',-11,0,0,'����',0,0,0);
INSERT INTO `st_actor_conf` VALUES (16,16,'level',-2,0,0,'����',0,0,0);
INSERT INTO `st_actor_conf` VALUES (20,20,'city_index',-3,0,0,'�ǳ�����',1,0,0);
INSERT INTO `st_actor_conf` VALUES (21,21,'token',-3,0,0,'��ʯ',0,0,0);
INSERT INTO `st_actor_conf` VALUES (22,22,'total_charge',-3,0,0,'�ܳ�ֵ',0,0,0);
INSERT INTO `st_actor_conf` VALUES (23,23,'charge_dollar',-5,0,0,'�����Ѷ���Ǯ',0,0,0);
INSERT INTO `st_actor_conf` VALUES (24,24,'itemext',-11,0,0,'��չ�ı�����λ��',0,0,0);
INSERT INTO `st_actor_conf` VALUES (25,25,'item',-102,300,0,'��ɫЯ���ĵ���',1,0,0);
INSERT INTO `st_actor_conf` VALUES (26,26,'equip',-109,100,0,'��ɫЯ����װ��',1,0,0);
INSERT INTO `st_actor_conf` VALUES (27,27,'equipext',-11,0,0,'��չ��װ����λ��',0,0,0);
INSERT INTO `st_actor_conf` VALUES (28,28,'hero',-108,128,0,'δ����Ӣ��',1,0,0);
INSERT INTO `st_actor_conf` VALUES (37,37,'sflag',-3,0,0,'�ض���־λ',0,0,0);
INSERT INTO `st_actor_conf` VALUES (38,38,'fdate',-3,0,0,'ˢ�µ�����������',0,0,0);
INSERT INTO `st_actor_conf` VALUES (39,39,'today_char',-7,-1,128,'char����ÿ�մ���',0,0,0);
INSERT INTO `st_actor_conf` VALUES (40,40,'today_int',-3,8,0,'int����ÿ�մ���',0,0,0);
INSERT INTO `st_actor_conf` VALUES (41,41,'cd',-3,8,0,'ͨ��CDʱ��',0,0,0);
INSERT INTO `st_actor_conf` VALUES (42,42,'config',-7,-1,8,'�������',0,0,0);
INSERT INTO `st_actor_conf` VALUES (43,43,'function',-3,0,0,'�����Ƿ���',0,0,0);
INSERT INTO `st_actor_conf` VALUES (64,64,'view_lastframe',-3,0,0,'�ϴη��͵�������Ϣʱ��',1,0,0);
INSERT INTO `st_actor_conf` VALUES (65,65,'subscribe_cmd',-2,8,0,'���ĵ���ϢID',1,0,0);
INSERT INTO `st_actor_conf` VALUES (80,80,'cdkey1',-3,0,0,'�Ƿ���ȡ�����ζһ���',0,0,0);
INSERT INTO `st_actor_conf` VALUES (81,81,'cdkey2',-3,0,0,'�Ƿ���ȡ�����ζһ���',0,0,0);
INSERT INTO `st_actor_conf` VALUES (82,82,'cdkey3',-3,0,0,'�Ƿ���ȡ�����ζһ���',0,0,0);
INSERT INTO `st_actor_conf` VALUES (83,83,'cdkey4',-3,0,0,'�Ƿ���ȡ�����ζһ���',0,0,0);
INSERT INTO `st_actor_conf` VALUES (122,122,'talkspeed_frame',-3,0,0,'˵���ӳ�',1,0,0);
INSERT INTO `st_actor_conf` VALUES (124,124,'cdkeywait',-1,0,0,'CDKEY�ȴ�',1,0,0);

#
# Source for table st_actor_equip_conf
#

CREATE TABLE `st_actor_equip_conf` (
  `dataid` int(11) NOT NULL AUTO_INCREMENT,
  `offset` int(11) NOT NULL DEFAULT '0',
  `name` varbinary(32) NOT NULL DEFAULT '',
  `data_type` smallint(6) NOT NULL DEFAULT '0',
  `data_count` smallint(6) NOT NULL DEFAULT '0',
  `data_size` smallint(6) NOT NULL DEFAULT '0',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `notsave` tinyint(4) NOT NULL DEFAULT '0',
  `kind` tinyint(4) NOT NULL DEFAULT '0',
  `m_fix` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`dataid`)
) ENGINE=MyISAM AUTO_INCREMENT=25 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table st_actor_equip_conf
#

INSERT INTO `st_actor_equip_conf` VALUES (1,1,'id',-4,0,0,'������',0,1,0);
INSERT INTO `st_actor_equip_conf` VALUES (2,2,'actorid',-3,0,0,'��ɫID',0,2,0);
INSERT INTO `st_actor_equip_conf` VALUES (3,3,'offset',-3,0,0,'װ�����ڱ���λ��',0,3,0);
INSERT INTO `st_actor_equip_conf` VALUES (4,4,'kind',-3,0,0,'��Ʒ����',0,0,0);
INSERT INTO `st_actor_equip_conf` VALUES (5,5,'ability',-2,4,0,'����',0,0,0);
INSERT INTO `st_actor_equip_conf` VALUES (6,6,'value',-3,4,0,'����ֵ',0,0,0);

#
# Source for table st_actor_hero_conf
#

CREATE TABLE `st_actor_hero_conf` (
  `dataid` int(11) NOT NULL AUTO_INCREMENT,
  `offset` int(11) NOT NULL DEFAULT '0',
  `name` varbinary(32) NOT NULL DEFAULT '',
  `data_type` smallint(6) NOT NULL DEFAULT '0',
  `data_count` smallint(6) NOT NULL DEFAULT '0',
  `data_size` smallint(6) NOT NULL DEFAULT '0',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `notsave` tinyint(4) NOT NULL DEFAULT '0',
  `kind` tinyint(4) NOT NULL DEFAULT '0',
  `m_fix` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`dataid`)
) ENGINE=MyISAM AUTO_INCREMENT=22 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table st_actor_hero_conf
#

INSERT INTO `st_actor_hero_conf` VALUES (1,1,'id',-4,0,0,'������',0,1,0);
INSERT INTO `st_actor_hero_conf` VALUES (2,2,'actorid',-3,0,0,'�ǳ�',0,2,0);
INSERT INTO `st_actor_hero_conf` VALUES (3,3,'offset',-3,0,0,'����',0,3,0);
INSERT INTO `st_actor_hero_conf` VALUES (4,4,'kind',-2,0,0,'Ӣ������',0,0,0);
INSERT INTO `st_actor_hero_conf` VALUES (5,5,'level',-2,0,0,'�ȼ�',0,0,0);
INSERT INTO `st_actor_hero_conf` VALUES (6,6,'exp',-3,0,0,'����',0,0,0);
INSERT INTO `st_actor_hero_conf` VALUES (7,7,'soldiers',-3,0,0,'����',0,0,0);
INSERT INTO `st_actor_hero_conf` VALUES (8,8,'attack',-2,0,0,'��������',0,0,0);
INSERT INTO `st_actor_hero_conf` VALUES (9,9,'defense',-2,0,0,'��������',0,0,0);
INSERT INTO `st_actor_hero_conf` VALUES (10,10,'troops',-2,0,0,'��������',0,0,0);
INSERT INTO `st_actor_hero_conf` VALUES (11,11,'growth',-2,0,0,'������',0,0,0);
INSERT INTO `st_actor_hero_conf` VALUES (12,12,'equip',-109,6,0,'װ��',1,0,0);

#
# Source for table st_actor_item_conf
#

CREATE TABLE `st_actor_item_conf` (
  `dataid` int(11) NOT NULL AUTO_INCREMENT,
  `offset` int(11) NOT NULL DEFAULT '0',
  `name` varbinary(32) NOT NULL DEFAULT '',
  `data_type` smallint(6) NOT NULL DEFAULT '0',
  `data_count` smallint(6) NOT NULL DEFAULT '0',
  `data_size` smallint(6) NOT NULL DEFAULT '0',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `notsave` tinyint(4) NOT NULL DEFAULT '0',
  `kind` tinyint(4) NOT NULL DEFAULT '0',
  `m_fix` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`dataid`)
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table st_actor_item_conf
#

INSERT INTO `st_actor_item_conf` VALUES (1,1,'id',-4,0,0,'��Ʒid',0,1,0);
INSERT INTO `st_actor_item_conf` VALUES (2,2,'actorid',-3,0,0,'��ɫID',0,2,0);
INSERT INTO `st_actor_item_conf` VALUES (3,3,'offset',-2,0,0,'��Ʒ����λ��',0,3,0);
INSERT INTO `st_actor_item_conf` VALUES (4,4,'kind',-3,0,0,'��Ʒ����',0,0,1);
INSERT INTO `st_actor_item_conf` VALUES (5,5,'num',-2,0,0,'��Ʒ����',0,0,1);
INSERT INTO `st_actor_item_conf` VALUES (6,6,'ability',-2,4,0,'����',0,0,1);
INSERT INTO `st_actor_item_conf` VALUES (7,7,'value',-3,4,0,'����ֵ',0,0,1);
INSERT INTO `st_actor_item_conf` VALUES (8,8,'color_level',-1,0,0,'��ɫ�ȼ�',0,0,1);

#
# Source for table st_army_conf
#

CREATE TABLE `st_army_conf` (
  `dataid` int(11) NOT NULL AUTO_INCREMENT,
  `offset` int(11) NOT NULL DEFAULT '0',
  `name` varbinary(32) NOT NULL DEFAULT '',
  `data_type` smallint(6) NOT NULL DEFAULT '0',
  `data_count` smallint(6) NOT NULL DEFAULT '0',
  `data_size` smallint(6) NOT NULL DEFAULT '0',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `notsave` tinyint(4) NOT NULL DEFAULT '0',
  `kind` tinyint(4) NOT NULL DEFAULT '0',
  `m_fix` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`dataid`)
) ENGINE=MyISAM AUTO_INCREMENT=219 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table st_army_conf
#

INSERT INTO `st_army_conf` VALUES (1,1,'index',-3,0,0,'��������',0,1,0);
INSERT INTO `st_army_conf` VALUES (2,2,'id',-3,0,0,'����ΨһID,�Ϸ�����֤',0,0,0);
INSERT INTO `st_army_conf` VALUES (3,3,'unit_index',-3,0,0,'��ʾ����',1,0,0);
INSERT INTO `st_army_conf` VALUES (4,4,'state',-1,0,0,'״̬',0,0,0);
INSERT INTO `st_army_conf` VALUES (5,5,'statetime',-3,0,0,'״̬ʱ���',0,0,0);
INSERT INTO `st_army_conf` VALUES (6,6,'stateduration',-3,0,0,'״̬����������',0,0,0);
INSERT INTO `st_army_conf` VALUES (7,7,'action',-3,0,0,'��Ϊ',0,0,0);
INSERT INTO `st_army_conf` VALUES (8,8,'from_type',-2,0,0,'�����Ķ�������',0,0,0);
INSERT INTO `st_army_conf` VALUES (9,9,'from_id',-3,0,0,'�����Ķ���ID',0,0,0);
INSERT INTO `st_army_conf` VALUES (10,10,'from_index',-3,0,0,'�����Ķ�������',0,0,0);
INSERT INTO `st_army_conf` VALUES (11,11,'from_posx',-2,0,0,'�����Ķ�������',0,0,0);
INSERT INTO `st_army_conf` VALUES (12,12,'from_posy',-2,0,0,'�����Ķ�������',0,0,0);
INSERT INTO `st_army_conf` VALUES (40,13,'to_type',-2,0,0,'Ŀ�Ķ�������',0,0,0);
INSERT INTO `st_army_conf` VALUES (41,14,'to_id',-3,0,0,'Ŀ�Ķ���ID',0,0,0);
INSERT INTO `st_army_conf` VALUES (42,15,'to_index',-3,0,0,'Ŀ�Ķ�������',0,0,0);
INSERT INTO `st_army_conf` VALUES (50,16,'to_posx',-2,0,0,'Ŀ�Ķ�������',0,0,0);
INSERT INTO `st_army_conf` VALUES (60,17,'to_posy',-2,0,0,'Ŀ�Ķ�������',0,0,0);
INSERT INTO `st_army_conf` VALUES (70,18,'posx',-2,0,0,'��ǰ����',0,0,0);
INSERT INTO `st_army_conf` VALUES (80,19,'posy',-2,0,0,'��ǰ����',0,0,0);
INSERT INTO `st_army_conf` VALUES (90,90,'herokind',-2,4,0,'�佫',0,0,0);

#
# Source for table st_city_building_barracks_conf
#

CREATE TABLE `st_city_building_barracks_conf` (
  `dataid` int(11) NOT NULL AUTO_INCREMENT,
  `offset` int(11) NOT NULL DEFAULT '0',
  `name` varbinary(32) NOT NULL DEFAULT '',
  `data_type` smallint(6) NOT NULL DEFAULT '0',
  `data_count` smallint(6) NOT NULL DEFAULT '0',
  `data_size` smallint(6) NOT NULL DEFAULT '0',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `notsave` tinyint(4) NOT NULL DEFAULT '0',
  `kind` tinyint(4) NOT NULL DEFAULT '0',
  `m_fix` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`dataid`)
) ENGINE=MyISAM AUTO_INCREMENT=81 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table st_city_building_barracks_conf
#

INSERT INTO `st_city_building_barracks_conf` VALUES (1,1,'actorid',-3,0,0,'',-1,1,0);
INSERT INTO `st_city_building_barracks_conf` VALUES (2,2,'offset',-1,0,0,'',-1,2,0);
INSERT INTO `st_city_building_barracks_conf` VALUES (3,3,'kind',-1,0,0,'��Ӫ����',0,0,0);
INSERT INTO `st_city_building_barracks_conf` VALUES (4,4,'level',-1,0,0,'��Ӫ�ȼ�',0,0,0);
INSERT INTO `st_city_building_barracks_conf` VALUES (5,5,'soldiers',-3,0,0,'��Ӫ����',0,0,0);
INSERT INTO `st_city_building_barracks_conf` VALUES (6,6,'trainnum',-3,0,0,'��ǰѵ��ʿ����',0,0,0);
INSERT INTO `st_city_building_barracks_conf` VALUES (7,7,'trainsec',-3,0,0,'��ǰѵ��ʣ��ʱ��(��)',0,0,0);
INSERT INTO `st_city_building_barracks_conf` VALUES (9,9,'queuenum',-3,8,0,'��ļ����',0,0,0);
INSERT INTO `st_city_building_barracks_conf` VALUES (10,10,'queuesec',-3,8,0,'��ļ����',0,0,0);
INSERT INTO `st_city_building_barracks_conf` VALUES (11,11,'queue',-1,0,0,'���ݶ�������',0,0,0);
INSERT INTO `st_city_building_barracks_conf` VALUES (12,12,'trainlong',-1,0,0,'ļ����ʱ����',0,0,0);
INSERT INTO `st_city_building_barracks_conf` VALUES (13,13,'quicksec',-2,0,0,'ļ������ʱ����',0,0,0);

#
# Source for table st_city_building_conf
#

CREATE TABLE `st_city_building_conf` (
  `dataid` int(11) NOT NULL AUTO_INCREMENT,
  `offset` int(11) NOT NULL DEFAULT '0',
  `name` varbinary(32) NOT NULL DEFAULT '',
  `data_type` smallint(6) NOT NULL DEFAULT '0',
  `data_count` smallint(6) NOT NULL DEFAULT '0',
  `data_size` smallint(6) NOT NULL DEFAULT '0',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `notsave` tinyint(4) NOT NULL DEFAULT '0',
  `kind` tinyint(4) NOT NULL DEFAULT '0',
  `m_fix` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`dataid`)
) ENGINE=MyISAM AUTO_INCREMENT=13 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table st_city_building_conf
#

INSERT INTO `st_city_building_conf` VALUES (1,1,'actorid',-3,0,0,'',-1,1,0);
INSERT INTO `st_city_building_conf` VALUES (2,2,'offset',-1,0,0,'',-1,2,0);
INSERT INTO `st_city_building_conf` VALUES (3,3,'kind',-1,0,0,'��������',0,0,0);
INSERT INTO `st_city_building_conf` VALUES (4,4,'level',-1,0,0,'�����ȼ�',0,0,0);
INSERT INTO `st_city_building_conf` VALUES (5,5,'officialkind',-1,0,0,'����ʹ�ù�Ա',0,0,0);
INSERT INTO `st_city_building_conf` VALUES (6,6,'officialfree',-3,0,0,'�Ƿ�ʹ�ù����(��λ)',0,0,0);
INSERT INTO `st_city_building_conf` VALUES (7,7,'officialsec',-3,0,0,'��Աʣ��ʱ��',0,0,0);
INSERT INTO `st_city_building_conf` VALUES (8,8,'value',-3,0,0,'ͨ��ֵ',0,0,0);
INSERT INTO `st_city_building_conf` VALUES (9,9,'sec',-3,0,0,'ʱ��',0,0,0);
INSERT INTO `st_city_building_conf` VALUES (10,10,'quicksec',-2,0,0,'����ʱ��',0,0,0);

#
# Source for table st_city_building_res_conf
#

CREATE TABLE `st_city_building_res_conf` (
  `dataid` int(11) NOT NULL AUTO_INCREMENT,
  `offset` int(11) NOT NULL DEFAULT '0',
  `name` varbinary(32) NOT NULL DEFAULT '',
  `data_type` smallint(6) NOT NULL DEFAULT '0',
  `data_count` smallint(6) NOT NULL DEFAULT '0',
  `data_size` smallint(6) NOT NULL DEFAULT '0',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `notsave` tinyint(4) NOT NULL DEFAULT '0',
  `kind` tinyint(4) NOT NULL DEFAULT '0',
  `m_fix` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`dataid`)
) ENGINE=MyISAM AUTO_INCREMENT=9 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table st_city_building_res_conf
#

INSERT INTO `st_city_building_res_conf` VALUES (1,1,'actorid',-3,0,0,'',-1,1,0);
INSERT INTO `st_city_building_res_conf` VALUES (2,2,'offset',-1,0,0,'',-1,2,0);
INSERT INTO `st_city_building_res_conf` VALUES (3,3,'kind',-1,0,0,'��Դ��������',0,0,0);
INSERT INTO `st_city_building_res_conf` VALUES (4,4,'level',-1,0,0,'��Դ�����ȼ�',0,0,0);

#
# Source for table st_city_conf
#

CREATE TABLE `st_city_conf` (
  `dataid` int(11) NOT NULL AUTO_INCREMENT,
  `offset` int(11) NOT NULL DEFAULT '0',
  `name` varbinary(32) NOT NULL DEFAULT '',
  `data_type` smallint(6) NOT NULL DEFAULT '0',
  `data_count` smallint(6) NOT NULL DEFAULT '0',
  `data_size` smallint(6) NOT NULL DEFAULT '0',
  `context` varbinary(128) NOT NULL DEFAULT '',
  `notsave` tinyint(4) NOT NULL DEFAULT '0',
  `kind` tinyint(4) NOT NULL DEFAULT '0',
  `m_fix` tinyint(4) NOT NULL DEFAULT '0',
  PRIMARY KEY (`dataid`)
) ENGINE=MyISAM AUTO_INCREMENT=204 DEFAULT CHARSET=gbk ROW_FORMAT=DYNAMIC;

#
# Dumping data for table st_city_conf
#

INSERT INTO `st_city_conf` VALUES (1,1,'actorid',-3,0,0,'��ɫID',0,1,0);
INSERT INTO `st_city_conf` VALUES (2,2,'index',-3,0,0,'����',0,0,0);
INSERT INTO `st_city_conf` VALUES (4,4,'name',-1,22,0,'����',0,0,0);
INSERT INTO `st_city_conf` VALUES (5,5,'type',-1,0,0,'�ǳ�����',0,0,0);
INSERT INTO `st_city_conf` VALUES (6,6,'shape',-1,0,0,'��������(ѡȡ)',0,0,0);
INSERT INTO `st_city_conf` VALUES (7,7,'headid',-3,0,0,'����ͷ��(�Զ���)',0,0,0);
INSERT INTO `st_city_conf` VALUES (8,8,'country',-2,0,0,'ѡ��Ĺ���(��ʵ)',0,0,0);
INSERT INTO `st_city_conf` VALUES (9,9,'ipcountry',-1,3,0,'IP��ַ���ڹ���',0,0,0);
INSERT INTO `st_city_conf` VALUES (10,10,'language',-1,0,0,'ѡ������',0,0,0);
INSERT INTO `st_city_conf` VALUES (11,11,'os',-1,0,0,'ϵͳ1ios 2android 3win',0,0,0);
INSERT INTO `st_city_conf` VALUES (12,12,'platid',-1,0,0,'ƽ̨',0,0,0);
INSERT INTO `st_city_conf` VALUES (13,13,'createtime',-3,0,0,'����ʱ��',0,0,0);
INSERT INTO `st_city_conf` VALUES (14,14,'lastlogin',-3,0,0,'�ϴε�½ʱ��',0,0,0);
INSERT INTO `st_city_conf` VALUES (15,15,'lastlogout',-3,0,0,'�ϴεǳ�ʱ��',0,0,0);
INSERT INTO `st_city_conf` VALUES (16,16,'state',-1,0,0,'�ǳص�ǰ״̬',0,0,0);
INSERT INTO `st_city_conf` VALUES (17,17,'posx',-2,0,0,'λ��',0,0,0);
INSERT INTO `st_city_conf` VALUES (18,18,'posy',-2,0,0,'λ��',0,0,0);
INSERT INTO `st_city_conf` VALUES (19,19,'sflag',-3,0,0,'��־λ',0,0,0);
INSERT INTO `st_city_conf` VALUES (20,20,'level',-2,0,0,'��ҵȼ�',0,0,0);
INSERT INTO `st_city_conf` VALUES (21,21,'exp',-3,0,0,'��Ҿ���',0,0,0);
INSERT INTO `st_city_conf` VALUES (22,22,'viplevel',-1,0,0,'VIP�ȼ�',1,0,0);
INSERT INTO `st_city_conf` VALUES (23,23,'vipexp',-3,0,0,'VIP����',0,0,0);
INSERT INTO `st_city_conf` VALUES (24,24,'nation',-1,0,0,'����(κ����)',0,0,0);
INSERT INTO `st_city_conf` VALUES (25,25,'official',-1,0,0,'��ְ',0,0,0);
INSERT INTO `st_city_conf` VALUES (26,26,'place',-1,0,0,'��λ',0,0,0);
INSERT INTO `st_city_conf` VALUES (27,27,'zone',-1,0,0,'����',0,0,0);
INSERT INTO `st_city_conf` VALUES (28,28,'battlepower',-3,0,0,'ս��',0,0,0);
INSERT INTO `st_city_conf` VALUES (29,29,'mokilllv',-1,0,0,'��ɱҰ����߼���',0,0,0);
INSERT INTO `st_city_conf` VALUES (30,30,'body',-2,0,0,'����',0,0,0);
INSERT INTO `st_city_conf` VALUES (31,31,'bodysec',-2,0,0,'�����ָ�ʱ��(ÿ��-1)',0,0,0);
INSERT INTO `st_city_conf` VALUES (32,32,'silver',-3,0,0,'����',0,0,0);
INSERT INTO `st_city_conf` VALUES (33,33,'wood',-3,0,0,'ľ��',0,0,0);
INSERT INTO `st_city_conf` VALUES (34,34,'food',-3,0,0,'����',0,0,0);
INSERT INTO `st_city_conf` VALUES (35,35,'iron',-3,0,0,'����',0,0,0);
INSERT INTO `st_city_conf` VALUES (36,36,'levynum',-11,0,0,'��ǰ���մ���',0,0,0);
INSERT INTO `st_city_conf` VALUES (37,37,'levysec',-2,0,0,'�´�����ʱ��(ÿ��-1)',0,0,0);
INSERT INTO `st_city_conf` VALUES (38,38,'people',-3,0,0,'�˿�',0,0,0);
INSERT INTO `st_city_conf` VALUES (39,39,'prestige',-3,0,0,'����ֵ',0,0,0);
INSERT INTO `st_city_conf` VALUES (40,40,'friendship',-3,0,0,'�������',0,0,0);
INSERT INTO `st_city_conf` VALUES (41,41,'function',-3,0,0,'�����Ƿ���',0,0,0);
INSERT INTO `st_city_conf` VALUES (98,98,'hero',-108,4,0,'����Ӣ��',0,0,0);
INSERT INTO `st_city_conf` VALUES (100,100,'building',-105,8,0,'��ͨ����',0,0,0);
INSERT INTO `st_city_conf` VALUES (101,101,'building_barracks',-106,4,0,'��Ӫ����',0,0,0);
INSERT INTO `st_city_conf` VALUES (102,102,'building_res',-107,64,0,'��Դ����',0,0,0);
INSERT INTO `st_city_conf` VALUES (103,103,'worker_op',-1,0,0,'������в���',0,0,0);
INSERT INTO `st_city_conf` VALUES (104,104,'worker_sec',-3,0,0,'����ʣ��ʱ��(ÿ��-1)',0,0,0);
INSERT INTO `st_city_conf` VALUES (105,105,'worker_kind',-1,0,0,'��ǰ������������',0,0,0);
INSERT INTO `st_city_conf` VALUES (106,106,'worker_offset',-1,0,0,'��ǰ������������',0,0,0);
INSERT INTO `st_city_conf` VALUES (107,107,'worker_op_ex',-1,0,0,'������в���(����)',0,0,0);
INSERT INTO `st_city_conf` VALUES (108,108,'worker_sec_ex',-3,0,0,'����ʣ��ʱ��(ÿ��-1)(����)',0,0,0);
INSERT INTO `st_city_conf` VALUES (109,109,'worker_kind_ex',-1,0,0,'��ǰ������������(����)',0,0,0);
INSERT INTO `st_city_conf` VALUES (110,110,'worker_offset_ex',-1,0,0,'��ǰ������������(����)',0,0,0);
INSERT INTO `st_city_conf` VALUES (111,111,'worker_expire_ex',-3,0,0,'���ý�����е���ʱ��',0,0,0);
INSERT INTO `st_city_conf` VALUES (201,201,'actor_index',-3,0,0,'��ɫ����',1,0,0);
INSERT INTO `st_city_conf` VALUES (202,202,'unit_index',-3,0,0,'��ʾ����',1,0,0);
INSERT INTO `st_city_conf` VALUES (203,203,'army_index',-3,5,0,'����',1,0,0);

#
# Source for table struct_data
#

CREATE TABLE `struct_data` (
  `id` int(11) NOT NULL DEFAULT '0',
  `table` varchar(255) NOT NULL DEFAULT '' COMMENT '����',
  `table_name` varchar(255) NOT NULL DEFAULT '' COMMENT '���ݿ����',
  `table_struct` varchar(255) NOT NULL DEFAULT '' COMMENT '����Ľṹ����',
  `load_key_dataid` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��ȡ�ļ���0ȫ������Ӧÿ����ڼ�����',
  `load_get_cb` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��ȡ֮ǰ�ĺ����ص�',
  `load_end_cb` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��ȡ֮��ĺ����ص�',
  `load_cb_dataid1` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�ص�key',
  `load_cb_dataid2` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�ص�key',
  `save_key_dataid` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�浵������0ȫ��',
  `save_clear` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�浵ǰ�Ƿ��������ݿ�',
  `save_batch` int(11) NOT NULL DEFAULT '0' COMMENT '>0ʹ��replace�������﷨',
  `type` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�������ͣ��������⴦��һ��',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

#
# Dumping data for table struct_data
#

INSERT INTO `struct_data` VALUES (1,'st_actor_conf','actor','Actor',1,0,0,0,0,0,0,0,0);
INSERT INTO `struct_data` VALUES (2,'st_actor_item_conf','actor_item','Item',2,1,0,2,3,1,0,256,1);
INSERT INTO `struct_data` VALUES (3,'st_city_conf','city','City',0,1,1,2,0,0,0,0,0);
INSERT INTO `struct_data` VALUES (4,'st_army_conf','army','Army',0,1,1,1,0,2,1,256,0);
INSERT INTO `struct_data` VALUES (5,'st_city_building_conf','city_building','Building',1,1,0,1,2,3,0,64,2);
INSERT INTO `struct_data` VALUES (6,'st_city_building_barracks_conf','city_building_barracks','BuildingBarracks',1,1,0,1,2,3,0,64,2);
INSERT INTO `struct_data` VALUES (7,'st_city_building_res_conf','city_building_res','BuildingRes',1,1,0,1,2,3,0,64,2);
INSERT INTO `struct_data` VALUES (8,'st_actor_hero_conf','actor_hero','Hero',2,1,0,2,3,1,0,128,1);
INSERT INTO `struct_data` VALUES (9,'st_actor_equip_conf','actor_equip','Equip',2,1,0,2,3,1,0,256,1);

#
# Source for table struct_serv_data
#

CREATE TABLE `struct_serv_data` (
  `id` int(11) NOT NULL DEFAULT '0',
  `table` varchar(255) NOT NULL DEFAULT '' COMMENT '����',
  `struct_name` varchar(255) NOT NULL DEFAULT '' COMMENT '�ṹ����',
  `variable_name` varchar(255) NOT NULL DEFAULT '' COMMENT '������',
  `skip_field1` varchar(32) NOT NULL DEFAULT '' COMMENT '�����ֶ�',
  `skip_field2` varchar(32) NOT NULL DEFAULT '',
  `skip_field3` varchar(32) NOT NULL DEFAULT '',
  `skip_field4` varchar(32) NOT NULL DEFAULT '',
  `fix` tinyint(3) NOT NULL DEFAULT '0',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=gbk;

#
# Dumping data for table struct_serv_data
#

INSERT INTO `struct_serv_data` VALUES (1,'item','ItemKind','g_itemkind','used','','','',1);
INSERT INTO `struct_serv_data` VALUES (2,'platinfo','PlatInfo','g_platinfo','desc','','','',0);
INSERT INTO `struct_serv_data` VALUES (3,'upgrade','UpgradeInfo','g_upgradeinfo','','','','',0);
INSERT INTO `struct_serv_data` VALUES (4,'paycountry','PayCountry','g_paycountry','name','','','',0);
INSERT INTO `struct_serv_data` VALUES (5,'paygoods','PayGoods','g_paygoods','name','','','',0);
INSERT INTO `struct_serv_data` VALUES (6,'building_upgrade','BuildingUpgrade','g_building_upgrade','name','','','',0);
INSERT INTO `struct_serv_data` VALUES (7,'vip','VipInfo','g_vipinfo','','','','',0);

/*!40111 SET SQL_NOTES=@OLD_SQL_NOTES */;
/*!40101 SET SQL_MODE=@OLD_SQL_MODE */;

CREATE TABLE `city_attr` (
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '��ɫID',
  `silver_per` smallint(6) NOT NULL DEFAULT '0' COMMENT '���Ҳ�������%',
  `wood_per` smallint(6) NOT NULL DEFAULT '0' COMMENT 'ľ�Ĳ�������%',
  `food_per` smallint(6) NOT NULL DEFAULT '0' COMMENT '��ʳ��������%',
  `iron_per` smallint(6) NOT NULL DEFAULT '0' COMMENT '������������%',
  `protectres_per` smallint(6) NOT NULL DEFAULT '0' COMMENT '�ֿⱣ������%',
  `buildingsec_per` smallint(6) NOT NULL DEFAULT '0' COMMENT '����ʱ�����%',
  `infantry_attack` smallint(6) NOT NULL DEFAULT '0' COMMENT '�����佫���ӹ�����',
  `cavalry_attack` smallint(6) NOT NULL DEFAULT '0' COMMENT '����佫���ӹ�����',
  `archer_attack` smallint(6) NOT NULL DEFAULT '0' COMMENT '�����佫���ӹ�����',
  PRIMARY KEY (`actorid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

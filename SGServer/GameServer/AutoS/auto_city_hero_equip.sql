CREATE TABLE `city_hero_equip` (
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '�����ǳ�',
  `herokind` smallint(6) NOT NULL DEFAULT '0' COMMENT '����Ӣ��',
  `offset` smallint(6) NOT NULL DEFAULT '0' COMMENT '��Ʒ����λ��',
  `kind` int(11) NOT NULL DEFAULT '0' COMMENT '��Ʒ����',
  `ability0` smallint(6) NOT NULL DEFAULT '0' COMMENT '����',
  `ability1` smallint(6) NOT NULL DEFAULT '0' COMMENT '����',
  `ability2` smallint(6) NOT NULL DEFAULT '0' COMMENT '����',
  `ability3` smallint(6) NOT NULL DEFAULT '0' COMMENT '����',
  `value0` int(11) NOT NULL DEFAULT '0' COMMENT '����ֵ',
  `value1` int(11) NOT NULL DEFAULT '0' COMMENT '����ֵ',
  `value2` int(11) NOT NULL DEFAULT '0' COMMENT '����ֵ',
  `value3` int(11) NOT NULL DEFAULT '0' COMMENT '����ֵ',
  PRIMARY KEY (`actorid`)
  KEY (`herokind`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `city_hero` (
  `cityid` int(11) NOT NULL DEFAULT '0' COMMENT '�ǳ�',
  `offset` tinyint(4) NOT NULL DEFAULT '0' COMMENT '����',
  `kind` smallint(6) NOT NULL DEFAULT '0' COMMENT 'Ӣ������',
  `level` smallint(6) NOT NULL DEFAULT '0' COMMENT '�ȼ�',
  `exp` int(11) NOT NULL DEFAULT '0' COMMENT '����',
  `soldiers` smallint(6) NOT NULL DEFAULT '0' COMMENT '����',
  `attack` smallint(6) NOT NULL DEFAULT '0' COMMENT '��������',
  `defense` smallint(6) NOT NULL DEFAULT '0' COMMENT '��������',
  `troops` smallint(6) NOT NULL DEFAULT '0' COMMENT '��������',
  `growth` smallint(6) NOT NULL DEFAULT '0' COMMENT '������',
  PRIMARY KEY (`cityid`)
  KEY (`offset`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

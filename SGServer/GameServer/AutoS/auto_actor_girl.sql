CREATE TABLE `actor_girl` (
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '��ɫ',
  `kind` tinyint(3) NOT NULL DEFAULT '0' COMMENT '����',
  `color` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��ɫ',
  `sflag` tinyint(3) NOT NULL DEFAULT '0' COMMENT '���',
  `love_level` tinyint(3) NOT NULL DEFAULT '0' COMMENT '���ܵȼ�',
  `soul` smallint(6) NOT NULL DEFAULT '0' COMMENT '��Ƭ',
  `love_exp` smallint(6) NOT NULL DEFAULT '0' COMMENT '���ܶ�',
  `love_today` smallint(6) NOT NULL DEFAULT '0' COMMENT '�����ȡ���ܶ�',
  `herokind` smallint(6) NOT NULL DEFAULT '0' COMMENT '�����н�',
  PRIMARY KEY (`actorid`)
  KEY (`kind`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

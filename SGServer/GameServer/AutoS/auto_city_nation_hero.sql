CREATE TABLE `city_nation_hero` (
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '',
  `offset` tinyint(3) NOT NULL DEFAULT '0' COMMENT '',
  `state` tinyint(3) NOT NULL DEFAULT '0' COMMENT '1��Ѻ,2�Ѿ�Ȱ��',
  `kind` smallint(6) NOT NULL DEFAULT '0' COMMENT '',
  `forever` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�Ƿ�����ӵ��',
  `loyal` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�ҳ϶�',
  `buypos` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�����������',
  PRIMARY KEY (`actorid`)
  KEY (`offset`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

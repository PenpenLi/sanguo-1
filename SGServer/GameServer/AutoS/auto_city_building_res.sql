CREATE TABLE `city_building_res` (
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '',
  `offset` tinyint(3) NOT NULL DEFAULT '0' COMMENT '',
  `kind` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��Դ��������',
  `level` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��Դ�����ȼ�',
  PRIMARY KEY (`actorid`)
  KEY (`offset`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

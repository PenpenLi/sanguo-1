CREATE TABLE `city_building` (
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '',
  `offset` tinyint(3) NOT NULL DEFAULT '0' COMMENT '',
  `kind` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��������',
  `level` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�����ȼ�',
  `sec` int(11) NOT NULL DEFAULT '0' COMMENT 'ʱ��',
  `value` int(11) NOT NULL DEFAULT '0' COMMENT 'ͨ��ֵ',
  `overvalue` int(11) NOT NULL DEFAULT '0' COMMENT '��ɵ�ֵ',
  `quicksec` smallint(6) NOT NULL DEFAULT '0' COMMENT '����ʱ��',
  PRIMARY KEY (`actorid`)
  KEY (`offset`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

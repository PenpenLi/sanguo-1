CREATE TABLE `city_building` (
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '',
  `offset` tinyint(3) NOT NULL DEFAULT '0' COMMENT '',
  `kind` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��������',
  `level` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�����ȼ�',
  `officialkind` tinyint(3) NOT NULL DEFAULT '0' COMMENT '����ʹ�ù�Ա',
  `officialfree` int(11) NOT NULL DEFAULT '0' COMMENT '�Ƿ�ʹ�ù����(��λ)',
  `officialsec` int(11) NOT NULL DEFAULT '0' COMMENT '��Աʣ��ʱ��',
  `value` int(11) NOT NULL DEFAULT '0' COMMENT 'ͨ��ֵ',
  `sec` int(11) NOT NULL DEFAULT '0' COMMENT 'ʱ��',
  `quicksec` smallint(6) NOT NULL DEFAULT '0' COMMENT '����ʱ��',
  PRIMARY KEY (`actorid`)
  KEY (`offset`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

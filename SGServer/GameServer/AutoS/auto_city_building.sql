CREATE TABLE `city_building` (
  `cityid` int(11) NOT NULL DEFAULT '0' COMMENT '',
  `offset` tinyint(4) NOT NULL DEFAULT '0' COMMENT '',
  `kind` tinyint(4) NOT NULL DEFAULT '0' COMMENT '��Դ��������',
  `level` tinyint(4) NOT NULL DEFAULT '0' COMMENT '��Դ�����ȼ�',
  `finish` int(11) NOT NULL DEFAULT '0' COMMENT '����ʱ��',
  `official` tinyint(4) NOT NULL DEFAULT '0' COMMENT '��Ա����',
  `value` int(11) NOT NULL DEFAULT '0' COMMENT 'ͨ��ֵ',
  PRIMARY KEY (`cityid`)
  KEY (`offset`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

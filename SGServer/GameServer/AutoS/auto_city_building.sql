CREATE TABLE `city_building` (
  `cityid` int(11) NOT NULL DEFAULT '0' COMMENT '',
  `offset` tinyint(4) NOT NULL DEFAULT '0' COMMENT '',
  `kind` tinyint(4) NOT NULL DEFAULT '0' COMMENT '��������',
  `level` tinyint(4) NOT NULL DEFAULT '0' COMMENT '�����ȼ�',
  `official` tinyint(4) NOT NULL DEFAULT '0' COMMENT '����ʹ�ù�Ա����',
  `officialfree` tinyint(4) NOT NULL DEFAULT '0' COMMENT '��Ա���鼶��',
  `officialsec` int(11) NOT NULL DEFAULT '0' COMMENT 'ʣ��ʱ��',
  `value` int(11) NOT NULL DEFAULT '0' COMMENT 'ͨ��ֵ',
  PRIMARY KEY (`cityid`)
  KEY (`offset`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

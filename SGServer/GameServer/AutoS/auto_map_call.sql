CREATE TABLE `map_call` (
  `index` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�ٻ��¼�����',
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '�������',
  `limitlevel` smallint(6) NOT NULL DEFAULT '0' COMMENT '等级限制',
  `endtimestamp` int(11) NOT NULL DEFAULT '0' COMMENT '����ʱ��',
  `num` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��ǰ�ٻ�����',
  `maxnum` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�ٻ���������',
  PRIMARY KEY (`index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `map_call` (
  `index` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�ٻ��¼�����',
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '�������',
  `posx` smallint(6) NOT NULL DEFAULT '0' COMMENT 'λ��',
  `posy` smallint(6) NOT NULL DEFAULT '0' COMMENT 'λ��',
  `endtimestamp` int(11) NOT NULL DEFAULT '0' COMMENT '����ʱ��',
  `num` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��ǰ�ٻ�����',
  `maxnum` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�ٻ���������',
  `invite` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�������',
  PRIMARY KEY (`index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

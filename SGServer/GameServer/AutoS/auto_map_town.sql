CREATE TABLE `map_town` (
  `townid` int(11) NOT NULL DEFAULT '0' COMMENT '����id',
  `nation` tinyint(3) NOT NULL DEFAULT '0' COMMENT '����',
  `name` varbinary(22) NOT NULL DEFAULT '' COMMENT '�޸ĺ������',
  `protect_sec` int(11) NOT NULL DEFAULT '0' COMMENT '����ʱ��',
  `produce_num` smallint(6) NOT NULL DEFAULT '0' COMMENT '���մ���',
  `produce_sec` int(11) NOT NULL DEFAULT '0' COMMENT '����ʱ��',
  `own_actorid` int(11) NOT NULL DEFAULT '0' COMMENT '������ɫid',
  `own_sec` int(11) NOT NULL DEFAULT '0' COMMENT '�������ڵ���ʱ',
  `join_actorid` varbinary(512) NOT NULL DEFAULT '' COMMENT '��ս��Ա',
  `ask_actorid` varbinary(512) NOT NULL DEFAULT '' COMMENT '������Ա',
  `soldier` varbinary(64) NOT NULL DEFAULT '' COMMENT '����Ѫ���浵',
  `soldier_update` tinyint(3) NOT NULL DEFAULT '0' COMMENT '����Ѫ���浵����',
  PRIMARY KEY (`townid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

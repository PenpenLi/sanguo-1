CREATE TABLE `nation_hero` (
  `kind` smallint(6) NOT NULL DEFAULT '0' COMMENT '��������kind',
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '��ǰ�������',
  `posx` smallint(6) NOT NULL DEFAULT '0' COMMENT 'λ��',
  `posy` smallint(6) NOT NULL DEFAULT '0' COMMENT 'λ��',
  `runsec` int(11) NOT NULL DEFAULT '0' COMMENT '���ܵ���ʱ',
  PRIMARY KEY (`kind`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

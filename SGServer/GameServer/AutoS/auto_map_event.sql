CREATE TABLE `map_event` (
  `index` int(11) NOT NULL DEFAULT '0' COMMENT '�¼�����',
  `posx` smallint(6) NOT NULL DEFAULT '0' COMMENT 'λ��',
  `posy` smallint(6) NOT NULL DEFAULT '0' COMMENT 'λ��',
  `kind` smallint(6) NOT NULL DEFAULT '0' COMMENT '����',
  `waitsec` int(11) NOT NULL DEFAULT '0' COMMENT '����ʱ',
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '���ڽ�ɫ',
  `state` tinyint(3) NOT NULL DEFAULT '0' COMMENT '״̬',
  PRIMARY KEY (`index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

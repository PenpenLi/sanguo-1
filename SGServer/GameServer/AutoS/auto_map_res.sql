CREATE TABLE `map_res` (
  `index` int(11) NOT NULL DEFAULT '0' COMMENT '����',
  `posx` smallint(6) NOT NULL DEFAULT '0' COMMENT 'λ��',
  `posy` smallint(6) NOT NULL DEFAULT '0' COMMENT 'λ��',
  `kind` smallint(6) NOT NULL DEFAULT '0' COMMENT '��Դ����',
  `num` int(11) NOT NULL DEFAULT '0' COMMENT '��Դ��',
  `idlesec` int(11) NOT NULL DEFAULT '0' COMMENT '����ʱ��',
  PRIMARY KEY (`index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

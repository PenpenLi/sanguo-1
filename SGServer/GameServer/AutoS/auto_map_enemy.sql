CREATE TABLE `map_enemy` (
  `index` int(11) NOT NULL DEFAULT '0' COMMENT '����id',
  `posx` smallint(6) NOT NULL DEFAULT '0' COMMENT 'λ��',
  `posy` smallint(6) NOT NULL DEFAULT '0' COMMENT 'λ��',
  `kind` tinyint(3) NOT NULL DEFAULT '0' COMMENT '����',
  PRIMARY KEY (`index`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `nation` (
  `nation` tinyint(3) NOT NULL DEFAULT '0' COMMENT '����',
  `level` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�ȼ�',
  `exp` int(11) NOT NULL DEFAULT '0' COMMENT '����',
  `notice` varbinary(512) NOT NULL DEFAULT '' COMMENT '���ҹ���',
  `official_actorid` varbinary(64) NOT NULL DEFAULT '' COMMENT '��Աid������0�ǹ���',
  PRIMARY KEY (`nation`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

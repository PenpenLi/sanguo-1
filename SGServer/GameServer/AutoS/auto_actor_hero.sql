CREATE TABLE `actor_hero` (
  `id` bigint(20) NOT NULL DEFAULT '0' COMMENT '������',
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '�ǳ�',
  `offset` int(11) NOT NULL DEFAULT '0' COMMENT '����',
  `kind` smallint(6) NOT NULL DEFAULT '0' COMMENT 'Ӣ������',
  `level` smallint(6) NOT NULL DEFAULT '0' COMMENT '�ȼ�',
  `exp` int(11) NOT NULL DEFAULT '0' COMMENT '����',
  `soldiers` int(11) NOT NULL DEFAULT '0' COMMENT '����',
  `attack` smallint(6) NOT NULL DEFAULT '0' COMMENT '��������',
  `defense` smallint(6) NOT NULL DEFAULT '0' COMMENT '��������',
  `troops` smallint(6) NOT NULL DEFAULT '0' COMMENT '��������',
  `growth` smallint(6) NOT NULL DEFAULT '0' COMMENT '������',
  PRIMARY KEY (`id`)
  KEY (`actorid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

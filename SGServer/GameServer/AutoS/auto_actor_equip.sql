CREATE TABLE `actor_equip` (
  `id` bigint(20) NOT NULL DEFAULT '0' COMMENT '������',
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '��ɫID',
  `offset` int(11) NOT NULL DEFAULT '0' COMMENT 'װ�����ڱ���λ��',
  `kind` smallint(6) NOT NULL DEFAULT '0' COMMENT '��Ʒ����',
  `washid0` smallint(6) NOT NULL DEFAULT '0' COMMENT 'ϴ������ID',
  `washid1` smallint(6) NOT NULL DEFAULT '0' COMMENT 'ϴ������ID',
  `washid2` smallint(6) NOT NULL DEFAULT '0' COMMENT 'ϴ������ID',
  `washid3` smallint(6) NOT NULL DEFAULT '0' COMMENT 'ϴ������ID',
  `washid4` smallint(6) NOT NULL DEFAULT '0' COMMENT 'ϴ������ID',
  `washid5` smallint(6) NOT NULL DEFAULT '0' COMMENT 'ϴ������ID',
  PRIMARY KEY (`id`)
  KEY (`actorid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

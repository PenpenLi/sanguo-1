CREATE TABLE `actor_equip` (
  `id` bigint(20) NOT NULL DEFAULT '0' COMMENT '������',
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '��ɫID',
  `offset` int(11) NOT NULL DEFAULT '0' COMMENT 'װ�����ڱ���λ��',
  `kind` smallint(6) NOT NULL DEFAULT '0' COMMENT '��Ʒ����',
  `washid` varbinary(6) NOT NULL DEFAULT '' COMMENT 'ϴ������ID',
  PRIMARY KEY (`id`)
  KEY (`actorid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

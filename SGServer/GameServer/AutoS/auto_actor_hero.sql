CREATE TABLE `actor_hero` (
  `id` bigint(20) NOT NULL DEFAULT '0' COMMENT '������',
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '�ǳ�',
  `offset` int(11) NOT NULL DEFAULT '0' COMMENT '����',
  `kind` smallint(6) NOT NULL DEFAULT '0' COMMENT 'Ӣ������',
  `color` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��ɫ',
  `level` smallint(6) NOT NULL DEFAULT '0' COMMENT '�ȼ�',
  `exp` int(11) NOT NULL DEFAULT '0' COMMENT '����',
  `soldiers` int(11) NOT NULL DEFAULT '0' COMMENT '��ǰ����',
  `attack_wash` smallint(6) NOT NULL DEFAULT '0' COMMENT 'ϴ�蹥������',
  `defense_wash` smallint(6) NOT NULL DEFAULT '0' COMMENT 'ϴ���������',
  `troops_wash` smallint(6) NOT NULL DEFAULT '0' COMMENT 'ϴ���������',
  `colorup` smallint(6) NOT NULL DEFAULT '0' COMMENT '����ͻ��ֵ',
  `god` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�Ƿ���ͻ��',
  PRIMARY KEY (`id`)
  KEY (`actorid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `nation` (
  `nation` tinyint(3) NOT NULL DEFAULT '0' COMMENT '����',
  `level` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�ȼ�',
  `exp` int(11) NOT NULL DEFAULT '0' COMMENT '����',
  `notice` varbinary(512) NOT NULL DEFAULT '' COMMENT '���ҹ���',
  `official_actorid` varbinary(40) NOT NULL DEFAULT '' COMMENT '��Աid������0�ǹ���',
  `tiance_point` int(11) NOT NULL DEFAULT '0' COMMENT '��߸�ͳ�����',
  `tiance_level` tinyint(3) NOT NULL DEFAULT '0' COMMENT '��߸�ͳ��ȼ�',
  `questlevel` varbinary(12) NOT NULL DEFAULT '' COMMENT '��������',
  `questkind` varbinary(12) NOT NULL DEFAULT '' COMMENT '��������',
  `missionlevel` tinyint(3) NOT NULL DEFAULT '0' COMMENT '������������ȼ�',
  `missionvalue` varbinary(16) NOT NULL DEFAULT '' COMMENT '���������������',
  `candidate_actorid` varbinary(40) NOT NULL DEFAULT '' COMMENT '��ѡ��id',
  `candidate_ballot` varbinary(40) NOT NULL DEFAULT '' COMMENT '��ѡ��ѡƱ',
  `paytoken` int(11) NOT NULL DEFAULT '0' COMMENT '�����ܳ�ֵԪ����ȫ��������',
  PRIMARY KEY (`nation`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `actor_friend` (
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '��ɫ���',
  `offset` tinyint(3) NOT NULL DEFAULT '0' COMMENT '����',
  `friend_actorid` int(11) NOT NULL DEFAULT '0' COMMENT '����id',
  `jointime` int(11) NOT NULL DEFAULT '0' COMMENT '����ʱ��',
  PRIMARY KEY (`actorid`)
  KEY (`offset`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

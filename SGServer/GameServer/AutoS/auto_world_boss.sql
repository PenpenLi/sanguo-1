CREATE TABLE `world_boss` (
  `bossid` tinyint(3) NOT NULL DEFAULT '0' COMMENT 'bossid',
  `hp` int(11) NOT NULL DEFAULT '0' COMMENT '��ǰѪ��',
  `maxhp` int(11) NOT NULL DEFAULT '0' COMMENT '��Ѫ��',
  PRIMARY KEY (`bossid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

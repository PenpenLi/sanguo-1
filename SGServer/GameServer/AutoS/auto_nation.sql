CREATE TABLE `nation` (
  `nation` tinyint(3) NOT NULL DEFAULT '0' COMMENT '国家',
  `level` tinyint(3) NOT NULL DEFAULT '0' COMMENT '等级',
  `exp` int(11) NOT NULL DEFAULT '0' COMMENT '经验',
  `notice` varbinary(512) NOT NULL DEFAULT '' COMMENT '国家公告',
  `official_actorid` varbinary(40) NOT NULL DEFAULT '' COMMENT '官员id，索引0是国王',
  `tiance_point` int(11) NOT NULL DEFAULT '0' COMMENT '天策府统领点数',
  `questlevel` varbinary(12) NOT NULL DEFAULT '' COMMENT '国家任务',
  `questkind` varbinary(12) NOT NULL DEFAULT '' COMMENT '国家任务',
  `missionlevel` tinyint(3) NOT NULL DEFAULT '0' COMMENT '国家荣誉任务等级',
  `missionvalue` varbinary(16) NOT NULL DEFAULT '' COMMENT '国家荣誉任务次数',
  PRIMARY KEY (`nation`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

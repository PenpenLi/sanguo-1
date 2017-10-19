CREATE TABLE `map_zone` (
  `zoneid` int(11) NOT NULL DEFAULT '0' COMMENT '地区id',
  `allow` tinyint(3) NOT NULL DEFAULT '0' COMMENT '是否允许',
  `nation` tinyint(3) NOT NULL DEFAULT '0' COMMENT '所属国家',
  PRIMARY KEY (`zoneid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

CREATE TABLE `map_zone` (
  `zoneid` int(11) NOT NULL DEFAULT '0' COMMENT '����id',
  `allow` tinyint(3) NOT NULL DEFAULT '0' COMMENT '�Ƿ�����',
  PRIMARY KEY (`zoneid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

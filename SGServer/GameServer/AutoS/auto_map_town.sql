CREATE TABLE `map_town` (
  `townid` int(11) NOT NULL DEFAULT '0' COMMENT '����id',
  `nation` tinyint(3) NOT NULL DEFAULT '0' COMMENT '����',
  PRIMARY KEY (`townid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

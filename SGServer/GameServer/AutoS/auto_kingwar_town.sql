CREATE TABLE `kingwar_town` (
  `id` int(11) NOT NULL DEFAULT '0' COMMENT 'id',
  `nation` tinyint(3) NOT NULL DEFAULT '0' COMMENT 'ռ���',
  `attack_total` int(11) NOT NULL DEFAULT '0' COMMENT '�������ܱ���',
  `defense_total` int(11) NOT NULL DEFAULT '0' COMMENT '�������ܱ���',
  `sec` int(11) NOT NULL DEFAULT '0' COMMENT 'ս������ʱ',
  PRIMARY KEY (`id`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

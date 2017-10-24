CREATE TABLE `actor` (
  `actorid` int(11) NOT NULL DEFAULT '0' COMMENT '角色编号',
  `userid` bigint(20) NOT NULL DEFAULT '0' COMMENT '账号编号',
  `username` varbinary(51) NOT NULL DEFAULT '' COMMENT '账号名',
  `admin` smallint(6) NOT NULL DEFAULT '0' COMMENT '管理员级别',
  `lastip` varbinary(16) NOT NULL DEFAULT '' COMMENT '上次登陆ip',
  `createtime` int(11) NOT NULL DEFAULT '0' COMMENT '创建时间',
  `forbidtime` int(11) NOT NULL DEFAULT '0' COMMENT '禁言时间',
  `name` varbinary(22) NOT NULL DEFAULT '' COMMENT '角色名称',
  `nation` tinyint(3) NOT NULL DEFAULT '0' COMMENT '角色国家',
  `shape` tinyint(3) NOT NULL DEFAULT '0' COMMENT '形象',
  `level` smallint(6) NOT NULL DEFAULT '0' COMMENT '级别',
  `token` int(11) NOT NULL DEFAULT '0' COMMENT '钻石',
  `total_charge` int(11) NOT NULL DEFAULT '0' COMMENT '总充值',
  `charge_dollar` double NOT NULL DEFAULT '0' COMMENT '总消费多少钱',
  `itemext` tinyint(3) NOT NULL DEFAULT '0' COMMENT '扩展的背包栏位数',
  `equipext` tinyint(3) NOT NULL DEFAULT '0' COMMENT '扩展的装备栏位数',
  `quest_complete` varbinary(8192) NOT NULL DEFAULT '' COMMENT '任务完成情况',
  `worldquest_complete` int(11) NOT NULL DEFAULT '0' COMMENT '世界任务领取情况',
  `sflag` int(11) NOT NULL DEFAULT '0' COMMENT '特定标志位',
  `fdate` int(11) NOT NULL DEFAULT '0' COMMENT '刷新的日子是哪天',
  `today_char` varbinary(512) NOT NULL DEFAULT '' COMMENT 'char类型每日次数',
  `today_int0` int(11) NOT NULL DEFAULT '0' COMMENT 'int类型每日次数',
  `today_int1` int(11) NOT NULL DEFAULT '0' COMMENT 'int类型每日次数',
  `today_int2` int(11) NOT NULL DEFAULT '0' COMMENT 'int类型每日次数',
  `today_int3` int(11) NOT NULL DEFAULT '0' COMMENT 'int类型每日次数',
  `today_int4` int(11) NOT NULL DEFAULT '0' COMMENT 'int类型每日次数',
  `today_int5` int(11) NOT NULL DEFAULT '0' COMMENT 'int类型每日次数',
  `today_int6` int(11) NOT NULL DEFAULT '0' COMMENT 'int类型每日次数',
  `today_int7` int(11) NOT NULL DEFAULT '0' COMMENT 'int类型每日次数',
  `cd0` int(11) NOT NULL DEFAULT '0' COMMENT '通用CD时间',
  `cd1` int(11) NOT NULL DEFAULT '0' COMMENT '通用CD时间',
  `cd2` int(11) NOT NULL DEFAULT '0' COMMENT '通用CD时间',
  `cd3` int(11) NOT NULL DEFAULT '0' COMMENT '通用CD时间',
  `cd4` int(11) NOT NULL DEFAULT '0' COMMENT '通用CD时间',
  `cd5` int(11) NOT NULL DEFAULT '0' COMMENT '通用CD时间',
  `cd6` int(11) NOT NULL DEFAULT '0' COMMENT '通用CD时间',
  `cd7` int(11) NOT NULL DEFAULT '0' COMMENT '通用CD时间',
  `config` varbinary(32) NOT NULL DEFAULT '' COMMENT '玩家配置',
  `function` int(11) NOT NULL DEFAULT '0' COMMENT '功能是否开启',
  `story_chapter` smallint(6) NOT NULL DEFAULT '0' COMMENT '副本进度章节',
  `story_rank` tinyint(3) NOT NULL DEFAULT '0' COMMENT '副本进度关卡',
  `story_state` varbinary(2048) NOT NULL DEFAULT '' COMMENT '副本关卡状态',
  `story_ranknum` varbinary(128) NOT NULL DEFAULT '' COMMENT '副本关卡有次数的存档',
  `story_ranktime` varbinary(128) NOT NULL DEFAULT '' COMMENT '副本关卡有时间的存档',
  `lastpeople_c` int(11) NOT NULL DEFAULT '0' COMMENT '上次本城人口',
  `lastpeople_n` int(11) NOT NULL DEFAULT '0' COMMENT '上次国家人口',
  `cdkey1` int(11) NOT NULL DEFAULT '0' COMMENT '是否领取该批次兑换码',
  `cdkey2` int(11) NOT NULL DEFAULT '0' COMMENT '是否领取该批次兑换码',
  `cdkey3` int(11) NOT NULL DEFAULT '0' COMMENT '是否领取该批次兑换码',
  `cdkey4` int(11) NOT NULL DEFAULT '0' COMMENT '是否领取该批次兑换码',
  PRIMARY KEY (`actorid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

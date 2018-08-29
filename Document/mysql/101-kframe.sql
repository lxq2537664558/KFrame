/*
Navicat MySQL Data Transfer

Source Server         : 192.168.1.9
Source Server Version : 50640
Source Host           : 192.168.1.9:3306
Source Database       : kframe

Target Server Type    : MYSQL
Target Server Version : 50640
File Encoding         : 65001

Date: 2018-08-21 11:55:05
*/

SET FOREIGN_KEY_CHECKS=0;

-- ----------------------------
-- Table structure for `deploy`
-- ----------------------------
DROP TABLE IF EXISTS `deploy`;
CREATE TABLE `deploy` (
  `appid` varchar(50) NOT NULL COMMENT '服务器id',
  `appname` varchar(50) NOT NULL COMMENT '服务器名字',
  `apptype` varchar(50) NOT NULL COMMENT '服务器类型',
  `startup` int(10) unsigned NOT NULL COMMENT '是否已经关闭',
  `shutdown` int(10) NOT NULL DEFAULT '0',
  `process` int(10) unsigned NOT NULL COMMENT '进程id',
  `time` bigint(20) unsigned NOT NULL COMMENT '状态时间( 启动或者关闭 )',
  `agentid` varchar(50) NOT NULL COMMENT '部署agentid',
  `localip` varchar(50) NOT NULL COMMENT '局域网ip',
  PRIMARY KEY (`appid`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of deploy
-- ----------------------------
INSERT INTO `deploy` VALUES ('101.0.11.1', 'data', 'master', '1', '0', '302', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.111.1', 'log', 'master', '1', '0', '317', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.112.1', 'log', 'proxy', '1', '0', '331', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.113.1', 'log', 'shard', '1', '0', '346', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.12.1', 'data', 'proxy', '1', '0', '359', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.121.1', 'dir', 'master', '1', '0', '6734', '1534822214', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.122.1', 'dir', 'proxy', '1', '0', '6744', '1534822214', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.123.1', 'dir', 'shard', '1', '0', '6755', '1534822214', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.13.1', 'data', 'shard', '1', '0', '402', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.21.1', 'public', 'master', '1', '0', '419', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.22.1', 'public', 'proxy', '1', '0', '433', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.23.1', 'public', 'shard', '1', '0', '448', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.31.1', 'route', 'master', '1', '0', '463', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.32.1', 'route', 'proxy', '1', '0', '477', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.33.1', 'route', 'shard', '1', '0', '490', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.4.1', 'auth', 'auth', '1', '0', '2967', '1534820286', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.41.1', 'match', 'master', '1', '0', '514', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.42.1', 'match', 'proxy', '1', '0', '528', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.43.1', 'match', 'shard', '1', '0', '541', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.51.1', 'battle', 'master', '1', '0', '555', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.52.1', 'battle', 'proxy', '1', '0', '567', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.53.1', 'battle', 'shard', '1', '0', '587', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.61.1', 'mail', 'master', '1', '0', '602', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.62.1', 'mail', 'proxy', '1', '0', '615', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.63.1', 'mail', 'shard', '1', '0', '629', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.71.1', 'relation', 'master', '1', '0', '643', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.72.1', 'relation', 'proxy', '1', '0', '656', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.73.1', 'relation', 'shard', '1', '0', '671', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.81.1', 'group', 'master', '1', '0', '687', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.82.1', 'group', 'proxy', '1', '0', '703', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.83.1', 'group', 'shard', '1', '0', '716', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.91.1', 'rank', 'master', '1', '0', '733', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.92.1', 'rank', 'proxy', '1', '0', '762', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.0.93.1', 'rank', 'shard', '1', '0', '780', '1534819748', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.1.241.1', 'zone', 'master', '1', '0', '2212', '1534820055', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.1.242.1', 'zone', 'world', '1', '0', '2224', '1534820055', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.1.243.1', 'zone', 'gate', '1', '0', '2238', '1534820055', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.1.244.1', 'zone', 'login', '1', '0', '2252', '1534820055', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.1.245.1', 'zone', 'game', '1', '0', '2263', '1534820055', '101.0.3.1', '192.168.1.9');
INSERT INTO `deploy` VALUES ('101.3.241.1', 'zone', 'master', '1', '0', '7788', '1534823289', '101.0.3.227', '192.168.10.230');
INSERT INTO `deploy` VALUES ('101.3.242.1', 'zone', 'world', '1', '0', '7798', '1534823289', '101.0.3.227', '192.168.10.230');
INSERT INTO `deploy` VALUES ('101.3.243.1', 'zone', 'gate', '1', '0', '7811', '1534823289', '101.0.3.227', '192.168.10.230');
INSERT INTO `deploy` VALUES ('101.3.244.1', 'zone', 'login', '1', '0', '7822', '1534823289', '101.0.3.227', '192.168.10.230');
INSERT INTO `deploy` VALUES ('101.3.245.1', 'zone', 'game', '1', '0', '7832', '1534823289', '101.0.3.227', '192.168.10.230');

-- ----------------------------
-- Table structure for `launch`
-- ----------------------------
DROP TABLE IF EXISTS `launch`;
CREATE TABLE `launch` (
  `appname` varchar(50) NOT NULL DEFAULT '' COMMENT '进程类名',
  `apptype` varchar(50) NOT NULL DEFAULT '' COMMENT '进程类型',
  `apppath` varchar(50) NOT NULL DEFAULT '' COMMENT '程序目录',
  `appfile` varchar(50) NOT NULL DEFAULT '' COMMENT '进程文件名',
  `appconfig` varchar(100) NOT NULL DEFAULT '' COMMENT '配置路径',
  `logtype` int(10) unsigned NOT NULL DEFAULT '0' COMMENT '日志类型 0 不打日志 1 本地日志  2远程日志',
  `service` varchar(50) NOT NULL DEFAULT '' COMMENT '服务类型  cluster 集群服务  zone 游戏分区',
  `ftpid` int(11) NOT NULL DEFAULT '1' COMMENT 'ftpid',
  `deploypath` varchar(100) NOT NULL DEFAULT '/data/' COMMENT '部署路径',
  PRIMARY KEY (`appname`,`apptype`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of launch
-- ----------------------------
INSERT INTO `launch` VALUES ('auth', 'auth', 'auth', 'authserver', './startup/auth.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('battle', 'master', 'battle', 'battleserver', './startup/battle.master.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('battle', 'proxy', 'battle', 'battleserver', './startup/battle.proxy.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('battle', 'shard', 'battle', 'battleserver', './startup/battle.shard.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('data', 'master', 'data', 'dataserver', './startup/data.master.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('data', 'proxy', 'data', 'dataserver', './startup/data.proxy.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('data', 'shard', 'data', 'dataserver', './startup/data.shard.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('dir', 'master', 'dir', 'dirserver', './startup/dir.master.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('dir', 'proxy', 'dir', 'dirserver', './startup/dir.proxy.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('dir', 'shard', 'dir', 'dirserver', './startup/dir.shard.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('group', 'master', 'group', 'groupserver', './startup/group.master.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('group', 'proxy', 'group', 'groupserver', './startup/group.proxy.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('group', 'shard', 'group', 'groupserver', './startup/group.shard.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('guild', 'master', 'guild', 'guildserver', './startup/guild.master.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('guild', 'proxy', 'guild', 'guildserver', './startup/guild.proxy.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('guild', 'shard', 'guild', 'guildserver', './startup/guild.shard.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('log', 'master', 'log', 'logserver', './startup/log.master.startup', '1', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('log', 'proxy', 'log', 'logserver', './startup/log.proxy.startup', '1', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('log', 'shard', 'log', 'logserver', './startup/log.shard.startup', '1', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('mail', 'master', 'mail', 'mailserver', './startup/mail.master.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('mail', 'proxy', 'mail', 'mailserver', './startup/mail.proxy.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('mail', 'shard', 'mail', 'mailserver', './startup/mail.shard.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('match', 'master', 'match', 'matchserver', './startup/match.master.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('match', 'proxy', 'match', 'matchserver', './startup/match.proxy.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('match', 'shard', 'match', 'matchserver', './startup/match.shard.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('public', 'master', 'public', 'publicserver', './startup/public.master.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('public', 'proxy', 'public', 'publicserver', './startup/public.proxy.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('public', 'shard', 'public', 'publicserver', './startup/public.shard.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('rank', 'master', 'rank', 'rankserver', './startup/rank.master.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('rank', 'proxy', 'rank', 'rankserver', './startup/rank.proxy.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('rank', 'shard', 'rank', 'rankserver', './startup/rank.shard.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('relation', 'master', 'relation', 'relationserver', './startup/relation.master.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('relation', 'proxy', 'relation', 'relationserver', './startup/relation.proxy.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('relation', 'shard', 'relation', 'relationserver', './startup/relation.shard.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('route', 'master', 'route', 'routeserver', './startup/route.master.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('route', 'proxy', 'route', 'routeserver', './startup/route.proxy.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('route', 'shard', 'route', 'routeserver', './startup/route.shard.startup', '2', 'cluster', '1', '../');
INSERT INTO `launch` VALUES ('zone', 'game', 'zone', 'zoneserver', './startup/zone.game.startup', '2', 'zone', '1', '../');
INSERT INTO `launch` VALUES ('zone', 'gate', 'zone', 'zoneserver', './startup/zone.gate.startup', '2', 'zone', '1', '../');
INSERT INTO `launch` VALUES ('zone', 'login', 'zone', 'zoneserver', './startup/zone.login.startup', '2', 'zone', '1', '../');
INSERT INTO `launch` VALUES ('zone', 'master', 'zone', 'zoneserver', './startup/zone.master.startup', '2', 'zone', '1', '../');
INSERT INTO `launch` VALUES ('zone', 'world', 'zone', 'zoneserver', './startup/zone.world.startup', '2', 'zone', '1', '../');

-- ----------------------------
-- Table structure for `machine`
-- ----------------------------
DROP TABLE IF EXISTS `machine`;
CREATE TABLE `machine` (
  `name` varchar(50) NOT NULL DEFAULT '' COMMENT '机器名',
  `localip` varchar(50) NOT NULL DEFAULT '' COMMENT '局域网ip',
  `interanetip` varchar(50) NOT NULL COMMENT '外网ip',
  `cpu` int(10) NOT NULL DEFAULT '8',
  `thread` int(10) NOT NULL DEFAULT '16',
  `memory` int(10) NOT NULL DEFAULT '16',
  `harddisk` int(10) NOT NULL DEFAULT '100',
  `agentid` varchar(50) NOT NULL DEFAULT '0' COMMENT '开启的agentid',
  `status` int(10) NOT NULL DEFAULT '0' COMMENT '状态 0 agent断开连接 1 agent保持连接',
  `port` int(11) NOT NULL DEFAULT '0',
  PRIMARY KEY (`localip`),
  KEY `ip` (`localip`) USING BTREE
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of machine
-- ----------------------------
INSERT INTO `machine` VALUES ('内网测试机', '192.168.1.9', '192.168.1.9', '4', '8', '16', '320', '101.0.3.1', '1', '12052');
INSERT INTO `machine` VALUES ('小兵测试机', '192.168.10.230', '192.168.10.230', '8', '16', '16', '100', '101.0.3.227', '1', '12001');

-- ----------------------------
-- Table structure for `version`
-- ----------------------------
DROP TABLE IF EXISTS `version`;
CREATE TABLE `version` (
  `version_time` datetime NOT NULL,
  `version_name` varchar(128) NOT NULL,
  `version_url` varchar(512) NOT NULL,
  `version_md5` varchar(32) NOT NULL,
  PRIMARY KEY (`version_name`)
) ENGINE=InnoDB DEFAULT CHARSET=utf8;

-- ----------------------------
-- Records of version
-- ----------------------------
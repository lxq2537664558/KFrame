# tcp, http配置启动配置


## HttpServer配置

配置文件位置: `_bin/setting/httpserver.setting`

	<!-- http服务器配置 -->
	<HttpServer KeepAlive="0" MaxThread="4" MaxQueue="64" IdleTime="1000">
		<!-- 认证服务器 -->
		<Server AppName="auth" AppType="auth" Type="1" Port="7776" />
		
		<!-- 目录服务器 -->
		<Server AppName="dir" AppType="shard" Type="1" Port="8000"/>

		<!-- world服务器 -->
		<Server AppName="zone" AppType="world" Type="1" Port="9000"/>	

		<!-- deploy 服务器 -->
		<Server AppName="deploy" AppType="server" Type="0" Port="9999"/>
	</HttpServer>


HttpServer节点的都是默认配置 如KeepAlive, MaxThread等, 如需要差异化,在子节点中添加相应字段即可.

	<Server AppName="auth" AppType="auth" Type="1" Port="7776" />

appname 程序名字

apptype 程序类型

type是端口类型, 0=固定端口 1=由id计算 2=共享内存计算

Port 端口 如果计算端口, 这个端口是计算的起始端口号

## TcpServer配置

配置文件位置: `_bin/setting/tcpserver.setting`	

	<!-- tcp服务器配置 -->
	<TcpServer>
		<!-- 通用服务器 -->
		<Server AppName="*" AppType="*" Type="2" Port="12000" MaxQueue="20000"/>

		<!-- master服务器 -->
		<Server AppName="*" AppType="master" Type="0" Port="0" MaxQueue="20000"/>

		<!-- deploy server 服务器-->
		<Server AppName="deploy" AppType="server" Type="0" Port="0" MaxQueue="20000"/>

		<!-- gate服务器 -->
		<Server AppName="zone" AppType="gate" Type="2" Port="12000" MaxQueue="200" MessageType="2"/>
	</TcpServer>

appname 程序名字 * 表示所有程序

apptype 程序类型 * 表示所有类型
type是端口类型, 0=固定端口 1=由id计算 2=共享内存计算

Port 端口 如果计算端口, 这个端口是计算的起始端口号, 如果为0, 则会去ip.address中查找相应的端口号

MaxQueue 消息队列的最大长度 服务器之间默认20000, 客户端最大200


MessageType 消息类型  1 是服务器之间通讯  2 服务器与客户端之间通讯, 服务器之间消息头会带一些数据,比客户端的消息头要大.




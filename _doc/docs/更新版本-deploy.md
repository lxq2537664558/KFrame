# 更新流程

## 上传资源
	修改Resource目录下的excel表
	点击执行 excel/_build.bat批处理, 把excel转换成config
	svn 上传资源

## Xshell 登录到打包机

### 进入打包目录

    cd /home/server/project/chess/trunk/Server/_build/linux/

![](https://i.imgur.com/xpMgPGe.png)

### 更新资源

    svn up ../../

![](https://i.imgur.com/oBI4Fl4.png)

### 打包版本

    sh make_develop.sh 0

![](https://i.imgur.com/95ITaSJ.png)

## 打开部署工具

### 选择版本 

	选择更新服务器, 点击选择版本, 选择你刚打包好的版本


![](https://i.imgur.com/bLf59uL.png)

### 执行命令
	点击执行命令, 其他设置默认
	部署中控会接受到命令, 并转发给所有agent
	agent接受到命令, 根据命令来执行操作

![](https://i.imgur.com/AQkmlDJ.png)


### 查看日志
	等待日志显示all task finish, 查看左边服务器列表的服务器状态和版本号 是否正确

![](https://i.imgur.com/xDBpAjQ.png)

![](https://i.imgur.com/25WfdzB.png)
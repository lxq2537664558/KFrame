#!/bin/sh

function copyfile()
{
	file1=$path1/$2
	file2=$path2/$2
	
	needcopyfile=0
	if [ ! -f "$file1" ];then
		needcopyfile=0
	elif [ ! -f "$file2" ];then
		needcopyfile=1	
	elif [ $1 == "1" ];then
		filetime1=`stat -c %Y $file1`
        	filetime2=`stat -c %Y $file2`

        	if [ $filetime1 -gt $filetime2 ];then
                	needcopyfile=1
        	fi
	fi
	
	if [ $needcopyfile == 1 ];then
		echo "copy $file1 $file2"
		cp -f $file1 $file2
	fi
}

binpath=../../_bin/linux
respath=../../../Resource
settingpath=../../_bin/setting
deploypath=/data/upload

mkdir -p $deploypath
mkdir -p $deploypath/setting
mkdir -p $deploypath/plugin
mkdir -p $deploypath/config

#setting
path1=$settingpath
path2=$deploypath/setting
copyfile 1 ip.address
copyfile 1 ftp.address
copyfile 1 server.network
copyfile 1 initapp.log4cxx
copyfile 1 templateapp.log4cxx


path1=$settingpath/deploy
path2=$deploypath/setting
copyfile 1 upload.startup
copyfile 1 upload.config

#config
path1=$respath/config
path2=$deploypath/config

#plugin
path1=$binpath
path2=$deploypath
copyfile 1 KFStartup
copyfile 1 KFStartupd

cp -f $deploypath/KFStartup $deploypath/uploadserver
cp -f $deploypath/KFStartupd $deploypath/uploadserverd

path2=$deploypath/plugin
copyfile 1 KFIpAddress.so
copyfile 1 KFIpAddressd.so
copyfile 1 KFHttpClient.so
copyfile 1 KFHttpClientd.so
copyfile 1 KFHttpServer.so
copyfile 1 KFHttpServerd.so
copyfile 1 KFConfig.so
copyfile 1 KFConfigd.so
copyfile 1 KFDeployUpload.so
copyfile 1 KFDeployUploadd.so
copyfile 1 KFFtp.so
copyfile 1 KFFtpd.so
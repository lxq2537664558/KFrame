
basepath=$(cd `dirname $0`; pwd)
cd /data/mailcluster

if [ "$1" = "debug" ]; then
server=mailserverd
else
server=mailserver
fi

echo Starting Mail Cluster Server
./$server 0 6 ./setting/master.startup

echo Starting Mail Proxy Server
./$server 0 6001 ./setting/proxy.startup
./$server 0 6002 ./setting/proxy.startup

echo Starting Mail Shard Server
./$server 0 6101 ./setting/shard.startup
./$server 0 6102 ./setting/shard.startup
./$server 0 6103 ./setting/shard.startup
./$server 0 6104 ./setting/shard.startup

cd $basepath

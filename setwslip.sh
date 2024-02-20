env wslip=`ip addr | grep 'inet.*eth' | sed 's/.*inet //' | sed 's/\/.*//'`
sed -r 's/172\.([0-9]{1,3}\.){3}/"$wslip"/g' /mnt/c/Users/cryoon/AppData/Roaming/ParaView/servers.pvsc > testip

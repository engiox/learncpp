#!/bin/bash

MY_IP=$(hostname -I | awk '{print $1}')

FILE_NAME="/mnt/c/Users/cryoon/AppData/Roaming/ParaView/servers.pvsc"

sed -ri 's/172\.([0-9]{1,3}\.){2}[0-9]{1,3}/'"$MY_IP"'/g' $FILE_NAME

program_name=pvserver
pgrep -x $program_name > /dev/null

if [ $? -eq 0 ]; then
        echo "$program_name 프로그램이 실행 중입니다."
    else
        echo "$program_name 프로그램을 실행합니다."
        pvserver -display localhost:0
fi

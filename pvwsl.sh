#!/bin/bash

# 현재 컴퓨터의 IP 주소를 가져옵니다.
MY_IP=$(hostname -I | awk '{print $1}')

# 변경하려는 파일의 이름입니다.
FILE_NAME="/mnt/c/Users/x/AppData/Roaming/ParaView/servers.pvsc"

# 파일 내의 172로 시작하는 모든 IP 주소를 현재 컴퓨터의 IP 주소로 변경합니다.
sed -ri 's/192\.([0-9]{1,3}\.){2}[0-9]{1,3}/'"$MY_IP"'/g' $FILE_NAME

# pgrep 명령어를 사용하여 프로세스 검색
program_name="pvserver"
pgrep -x $program_name  > /dev/null

# 프로세스가 실행 중인지 확인합니다.
if [ $? -eq 0 ]; then
        echo "$program_name 프로그램이 실행 중입니다."
    else
        echo "$program_name 프로그램을 실행합니다."
        pvserver -display localhost:0
fi

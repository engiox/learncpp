#!/bin/bash

# 현재 컴퓨터의 IP 주소를 가져옵니다.
MY_IP=$(hostname -I | awk '{print $1}')

# 변경하려는 파일의 이름입니다.
FILE_NAME="/mnt/c/Users/cryoon/AppData/Roaming/ParaView/servers.pvsc"

# 파일 내의 172로 시작하는 모든 IP 주소를 현재 컴퓨터의 IP 주소로 변경합니다.
sed -ri 's/172\.([0-9]{1,3}\.){2}[0-9]{1,3}/'"$MY_IP"'/g' $FILE_NAME

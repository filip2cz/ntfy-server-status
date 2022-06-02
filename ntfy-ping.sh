#!/bin/bash

#config:
servername="myserver"
serverip="8.8.8.8"
ntfytopic="mytopic"

status=0
while (($status == 0))
do
   if ! [ "`ping -c 1 $serverip`" ]; then
        if (($status == 1)); then
            echo $servername ($serverip) is offline.
            status=0
            curl -d "$servername ($serverip) is offline." ntfy.sh/$ntfytopic
        fi
   else
        if (($status == 0)); then
            echo $servername ($serverip) is online.
            status=1
            curl -d "$servername ($serverip) is online." ntfy.sh/$ntfytopic
        fi
   fi
   sleep 30
done

# created by filip2cz
# github: https://github.com/filip2cz/ntfy-ping
#!/bin/bash

#config:
servername="myserver"
serverip="8.8.8.8"
ntfytopic="komarekf-test"
debug=0

#script
status=0
while :
do
    if (($debug == 1)); then
            echo "new ping test"
            echo $status
            echo
    fi
    if ! [ "`ping -c 1 $serverip`" ]; then
        if (($debug == 1)); then
            echo "ping failed"
            echo $status
            echo
        fi
        if (($status == 1)); then
            echo "$servername ($serverip) is offline."
            status=0
            curl -d "$servername ($serverip) is offline." ntfy.sh/$ntfytopic
        fi
    else
        if (($debug == 1)); then
            echo "ping done"
            echo $status
            echo
        fi
        if (($status == 0)); then
            echo "$servername ($serverip) is online."
            status=1
            curl -d "$servername ($serverip) is online." ntfy.sh/$ntfytopic
        fi
    fi
    sleep 5
done

# created by filip2cz
# github: https://github.com/filip2cz/ntfy-ping
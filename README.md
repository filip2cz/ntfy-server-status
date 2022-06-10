# NTFY server status reporting
This reporting through ntfy.sh, if your server is online or offline.

## How it works?
There are 2 versions that differ depending on who controls who. In the server-reporting version, the guest connects to the port from time to time and sends a "1". The server expects this, and if it doesn't, after a few tries it sends the status via ntfy.sh. If the server reports again, it will send another report about the new server state. In the host-report version the roles are swapped, this is useful if you want to check a machine that you can't have an open port on.

## Compilation
The current version has 2 parts, part written in C and part in bash script. The bash script has all the configuration. The C part comes precompiled for Linux x86_64, however it can be compiled using the "gcc -o net net.c" command.

## Current issues and bugs
1) NetCat version is printing syntax error on line 21 when the connection is not established, but it is still working :)
2) Server-reporting version is littlebit broken (It works, but has a low connection success rate. This can be solved by a large number of attempts before reporting). It is possible to use the old netcat version that uses netcat.

## Other info
I am not the full author of that c part, I only forked it.
I plan to do the whole thing in C.

## Old versions
There are several old versions. The oldest is the ping version, which doesn't require a client host or open port, but you need to have a direct ip address to the controlled server (not a router address or anything).
Then there is the netcat version, which works fine, but in some cases the server-reporting version doesn't work, I found this problem in some Linux distributions, it worked in some, however it was replaced.

## What I forked:
1) C part in host-reporting and server-reporting. It's from a friend of mine who doesn't have the code on github, but he agreed to use it and the original code as I got it from him is here: https://github.com/filip2cz/ntfy-server-status/blob/main/forked%20files/net.c
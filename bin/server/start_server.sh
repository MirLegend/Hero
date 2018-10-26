#!/bin/sh

sh ./kill_server.sh

./logger --cid=9000 --gus=11&
./login --cid=9001 --gus=11&
./dbmgr --cid=9002 --gus=11&
./cellmgr --cid=9003 --gus=11&
./basemgr --cid=9004 --gus=11&
./baseapp --cid=9005 --gus=11&
./cellapp --cid=9006 --gus=11&

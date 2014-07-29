#!/bin/bash
. env.sh # load env

if [ $# != 1 ]; then
	echo Usage $0 deliveryid
	exit 1
fi

DELIVERYID=$1

curl -i -u $APPID:$APIKEY $HOST/smscenter/v1.0/result/$DELIVERYID 

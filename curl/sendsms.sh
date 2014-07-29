#!/bin/bash

SENDER=01000000000 # FIXME MUST BE CHANGED AS REAL PHONE NUMBER
RECEIVER=01000000000 # FIXME MUST BE CHANGED AS REAL PHONE NUMBER

. env.sh # load env

curl -i -u $APPID:$APIKEY \
     -X POST $HOST/smscenter/v1.0/sendsms \
     -H "Content-Type: application/json;charset=utf-8" \
     -d '{"sender": "'$SENDER'", "receivers": ["'$RECEIVER'"], "content": "나는 유리를 먹을 수 있어요. 그래도 아프지 않아요"}'

#!/usr/bin/env python
# -*- coding: utf-8 -*-
import json
import requests
import sys
from conf import appid, apikey, sender, receivers, content

if len(sys.argv) == 1:
    print 'Usage:\n python %s deliveryid' % sys.argv[0]
    sys.exit(1)

deliveryid = sys.argv[1]

url = 'https://api.bluehouselab.com/smscenter/v1.0/result/'+deliveryid
params = {
    'sender'     : sender,
    'receivers'  : receivers,
    'content'    : content,
}
headers = {'Content-type': 'application/json; charset=utf-8',}
r = requests.get(url, auth=(appid, apikey), headers=headers)

print r.status_code, r.reason
if r.status_code == 200:
    print r.json()

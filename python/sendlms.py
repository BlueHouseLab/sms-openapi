#!/usr/bin/env python
# -*- coding: utf-8 -*-
import httplib
import json
from conf import address, sender, receivers, headers, content

c = httplib.HTTPSConnection(address)

path = "/smscenter/v1.0/sendlms"
value = {
    'sender'     : sender,
    'receivers'  : receivers,
    'subject'  :  u'LMS 제목',
    'content'    : content,
}
data = json.dumps(value, ensure_ascii=False).encode('utf-8')

c.request("POST", path, data, headers)
r = c.getresponse()

print r.status, r.reason
print r.read()

#!/usr/bin/env python
# -*- coding: utf-8 -*-
import httplib
import json
from conf import address, sender, receivers, headers, content
import datetime

# about 1 minute later
about1m = datetime.datetime.utcnow() + datetime.timedelta(seconds=65)
print 'send sms at '+about1m.isoformat()+' (UTC)'

c = httplib.HTTPSConnection(address)


path = "/smscenter/v1.0/sendsms"
value = {
    'sender'      : sender,
    'receivers'   : receivers,
    'content'     : content,
    'reservation' : about1m.isoformat()
}
data = json.dumps(value, ensure_ascii=False).encode('utf-8')

c.request("POST", path, data, headers)
r = c.getresponse()

print r.status, r.reason
print r.read()

# -*- coding: utf-8 -*-
import httplib
import json
import sys

from conf import address, sender, receivers, headers, content

c = httplib.HTTPSConnection(address)

if len(sys.argv) == 1:
    print 'Usage:\n python %s groupid' % sys.argv[0]
    sys.exit(1)

groupid = sys.argv[1]
path = "/smscenter/v1.0b/result/group/"+groupid

c.request("GET", path, '', headers)
r = c.getresponse()

print r.status, r.reason
print r.read()

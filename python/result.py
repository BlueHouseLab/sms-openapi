#!/usr/bin/env python
# -*- coding: utf-8 -*-
import httplib
import json
import sys

from conf import address, sender, receivers, headers, content

c = httplib.HTTPSConnection(address)

if len(sys.argv) == 1:
    print 'Usage:\n python %s deliveryid' % sys.argv[0]
    sys.exit(1)

deliveryid = sys.argv[1]
path = "/smscenter/v1.0/result/"+deliveryid

c.request("GET", path, '', headers)
r = c.getresponse()

print r.status, r.reason
print r.read()

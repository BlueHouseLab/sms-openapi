#!/usr/bin/env python
# -*- coding: utf-8 -*-
import httplib
import json
import sys

from conf import address, sender, receivers, headers, content

c = httplib.HTTPSConnection(address)

path = "/smscenter/v1.0/rejectednumbers"
c.request("POST", path, '', headers)
r = c.getresponse()

print r.status, r.reason
print r.read()

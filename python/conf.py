# -*- coding: utf-8 -*-
import base64

appid = 'example'
apikey = 'c5dd7e7dkjp27377l903c42c032b413b'
address = 'api.bluehouselab.com'

sender = '01000000000'        # FIXME - MUST BE CHANGED AS REAL PHONE NUMBER
receivers = ['01000000000', ] # FIXME - MUST BE CHANGED AS REAL PHONE NUMBERS
content = u'나는 유리를 먹을 수 있어요. 그래도 아프지 않아요'

credential = "Basic "+base64.encodestring(appid+':'+apikey).strip()
headers = {
  "Content-type": "application/json;charset=utf-8",
  "Authorization": credential,
}

print "Warnings: python httplib doesn't verify SSL certificate."
print "          python-requests module is recommended for secured API call"

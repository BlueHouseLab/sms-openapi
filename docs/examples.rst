.. module:: examples

Sample Codes
============

청기와랩의 SMS OpenAPI 샘플 코드들은 GitHub (https://github.com/bluehouselab/sms-openapi) 에서 다운 받으실 수 있습니다.

Git를 이용한 샘플코드 프로젝트 체크아웃:

.. code-block:: bash

    $ git clone https://github.com/BlueHouseLab/sms-openapi.git

또는 샘플코드 Zip 아카이브 파일 다운 받기:

.. code-block:: bash

    $ wget https://github.com/BlueHouseLab/sms-openapi/archive/master.zip

cURL
----

`curl <http://curl.haxx.se>`_ 은 많은 Unix 기반 Platform에 기본으로 탑재된 command line http client 입니다. 각종 Linux 배포판, BSD 배포판 및 Mac OS X에서 테스트 용도로 활용 가능 합니다.

`env.sh <https://github.com/BlueHouseLab/sms-openapi/blob/master/curl/env.sh>`_ - 발급 받은 appid, apikey 및 수발신 번호를 설정해 주세요.

.. literalinclude:: ../curl/env.sh
   :language: bash
   :lines: 1-4

`sendsms.sh <https://github.com/BlueHouseLab/sms-openapi/blob/master/curl/sendsms.sh>`_ - sms 발송

.. literalinclude:: ../curl/sendsms.sh
   :language: bash

실행 예 

.. code-block:: bash

    $ ./sendsms.sh 
    HTTP/1.0 200 OK
    Date: Thu, 03 Jul 2014 17:15:16 GMT
    Content-Type: application/json; charset=utf-8

    {"filtered": [], "reserved": null, "sent": [["01000000000", "201407040215163682530"]]}

`result.sh <https://github.com/BlueHouseLab/sms-openapi/blob/master/curl/result.sh>`_ - 발송 확인 예제, sendsms.sh 의 결과로 받은 발송ID를 인자로 주어야 함

.. literalinclude:: ../curl/result.sh
   :language: bash

실행 예 

.. code-block:: bash

    $ ./result.sh 201407040215163682530
    HTTP/1.0 200 OK
    Date: Thu, 03 Jul 2014 17:20:55 GMT
    Content-Type: application/json; charset=utf-8

    {"status": "0", "destination": "01000000000", "sent_time": "2014-07-03T17:15:20Z"}

Python
------

Python 예제는 Standard Library인 `httplib <https://docs.python.org/2/library/httplib.html>`_ 모듈을 이용하여 작성 되었습니다. `httplib <https://docs.python.org/2/library/httplib.html>`_ 모듈은 SSL Certificate Verification 과정이 생략된 HTTP Client 모듈 이므로 개발 참고용으로만 사용하세요. 실제 개발에는 보안을 위해 `Requests <http://docs.python-requests.org/en/latest/>`_ 모듈을 추천 합니다.


`conf.py <https://github.com/BlueHouseLab/sms-openapi/blob/master/python/conf.py>`_ - 발급 받은 appid, apikey 및 수발신 번호를 설정해 주세요.

.. literalinclude:: ../python/conf.py
   :language: python
   :emphasize-lines: 3-
   :lines: 1-16

`sendsms.py <https://github.com/BlueHouseLab/sms-openapi/blob/master/python/sendsms.py>`_ - sms 발송

.. literalinclude:: ../python/sendsms.py
   :language: python
   :emphasize-lines: 6-18

실행 예 

.. code-block:: bash

    $ python sendsms.py 
    200 OK
    {"filtered": [], "reserved": null, "sent": [["01000000000", "201407040043284939320"]]}


`result.py <https://github.com/BlueHouseLab/sms-openapi/blob/master/python/result.py>`_ - 발송 확인 예제, sendsms.py 의 결과로 받은 발송ID를 인자로 주어야 함

.. literalinclude:: ../python/result.py
   :language: python
   :emphasize-lines: 8, 14-18

실행 예 

.. code-block:: bash

    $ python result.py 201407040043284939320
    200 OK
    {"status": "0", "destination": "01000000000", "sent_time": "2014-07-03T15:43:31Z"}


Python (Requests)
-----------------

`Requests <http://docs.python-requests.org/en/latest/>`_ 모듈을 이용한 더 안전하고 Human을 위한 예제 구현 입니다.

`sendsms.py <https://github.com/BlueHouseLab/sms-openapi/blob/master/python/sendsms.py>`_ - sms 발송

.. literalinclude:: ../python-requests/sendsms.py
   :language: python

실행 예 

.. code-block:: bash

    $ python sendsms.py 
    200 OK
    {"filtered": [], "reserved": null, "sent": [["01000000000", "201407040043284939320"]]}


`result.py <https://github.com/BlueHouseLab/sms-openapi/blob/master/python/result.py>`_ - 발송 확인 예제, sendsms.py 의 결과로 받은 발송ID를 인자로 주어야 함

.. literalinclude:: ../python-requests/result.py
   :language: python

실행 예 

.. code-block:: bash

    $ python result.py 201407040043284939320
    200 OK
    {"status": "0", "destination": "01000000000", "sent_time": "2014-07-03T15:43:31Z"}


Ruby
----

`sendsms.rb <https://github.com/BlueHouseLab/sms-openapi/blob/master/ruby/sendsms.rb>`_ - sms 발송

.. literalinclude:: ../ruby/sendsms.rb
   :language: ruby
   :emphasize-lines: 8-19

실행 예 

.. code-block:: bash

    $ ruby sendsms.rb
    200
    {"filtered": [], "reserved": null, "sent": [["01000000000", "201407201409478863550"]]]}

`result.rb <https://github.com/BlueHouseLab/sms-openapi/blob/master/ruby/result.rb>`_ - 발송 확인 예제, sendsms.rb 의 결과로 받은 발송ID를 인자로 주어야 함

.. literalinclude:: ../ruby/result.rb
   :language: ruby
   :emphasize-lines: 13-18

실행 예 

.. code-block:: bash

    $ ./result.rb 201407201409478863550
    200
    {"status": "0", "destination": "01000000000", "sent_time": "2014-07-20T05:09:51Z"}



PHP
---

`sendsms.php <https://github.com/BlueHouseLab/sms-openapi/blob/master/php/sendsms.php>`_ - sms 발송

.. literalinclude:: ../php/sendsms.php
   :language: xml+php

실행 예 

.. code-block:: bash

    $ php sendsms.php
    200
    Array
    (
        [filtered] => Array
            (
            )
        [reserved] => 
        [sent] => Array
            (
                [0] => Array
                    (
                        [0] => 01000000000
                        [1] => 201408010307369291320
                    )
            )
    )


`result.php <https://github.com/BlueHouseLab/sms-openapi/blob/master/php/result.php>`_ - 발송 확인 예제, sendsms.php 의 결과로 받은 발송ID를 인자로 주어야 함

.. literalinclude:: ../php/result.php
   :language: xml+php

실행 예 

.. code-block:: bash

    $ php result.php 201408010307369291320
    200
    Array
    (
        [status] => 0
        [destination] => 01000000000
        [sent_time] => 2014-07-31T18:07:38Z
    )


Javascript (Node.js)
--------------------

`sendsms.js <https://github.com/BlueHouseLab/sms-openapi/blob/master/node.js/sendsms.js>`_ - sms 발송

.. literalinclude:: ../node.js/sendsms.js
   :language: javascript

실행 예 

.. code-block:: bash

    $ node sendsms.js 
    200
    { filtered: [],
      reserved: null,
      sent: [ [ '01000000000', '201408021612156351310' ] ] }


`result.js <https://github.com/BlueHouseLab/sms-openapi/blob/master/node.js/result.js>`_ - 발송 확인 예제, sendsms.js 의 결과로 받은 발송ID를 인자로 주어야 함

.. literalinclude:: ../node.js/result.js
   :language: javascript

실행 예 

.. code-block:: bash

    $ node result.js 201408021612156351310
    200
    { status: '10001',
      destination: '01000000000',
      sent_time: '2014-08-01T18:14:35Z' }

Java (Android)
--------------

Java 예제는 Apache 프로젝트의 `Http Component <http://hc.apache.org>`_ 를 사용하여 작성 하였 습니다. Mac, Linux, Windows 등의 일반적인 Java 개발 환경 뿐만 아니라, Apache Http Component가 기본 탑재 되어 있는 Android (API level 1) 에도 적용 가능한 샘플 입니다.

빌드 (Linux/Mac/Windows) - GNU make 명령을 이용하여 Java 코드들을 컴파일 합니다. `Makefile <https://github.com/BlueHouseLab/sms-openapi/blob/master/java/Makefile>`_ 을 참고 하세요.

.. code-block:: bash

    $ make

`Sendsms.java <https://github.com/BlueHouseLab/sms-openapi/blob/master/java/SendSMS.java>`_ - sms 발송

.. literalinclude:: ../java/SendSMS.java
   :language: java
   :lines: 17-

실행 예 

.. code-block:: bash

    $ ./sendsms # bash shell script to execute java with require params
    200
    {"filtered": [], "reserved": null, "sent": [["01000000000", "201408030412368846800"]]}


`Result.java <https://github.com/BlueHouseLab/sms-openapi/blob/master/java/Result.java>`_ - 발송 확인 예제, SendSMS.java 의 결과로 받은 발송ID를 인자로 주어야 함

.. literalinclude:: ../java/Result.java
   :language: java
   :lines: 15-

실행 예 

.. code-block:: bash

    $ ./result 201408030412368846800 # bash shell script to execute java
    200
    {"status": 0, "destination": "01000000000", "sent_time": "2014-08-02T19:12:35Z"}

C (libcurl)
-----------

C 예제는 `libcurl <http://curl.haxx.se>`_ 라이브러리를 HTTP Client 로 사용하였습니다. libcurl은 Linux/BSD/Win32 환경에서 가장 많이 사용되는 통신 모듈 중 하나로 이식성이 우수 하며 여러 프로젝트에서 사용되어 안정성 및 그 우수성을 인정 받고 있는 오픈 소스 라이브러리 입니다. 

빌드 (Linux/Mac/Windows) - GNU make 및 pkg-config 명령을 이용하여 빌드 합니다. Windows 환경에서는 `cygwin <http://www.cygwin.com>`_ 또는 `msys <http://www.mingw.org/wiki/msys>`_ 환경에서 쉽게 빌드 하실 수 있습니다.

.. code-block:: bash

    $ make
    cc -Wall -O2 -o sendsms.o -c sendsms.c `pkg-config --cflags libcurl`
    cc -o sendsms sendsms.o `pkg-config --libs libcurl`
    cc -Wall -O2 -o result.o -c result.c `pkg-config --cflags libcurl`
    cc -o result result.o `pkg-config --libs libcurl`

`sendsms.c <https://github.com/BlueHouseLab/sms-openapi/blob/master/c-curl/sendsms.c>`_ - sms 발송

.. literalinclude:: ../c-curl/sendsms.c
   :language: c

실행 예 

.. code-block:: bash

    $ ./sendsms
    200
    {"filtered": [], "reserved": null, "sent": [["01000000000", "201408030412368846800"]]}


`result.c <https://github.com/BlueHouseLab/sms-openapi/blob/master/c-curl/result.c>`_ - 발송 확인 예제, sendsms.c 의 결과로 받은 발송ID를 인자로 주어야 함

.. literalinclude:: ../c-curl/result.c
   :language: c

실행 예 

.. code-block:: bash

    $ ./result 201408030412368846800
    200
    {"status": 0, "destination": "01000000000", "sent_time": "2014-08-02T19:12:35Z"}


C++ (Qt5)
-----------

.. code-block:: c++

Obj-C
-----------

.. code-block:: objective-c++

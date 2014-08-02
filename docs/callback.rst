.. module:: callback


Callback API
============

Callback API는 청기와랩의 Callback Gateway를 통해 고객의 웹서버로 실시간 정보 전달하기 위해 정의된 Open API입니다.

발송 결과 Callback
------------------

callback 값을 URL로 입력하면 전송 결과를 일정 시간 뒤 해당 URL로 보내줍니다. (발송 량과 상황에 따라 callback URL이 호출되는 시간은 발송 후 30초에서 최대 48시간 까지 소요될 수 있음) 

Callback Request Header:

============  ================================
HTTP Header   Value
============  ================================
Method        Post
URI Path      your callback URI
Content-Type  application/json; charset=utf-8
============  ================================

Callback Request Data Format (JSON): 

=============  ===========================   =========  ======
Key            Value                         Format     비고
=============  ===========================   =========  ======
succeed        ["10001", "10002", ]          List       필수
failed         ["10003", "10004", ]          List       옵션
pending        ["10005", "10006", ]          List       옵션
=============  ===========================   =========  ======

succeed, failed, pending 은 각각 성공된 발송ID 리스트, 실패한 발송ID리스트, 아직 성공여부가 확인 되지 않은 발송ID리스트 입니다. pending의 경우, 수신자가 응영지역에 있거나, 전원이 꺼져있는 등의 이유로 48시간 이내에 전달이 안된 경우 입니다. 이 경우 48시간 이내에 수신자가 수신가능 상태가 될경우 전송이 재개되어 추후 succeed로 처리 되어 48시간 후 다시 callback URL로 succeed 상태로 report 될 수 있습니다. 또는 48시간이 경과 했음에도 전송이 되지 못했다면 48시간 후에 다시 callback URL로 failed 상태로 report 될 수 있습니다.

080 수신거부 Callback
---------------------

한국의 정보통신망법 스팸 규제 법률에 따라 영리 목적으로 발송하는 매체에 080 수신자부담 전화 서비스를 통한 수신거부처리 서비스를 반드시 제공해야 합니다. 이를 위해 청기와랩은 수신거부 Callback 서비스를 제공합니다. 청기와랩의 080 수신거부 서비스를 통해 접수된 전화번호를 등록한 Callback URL로 실시간 전달 받으실 수 있습니다.

Callback Request Header:

============  ====================================
HTTP Header   Value
============  ====================================
Method        Post
URI Path      your callback URI for 080 Rejection
Content-Type  application/json; charset=utf-8
============  ====================================

Callback Request Data Format (JSON): 

==============  ===========================   =========  ======
Key             Value                         Format     비고
==============  ===========================   =========  ======
rejected        ["0101112222",]               List       필수
==============  ===========================   =========  ======


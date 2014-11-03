.. module:: restful

RESTful API
===========

HTTP Common Header
------------------

클라이언트는 HTTP Request 시 Header에 아래 표의 Key와 Value를 설정해야 합니다..

예제:

=============  =======================================  =====
Key            Value                                    비고
=============  =======================================  =====
Authorization  Basic Zm9vYmFyLXdlYnNpdGU6MTIzNDU2Nzg=   필수
=============  =======================================  =====

.. note::
    Authorization에 들어가는 HTTP Basic Auth (RFC-2617) 값은 Authorization_ 를 참조하십시오.

.. note::
    Authorization 정보가 없으면 HTTP Status Code로 401 Authorization Required 에러를 리턴 받습니다.



.. _Authorization:

Authorization
--------------

청기와랩의 SMS Open API는 HTTP 표준 Basic Auth 을 사용하여 인증 합니다. HTTP Basic Auth는 Username과 Password를 조합한 후 Base64로 인코딩한 값을 HTTP Header에 설정하여 보냅니다. 여기서는 App Id가 Username으로 사용되며 API Key가 Password로 사용됩니다.

가령 App Id가 foobar-website 이고 API Key가 12345678 이라고 하면 "foobar-website:12345678"을 Base64로 인코딩한 값을 사용하여 HTTP Header에 설정 하면 됩니다.

::

    인증문자열 (Base64 Encoding 전)
    Basic foobar-website:12345678

    Base64 적용 후 인증 문자열
    Basic Zm9vYmFyLXdlYnNpdGU6MTIzNDU2Nzg=

    HTTP Header 에 들어간 완전한 인증 문자열
    Authorization: Basic Zm9vYmFyLXdlYnNpdGU6MTIzNDU2Nzg=


HTTP Status Code
----------------

클라이언트가 API서버로 부터 받을 수 있는 HTTP Status Code 목록

=============  ======================================
Status Code    Description
=============  ======================================
200            OK, 성공
204            No Content, 성공 (Response Data 가 없는 경우)
400            Bad Request, 입력 데이타 잘못된 경우
401            Unauthorized, API Key 인증 실패
402            Payment Required, Credit 또는 Point 부족, Credit 충전 필요
403            Forbidden, 접근 불가, HTTPS를 통한 연결이 아니거나 인증 실패
404            Not found, delivery id 등의 resource가 존재하지 않는 경우
406            Not Acceptable, JSON 파싱 실패 등
410            Gone, API deprecated
412            Precondition Failed, 입력 값에 문제 있음
500            Internal Server Error, 내부 서버 오류
503            Service Unavailable, 내부 서버 오류
=============  ======================================


메시지 발송 (SMS)
------------------

HTTP Request Header:

============  ================================
HTTP Header   Value
============  ================================
Method        Post
URI Path      /smscenter/v1.0/sendsms
Content-Type  application/json; charset=utf-8
============  ================================

Request Data Format (JSON): 

=====================  ====================================   ==================  ======
Key                    Value                                  Format              비고
=====================  ====================================   ==================  ======
sender                 "0212341234"                           String              필수
receivers              ["01011111111", "01011112222",]        List                필수
content                "주문하신 제품이 발송 되었습니다."     String (UTF-8)      필수
reservation            "2014-06-12T16:01:45.923Z"             UTC Date (ISO8601)  옵션
blockrejectednumbers   true                                   Boolean             옵션 (기본값 true)
=====================  ====================================   ==================  ======

.. note::

   한국의 SMS망 표준에 의거하여 EUC-KR 인코딩 기준으로 80바이트 길이 제한이 있습니다. EUC-KR 인코딩 기준 문자열 길이는 ASCII는 1바이트, 한글 및 특수 문자는 2바이트로 계산 됩니다.  EUC-KR 인코딩 기준 80바이트가 넘어갈 경우 자동으로 문자열이 80바이트에 맞춰 잘라져서 발송 됩니다. 장문의 메시지를 보내고자 할경우 LMS (장문 문자)로 발송 하십시오.
   
.. note::

   청기와랩의 Open API는 ECMA-262 표준에 따라 JSON 표기시 Unicode 인코딩 (\uHHHH) 또는 UTF-8인코딩으로 문자열을 처리하는 것이 기본 원칙 입니다. UTF-8 인코딩의 경우 한 글자가 1~6바이트 까지 차지할 수 있는 가변길이 문자열 인코딩 이나 Server에서 SMS 문자열 계산시에는 EUC-KR로 변환 한 후 문자열 길이를 체크 하여 발송 합니다.

.. note::

   EUC-KR 인코딩에서 지원하지 않는 문자의 경우 '?'로 대치 됩니다. 예) '똠', '뷁'

.. note::

   예약 전송 옵션 사용시 reservation 값으로 JavaScript의 Date 표기법인 ISO 8601 형식의 UTC기준 시간을 기술 하십시오. 과거 또는 1분 미만의 미래 시간은 예약으로 간주되지 않습니다. 

.. note::

   발송후 등록하신 callback URL로 발송 결과를 보내줍니다.  `발송 결과 Callback`_ 을 참고하세요.

.. note::

   blockrejectednumbers은 기본값이 true이고 Optional한 인자 입니다. 발송시 080 수신자 부담 수신거부 시스템에 등록되어 있는 번호이면 SMS가 발송되지 않습니다. 만약 blockrejectednumbers를 false로 설정하여 발송 시 080 수신자 부담 수신거부 시스템에 등록된 전화번호를 체크하지 않고 그대로 발송 되므로 주의하여 사용하세요. 

.. note::

   수신자가 2명 이상일 경우 groupid가 같이 리턴됩니다. groupid를 이용하여 전송 결과를 한꺼번에 받아 오실 수 있습니다.


Example::

  {sender: "01011112222", receivers: ["01011111111",], content: "주문 취소건 발생"}


.. _SMS발송결과:

HTTP Response Header:

=============  ======================================
HTTP Header    Value
=============  ======================================
Status         200
Content-Type   application/json; charset=utf-8
=============  ======================================

Response Data Format (JSON): 

=============  ===================================   =================  ========
Key            Value                                 Format             비고
=============  ===================================   =================  ========
sent           [["01011111111", "10001"], ]          List               [수신번호,발송ID]의 리스트
filtered       ["01011111113", ]                     List               수신 거부 번호들
reserved       187c4b7affa011e3bf47c42c032b413b      String             예약ID
groupid        09e9a0680ea111e49044c42c032b413b      String (Optional)  그룹ID
=============  ===================================   =================  ========

Example::

  {result: [["01011111111", 20001], ["01011111112", 20002], ], filtered: [], reserved: null}

메시지 발송 (LMS)
-----------------

HTTP Request Header:

============  ================================
HTTP Header   Value
============  ================================
Method        Post
URI Path      /smscenter/v1.0/sendlms
Content-Type  application/json; charset=utf-8
============  ================================

Request Data Format (JSON): 

======================  ===================================   ==================  =====
Key                     Value                                 Format              비고
======================  ===================================   ==================  =====
sender                  "0212341234"                          String              필수
receivers               ["01011111111", "01011112222",]       List                필수
subject                 "이벤트 알림"                         String (UTF-8)      필수
content                 "주문하신 제품이 발송 되었습니다."    String (UTF-8)      필수
reservation             "2014-06-12T16:01:45.923Z"            UTC Date (ISO8601)  옵션
blockrejectednumbers    true                                  Boolean             옵션 (기본값 true)
======================  ===================================   ==================  =====

Example::

  {sender "01011112222", receivers: ["01011111111",], subject: "관리자 알림", content: "주문 취소건 발생"}


.. note::

    Subject는 EUC-KR 인코딩 기준 60바이트 까지 허용 됩니다.  contents는 EUC-KR 인코딩 기준 최대 2000자 까지 전송 가능합니다. 2000자가 넘는 긴 문자열을 보낼 경우 2000자로 자동으로 잘려서 발송 됩니다.

.. note::

    EUC-KR기준 80바이트를 넘지 않더라도 LMS URI로 Request 할 경우 장문 전송으로 과금 처리 됩니다.

.. note::

    기타 고려사항 및 Response는 SMS발송결과_ 와 동일합니다. 

메시지 발송 결과 조회
---------------------

HTTP Request Header:

============  ================================
HTTP Header   Value
============  ================================
Method        Get
URI Path      /smscenter/v1.0/sendresult/발송ID
============  ================================

.. note::

   SMS또는 LMS 발송 결과로 리턴받은 발송ID를 URI에 붙여서 Request 하십 시오.

.. note::

   발송ID는 일정 기간 후에는 자동 소멸 되며 이후 발송 결과 조회에 사용할 수 없습니다.


Example::

  Get /smscenter/v1.0/sendresult/10001 HTTP/1.1

HTTP Response Header:

=============  ======================================
HTTP Header    Value
=============  ======================================
Status         200
Content-Type   application/json; charset=utf-8
=============  ======================================

.. _발송결과Object:

Response Data Format (JSON): 

=============  ===================================   =========  ======
Key            Value                                 Format     비고
=============  ===================================   =========  ======
sent_time      "2014-06-12T16:01:45.923Z"            UTC Date   발송 시간
destination    "01011112222"                         String     수신 번호
status         0                                     Int        발송상태_
=============  ===================================   =========  ======

Example::

  {status: 0, sent_time: "2014-06-12T16:01:45.923Z", destination: "01011112222"}

.. _발송상태:
.. note::

    발송상태 표
	=======  =====
	status   의미
	=======  =====
	-1       확인 불가 (재시도 필요)
	0        성공
	10000    실패 (알수 없는 이유)
	10001    서비스 불가 단말기
	10002    NPDB (번호이동DB) 관련 에러
	10003    서비스 일시 정지
	10004    단말기 문제
	10005    System 에러
	10006    발송 제한시간 초과
	=======  =====


메시지 발송 결과 조회 (그룹)
----------------------------

HTTP Request Header:

============  ========================================
HTTP Header   Value
============  ========================================
Method        Get
URI Path      /smscenter/v1.0/sendresult/group/그룹ID
============  ========================================

.. note::

   SMS또는 LMS 발송 결과로 리턴받은 그룹ID를 URI에 붙여서 Request 하십 시오.

Example::

  Get /smscenter/v1.0/sendresult/group/10001 HTTP/1.1

HTTP Response Header:

=============  ======================================
HTTP Header    Value
=============  ======================================
Status         200
Content-Type   application/json; charset=utf-8
=============  ======================================

.. 발송결과Object:

Response Data Format (JSON): 

=============  ===========================   =========  ======
Key            Value                         Format     비고
=============  ===========================   =========  ======
succeed        ["10001", "10002", ]          List       필수
failed         ["10003", "10004", ]          List       옵션
pending        ["10005", "10006", ]          List       옵션
=============  ===========================   =========  ======

succeed, failed, pending 은 각각 성공된 발송ID 리스트, 실패한 발송ID리스트, 아직 성공여부가 확인 되지 않은 발송ID리스트 입니다. pending의 경우, 수신자가 응영지역에 있거나, 전원이 꺼져있는 등의 이유로 48시간 이내에 전달이 안되었 거나 아직 시스템에 의해 발송 성공 여부의 파악이 완료되지 않은 경우 입니다. 

.. note::

   `발송 결과 Callback`_ 이 호출되기 이전에는 아직 시스템에 해당 그룹의 메시지의 발송 결과값들이 모두 파악 되지 않은 상태이기 때문에 대부분 pending 상태의 결과 값을 받게 됩니다.


예약 발송 취소
--------------

HTTP Request Header:

============  ================================
HTTP Header   Value
============  ================================
Method        Delete
URI Path      /smscenter/v1.0/cancel/예약ID
============  ================================

.. note::

   SMS또는 LMS 발송 결과로 리턴받은 발송ID를 URI에 붙여서 Request 하십 시오.


Example::

  Delete /smscenter/v1.0/cancel/187c4b7affa011e3bf47c42c032b413b

.. note::

    이 Request는 Response Data (Content) 없이 HTTP Status 로 결과가 리턴됩니다. HTTP Status Code 별 의미는 아래 표와 같습니다.

	=======  =====
	Status   의미
	=======  =====
	204      성공 (200과 같으나 content가 없으므로 HTTP 규약에 따라 204)
	404      발송ID 찾을 수 없음
	500      알수 없는 에러 (Internal Server Error)
	=======  =====

수신거부 번호 조회
------------------

080 수신자 부담 전화 서비스를 통해 접수된 SMS 수신 거부 등록된 번호 목록을 조회하는 기능입니다.

HTTP Request Header:

============  ================================
HTTP Header   Value
============  ================================
Method        Get
URI Path      /smscenter/v1.0/rejectednumbers
============  ================================

Example::

  Get /smscenter/v1.0/rejectednumbers HTTP/1.1

HTTP Response Header:

=============  ======================================
HTTP Header    Value
=============  ======================================
Status         200
Content-Type   application/json; charset=utf-8
=============  ======================================

Response Data Format (JSON): 

=============  ===================================   =========
Key            Value                                 Format   
=============  ===================================   =========
rejected       [수신거부Object, 수신거부Object,]     List     
=============  ===================================   =========

.. Note::

   수신거부 Object의 Format은 다음과 같습니다.

   =============  ===========================   =========  =================
   Key            Value                         Format     비고
   =============  ===========================   =========  =================
   number         "0101112222"                  String     전화번호
   registered     "2014-06-12T16:01:45.923Z"    UTC Date   수신거부 등록시간
   =============  ===========================   =========  =================


Example::

  {rejected: [
  	{number: "01011112222", registered: "2014-06-12T16:01:45.923Z"},
  	{number: "01011112223", registered: "2014-06-12T16:01:45.923Z"},
  	{number: "01011112224", registered: "2014-06-12T16:01:45.923Z"},
  ]}


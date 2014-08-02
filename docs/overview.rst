.. module:: overview

서비스 개요
===========

청기와랩의 SMS Open API는 중소규모 웹사이트에 필요한 SMS (장문/단문) 발송 기능 구현을 오픈API 제공 서비스 입니다.  이를 위해 청기와랩의 SMS OpenAPI 서비스는 RESTful하게 디자인 되었고 JSON을 메인 전송 포멧으로 채택한 HTTP 기반 인터페이스를 제공합니다. 

용어 정리
---------

* 청기와랩 : https://bluehouselab.com
* Server : 청기와랩이 SMS OpenAPI를 위해 제공하는 WebServer
* Client : SMS OpenAPI를 사용하여 구현된 어플리케이션, 모바일앱, 웹사이트
* HTTP : Hypertext 전송 프로토콜 http://ko.wikipedia.org/wiki/HTTP
* HTTPS : HTTP over SSL, http://ko.wikipedia.org/wiki/HTTPS
* HTTP Request Header : 클라이언트가 HTTP Request시 부여할 수 있는 설정값, HTTP Request Data의 Mime Type, API Key 등이 기술 될 수 있다.
* HTTP Request Data : 클라이언트가 HTTP Request시 실어 보내는 데이타
* HTTP Response Header : Server가 클라이언트의 HTTP Request에 대해 응답할때의 각종 설정 값. HTTP Status Code (200, 204, 404, 500 ...) 및 Response Data의 Mime Type등이 기술 될 수 있다. 및 Response Data의 Mime Type등이 기술 될 수 있다.
* HTTP Response Data : Server가 클라이언트의 HTTP Request에 대해 응답 하는 데이타
* JSON : Data 교환을 위한 포멧 http://www.json.org/json-ko.html
* HTTP Basic Auth : HTTP에서 가장 많이 쓰이는 인증 방법 중의 하나 http://tools.ietf.org/html/rfc2617
* App Id : 등록된 App 또는 웹사이트의 ID
* API Key : 서비스 과금을 위해 클라이언트에게 제공되는 암호화된 문자열, App Id별로 하나씩 발급 됨
* Git : 소스코드관리도구(SCM) http://git-scm.com
* EUC-KR : KSC5601 한국어 문자세트를 표기하기 위해 유닉스에서 사용하던 문자열 인코딩 표준. 과거 인터넷 및 각종 OS에서 한국어 문자열을 표현하기 위해 널리 사용 되었으나 현재는 UTF-8, 16등의 유니코드용 인코딩 표준에 의해 대체 되었다. 한국의 SMS 망 표준으로도 사용 되었으며, 한글은 2바이트, 영문 및 특수 문자는 1바이트를 차지 한다.
* UTF-8 : 유니코드 문자세트를 표기하기 위한 문자열 인코딩 표준. 한국어 뿐만 아니라 유니코드에서 표현할 수 있는 전세계 문자를 모두 인코딩 할수 있어, 각종 OS및 인터넷 관련 표준으로 사용됨. 영문 및 ASCII 영역 특수문자는 1바이트 그외 문자열은 3~6바이트로 표현 된다. 한글 문자의 경우 대부분 3바이트로 표현 된다.


Server 정보
-------------

안전한 Open API 접근을 위해 청기와랩은 HTTPS (TLSv1) 연결을 제공합니다.

* Server URL: https://api.bluehouselab.com (Port 443)

.. note::

   API Key 보호를 위해 HTTP 연결은 제공되지 않고 HTTPS 연결만 제공 합니다.  청기와랩은 HTTPS 연결을 위해 공인 인증기관(CA)으로 부터 발급된 SSL 인증서를 제공하므로 HTTPS 연결을 믿고 쓸 수 있습니다.

   만약 HTTPS 연결시 SSL 인증서 검증(Verify) 과정을 무시하도록 클라이언트를 구현할 경우 보안 공격에 의해 API Key가 노출 될 수 있으므로 주의가 필요 합니다.

App Id와 API Key
-----------------

App Id는 청기와랩 SMS Open API 서비스에 등록된 App 또는 웹사이트의 Id이며 각 App Id별로 고유의 API Key가 존재 합니다. App Id와 API Key는 인증을 위해 사용 됩니다.

청기와랩 https://bluehouselab.com/sms 페이지를 방문하시면 App Id및 API Key를 발급 받으실 수 있습니다.

APACHEHTTPCLIENTVER=4.3.4
APACHEHTTPCOREVER=4.3.2
APACHEHTTPCLIENT=httpcomponents-client-$(APACHEHTTPCLIENTVER)
APACHEHTTPCLIENTURL=http://apache.mirror.cdnetworks.com//httpcomponents/httpclient/binary/$(APACHEHTTPCLIENT)-bin.zip
APACHEHTTPCLIENTJAR=$(APACHEHTTPCLIENT)/lib/httpclient-$(APACHEHTTPCLIENTVER).jar
APACHEHTTPCOREJAR=$(APACHEHTTPCLIENT)/lib/httpcore-$(APACHEHTTPCOREVER).jar
APACHECOMMONSJAR=$(APACHEHTTPCLIENT)/lib/commons-codec-1.6.jar 
CLASSPATH=.:$(APACHEHTTPCLIENTJAR):$(APACHEHTTPCOREJAR):$(APACHECOMMONSJAR)
JAVAC=javac
OPTS=-encoding UTF8 -cp $(CLASSPATH)

all: SendSMS.class Result.class

SendSMS.class: SendSMS.java $(APACHEHTTPCLIENTJAR) Config.class
	$(JAVAC) $(OPTS) $<

Result.class: Result.java $(APACHEHTTPCLIENTJAR) Config.class
	$(JAVAC) $(OPTS) $<

Config.class: Config.java
	$(JAVAC) $(OPTS) $<

$(APACHEHTTPCLIENT)/lib/httpclient-$(APACHEHTTPCLIENTVER).jar: $(APACHEHTTPCLIENT)-bin.zip
	test ! -f $@ && unzip $<
	touch $@

$(APACHEHTTPCLIENT)-bin.zip:
	test ! -f $@ && curl $(APACHEHTTPCLIENTURL) > $@


clean:
	rm -f *.class
	rm -rf httpcomponents-client-*

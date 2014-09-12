CSC=mcs

all: sendsms.exe result.exe

sendsms.exe: sendsms.cs
	$(CSC) $<

result.exe: result.cs
	$(CSC) $<

clean:
	rm -f *.exe

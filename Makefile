SERVER: http-client.c
	g++ -o client -Wall -pedantic http-client.c httpget.c httpput.c httppost.c httpclient.h 
clean:
	rm -rf client

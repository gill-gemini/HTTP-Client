# HTTP CLIENT

**Descrition:**
Http client built a transport layer connection with the server for the purpose of communication. This
transport layer virtual circuit is built with the help of mostly TCP.It is a program that establishes connections
for the purpose of sending requests.
There are various kinds of requests which a HTTP client can send, but in this implementation there are two
mandatory requests which were implemented in the first phase of the assignment.
* GET: Fetch a file from a server and store it into local file system.
* PUT: push a file to a given server provided by user from a local file system.
* Post

![Diagram of models]( https://github.com/gill-gemini/HTTP-Client/blob/master/httpclient.png)

**Installation Instructions and requirements:**
 * Just write “make” in the terminal.
Make sure while using “PUT” feature, the file is in the same directory

**4.User Instructions:**
The make file generates the executable ./client.

GET & PUT METHOD
*`./client <GET/PUT><DNS>:<PORT>/<filename>`
for example

GET
*`./client GET nwprog1.netlab.hut.fi:3000/index`

PUT
*`./client PUT nwprog1.netlabt.hut.fi:3000/index`

POST METHOD
`./client <POST><SERVERDNS>:<PORT>/<lookupname><querytype>`

for example you want to find ip address for www.google.com and query A
*`./client POST nwprog1.netlab.hut.fi:8934/www.google.com A`


The results of the post query will be saved in the results.txt.In command line you can only write "Get"/"GET" and "Put"/"PUT"
Other than that program will not be implemented.The file you want to upload during the HTTP put should be in the same directory shown in the terminal. 


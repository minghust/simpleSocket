Chatting Room
=
Based on C, s simple SOCKET program. 
## Develope Environment

|       OS       |            Compiler                |
|----------------|------------------------------------|
|  OS X 10.10.5  | LLVM version 7.0.0 (clang-700.1.76)|




## Prerequisite
You should know about **TCP/IP** protocol and what is **socket**.<br \>
**Server**<br \>

- **create** a socket
- give server's(means itself) **address**
- **bind** your socket with address
- start **listening** from client
- waiting for cilent's connection, once connected, it will **accept** client's connection
- use the socket getting from acceptation to **recieve** and **send** data.
- **close** socket.


**Client**<br \>

- **create** a socket
- give a server's **address**
- while server start listening, it can make **connect** to server
- while get server's acceptation, it will **recieve** and **send** data
- **close** socket.

## Reference
you can refer blogs below<br \>

- [http://blog.csdn.net/g_brightboy/article/details/12854117](http://blog.csdn.net/g_brightboy/article/details/12854117)
- [http://blog.csdn.net/wind19/article/details/6156339](http://blog.csdn.net/wind19/article/details/6156339)


## Exceptation
all the cpu bellow has big endian, you should test your cpu first.

- Motorola680x()
- HP-PA UNIX
- MIPS UNIX
- PowerPC
- RS/6000
- SPARC
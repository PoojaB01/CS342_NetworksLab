# FILE TRANSFER PROTOCOL USING CLIENT-SERVER SOCKET PROGRAMMING

Creators:
  * Pooja Gajendra Bhagat , Department: CSE, Roll number: 180101057
  * Saurabh Baranwal, Department: CSE, Roll number: 180101072

The following is a C-based implementation of File Transfer Protocol (FTP). It has the following 5 functionalities:
 * PUT : Transfer a file from client's to server's disk
 * GET : Fetch a file from server's disk to client's disk
 * MGET : Fetch all files of a given extension from server's disk to client's disk
 * MPUT : Transfer all files of a given extension from client's disk to server's disk
 * ls : List all files

Along with the above 5 functionalities, a file overwrite feature is also implemented i.e. if a file that is to be transferred already exists in the destination directory; the user must specify Y or N to let the system know if the existing file has to be overwritten or not.

### Code Details

Client's source code is stored in "client.c" and Server's source code is stored in "server.c"

The directories 'client_dir' and 'server_dir' act the respective disks of client and server. Any file transfer take place between both these directories, and client and server maintain their files in the respective directories. 

Info about compilation of code:

Two different terminals should be opened (one for client and the other for server). 

For server:
```bash
$ gcc server.c -o server
```

For client:
```bash
$ gcc client.c -o client
```

Info about running the code:

First on the server, run:
```bash
$ ./server <Port number>
```

Then, on the client terminal run:
```bash
$ ./client <Server IP Address> <Server Port number>
```

For easy check of the program, we can take the IP Address of Server to be simply the loopback address.
On doing this, the client is now connected to the server. 

The client will have to give input a command in legal format so that necessary action can be taken. The server code is executed just once and waits for incoming connections. Server can be stopped by pressing "CTRL + C" on the corresponding terminal on which its code was compiled and run. Further, the client can make a connection with the server and keeps on giving necessary inputs. The client will be closed only when the user gives the exit input on its own.

The legal format for commands to be entered from client's side is specified as follows:
### Command format
   * PUT : PUT \<filename>                         ( For example : PUT abc.c )
   * GET : GET \<filename>                         ( For example : GET bcd.c )
   * MGET :  MGET \<extension excluding dot>     	( For example : MGET txt)
   * MPUT : MPUT \<extension excluding dot>        ( For example : MPUT txt )
   * ls : ls
   * exit : exit
  
In cases, where the terminal asks you permission to whether overwrite a particular file at the destination (if it is already existing), you can give the user input as Y or N depending on whether your choice is "Yes" or "No".

### Assumptions made
  * The commands should be given in legal format, otherwise the terminal will show output "Invalid Command". Strictly follow the above format to get the desired results
  * Filename should only have ASCII characters along with the extension (.c or .txt). Any case where file is not found is handled appropriately by our code. For the purpose of this assignment, we assume only TXT or C files to be there.
  * The directories 'client_dir' and 'server_dir' are chosen to be disks of client and server so that the file transfer can be checked easily on my local machine without worrying about addressing (for testing purposes, we chose loopback address). In cases, where client and server are remotely located; the disks (path to be precise) can be chosen differently. 

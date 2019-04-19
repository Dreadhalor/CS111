#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>
#include <poll.h>
#include <unistd.h>
//#include <wait.h>

pid_t pid;
int debug_flag;
int encrypt_flag;
int port;
int socket_fd;
int new_socket_fd;
int to_child_pipe[2];
int to_parent_pipe[2];
int buffer[256];
struct sockaddr_in server_address;
struct sockaddr_in client_address;
struct pollfd polls[2];
socklen_t client_length;

void print_usage()
{
	fprintf(stderr, "Usage: lab1b-server [port p]\np: Port to open\n");
	exit(1);
}

void create_socket()
{
	socket_fd=socket(AF_INET, SOCK_STREAM, 0);
	if(socket_fd < 0)
	{
		perror("Socket Error");
		exit(1);
	}

	memset((char*)&server_address, 0, (sizeof(server_address)));
	server_address.sin_family=AF_INET;
	server_address.sin_addr.s_addr=INADDR_ANY;
	server_address.sin_port=htons(port);

	if(debug_flag)
		fprintf(stderr, "Successfully created and set up socket\n");
}

void bind_socket()
{
	if(bind(socket_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
	{
		perror("Bind error");
		exit(1);
	}

	if(debug_flag)
		fprintf(stderr, "Successfully bound name to socket\n");
}

void listen_connection()
{
	if(listen(socket_fd, 5) < 0)
	{
		perror("Listen error");
		exit(1);	
	}
	
	if(debug_flag)
		fprintf(stderr, "Listening for connection on port %d\n", port);
}

void accept_connection()
{
	if((new_socket_fd=accept(socket_fd, (struct sockaddr*)&client_address, &client_length)) < 0)
	{
		perror("Accept error");
		exit(1);		
	}

	if(debug_flag)
		fprintf(stderr, "Successfully accepted the connection\n");
}

void set_polls()
{
	polls[0].fd=new_socket_fd;
	polls[1].fd=to_parent_pipe[0];
	polls[0].events= (POLLIN | POLLHUP | POLLERR);
	polls[1].events= (POLLIN | POLLHUP | POLLERR);

	if(debug_flag)
		fprintf(stderr, "Successfully set up polls\n");	
}

void create_pipe()
{
	if(pipe(to_parent_pipe) < 0)
	{
		perror("Pipe error");
		exit(1);
	}

	if(pipe(to_child_pipe) < 0)
	{
		perror("Pipe error");
		exit(1);
	}	

	if(debug_flag)
		fprintf(stderr, "Successfully created pipes\n"); 
}

void exit_code()
{
	if(debug_flag)
		fprintf(stderr, "Running exit code\n");

	close(to_child_pipe[0]);
	close(to_child_pipe[1]);
	close(to_parent_pipe[0]);
	close(to_parent_pipe[1]);
	
	close(new_socket_fd);
	//encrypt flag
	
	int status;
	if(waitpid(pid, &status, 0) < 0)
	{
		perror("Wait error");
		exit(1);
	}

	if(WIFEXITED(status))
	{
		fprintf(stderr, "SHELL EXIT SIGNAL=%d STATUS=%d\n", WEXITSTATUS(status), WTERMSIG(status));
	}
}

void read_write()
{
	while(1)
	{
		if(poll(polls, 2, 0) < 0)
		{
			perror("Poll error");
			exit(1);
		}

		//if we need to read from socket
		if(polls[0].revents & POLLIN)
		{
			if(debug_flag)
				fprintf(stderr, "received input from socket!");
			int bytes_read;
			bytes_read=read(new_socket_fd, buffer, 1);
			if(bytes_read < 0)
			{
				perror("Read error");
				exit(1);
			}
			//if encrypt
			if((*buffer) == 3)
			//^C
			{
				kill(pid, SIGINT);	
				exit(0);	
			}
			else if((*buffer) == 4)
			//^D
			{		
				exit(0);	
			}
			else if((*buffer) == '\r' || (*buffer) == '\n')
			{
				char* temp = "\n";
				write(to_child_pipe[1], &temp, 1); 
			}
			else 
			{
				write(to_child_pipe[1], &buffer, 1);
			}
		}
		//if we need to output from shell
		if(polls[1].revents & POLLIN)
		{
			if(debug_flag)
				fprintf(stderr, "outputting things from the shell!");
			int bytes_read;
			if((bytes_read=read(to_parent_pipe[0], &buffer, 1)) < 0)
			{
				perror("Read error");
				exit(1);
			}
			
			if(bytes_read == 0)
			{
				exit(0);
			}
			//if encrypt
			write(new_socket_fd, &buffer, 1);
		}
		//if receive interrupt
		if(polls[1].revents & (POLLHUP | POLLERR))
		{
			if(debug_flag)
				fprintf(stderr, "Shell received an interrupt! Shell shutting down\n");
			exit(0);
		}
	}
}

int main(int argc, char* argv[])
{

	debug_flag=0;
	encrypt_flag=0;
	struct option options[]=
	{
		{"port", required_argument, 0, 'p'},
		{"encrypt", required_argument, 0, 'e'},
		{"debug", no_argument, 0, 'd'}
	};	

	int option_num;
	while((option_num=getopt_long(argc, argv, "p:e:d", options, NULL)) != -1)
	{
		switch(option_num)
		{
			case 'p':
				port=atoi(optarg);
				break;
			case 'e':
				encrypt_flag=1;
				break;
			case 'd':
				debug_flag=1;
				break;
			default:
				print_usage();
				break;
		}
	}	

	atexit(exit_code);
	
	create_socket();	
	//bind
	bind_socket();	
	//listen
	listen_connection();	
	//accept
	client_length=sizeof(client_address);
	accept_connection();

	create_pipe();
	//poll
	set_polls();

	pid=fork();
	if(pid < 0)
	{
		perror("Fork error");
		exit(1);
	}
	else if(pid == 0)
	//in child process
	{
		if(debug_flag)
			fprintf(stderr, "in child process before pipe redir\n");
		close(to_child_pipe[1]);
	        close(to_parent_pipe[0]);
	        dup2(to_child_pipe[0], STDIN_FILENO);
	        dup2(to_parent_pipe[1], STDOUT_FILENO);
	        dup2(to_parent_pipe[1], STDERR_FILENO);
	        close(to_child_pipe[0]);
	        close(to_parent_pipe[1]);

		if(debug_flag)
			fprintf(stderr, "in child after pipe redir\n");
	        char * arg[2] = {"/bin/bash", NULL};
	        if (execvp("/bin/bash", arg) < 0)
	        {
			perror("Exec error");
			exit(1);
	        }

		if(debug_flag)
			fprintf(stderr, "in child after exec\n");
	}
	else
	//in parent process
	{
		close(to_child_pipe[0]);
		close(to_parent_pipe[1]);
		read_write();
	}
	
	//mcrypt

	exit(0);
}
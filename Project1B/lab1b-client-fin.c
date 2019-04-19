#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <unistd.h>
#include <fcntl.h>
#include <termios.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <errno.h>
#include <poll.h>

int socket_fd;
int port;
int log_fd;
int log_flag;
int debug_flag;
int encrypt_flag;
char buffer[1];
char line_feed[2]={'\r', '\n'};
char* log_file;
struct pollfd polls[2];
struct termios saved_terminal_mode;
struct hostent *server;
struct sockaddr_in server_address;

void print_usage()
{
	fprintf(stderr, "Usage: lab1b-client [port p]\np: port to open\n"); 
	exit(1);
}

void save_terminal()
{
	if(tcgetattr(STDIN_FILENO, &saved_terminal_mode) < 0)
	{
		perror("Save terminal error");
		exit(1);	
	}
	
	if(debug_flag)
		fprintf(stderr, "Successfully saved terminal\n");
}

void set_old_terminal()
{
	if(tcsetattr(STDIN_FILENO, TCSANOW, &saved_terminal_mode) < 0)
	{
		perror("Terminal set error");
		exit(1);	
	}
	if(debug_flag)
		fprintf(stderr, "Successfully set old terminal\n");
}

void set_new_terminal()
{	
	struct termios current_terminal_mode;
	tcgetattr(STDIN_FILENO, &current_terminal_mode);
	current_terminal_mode.c_iflag=ISTRIP;
	current_terminal_mode.c_lflag=0;
	if(tcsetattr(STDIN_FILENO, TCSANOW, &current_terminal_mode) < 0)
	{
		perror("Terminal set error");
		exit(1);
	}
	atexit(set_old_terminal);	
	
	if(debug_flag)
		fprintf(stderr, "Successfully set new terminal\n");
}

void create_socket()
{
	if((socket_fd=socket(AF_INET, SOCK_STREAM, 0)) < 0)
	{
		perror("Socket error");
		exit(1);
	}

	if((server=gethostbyname("localhost")) == NULL)
	{
		perror("Host name error");
		exit(1);
	}

	memset((char*)&server_address, 0, sizeof(server_address));
	server_address.sin_family=AF_INET;
	memcpy((char*)&server_address.sin_addr.s_addr, (char*)server->h_addr, server->h_length);
	server_address.sin_port=htons(port);

	if(debug_flag)
		fprintf(stderr, "Successfully created socket\n");	
}

void set_polls()
{
	polls[0].fd=STDIN_FILENO;
	polls[1].fd=socket_fd;
	polls[0].events= (POLLIN | POLLHUP | POLLERR);
	polls[1].events= (POLLIN | POLLHUP | POLLERR);
	
	if(debug_flag)
		fprintf(stderr, "Successfully set up polls\n");
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
	
		//if keyboard has stuff to read
		if(polls[0].revents & POLLIN)
		{
			if(read(STDIN_FILENO, &buffer, 1) < 0)
			{
				perror("Read error");
				exit(1);
			}

			if((*buffer) == '\r' || (*buffer) == '\n')
			{
				write(STDOUT_FILENO, &line_feed, 2);
				//if encrypt
				if(log_flag)
				{
					write(log_fd, "SENT 1 bytes: ", 14);
					write(log_fd, &buffer, 1);
					write(log_fd, "\n", 1);		
				}
				write(socket_fd, &buffer, 1);
			}
			else
			{
				write(STDOUT_FILENO, &buffer, 1);
				//if encrypt
				if(log_flag)
				{
					write(log_fd, "SENT 1 bytes: ", 14);
					write(log_fd, &buffer, 1);
					write(log_fd, "\n", 1);
				}
				write(socket_fd, &buffer, 1);
			}
		}
		
		//if socket has stuff to read
		if(polls[1].revents & POLLIN)
		{
			read(socket_fd, &buffer, 1);

			if(log_flag)
			{
				write(log_fd, "RECEIVED 1 bytes: ", 17);
				write(log_fd, &buffer, 1);
				write(log_fd, "\n", 1);
			}
			//if encrypt
			
			if((*buffer) == '\n' || (*buffer) == '\r')
			{
				write(STDOUT_FILENO, &line_feed, 2);
			}
			else if((*buffer) == 3)
			{
				exit(0);
			}
			else
			{
				write(STDOUT_FILENO, &buffer, 1);
			}
		}

		//if socket receives interrupt
		if(polls[1].revents & (POLLHUP | POLLERR))
		{
			if(debug_flag)
				fprintf(stderr, "Recevied an interrupt from socket!\n");
			exit(0);
		}
	}
}

void connect_port()
{
	if(debug_flag)
		fprintf(stderr, "Attempting to connect on port %d\n", port);

	if(connect(socket_fd, (struct sockaddr*)&server_address, sizeof(server_address)) < 0)
	{
		perror("Connect error");
		exit(1);	
	}

	if(debug_flag)
		fprintf(stderr, "Successfully connected on port%d\n", port);
}

int main(int argc, char* argv[])
{
	int option_num;
	debug_flag=0;
	log_flag=0;
	encrypt_flag=0;
	struct option options[]=
	{
		{"port", required_argument, 0, 'p'},
		{"log", required_argument, 0, 'l'},
		{"encrypt", required_argument, 0, 'e'},
		{"debug", no_argument, 0, 'd'}
	};

	while((option_num=getopt_long(argc, argv, "p:l:e:d", options, NULL)) != -1)
	{
		switch(option_num)
		{
			case 'p':
				port=atoi(optarg);
				if(debug_flag)
					fprintf(stderr, "Port specified\n");
				break;
			case 'l':
				log_flag=1;
				log_file=optarg;
				log_fd=creat(log_file, O_WRONLY);
				if(log_fd < 0)
				{
					fprintf(stderr, "Open/create error\n");
					exit(1);
				}
				if(debug_flag)
					fprintf(stderr, "Log specified\n");
				break;
			case 'e':
				encrypt_flag=1;
				if(debug_flag)
					fprintf(stderr, "Encrypt specified\n");
				break;
			case 'd':
				debug_flag=1;
				break;
			default:
				print_usage();
				break;
		}
	}

	save_terminal();
	set_new_terminal();
	//connect
	create_socket();
	connect_port();	

	set_polls();

	read_write();	
	
	exit(0);
}
#include <errno.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>

////////////////////////////////////////////////////////////////////////////////

int extract_message(char **buf, char **msg) {
	char	*newbuf;
	int	i;

	*msg = 0;
	if (*buf == 0)
		return (0);
	i = 0;
	while ((*buf)[i]) {
		if ((*buf)[i] == '\n') {
			newbuf = calloc(1, sizeof(*newbuf) * (strlen(*buf + i + 1) + 1));
			if (newbuf == 0)
				return (-1);
			strcpy(newbuf, *buf + i + 1);
			*msg = *buf;
			(*msg)[i + 1] = 0;
			*buf = newbuf;
			return (1);
		}
		i++;
	}
	return (0);
}

char *str_join(char *buf, char *add)
{
	char	*newbuf;
	int		len;

	if (buf == 0)
		len = 0;
	else
		len = strlen(buf);
	newbuf = malloc(sizeof(*newbuf) * (len + strlen(add) + 1));
	if (newbuf == 0)
		return (0);
	newbuf[0] = 0;
	if (buf != 0)
		strcat(newbuf, buf);
	free(buf);
	strcat(newbuf, add);
	return (newbuf);
}

////////////////////////////////////////////////////////////////////////////////

typedef struct	s_client {
	int				id;
	int				fd;
	struct s_client	*next;
}				t_client;

int			g_id = 0;
int			g_socket = -1;
t_client	*g_clients = NULL;

void	ft_exit(char *msg) {
	t_client *next;

	write(2, msg, strlen(msg));
	write(2, "\n", 1);
	if (g_socket != -1)
		close(g_socket);
	while (g_clients != NULL) {
		next = g_clients->next;
		close(g_clients->fd);
		free(g_clients);
		g_clients = next;
	}
	exit(1);
}

t_client	**lstnext(void) {
	t_client *last = g_clients;

	if (g_clients == NULL)
		return (&g_clients);
	while (last->next != NULL)
		last = last->next;
	return (&last->next);
}

void	send_one_client(t_client *client, const char *const msg) {
	int ret;
	int sent = 0;
	int len = strlen(msg);

	while (sent < len) {
		if ((ret = send(client->fd, msg + sent, len - sent, MSG_DONTWAIT)) <= 0)
			return ;
		sent += ret;
	}
}

void	send_to_clients(const char *const msg, int except_id) {
	t_client *client = g_clients;

	while (client) {
		if (client->id != except_id)
			send_one_client(client, msg);
		client = client->next;
	}
}

void	new_client(fd_set *set, int *max_fd) {
	t_client *client;
	struct sockaddr_in cli;
	socklen_t len = sizeof(cli);

	if ((client = malloc(sizeof(t_client))) == NULL)
		ft_exit("Fatal error");
	bzero(client, sizeof(t_client));
	*lstnext() = client;
	if ((client->fd = accept(g_socket, (struct sockaddr *)&cli, &len)) < 0)
		ft_exit("Fatal error");
	client->id = g_id++;
	{
		char msg[50];

		if (sprintf(msg, "server: client %d just arrived\n", client->id) < 0)
			ft_exit("Fatal error");
		send_to_clients(msg, client->id);
	}
	FD_SET(client->fd, set);
	if (client->fd > *max_fd)
		*max_fd = client->fd;
}

void	mini_serv(void) {
	fd_set	origin, cpy;
	int		max_fd = g_socket;

	FD_ZERO(&origin);
	FD_SET(g_socket, &origin);
	while (1) {
		FD_ZERO(&cpy);
		FD_COPY(&origin, &cpy);
		if (select(max_fd + 1, &cpy, NULL, NULL, NULL) == -1)
			ft_exit("Fatal error");
		if (FD_ISSET(g_socket, &cpy))
			new_client(&origin, &max_fd);

	}
}

void	init_serv(int port) {
	struct sockaddr_in servaddr;

	if ((g_socket = socket(AF_INET, SOCK_STREAM, 0)) == -1)
		ft_exit("Fatal error");
	bzero(&servaddr, sizeof(servaddr));
	servaddr.sin_family = AF_INET;
	servaddr.sin_addr.s_addr = htonl(2130706433); //127.0.0.1
	servaddr.sin_port = htons(port);

	if ((bind(g_socket, (struct sockaddr *)&servaddr, sizeof(servaddr))) != 0)
		ft_exit("Fatal error");
	if (listen(g_socket, 10) != 0)
		ft_exit("Fatal error");
}

int		main(int argc, char **argv)
{
	if (argc != 2)
		ft_exit("Wrong number of arguments");
	init_serv(atoi(argv[1]));
	mini_serv();
	return (0);
}

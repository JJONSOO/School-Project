#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include<signal.h>
#include<fcntl.h>
#define MAX_CMD_ARG 30

const char *prompt = "myshell> ";
char* cmdvector[MAX_CMD_ARG];
char  cmdline[BUFSIZ];
char* firstcmd[MAX_CMD_ARG];
char* secondcmd[MAX_CMD_ARG];
char* lastcmd[MAX_CMD_ARG];
void fatal(char *str)
{
	perror(str);
	exit(1);
}

void command_cd(char* path)
{
	chdir(path);
}

int makelist(char *s, const char *delimiters, char** list, int MAX_LIST)
{
	int i = 0;
	int numtokens = 0;
	char *snew = NULL;

	if ((s == NULL) || (delimiters == NULL))
	{
		return -1;
	}

	snew = s + strspn(s, delimiters);    /* delimitersžŠ skip */
	if ((list[numtokens] = strtok(snew, delimiters)) == NULL)
	{
		return numtokens;
	}

	numtokens = 1;

	while (1)
	{
		if ((list[numtokens] = strtok(NULL, delimiters)) == NULL)
		{
			break;
		}
		if (numtokens == (MAX_LIST - 1))
		{
			return -1;
		}
		numtokens++;
	}
	return numtokens;
}
static void Sa_handler(int signal) {
	int status;
	pid_t pid;
	while ((pid = waitpid(-1, &status, WNOHANG))>0) {
	}
}
void handler(int signal) {
	printf("\n");
	return;
}
int redirection_in(char **cmdvector) {
	int i;
	int fd;
	for (int j = 0; cmdvector[j] != NULL; j++) {
		if (!strcmp(cmdvector[j], "|")) {
			break;
		}
	}
	for (i = 0; cmdvector[i] != NULL; i++) {
		if (!strcmp(cmdvector[i], "<"))
			break;
	}
	if (cmdvector[i]) {
		if (!cmdvector[i + 1])
			return -1;

		else {
			if ((fd = open(cmdvector[i + 1], O_RDONLY)) == -1) {
				perror(cmdvector[i + 1]);
				return -1;
			}
		}
		dup2(fd, 0);
		close(fd);
		for (i = i; cmdvector[i] != NULL; i++) {
			cmdvector[i] = cmdvector[i + 2];
		}
		cmdvector[i] = NULL;
	}
	return 0;
}
int redirection_out(char **cmdvector) {
	int i;
	int fd;


	for (i = 0; cmdvector[i] != NULL; i++) {
		if (!strcmp(cmdvector[i], ">"))
			break;
	}
	if (cmdvector[i]) {
		if (!cmdvector[i + 1])
			return -1;
		else {
			if ((fd = open(cmdvector[i + 1], O_RDWR | O_CREAT, 0644)) == -1) {
				perror(cmdvector[i + 1]);
				return -1;
			}
		}
		dup2(fd, 1);
		close(fd);
		for (i = i; cmdvector[i] != NULL; i++) {
			cmdvector[i] = cmdvector[i + 2];
		}
		cmdvector[i] = NULL;
	}
	return 0;
}

int pipeaction(char **cmdvector) {
	int i, j;
	int k = 0;
	int n = 0;
	pid_t pid1;
	int fd[2];
	int truth = 0;
	int minpipe[10];
	

	for (j = 0; cmdvector[j] != NULL; j++) {
		if (!strcmp(cmdvector[j], "|")) {
			truth = 1;
			minpipe[n] = j;
			n++;
		}
	}
	if (truth == 0)return 1;
	for (i = 0; i<minpipe[0]; i++) {
		firstcmd[i] = cmdvector[i];
	}
	firstcmd[i] = NULL;
	int chk = 0;
	for (i = i + 1; i<minpipe[1]; i++) {
		secondcmd[chk] = cmdvector[i];
		chk++;
	}
	secondcmd[i] = NULL;
	chk = 0;
	for (i = i + 1; cmdvector[i] != NULL; i++) {
		lastcmd[chk] = cmdvector[i];
		chk++;
	}
	lastcmd[i] = NULL;
	redirection_out(firstcmd);
	pipe(fd);
	pid1 = fork();
	switch (pid1) {
	case -1: perror("fork error");
		break;
	case 0: redirection_in(firstcmd);
		dup2(fd[1], 1);
		close(fd[1]);
		close(fd[0]);
		execvp(secondcmd[0], secondcmd);
		exit(0);
	default: {
		redirection_out(lastcmd);
		dup2(fd[0], 0);
		close(fd[1]);
		close(fd[0]);
		execvp(lastcmd[0], lastcmd);
		exit(0);
	}
	}
	return 0;
}

int main(int argc, char**argv)
{

	int i = 0;
	pid_t pid;
	signal(SIGCHLD, (void*)Sa_handler);
	signal(SIGINT, handler);
	signal(SIGQUIT, handler);
	signal(SIGTSTP, handler);
	while (1)
	{
		int flag = 0;
		fputs(prompt, stdout);
		fgets(cmdline, BUFSIZ, stdin);
		cmdline[strlen(cmdline) - 1] = '\0';

		i = makelist(cmdline, " \t", cmdvector, MAX_CMD_ARG);

		if (!strcmp(cmdline, "exit"))
		{
			exit(1);
		}

		if (!strcmp(cmdline, "cd"))      //command cd
		{
			command_cd(cmdvector[1]);
			continue;

		}

		if (!strcmp(cmdvector[i - 1], "&")) {

			cmdvector[i - 1] = NULL;
			flag--;
		}

		switch (pid = fork())
		{


		case 0:
			if (flag == 0) {
				signal(SIGINT, SIG_DFL);
				signal(SIGQUIT, SIG_DFL);
				signal(SIGTSTP, SIG_DFL);
			}
			else {
				signal(SIGINT, SIG_IGN);
				signal(SIGQUIT, SIG_IGN);
				signal(SIGTSTP, SIG_IGN);
			}


			pipeaction(cmdvector);

			redirection_in(cmdvector);

			redirection_out(cmdvector);







			execvp(cmdvector[0], cmdvector);
			fatal("main()");

		case -1:

			fatal("main()");

		default:

			if (flag<0) {


				waitpid(-1, NULL, WNOHANG);

				pipeaction(cmdvector);

				redirection_in(cmdvector);

				redirection_out(cmdvector);
			}
			else { wait(NULL); };


		}
	};



	return 0;
}
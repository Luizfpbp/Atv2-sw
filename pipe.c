#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
	pid_t Tpid;
	int pipeFile[2];
	int rStatus;
	char writeMessages[1][20] = {"Teste, Teste"};
	char readMessages[20];
	memset(readMessages, '\0', sizeof(char) * 20);

	rStatus = pipe(pipeFile);

	if (rStatus == -1) {
		printf("Erro creating a pipe\n");
		return 1;
	}

	Tpid = fork();

	if (Tpid == 0) {	

		printf("Writing Message is %s\n", writeMessages[0]);	
		write(pipeFile[1], writeMessages[0], sizeof(char) * 20);
		printf("pid: %d\n\n", getpid());

	}

	else {
		
		read(pipeFile[0], readMessages, sizeof(char) * 20);
		printf("Reading Message is %s\n", readMessages);
		printf("pid: %d\n\n", getpid());

		return 0;

	}
	
	wait(NULL);
	return 0;
}

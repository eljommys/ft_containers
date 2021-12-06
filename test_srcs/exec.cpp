#include "test.hpp"

using namespace std;

#define READ   0
#define WRITE  1
static FILE * popen2(string command, string type, int & pid) {
	pid_t child_pid;
	int fd[2];
	pipe(fd);

	if((child_pid = fork()) == -1) {
		perror("fork");
		exit(1);
	}

	/* child process */
	if (child_pid == 0) {
		if (type == "r") {
			close(fd[READ]);
			dup2(fd[WRITE], 1);
		}
		else {
			close(fd[WRITE]);
			dup2(fd[READ], 0);
		}

		setpgid(child_pid, child_pid);
		execl("/bin/sh", "/bin/sh", "-c", command.c_str(), NULL);
		exit(0);
	}
	else {
		if (type == "r")
			close(fd[WRITE]);
		else
			close(fd[READ]);
	}

	pid = child_pid;

	if (type == "r")
		return fdopen(fd[READ], "r");

	return fdopen(fd[WRITE], "w");
}

static int pclose2(FILE * fp, pid_t pid) {
	int stat;

	fclose(fp);
	while (waitpid(pid, &stat, 0) == -1) {
		if (errno != EINTR) {
			stat = -1;
			break;
		}
	}

	return stat;
}

std::string exec(const char* cmd) {
	char buffer[128];
	int pid;
	std::string result = "";
	FILE* pipe = popen2(cmd, "r", pid);
	if (!pipe) throw std::runtime_error("popen() failed!");
	try {
		while (fgets(buffer, sizeof buffer, pipe) != NULL) {
			result += buffer;
		}
	} catch (...) {
		pclose2(pipe, pid);
		throw;
	}
	pclose2(pipe, pid);
	return result;
}

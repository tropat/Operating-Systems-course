#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include "procinfo.h"

int procinfo(const char* name) {
	uid_t UID=getuid();
	gid_t GID=getgid();
	pid_t PID=getpid();
	pid_t PPID=getppid();
	pid_t PGID=getpgid(PID);

	printf("Name = %s, UID = %d, GID = %d, PID = %d, PPID = %d, PGID = %d\n", name, UID, GID, PID, PPID, PGID);
	return 0;
}
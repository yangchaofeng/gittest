#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <linux/netlink.h>

#define UEVENT_MSG_LEN 4096
struct luther_gliethttp {
    const char *action;
    const char *path;
    const char *subsystem;
    const char *firmware;
	const char *lcd_panel_status;
    int major;
    int minor;
};
static int open_luther_gliethttp_socket(void);
static void parse_event(const char *msg, struct luther_gliethttp *luther_gliethttp);

int main(int argc, char* argv[])
{
    int device_fd = -1;
    char msg[UEVENT_MSG_LEN+2];
    int n;

    device_fd = open_luther_gliethttp_socket();
    printf("device_fd 000 = %d\n", device_fd);

    do {
        while((n = recv(device_fd, msg, UEVENT_MSG_LEN, 0)) > 0) {
            struct luther_gliethttp luther_gliethttp;

            if(n == UEVENT_MSG_LEN)
                continue;

            msg[n] = '\0';
            msg[n+1] = '\0';

            parse_event(msg, &luther_gliethttp);
        }
    } while(1);
}

static int open_luther_gliethttp_socket(void)
{
    struct sockaddr_nl addr;
    int sz = 64*1024;
    int s;

    memset(&addr, 0, sizeof(addr));
    addr.nl_family = AF_NETLINK;
    addr.nl_pid = getpid();
    addr.nl_groups = 0xffffffff;

    s = socket(PF_NETLINK, SOCK_DGRAM, NETLINK_KOBJECT_UEVENT);
    if (s < 0)
        return -1;

    setsockopt(s, SOL_SOCKET, SO_RCVBUFFORCE, &sz, sizeof(sz));

    if (bind(s, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
        close(s);
        return -1;
    }

    return s;
}

static void parse_event(const char *msg, struct luther_gliethttp *luther_gliethttp)
{
    luther_gliethttp->action = "";
    luther_gliethttp->path = "";
    luther_gliethttp->subsystem = "";
    luther_gliethttp->firmware = "";
    luther_gliethttp->major = -1;
    luther_gliethttp->minor = -1;


    printf("========================================================\n");
    while (*msg) {

        //printf("%s\n", msg);

        if (!strncmp(msg, "ACTION=", 7)) {
            msg += 7;
            luther_gliethttp->action = msg;
        } else if (!strncmp(msg, "DEVPATH=", 8)) {
            msg += 8;
            luther_gliethttp->path = msg;
        } else if (!strncmp(msg, "SUBSYSTEM=", 10)) {
            msg += 10;
            luther_gliethttp->subsystem = msg;
        } else if (!strncmp(msg, "FIRMWARE=", 9)) {
            msg += 9;
            luther_gliethttp->firmware = msg;
        } else if (!strncmp(msg, "MAJOR=", 6)) {
            msg += 6;
            luther_gliethttp->major = atoi(msg);
        } else if (!strncmp(msg, "MINOR=", 6)) {
            msg += 6;
            luther_gliethttp->minor = atoi(msg);
        } else if (!strncmp(msg, "panel_status=", 13)) {
			msg += 13;
			luther_gliethttp->lcd_panel_status = msg;
		}

        while(*msg++)
            ;
    }

	#define LCD_PATH "/devices/platform/zte_lcd"
    if (!strncmp(luther_gliethttp->path, LCD_PATH, sizeof(LCD_PATH)) && luther_gliethttp->lcd_panel_status)
	{
		if (!strncmp(luther_gliethttp->lcd_panel_status, "suspend", sizeof("suspend")))
			printf("lcd_panel_status=%s\n", luther_gliethttp->lcd_panel_status);
		else if (!strncmp(luther_gliethttp->lcd_panel_status, "resume", sizeof("resume")))
			printf("lcd_panel_status=%s\n", luther_gliethttp->lcd_panel_status);
	}
		
				//printf("event { '%s', '%s', '%s', '%s', %d, %d }\n",
                  //  luther_gliethttp->action, luther_gliethttp->path, luther_gliethttp->subsystem,
                    //luther_gliethttp->firmware, luther_gliethttp->major, luther_gliethttp->minor);
}

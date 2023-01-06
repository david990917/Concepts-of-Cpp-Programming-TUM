#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

typedef struct {
    int interface_id;
    char ip_address[16];
} router_port_config;

router_port_config port_config;

int main(int argc, char *argv[]) {
    int c;
    while ((c = getopt(argc, argv, "p:")) != -1) {
        switch (c) {
            case 'p':
                sscanf(optarg, "%d%s", &port_config.interface_id, port_config.ip_address);
                break;
            default:
                fprintf(stderr, "Usage: %s [-p interface_id ip_address]\n", argv[0]);
                exit(EXIT_FAILURE);
        }
    }

    printf("DPDK interface id: %d\n", port_config.interface_id);
    printf("IP address: %s\n", port_config.ip_address);

    return 0;
}

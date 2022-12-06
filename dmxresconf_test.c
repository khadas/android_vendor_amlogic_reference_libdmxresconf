#include "libdmxresconf.h"
#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <signal.h>
#include <stdbool.h>
#include <pthread.h>

// // int dmx_res_conf_get_dev_list(const char *app_name, int *dev_no_buf, int size);

int main(int argc, char *argv[])
{

    int *dev_no_buf;
    int size;
    int returnsize;
    int i;
    if (argc < 0) {
        printf("input error\n");
    }
    size = atoi(argv[2]);
    dev_no_buf = malloc(size*sizeof(int));
    returnsize = dmx_res_conf_get_dev_list(argv[1], dev_no_buf, size);
    printf("returnsize %d\n",returnsize);
    for (i = 0; i < returnsize; i++,dev_no_buf++) {
        printf("dev_no_buf[%d]: %d\r\n",i,*dev_no_buf);
    }
    free(dev_no_buf);
}



// struct Dmxcong {
//     int *dev_no_buf;
//     int size;
//     char *appname;
//     int returnsize;
// };


// static void *thread_start(void *arg)
// {
//     struct Dmxcong *dmxconf = (struct Dmxcong *)arg;
//     printf("线程%d 被创建: 线程 ID<%lu>\n", *((int *)arg), pthread_self());
//     dmxconf->returnsize = dmx_res_conf_get_dev_list(arg, dmxconf->dev_no_buf, dmxconf->size);
//     pthread_exit(NULL); //线程终止
// }

// int main(int argc, char *argv[])
// {

//     int *dev_no_buf;
//     int size;
//     struct Dmxcong *dmxconf;
//     int returnsize;
//     int i;
//     pthread_t tid[5];
//     int nums[5] = {0, 1, 2, 3, 4};
//     int j;

//     if (argc < 0) {
//         printf("input error\n");
//     }
//     dmxconf = (struct Dmxcong *)malloc(sizeof(struct Dmxcong));
//     dmxconf->size = atoi(argv[2]);
//     dmxconf->dev_no_buf = (int *)malloc(sizeof(int) * dmxconf->size);
//     dmxconf->appname = argv[1];

//     for (j = 0; j < 5; j++) {
//         pthread_create(&tid[j], NULL, thread_start, dmxconf);
//     }

//     /* 等待线程结束 */
//     for (j = 0; j < 5; j++) {
//        pthread_join(tid[j], NULL);//回收线程
//     }

//     // returnsize = dmx_res_conf_get_dev_list(argv[1], dev_no_buf, size);

//     printf("returnsize %d\n",dmxconf->returnsize);
//     for (i = 0; i < dmxconf->returnsize; i++,(dmxconf->dev_no_buf)++) {
//         printf("dev_no_buf[%d]: %d\r\n",i,*(dmxconf->dev_no_buf));
//     }

//     free(dmxconf);
// }
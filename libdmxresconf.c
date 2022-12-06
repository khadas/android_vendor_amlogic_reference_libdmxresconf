#include "cJSON.h"
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
#include <libdmxresconf.h>
#include <utils/Log.h>
#include <android/log.h>


static pthread_once_t once = PTHREAD_ONCE_INIT;
static cJSON *cjson = NULL;//Store the parsed json

//old demux driver's node
#define demux "/sys/class/stb/demux0_source"

// demux config file path
// #define dmxresconf "/vendor/etc/demuxresource.json"
// #define dmxresconf "/etc/demuxresource.json"
// #define dmxresconf "/system/etc/demuxresource.json"

static char* dmxresconf[] = {"/vendor/etc/demuxresource.json","/etc/demuxresource.json","/system/etc/demuxresource.json"};

//old demux json config
static char *old_demux = "{\"DTVKit\":[0,1,2],\
                                   \"IPTV\":[0,1,2]}";
//new demux json config
static char *new_demux = "{\"DTVKit\":[9,10,11,12,13,14,15,16],\
                                   \"IPTV\":[0,1,2,3,4,5,6,7,8]}";


static int findconfigfile(void)
{
    int i;
    for ( i = 0; i < (sizeof(dmxresconf)/sizeof(dmxresconf[0])); i++ ) {
        if (access(dmxresconf[i],F_OK) == 0) {
            ALOGI("demux config file stored in %s\n", dmxresconf[i]);
            return i;
        }
    }
    return -1;
}

//load file,excute only once
static void loadconffile(void)
{
    struct stat filestat;//get config file information
    char *buf;//save config file information
    int rsize;
    int fd;
    int rsite;
    ALOGI("Loading the configuration File\n");
    rsite = findconfigfile();
    if ( rsite < 0 ) {//if config file not exist
        ALOGI("%s dmx res conf file does not exist!\n", __func__);

        if (access(demux,F_OK) == -1) {//old demux driver node do not exist
            ALOGI("the new demux's attribute node!\n");
            cjson = cJSON_Parse(new_demux);//new_demux convert to cjson
        } else {//old demux driver node exist
            ALOGI("the old demux's attribute node!\n");
            cjson = cJSON_Parse(old_demux);//old_demux convert to cjson
        }

    } else {//if config file exist
        ALOGI("%s dmx res conf file exist!\n", __func__);

        memset(&filestat,0,sizeof(struct stat));
        stat(dmxresconf[rsite], &filestat);//get config file information

        buf = malloc(filestat.st_size);//get config file context
        memset(buf,0,filestat.st_size);

        fd = open(dmxresconf[rsite],O_RDWR);//open config file
        if ( fd < 0 ) {
            ALOGI("%s file does not open!\n", __func__);
        }

        rsize = read(fd,buf,filestat.st_size);//read config file
        if ( rsize < 0 ) {
            ALOGI("%s file does not read!\n", __func__);
        }

        cjson = cJSON_Parse(buf);//convert to cjson
        if ( cjson == NULL ) {
            ALOGI("%s JSON does not get!\n", __func__);
        }

        free(buf);
        close(fd);
        ALOGI("dmux config file exit \n");
    }
}


int dmx_res_conf_get_dev_list(const char *app_name, int *dev_no_buf, int size)
{

    int i;
    int *temp_buf;
    int length;

    ALOGI("%s !\n", __func__);

    pthread_once(&once,loadconffile);//excute only once

    cJSON* TIM = cJSON_GetObjectItem(cjson,app_name);//get app_name key information,return 0 if failure
    if ( TIM == NULL ) {
        ALOGI("%s Object does not get!\n", __func__);
        return 0;
    }

    int TIM_size = cJSON_GetArraySize(TIM);//get app_name Array size
    if ( TIM_size == 0 ) {
        ALOGI("%s Object does not get!\n", __func__);
        return 0;
    }
    length = TIM_size<size? TIM_size:size;//return demux count

    temp_buf = dev_no_buf;//tempority buffer save array
    ALOGI("%s dev_no_buf length : %d\n", __func__,length);

    for (i=0;i<length;i++,temp_buf++) {//app_name Array filled temp_buf
        *temp_buf = cJSON_GetArrayItem(TIM,i)->valueint;
        ALOGI("%s *temp_buf : %d\n", __func__,*temp_buf);
	    ALOGI("dmxresconf *temp_buf : %d\n",*temp_buf);
    }

    return length;

}
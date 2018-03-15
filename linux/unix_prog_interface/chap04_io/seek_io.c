#include "../common/common.h"
#include <fcntl.h> //file control S_IRUSR S_IWUSR S_IXUSR
#include <ctype.h> //c types
#include <sys/stat.h> //stat

#include <string.h> //strlen strncpy strcpy
#include <malloc.h> //malloc
#include <stdlib.h> //strtol
#include <unistd.h> //lseek

typedef off_t offset;

typedef struct _seekio_t {
    offset m_offset;
    bool m_isRead;
    char *m_buf;
    offset m_len;
    char m_filename[MAX_PATH+1];
} seekio_t;

int main(int argc, char *argv[]) {
    int i,j,fd, flags, checker;
    int nReaded, nWritten;
    char opt;
    char *nptr;
    seekio_t st;

    st.m_isRead=0;
    st.m_len=0;
    st.m_filename[0]=0;
    st.m_buf=NULL;

    if(argc != 4) {
        err_exit("usage: %s filename s[NUM] w[str]|r[str]", argv[1]);
    }

    checker=0;
    strncpy(st.m_filename, argv[1], MAX_PATH);
    for(i=2; i<argc; ++i) {
        opt=argv[i][0];
        if(strlen(argv[i]) < 2) {
            err_exit("too less argument:%s", argv[i]);
        }

        switch(opt) {
            case 's':
            case 'S':{
                         checker++;
                         st.m_offset=strtol(&argv[i][1],&nptr, 0);
                         break;
                     }
            case 'w':
            case 'W':{
                         checker++;
                         st.m_isRead=false;
                         st.m_len=strlen(&argv[i][1]);
                         st.m_buf = (char*)malloc(sizeof(char) *(st.m_len+1));
                         strcpy(st.m_buf, &argv[i][1]);
                         break;
                     }
            case 'r':
            case 'R':{
                         checker++;
                         st.m_isRead=true;
                         st.m_len=strtol(&argv[i][1], &nptr, 0);
                         st.m_buf=malloc(sizeof(char) * st.m_len);
                         break;
                     }
            default: {
                         err_exit("error option:%s", argv[i]);
                         break;
                     }
        }
    }

    if(checker != 2) err_exit("argument is not complete");
    flags = st.m_isRead ? O_RDONLY : O_WRONLY | O_CREAT;
    fd = open(st.m_filename, flags, S_IWUSR | S_IRUSR | S_IRGRP | S_IWGRP | S_IWOTH | S_IROTH);
    if(fd < 0) err_exit("%s open failed:\n", argv[1]);
    if(lseek(fd,st.m_offset,SEEK_SET) < 0) {
        err_exit("S%d seek error",st.m_offset);
    } else {
        printf("S%ld seek succeed.\n",st.m_offset);
    }

    j=0;
    if(st.m_isRead) {
        while(j!=st.m_len){
            nReaded=read(fd, st.m_buf+j, st.m_len);
            if(nReaded<0) {
                close(fd);
                free(st.m_buf);
                err_exit("read error");
            } 
            j+=nReaded;
        }
        printf("R%ld:",st.m_len);
        for(i=0; i<st.m_len; ++i) {
            printf("%x",st.m_buf[i]);
        }
        printf("\n");
        fflush(stdout);
    } else {
        while(j!=st.m_len) {
            nWritten=write(fd, st.m_buf+j, st.m_len);
            if(nWritten<0) {
                close(fd);
                free(st.m_buf);
                err_exit("write error");
            }
            j+=nWritten;
        }
        printf("W%s",st.m_buf);
    }
    printf("\n");
    close(fd);
    free(st.m_buf);
    return 0;
}



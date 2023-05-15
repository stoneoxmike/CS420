#ifndef _IPCEX_H_
#define _IPCEX_H_

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 128
#endif


struct ipc_struct {
    int  repeat_val;
    char data[BUFFER_SIZE];
};


#endif

#include "serial.h"

#define DATA_LENGTH 14               //接受的数据位数
#define SERIAL_RECIVER_TRANSFER_TIME  0.001875f
int DataControler::OpenPort(const char *Portname)
{
    int fd;
//    fd = open(Portname,O_RDWR);
    fd = open(Portname,O_RDWR | O_NOCTTY | O_NONBLOCK);
    cout << fd << endl;
    if(-1 == fd)
    {
        printf("The port open error!\n");
        return -1;
    }
    else
    {
        fcntl(fd,F_SETFL,0);   //读取串口的信息
    }
    return fd;
}
int DataControler::configureSerial(int fd){
    struct termios port_set;
    //波特率
    cfsetispeed(&port_set,B115200);
    cfsetospeed(&port_set,B115200);
    //No parity
    port_set.c_cflag &= ~PARENB;         //无奇偶校验
    port_set.c_cflag &= ~CSTOPB;         //停止位:1bit
    port_set.c_cflag &= ~CSIZE;          //清除数据位掩码
    port_set.c_cflag |=  CS8;

    tcsetattr(fd,TCSANOW,&port_set);
    return (fd);
}
void DataControler::sentData(int fd, char sign){
    unsigned char sent_bytes[1];
    sent_bytes[0] = sign;
    write(fd, sent_bytes, 1);
}
void DataControler::sentData(int fd,VisionData &data){


    unsigned char send_bytes[15];

    send_bytes[0] = 0X0a;

    send_bytes[1] = data.X.c[0];
    send_bytes[2] = data.X.c[1];
    send_bytes[3] = data.X.c[2];
    send_bytes[4] = data.X.c[3];


    send_bytes[5] = data.Z.c[0];
    send_bytes[6] = data.Z.c[1];
    send_bytes[7] = data.Z.c[2];
    send_bytes[8] = data.Z.c[3];


    send_bytes[9] = data.angle.c[0];
    send_bytes[10] = data.angle.c[1];
    send_bytes[11] = data.angle.c[2];
    send_bytes[12] = data.angle.c[3];

    send_bytes[13] = data.sign;
    send_bytes[14] = 0xbb;

    write(fd, send_bytes, 15);
}


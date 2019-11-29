#include "printf.h"
typedef char*  va_list;
#define _INTSIZEOF(n)   ((sizeof(n)+sizeof(int)-1) & ~(sizeof(int)-1))
#define va_start(ap,v)  (ap = (va_list)&v + _INTSIZEOF(v))
//#define va_arg(ap,t)    (*(t *)((ap+=_INTSIZEOF(t))- _INTSIZEOF(t)))
#define va_arg(ap,t)    (*(t*)(ap = ap+_INTSIZEOF(t), ap-_INTSIZEOF(t)))
#define va_end(ap)      (ap = va_list(0))

unsigned char hex_tab[]={'0','1','2','3','4','5','6','7',\
                         '8','9','a','b','c','d','e','f'};



static int  out_num(long n, int base,char lead,int maxwidth)
{
    unsigned long m=0;
    char buf[MAX_NUMBER_BYTES], *s = buf + sizeof(buf); //s为buf末尾下一个空间
    int count=0,i=0;


    *--s = '\0';

    if (n < 0){
        m = -n;
    }
    else{
        m = n;
    }

    do{
        *--s = hex_tab[m%base];
        count++;
    }while ((m /= base) != 0);

    if( maxwidth && count < maxwidth){
        for (i=maxwidth - count; i; i--)
            *--s = lead;        //填充前导字符，比如说0
}

    if (n < 0)
        *--s = '-';

    return puts(s);
}


/*reference :   int vprintf(const char *format, va_list ap); */
static int my_vprintf(const char *fmt, va_list ap)
{
    char lead=' ';              //默认前导字符为空格
    int  maxwidth=0;
    int i;
    for(; *fmt != '\0'; fmt++)
    {
       if (*fmt != '%') {       //%是格式的开头
         putchar(*fmt);         //如果没有遇到%则字符按原样输出
         continue;
       }

       lead=' ';                //没处理完一次要复位
       maxwidth=0;

       //format : %08d, %8d,%d,%u,%x,%f,%c,%s
       fmt++;                   //*fmt==%，处理下一个字符
       if(*fmt == '0'){
         lead = '0';
         fmt++;
       }

       //例如%08d 最大宽度就是8
       while(*fmt >= '0' && *fmt <= '9'){
         maxwidth *=10;
         maxwidth += (*fmt - '0');
         fmt++;
        }

       /*正确代码*/
        switch (*fmt){
        case 'd': out_num(va_arg(ap, int),           10,lead,maxwidth); break;
        case 'l': out_num(va_arg(ap, long),          10,lead,maxwidth); break;
        case 'O': out_num(va_arg(ap, unsigned long), 8,lead,maxwidth); break;
        case 'o': out_num(va_arg(ap, unsigned int),  8,lead,maxwidth); break;
        case 'U': out_num(va_arg(ap, unsigned long),10,lead,maxwidth); break;
        case 'u': out_num(va_arg(ap, unsigned int), 10,lead,maxwidth); break;
        case 'X': out_num(va_arg(ap, unsigned long), 16,lead,maxwidth);  break;
        case 'x': out_num(va_arg(ap, unsigned int), 16,lead,maxwidth); break;
        case 'c': putchar(va_arg(ap, int   )); break;
        case 's': puts(va_arg(ap, char *)); break;
        default:putchar(*fmt);break;
            }
    }
    return 0;
}


//reference :  int printf(const char *format, ...);
// 编译与ARM不同 强制将前四个参数放在寄存器
int printf(char unused1,char unused2,char unused3,char unused4, const char *fmt, ...)
//int printf(const char *fmt, ...)
{
    va_list ap;
    int i=_INTSIZEOF(fmt);
    ap=(char *)&fmt;
    ap+=i;
    //va_start(ap, fmt);
    my_vprintf(fmt, ap);
    ap=(char *)(0);
    //va_end(ap);
    return 0;
}






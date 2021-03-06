#include "tools.h"

char *strupr(char *str){
    char *p = str;
    while (*p != '\0'){
        if(*p >= 'a' && *p <= 'z'){
            *p -= 0x20;
        }
        p++;
    }
    return str;
}

char *urldecode(char *p){
    char *pm = p;
    register i = 0;
    while(*(p+i)){
        if ((*p=*(p+i)) == '%'){
            *p=*(p+i+1) >= 'A' ? ((*(p+i+1) & 0XDF) - 'A') + 10 : (*(p+i+1) - '0');
            *p=(*p) * 16;
            *p+=*(p+i+2) >= 'A' ? ((*(p+i+2) & 0XDF) - 'A') + 10 : (*(p+i+2) - '0');
            i+=2;
        } else if (*(p+i)=='+'){
            *p=' ';
        }
        p++;
    }
    *p='\0';
    return pm;
}

int explode(char *string,char explode,dlist *dlist){
    int strlength = strlen(string);
    int markNum = 0;
    int i = 0;
    for (i = 0;i < strlength;){
        if (string[i++] == explode){
            markNum++;
        }     
    }

    int ereryStrLen[markNum];
    int strlen = 0;
    markNum = 0;
    for (i = 0;i < strlength;){
        strlen++;
        if ((i + 1) == strlength){
            ereryStrLen[markNum++] = strlen;
        }
        if (string[i++] == explode){
            ereryStrLen[markNum++] = strlen - 1;
            strlen = 0;
            continue;
        }
    }
    for (i = 0;i < markNum;i++){
        char *explodeStr = (char *) malloc(ereryStrLen[i] + 1);
        for (strlen = 0;strlen < ereryStrLen[i];strlen++){
            explodeStr[strlen] = *string;
            string++;
        }
        explodeStr[strlen] = '\0';
        string++;
        if (0 != dlistInsert(dlist,NULL,explodeStr)){
            return -1;    
        }
    }
    return 0;
}

int countChar(const char *string,char c){
    int i = 0,count = 0;
    while(string[i] != '\0'){
        if (string[i++] == c){
            count++;    
        }
    }    
    return count;
}

int getDateByType(int type){
    struct tm *datetime;
    time_t nowTime;
    time(&nowTime);
    datetime = localtime(&nowTime);
    int timeNum;
    switch(type){
        case 0 : timeNum = datetime->tm_year + 1900;
                 break;
        case 1 : timeNum = datetime->tm_mon + 1;
                 break;
        case 2 : timeNum = datetime->tm_mday;
                 break;
        case 3 : timeNum = datetime->tm_hour;
                 break;
        case 4 : timeNum = datetime->tm_min;
                 break;
        case 5 : timeNum = datetime->tm_sec;
                 break;
    }
    return timeNum;
}

char *getDatetime(){
    int year  = _YEAR;
    int mon   = _MON;
    int day   = _DAY;
    int hour  = _HOUR;
    int min   = _MIN;
    int sec   = _SEC;
    char *datetime = (char *)malloc(20*sizeof(char));
    sprintf(datetime,"%d-%d-%d %d:%d:%d",year,mon,day,hour,min,sec);
    return datetime;
}

char *getDate(){
    int year  = _YEAR;
    int mon   = _MON;
    int day   = _DAY;
    int hour  = _HOUR;
    int min   = _MIN;
    int sec   = _SEC;
    char *date = (char *)malloc(20*sizeof(char));
    sprintf(date,"%d-%d-%d",year,mon,day);
    return date;
}


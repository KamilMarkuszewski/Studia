#ifndef _TASK_H_
#define _TASK_H_

struct Proces 
{ 
    int index;// 
    int p;//co� jak kiedy� by�o a teraz to p- wykonywane odpowiednia ilosc jednostek czasu 
    int w;//priorytet/waga 
    float d;//termin wykonania zadania. 
};

#endif //_TASK_H_
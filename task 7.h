#ifndef TASK_7_H_INCLUDED
#define TASK_7_H_INCLUDED



typedef struct request
{
   int id;
   double spawn_time;
   double enter_time;
   double wait_time;
   double leave_time;
   double process_time;
}request;

typedef struct queue
{
    request *req;
    struct queue *next;
}queue;


typedef struct AO
{
    double wait_time;
    int req_count;
    struct request *req;

}AO;

request *new_r(int id);

void push(queue **ptr,request **rqst);

request *poplast(queue **Q);

void var_1(int N);

void var_2 ();






#endif // TASK_7_H_INCLUDED

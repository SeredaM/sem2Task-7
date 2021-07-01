#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "Task 7.h"

const a1=0, a2=2;///T1
const b1=0, b2=2;///T2
const c1=0, c2=4;///T3

request *new_r(int id)
{
    request *new_request=(request*)malloc(sizeof(request));
    new_request->id=id;
    new_request->wait_time=0;
    new_request->process_time=0;

    return new_request;
}
void push(queue **ptr,request **rqst)
{
    queue *tmp = (queue*)malloc(sizeof(queue));

    tmp->req=*rqst;
    tmp->next=*ptr;
    *ptr = tmp;
}
 request *poplast(queue **Q)
{
  queue *prev=NULL;
  request *tmpr;
  queue *tmp=*Q;
  while (tmp->next != NULL)
  {
      prev=tmp;
      tmp=tmp ->next;
  }
  if (prev==NULL)
  {
      tmpr=tmp->req;
      *Q=NULL;
      free(tmp);
      return tmpr;
  }
  prev->next=NULL;
  tmpr=tmp->req;
  free(tmp);
  return tmpr;

}

void var_1(int N)
{
    double t=0;
    double f1=999999,f2=999999,sp=a1+(a2-a1)*(double)rand()/RAND_MAX,s=t+sp;
    AO *AO1 = (AO*)malloc(sizeof(AO));
    AO *AO2=(AO*)malloc(sizeof(AO2));
    queue *Q1=NULL;
    queue *Q2=NULL;
    queue *DONE = NULL;
    AO1->req=NULL;
    AO1->wait_time=0;
    AO2->req=NULL;
    AO2->wait_time=0;
    double tick,skip,max_wait=0,av_wait=0;
    int Q1_fl=0,Q2_fl=0,rq_fl=0,max_id;
    queue *ptr;
    request *tmpr;

    int id=1,k=0;
    while (id<=N)
    {

     Q1_fl=0;
     Q2_fl=0;
     rq_fl=0;
      tick=s;
    if(f2<tick)
        tick=f2;
    if(f1<tick)
        tick=f1;

    if (fabs(tick-f1)<0.0001)
        Q1_fl++;
    if (fabs(tick-f2)<0.0001)
        Q2_fl++;
    if (fabs(tick-s)<0.0001)
        rq_fl++;

    if (Q1_fl==1)
        printf("AO1 request finished!\n");
    if (Q2_fl==1)
        printf("AO2 request finished!\n");
    ptr=Q1;
    if (ptr != NULL)
    {
        while (ptr->next!=NULL)
        {
          ptr->req->wait_time+=tick-t;
          ptr = ptr -> next;
        }

    }
    ptr=Q2;
    if (ptr != NULL)
    {
        while (ptr->next!=NULL)
        {
          ptr->req->wait_time+=tick-t;
          ptr = ptr -> next;
        }
     ptr->req->wait_time+=tick-t;

    }
    if (AO1->req==NULL)
        AO1->wait_time+=tick-t;
    else
        AO1->req->process_time+=tick-t;
    if (AO2->req==NULL)
        AO2->wait_time+=tick-t;
    else
        AO2->req->process_time+=tick-t;
    ///добавили время ожидания
    t=tick;
    if (rq_fl==1)
    {
        tmpr=new_r(id);
        tmpr->enter_time=t;
        tmpr->spawn_time=sp;
        sp=a1+(a2-a1)*(double)rand()/RAND_MAX;
        s=t+sp;
        id++;

       skip=(double)rand()/RAND_MAX;
       if (skip<0.4)
       {
        printf("New request in Q2!\n\n");
            push(&Q2,&tmpr);
            if (f2==999999)
            {
                AO2->req=poplast(&Q2);
                f2=t+c1+(c2-c1)*(double)rand()/RAND_MAX;
            }
       }
       else
       {   printf("New request in Q1!\n\n");
           push(&Q1,&tmpr);
           if (f1==999999)
            {
                AO1->req=poplast(&Q1);
                f1=t+b1+(b2-b1)*(double)rand()/RAND_MAX;
            }
       }


    }
    ///добавили новую заявку очередь
    if (Q1_fl==1)
    {
      if (AO2->req == NULL)
      {
          AO2->req=AO1->req;
          f1=999999;
          f2=t+c1+(c2-c1)*(double)rand()/RAND_MAX;
          AO1->req=NULL;
      }
      else
      {
          tmpr=AO1->req;
          push(&Q2,&tmpr);
          f1=999999;
          AO1->req=NULL;
      }
      if (Q1!=NULL)
      {
      AO1->req=poplast(&Q1);
      f1=t+b1+(b2-b1)*(double)rand()/RAND_MAX;
      }
    }
    ///обработали заявку в AO1
    if (Q2_fl==1)
    {
      if (AO2->req->wait_time>max_wait)
      {
          max_wait = AO2->req->wait_time;
          max_id = AO2->req->id;
      }
      AO2->req->leave_time=t;
      tmpr=AO2->req;
      push(&DONE,&tmpr);
      if (Q2!=NULL)
      {
      AO2->req=poplast(&Q2);
      f2=t+c1+(c2-c1)*(double)rand()/RAND_MAX;
      }
      else
      {
      AO2->req=NULL;
      f2=999999;
      }
    ///обработали заявку в AO2
    }
     printf("Queue 1:");
     if (Q1==NULL)
        printf("empty\n");
     else
     {
         ptr = Q1;
         while (ptr->next != NULL)
         {
            printf("%d ",ptr->req->id);
            ptr=ptr->next;
         }
         printf("%d ",ptr->req->id);
         printf("\n");

     }
     printf("Queue 2:");
     if (Q2==NULL)
        printf("empty\n");
     else
     {
         ptr = Q2;
         while (ptr->next != NULL)
         {
            printf("%d ",ptr->req->id);
            ptr=ptr->next;
         }
         printf("%d ",ptr->req->id);
         printf("\n",f2-t);

     }
     if (AO1->req!=NULL)
     {
     printf("In AO1:%d \n",AO1->req->id);
     }
     else
     printf("In AO1: NONE \n");
     if (AO2->req!=NULL)
     {
     printf("In AO2:%d \n********************\n",AO2->req->id);
     }
     else
     printf("In AO2: NONE \n********************\n");
    }

ptr = DONE;
if (ptr!=NULL)
{
    printf("These are processed requests \n");
         while (ptr->next != NULL)
         {
            printf("id: %d enter time: %lf wait time: %lf exit time: %lf process time: %lf spawn time: %lf\n",ptr->req->id,ptr->req->enter_time,ptr->req->wait_time,ptr->req->leave_time,ptr->req->process_time,ptr->req->spawn_time);
            av_wait=av_wait+ptr->req->wait_time;
            ptr=ptr->next;
            k++;
         }
         k++;
         av_wait=av_wait+ptr->req->wait_time;
         av_wait=av_wait/k;
         printf("id: %d enter time: %lf wait time: %lf exit time: %lf process time: %lf spawn time: %lf\n ",ptr->req->id,ptr->req->enter_time,ptr->req->wait_time,ptr->req->leave_time,ptr->req->process_time,ptr->req->spawn_time);
         printf("\n");
         printf("Max wait time: %lf for id %d\n",max_wait,max_id);
         printf("Average wait time: %lf \n",av_wait);
         printf("AO1 inactive time: %lf \n",AO1->wait_time);
         printf("AO2 inactive time: %lf \n",AO2->wait_time);
         printf("Total requests entered: %d \n",id-1);


}
else
{
    printf("No processed requests");
}

}

void var_2 ()
{
   double t=0;
    double f1=999999,f2=999999,sp=a1+(a2-a1)*(double)rand()/RAND_MAX,s=t+sp;
    AO *AO1 = (AO*)malloc(sizeof(AO));
    AO *AO2=(AO*)malloc(sizeof(AO2));
    queue *Q1=NULL;
    queue *Q2=NULL;
    queue *DONE = NULL;
    AO1->req=NULL;
    AO1->wait_time=0;
    AO1->req_count=0;
    AO2->req=NULL;
    AO2->wait_time=0;
    AO2->req_count=0;
    double tick,skip,max_wait=0,av_wait=0;
    int Q1_fl=0,Q2_fl=0,rq_fl=0,max_id;
    queue *ptr;
    request *tmpr;

    int id=1,p=0,k=0,l;
    while (p<1000)
    {

     Q1_fl=0;
     Q2_fl=0;
     rq_fl=0;
      tick=s;
    if(f2<tick)
        tick=f2;
    if(f1<tick)
        tick=f1;

    if (fabs(tick-f1)<0.0001)
        Q1_fl++;
    if (fabs(tick-f2)<0.0001)
        Q2_fl++;
    if (fabs(tick-s)<0.0001)
        rq_fl++;


    ptr=Q1;
    if (ptr != NULL)
    {
        while (ptr->next!=NULL)
        {
          ptr->req->wait_time+=tick-t;
          ptr = ptr -> next;
        }

    }
    ptr=Q2;
    if (ptr != NULL)
    {
        while (ptr->next!=NULL)
        {
          ptr->req->wait_time+=tick-t;
          ptr = ptr -> next;
        }
     ptr->req->wait_time+=tick-t;

    }
    if (AO1->req==NULL)
        AO1->wait_time+=tick-t;
    else
        AO1->req->process_time+=tick-t;
    if (AO2->req==NULL)
        AO2->wait_time+=tick-t;
    else
        AO2->req->process_time+=tick-t;
    ///добавили время ожидания
    t=tick;
    if (rq_fl==1)
    {
        tmpr=new_r(id);
        tmpr->enter_time=t;
        tmpr->spawn_time=sp;
        sp=a1+(a2-a1)*(double)rand()/RAND_MAX;
        s=t+sp;
        id++;

       skip=(double)rand()/RAND_MAX;
       if (skip<0.4)
       {

            push(&Q2,&tmpr);
            if (f2==999999)
            {
                AO2->req=poplast(&Q2);
                f2=t+c1+(c2-c1)*(double)rand()/RAND_MAX;
            }
       }
       else
       {
           push(&Q1,&tmpr);
           if (f1==999999)
            {
                AO1->req=poplast(&Q1);
                f1=t+b1+(b2-b1)*(double)rand()/RAND_MAX;
            }
       }


    }
    ///добавили новую заявку очередь
    if (Q1_fl==1)
    {
      AO1->req_count+=1;
      if (AO2->req == NULL)
      {
          AO2->req=AO1->req;
          f1=999999;
          f2=t+c1+(c2-c1)*(double)rand()/RAND_MAX;
          AO1->req=NULL;
      }
      else
      {
          tmpr=AO1->req;
          push(&Q2,&tmpr);
          f1=999999;
          AO1->req=NULL;
      }
      if (Q1!=NULL)
      {
      AO1->req=poplast(&Q1);
      f1=t+b1+(b2-b1)*(double)rand()/RAND_MAX;
      }
    }
    ///обработали заявку в AO1
    if (Q2_fl==1)
    { p++;
      AO2->req_count+=1;
      if (AO2->req->wait_time>max_wait)
      {
          max_wait = AO2->req->wait_time;
          max_id = AO2->req->id;
      }
      AO2->req->leave_time=t;
      tmpr=AO2->req;
      push(&DONE,&tmpr);
      if (Q2!=NULL)
      {
      AO2->req=poplast(&Q2);
      f2=t+c1+(c2-c1)*(double)rand()/RAND_MAX;
      }
      else
      {
      AO2->req=NULL;
      f2=999999;
      }
      if (p%100==0)
      {
ptr = DONE;
if (ptr!=NULL)
{
      printf("\n*********************\n");
         while (ptr->next != NULL)
         {
            av_wait+=ptr->req->wait_time;
            ptr=ptr->next;
            k++;
         }
         k++;
         av_wait=(av_wait+ptr->req->wait_time)/k;
         k=0;
         printf("Max wait time: %lf for id %d\n",max_wait,max_id);
         printf("Average wait time: %lf \n",av_wait);
         ptr=Q1;
         l=0;
         if (ptr!=NULL)
         {
         while (ptr->next != NULL)
         {
            ptr=ptr->next;
            l++;
         }
         l++;
         }
         printf("Queue 1 length: %d\n",l);
          ptr=Q2;
          l=0;
         if (ptr!=NULL)
         {
         while (ptr->next != NULL)
         {
            ptr=ptr->next;
            l++;
         }
         l++;
         }
         printf("Queue 2 length: %d\n",l);
         printf("Total requests entered: %d \n",id-1);


}
else
{
    printf("\n*********************\n");
    printf("No processed requests\n");
}
      }
    }
  }
  printf("\n*********************\n");
  printf("AO1 inactive time: %lf \n",AO1->wait_time);
  printf("AO1 processed %d requests \n",AO1->req_count);
  printf("AO2 inactive time: %lf \n",AO2->wait_time);
  printf("AO2 processed %d requests \n",AO2->req_count);
  printf("Total time: %lf \n",t);



}

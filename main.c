#include <stdio.h> // for printf, scanf, puts, NULL
#include <pthread.h> // for pthread types
#include <unistd.h> // for sleep()
#include <sys/types.h> // for pthread types
#include <stdbool.h> // for bool type
#include <regex.h> // for regular expressions POSIX
#include <stdlib.h> // for malloc() & free()
#include <string.h> // for strlen(), memcpy() & memset()
#include <stdlib.h> // for srand, rand
#include <time.h> // for time()

#define NUM_THREADS 3

pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex3 = PTHREAD_MUTEX_INITIALIZER;

pthread_mutex_t * mutexes[NUM_THREADS] = {&mutex1,&mutex2,&mutex3};

int busy[NUM_THREADS] = { 0 };
int counter = 0;

void exitProgram();
void setbusy(int number);
void * foo(void * pArgs);

int main(int argc, char * argv[])
{
  printf("entered main\n");
  pthread_t threads[NUM_THREADS] = { 0 };
  printf("after threads\n");
  int pthreads[NUM_THREADS] = { 1,2,3 };

  int creator;
  printf("after creator\n");

  for (creator = 0;creator < NUM_THREADS;creator++)
    {
      printf("in for iteration:%d\n",creator+1);
      if(!pthread_create(&(threads[creator]),0,foo,(void*)(&(pthreads[creator]))))
        {
          perror("pthread_create");
        }
      printf("after pthread_create\n");
    }
  for (creator = 0;creator < NUM_THREADS;creator++)
    {
      printf("threads element #%d is %d\n",creator,(threads[creator]));
    }
  printf("after for\n");
  setbusy(1);
  printf("after setbusy 1 0\n");
  setbusy(2);
  printf("after setbusy 2 0\n");
  setbusy(1);
  printf("after setbusy 1 1\n");
  setbusy(2);
  printf("after setbusy 2 1\n");
  setbusy(3);
  printf("after setbusy 3 0\n");
  setbusy(1);
  printf("after setbusy 1 2\n");
  setbusy(2);
  printf("after setbusy 2 2\n");
  setbusy(3);
  printf("after setbusy 3 1\n");
  printf("after exitProgram\n");
  exitProgram();
  //sleep(15);
  for (creator = 0;creator < NUM_THREADS;creator++)
    {
      pthread_join(threads[creator],0);
    }

  setbusy(2);
  printf("after setbusy 2 3\n");
  setbusy(3);
  printf("after setbusy 3 2\n");
  setbusy(1);
  printf("after setbusy 1 3\n");

  printf("right before last thing in main\n");
  return 0;
}

void exitProgram()
{
  printf("entered exitProgram\n");
  int i;
  printf("after i in exitProgram\n");
  for(i = 0; i < NUM_THREADS ; i++)
    {
      pthread_mutex_lock( (mutexes[i]) );
      printf("for iteration#%d in exitProgram\n",i+1);
      printf("current busy[%d] state: %d\n",i,busy[i]);
      busy[i] = 2;
      printf("new busy[%d] state: %d\n",i,busy[i]);
      pthread_mutex_unlock( (mutexes[i]) );
    }
}

void setbusy(int number)
{
  if(number == 1)
    {
      pthread_mutex_lock( &mutex1 );
      if(busy[number-1] == 2)
        {
          printf("end signal as been sent\n");
          printf("cannot order again %d\n",number);
          pthread_mutex_unlock( &mutex1 );
          return;
        }
      printf("entered setbusy\n");
      printf("number: %d\n",number);
      sleep(1);
      printf("number: %d\n",number);
      busy[number-1] = ((busy[number-1] == 0)?1:0);
      pthread_mutex_unlock( &mutex1 );
    }
  if(number == 2)
    {
      pthread_mutex_lock( &mutex2 );
      if(busy[number-1] == 2)
        {
          printf("end signal as been sent\n");
          printf("cannot order again %d\n",number);
          pthread_mutex_unlock( &mutex2 );
          return;
        }
      printf("entered setbusy\n");
      printf("number: %d\n",number);
      sleep(1);
      printf("number: %d\n",number);
      busy[number-1] = ((busy[number-1] == 0)?1:0);
      pthread_mutex_unlock( &mutex2 );
    }
  if(number == NUM_THREADS)
    {
      pthread_mutex_lock( &mutex3 );
      if(busy[number-1] == 2)
        {
          printf("end signal as been sent\n");
          printf("cannot order again %d\n",number);
          pthread_mutex_unlock( &mutex3 );
          return;
        }
      printf("entered setbusy\n");
      printf("number: %d\n",number);
      sleep(1);
      printf("number: %d\n",number);
      busy[number-1] = ((busy[number-1] == 0)?1:0);
      pthread_mutex_unlock( &mutex3 );
    }
}

int getbusy(int number)
{
  int _ReturnVal = 0;

  if(number == 1)
    {
      pthread_mutex_lock( &mutex1 );
      printf("entered getbusy\n");
      printf("number: %d\n",number);
      _ReturnVal = busy[number-1];
      pthread_mutex_unlock( &mutex1 );
    }
  if(number == 2)
    {
      pthread_mutex_lock( &mutex2 );
      printf("entered getbusy\n");
      printf("number: %d\n",number);
      _ReturnVal = busy[number-1];
      pthread_mutex_unlock( &mutex2 );
    }
  if(number == 3)
    {
      pthread_mutex_lock( &mutex3 );
      printf("entered getbusy\n");
      printf("number: %d\n",number);
      _ReturnVal = busy[number-1];
      pthread_mutex_unlock( &mutex3 );
    }
  return _ReturnVal;
}

void * foo(void * pArgs)
{
  int thread_number = *(int*)pArgs;
  printf("number:%d\n",thread_number);
  printf("entered foo\n");
  printf("number: %d\n",thread_number);
  while (true)
    {
      printf("entered while in foo\n");
      int check = getbusy(thread_number);
      printf("after getbusy in while in foo\n");
      printf("after while in while in foo\n");
      printf("number: %d\n",thread_number);
      printf("########################check state is: %d\n",check);

      if (check == 1)
      {
        printf("number:%d\n",thread_number);
        printf("after printf args\n");
        setbusy(thread_number);
        printf("after setbusy\n");
      }
      if (check == 2)
      {
        printf("\n\nclose thread %d\n\n",thread_number);
        pthread_exit(0);
      }
      if (check == 0)
      {
        printf("idling\n");
        sleep(1);
      }
    }
  return 0;
}

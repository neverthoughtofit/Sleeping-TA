#include <stdio.h> 
#include <stdlib.h> 
#include <string.h> // memset 
#include <pthread.h> // pthread_t, pthread_create, pthread_join 
#include <semaphore.h> // sem_init, sem_wait, sem_post 
#include <time.h> 
 
#define NUM_SEAT 3 
#define SLEEP_MAX 5 
  
//semaphores 
sem_t sem_stu; 
sem_t sem_ta; 
  
//sem_t mutex; 
pthread_mutex_t mutex; 
  
int waiting_room_chairs[3]; //number of chairs in waiting area 
int number_students_waiting = 0; //number of waiting students 
int next_seat = 0; 
int next_teach = 0; 
 
void rand_sleep(void); 
void* stu_process(void* stu_id); 
void* ta_process(); 
  
int main(){ 

  	//thread(s) 
 	pthread_t *students; 
 	pthread_t ta;
	   	 
    int* student_id; 
    int total_student; 
 	 
    int i; 
 
    //get number of students from user 
    printf("                                 Enter the number of Student Programming  -- > "); 
    scanf("%d", &total_student); 


    if (total_student>0)
    {
     	//initialize 
 	students = (pthread_t*)malloc(sizeof(pthread_t) * total_student); 
 	student_id = (int*)malloc(sizeof(int) * total_student); 
  	memset(student_id, 0, total_student); 

  	sem_init(&sem_stu,0,0); 
 	sem_init(&sem_ta,0,1); 
 	 
 	//set random 
 	srand(time(NULL)); 
  
 	//sem_init(&mutex,0,1); 
 	pthread_mutex_init(&mutex,NULL); 
  
 	//create thread 
 	pthread_create(&ta,NULL,ta_process,NULL); 
 
    //create threads 
    for(i=0; i<total_student; i++) 
    { 
 	student_id[i] = i+1; 
 	pthread_create(&students[i], NULL, stu_process, (void*) &student_id[i]); 
    }  

 	pthread_join(ta, NULL); 
 	 
    for(i=0; i<total_student;i++) 
    { 
 	pthread_join(students[i],NULL); 
    }	
    }
     else
    {
    printf ("                                     There is no Student, TA is Sleeping");
    exit(-1);
    }

 
 	 
return 0; 
} 
// Student Progress Block  
void* stu_process(void* stu_id) 
{ 
    int id = *(int*)stu_id; 
 	printf("                                  Student -> %d is Visiting TA office for Doubts\n",id);		 
 	 
 	while(1) 
 	{ 
 		rand_sleep(); 
  
 		//sem_wait(&mutex); 
 		pthread_mutex_lock(&mutex); 
    if(number_students_waiting < NUM_SEAT)	 
    {
 	waiting_room_chairs[next_seat] = id; 
 	number_students_waiting++; 
 			 
 	printf("                                  Student %d is waiting in the chair at hallway\n",id); 
 	printf("                      Waiting students : ( 1 ) Student - %d ( 2 ) Student - %d ( 3 ) Student - %d\n",waiting_room_chairs[0],waiting_room_chairs[1],waiting_room_chairs[2]); 
	next_seat = (next_seat+1) % NUM_SEAT; 
		 
	//sem_post(&mutex); 
 	pthread_mutex_unlock(&mutex); 
 	 
 	//wakeup ta 
 	sem_post(&sem_stu); 
 	sem_wait(&sem_ta); 
} 
else //no more waiting_room_chairs
   { 
 	//sem_post(&mutex); 
 	pthread_mutex_unlock(&mutex); 
 			 
 	printf("\n    No more Chairs. Student %d  will be back later\n",id);		 
   } 
 }				 
} 
 
// TA Progress Block 
void* ta_process() 
{ 
 	while(1) 
 	{ 
 		sem_wait(&sem_stu);	 
 		 
 		//sem_wait(&mutex); 
 		pthread_mutex_lock(&mutex); 
 		 
 		printf("\n    TA is teaching student -> %d\n",waiting_room_chairs[next_teach]);	 
 		waiting_room_chairs[next_teach]=0; 
 		number_students_waiting--; 
 		 
 		printf("                      Waiting students : ( 1 ) Student - %d ( 2 ) Student - %d ( 3 ) Student - %d\n",waiting_room_chairs[0],waiting_room_chairs[1],waiting_room_chairs[2]
		 ); 
 		next_teach = (next_teach + 1) % NUM_SEAT; 
 		 
 		rand_sleep(); 
 
 
 		printf("    Teaching finish.\n");	 
 
 
 		//sem_post(&mutex); 
 		pthread_mutex_unlock(&mutex); 
 
 
 		sem_post(&sem_ta); 
 	}	 
 } 
 
 
 void rand_sleep(void){ 
 	int time = rand() % SLEEP_MAX + 1; 
 	sleep(time); 
 }

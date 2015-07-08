#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

pthread_mutex_t office_mutex;
pthread_mutex_t question_mutex;
pthread_mutex_t waiting_mutex;
pthread_cond_t cond_empty, cond_full;
int roomCapacity;
int currentStudent = -1;
int studentWaiting = 0;
int qInProgress = 0;
int profDone = 1;
int qStarted = 0;
int qAnswered = 0;
pthread_mutex_t qStarted_mutex;
pthread_mutex_t qAnswered_mutex;

struct student_struct {
  pthread_t id; /* thread id */
  int idx; /* thread index (0 .. p-1) */
  int numq;
};

void enterOffice(struct student_struct* stud){
  int flag = 0;

  while(!flag){
    pthread_mutex_lock(&office_mutex);
    if(roomCapacity > 0){
      printf("Student %d enters the office.\n", stud->idx);
      roomCapacity--;
      flag = 1;
    }
    pthread_mutex_unlock(&office_mutex);
  }
}

void leaveOffice(struct student_struct* stud){
  pthread_mutex_lock(&office_mutex);
  roomCapacity++;
  pthread_mutex_unlock(&office_mutex);
  printf("Student %d leaves the office.\n", stud->idx);
}

void QuestionStart(struct student_struct* stud){
  int flag = 0;

  while(!flag){  
    pthread_mutex_lock(&qStarted_mutex);
    pthread_mutex_lock(&qAnswered_mutex);
    if(!qStarted){
      currentStudent = stud->idx;
      qStarted = 1;
      qAnswered = 0;      
      flag = 1;
      printf("Student %d asks a question.\n", stud->idx);
    }
    pthread_mutex_unlock(&qAnswered_mutex);
    pthread_mutex_unlock(&qStarted_mutex);
  }
}

void QuestionDone(struct student_struct* stud){
  int flag = 0;

  while(!flag){
    pthread_mutex_lock(&qStarted_mutex);
    pthread_mutex_lock(&qAnswered_mutex);
    if(qAnswered){
      qStarted = 0;
      qAnswered = 0;
      printf("Student %d is satisfied.\n", stud->idx);
      flag = 1;
    }
    pthread_mutex_unlock(&qAnswered_mutex);
    pthread_mutex_unlock(&qStarted_mutex);
  }
}

void AnswerStart(){
  int flag = 0;

  while(!flag){
    pthread_mutex_lock(&qStarted_mutex);
    pthread_mutex_lock(&qAnswered_mutex);
    if(qStarted && !qAnswered){
      printf("Professor starts to answer question for student %d.\n", currentStudent);
      flag = 1;
    }
    pthread_mutex_unlock(&qAnswered_mutex);
    pthread_mutex_unlock(&qStarted_mutex);
  }
}

void AnswerDone(){
  int flag = 0;

  while(!flag){
    pthread_mutex_lock(&qAnswered_mutex);
    if(!qAnswered){
      qAnswered = 1;
      printf("Professor is done with answer for student %d.\n", currentStudent);
      flag = 1;
    }
    pthread_mutex_unlock(&qAnswered_mutex);
  }
}

void* professor(){
  for(;;){
    AnswerStart();
    AnswerDone();
  }
}

void* student(void* arg){
  struct student_struct* stud = (struct student_struct*)arg;
  int i;

  //Enter Office
  enterOffice(stud);

  //Ask Questions
  for(i=0; i<stud->numq; i++){
    QuestionStart(stud);
    QuestionDone(stud);
  }

  //Exit Office
  leaveOffice(stud);

  return 0;
}

int main(int argc, char *argv[]){

  int i;
  int numStudents;
  struct student_struct* students;
  pthread_t prof_thread;

  //Read in command line args and initialize variables
  if(argc != 3){
    printf("USAGE:\n\t./task1_3.c <# of students> <room capacity>\n");
    return 1;
  }

  numStudents = atoi(argv[1]);
  roomCapacity = atoi(argv[2]);
  students = (struct student_struct*)malloc(numStudents*sizeof(struct student_struct));
  pthread_mutex_init(&office_mutex, NULL);
  pthread_mutex_init(&question_mutex, NULL);
  pthread_mutex_init(&qStarted_mutex, NULL);
  pthread_mutex_init(&qAnswered_mutex, NULL);

  pthread_create(&prof_thread, NULL, professor, NULL);

  //Create a thread for each student
  for(i=0; i<numStudents; i++){
    students[i].idx = i;
    students[i].numq = i%4 + 1;

    pthread_create(&students[i].id, NULL, student, &students[i]);
  }

  //Wait for each student thread to complete before continueing
  for(i=0; i<numStudents; i++) {
    pthread_join(students[i].id, 0);
  }

  pthread_cancel(prof_thread);

  printf("---- End Simulation ----\n");

  return 0;
}


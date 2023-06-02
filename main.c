#include "../eom.c"
#include "../formation.c"
#include "../scas.c"
...
#include "../col_avoid.c" 
#include "../wpt_follow.c"
...
#include "litmus.h"  //Include the LITMUS^RT API

#define PERIOD50             20  //50hz -> period = 20 ms
#define RELATIVE_DEADLINE50  20
...
#define NUM_THREADS          13 

//=ff======================================
//The real-time thread program, that will invoke job().
void* rt_thread_eom(...);  
void* rt_thread_scas(...);  
void* rt_thread_col_avoid(...);  
void* rt_thread_wpt_follow(...);  
void* rt_thread_ter_follow(...);  
//=ff======================================
//Declare the periodically invoked job. 
job_eom(...);  
job_scas(...);  
job_col_avoid(...);  
job_wpt_follow(...);  
...
//=ff=====================================

//main program
int main(...)
{
   struct thread_context ctx[NUM_THREADS];
   pthread_t task[NUM_THREADS];

//The task is in background mode upon startup. 
//1) Command line paramter parsing would be done here.      
//2) Work environment (e.g., global data structures, 
//   file data, etc.) would be setup here.
//... 
//3) Initialize LITMUS^RT.
//   Task parameters will be specified per thread.
   init_litmus();
 
//4) Launch threads.
   pthread_create(... rt_thread_eom, ...);	

//...etc  
//5) Wait for RT threads to terminate.
   for (i = 0; i < NUM_THREADS; i++)
      pthread_join(...);
 
   return 0;
}
//=ff============================================
void* rt_thread_eom(...){
//...
   init_rt_task_param(...);   //Set up task parameters 
   ...
//1) Initialize real-time settings.
   CALL( init_rt_thread() );
   CALL( set_rt_task_param(...) );
//2) Transition to real-time mode.
   CALL( task_mode(LITMUS_RT_TASK) );
//The task is now executing as a real-time task, init quad rotor stuff
   qr_init(...);   
//3) Invoke real-time jobs.
   do {
//Wait until the next job is released. 
      sleep_next_period();
//Invoke job. 
      do_exit = job_eom();  
   } while (!do_exit);
//4) Transition to background mode.
   CALL( task_mode(BACKGROUND_TASK) );
   return NULL;
}
void* rt_thread_scas(...) {  
//... 
   do_exit = job_scas();  
//...
}
void* rt_thread_col_avoid(...) { 
//... 
   do_exit = job_col_avoid();  
//...
}
void* rt_thread_wpt_follow(void *tcontext) {  
//...
   do_exit = job_wpt_follow();  
//...
}

//=ff============================
int job_eom(...) 
{ 
//Do real-time eom calculation  
//update simulation time 
   qrstate.t += DT;
   qr_nextstate(...);  //eom.c 
   if (creset1==1) 
   {
      qr_init(...);  //eom.c 
//...
      creset1=0; 
   }
//...
//calculate formation keeping
   if (cformation1==1) 
   {
      formation(...);  //formation.c  
      cformation1 = 0; 
   }
   form_center(...);  //center of formation
   form_keep(...);  //formation keeping
//...	 
    
   return 0;
}
int job_scas(...) { //Do real-tme scas calculation 
//... 
   cont_nextstate(...);  //source/inner_loop/scas.c 
//... 
}
int job_col_avoid(...) { //Do real-tme col_avoid calculation 
//...
   col_avoid_loop();  //col_avoid.c 
//...
}
int job_wpt_follow(...) { //Do real-tme wpt_follow calculation 
//...
   wpt_follow_loop();  //wpt_follow.c 
//... 
}

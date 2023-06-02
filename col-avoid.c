#include "col_avoid.h"
#include "../astar/astar_x.h"

void col_avoid_loop(void)
{
   int k=0; 	
//=ff25jul21, ff27feb21=collision avoidance using A* algorithm=======
//-ff10sep21-find quadrant------
      find_quadrant();
      if (iscen>=1)
      {
         k = 1;  
         {
            if ((qr[k].los<5.0) && (castar[k]==0))  //obstacle threshold = 5m
            {
               castar[k] = 1; 
 //-ff06feb21-algoritma astar (A*)------
               astar(); 
               castar[k] = 2;  //ff25jul21 
            }
         }  //k 
      }  //iscen
}; 

void find_quadrant(void)
{
   if ((qr[1].hdg<45.0)||(qr[1].hdg>315.0))  //utara 
   {
      qr_quadrant[1] = 2;
   }
   else if ((qr[1].hdg>45.0)||(qr[1].hdg<135.0))  //timur 
   {
      qr_quadrant[1] = 1;
   }
   else if ((qr[1].hdg>135.0)||(qr[1].hdg<225.0))  //selatan 
   {
      qr_quadrant[1] = 4;
   }
   else if ((qr[1].hdg>225.0)||(qr[1].hdg<315.0))  //barat 
   {
      qr_quadrant[1] = 3;
   }
}; 


//=ff========================================================== 

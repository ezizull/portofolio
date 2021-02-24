#include<stdio.h>
#include<string.h>
int main()
{
  int n = 1, i = 0, len;
  char tahun[100][10], bulan[100][10], hari[100][10], agenda[100][10] ;
  char clon_tahun[100][10], clon_bulan[100][10], clon_hari[100][10], clon_agenda[100][10];
  FILE *ptr;
  ptr = fopen("database.txt", "r");
  while(n > 0)
    {
      n = fscanf(ptr, "%s %s %s %s ", tahun[i], bulan[i], hari[i], agenda[i]);

      i++;
    }
  // memset(hari[1], 0, 100);
  n = i;

  // for(i=0 ; i<n-1; i++)
  // {
  //   memset(hari[i], 0, sizeof hari[i]); // zeros out entire subarray
  // }

  for(i=0; i<n-1; i++){
    strcpy(clon_tahun[i], tahun[i]);
    strcpy(clon_bulan[i], bulan[i]);
    strcpy(clon_hari[i], hari[i]);
    strcpy(clon_agenda[i], agenda[i]);
    // strcpy(hari[i], hari[i+1]); // overwrites "four" with "five"
    // strcpy(hari[i], clon_hari[i]); // zeros out the first element in the subarray
  }
 

  // memset(hari[1], 0, sizeof hari[1]); // zeros out entire subarray

  // printf("\ntahun: %s   bulan: %s   hari: %s   agenda: %s\n",tahun[0],bulan,hari[0], agenda[0]);
  // printf("\ntahun: %s   bulan: %s   hari: %s   agenda: %s\n",tahun[1],bulan,hari[1], agenda[1]);
  // printf("\ntahun: %s   bulan: %s   hari: %s   agenda: %s\n",tahun[2],bulan,hari[2], agenda[2]);

  for(i = 0; i < n - 1; i++){
    printf("tahun: %s   bulan: %s   hari: %s   agenda: %s\n",clon_tahun[i],clon_bulan[i],clon_hari[i], clon_agenda[i]);
  }  
  return 0;
}

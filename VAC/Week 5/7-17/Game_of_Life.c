#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

int num=20;

int randInt( int min, int max )
{
  return ((rand()*(max-min+1))/(RAND_MAX+1) + min) ;
}

int checkBox(int grid[num][num],int r,int c)    //checks all #s in box area
{
    int i,j,count=0;

    count=0;

   if(r==0&&c==0)
   {
       for(i=r;i<=r+1;i++)
       {
           for(j=c;j<=c+1;j++)
           {
               if(i==r&&j==c)
                    continue;
               else if(grid[i][j]==1)
                    count++;
           }
       }
   }
   else if(r==num-1&&c==num-1)
   {
       for(i=r-1;i<=r;i++)
       {
           for(j=c-1;j<=c;j++)
           {
               if(i==r&&j==c)
                    continue;
               else if(grid[i][j]==1)
                    count++;
           }
       }
   }
   else if(r==0&&c==num-1)
   {
       for(i=r;i<=r+1;i++)
       {
           for(j=c-1;j<=c;j++)
           {
               if(i==r&&j==c)
                    continue;
               else if(grid[i][j]==1)
                    count++;
           }
       }
   }
   else if(r==0&&c!=0)
   {
       for(i=r;i<=r+1;i++)
       {
           for(j=c-1;j<=c+1;j++)
           {
               if(i==r&&j==c)
                    continue;
               else if(grid[i][j]==1)
                    count++;
           }
       }
   }
   else if(c==0&&r!=0)
   {
       for(i=r-1;i<=r+1;i++)
       {
           for(j=c;j<=c+1;j++)
           {
               if(i==r&&j==c)
                    continue;
               else if(grid[i][j]==1)
                    count++;
           }
       }
   }
   else if(r==num-1&&c==0)
   {
       for(i=r-1;i<=r;i++)
       {
           for(j=c;j<=c+1;j++)
           {
               if(i==r&&j==c)
                    continue;
               else if(grid[i][j]==1)
                    count++;
           }
       }
   }
   else if(r==num-1&&c==num-1)
   {
       for(i=r-1;i<=r;i++)
       {
           for(j=c-1;j<=c;j++)
           {
               if(i==r&&j==c)
                    continue;
               else if(grid[i][j]==1)
                    count++;
           }
       }
   }
   else if(r==num-1&&c!=num-1)
   {
       for(i=r-1;i<=r;i++)
       {
           for(j=c-1;j<=c+1;j++)
           {
               if(i==r&&j==c)
                    continue;
               else if(grid[i][j]==1)
                    count++;
           }
       }
   }
   else if(c==num-1&&r!=num-1)
   {
       for(i=r-1;i<=r+1;i++)
       {
           for(j=c-1;j<=c;j++)
           {
               if(i==r&&j==c)
                    continue;
               else if(grid[i][j]==1)
                    count++;
           }
       }
   }
   else
   {
       for(i=r-1;i<=r+1;i++)
       {
           for(j=c-1;j<=c+1;j++)
           {
               if(i==r&&j==c)
                    continue;
               else if(grid[i][j]==1)
                    count++;
           }
       }
    }
//printf(" count:%d\t",count);
    return count;

}


int main()
{
  int i,j,count1=0;

  time_t t;
    printf("Enter value of N for number of rows and columns: ");
    scanf("%d",&num);
    char answer='y';
      int c[num][num];
    int grid[num][num];

  /* Initialize the random number generator */
  srand( time(&t));
    printf("\n\nGeneration %d:\n\n",count1);
    for(i=0;i<num;i++)
    {
       for(j=0;j<num;j++)
       {
           c[i][j]=randInt(0,1);
           grid[i][j]=0;
           printf("%d ",c[i][j]);
       }
       printf("\n");
    }

    while(answer=='y')
    {
        count1++;
        printf("\n\nGeneration %d:\n\n",count1);

        for(i=0;i<num;i++)
        {
            for(j=0;j<num;j++)
            {
                if(c[i][j]==0)          //dead
                {
                     //printf("hi");
                    if(checkBox(c,i,j)==3)
                    {
                        grid[i][j]=1;           //revived
                    }
                    else
                    {
                        grid[i][j]=0;           //dead
                    }
                }
                else if(c[i][j]==1)
                {
                    if(checkBox(c,i,j)==2||checkBox(c,i,j)==3)
                    {
                        grid[i][j]=1;               //still alive
                    }
                    else
                    {
                        grid[i][j]=0;               //killed
                    }
                }
               // printf("%d ",grid[i][j]);

            }
            //printf("\n");

        }

        i=0;
        j=0;
        for(i=0;i<num;i++)
        {
            for(j=0;j<num;j++)
            {
                printf("%d ",grid[i][j]);
                c[i][j]=grid[i][j];
            }
            printf("\n");
        }
        printf("\n\nContinue onto another generation (y or n)? ");
        scanf(" %c",&answer);
    }


    return 0;
}


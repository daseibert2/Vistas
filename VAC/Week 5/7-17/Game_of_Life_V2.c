#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#define NUM 20

int randInt( int min, int max )
{
  return ((rand()*(max-min+1))/(RAND_MAX+1) + min) ;
}

int checkBox(int grid[NUM][NUM],int start_r,int start_c,int num)    //checks all #s in box area
{
    int r,c,i,j,count=0;
    r=start_r;c=start_c;

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
   else if(r==0)
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
   else if(c==0)
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
   else if(r==num-1)
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
   else if(c==num-1)
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
       for(i=r-1;r<=r+1;i++)
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

    /*if(count<2&&grid[start_r][start_c]==1)
    {
        //grid[start_r][start_c]= 0;
        return 0;
    }
    else if(grid[start_r][start_c]==1&&count>=2||count<=3)
    {
        //grid[start_r][start_c]=1;
        return 1;
    }
    else if(count>3&&grid[start_r][start_c])
    {
        //grid[start_r][start_c]=0;
        return 0;
    }
    else if(count==3&&!grid[start_r][start_c])
    {
        //grid[start_r][start_c]=1;
        return 1;
    }*/
    if(count==2||count==3)
        return 1;
    else
        return 0;
    count=0;
}

int checkCount(int grid[NUM][NUM],int start_r,int start_c,int num)
{
    int r,c,i,j,count=0;
    r=start_r;c=start_c;

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
   else if(r==0)
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
   else if(c==0)
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
   else if(r==num-1)
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
   else if(c==num-1)
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
       for(i=r-1;r<=r+1;i++)
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
    if(count==3)
        return 1;
    else
        return 0;
}

int main()
{
  int i,j,num=0,count=0;
  int c[NUM][NUM];
    printf("Enter value of N for number of rows and columns: ");
    scanf("%d",&num);
    char answer='y';
    int grid[num][num];

  /* Initialize the random number generator */
  srand( time(NULL) );
    printf("\n\nGeneration %d:\n\n",count);
    for(i=0;i<num;i++)
    {
       for(j=0;j<num;j++)
       {
           c[i][j]=randInt(0,1);
           printf("%d ",c[i][j]);
       }
       printf("\n");
    }

    while(answer=='y')
    {
        count++;
        printf("\n\nGeneration %d:\n\n",count);

        for(i=0;i<num;i++)
            {
            for(j=0;j<num;j++)
            {
                grid[i][j]=c[i][j];
            }
        }

        for(i=0;i<num;i++)
        {
            for(j=0;j<num;j++)
            {
                if(c[i][j]==0)
                {
                    if(checkBox(grid,i,j,num))
                    {
                        if(checkCount(grid,i,j,num))
                        {
                            c[i][j]=1;
                        }
                    }
                }
                else if(c[i][j]==1)
                {
                    if(checkBox(grid,i,j,num))
                    {
                        c[i][j]=1;
                    }
                    else
                    {
                        c[i][j]=0;
                    }
                }

                c[i][j]=checkBox(grid,i,j,num);
                printf("%d ",c[i][j]);
            }
            printf("\n");
        }
        printf("\n\nContinue onto another generation (y or n)? ");
        scanf(" %c",&answer);
    }


    return 0;
}

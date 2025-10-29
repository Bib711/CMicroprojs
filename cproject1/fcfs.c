#include <stdio.h>
int main()
{
    int n;
    printf("Enter no of process:");
    scanf("%d",&n);
    int bt[n];
    for(int i=0;i<n;i++){
        printf("Enter the burst time of process P%d",i+1);
        scanf("%d",&bt[i]);
    }
    int wt[n];
    wt[0]=0;
    for(int i=0;i<n;i++){
        wt[i]=bt[i-1]+wt[i-1];
    }
    int tat[n],total_wt=0,total_tat=0;
    for(int i=0;i<n;i++){
        tat[i]=bt[i]+wt[i];
        total_wt += wt[i];
        total_tat += tat[i];
    }
    //Gantt chart printing
    printf("Gantt Chart");
    

}
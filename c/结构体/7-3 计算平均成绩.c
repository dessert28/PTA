#include<stdio.h>
struct student{
    char num[6];
    char name[10];
    int score;
};
int main()
{
    struct student a[10];
    int n,i,sum=0;
    scanf("%d\n",&n);
    for(i=0;i<n;i++)
    {
        scanf("%s%s%d",a[i].num,a[i].name,&a[i].score);
        sum+=a[i].score;
    }
    float average;
    average=((float)sum/n);
    int flag = 0;
    printf("%.2f\n",average);
    for(i=0;i<n;i++)
    {
        if(a[i].score<average && flag==0)
        {
            printf("%s %s",a[i].name,a[i].num);
            flag++;
        }
        else if(a[i].score<average)
        {
            printf("\n");
            printf("%s %s",a[i].name,a[i].num);
        }
    }
    return 0;
}
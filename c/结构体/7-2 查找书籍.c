#include<stdio.h>
#include<string.h>
struct book{
    char name[31];
    double price;
}b[10];
int main()
{
    int n,i,j,mini=0,maxi=0;
    double min=1000000,max=-1;
    scanf("%d",&n);
    for(i=0;i<n;i++)
    {
        scanf("\n");
        gets(b[i].name);
        scanf("%lf",&b[i].price);
        if(b[i].price>max)
        {
            max=b[i].price;
            maxi=i;
        }
        if(b[i].price<min)
        {
            min=b[i].price;
            mini=i;
        }
    }
    printf("%.2lf, %s\n",b[maxi].price,b[maxi].name);
    printf("%.2lf, %s\n",b[mini].price,b[mini].name);
    return 0;
}
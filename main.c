#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <conio.h>


struct book  //定义图书结构体
{
	int num;  // 书号
	char name[20];  //书名
	char publish[20];  // 出版社
    struct time //定义时间结构体
	{
		int year,month,day; //年月日
	}t;
	int jie;// 定义 借的状态

}bk[20];

int N;   // N可以理解为 录入的图书的数量

	
int mymainmenu()   //主菜单
 {   
	int x;  
	printf("\n\n\n\n");   
	printf("\t\t|-------------------------------------------------------------|\n");
	printf("\t\t|                     |\n");   
	printf("\t\t|    ======================    |\n");   
	printf("\t\t|      欢迎光临图书管理系统     |\n");   
	printf("\t\t|    ======================    |\n");   
	printf("\t\t|                     |\n");   
	printf("\t\t|      1.管理员模式          |\n");   
	printf("\t\t|      2.客户模式           |\n");   
	printf("\t\t|      3.退出系统           |\n");   
	printf("\t\t|--------------------------------------------------------------|\n");   
    printf("\n\t\t请输入您的选择:");   
	scanf("%d",&x);   
	return x; 
}
char mima[20] = "mm";  //密码
 
int mimayanzheng()  //密码验证
{ 
    char mm[20];   //用来存放输入的密码
		 printf("\n");   
		 printf("\t\t     ======================    \n");   
		 printf("\t\t      欢迎使用管理员模式      \n");   
		 printf("\t\t     ======================    \n");   
		 printf("\n");   
		 printf("\t\t     请输入密码:"); 
	     scanf("%s",&mm);
	if(!strcmp(mm,mima))  //比较输入的密码 是否 与原密码相同
	{
		return 1;
	}
	else
	{
		return 0;
	}

}

int xiugaimima()   //修改密码
{
	char mima_temp[20];//用来存放用户输入的密码
	char new_mima[20];   //存放第一次新密码
	char new_mima1[20];  //存放第二次新密码

	printf("请输入原始密码：\n");
	scanf("%s",&mima_temp);
	if(!strcmp(mima_temp,mima))  //比较原始密码 与 用户输入的密码
	{
		printf("请输入新密码：\n");
		scanf("%s",&new_mima);
		printf("请再输一次：\n");
		scanf("%s",&new_mima1);
		if(!strcmp(new_mima1,new_mima)) //比较 两次修改后输入的密码
		{
			strcpy(mima,new_mima); //将 新密码 拷贝给 原始密码
			printf("密码修改成功，请牢记，按任意键返回。。。\n");
			getch();
			return 0;
		}
		else
		{
			printf("错误！两次输入的密码不一致，按任意键返回。。。\n");
			getch();
			return 1;
		}
	}
	else
	{
		printf("原始密码错误，按任意键返回。。。\n");
		getch();
	}
}

int adm()  //管理员模式
{   
	int x; 
		 system("cls");
 		 printf("\n\n\n\n");   
 		 printf("\t\t|-------------------------------------------------------------|\n");   
		 printf("\t\t|                     |\n");   
		 printf("\t\t|    ======================    |\n");   
		 printf("\t\t|        管理员模式        |\n");  
		 printf("\t\t|    ======================    |\n");   
		 printf("\t\t|                     |\n");   
 		 printf("\t\t|      1.录入图书信息        |\n");  
		 printf("\t\t|      2.查看图书信息        |\n");   
		 printf("\t\t|      3.修改图书信息        |\n");   
		 printf("\t\t|      4.修改管理密码        |\n");   
		 printf("\t\t|      5.退出系统          |\n");  
		 printf("\t\t|-------------------------------------------------------------|\n");   
		 printf("\n\t\t请输入您的选择:");   
		 scanf("%d",&x);   
	return x; 
} 

void xiugai_name()        //按书名来修改信息      
{
	char name[20];  //用来存放想要修改的 书名
	int i;   //循环下标
	int k = 0;// 标记书名是否存在
	printf("输入你想要修改的书名，按“exit”退出：\n");
	do
	{
		scanf("%s",&name);
		if(!strcmp(name,"exit"))
		{
			break;
		}
		for(i=0;i<N;i++)
		{
			if(!strcmp(name,bk[i].name))
			{
				k++;
				printf("该书的信息为：\n");
				 printf("\t编号    图书名称     出版社        出版时间     状态\n");
				printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				if(bk[i].jie == 1)
				{
					printf("已被借阅\n");
				}
				else
				{
					printf("可以借阅\n");	
				}
				printf("现在请输入新的信息：\n");
				printf("请输入书的编号：\n");
				scanf("%d",&bk[i].num);
				printf("请输入书的名称：\n");
				scanf("%s",&bk[i].name);
				printf("请输入书的出版社：\n");
				scanf("%s",&bk[i].publish);
				printf("请输入书的出版时间（用逗号隔开，英文的逗号哦！）：\n");
				scanf("%4d,%2d,%d",&bk[i].t.year,&bk[i].t.month,&bk[i].t.day);
				printf("该书是否已经被借阅，已经借阅输入‘1’，未被借阅输入‘0’:\n");
				scanf("%d",&bk[i].jie);
			//	if(bk[i].jie == 1)
			//		{
			//			printf("恭喜你信息修改成功，按任意键返回。。。\n");
			//			getch();
			//			break;
			//		}
			//		else
			//		{								
			//			 printf("恭喜你信息修改成功，按任意键返回。。。\n");
			//			 getch();
			//			 break;
			//		}
			//}
			//else
			//{
			//	break;
			//}
			}
		}
		if(k == 0)
		{
			system("cls");
			printf("您输入的书名不存在，请重新输入(按“exit”退出)：\n");
		}
		else
		{
			 printf("恭喜你信息修改成功，按任意键返回。。。\n");
						 getch();
						 break;
		}
	}while(1);
}

void xiugai_num() //按书号修改图书
{
	int num;  //用来存放 想要 修改的书号
	int i;  //循环下标变量
	int k = 0; //用来标记 该书是否存在
	printf("请输入你想要修改的图书的书号(按'0'退出)：\n");
	do
	{
		scanf("%d",&num);
		if(num == 0)
		{
			break;
		}
		for(i=0;i<N;i++)
		{
			if(num == bk[i].num)
			{
				k++;
				printf("该书的信息为：\n");
				 printf("\t编号    图书名称     出版社        出版时间     状态\n");
				printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				if(bk[i].jie == 1)
				{
					printf("已被借阅\n");
				}
				else
				{
					printf("可以借阅\n");	
				}
				printf("现在请输入新的信息：\n");
				printf("请输入书的编号：\n");
				scanf("%d",&bk[i].num);
				
				printf("请输入书的名称：\n");
				scanf("%s",&bk[i].name);
				
				printf("请输入书的出版社：\n");
				scanf("%s",&bk[i].publish);
					
				printf("请输入书的出版时间（用逗号隔开，英文的逗号哦！）：\n");
				scanf("%4d,%2d,%d",&bk[i].t.year,&bk[i].t.month,&bk[i].t.day);
				printf("该书是否已经被借阅，已经借阅输入‘1’，未被借阅输入‘0’:\n");
				scanf("%d",&bk[i].jie);
			//	if(bk[i].jie == 1)
			//		{			
			//			printf("恭喜你信息修改成功，按任意键返回。。。\n");
			//			getch();
			//			break;
			//		}
			//		else
			//		{			
			//			 printf("恭喜你信息修改成功，按任意键返回。。。\n");
			//			 getch();
			//			 break;
			//		}
			//}
			//else
			//{
			//	break;
			//}
			}
		}
		if(k == 0)
		{
			system("cls");
			printf("您输入的书号不存在，请重新输入(按“0”退出)：\n");
		}
		else
		{
			printf("恭喜你信息修改成功，按任意键返回。。。\n");
						 getch();
						 break;
		}		
	}while(1);
}

void dele_name()   //按 书名删除
{                                        
	int i; //循环下标变量
	char name[20]; //用来存放输入的书名
	char new_name[20];  //定义一个空数组
	int k = 0;//用来标记 是否存在该书
	char c[2];    //用来表示   是否删除图书               
	printf("请输入您想要删除的书名(输入”exit”退出)：\n");
	while(1)
	{
		scanf("%s",&name);
		if(!strcmp(name,"exit"))
		{
			break;
		}
		for(i=0;i<N;i++)
		{
			if(!strcmp(name,bk[i].name))
			{
				k++;
				printf("该书的信息为：\n");
				printf("\t编号    图书名称     出版社        出版时间     状态\n");
				printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				if(bk[i].jie == 1)
				{
					printf("已被借阅\n");
				}
				else
				{
					printf("可以借阅\n");	
				}
				printf("\t是否要删除此书('y' or 'n')：\n");
				scanf("%s",&c); 
				if(!strcmp(c,"y"))
				{
					strcpy(bk[i].name,new_name);     //空数组 拷贝给 已有书名
					bk[i].num = 0;                   //令书号值为0
					strcpy(bk[i].publish,new_name);  //空数组 拷贝给  已有出版社  
					bk[i].t.year = 0;                //令年  = 0  
					bk[i].t.month = 0;               //令月  = 0
					bk[i].t.day = 0;                 //令日  = 0  
					printf("\t删除成功！\n");
					getch();
					break;
				}
				else
				{
					printf("用户取消操作，任意键返回。。。");
					getch();
					break;
				}
			}
		/*	else
			{
				break;
			}*/
		}
		if(k == 0)
		{
			system("cls");
			printf("未找到该书，请重新输入（输入“exit”退出）：\n");
		}
		else
		{
			break;
		}
	}
}

void dele_num()   //按 书号删除
{
	int i;//循环下标变量
	int k = 0; //标记是否存在该书
	int num; //存放输入的书号
	char new_name[20];//定义一个空数组
	char c[2];//用来表示   是否删除图书
	printf("请输入您想要删除的书名的书号(输入”0”退出)：\n");
	while(1)
	{
		scanf("%d",&num);
		if(num == 0)
		{
			break;
		}
		for(i=0;i<N;i++)
		{
			if(num == bk[i].num)
			{
				k++;
				printf("该书的信息为：\n");
				printf("\t编号    图书名称     出版社        出版时间     状态\n");
				printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				if(bk[i].jie == 1)
				{
					printf("已被借阅\n");
				}
				else
				{
					printf("可以借阅\n");	
				}
				printf("\t是否要删除此书('y' or 'n')：\n");
				scanf("%s",&c); 
				if(!strcmp(c,"y"))
				{
					strcpy(bk[i].name,new_name);
					bk[i].num = 0;
					strcpy(bk[i].publish,new_name);
					bk[i].t.year = 0;
					bk[i].t.month = 0;
					bk[i].t.day = 0;
					printf("\t删除成功！\n");
					getch();
					break;
				}
				else
				{
					printf("用户取消操作，任意键返回。。。");
					getch();
					break;
				}
			}
			/*else
			{
				break;
			}*/
		}
		if(k == 0)
		{
			system("cls");
			printf("未找到该书，请重新输入（输入“0”退出）：\n");
		}
		else 
		{
			break;
		}
	}
}

void dele_all()  //删除所有图书
{
	char c[2]; //用来表示 是否 删除
	printf("\t继续操作会删除所有图书信息，是否继续（“y” or “n”）");
	scanf("%s",&c);
	if(!strcmp(c,"y"))
	{
		N = 0;  //Ｎ等于０　也就是令录入的图书数量为零　即删除了所有图书
		printf("\t删除成功\n");
		getch();
	}
	else
	{
		printf("\t操作取消，任意键返回。。。\n");
		getch();
	}
}

void dele()  //删除图书
{
	int x;	
	do
	{
		system("cls");
		printf("\t\t|-------------------------------------------------------------|\n");
    		printf("\t\t|         =====================        |\n");
    		printf("\t\t|              删除图书信息               |\n");
    		printf("\t\t|         =====================        |\n");
    		printf("\t\t|                                         |\n");
    		printf("\t\t|            1.按书名删除                 |\n");
    		printf("\t\t|            2.按书号删除                 |\n");
		printf("\t\t|            3.删除所有图书               |\n");
    		printf("\t\t|            4.返回主菜单                 |\n");
    		printf("\t\t|-------------------------------------------------------------|\n");
		printf("\t\t请输入您的选项：");
		scanf("%d",&x);
		switch(x)
		{
			case 1:system("cls");dele_name();break;/*按书名删除*/
			case 2:system("cls");dele_num();break;/*按书号删除*/
			case 3:system("cls");dele_all();getch();break;/*删除所有图书*/
		}
	}while(x!=4);
}

/***********修改图书信息*********/
void xiugai()
{
    int x;
    do
    {
		system("cls");
		printf("\n\n\n\n");
   	 	printf("\t\t|-------------------------------------------------------------|\n");
   	 	printf("\t\t|         =====================        |\n");
    		printf("\t\t|               修改图书信息              |\n");
    		printf("\t\t|         =====================        |\n");
    		printf("\t\t|                                         |\n");
    		printf("\t\t|            1.按书名查找                 |\n");
    		printf("\t\t|            2.按书号查找                 |\n");
    		printf("\t\t|            3.删除图书                   |\n");
    		printf("\t\t|            4.返回主菜单                 |\n");
    		printf("\t\t|-------------------------------------------------------------|\n");
    		printf("\t\t请输入您的选择:");
    		scanf("%d",&x);
    		switch(x)
    		{
      	  		case 1:system("cls");xiugai_name();break;/*按书名查找名修改信息*/
      	  		case 2:system("cls");xiugai_num();break;/*按书号查找并修改信息*/
				case 3:system("cls");dele();break;							
    		}
    }while(x!=4);
}

/********建立图书信息库********/
void xinxi()  
{   
	int i;   
		system("cls");   
		printf("\t\t     =====================    \n");   
		printf("\t\t        录入图书信息       \n");   
		printf("\t\t     =====================    \n\n");  
		printf("\t\t请输入您要录入的数量:");  
		scanf("%d",&N);   
	for(i=0;i<N;i++)   
	{  
			printf("\t\t请输入第%d本书的编号:",i+1);     
			scanf("%d",&bk[i].num);     
			printf("\t\t请输入第%d本书的名称:",i+1);     
			scanf("%s",bk[i].name);     
			printf("\t\t请输入第%d本书的出版社:",i+1);     
			scanf("%s",bk[i].publish);     
			printf("\t\t请输入第%d本书的出版时间(用逗号隔开):",i+1);     
			scanf("%d,%d,%d",&bk[i].t.year,&bk[i].t.month,&bk[i].t.day);     
			printf("\t\t该书是否已经被借阅,已被借阅输入'1'，未被借阅输入'0':");     
			scanf("%d",&bk[i].jie);  
			printf("--------------------------------------------------------------------------------\n");   
	}  
		system("cls");   
		printf("\t\t     =====================    \n");   
		printf("\t\t        信息录入完成       \n");   
		printf("\t\t     =====================    \n");   
		printf("\n\t\t       按任意键继续...\n"); 
}
 
void showbook_name()  //管理员————按书名查看
{
	 //int i;
  //   char name[20];
	 //printf("请输入需要查看的书名：\n");                      
	 //scanf("%s",&name);
	 //for(i=0;i<N;i++)
	 //{
		// if(strcmp(name,bk[i].name)!=0 || N == 0)  //如果当 输入的书名与想要查看的书名 比较时 不相等 或者 录入图书数量 为0  则数据不存在
		// {
		//	 printf("数据不存在...\n");
		//	 system("pause");
		//	
		// }
		// else
		// {
		//		printf("\t编号    图书名称     出版社        出版时间     状态\n");
		//		printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
		//	 if(bk[i].jie == 1)
		//	 {
		//		 printf("\t\t已借阅\n");
		//	 }
		//	 else
		//	 {
		//		 printf("\t\t未借阅\n");
		//	 }
		// }
	 //}
	int i,k=0; //i是局部变量一定记住， ，k用来标记书的借阅状态。
	char name[20];
	printf("请输入需要查看的书名：\n");
	scanf("%s",&name);                              
	for(i=0;i<N;i++)
	{
		if(!strcmp(name,bk[i].name))
		{		 
			   printf("\t编号    图书名称     出版社        出版时间     状态\n");
			   printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
			 if(bk[i].jie == 1)
			 {
				 printf("\t\t已借阅\n");
			 }
			 else
			 {
				 printf("\t\t未借阅\n");
			 }
			 k++;
			 printf("\t按任意键返回。。。\n");
		}
	}
	if(k == 0)
	{
		printf("该书不存在，任意键返回。。。\n");
	}
}

void showbook_num()  //管理员————按书号查看
{
	int i,k=0; //i是局部变量一定记住， ，k用来标记书的借阅状态。
	int num;
	printf("请输入需要查看的书号：\n");
	scanf("%d",&num);                              
	for(i=0;i<N;i++)
	{
		if(num==bk[i].num)
		{		 
			   printf("\t编号    图书名称     出版社        出版时间     状态\n");
			   printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
			 if(bk[i].jie == 1)
			 {
				 printf("\t\t已借阅\n");
			 }
			 else
			 {
				 printf("\t\t未借阅\n");
			 }
			 k++;
			 printf("\t按任意键返回。。。\n");
		}
	}
	if(k == 0)
	{
		printf("该书不存在，任意键返回。。。\n");
	}
}

void weijieyue()  //管理员————未借阅的图书
{
	int i,k=0;
	if(bk[0].num == 0&&bk[0].t.year == 0 || N == 0)   //如果 结构体中 bk【】数组中存放 的第一个 数据 书号 为零 年 为零 或 数量为零 则 数据不存在
		{
			printf("数据不存在，请先录入数据...\n");
			printf("按任意键返回...\n");
		}
	for(i=0;i<N;i++)
	{		
			if(bk[i].jie == 0)
			{
				printf("\t编号    图书名称     出版社        出版时间     状态\n");
				printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				printf("您可以借阅此书...\n");
				k++;
			}
	}
	if(k == 0)
		printf("目前没有可借阅的图书,按任意键继续。。。\n");
}

void yijieyue()  //管理员————已经借阅的图书
{
	int i,k=0;
	if(bk[0].num == 0&&bk[0].t.year == 0 || N == 0)   //如果 结构体中 bk【】数组中存放 的第一个 数据 书号 为零 年 为零 或 数量为零 则 数据不存在
	{
		printf("数据不存在，请先录入数据。。。\n");
		printf("按任意键返回...\n");
	}
	else
	{
		for(i=0;i<N;i++)
		{
			if(bk[i].jie == 1)
			{
				printf("\t编号    图书名称     出版社        出版时间     状态\n");
				printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				printf("很遗憾，此书已被接走。。。\n");
				k++;
			}
		}
		if(k == 0)
			printf("目前没有任何书借出。按任意键继续。。。\n");
	}
}

void show_all_book()  //管理员————查看所有图书
{
	int i;
	if(bk[0].num == 0&&bk[0].t.year == 0 || N == 0)  //如果 结构体中 bk【】数组中存放 的第一个 数据 书号 为零 年 为零 或 数量为零 则 数据不存在
	{
		printf("数据不存在，请先录入数据。。。\n");
	}
	else
	{
		printf("\t编号    图书名称     出版社        出版时间     状态\n");
		for(i=0;i<N;i++)
		{		
			printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
			if(bk[i].jie == 1)
			{
				printf("已借阅\n");
			}
			else
			{
				printf("未借阅\n");
			}
		}


	}
}

void show() //管理员———查看图书信息
{
	int x; 
	do
	{
		 system("cls");   
		 printf("\n\n\n\n");    
		 printf("\t\t|-------------------------------------------------------------|\n");    
		 printf("\t\t|                     |\n");    
		 printf("\t\t|     =====================    |\n");    
		 printf("\t\t|       查看图书信息        |\n");    
		 printf("\t\t|     =====================    |\n");    
		 printf("\t\t|                     |\n");    
		 printf("\t\t|      1.按书名查找         |\n");    
		 printf("\t\t|      2.按书号查找         |\n");    
		 printf("\t\t|      3.查看所有未借阅图书     |\n");    
		 printf("\t\t|      4.查看所有已借阅图书     |\n");    
		 printf("\t\t|      5.查看所有图书        |\n");    
		 printf("\t\t|      6.返回主菜单         |\n");    
		 printf("\t\t|-------------------------------------------------------------|\n");    
		 printf("\n\t\t请输入您的选择:");    
		 scanf("%d",&x);    
		 switch(x)    
		 {       
			 case 1:system("cls");showbook_name();getch();break;/*按书名查看*/     
			 case 2:system("cls");showbook_num();getch();break;/*按书号查看*/       
			 case 3:system("cls");weijieyue();getch();break;/*查看未借阅图书*/       
			 case 4:system("cls");yijieyue();getch();break;/*查看已借阅图书*/   
			 case 5:system("cls");show_all_book();getch();break;/*查看所有图书*/    
		 }                   
	}while(x!=6);

} 

int peo()  //客户模式
{
	int x;
	printf("\n\n\n\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|               欢迎光临                  |\n");
    printf("\t\t|        ======================        |\n");
    printf("\t\t|                                         |\n");
    printf("\t\t|           1.查看图书信息                |\n");
    printf("\t\t|           2.借阅图书                    |\n");
    printf("\t\t|           3.退出系统                    |\n");
    printf("\t\t|-------------------------------------------------------------|\n");
    printf("\n\t\t请输入您的选择:");
    scanf("%d",&x);
    return x;
}

void jie_name()                 
{
	char name[20];   
	int i;
	char n[2];       //用来表示 是否 借阅 
	int k = 0;      
	system("cls");
	printf("请输入书名：\n");
	while(1)
	{
		scanf("%s",&name);
		for(i=0;i<N;i++)
		{
			if((!strcmp(name,bk[i].name))&&(bk[i].jie == 0))  //比较输入书名与已有书名相等时 且 未借阅  时 执行 if语句
			{
				k++;
				printf("\t编号    图书名称     出版社        出版时间     状态\n");
				printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				printf("可以借阅\n");
				printf("您是否需要借阅此书：'y' or 'n' \n");
				scanf("%s",&n);
				if(!strcmp(n,"y"))
				{
					bk[i].jie = 1;
					printf("借阅成功，按任意键返回。。。\n");
					getch();
					break;
				}
				else 
				{
					if(!strcmp(n,"n"))
					{
						printf("借阅取消，按任意键返回。。。\n");
						getch();
					}
					else 
					{
						printf("输入有错，按任意键返回。。。\n");  
						getch();
					}	
					break;
				}
			}
			/*else
			{
				break;
			}*/

		}
		if(k == 0)
		{
				printf("不存在该书，或该书已经借出!请正确输入图书名称!\n");
				printf("按任意键返回。。。\n");
				getch();
				break;
		}

		else 
		{
				break;
		}
		
	}
}

void jie_num()
{
	int i;
	int num;
	int k = 0;
	char n[2];  //用来表示 是否借阅
	system("cls");
	printf("请输入书名的书号：\n");
	while(1)
	{
		scanf("%d",&num);
		for(i=0;i<N;i++)
		{
			if((num == bk[i].num)&&(bk[i].jie == 0)) //比较输入书号与已有书号相等时 且 未借阅  时 执行 if语句
			{
				k++;
				printf("\t编号    图书名称     出版社        出版时间     状态\n");
				printf("\t%-7d %-8s %-12s   %4d年%2d月%2d日 ",bk[i].num,bk[i].name,bk[i].publish,bk[i].t.year,bk[i].t.month,bk[i].t.day);
				printf("可以借阅\n");
				printf("您是否需要借阅此书：'y' or 'n' \n");
				scanf("%s",&n);
				if(!strcmp(n,"y"))
				{
					bk[i].jie = 1;
					printf("借阅成功，按任意键返回。。。\n");
					getch();
					break;
				}
				else 
				{
					if(!strcmp(n,"n"))
					{
						printf("借阅取消，按任意键返回。。。\n");
						getch();
					}
					else 
					{
						printf("输入有错，按任意键返回。。。\n");  
						getch();
					}	
					break;
				}
			}
			/*else
			{
				break;
			}
*/
		}
		if(k == 0)
		{
				printf("不存在该书，或该书已经借出!请正确输入图书名称!\n");
				printf("按任意键返回。。。\n");
				getch();
				break;
		}

		else 
		{
				break;
		}
		
	}
}

void jieyue()   //借阅图书
{
	int x;
    do
    {
		system("cls");
		printf("\n\n\n\n");
		printf("\t\t|-------------------------------------------------------------|\n");
		printf("\t\t|         =====================        |\n");
		printf("\t\t|                借阅图书                 |\n");
		printf("\t\t|         =====================        |\n");
		printf("\t\t|                                         |\n");
		printf("\t\t|            1.按书名借阅                 |\n");
		printf("\t\t|            2.按书号借阅                 |\n");
		printf("\t\t|            3.查看所有图书               |\n");
		printf("\t\t|            4.返回主菜单                 |\n");
		printf("\t\t|-------------------------------------------------------------|\n");
		printf("\t\t请输入您的选择:");
		scanf("%d",&x);
		switch(x)
		{
			case 1:system("cls");jie_name();getch();break;/*按书名借阅*/
			case 2:system("cls");jie_num();getch();break;/*按书号借阅*/
			case 3:system("cls");show_all_book();getch();break;/*查看所有图书*/
		}
    }while(x!=4);

}

int main()  /*主函数*/
{
	int n,s,x,t;  //s用来接收主菜单的值   n来接收管理员模式的值  x来接受客户模式的值
	do
	{
	    system("cls");
		s = mymainmenu();
		switch(s)
		{
			case 1 : system("cls");
					 t=mimayanzheng(); //t来存放 密码 错误与正确 的 返回值
					do
					{
						if(t == 1)
						{
							n = adm();
							switch(n)
							{
								case 1:system("cls");xinxi();getch();break;/*录入信息*/    
								case 2:system("cls");show();break;/*查看信息*/            
								case 3:system("cls");xiugai();break;/*修改信息*/    
								case 4:system("cls");xiugaimima();break;/*修改密码*/
							}
						}
						else
						{
							printf("密码错误，按任意键返回。。。\n");
							getch();
							break;
						}
					}while(n!=5);break; 
			
			case 2 : 
				    do
					{
						system("cls");
						x = peo();
						switch(x)
						{
							case 1:system("cls");show();break;//查看图书信息
							case 2:system("cls");jieyue();break;//借阅图书
						}
					}while(x!=3);break;
		}
	}while(s!=3);
	system("cls");
	printf("\n\n\n\n\n\n                            \t\t谢谢使用！！！\n");
    getch();//等待用户 输入 一个字符  然后继续执行下面语句

	return 0;
}

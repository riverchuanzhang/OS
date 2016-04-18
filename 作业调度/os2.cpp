#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#define getpch(type) (type*)malloc(sizeof(type)) 

int Select;
int Systemtime = 0;         /*系统初始时间*/
int JCBnum = 0;             /*总作业数*/
int JCBtime = 0;            /*总周转时间*/
double JCBtotaltime =0;     /*总带权周转时间*/


struct source{              /*定义资源需求结构*/
	char    memery[5];      /*主存需求*/
	int     machine;        /*磁带机数量*/
};

struct jcb {                /* 定义作业控制块PCB */ 
    char   name[10]; 
    char   state;           /* 状态 */
    double super;           /* 响应比优先权 */
    int    ntime;           /* 需要运行时间 */
    int    rtime;           /* 开始运行时间 */
	int    ptime;           /*提交时间*/
	int    ftime;           /*完成时间*/
    source *needsources;    /*资源需求链*/
    struct jcb* link;       /* 下一个作业控制块的地址 */
}*ready=NULL,*run,*p; 

typedef struct jcb JCB;
typedef struct source SOURCE;


void display()
{
 int c;
 do
 {
   system("cls");
   printf("\n\t\t          <<作业调度演示>>\n");
   printf("\n\t\t***************************************\t\t");
   printf("\n\t\t   1.先来先服务算法.");
   printf("\n\t\t   2.响应比高者优先算法");
   printf("\n\t\t   0.退出程序.");
   printf("\n");
   printf("\t\t***********************************计科3班 张大川");
   printf("\n\t\t***************************************\t\t\n");
   printf("\t请输入选择所要操作(0-2):");
   scanf("%d",&c); 
   system("cls"); 
 }while(c<0||c>3) ;
   switch(c)
   {
   case 0:
	   exit(0);
	   break;
   case 1:
	   Select=1;
	  
	   break;
/*   case 2:
	   Select=2;*/

	   break;
   case 2:
	   Select=2;
	   break; 
   default:
	   break;
   }

}

void sort() /* 建立对进程进行优先级排列函数*/ 
{ 
    JCB *first, *second,*temp; 
    int insert=0; 
	switch(Select)
	{

	case 1:                  /*先来先去服务算法*/
		if(ready==NULL)    /*队首空插入队首*/
		{
			p->link=ready;
			ready=p;
		}
		else                /*否则插入队尾*/
		{
			first=ready;
			second=ready->link;
			while(second!=NULL)
			{
				first=first->link;
				second=second->link;
			}
			first->link=p;
		}
		break;

/*	case 2:                  

        if((ready==NULL)||((p->ntime)<(ready->ntime)))  / /*队首 
		{ 
            p->link=ready; 
            ready=p; 
		}
        else                   / /往后搜索适当的位置插
		{ 
            first=ready; 
            second=first->link; 
            while(second!=NULL)  / /插入队伍中间		
			{ 
                if((p->ntime)<(second->ntime))  
				{  
					p->link=second; 
                    first->link=p; 
                    second=NULL; 
                    insert=1; 
				} 
                else             
				{ 
                    first=first->link; 
                    second=second->link; 
				} 
			}
			if(insert==0) first->link=p;   // 插入队尾
        } 
        break;  */

	case 2:             /*响应比高者优先算法*/
		                /*响应比=(等待时间+需求时间)/需求时间*/

        temp=ready;
		p->super=(double)(Systemtime-p->ptime+p->ntime)/(double)(p->ntime);  /*计算插入队列作业优先权*/
        while(temp)            /*计算就绪队列作业优先权*/                                  
		{
			temp->super=(double)(Systemtime-temp->ptime+temp->ntime)/(double)(temp->ntime);
			temp=temp->link;
		}

        /*响应比越大优先权越高*/
		 if((ready==NULL)||((p->super)>(ready->ntime)))   /*队首*/ 
		{ 
            p->link=ready; 
            ready=p; 
		}
        else                    /* 往后搜索适当的位置插入*/ 
		{ 
            first=ready; 
            second=first->link; 
            while(second!=NULL)   /*插入队伍中间*/		
			{ 
                if((p->super)>(second->super))  
				{  
					p->link=second; 
                    first->link=p; 
                    second=NULL; 
                    insert=1; 
				} 
                else             
				{ 
                    first=first->link; 
                    second=second->link; 
				} 
			}
			if(insert==0) first->link=p;   /* 插入队尾*/ 
        } 
		break;

    default:
		break;
	}
}
 
 
void input() /* 建立作业输入函数*/ 
{
    int i,num;
	SOURCE *q;
    printf("\n\n请输入作业数目:");
    scanf("%d",&num);
    JCBnum+=num;               /*总作业数*/
    for(i=0;i<num;i++)
    {
        printf("\n 【作业号No.%d】\n",i); 
        p=getpch(JCB);
        q=getpch(SOURCE);
        printf("请输入作业名:");
        scanf("%s",p->name);
        getchar();
        printf("请输入作业需要运行时间:");
		scanf("%d",&p->ntime);
        getchar();
        printf("请输入作业主存资源需求:");
        scanf("%s",q->memery);
        getchar();
        printf("请输入作业磁带机数量需求:");
        scanf("%d",&q->machine);
		p->needsources=q;
		p->ptime=Systemtime;                 /*作业提交时间为系统默认时间*/
		p->super=0;                          
		p->ftime=0;                          /*作业完成时间*/ 
        p->state='W';
        p->link=NULL;
		sort();
    }
}


void disp(JCB *pr) /*建立作业显示函数*/ 
{ 
    printf("\n 作业名 提交时间 需求时间 响应比 即时状态 主存需求 磁带机数量 \n"); 
    printf("   %s\t",pr->name); 
    printf("   %d\t",pr->ptime); 
    printf("   %d\t",pr->ntime); 
    printf("   %.2f\t",pr->super); 
    printf("   %c\t",pr->state); 
    printf("    %s\t",pr->needsources->memery); 
	printf("    %d\t",pr->needsources->machine); 
    printf(" \n"); 
}



void check() /* 建立作业查看函数 */ 
{ 
    JCB* pr; 
    printf("\n *********************当前正在运行的作业**********************");  /*显示当前运行作业*/ 
    disp(run); 
    pr=ready; 
    printf("\n **********************当前就绪队列状态************************");  /*显示就绪队列状态*/ 
    while(pr!=NULL) 
    { 
        disp(pr); 
        pr=pr->link; 
    } 
} 


void destroy() /*建立作业撤销函数)*/ 
{ 
	JCB *pr=run;
	run->ftime=Systemtime;
    printf("\n\t\t 【作业 [%s] 已完成...】\n",run->name); 
    printf("\n 开始时间 完成时间 周转时间 带权周转时间 释放主存资源 释放磁带机数量\n"); 
    printf("    %d\t",run->rtime); 
    printf("    %d\t",run->ftime); 
    printf("    %d\t",Systemtime-run->ptime);
    printf("    %f\t",(double)(Systemtime-run->ptime)/(double)run->ntime); 
    printf("     %s\t",run->needsources->memery);
	printf("     %d\t",run->needsources->machine);
    printf(" \n"); 
    JCBtime += Systemtime-run->ptime;                         /*更新总周转时间*/
    JCBtotaltime += JCBtime/(double)run->ntime;     /*更新总带权周转时间*/
    run=run->link;
	free(pr);
	pr=NULL;
} 

void running() /* 建立作业运行函数*/ 
{ 
	run->rtime=Systemtime;     /*作业开始时间为系统当前时间*/
	Systemtime += run->ntime;  /*更新系统时间*/
    destroy();
} 


void main() /*主函数*/ 
{ 
    int h=0; 
    char ch; 
	display();
    input();
	Systemtime=0;    /*初始系统时间*/
    while(ready!=NULL) 
    { 
        ch=getchar(); 
        h++; 
        printf("\n 【作业调度轮次:%d】 \n",h); 
        run=ready; 
        ready=ready->link; 
        run->link=NULL; 
        run->state='R'; 
        check(); 
        running(); 
        printf("\n\t\t 按任一键继续......"); 
        ch=getchar(); 
    } 
    printf("\n\n\t\t\t <<全部作业已经完成...>>\n"); 
    printf("\n\t\t 作业数量 平均周转时间  带权周转时间 \n"); 
	printf("\t\t   %d\t",JCBnum);
	printf("   %f\t",(double)JCBtime/(double)JCBnum); 
    printf("   %f\t",(double)JCBtotaltime/(double)JCBnum); 
    printf(" \n"); 
    ch=getchar(); 
} 







#include <stdio.h> 
#include <stdlib.h> 
#include <conio.h> 
#define getpch(type) (type*)malloc(sizeof(type)) 

int Select;
int Systemtime = 0;         /*ϵͳ��ʼʱ��*/
int JCBnum = 0;             /*����ҵ��*/
int JCBtime = 0;            /*����תʱ��*/
double JCBtotaltime =0;     /*�ܴ�Ȩ��תʱ��*/


struct source{              /*������Դ����ṹ*/
	char    memery[5];      /*��������*/
	int     machine;        /*�Ŵ�������*/
};

struct jcb {                /* ������ҵ���ƿ�PCB */ 
    char   name[10]; 
    char   state;           /* ״̬ */
    double super;           /* ��Ӧ������Ȩ */
    int    ntime;           /* ��Ҫ����ʱ�� */
    int    rtime;           /* ��ʼ����ʱ�� */
	int    ptime;           /*�ύʱ��*/
	int    ftime;           /*���ʱ��*/
    source *needsources;    /*��Դ������*/
    struct jcb* link;       /* ��һ����ҵ���ƿ�ĵ�ַ */
}*ready=NULL,*run,*p; 

typedef struct jcb JCB;
typedef struct source SOURCE;


void display()
{
 int c;
 do
 {
   system("cls");
   printf("\n\t\t          <<��ҵ������ʾ>>\n");
   printf("\n\t\t***************************************\t\t");
   printf("\n\t\t   1.�����ȷ����㷨.");
   printf("\n\t\t   2.��Ӧ�ȸ��������㷨");
   printf("\n\t\t   0.�˳�����.");
   printf("\n");
   printf("\t\t***********************************�ƿ�3�� �Ŵ�");
   printf("\n\t\t***************************************\t\t\n");
   printf("\t������ѡ����Ҫ����(0-2):");
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

void sort() /* �����Խ��̽������ȼ����к���*/ 
{ 
    JCB *first, *second,*temp; 
    int insert=0; 
	switch(Select)
	{

	case 1:                  /*������ȥ�����㷨*/
		if(ready==NULL)    /*���׿ղ������*/
		{
			p->link=ready;
			ready=p;
		}
		else                /*��������β*/
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

        if((ready==NULL)||((p->ntime)<(ready->ntime)))  / /*���� 
		{ 
            p->link=ready; 
            ready=p; 
		}
        else                   / /���������ʵ���λ�ò�
		{ 
            first=ready; 
            second=first->link; 
            while(second!=NULL)  / /��������м�		
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
			if(insert==0) first->link=p;   // �����β
        } 
        break;  */

	case 2:             /*��Ӧ�ȸ��������㷨*/
		                /*��Ӧ��=(�ȴ�ʱ��+����ʱ��)/����ʱ��*/

        temp=ready;
		p->super=(double)(Systemtime-p->ptime+p->ntime)/(double)(p->ntime);  /*������������ҵ����Ȩ*/
        while(temp)            /*�������������ҵ����Ȩ*/                                  
		{
			temp->super=(double)(Systemtime-temp->ptime+temp->ntime)/(double)(temp->ntime);
			temp=temp->link;
		}

        /*��Ӧ��Խ������ȨԽ��*/
		 if((ready==NULL)||((p->super)>(ready->ntime)))   /*����*/ 
		{ 
            p->link=ready; 
            ready=p; 
		}
        else                    /* ���������ʵ���λ�ò���*/ 
		{ 
            first=ready; 
            second=first->link; 
            while(second!=NULL)   /*��������м�*/		
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
			if(insert==0) first->link=p;   /* �����β*/ 
        } 
		break;

    default:
		break;
	}
}
 
 
void input() /* ������ҵ���뺯��*/ 
{
    int i,num;
	SOURCE *q;
    printf("\n\n��������ҵ��Ŀ:");
    scanf("%d",&num);
    JCBnum+=num;               /*����ҵ��*/
    for(i=0;i<num;i++)
    {
        printf("\n ����ҵ��No.%d��\n",i); 
        p=getpch(JCB);
        q=getpch(SOURCE);
        printf("��������ҵ��:");
        scanf("%s",p->name);
        getchar();
        printf("��������ҵ��Ҫ����ʱ��:");
		scanf("%d",&p->ntime);
        getchar();
        printf("��������ҵ������Դ����:");
        scanf("%s",q->memery);
        getchar();
        printf("��������ҵ�Ŵ�����������:");
        scanf("%d",&q->machine);
		p->needsources=q;
		p->ptime=Systemtime;                 /*��ҵ�ύʱ��ΪϵͳĬ��ʱ��*/
		p->super=0;                          
		p->ftime=0;                          /*��ҵ���ʱ��*/ 
        p->state='W';
        p->link=NULL;
		sort();
    }
}


void disp(JCB *pr) /*������ҵ��ʾ����*/ 
{ 
    printf("\n ��ҵ�� �ύʱ�� ����ʱ�� ��Ӧ�� ��ʱ״̬ �������� �Ŵ������� \n"); 
    printf("   %s\t",pr->name); 
    printf("   %d\t",pr->ptime); 
    printf("   %d\t",pr->ntime); 
    printf("   %.2f\t",pr->super); 
    printf("   %c\t",pr->state); 
    printf("    %s\t",pr->needsources->memery); 
	printf("    %d\t",pr->needsources->machine); 
    printf(" \n"); 
}



void check() /* ������ҵ�鿴���� */ 
{ 
    JCB* pr; 
    printf("\n *********************��ǰ�������е���ҵ**********************");  /*��ʾ��ǰ������ҵ*/ 
    disp(run); 
    pr=ready; 
    printf("\n **********************��ǰ��������״̬************************");  /*��ʾ��������״̬*/ 
    while(pr!=NULL) 
    { 
        disp(pr); 
        pr=pr->link; 
    } 
} 


void destroy() /*������ҵ��������)*/ 
{ 
	JCB *pr=run;
	run->ftime=Systemtime;
    printf("\n\t\t ����ҵ [%s] �����...��\n",run->name); 
    printf("\n ��ʼʱ�� ���ʱ�� ��תʱ�� ��Ȩ��תʱ�� �ͷ�������Դ �ͷŴŴ�������\n"); 
    printf("    %d\t",run->rtime); 
    printf("    %d\t",run->ftime); 
    printf("    %d\t",Systemtime-run->ptime);
    printf("    %f\t",(double)(Systemtime-run->ptime)/(double)run->ntime); 
    printf("     %s\t",run->needsources->memery);
	printf("     %d\t",run->needsources->machine);
    printf(" \n"); 
    JCBtime += Systemtime-run->ptime;                         /*��������תʱ��*/
    JCBtotaltime += JCBtime/(double)run->ntime;     /*�����ܴ�Ȩ��תʱ��*/
    run=run->link;
	free(pr);
	pr=NULL;
} 

void running() /* ������ҵ���к���*/ 
{ 
	run->rtime=Systemtime;     /*��ҵ��ʼʱ��Ϊϵͳ��ǰʱ��*/
	Systemtime += run->ntime;  /*����ϵͳʱ��*/
    destroy();
} 


void main() /*������*/ 
{ 
    int h=0; 
    char ch; 
	display();
    input();
	Systemtime=0;    /*��ʼϵͳʱ��*/
    while(ready!=NULL) 
    { 
        ch=getchar(); 
        h++; 
        printf("\n ����ҵ�����ִ�:%d�� \n",h); 
        run=ready; 
        ready=ready->link; 
        run->link=NULL; 
        run->state='R'; 
        check(); 
        running(); 
        printf("\n\t\t ����һ������......"); 
        ch=getchar(); 
    } 
    printf("\n\n\t\t\t <<ȫ����ҵ�Ѿ����...>>\n"); 
    printf("\n\t\t ��ҵ���� ƽ����תʱ��  ��Ȩ��תʱ�� \n"); 
	printf("\t\t   %d\t",JCBnum);
	printf("   %f\t",(double)JCBtime/(double)JCBnum); 
    printf("   %f\t",(double)JCBtotaltime/(double)JCBnum); 
    printf(" \n"); 
    ch=getchar(); 
} 







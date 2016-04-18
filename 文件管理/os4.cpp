#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL 0
#define getpch(type,num) (type*)malloc(sizeof(type)*num)

struct ufd{                /* �ڶ������û��ļ�Ŀ¼ UFD */
    char filename[10];     /* �ļ��� */ 
    char procode[3];       /* ������ 1:�� 2:д 3:ִ��*/
    int length;            /* �ļ����� */
    }*p;

typedef struct ufd UFD;

struct mdf{  	           /* ��һ������Ŀ¼ MDF */
    char name[10];         /* �û���  */
    UFD* directory;        /* �ļ�Ŀ¼ָ��  */
    }maindir[10];          /* �û����� */

typedef struct mdf MDF;



struct afd{                /* �ļ�����Ŀ¼ */
    char filename[10];     /* �ļ��� */ 
    char procode[3];       /* ������ 1:�� 2:д 3:ִ��*/
    int rw;                /* ��дָ�� ��ʼ״̬��:0 д:�ļ����� */
    }afd[5];

int usernum,opennum;       /* ��½�û����� ���ļ�����*/ 
int filenum[10];           /* ���е��û�Ŀ¼�µ��ļ���Ŀ*/
char username[10];         /* ��ǰ��½ϵͳ���û���*/
char command[][10]={"create","delete","open","close","read","write","display","quit"};  /*�ļ���������*/

void login()   /*�û�ע�ᣬ��Ϣд��database�ļ�*/
{
	int i,j;
    FILE *fp;  
	int loginum;
    int creatnum[10];
    printf("\t\t=====ע��ҳ��=====\n\n");
    printf("\t\t������ע����û�����:");
    scanf("%d",&loginum);
    for(i=0;i<loginum;i++)
    {
        printf("\t\t�������%d���û���:",i+1);
        scanf("%s",maindir[i].name);
    }
    for(i=0;i<loginum;i++)
    {
        printf("\t\t������%s�û��½��ļ���(С��10):",maindir[i].name);
        scanf("%d",&creatnum[i]);
        p=getpch(UFD,10);
        maindir[i].directory=p;
        for(j=0;j<creatnum[i];j++)
        {
            printf("\t\t�������½��ļ���:");
            scanf("%s",p[j].filename);
            printf("\t\t������Ҫ�������ļ�������(1:��,2:д,3:ִ��.):");
            scanf("%s",p[j].procode);
            printf("\t\t������Ҫ������ļ��ĳ���:");
            scanf("%d",&p[j].length);
        }
    }

    fp=fopen("database.txt","wb");
    fwrite(&loginum,sizeof(int),1,fp);                /* д��ע���û�������dat�ļ�*/
    for(i=0;i<loginum;i++)
    {
        fwrite(maindir[i].name,sizeof(char)*10,1,fp);  /* д��ע���û�����dat�ļ�*/
    }
    for(i=0;i<loginum;i++)
    { 
        fwrite(&creatnum[i],sizeof(int),1,fp);         /* д�û��½��ļ�������dat�ļ�*/
        p=maindir[i].directory;                       /* UFD����ļ�Ŀ¼ָ��*/ 
        fwrite(p,sizeof(UFD),10,fp);                  /* д�û��ļ�Ŀ¼ָ���ַ��dat�ļ�*/  
    }
    fclose(fp);
	printf("\n\t\t=====ע�����=====\n");
	printf("\n\t\t");
	system("pause");
	system("cls");
}

void init()     /*��ʼ������login��Ϣ*/
{
    int i,j;
    FILE *fp;
    fp=fopen("database.txt","rb");
	if(fp==NULL)
	{
		printf("\n\t����:��Ŀ¼�����ڼ�¼������ע���û�\n");
		login();
		fp=fopen("database.txt","rb");
	}
    fread(&usernum,sizeof(int),1,fp);              /* ������ע���û�����*/  
    for(i=0;i<usernum;i++)
    {
        fread(maindir[i].name,sizeof(char)*10,1,fp);  /* ������ע���û���*/
        p=getpch(UFD,10);
        maindir[i].directory=p;
    }
    for(i=0;i<usernum;i++)
    {
        fread(&j,sizeof(int),1,fp);
        filenum[i]=j;                             /*�����û��½��ļ�����*/
        p=maindir[i].directory;                   /*����ļ�Ŀ¼ָ��*/
        fread(p,sizeof(UFD),10,fp);               /*�����û��ļ�Ŀ¼ָ���ַp*/ 
    }
    opennum=0;                                   /*�����ļ���*/
}

void createfile(int userid)                 /*�½��ļ�*/
{
	system("cls");
    char cfilename[10];
    int  filelen,i;
    char code[3];
    if(filenum[userid]>=10)/*����û����ļ�����10��*/
    {
        printf("\n\t\t�û����ļ������Ѵﵽ����,��10��!\n");
        return ;
    }
    printf("\t\t=====�½��ļ�ҳ��=====\n\n");
    printf("\t\t������Ҫ�������ļ���:");
    scanf("%s",cfilename);
    for(i=0;i<filenum[userid];i++)    /*����Ƿ���ͬ���ļ�,������ʾȻ�󷵻�*/
	{
        if(strcmp((p+i)->filename,cfilename)==0)
    	{
            printf("\t\t�ļ���%s�Ѵ���!\n",cfilename);
			system("pause");
			system("cls");
            return ;
    	}
	}
    printf("\t\t������Ҫ�������ļ�������(1:�� 2:д 3:ִ��):");
    scanf("%s",code);
    printf("\t\t������Ҫ�������ļ��ĳ���:");
    scanf("%d",&filelen);
    strcpy(p[filenum[userid]].filename,cfilename); /*������ļ���*/
    strcpy(p[filenum[userid]].procode,code);       /*��ӱ�����*/
    p[filenum[userid]].length=filelen;             /*����ļ�����*/
    filenum[userid]=filenum[userid]+1;             /*�����ļ�����*/
    printf("\t\t==<%s>�ļ������ɹ�!==\n",cfilename);
	system("pause");
	system("cls");
}

void deletefile(int userid)          /*ɾ���ļ�*/
{
	system("cls");
    char dfilename[10];
    int i,j;
	printf("\t\t=====ɾ���ļ�ҳ��=====\n\n");
    printf("\t\t������Ҫɾ�����ļ���:");
    scanf("%s",dfilename);
    for(i=0;i<filenum[userid];i++)
    {
        if(strcmp(p[i].filename,dfilename)==0)/*�ҵ�Ҫɾ�����ļ�*/
    	{
            for(j=i;j<filenum[userid]-1;j++)
    		{
                strcpy(p[j].filename,p[j+1].filename);
                strcpy(p[j].procode,p[j+1].procode);
                p[j].length=p[j+1].length;
    			if(j==filenum[userid]-1)
				{
					strcpy(p[j+1].filename," ");
                    strcpy(p[j+1].filename," ");
                    p[j+1].length=0;
					free(p+j+1);
				}
    		}

            filenum[userid]--;
            printf("\t\t=====�ļ�ɾ���ɹ�!=====\n");
			system("pause");
	        system("cls");
            return ;
    	}
    }
    printf("\t\t�Ҳ���Ҫɾ�����ļ�!\n");
	system("pause");
	system("cls");
}

void openfile(int userid)        /*���ļ�*/
{
	system("cls");
    int i;
    char ofilename[10];
	printf("\t\t=====���ļ�ҳ��=====\n\n");
    if(opennum>=5)
    {
        printf("\t\t�򿪳���5���ļ�!\n");
        return ;		
    }
    printf("\t\t������Ҫ�򿪵��ļ����ļ���:");
    scanf("%s",ofilename);
    for(i=0;i<opennum;i++)
    {
        if(strcmp(afd[i].filename,ofilename)==0)  /*�ļ��Ѿ���*/
    	{
            printf("\t\t�ļ�%s�Ѵ�!\n",ofilename);
            return ;
    	}
    }
    for(i=0;i<filenum[userid];i++)              /*�������ļ�Ŀ¼���ҵ�Ҫ�򿪵��ļ�*/
    {
        if(strcmp(p[i].filename,ofilename)==0)   /*�ҵ����ļ�*/
    	{
            strcpy(afd[opennum].filename,ofilename);  /*�ļ�����Ŀ¼��Ӵ��ļ���*/
            strcpy(afd[opennum].procode,p[i].procode);  /*�ļ�����Ŀ¼����ļ�������*/
            afd[opennum].rw=0;                         /*�����ļ�����Ŀ¼�ļ���дָ��*/
            opennum++;
            printf("\t\t�ļ�%s�Ѵ�!\n",ofilename);
			printf("\t\t=====���ļ��ɹ�=====\n\n");
		    system("pause");
	        system("cls");
            return ;
    	}
    }
    printf("�򲻵�Ҫ�ļ��򿪵��ļ�,���ļ�ʧ��!\n");
	system("pause");
	system("cls");
}

void closefile()           /*�ر��ļ�*/
{
	system("cls");
    int i,j;
    char clfilename[10];
    if(opennum==0)       /*û���ļ����򿪹�*/
    {
        printf("\t\t��ǰ��û�д��ļ�!\n");
        return ;		
    }
	printf("\t\t=====ɾ���ļ�ҳ��=====\n\n");
    printf("\t\t������Ҫ�رյ��ļ���:");
    scanf("%s",clfilename);
    for(i=0;i<opennum;i++)
    {
        if(strcmp(afd[i].filename,clfilename)==0)/*�������ļ�Ŀ¼���ҵ�Ҫ�رյ��ļ�*/
    	{
            if(afd[i].rw==1)
    		{
                printf("\t\t�ļ�д�ش���!\n");
    		}
            for(j=i;j<opennum-1;j++)               /*�����ļ�����Ŀ¼���ر��ļ�*/
    		{
                strcpy(afd[j].filename,afd[j+1].filename);
                strcpy(afd[j].procode,afd[j+1].procode);
                afd[j].rw=afd[j+1].rw;
    		}
            opennum--;
            printf("\t\t�ļ�%s�ѳɹ��ر�!\n",clfilename);
			printf("\t\t=====�ر��ļ��ɹ�=====\n\n");
		    system("pause");
	        system("cls");
            return ;
    	}
    }
    printf("\t\t�ļ�%sû�д�!�ر�ʧ��!\n",clfilename);
	system("pause");
	system("cls");
}

void readfile()         /*�����ļ�*/
{
	system("cls");
    int i;
    char rfilename[10];
    if(opennum==0)     /*û���ļ����򿪹�*/
    {
        printf("\t\t�������󣬵�ǰ��û�д��ļ�!\n");
		system("pause");
	    system("cls");
        return ;		
    }
	printf("\t\t=====�����ļ�ҳ��=====\n\n");
    printf("������Ҫ������ļ���:");
    scanf("%s",rfilename);
    for(i=0;i<opennum;i++)
    {
        if(strcmp(afd[i].filename,rfilename)==0)/*�������ļ�Ŀ¼���ҵ�Ҫ�����ļ�*/
    	{
            if(afd[i].procode[0]!='1')/*�ļ�û�ж�Ȩ��,����ִ�ж�����,��ʾ����*/
    		{
                printf("\t\tȨ�޲��㣬���ļ����ܶ�!��ʧ��!\n");
            	return ;
    		}
            printf("\t\t�ļ�%s�Ѷ���!\n",rfilename);
			printf("\t\t=====�����ļ��ɹ�=====\n\n");
			system("pause");
	        system("cls");
            break ;
    	}
    }
}

void writefile()       /*д���ļ�*/
{
    system("cls");
    int i;
    char wfilename[10];
    if(opennum==0)    /*û���ļ����򿪹�*/
    {
        printf("\t\t��ǰ��û�д��ļ�!\n");
	    system("pause");
	    system("cls");
        return ;		
    }
	printf("\t\t=====д���ļ�ҳ��=====\n\n");
    printf("\t\t������Ҫд���ļ����ļ���:");
    scanf("%s",wfilename);
    for(i=0;i<opennum;i++)
    {
        if(strcmp(afd[i].filename,wfilename)==0)/*�������ļ�Ŀ¼���ҵ�Ҫ�رյ��ļ�*/
    	{
            if(p[i].procode[1]!='1')/*�ļ�û��дȨ��,����ִ��д����,��ʾ����*/
    		{
                printf("\t\t���ļ�����д!дʧ��!\n");
            	return ;
    		}
            afd[i].rw=1;
            printf("\t\t�ļ�%s��д��!\n",wfilename);
			printf("\t\t=====д���ļ��ɹ�=====\n\n");
            return ;
    	}
    }
    printf("\t\t�������󣬵�ǰ�ļ�%s��û�д�!\n");
	system("pause");
	system("cls");
}

void  displayinfo()     /*��ʾ�����û�Ŀ¼�ļ���Ϣ*/
{
	system("cls");
    int i,j;
	printf("\t=================================\n");
    for(i=0;i<usernum;i++)    /*��½ҳ���û��б���ʾ*/
    {   	       
        printf("\n\t�û���\t�ļ���\t������\t�ļ�����\n");
		printf("\t%s",maindir[i].name);
        for(j=0;j<filenum[i];j++)
        {
			if(j!=0)printf("\t");
            printf("\t%s\t%s\t%d\n",maindir[i].directory[j].filename,maindir[i].directory[j].procode,maindir[i].directory[j].length);
        }
	}
    printf("\t=================================\n");
    printf("\t�Ѿ����ļ��б�:\n\t\t�ļ���\t������\t��дָ��(Ϊ1��ʾ�ѽ��й�д����)\n");
    for(i=0;i<opennum;i++)
    {
        printf("%s\t%s\t%d\n",afd[i].filename,afd[i].procode,afd[i].rw);
    }
	system("pause");
	system("cls");
}

void savefile()  /*�������*/
{   
    /*��ʼ������Ĺ�����Ϣд�뵽�ļ�dat*/
    int i;
    FILE *fp;
    fp=fopen("database.txt","wb");
    fwrite(&usernum,sizeof(int),1,fp);
    for(i=0;i<usernum;i++)
    {
        fwrite(maindir[i].name,sizeof(char)*10,1,fp);
    }
    for(i=0;i<usernum;i++)
    {
        fwrite(&filenum[i],sizeof(int),1,fp);
        p=maindir[i].directory;
        fwrite(p,sizeof(UFD),10,fp);
    }
    fclose(fp);
    printf("\t\t��ǰĿ¼��Ϣ���Զ��������ļ�database!\n");
}


void main()
{
    int i,j,n,userid,choose=0,quit=0;
    char inputname[10];
	system("cls");
	printf("\n\t   ----10���������ѧ�뼼��03��---");
	printf("\n\t    -----�ƿ�3�Ŵ�----\n");
	printf("\n\t\t=====��ҳ��=====\n");
    printf("\n\t\t   1.ע���û�");
    printf("\n\t\t   2.��½�û�");
    printf("\n\t\t================\n");
	printf("\t\t�������������:");
	scanf("%d",&n);
    if(n==1)
	{
		login();    /*�û�ע�ᣬ�û��ļ���Ϣд��dat�ļ�*/
	}
    init();     /*��Ϣ��ʼ��*/
	system("cls");
	for(i=0;i<usernum;i++)    /*��½ҳ���û��б���ʾ*/
    {   	       
        printf("\n\t�û���\t�ļ���\t������\t�ļ�����\n");
		printf("\t%s",maindir[i].name);
        for(j=0;j<filenum[i];j++)
        {
			if(j!=0)printf("\t");
            printf("\t%s\t%s\t%d\n",maindir[i].directory[j].filename,maindir[i].directory[j].procode,maindir[i].directory[j].length);
        }
	}
	printf("\n\t\t=====��½ҳ��=====\n\n");
    j=0;
    while(j==0)
	{
    	printf("\n\t\t�������¼�û���:");               /*�û���½*/
	    scanf("%s",username);
        for(userid=0;userid<usernum;userid++)
		{
			if(strcmp(maindir[userid].name,username)==0)  /*�û�����*/
			{
        		j=1;
				break;
			}
		}
		if(j==1)
		{
			break;
		}
		printf("\n\t\t������û���������!\n");               /*�û�������*/
	}
    p=maindir[userid].directory;                     /*����û��ļ�Ŀ¼ָ��*/
    printf("\n\t\t======�û�%sĿ¼�µ��ļ�======\n",username);
    for(i=0;i<filenum[userid];i++)
	{
        printf("\n\t\t%s",p[i].filename);               /*��ʾ���û��ļ��б�*/
    }
    printf("\n\t\t");
	system("pause");
	system("cls");
	opennum=0;
    while(true)                        /*������Ŀ¼*/
    {    
		j=0;
        system("cls");
        printf("\n\t\t             <<�ļ�ϵͳ��ʾ>>\n");
        printf("\n\t\t*********************************************\t\t");
        printf("\n\t\t\t   create  �½��ļ�.");
        printf("\n\t\t\t   delete  ɾ���ļ�.");
        printf("\n\t\t\t   open    ���ļ�.");
        printf("\n\t\t\t   close   �ر��ļ�.");
        printf("\n\t\t\t   read    �����ļ�.");
        printf("\n\t\t\t   write   д���ļ�.");
		printf("\n\t\t\t   display ��ʾ�û��б�.");
        printf("\n\t\t\t   quit    ��ȫ�˳�.");
        printf("\n\t\t*********************************************\t\t\n");
		printf("\t\t��������:create delete open close read write display quit\n");  
        printf("\t\t�������������:");        
		scanf("%s",inputname);
		getchar();
        for(i=0;i<8;++i)
		{
			if(strcmp(command[i],inputname)==0)   /*�������*/
			{
				j=1;
        	    choose=i+1;
                break;
			}
		}
        if(j==0)
		{
			printf("���������ȷ!"); 
			system("pause");
			continue;
		}
	
        switch(choose)
    	{

        case 1:
               createfile(userid);
               break;
               
        case 2:
               deletefile(userid);
               break;

        case 3:

               openfile(userid);
               break;   

        case 4:
               closefile();
               break;
      
        case 5:
               readfile();
			   break;

        case 6:
               writefile();
			   break;

        case 7:
			   displayinfo();
			   break;

        case 8: 
			   quit=1;
			   break;

        default:
               break;
    	}

		if(quit==1)break;
	}
  	savefile();
}
 













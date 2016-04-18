#include<stdio.h>
#include<stdlib.h>
#include<iostream>
#define NULL 0
#define getpch(type,num) (type*)malloc(sizeof(type)*num)

struct ufd{                /* 第二级：用户文件目录 UFD */
    char filename[10];     /* 文件名 */ 
    char procode[3];       /* 保护码 1:读 2:写 3:执行*/
    int length;            /* 文件长度 */
    }*p;

typedef struct ufd UFD;

struct mdf{  	           /* 第一级：主目录 MDF */
    char name[10];         /* 用户名  */
    UFD* directory;        /* 文件目录指针  */
    }maindir[10];          /* 用户数组 */

typedef struct mdf MDF;



struct afd{                /* 文件运行目录 */
    char filename[10];     /* 文件名 */ 
    char procode[3];       /* 保护码 1:读 2:写 3:执行*/
    int rw;                /* 读写指针 初始状态读:0 写:文件长度 */
    }afd[5];

int usernum,opennum;       /* 登陆用户数量 打开文件数量*/ 
int filenum[10];           /* 所有的用户目录下的文件数目*/
char username[10];         /* 当前登陆系统的用户名*/
char command[][10]={"create","delete","open","close","read","write","display","quit"};  /*文件操作命令*/

void login()   /*用户注册，信息写入database文件*/
{
	int i,j;
    FILE *fp;  
	int loginum;
    int creatnum[10];
    printf("\t\t=====注册页面=====\n\n");
    printf("\t\t请输入注册的用户数量:");
    scanf("%d",&loginum);
    for(i=0;i<loginum;i++)
    {
        printf("\t\t请输入第%d个用户名:",i+1);
        scanf("%s",maindir[i].name);
    }
    for(i=0;i<loginum;i++)
    {
        printf("\t\t请输入%s用户新建文件数(小于10):",maindir[i].name);
        scanf("%d",&creatnum[i]);
        p=getpch(UFD,10);
        maindir[i].directory=p;
        for(j=0;j<creatnum[i];j++)
        {
            printf("\t\t请输入新建文件名:");
            scanf("%s",p[j].filename);
            printf("\t\t请输入要建立的文件的属性(1:读,2:写,3:执行.):");
            scanf("%s",p[j].procode);
            printf("\t\t请输入要构造的文件的长度:");
            scanf("%d",&p[j].length);
        }
    }

    fp=fopen("database.txt","wb");
    fwrite(&loginum,sizeof(int),1,fp);                /* 写已注册用户数量到dat文件*/
    for(i=0;i<loginum;i++)
    {
        fwrite(maindir[i].name,sizeof(char)*10,1,fp);  /* 写已注册用户名到dat文件*/
    }
    for(i=0;i<loginum;i++)
    { 
        fwrite(&creatnum[i],sizeof(int),1,fp);         /* 写用户新建文件数量到dat文件*/
        p=maindir[i].directory;                       /* UFD获得文件目录指针*/ 
        fwrite(p,sizeof(UFD),10,fp);                  /* 写用户文件目录指针地址到dat文件*/  
    }
    fclose(fp);
	printf("\n\t\t=====注册完毕=====\n");
	printf("\n\t\t");
	system("pause");
	system("cls");
}

void init()     /*初始化读入login信息*/
{
    int i,j;
    FILE *fp;
    fp=fopen("database.txt","rb");
	if(fp==NULL)
	{
		printf("\n\t警告:根目录不存在记录，请先注册用户\n");
		login();
		fp=fopen("database.txt","rb");
	}
    fread(&usernum,sizeof(int),1,fp);              /* 读入已注册用户数量*/  
    for(i=0;i<usernum;i++)
    {
        fread(maindir[i].name,sizeof(char)*10,1,fp);  /* 读入已注册用户名*/
        p=getpch(UFD,10);
        maindir[i].directory=p;
    }
    for(i=0;i<usernum;i++)
    {
        fread(&j,sizeof(int),1,fp);
        filenum[i]=j;                             /*读入用户新建文件数量*/
        p=maindir[i].directory;                   /*获得文件目录指针*/
        fread(p,sizeof(UFD),10,fp);               /*读入用户文件目录指针地址p*/ 
    }
    opennum=0;                                   /*运行文件数*/
}

void createfile(int userid)                 /*新建文件*/
{
	system("cls");
    char cfilename[10];
    int  filelen,i;
    char code[3];
    if(filenum[userid]>=10)/*如果用户的文件已有10个*/
    {
        printf("\n\t\t用户的文件数量已达到上限,即10个!\n");
        return ;
    }
    printf("\t\t=====新建文件页面=====\n\n");
    printf("\t\t请输入要建立的文件名:");
    scanf("%s",cfilename);
    for(i=0;i<filenum[userid];i++)    /*检查是否有同名文件,有则提示然后返回*/
	{
        if(strcmp((p+i)->filename,cfilename)==0)
    	{
            printf("\t\t文件名%s已存在!\n",cfilename);
			system("pause");
			system("cls");
            return ;
    	}
	}
    printf("\t\t请输入要建立的文件的属性(1:读 2:写 3:执行):");
    scanf("%s",code);
    printf("\t\t请输入要建立的文件的长度:");
    scanf("%d",&filelen);
    strcpy(p[filenum[userid]].filename,cfilename); /*添加新文件名*/
    strcpy(p[filenum[userid]].procode,code);       /*添加保护码*/
    p[filenum[userid]].length=filelen;             /*添加文件长度*/
    filenum[userid]=filenum[userid]+1;             /*更新文件数量*/
    printf("\t\t==<%s>文件建立成功!==\n",cfilename);
	system("pause");
	system("cls");
}

void deletefile(int userid)          /*删除文件*/
{
	system("cls");
    char dfilename[10];
    int i,j;
	printf("\t\t=====删除文件页面=====\n\n");
    printf("\t\t请输入要删除的文件名:");
    scanf("%s",dfilename);
    for(i=0;i<filenum[userid];i++)
    {
        if(strcmp(p[i].filename,dfilename)==0)/*找到要删除的文件*/
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
            printf("\t\t=====文件删除成功!=====\n");
			system("pause");
	        system("cls");
            return ;
    	}
    }
    printf("\t\t找不到要删除的文件!\n");
	system("pause");
	system("cls");
}

void openfile(int userid)        /*打开文件*/
{
	system("cls");
    int i;
    char ofilename[10];
	printf("\t\t=====打开文件页面=====\n\n");
    if(opennum>=5)
    {
        printf("\t\t打开超过5个文件!\n");
        return ;		
    }
    printf("\t\t请输入要打开的文件的文件名:");
    scanf("%s",ofilename);
    for(i=0;i<opennum;i++)
    {
        if(strcmp(afd[i].filename,ofilename)==0)  /*文件已经打开*/
    	{
            printf("\t\t文件%s已打开!\n",ofilename);
            return ;
    	}
    }
    for(i=0;i<filenum[userid];i++)              /*在运行文件目录中找到要打开的文件*/
    {
        if(strcmp(p[i].filename,ofilename)==0)   /*找到该文件*/
    	{
            strcpy(afd[opennum].filename,ofilename);  /*文件运行目录添加打开文件名*/
            strcpy(afd[opennum].procode,p[i].procode);  /*文件运行目录添加文件保护码*/
            afd[opennum].rw=0;                         /*更新文件运行目录文件读写指针*/
            opennum++;
            printf("\t\t文件%s已打开!\n",ofilename);
			printf("\t\t=====打开文件成功=====\n\n");
		    system("pause");
	        system("cls");
            return ;
    	}
    }
    printf("打不到要文件打开的文件,打开文件失败!\n");
	system("pause");
	system("cls");
}

void closefile()           /*关闭文件*/
{
	system("cls");
    int i,j;
    char clfilename[10];
    if(opennum==0)       /*没有文件被打开过*/
    {
        printf("\t\t当前还没有打开文件!\n");
        return ;		
    }
	printf("\t\t=====删除文件页面=====\n\n");
    printf("\t\t请输入要关闭的文件名:");
    scanf("%s",clfilename);
    for(i=0;i<opennum;i++)
    {
        if(strcmp(afd[i].filename,clfilename)==0)/*在运行文件目录中找到要关闭的文件*/
    	{
            if(afd[i].rw==1)
    		{
                printf("\t\t文件写回磁盘!\n");
    		}
            for(j=i;j<opennum-1;j++)               /*更新文件运行目录，关闭文件*/
    		{
                strcpy(afd[j].filename,afd[j+1].filename);
                strcpy(afd[j].procode,afd[j+1].procode);
                afd[j].rw=afd[j+1].rw;
    		}
            opennum--;
            printf("\t\t文件%s已成功关闭!\n",clfilename);
			printf("\t\t=====关闭文件成功=====\n\n");
		    system("pause");
	        system("cls");
            return ;
    	}
    }
    printf("\t\t文件%s没有打开!关闭失败!\n",clfilename);
	system("pause");
	system("cls");
}

void readfile()         /*读入文件*/
{
	system("cls");
    int i;
    char rfilename[10];
    if(opennum==0)     /*没有文件被打开过*/
    {
        printf("\t\t操作错误，当前还没有打开文件!\n");
		system("pause");
	    system("cls");
        return ;		
    }
	printf("\t\t=====读入文件页面=====\n\n");
    printf("请输入要读入的文件名:");
    scanf("%s",rfilename);
    for(i=0;i<opennum;i++)
    {
        if(strcmp(afd[i].filename,rfilename)==0)/*在运行文件目录中找到要读的文件*/
    	{
            if(afd[i].procode[0]!='1')/*文件没有读权限,将不执行读操作,提示返回*/
    		{
                printf("\t\t权限不足，该文件不能读!读失败!\n");
            	return ;
    		}
            printf("\t\t文件%s已读完!\n",rfilename);
			printf("\t\t=====读入文件成功=====\n\n");
			system("pause");
	        system("cls");
            break ;
    	}
    }
}

void writefile()       /*写出文件*/
{
    system("cls");
    int i;
    char wfilename[10];
    if(opennum==0)    /*没有文件被打开过*/
    {
        printf("\t\t当前还没有打开文件!\n");
	    system("pause");
	    system("cls");
        return ;		
    }
	printf("\t\t=====写出文件页面=====\n\n");
    printf("\t\t请输入要写的文件的文件名:");
    scanf("%s",wfilename);
    for(i=0;i<opennum;i++)
    {
        if(strcmp(afd[i].filename,wfilename)==0)/*在运行文件目录中找到要关闭的文件*/
    	{
            if(p[i].procode[1]!='1')/*文件没有写权限,将不执行写操作,提示返回*/
    		{
                printf("\t\t该文件不能写!写失败!\n");
            	return ;
    		}
            afd[i].rw=1;
            printf("\t\t文件%s已写完!\n",wfilename);
			printf("\t\t=====写出文件成功=====\n\n");
            return ;
    	}
    }
    printf("\t\t操作错误，当前文件%s还没有打开!\n");
	system("pause");
	system("cls");
}

void  displayinfo()     /*显示所有用户目录文件信息*/
{
	system("cls");
    int i,j;
	printf("\t=================================\n");
    for(i=0;i<usernum;i++)    /*登陆页面用户列表显示*/
    {   	       
        printf("\n\t用户名\t文件名\t保护码\t文件长度\n");
		printf("\t%s",maindir[i].name);
        for(j=0;j<filenum[i];j++)
        {
			if(j!=0)printf("\t");
            printf("\t%s\t%s\t%d\n",maindir[i].directory[j].filename,maindir[i].directory[j].procode,maindir[i].directory[j].length);
        }
	}
    printf("\t=================================\n");
    printf("\t已经打开文件列表:\n\t\t文件名\t保护码\t读写指针(为1表示已进行过写操作)\n");
    for(i=0;i<opennum;i++)
    {
        printf("%s\t%s\t%d\n",afd[i].filename,afd[i].procode,afd[i].rw);
    }
	system("pause");
	system("cls");
}

void savefile()  /*保存操作*/
{   
    /*开始把输入的构造信息写入到文件dat*/
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
    printf("\t\t当前目录信息已自动保存至文件database!\n");
}


void main()
{
    int i,j,n,userid,choose=0,quit=0;
    char inputname[10];
	system("cls");
	printf("\n\t   ----10级计算机科学与技术03班---");
	printf("\n\t    -----计科3张大川----\n");
	printf("\n\t\t=====主页面=====\n");
    printf("\n\t\t   1.注册用户");
    printf("\n\t\t   2.登陆用户");
    printf("\n\t\t================\n");
	printf("\t\t请输入操作命令:");
	scanf("%d",&n);
    if(n==1)
	{
		login();    /*用户注册，用户文件信息写入dat文件*/
	}
    init();     /*信息初始化*/
	system("cls");
	for(i=0;i<usernum;i++)    /*登陆页面用户列表显示*/
    {   	       
        printf("\n\t用户名\t文件名\t保护码\t文件长度\n");
		printf("\t%s",maindir[i].name);
        for(j=0;j<filenum[i];j++)
        {
			if(j!=0)printf("\t");
            printf("\t%s\t%s\t%d\n",maindir[i].directory[j].filename,maindir[i].directory[j].procode,maindir[i].directory[j].length);
        }
	}
	printf("\n\t\t=====登陆页面=====\n\n");
    j=0;
    while(j==0)
	{
    	printf("\n\t\t请输入登录用户名:");               /*用户登陆*/
	    scanf("%s",username);
        for(userid=0;userid<usernum;userid++)
		{
			if(strcmp(maindir[userid].name,username)==0)  /*用户存在*/
			{
        		j=1;
				break;
			}
		}
		if(j==1)
		{
			break;
		}
		printf("\n\t\t输入的用户名不存在!\n");               /*用户不存在*/
	}
    p=maindir[userid].directory;                     /*获得用户文件目录指针*/
    printf("\n\t\t======用户%s目录下的文件======\n",username);
    for(i=0;i<filenum[userid];i++)
	{
        printf("\n\t\t%s",p[i].filename);               /*显示该用户文件列表*/
    }
    printf("\n\t\t");
	system("pause");
	system("cls");
	opennum=0;
    while(true)                        /*操作主目录*/
    {    
		j=0;
        system("cls");
        printf("\n\t\t             <<文件系统演示>>\n");
        printf("\n\t\t*********************************************\t\t");
        printf("\n\t\t\t   create  新建文件.");
        printf("\n\t\t\t   delete  删除文件.");
        printf("\n\t\t\t   open    打开文件.");
        printf("\n\t\t\t   close   关闭文件.");
        printf("\n\t\t\t   read    读出文件.");
        printf("\n\t\t\t   write   写进文件.");
		printf("\n\t\t\t   display 显示用户列表.");
        printf("\n\t\t\t   quit    安全退出.");
        printf("\n\t\t*********************************************\t\t\n");
		printf("\t\t操作命令:create delete open close read write display quit\n");  
        printf("\t\t请输入操作命令:");        
		scanf("%s",inputname);
		getchar();
        for(i=0;i<8;++i)
		{
			if(strcmp(command[i],inputname)==0)   /*命令存在*/
			{
				j=1;
        	    choose=i+1;
                break;
			}
		}
        if(j==0)
		{
			printf("输入命令不正确!"); 
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
 













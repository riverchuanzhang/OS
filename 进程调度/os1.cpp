#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
//进程结构
class JCB
{
public:
	string name;
	int cometime;
	int sertime;
	bool run;
	JCB * next;
public:
	JCB(string tn="",int tc=-1,int ser=0,bool tr=false,JCB *nex=NULL)
		:name(tn),cometime(tc),sertime(ser),run(tr),next(nex)
	{}
	void show()
	{
		cout<<"\t进程名："<<name<<"\t到达时间："<<cometime<<"\t服务时间："<<sertime<<endl;
	}
};

//进程的排序，按照进程的提交时间先后排序
void sort(JCB *head)
{
	JCB *q,*s,*p=head->next;
	head->next=NULL;
	while(p!=NULL)
	{
		q=p->next;
		if(head->next==NULL)
		{
			p->next=head->next;
			head->next=p;
		}
		else
		{
			s=head;
			while(p->cometime>s->next->cometime)
			{
				s=s->next;
			}
			p->next=s->next;
			s->next=p;
		}
		p=q;
	}
}
//辅助函数，查找JCB
JCB * getJCB(JCB *q,JCB *p)
{
	JCB *find=q;
	int minsertime=q->sertime;
	while(q!=p)
	{
		if(q->sertime<minsertime&&q->run==false)
		{
			minsertime=q->sertime;
			find=q;
		}
		q=q->next;
	}
	return find;
}
//shadule调度函数
//
void shadule(JCB *head,int n)
{
	JCB *s,*q,*p=head->next;
	JCB *sp;
	int sum_rolltime=p->sertime-p->cometime;
	int waittime=p->cometime;
	int sum_rollsertime=p->sertime;
	int i=1;
	sp=p;
	for(int num=0;num<n;num++)
	{
		while(p->run==true)
			p=p->next;
		q=p;
		while(p!=NULL&&p->cometime<=waittime)
			p=p->next;
		s=getJCB(q,p);
		cout<<"第 "<<i++<<" 个调度进程：";
		s->show();
		s->run=true;
		waittime+=s->sertime;
		cout<<"完成时间(下一个进程开始时间)："<<waittime<<"\t周转时间："<<waittime-(s->cometime)
			<<"\t带权周转时间："<<waittime/float(s->sertime)<<endl;
		sum_rolltime+=(waittime-(s->cometime));
		sum_rollsertime+=s->sertime;
		p=sp;
	}
	cout<<"/////////////////////////平均周转时间："<<sum_rolltime/float(n)<<endl;
	cout<<"/////////////////////////平均带权周转时间："<<sum_rolltime/float(sum_rollsertime)<<endl;
	system("pause");
}



void main()
{
	int num;
	string name;
	int cometime,sertime;
	cout<<" ------进程调度-----"<<endl;
	cout<<"    ----张大川3110005966-----"<<endl;

	cout<<"      输入进程个数："<<endl;
	cin>>num;
	JCB *head=new JCB();
	
	for(int i=0;i<num;++i){
		cout<<"输入进程名:\t";
		cin>>name;
		cout<<"输入进程 "<<i<<" 的到达时间和服务时间:"<<endl;
		cin>>cometime>>sertime;
		JCB *p=new JCB(name,cometime,sertime,false,head->next);
		head->next=p;
	}
	sort(head);
	shadule(head,num);
}


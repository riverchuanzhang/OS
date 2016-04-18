#include<iostream>
#include<string>
#include<stdio.h>
using namespace std;
//���̽ṹ
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
		cout<<"\t��������"<<name<<"\t����ʱ�䣺"<<cometime<<"\t����ʱ�䣺"<<sertime<<endl;
	}
};

//���̵����򣬰��ս��̵��ύʱ���Ⱥ�����
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
//��������������JCB
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
//shadule���Ⱥ���
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
		cout<<"�� "<<i++<<" �����Ƚ��̣�";
		s->show();
		s->run=true;
		waittime+=s->sertime;
		cout<<"���ʱ��(��һ�����̿�ʼʱ��)��"<<waittime<<"\t��תʱ�䣺"<<waittime-(s->cometime)
			<<"\t��Ȩ��תʱ�䣺"<<waittime/float(s->sertime)<<endl;
		sum_rolltime+=(waittime-(s->cometime));
		sum_rollsertime+=s->sertime;
		p=sp;
	}
	cout<<"/////////////////////////ƽ����תʱ�䣺"<<sum_rolltime/float(n)<<endl;
	cout<<"/////////////////////////ƽ����Ȩ��תʱ�䣺"<<sum_rolltime/float(sum_rollsertime)<<endl;
	system("pause");
}



void main()
{
	int num;
	string name;
	int cometime,sertime;
	cout<<" ------���̵���-----"<<endl;
	cout<<"    ----�Ŵ�3110005966-----"<<endl;

	cout<<"      ������̸�����"<<endl;
	cin>>num;
	JCB *head=new JCB();
	
	for(int i=0;i<num;++i){
		cout<<"���������:\t";
		cin>>name;
		cout<<"������� "<<i<<" �ĵ���ʱ��ͷ���ʱ��:"<<endl;
		cin>>cometime>>sertime;
		JCB *p=new JCB(name,cometime,sertime,false,head->next);
		head->next=p;
	}
	sort(head);
	shadule(head,num);
}


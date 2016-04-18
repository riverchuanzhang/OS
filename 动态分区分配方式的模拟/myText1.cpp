#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;
struct memory
{
	struct memory *former;
	int address;//��ַ
	int num;//��ҵ��
	int size;//�����ڴ��С
	int state;//״̬0��ʾ����1��ʾ�ѷ���
	struct memory *next;
};
typedef struct memory MEMORY;
MEMORY *mem;
const int size_min=10;//�ڴ��������С���п�Ĵ�С
bool is_optimist=false;//�ж��Ƿ��������Ӧ�㷨

void init();
void FF();
void alloc(MEMORY *,MEMORY *);//�״���Ӧ�㷨�����ڴ�
void free(MEMORY *);//�״���Ӧ�㷨�����ڴ�
void sort(MEMORY *);//���ڴ�����������
void insert(MEMORY *,MEMORY *);
void free_optimist(MEMORY *);
void print(MEMORY *);//��ӡ�ڴ���
void main()
{
	int i=0;
	while(1)
	{   
		cout<<" ------��̬�������䷽ʽ-----"<<endl;
	    cout<<"    ----�Ŵ�3110005966-----"<<endl;
		cout<<("Please select a number(1,2,0)");
		cout<<("\n 1--�״���Ӧ�㷨");
		cout<<"\n 2--�����Ӧ�㷨"<<endl;
		cout<<"    0--��ֹ����"<<endl;
		cin>>i;

		if(i==1)
		{
			cout<<("\nThis is an example for FF:\n");
			is_optimist=false;
			init();
			FF();
		}
		else if(i==2)
		{
			cout<<"\nThis is an example for optimist method;\n";
			is_optimist=true;
			init();
			FF();

		}
		else if(i==0)
		{
			exit(1);
		}
	}
}
void init()
{
	mem=new MEMORY;
	mem->size=640;
	//mem->state=0;
	mem->former=0;
	mem->next=0;
}
void FF()//�״���Ӧ�㷨
{
	int i;
	int work[]={130,60,100,200,140,60,50,60};//��ҵ����
	//int assignment;
	MEMORY *running;
	for(i=0;i<sizeof(work)/sizeof(int);i++)
	{
		running=(MEMORY *)malloc(sizeof(MEMORY));//��ʼ����ҵ
		if(running!=NULL)
		{
			running->former=NULL;
			running->address=0;
			running->num=i+1;
			running->size=work[i];
			running->state=0;
			running->next=NULL;
			//cout<<"��ҵ��ʼ���ɹ�"<<running->num<<endl;
			if(is_optimist==true)//�����Ӧ�㷨
			{
				//cout<<"xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx"<<endl;
				alloc(mem,running);
			}
			else//�״���Ӧ�㷨
			{
				alloc(mem,running);
			}
			print(mem);
			cout<<endl;
		}
		else
			cout<<"û���㹻���ڴ�ռ�"<<endl;


		if(rand()%3==1)
		{
			if(is_optimist==false)//�״���Ӧ�㷨
			{
				free(mem);
			}
			else//�����Ӧ�㷨
			{
				::free_optimist(mem);
			}
		}
	}
}
void free(MEMORY *ptr)//��ҵ��������ͷ��ڴ�ռ�
{
	MEMORY *previous,*current;
	previous=ptr;
	current=previous->next;
	while(current!=NULL)
	{
		if(current->state==1&&rand()%3==1)
		{
			break;
		}
		previous=current;
		current=current->next;
	}
	if(current==NULL)
	{
		//cout<<"�ڴ���û���κ���ҵ������"<<endl;
		return;
	}
	else if(current->next==NULL)
	{
		if(previous->state==0)
		{
			MEMORY *temp;
			temp=current;
			previous->size=previous->size+current->size;
			previous->next=NULL;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			delete temp;
			print(mem);
		}
		else
		{
			current->state=0;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			print(mem);
		}
	}
	else if((current->next)->next==NULL)
	{
		if(previous->state==0&&(current->next)->state==0)
		{
			MEMORY *temp1,*temp2;
			temp1=current;
			temp2=current->next;
			previous->size=previous->size+current->size+(current->next)->size;
			previous->next=NULL;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			delete temp1;
			delete temp2;
			print(mem);
		}
		else if(previous->state==0)//�ͷŵĵ�ַ�ռ�ǰ���п��п��������ǰ��ĺϲ�
		{
			MEMORY *temp;
			temp=current;
			previous->size=previous->size+current->size;
			(current->next)->former=previous;
			previous->next=current->next;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			delete temp;
			print(mem);
		}
		else if((current->next)->state==0)//�ͷŵĵ�ַ�ռ�����п��п�������ͺ���Ŀ��п�ϲ�
		{
			MEMORY *temp;
			temp=current->next;
			current->size=current->size+(current->next)->size;
			current->state=0;
			current->next=NULL;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;

			delete temp;
			print(mem);

		}
		else//���������ҵǰ��û�п��п�ʱֱ�Ӱ�����״̬��Ϊû����
		{
			current->state=0;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			print(mem);
		}

	}
	else
	{
		if(previous->state==0&&(current->next)->state==0)
		{
			MEMORY *temp1,*temp2;
			temp1=current;
			temp2=current->next;
			previous->size=previous->size+current->size+(current->next)->size;
			((current->next)->next)->former=previous;
			previous->next=(current->next)->next;

			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			delete temp1;
			delete temp2;
			print(mem);
		}
		else if(previous->state==0)//�ͷŵĵ�ַ�ռ�ǰ���п��п��������ǰ��ĺϲ�
		{
			MEMORY *temp;
			temp=current;
			previous->size=previous->size+current->size;
			(current->next)->former=previous;
			previous->next=current->next;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			delete temp;
			print(mem);
		}
		else if((current->next)->state==0)//�ͷŵĵ�ַ�ռ�����п��п�������ͺ���Ŀ��п�ϲ�
		{
			MEMORY *temp;
			temp=current->next;
			current->size=current->size+(current->next)->size;
			current->state=0;
			((current->next)->next)->former=current;
			current->next=(current->next)->next;

			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;

			delete temp;
			print(mem);

		}
		else//���������ҵǰ��û�п��п�ʱֱ�Ӱ�����״̬��Ϊû����
		{
			current->state=0;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			print(mem);
		}
	}
}

void alloc(MEMORY *ptr,MEMORY *assign)//�ڴ����
{
	if(ptr->next==NULL)//�ڴ�û����ҵ����
	{
		if(ptr->size>=assign->size)//�ڴ�ռ������ҵ����ռ�
		{
			ptr->size=ptr->size-assign->size;//Ϊ�ڴ����ռ�
			assign->state=1;
			ptr->next=assign;
			assign->former=ptr;

			cout<<"��ҵ "<<(assign->num)<<"����"<<(assign->size)<<" "<<"k���ڴ�ռ�"<<endl;
		}
		else
		{
			cout<<"û���㹻���ڴ�ռ�Ϊ��ҵ"<<(assign->num)<<"����"<<endl;
			delete assign;
		}
	}
	else//�ڴ�������Ѿ������˿ռ�
	{
		MEMORY *previous,*current;
		previous=ptr;
		current=previous->next;
		while(current!=NULL)
		{
			if(current->size>assign->size&&ptr->state==0)//�����ǰ�ڴ�ռ������ҵ����ռ䲢���ڴ�û�б�����
			{
				break;
			}
			previous=current;
			current=current->next; 
		}

		if(current==NULL)//��������û��Ϊ��ҵ��������Ŀռ�
		{

			if(ptr->size>=assign->size)//�ڴ��л����㹻û����Ŀռ�Ϊ����ҵ����
			{
				assign->address =640-(ptr->size);//max+size_offset;//��ҵ���ڴ��е��׵�ַ
				ptr->size=ptr->size-assign->size;
				assign->state=1;
				assign->former=previous;
				previous->next=assign;


				cout<<"��ҵ "<<(assign->num)<<"����"<<(assign->size)<<" "<<"k���ڴ�ռ�"<<endl;
			}
			else
			{
				cout<<"û���㹻���ڴ�ռ�Ϊ��ҵ"<<(assign->num)<<"����"<<endl;
			}
		}
		else//���������п�Ϊ����ҵ����Ŀռ�
		{

			if((current->size-assign->size)<=size_min)//���������߱��Ŀռ�����ҵ����ռ��С���ʱ
			{                                         //ֱ�Ӱ��������п�Ŀռ�������ҵ����ӿ��п���
				current->num=assign->num;               //��������ҵ��ͬ�Ŀռ�
				current->state=1;
				delete assign;//free(assign);

				cout<<"��ҵ "<<(current->num)<<"����"<<(current->size)<<" "<<"k���ڴ��"<<endl;   
			}
			else//�ӿ��п��л���һ������ҵ��С��ͬ�Ŀռ�
			{
				current->size=current->size-assign->size;
				assign->state=1;
				assign->address=current->address+current->size;

				if(current->next==NULL)//��Ҫ����Ŀռ��ǿ����������һ��Ԫ��
				{
					assign->former=current;
					current->next=assign;
				}
				else
				{
					assign->next=current->next;
					(current->next)->former=assign;
					assign->former=current;
					current->next=assign;
				}
				cout<<"��ҵ "<<(assign->num)<<"����"<<(assign->size)<<" "<<"k���ڴ�ռ�"<<endl;
			}
		}

	}

	if((ptr->next)->next!=NULL&&is_optimist==true)
		sort(ptr);//�����ɿ��п��С����
	//print(ptr);

}
void sort(MEMORY *ptr)
{
   MEMORY *temp=new MEMORY;
   temp->next=0;
   temp->former=0;
   
   while(ptr->next)
   { 
   if((ptr->next)->next==NULL)//�ڴ�����ֻ������Ԫ��
   {
    MEMORY *p;
    p=ptr->next;
    ptr->next=NULL;
        insert(temp,p);
   } 
   else//�ڴ������ж��Ԫ��
   {
      MEMORY *p;
         p=ptr->next;
      p->former=ptr;
      ptr->next=p->next;
     (p->next)->former=ptr;
   insert(temp,p);
   }

   }
   ptr->next=temp->next;
   (temp->next)->former=ptr;
   delete temp;
}
void insert(MEMORY *queue,MEMORY *item)
{
	MEMORY *previous,*current;
	previous=queue;
	current=previous->next;
	while(current!=NULL && item->size>=current->size)
	{
		previous=current;
		current=current->next; 
	}

	if(previous==queue)//��Ҫ�����Ԫ����С
	{

		if(queue->next==NULL)//�ڴ�����ֻ��һ��Ԫ��
		{
			item->next=0;
			queue->next=item;
			item->former=queue;
		}
		else//�ڴ������ж��Ԫ��
		{
			item->next=queue->next;
			(queue->next)->former=item;
			item->former=queue;
			queue->next=item; 
		}
	}
	else//��λ��Ҫ�����Ԫ��
	{
		item->next=current;
		item->former=previous;
		if(current==NULL)
		{
			previous->next=item;
		}
		else
		{
			current->former=item;
			previous->next=item;
		}

	}
}
void free_optimist(MEMORY *ptr)
{
	MEMORY *previous,*current;
	previous=ptr;
	current=previous->next;
	while(current!=NULL)
	{
		if(current->state==1&&rand()%3==1)
		{
			break;
		}
		previous=current;
		current=current->next;
	}
	if(current==NULL)
	{
		//cout<<"�ڴ���û���κ���ҵ������"<<endl;
		return;
	}
	else if(current->next==NULL)
	{
		if(previous->state==0&&((previous->address+previous->size)==current->address))
		{
			MEMORY *temp;
			temp=current;
			previous->size=previous->size+current->size;
			previous->next=NULL;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			delete temp;
			print(mem);
		}
		else
		{
			current->state=0;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			print(mem);
		}
	}
	else if((current->next)->next==NULL)
	{
		if(previous->state==0&&(current->next)->state==0&&((previous->address+previous->size)==current->address)&&((current->size+current->address)==(current->next)->address))
		{
			MEMORY *temp1,*temp2;
			temp1=current;
			temp2=current->next;
			previous->size=previous->size+current->size+(current->next)->size;
			previous->next=NULL;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			delete temp1;
			delete temp2;
			print(mem);
		}
		else if(previous->state==0&&((previous->address+previous->size)==current->address))//�ͷŵĵ�ַ�ռ�ǰ���п��п��������ǰ��ĺϲ�
		{
			MEMORY *temp;
			temp=current;
			previous->size=previous->size+current->size;
			(current->next)->former=previous;
			previous->next=current->next;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			delete temp;
			print(mem);
		}
		else if((current->next)->state==0&&((current->size+current->address)==(current->next)->address))//�ͷŵĵ�ַ�ռ�����п��п�������ͺ���Ŀ��п�ϲ�
		{
			MEMORY *temp;
			temp=current->next;
			current->size=current->size+(current->next)->size;
			current->state=0;
			current->next=NULL;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;

			delete temp;
			print(mem);
		}
	}
	else
	{
		if(previous->state==0&&(current->next)->state==0&&((previous->address+previous->size)==current->address)&&((current->size+current->address)==(current->next)->address))
		{
			MEMORY *temp1,*temp2;
			temp1=current;
			temp2=current->next;
			previous->size=previous->size+current->size+(current->next)->size;
			((current->next)->next)->former=previous;
			previous->next=(current->next)->next;

			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			delete temp1;
			delete temp2;
			print(mem);
		}
		else if(previous->state==0&&(previous->address+previous->size)==current->address)//�ͷŵĵ�ַ�ռ�ǰ���п��п��������ǰ��ĺϲ�
		{
			MEMORY *temp;
			temp=current;
			previous->size=previous->size+current->size;
			previous->state=0;
			(current->next)->former=previous;
			previous->next=current->next;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			delete temp;
			print(mem);
		}
		else if((current->next)->state==0&&((current->size+current->address)==(current->next)->address))//�ͷŵĵ�ַ�ռ�����п��п�������ͺ���Ŀ��п�ϲ�
		{
			MEMORY *temp;
			temp=current->next;
			current->size=current->size+(current->next)->size;
			current->state=0;
			((current->next)->next)->former=current;
			current->next=(current->next)->next;

			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;

			delete temp;
			print(mem);

		}
		else//���������ҵǰ��û�п��п�ʱֱ�Ӱ�����״̬��Ϊû����
		{
			current->state=0;
			cout<<"��ҵ "<<(current->num)<<"�ͷ� "<<(current->size)<<"k �Ŀռ�"<<endl;
			print(mem);
		}
	}
	if((ptr->next)->next!=NULL)
		sort(ptr);//�����ɿ��п��С����
}
void print(MEMORY *ptr)
{
	MEMORY *temp;
	temp=ptr->next;
	cout<<"\n�ڴ�����״̬Ϊ��"<<endl;
	while(temp!=NULL)
	{
		cout<<"����ĵ�ַΪ��"<<temp->address<<"   ����Ŀռ䣺"<<temp->size<<"k"
			<<"   ���е���ҵ��:"<<temp->num;
		if(temp->state==0)
		{
			cout<<"     �ڴ����";
		}
		else
		{
			cout<<"    �ڴ��ѷ���";
		}
		cout<<endl;
		temp=temp->next;
	}
} 

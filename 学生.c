#include<stdio.h>
#include<stdlib.h>
#define N 100
void init();
char welcome();
void InputInfo();
void view();
void xiugai();
void DeleteInfo();
void paiming1(struct student_info student[]);
void paiming2(struct student_info student[]);
void ViewAll();
void clean();
void PaimingView();
void exits();
struct student_info input();
void SortInfo(struct student_info student[]);
void ViewInfo(struct student_info *sp);
void SaveStruct(struct student_info *sp,int size,int n,char filename[20]);
void LoadStruct(struct student_info *sp,int size,int n,char filename[20]);
void SaveInt(int *p,int size,int n,char filename[20]);
void LoadInt(int *p,int size,int n,char filename[20]);
int NumExist(struct student_info student[],int num);
struct student_info 
{
	int num;			//ѧ��
	char name[6];		//����
	char sex[5];		//�Ա�
	char adress[20];	//��ͥסַ
	int tel[10];		//�绰
	int chinese,math,english,huping,pingde,jiaoping,paiming1,paiming2;	
	    //����  ��ѧ  Ӣ��    ����   Ʒ��    ����    
	double ave,zhongping;
};

	struct student_info student[N];
	int counter,PM;
   void main()
  {
	char select;
	init();        //���ó�ʼ������
	while(1)
	{ 
        select=welcome();
		switch(select)
		{
			case '1':	system("cls");	InputInfo(); break;     	 //ѡ��1:����ѧ����Ϣ
			case '2':	system("cls");    view(); break;         	//ѡ��2:���ѧ����Ϣ
			case '3':	system("cls");	xiugai(); break;       	 //ѡ��3:�޸�ѧ����Ϣ
			case '4':	system("cls");	DeleteInfo(); break;   	 //ѡ��4:ɾ��ѧ����Ϣ
			case '5':	system("cls");    paiming1(student);paiming2(student);PM=1;getchar();
getchar();	system("cls"); break; 		//ѡ��5:ѧ����Ϣ����
			case '6':   system("cls");  ViewAll();break;      	 //ѡ��6:���ȫ��ѧ����Ϣ
			case '7':   system("cls");  clean();break;			//ѡ��7:���������Ϣ
			case '8':   system("cls");  PaimingView();break;		//ѡ��8:��ѯ����
			case '0':	system("cls");	 exits(); break;        	 //ѡ��9:�˳�	
		}
	}
}
void init()
{
	FILE *fp;
	fp=fopen("counter.dat","rb");			//�򿪼�������counter�ļ�
	if(fp!=NULL)							//����counter
	{
		fclose(fp);
		LoadInt(&counter,sizeof(counter),1,"counter.dat");
	}
	else
	{
		fp=fopen("counter.dat","wb");		//��û��counter�ļ����򴴽�һ����counter��ʼΪ0��
		fclose(fp);
		counter=0;
	}
	if(counter!=0)						    //����ѧ������
		LoadStruct(student,sizeof(struct student_info),counter,"student_info.dat");
}
char welcome()
{
	char select;
	while(1)
	{
		system("cls");
		printf("\t\t��ӭʹ��ѧ����Ϣ����ϵͳ                 \n");
		printf("\n");
		printf("1.¼��ѧ����Ϣ                                        \n\n");
		printf("2.���ѧ����Ϣ                                        \n\n");
		printf("3.�޸�ѧ����Ϣ                                        \n\n");
		printf("4.ɾ��ѧ����Ϣ                                        \n\n");
		printf("5.����ѧ���ɼ�                                        \n\n");
		printf("6.�������ѧ����Ϣ                                    \n\n");
		printf("7.�����������                                        \n\n");
		printf("8.��ѯ����                                            \n\n");
		printf("0.�˳�                                                \n\n");
		printf("������Ӧ�Ĺ������:");
		select=getchar();
		if(select=='1'||select=='2'||select=='3'||select=='4'||select=='5'||select=='6'||select=='7'||select=='8'||select=='0')
			return select;
		system("cls");
		continue;
	}
}
void InputInfo()
{
	int i,n;
	printf("��Ҫ¼�����λѧ������Ϣ:");
	scanf("%d",&n);
	system("cls");
	for(i=1;i<=n;i++)
	{
		student[counter]=input();
		counter++;
	}
	PM=0;
	SortInfo(student);
	SaveStruct(student,sizeof(struct student_info),counter,"student_info.dat");
	SaveInt(&counter,sizeof(counter),1,"counter.dat");
}
void view()
{
	int i,num;
		printf("��������Ҫ������ѧ����Ϣ��ѧ��:");
		scanf("%d",&num);
		getchar();
		if((i=NumExist(student,num))==-1)
		{
			printf("�����ڸ�ѧ��,���س�������...");
			getchar();
			system("cls");
			return;
		}
		ViewInfo(&student[i]);
		printf("\n���س�������...");
		getchar();
		system("cls");
		return;
}
void xiugai()
{
	int i,num;
	char YN,select;
	printf("��������Ҫ�޸ĵ�ѧ����Ϣ��ѧ��:");
	scanf("%d",&num);
	getchar();
	if((i=NumExist(student,num))==-1)
	{
		printf("�����ڸ�ѧ��,���س�������...");
		getchar();
		system("cls");
		return;
	}
	ViewInfo(&student[i]);
	printf("�Ƿ�Ҫ�޸ģ�(Y/N):");
	scanf("%c",&YN);
	getchar();
	if(YN !='Y'&& YN !='y')
	{
		printf("�޸�ȡ��.");
		getchar();
		system("cls");
		return;
	}
		system("cls");
		printf("1.ѧ��                 \n");
		printf("2.�Ա�                 \n");
		printf("3.��ͥסַ             \n");
		printf("4.��ϵ�绰             \n");
		printf("5.���ĳɼ�             \n");
		printf("6.��ѧ�ɼ�             \n");
		printf("7.����ɼ�             \n");
		printf("8.ͬѧ������           \n");
		printf("9.Ʒ�³ɼ�             \n");
		printf("0.�ον�ʦ��ʦ����     \n");
		scanf("%c",&select);
	switch(select)
	{
		case '1':printf("�޸�ѧ��:");scanf("%d",&student[i].num);break;
		case '2':printf("�޸��Ա�:");scanf("%s",&student[i].sex);break;
		case '3':printf("�޸ļ�ͥסַ:");scanf("%s",&student[i].adress);break;
		case '4':printf("�޸���ϵ�绰:");scanf("%s",&student[i].tel);break;
		case '5':printf("�޸����ĳɼ�:");scanf("%d",&student[i].chinese);break;
		case '6':printf("�޸���ѧ�ɼ�:");scanf("%d",&student[i].math);break;
		case '7':printf("�޸�����ɼ�:");scanf("%d",&student[i].english);break;
		case '8':printf("�޸�ͬѧ������:");scanf("%d",&student[i].huping);break;
		case '9':printf("�޸�Ʒ�³ɼ�:");scanf("%d",&student[i].pingde);break;
		case '0':printf("�޸��ον�ʦ����:");scanf("%d",&student[i].jiaoping);break;
	}
	SortInfo(student);
	SaveStruct(student,sizeof(struct student_info),counter,"student_info.dat");
PM=0;
	getchar();
	printf("�޸����...");
	getchar();
	system("cls");
}
void DeleteInfo()
{
	
	int i,j,num;
	char YN;
	printf("������Ҫɾ����ѧ����Ϣѧ��:");
	scanf("%d",&num);
	getchar();
	if((i=NumExist(student,num))==-1)
	{
		printf("û�и�ѧ��,���س�������...");
		getchar();
		system("cls");
		return;
	}
	
	ViewInfo(&student[i]);
	printf("\nȷ��ɾ��(Y/N):");
	scanf("%c",&YN);
	getchar();
	if(YN!='Y' && YN!='y')
	{
		printf("ɾ��ȡ��...");

	}
	else
	{
		for(j=i;j<counter-1;j++)
			student[j]=student[j+1];
		counter--;
		PM=0;
		SaveStruct(student,sizeof(struct student_info),counter,"student_info.dat");
		SaveInt(&counter,sizeof(counter),counter,"counter.dat");
		printf("ɾ�����...");
	}
	
	getchar();
	system("cls");
}
void paiming1(struct student_info student[])
{
	struct student_info *p[N],*temp;
	int i,j;
	for(i=0;i<counter;i++)
		p[i]=&student[i];
	for(i=0;i<counter-1;i++)
		for(j=i+1;j<counter;j++)
	{	
		if(p[i]->ave < p[j]->ave)
		{
			temp=p[i];
			p[i]=p[j];
			p[j]=temp;
		}
	}
	for(i=0;i<counter;i++)
		p[i]->paiming1=i+1;
	printf("ƽ�����������...\n");
	
}
void paiming2(struct student_info student[])
{
	struct student_info *p[N],*temp;
	int i,j;
	for(i=0;i<counter;i++)
		p[i]=&student[i];
	for(i=0;i<counter-1;i++)
		for(j=i+1;j<counter;j++)
	{	
		if(p[i]->zhongping < p[j]->zhongping)
		{
			temp=p[i];
			p[i]=p[j];
			p[j]=temp;
		}
	}
	for(i=0;i<counter;i++)
		p[i]->paiming2=i+1;
	printf("�ۺϲ������������...\n");
}
void ViewAll()
{
	int i;
	for(i=0;i<counter;i++)
	{
		ViewInfo(&student[i]);
		printf("\n");
	}
	getchar();
	printf("�س�������...");
	getchar();
	system("cls");
}
void clean()
{
	counter=0;						 
	SaveInt(&counter,sizeof(counter),1,"counter.dat");
	printf("������...");
	getchar();
	getchar();
	system("cls");
}void PaimingView()
{
	int i,num;
	printf("����Ҫ��ѯ��ѧ��:");
	scanf("%d",&num);
	getchar();
	i=NumExist(student,num);
	if(i==-1)
	{
		printf("��ѧ�Ų�����...");
		getchar();
		return;
	}
	if(PM==0)
	{
		printf("���Ƚ��гɼ�����...");
		getchar();
		return;
	}
	printf("%s��ƽ��������%d\n",student[i].name,student[i].paiming1);
	printf("%s���ۺϲ���������%d\n",student[i].name,student[i].paiming2);
	printf("���س�������...");
	getchar();
	return;
}
void exits()
{
	
	printf("ллʹ��!\n");
}

struct student_info input()
{
	struct student_info stu,*sp;
	char YN;
	sp=&stu;
	while(1)
	{
		while(1)
		{
			printf("¼��ѧ��:");
			scanf("%d",&sp->num);
			getchar();
			if(NumExist(student,sp->num)!=-1)
			{
				printf("��ѧ���Ѵ���,����������...");
				getchar();
				system("cls");
				continue;
			}
			break;
		}
		printf("¼������:");
		gets(sp->name);
		printf("¼���Ա�:");
		gets(sp->sex);
		printf("¼���ͥסַ:");
		gets(sp->adress);
		printf("¼����ϵ�绰:");
		gets(sp->tel);
		printf("\n������¼��ɼ�\n");
		printf("����:");
		scanf("%d",&sp->chinese);
		printf("��ѧ:");
		scanf("%d",&sp->math);
		printf("Ӣ��:");
		scanf("%d",&sp->english);
		sp->ave=(sp->chinese+sp->math+sp->english)/3.0;
		printf("ͬѧ����:");
		scanf("%d",&sp->huping);
		printf("Ʒ�·���:");
		scanf("%d",&sp->pingde);
		printf("��ʦ����:");
		scanf("%d",&sp->jiaoping);
		getchar();
		sp->zhongping=(sp->ave*0.6+sp->huping*0.1+sp->pingde*0.1+sp->jiaoping*0.2);
		printf("¼����ϣ�ȷ����Ϣ�Ƿ���ȷ(Y/N)");
		YN=getchar();
		getchar();
		if(YN=='Y'|| YN=='y')
			break;
		else
		{
			printf("���س�������¼����Ϣ��");
			getchar();
			system("cls");
			continue;
		}
	}
	system("cls");
	return stu;
}
void SortInfo(struct student_info student[])
{
	int i,j;
	struct student_info temp;
	for(i=0;i<counter-1;i++)
		for(j=i+1;j<=counter-1;j++)
		{
			if(student[i].num<student[j].num)
			{
				temp=student[i];
				student[i]=student[j];
				student[j]=temp;
			}
		}
}
void ViewInfo(struct student_info *sp)
{
	printf("ѧ��\t����\t�Ա�\t��ͥסַ\t��ϵ�绰\n");
	printf("%d\t%s\t%s\t%s\t\t%s\n",sp->num,sp->name,sp->sex,sp->adress,sp->tel);
	printf("����\t��ѧ\tӢ��\t����\tƷ��\t����\n");
	printf("%d\t%d\t%d\t%d\t%d\t%d\t\n",sp->chinese,sp->math,sp->english,sp->huping,sp->pingde,sp->jiaoping);
	printf("ƽ����\t�ۺϷ�\n");
	printf("%.2f\t%.2f\n",sp->ave,sp->zhongping);
	if(PM==1)
	{
		printf("ƽ��������\t�ۺϲ���������\n");
		printf("%d\t\t%d\n",sp->paiming1,sp->paiming2);
	}
}
void SaveStruct(struct student_info *sp,int size,int n,char filename[20])
{
	FILE *fp;
	fp=fopen(filename,"wb");
	fwrite(sp,size,n,fp);
	fclose(fp);
}
void LoadStruct(struct student_info *sp,int size,int n,char filename[20])
{
	FILE *fp;
	fp=fopen(filename,"rb");
	fread(sp,size,n,fp);
	fclose(fp);


}
void SaveInt(int *p,int size,int n,char filename[20])
{
	FILE *fp;
	fp=fopen(filename,"wb");
	fwrite(p,size,n,fp);
	fclose(fp);
}
void LoadInt(int *p,int size,int n,char filename[20])
{
	FILE *fp;
	fp=fopen(filename,"rb");
	fread(p,size,n,fp);
	fclose(fp);
}
int NumExist(struct student_info student[],int num)
{
	int i;
	for(i=0;i<counter;i++)
	{if(student[i].num==num)
			return i;
	}
	return -1;
}
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
	int num;			//学号
	char name[6];		//姓名
	char sex[5];		//性别
	char adress[20];	//家庭住址
	int tel[10];		//电话
	int chinese,math,english,huping,pingde,jiaoping,paiming1,paiming2;	
	    //语文  数学  英语    互评   品德    教评    
	double ave,zhongping;
};

	struct student_info student[N];
	int counter,PM;
   void main()
  {
	char select;
	init();        //调用初始化函数
	while(1)
	{ 
        select=welcome();
		switch(select)
		{
			case '1':	system("cls");	InputInfo(); break;     	 //选项1:输入学生信息
			case '2':	system("cls");    view(); break;         	//选项2:浏览学生信息
			case '3':	system("cls");	xiugai(); break;       	 //选项3:修改学生信息
			case '4':	system("cls");	DeleteInfo(); break;   	 //选项4:删除学生信息
			case '5':	system("cls");    paiming1(student);paiming2(student);PM=1;getchar();
getchar();	system("cls"); break; 		//选项5:学生信息排名
			case '6':   system("cls");  ViewAll();break;      	 //选项6:浏览全部学生信息
			case '7':   system("cls");  clean();break;			//选项7:清除所有信息
			case '8':   system("cls");  PaimingView();break;		//选项8:查询排名
			case '0':	system("cls");	 exits(); break;        	 //选项9:退出	
		}
	}
}
void init()
{
	FILE *fp;
	fp=fopen("counter.dat","rb");			//打开计数变量counter文件
	if(fp!=NULL)							//载入counter
	{
		fclose(fp);
		LoadInt(&counter,sizeof(counter),1,"counter.dat");
	}
	else
	{
		fp=fopen("counter.dat","wb");		//若没有counter文件，则创建一个，counter初始为0。
		fclose(fp);
		counter=0;
	}
	if(counter!=0)						    //载入学生数据
		LoadStruct(student,sizeof(struct student_info),counter,"student_info.dat");
}
char welcome()
{
	char select;
	while(1)
	{
		system("cls");
		printf("\t\t欢迎使用学生信息管理系统                 \n");
		printf("\n");
		printf("1.录入学生信息                                        \n\n");
		printf("2.浏览学生信息                                        \n\n");
		printf("3.修改学生信息                                        \n\n");
		printf("4.删除学生信息                                        \n\n");
		printf("5.排名学生成绩                                        \n\n");
		printf("6.浏览所有学生信息                                    \n\n");
		printf("7.清除所有数据                                        \n\n");
		printf("8.查询排名                                            \n\n");
		printf("0.退出                                                \n\n");
		printf("输入相应的功能序号:");
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
	printf("需要录入多少位学生的信息:");
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
		printf("请输入需要游览的学生信息的学号:");
		scanf("%d",&num);
		getchar();
		if((i=NumExist(student,num))==-1)
		{
			printf("不存在该学号,按回车键返回...");
			getchar();
			system("cls");
			return;
		}
		ViewInfo(&student[i]);
		printf("\n按回车键返回...");
		getchar();
		system("cls");
		return;
}
void xiugai()
{
	int i,num;
	char YN,select;
	printf("请输入需要修改的学生信息的学号:");
	scanf("%d",&num);
	getchar();
	if((i=NumExist(student,num))==-1)
	{
		printf("不存在该学号,按回车键返回...");
		getchar();
		system("cls");
		return;
	}
	ViewInfo(&student[i]);
	printf("是否要修改？(Y/N):");
	scanf("%c",&YN);
	getchar();
	if(YN !='Y'&& YN !='y')
	{
		printf("修改取消.");
		getchar();
		system("cls");
		return;
	}
		system("cls");
		printf("1.学号                 \n");
		printf("2.性别                 \n");
		printf("3.家庭住址             \n");
		printf("4.联系电话             \n");
		printf("5.语文成绩             \n");
		printf("6.数学成绩             \n");
		printf("7.外语成绩             \n");
		printf("8.同学互评分           \n");
		printf("9.品德成绩             \n");
		printf("0.任课教师教师评分     \n");
		scanf("%c",&select);
	switch(select)
	{
		case '1':printf("修改学号:");scanf("%d",&student[i].num);break;
		case '2':printf("修改性别:");scanf("%s",&student[i].sex);break;
		case '3':printf("修改家庭住址:");scanf("%s",&student[i].adress);break;
		case '4':printf("修改联系电话:");scanf("%s",&student[i].tel);break;
		case '5':printf("修改语文成绩:");scanf("%d",&student[i].chinese);break;
		case '6':printf("修改数学成绩:");scanf("%d",&student[i].math);break;
		case '7':printf("修改外语成绩:");scanf("%d",&student[i].english);break;
		case '8':printf("修改同学互评分:");scanf("%d",&student[i].huping);break;
		case '9':printf("修改品德成绩:");scanf("%d",&student[i].pingde);break;
		case '0':printf("修改任课教师评分:");scanf("%d",&student[i].jiaoping);break;
	}
	SortInfo(student);
	SaveStruct(student,sizeof(struct student_info),counter,"student_info.dat");
PM=0;
	getchar();
	printf("修改完成...");
	getchar();
	system("cls");
}
void DeleteInfo()
{
	
	int i,j,num;
	char YN;
	printf("请输入要删除的学生信息学号:");
	scanf("%d",&num);
	getchar();
	if((i=NumExist(student,num))==-1)
	{
		printf("没有该学号,按回车键返回...");
		getchar();
		system("cls");
		return;
	}
	
	ViewInfo(&student[i]);
	printf("\n确认删除(Y/N):");
	scanf("%c",&YN);
	getchar();
	if(YN!='Y' && YN!='y')
	{
		printf("删除取消...");

	}
	else
	{
		for(j=i;j<counter-1;j++)
			student[j]=student[j+1];
		counter--;
		PM=0;
		SaveStruct(student,sizeof(struct student_info),counter,"student_info.dat");
		SaveInt(&counter,sizeof(counter),counter,"counter.dat");
		printf("删除完成...");
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
	printf("平均分排名完成...\n");
	
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
	printf("综合测评分排名完成...\n");
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
	printf("回车键返回...");
	getchar();
	system("cls");
}
void clean()
{
	counter=0;						 
	SaveInt(&counter,sizeof(counter),1,"counter.dat");
	printf("清除完毕...");
	getchar();
	getchar();
	system("cls");
}void PaimingView()
{
	int i,num;
	printf("输入要查询的学号:");
	scanf("%d",&num);
	getchar();
	i=NumExist(student,num);
	if(i==-1)
	{
		printf("该学号不存在...");
		getchar();
		return;
	}
	if(PM==0)
	{
		printf("请先进行成绩排名...");
		getchar();
		return;
	}
	printf("%s的平均分排名%d\n",student[i].name,student[i].paiming1);
	printf("%s的综合测评分排名%d\n",student[i].name,student[i].paiming2);
	printf("按回车键返回...");
	getchar();
	return;
}
void exits()
{
	
	printf("谢谢使用!\n");
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
			printf("录入学号:");
			scanf("%d",&sp->num);
			getchar();
			if(NumExist(student,sp->num)!=-1)
			{
				printf("该学号已存在,请重新输入...");
				getchar();
				system("cls");
				continue;
			}
			break;
		}
		printf("录入姓名:");
		gets(sp->name);
		printf("录入性别:");
		gets(sp->sex);
		printf("录入家庭住址:");
		gets(sp->adress);
		printf("录入联系电话:");
		gets(sp->tel);
		printf("\n接下来录入成绩\n");
		printf("语文:");
		scanf("%d",&sp->chinese);
		printf("数学:");
		scanf("%d",&sp->math);
		printf("英语:");
		scanf("%d",&sp->english);
		sp->ave=(sp->chinese+sp->math+sp->english)/3.0;
		printf("同学互评:");
		scanf("%d",&sp->huping);
		printf("品德分数:");
		scanf("%d",&sp->pingde);
		printf("教师评价:");
		scanf("%d",&sp->jiaoping);
		getchar();
		sp->zhongping=(sp->ave*0.6+sp->huping*0.1+sp->pingde*0.1+sp->jiaoping*0.2);
		printf("录入完毕，确认信息是否正确(Y/N)");
		YN=getchar();
		getchar();
		if(YN=='Y'|| YN=='y')
			break;
		else
		{
			printf("按回车键重新录入信息。");
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
	printf("学号\t姓名\t性别\t家庭住址\t联系电话\n");
	printf("%d\t%s\t%s\t%s\t\t%s\n",sp->num,sp->name,sp->sex,sp->adress,sp->tel);
	printf("语文\t数学\t英语\t互评\t品德\t教评\n");
	printf("%d\t%d\t%d\t%d\t%d\t%d\t\n",sp->chinese,sp->math,sp->english,sp->huping,sp->pingde,sp->jiaoping);
	printf("平均分\t综合分\n");
	printf("%.2f\t%.2f\n",sp->ave,sp->zhongping);
	if(PM==1)
	{
		printf("平均分排名\t综合测评分排名\n");
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
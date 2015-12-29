#include <stdio.h>
#include <stdlib.h>
#include <windows.h>      //清屏函数头文件
#include <string.h>

struct Stuff
{
 char number[10];      //员工编号
 char name[10];        //员工姓名
 char sex[8];          //员工性别
 char borth[10];       //员工生日
 char degree[20];      //员工学历
 char business[20];    //员工职务
 char phone[15];       //员工电话
 char place[50];       //员工住址
 char con[50];         //判断关键字专用
 struct Stuff *next;  
};

char Menu(void);                                    //菜单显示
struct Stuff *App(struct Stuff *head);              //添加
void Sort(struct Stuff *head);                      //排序
struct Stuff *Ser(struct Stuff *head);              //查找
void Chn(struct Stuff *head,char n[10]);            //更改
void Scpy(char *p,char *q);                         //排序中用于交换员工信息
struct Stuff *Del(struct Stuff *head,char n[10]);   //删除
int Sel(char ch,struct Stuff *p,struct Stuff *q);   //判断排序及关键字专用函数
void Prf(struct Stuff *head);                       //输出
void Fre(struct Stuff *head);                       //释放
int i=1;    //定义全局变量，实现实时员工人数统计

int main(void)
{
 char n[10];
 struct Stuff *head=NULL;    //链表头指针定义
 while(1)
 {
  switch(Menu())
  {
  case '1':
   printf("请输入员工信息，直接输入'#'结束\n");
   head=App(head);
   break;
  case '2':
   Sort(head);
   break;
  case '3':
   head=Ser(head);
   break;
  case '4':
   printf("员工信息如下:\n");
   Prf(head);
   break;
  case '5':
   printf("请输入员工编号:");
   scanf("%s",n);
   Chn(head,n);
   break;
  case '6':
   printf("请输入员工编号:");
   scanf("%s",n);
   head=Del(head,n);
   break;
  case '0':
   printf("欢迎下次光临，88!\n");
   exit(0);
  default:
   printf("输入错误，请重新输入!\n");
  }
  fflush(stdin);          //清楚缓冲区
  printf("按任意键继续~");
  getchar();
  system("cls");          //清屏效果
 }
 Fre(head);

 return 0;
}

//菜单函数
char Menu(void)
{
 char ch;
 printf("------------请选择-----------\n");
 printf("1.添加员工信息\n2.员工信息排序\n3.查找员工信息\n4.输出员工信息\n5.更改员工信息\n6.删除员工信息\n0.退出\n-----------------------------\n");
 scanf(" %c",&ch);
 return ch;
}

//添加成员函数
//输入参数:链表头指针
//返回参数:链表头指针
struct Stuff *App(struct Stuff *head)
{
 struct Stuff *p=NULL,*q=head;
 while(i)
 {
  p=(struct Stuff *)malloc(sizeof(struct Stuff));  //申请结构体空间
  if(p==NULL)
  {
   printf("内存不够!\n");
   exit(0);
  }
  p->next =NULL;        //指针域为空
  printf("请输入第%d名员工:\n",i);
  printf(" 编号 | 姓名 | 性别 | 出生年月 | 学历 | 职务 | 电话 | 住址 :\n");
  fflush(stdin);
  scanf("%s",p->number );
  if(!strcmp(p->number ,"#"))
  {
   free(p);          //释放不需要的结构体内存
   break;
  }
  else
  {
   ++i;
   scanf("%s%s%s%s%s%s%s",p->name ,p->sex ,p->borth ,p->degree ,p->business ,p->phone ,p->place );
   p->con[0]='\0';   //防止后面判断出现随机值
   if(head==NULL)
    head=p;
   else
   {
    while(q->next !=NULL)  //防止结束后再次输入时出现问题
     q=q->next ;
    q->next =p;
   }
   q=p;             //每次都加在链表尾
  }
 }
 return head;
}

//排序函数
//输入参数:头指针
void Sort(struct Stuff *head)
{  
 char ch;
 struct Stuff *p,*q,*r;
 while(1)
 {
  printf("请选择排序条件:1.编号2.姓名3.性别4.出生年月5.学历6.职务7.电话8.地址0.退出\n");
  scanf(" %c",&ch);
  if(ch=='0')
   break;
  if(ch<'1'||ch>'8')
  {
   printf("输入错误，请重新输入!\n");
   continue;
  }
  p=head;
  while(p->next!=NULL)                      //选择排序
  {
   q=p->next;
   r=p;
   while(q!=NULL)
   {
    if(Sel(ch,r,q))                   //调用判断函数
     r=q;
    q=q->next;
   }
   if(r!=p)                              //交换内容
   {
    Scpy(r->number,p->number);
    Scpy(r->name,p->name);
    Scpy(r->sex,p->sex);
    Scpy(r->borth,p->borth);
    Scpy(r->degree,p->degree);
    Scpy(r->business,p->business);
    Scpy(r->phone,p->phone);
    Scpy(r->place,p->place);
   }
   p=p->next;
  }
  Prf(head);       //输出
 }
}

//交换函数
void Scpy(char *p,char *q)
{
 char c[50];
 strcpy(c,p);
 strcpy(p,q);
 strcpy(q,c);
}

//判断函数
//输出参数:1为真，0为假
int Sel(char ch,struct Stuff *p,struct Stuff *q)
{
 switch(ch)         //实现各个关键字查找
 {
 case '1':
  return strcmp(q->number ,p->number )<0||strcmp(q->con ,p->number )==0 ; //排序条件及查找条件
 case '2':
  return strcmp(q->name ,p->name )<0||strcmp(q->con ,p->name  )==0 ;
 case '3':
  return strcmp(q->sex ,p->sex )<0||strcmp(q->con ,p->sex )==0 ;
 case '4':
  return strcmp(q->borth ,p->borth)<0 ||strcmp(q->con ,p->borth  )==0 ;
 case '5':
  return strcmp(q->degree ,p->degree )<0||strcmp(q->con ,p->degree )==0 ;
 case '6':
  return strcmp(q->business ,p->business )<0||strcmp(q->con ,p->business)==0 ;
 case '7':
  return strcmp(q->phone ,p->phone )<0 ||strcmp(q->con ,p->phone)==0;
 case '8':
  return strcmp(q->place ,p->place )<0||strcmp(q->con ,p->place )==0;
 default :
  exit(0);
 }
}
 
//查找函数
struct Stuff *Ser(struct Stuff *head)
{
 struct Stuff *p=NULL,*q,a={"\0","\0","\0","\0","\0","\0","\0","\0"}; //防止判断时错误
 int flag;   //查找判断
 char ch,sh;
 q=&a;
 while(1)
 {
  printf("请输入要查找的条件:1.编号2.姓名3.性别4.出生年月5.学历6.职务7.电话8.住址0.退出\n");
  scanf(" %c",&ch);
  if(ch=='0')
   break;
  if(ch<'1'||ch>'8')
  {
   printf("输入错误，请重新输入!\n");
   continue;
  }
  fflush(stdin);
  printf("请输入:");
  gets(q->con );
  p=head;        //指向表头
  flag=0;
  while(p!=NULL)
  {
   if(Sel(ch,p,q))
   {
    printf("员工信息如下:\n");
    printf(" 编号 | 姓名 | 性别 | 出生年月 | 学历 | 职务 | 电话 | 住址 \n%s  %s  %s  %s  %s  %s  %s  %s\n"
     ,p->number ,p->name ,p->sex ,p->borth ,p->degree ,p->business ,p->phone ,p->place );
    printf("是否需要:1.更改 2.删除 3.继续\n");
    scanf(" %c",&sh);
    if(sh=='1')
     Chn(head,p->number);         //调用更改函数
    else if(sh=='2')
     head=Del(head,p->number);    //调用删除函数，得到的head必须return
    flag=1;
    break;
   }
   p=p->next ;
  }
  if(flag==0)
   printf("没有找到该员工信息!\n");
 }
 return head;
}

//更改函数
//输入参数:n[10] 为员工编号
void Chn(struct Stuff *head,char n[10])
{
 struct Stuff *p=head;
 int flag=0;
 if(head==NULL)
  printf("未找到员工信息!\n");
 else
 {
  while(p!=NULL)
  {
   if(!strcmp(p->number,n))
   {
    printf("请输入新的信息:\n编号|姓名|性别|出生年月|学历|职务|电话|住址\n");
    scanf("%s%s%s%s%s%s%s%s",p->number ,p->name ,p->sex ,p->borth ,p->degree ,p->business ,p->phone ,p->place );
    printf("员工信息如下:\n");
    flag++;
    break;
   }
   p=p->next;
  }
  if(flag==0)
   printf("未找到该员工信息!\n");
 }
 Prf(head);
}

//删除函数
//输入参数:n为员工编号
//输出参数:头指针
struct Stuff *Del(struct Stuff *head,char n[10])
{
 
 struct Stuff *p,*pr;
 int flag;
 flag=0;
 p=head,pr=head;
 if(head==NULL)
  printf("未找到员工信息!\n");
 else
 {
  while(strcmp(p->number ,n)&&p->next !=NULL)
  {
   pr=p;
   p=p->next ;
  }
  if(!strcmp(p->number ,n))
  {
   if(p==head)
    head=p->next ;
   else
    pr->next=p->next ;
   free(p);
   printf("删除成功!\n");
   i--;
  }
  else
   printf("未找到员工信息!\n");
 }
 Prf(head); 
 return head;
}

//输出函数
void Prf(struct Stuff *head)
{
 struct Stuff *p=head;
 int i=1;
 while(p!=NULL)
 {
  printf("%d. %s  %s  %s  %s  %s  %s  %s  %s\n"
   ,i++,p->number ,p->name ,p->sex ,p->borth ,p->degree ,p->business ,p->phone ,p->place);
  p=p->next ;
 }
}

//释放函数
void Fre(struct Stuff *head)
{
 struct Stuff *p;
 while(head!=NULL)
 {
  p=head;
  head=head->next ;
  free(p);
 }
}

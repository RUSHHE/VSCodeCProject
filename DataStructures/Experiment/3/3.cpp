//2-2-3.cpp 对口援疆城市的判断问题
#include<stdio.h>
#include<string.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define NULL 0
#define Over -2
#define Infe -1
typedef struct {
	char provincer[20];       //省市
	char assistance[50];      //援助地区
}Friends;                     //对口数据                
Friends group[100];           //存放映射关系的结构体数组
int ind=0;                  //记录当前gruop数组长度
typedef char SElemType[50];   
typedef int Status;
typedef struct SNode{
 SElemType data;
 struct SNode *next;
}SNode,*LinkStack;

Status Push(LinkStack &S,SElemType e)
//入栈 
{
 LinkStack p =(LinkStack)malloc(sizeof(SNode));
 if(!p) return ERROR;
 strcpy(p->data,e);
 p->next=S;
 S=p;
 return OK; 
}

Status Pop(LinkStack &S,SElemType &e)
//出栈 
{
 if(S==NULL)
  return ERROR;
 LinkStack p=S;
 strcpy(e,p->data);
 S=p->next;
 free(p);
 return OK;
}

Status GetTop(LinkStack S,SElemType &e)
//取当前栈顶元素的值
{
  if(S==NULL)
    return ERROR;
  strcpy(e,S->data);
  return OK;
}

Status EmptyStack(LinkStack S)
//判空
{
  if(S==NULL) return TRUE;
  else return FALSE; 
 
}

Status ReadFile()
//从文件中读取数据给全局变量结构体数组group赋值
{
    FILE *fp;                  
	fp = fopen("/Users/rushhe/VSCodeCProject/DataStructures/Experiment/3/2_2_5_inputdata.txt", "r");
	int i=0;
	while(!feof(fp))
	{
		fscanf(fp,"%s %s",group[i].provincer,group[i].assistance); //给group各成员赋值
        i++;
		if(getc(fp)==EOF)
			break;
	}
	ind=i;
    fclose(fp);
	return OK;
}

Status SearchInGroup(SElemType e,char a[])  
//在group数组中查找当前e对应的省市名称，用数组a返回
{	
	for(int i=0;i<=ind;i++)          //查找
		if(strcmp(group[i].assistance,e)==0)    //如果当前数组中援助地区的名称与e相同   
		{
			strcpy(a,group[i].provincer);       //将其对应的省市名称返回
			break;
		}
		return OK;
}

Status Handle_str1(char s[])         
//根据当前输入的字符串s进行比对
{
  char t1[20],t2[20],z[20],str[20];
  SElemType e1,e2,e;
  int i=0,j=0,t=1;
  LinkStack top=NULL;
  for(i=0;s[i]!='#';i++)                              //从左自右读取字符
  if(s[i]!=' ')                                      //某一个省市名称的中间
  {  t1[j]=s[i];                                     //赋值给临时数组t1
     j=j+1; 
  }
  else if(s[i]==' ')                                 //某一个省市名称读取结束
  {  t1[j]='\0';                                     //t1数组尾部添加'\0'
     strcpy(e1,t1);               
     Push(top,e1);                                   //入栈
     j=0;                                            //j重新赋值为0，准备读入下一个名称
  } 
  if(s[i]=='#')                                     //最后一个省市名称读取结束
  { if(i!=0)                                        //当省市名称无缺省
	  { t1[j]='\0';  
	    strcpy(e1,t1);       
	    Push(top,e1);
	    j=0;	  
	  }                              
  }
  for(i++;i<=strlen(s);i++)                          //读取对口援助地区名称
  { if(s[i]!=' '&&s[i]!='\0')                        //某一个对口援助地区名称的中间   
	   { t2[j]=s[i];
         j=j+1;
	   }
	 else                                           //某一个对口援助地区名称读取结束
	 { if(j!=0)
           { t2[j]='\0';	                 
             strcpy(e2,t2);
	         if(EmptyStack(top))                    //若当前栈空
			 {  printf("对接不成功\n");
		        printf("%s缺少对口省市\n",e2);
		        t=0;
		        break;
			 }
	        GetTop(top,e);                         //取当前栈顶元素的值
            SearchInGroup(e2,str);                 //查找其对口省市的名称，赋值给str
	        if(strcmp(str,e)!=0)                   //若当前栈顶元素的值与其对口省市名称不同
			{   printf("对接不成功\n");
	            printf("%s不是%s的对口地区，%s的对接省市应为%s\n",e2,e,e2,str);
		        t=0;                              //t为0表示有匹配不成功的情况，1表示匹配成功，其初始值为1       
			}
            Pop(top,e);                          //出栈
	        j=0;
	   }
	   else
	   { GetTop(top,e);
         printf("对接不成功\n");
	     printf("%s缺少对口援助地区\n",e);
         Pop(top,e);
		 t=0;
	   }
	 }
	}
   if(EmptyStack(top)&&t)                                    //t为1且栈空
      printf("全部对接成功\n");
   else if(!EmptyStack(top))                                //栈不空（省市有多余）
	 { GetTop(top,e);
       printf("对接不成功\n");
	   printf("%s缺少对口援助地区\n",e);
	 }
  return OK; 
}





Status Display(LinkStack S)
{
 LinkStack p=S;
 while(p)
 {
  printf("%s",p->data);
  p=p->next;
 }
 return OK;

}


int main()
{
 ReadFile();
 char a[100];
 gets(a);
 Handle_str1(a);
return 0;
}
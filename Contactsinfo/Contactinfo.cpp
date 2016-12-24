//存在问题：程序将contacts_list.txt进行修改，结果写入newcontactsinfo.txt文件之后，带程序结束之时想要
//将newcontactsinfo文件重命名成contacts_list.txt失败！
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <easyx.h>
#include <graphics.h>
#include <string.h>
#include <windows.h>
#include <mmsystem.h>
#include <locale.h>
#define N 15
#define CTCS struct contacts
//定义全局变量
IMAGE img[7];
int count;//用来表示通讯录中的信息条数
MOUSEMSG m;
struct contacts
{
  char name[20];
  char tel[12];
  char type[20];
  char mail[20];
}ctcs[N];
//引用性函数声明
int loadfile();
void sort();
void mainmenu();
void submenu();
void FlushMouseMsgBuffer();
void loadimages();
void allcontacts();
void family();
void friends();
void colleagues();
void profile(int i,int t);
void back(int t);
void add();
void delete_ctcs(int i);
void refresh();
void modify(int i);
void save();
//主函数
void main()
{
	loadimages();
	count=loadfile();
	sort();
	mainmenu();
	save();
	closegraph();
}
//加载图片
void loadimages()
{
	loadimage(&img[0], "photos\\Background.bmp");
	loadimage(&img[1], "photos\\submenu.bmp");
	loadimage(&img[2], "photos\\allcontacts.bmp");
	loadimage(&img[3], "photos\\family.bmp");
	loadimage(&img[4], "photos\\friends.bmp");
	loadimage(&img[5], "photos\\colleagues.bmp");
	loadimage(&img[6], "photos\\profiledelmodify.bmp");
	initgraph(300, 533);
}
//从文本文档中读取已有的信息并返回信息条数
int loadfile()
{
	FILE *fp;
    int i;
    if((fp=fopen("contacts_list.txt","r+"))==NULL)//解决了之前预想的可能会出现的必须有一个txt里面存在着一些附加的联系人信息的问题
    {
		printf("\nCannot open file!\n");
		exit(0);
	}
	i=0;
	rewind(fp);
	while(!feof(fp))
    {
		fscanf(fp,"%s%s%s%s",ctcs[i].name,ctcs[i].tel,ctcs[i].type,ctcs[i].mail);
		setlocale(LC_ALL,"chs");
		i++;
    }
	fclose(fp);
	return(i);
}

int loadfilenew()
{
	FILE *fp;
    int i;
    if((fp=fopen("newcontactsinfo.txt","r+"))==NULL)//解决了之前预想的可能会出现的必须有一个txt里面存在着一些附加的联系人信息的问题
    {
		printf("\nCannot open file!\n");
		exit(0);
	}
	i=0;
	rewind(fp);
	while(!feof(fp))
    {
		fscanf(fp,"%s%s%s%s",ctcs[i].name,ctcs[i].tel,ctcs[i].type,ctcs[i].mail);
		i++;
    }
	fclose(fp);
	return(i);
}
//将文本文档中的信息按照ASCII字典序排列
void sort()
{
	CTCS t;
	int i,j,w;
	i=0;
	while(i<count-1){ 
		w=i;
		j=i+1;
		while(j<count)
		{
			if(strcmp(ctcs[w].name,ctcs[j].name)>0)
				w=j;
			j++;
		}
		t=ctcs[w];
		ctcs[w]=ctcs[i];
		ctcs[i]=t;
		i++;
	}
}

void mainmenu()
{
	int x,y; 
	cleardevice();
	initgraph(300, 533);
	putimage(0,0,&img[0]);
    FlushMouseMsgBuffer();
	settextcolor(LIGHTBLUE);
	settextstyle(22,14,_T("黑体"));
	setbkmode(TRANSPARENT);   
	while(1){
      m=GetMouseMsg();
	  x=m.x;
	  y=m.y;
	  if(m.uMsg==WM_LBUTTONDOWN){
		  if(x>80&&x<230&&y>213&&y<240)
			  submenu();
		  if(x>88&&x<212&&y>280&&y<326)
			  exit(0);
	  }
	  else
		  continue;
   }
	getch();
}
//点击主页面中contact的按钮进去之后进行分组显示
void submenu()
{
	int x,y,t=6;
	FlushMouseMsgBuffer();
	cleardevice();
	initgraph(300, 533);
	putimage(0,0,&img[1]);
	while(1){
      m=GetMouseMsg();
	  x=m.x;
	  y=m.y;
	  if(m.uMsg==WM_LBUTTONDOWN){
		  if(x>100&&x<220&&y>93&&y<112)
			  allcontacts();
		  if(x>127&&x<178&&y>199&&y<219)
			  family();
		  if(x>130&&x<182&&y>303&&y<329)
			  friends();
		  if(x>133&&x<181&&y>411&&y<430)
			  colleagues();
		  if(x>100&&x<200&&y>400&&y<500)
			  back(t);
	  }
	  else
		  continue;
   }

}

void family()
{
	int i,j,n,x,y,num[N],t=2;
	FlushMouseMsgBuffer();
	cleardevice();
	initgraph(300, 533);
	putimage(0,0,&img[3]);
	for(i=0,n=0;i<count;i++)
		if(!strcmp(ctcs[i].type,"家人")){
			num[n]=i;
			n++;
			settextcolor(LIGHTBLUE);
			settextstyle(20,0,_T("楷体"));                                                      
			setbkmode(TRANSPARENT); 
			outtextxy(10,60+30*n,ctcs[i].name);
		}
	while(1){
			m=GetMouseMsg();
			x=m.x;
			y=m.y;
			if(m.uMsg==WM_LBUTTONDOWN){
				for(j=0;j<=n;j++){
					if(x>10&&x<170&&y>80+30*j&&y<100+30*j+30*j){
						profile(num[j],t);
					}
				}
				if(x>200&&x<290&&y>473&&y<523)
					back(5);
				if(x>10&&x<70&&y>500&&y<520){
					FlushMouseMsgBuffer();
					cleardevice();
					initgraph(300, 533);
					putimage(0,0,&img[3]);
					count=loadfile();
					sort();
					for(i=0,n=0;i<count;i++)
						if(!strcmp(ctcs[i].type,"家人")){
							num[n]=i;
							n++;
							settextcolor(LIGHTBLUE);
							settextstyle(20,0,_T("楷体"));                                                      
							setbkmode(TRANSPARENT); 
							outtextxy(10,60+30*n,ctcs[i].name);
						}
				}
			}
			else
				continue;
		}

}

void friends()
{
	int i,j,n,x,y,num[N],t=3;
	FlushMouseMsgBuffer();
	cleardevice();
	initgraph(300, 533);
	putimage(0,0,&img[4]);
	for(i=0,n=0;i<count;i++)
		if(!strcmp(ctcs[i].type,"朋友")){
			num[n]=i;
			n++;
			settextcolor(LIGHTBLUE);
			settextstyle(20,0,_T("楷体"));                                                      
			setbkmode(TRANSPARENT); 
			outtextxy(10,60+30*n,ctcs[i].name);
		}
	while(1){
			m=GetMouseMsg();
			x=m.x;
			y=m.y;
			if(m.uMsg==WM_LBUTTONDOWN){
				for(j=0;j<=n;j++){
					if(x>10&&x<170&&y>80+30*j&&y<100+30*j+30*j){
						profile(num[j],3);
					}
				}
				if(x>200&&x<290&&y>473&&y<523)
					back(5);
				if(x>10&&x<70&&y>500&&y<520){
					FlushMouseMsgBuffer();
					cleardevice();
					initgraph(300, 533);
					putimage(0,0,&img[4]);
					count=loadfile();
					sort();
					for(i=0,n=0;i<count;i++)
						if(!strcmp(ctcs[i].type,"朋友")){
							num[n]=i;
							n++;
							settextcolor(LIGHTBLUE);
							settextstyle(20,0,_T("楷体"));                                                      
							setbkmode(TRANSPARENT); 
							outtextxy(10,60+30*n,ctcs[i].name);
						}
				}
					
			}
			else
				continue;
		}
}

void colleagues()
{
	int i,j,n,x,y,num[N],t=4;
	FlushMouseMsgBuffer();
	cleardevice();
	initgraph(300, 533);
	putimage(0,0,&img[5]);
	for(i=0,n=0;i<count;i++)
		if(!strcmp(ctcs[i].type,"同事")){
			num[n]=i;
			n++;
			settextcolor(LIGHTBLUE);
			settextstyle(20,0,_T("楷体"));                                                      
			setbkmode(TRANSPARENT); 
			outtextxy(10,60+30*n,ctcs[i].name);
		}
	while(1){
			m=GetMouseMsg();
			x=m.x;
			y=m.y;
			if(m.uMsg==WM_LBUTTONDOWN){
				for(j=0;j<=n;j++){
					if(x>10&&x<170&&y>80+30*j&&y<100+30*j+30*j){
						profile(num[j],t);
					}
				}
				if(x>200&&x<290&&y>473&&y<523)
					back(5);
				if(x>10&&x<70&&y>500&&y<520)
				{
					FlushMouseMsgBuffer();
					cleardevice();
					initgraph(300, 533);
					putimage(0,0,&img[5]);
					count=loadfile();
					sort();
					for(i=0,n=0;i<count;i++)
						if(!strcmp(ctcs[i].type,"同事")){
							num[n]=i;
							n++;
							settextcolor(LIGHTBLUE);
							settextstyle(20,0,_T("楷体"));                                                      
							setbkmode(TRANSPARENT); 
							outtextxy(10,60+30*n,ctcs[i].name);
						}
				}
			}
			else
				continue;
		}

}

void allcontacts()
{
	int i,x,y,t=1;
	FlushMouseMsgBuffer();
	cleardevice();
	initgraph(300, 533);
	putimage(0,0,&img[2]);
	for(i=0;i<count;i++){
		settextcolor(LIGHTBLUE);
		settextstyle(20,0,_T("楷体"));                                                      
		setbkmode(TRANSPARENT); 
		outtextxy(10,80+30*i,ctcs[i].name);
	}
	while(1){
			m=GetMouseMsg();
			x=m.x;
			y=m.y;
			if(m.uMsg==WM_LBUTTONDOWN){
				for(i=0;i<=count;i++){
					if(x>10&&x<170&&y>80+30*i&&y<100+30*i){
						profile(i,t);
					}
				}
				if(x>180&&x<280&&y<120&&y>20){
					if(count<N)
						add();
					else{
						settextcolor(RED);
						settextstyle(40,0,_T("楷体"));
						setbkmode(TRANSPARENT); 
						outtextxy(10,80+30*i,"内存已满！");
					}
				}
				if(x>200&&x<290&&y>473&&y<523)
					back(5);
				if(x>10&&x<70&&y>500&&y<520)
					refresh();
			}
			else
				continue;
		}
}

void profile(int i,int t)
{
	int x,y;
	FlushMouseMsgBuffer();
	cleardevice();
	initgraph(300, 533);
	putimage(0,0,&img[6]);
	settextcolor(BROWN);
	settextstyle(50,0,_T("楷体"));                                                        //此处需要改。
	setbkmode(TRANSPARENT); 
	outtextxy(140,60+1*22.65,ctcs[i].name);
	settextstyle(25,0,_T("楷体"));
	outtextxy(135,145+2*22.65,ctcs[i].tel);
	outtextxy(100,185+3*22.65,ctcs[i].type);
	settextstyle(20,0,_T("楷体"));
	outtextxy(100,225+4*22.65,ctcs[i].mail);
	while(1){
      m=GetMouseMsg();
	  x=m.x;
	  y=m.y;
	  if(m.uMsg==WM_LBUTTONDOWN){
		  if(x>100&&x<200&&y>400&&y<500)
			  back(t);
		  if(x>150&&x<200&&y>20&&y<120){
			  modify(i);
		  }
		  if(x>230&&x<280&&y<120&&y>20){
			  delete_ctcs(i);
			  count=loadfilenew();
			  sort();
			  back(t);
			  //此处添加删除代码deletectcs();并注去下面一句代码//delete_ctcs(); ________________________________________________请添加删除函数
			  //putimage(0,0,&img[0]);
			  //delete的后续处理
		  }
	  }
	else
		  continue;
	}	  
}

void back(int t)
{
	int x,y;
	FlushMouseMsgBuffer();
	while(1){
      m=GetMouseMsg();
	  x=m.x;
	  y=m.y;
	  if(m.uMsg==WM_LBUTTONDOWN){
		  if(x>100&&x<200&&y>400&&y<500){
			  switch(t)
			  {
			  case 1:allcontacts();break;
			  case 2:family();break;
			  case 3:friends();break;
			  case 4:colleagues();break;
			  case 6:mainmenu();break;
			  }
		  }
		  if(x>200&&x<290&&y>473&&y<530&&t==5)
			  submenu();
		  if(x>230&&x<280&&y<120&&y>20){
			  switch(t)
			  {
			  case 1:allcontacts();break;
			  case 2:family();break;
			  case 3:friends();break;
			  case 4:colleagues();break;
			  }
		  }
	  }
	  else
		  continue;
	}	  
}

//可以添加但是未能实现判断重名等功能
void add()
{
	int i;
	FILE *fp;
	FlushMouseMsgBuffer();
	InputBox(ctcs[count].name,20,"请输入新的联系人姓名","添加新的联系人","罗伯特",false);
	InputBox(ctcs[count].tel,12,"请输入新的联系人电话","添加新的联系人","13812345678",false);
	InputBox(ctcs[count].type,20,"请输入新的联系人分组","添加新的联系人","家人",false);
	InputBox(ctcs[count].mail,20,"请输入新的联系人电子邮件","添加新的联系人","10@qq.com",false);
	/*
	for(i=0;i<count;i++)
		if(!strcmp(ctcs[i].name,pname)){
			settextcolor(LIGHTBLUE);
			settextstyle(20,0,_T("楷体"));                                                      
			setbkmode(TRANSPARENT); 
			outtextxy(0,0,"该联系人已存在！请重新输入或放弃输入！");
		}
		*/
	if((fp=fopen("contacts_list.txt","a+"))==NULL)
    {
		printf("\nCannot open file!\n");
		exit(0);
	}
	fprintf(fp,"\n%s %s %s %s",ctcs[count].name,ctcs[count].tel,ctcs[count].type,ctcs[count].mail);
	rewind(fp);
	count=loadfile();
	sort();
	fclose(fp);
}

void delete_ctcs(int i)
{
	FILE *fp;
	int j,flag;
	char *oldname="newcontactsinfo.txt";
	char *newname="contacts_list.txt";
	FlushMouseMsgBuffer();
	for(j=i;j<count;j++){
		strcpy(ctcs[j].name,ctcs[j+1].name);
		strcpy(ctcs[j].tel,ctcs[j+1].tel);
		strcpy(ctcs[j].type,ctcs[j+1].type);
		strcpy(ctcs[j].mail,ctcs[j+1].mail);
	}
	count=count-1;
	if((fp=fopen("newcontactsinfo.txt","w"))==NULL)
	{ 
		printf("\nCannot open file!\n");
		exit(0);
	}
	j=0;
	while(j<count){ 
		fprintf(fp,"%s %s %s %s",ctcs[j].name,ctcs[j].tel,ctcs[j].type,ctcs[j].mail);
		if(j<count-1)
			fprintf(fp,"\n");
		j++;
	}
	count=loadfilenew();
	flag=rename(oldname,newname);
	sort();
	fclose(fp);
}

void refresh()
{
	int i;
	FlushMouseMsgBuffer();
	cleardevice();
	initgraph(300, 533);
	putimage(0,0,&img[2]);
	count=loadfile();
	sort();
	for(i=0;i<count;i++){
		settextcolor(LIGHTBLUE);
		settextstyle(20,0,_T("楷体"));                                                      
		setbkmode(TRANSPARENT); 
		outtextxy(10,80+30*i,ctcs[i].name);
	}
}

void modify(int i)
{
	FILE *fp;
	int j,flag;
	char *oldname="newcontactsinfo.txt";
	char *newname="contacts_list.txt";
	FlushMouseMsgBuffer();
	InputBox(ctcs[i].tel,12,"请输入新的联系人电话","添加新的联系人","13812345678",false);
	InputBox(ctcs[i].type,20,"请输入新的联系人分组","添加新的联系人","家人",false);
	InputBox(ctcs[i].mail,20,"请输入新的联系人电子邮件","添加新的联系人","10@qq.com",false);  
	if((fp=fopen("newcontactsinfo.txt","w"))==NULL)
	{ 
		printf("\nCannot open file!\n");
		exit(0);
	}
	j=0;
	while(j<count){ 
		fprintf(fp,"%s %s %s %s",ctcs[j].name,ctcs[j].tel,ctcs[j].type,ctcs[j].mail);
		if(j<count-1)
			fprintf(fp,"\n");
		j++;
	}
	count=loadfilenew();
	flag=rename(oldname,newname);
	sort();
	fclose(fp);
}

void save()
{ FILE *fp;
  int i;
  if((fp=fopen("newcontactsinfo.txt","w"))==NULL)
  { 
  printf("\nCannot open file!\n");
  exit(0);
  }
  i=0;
  while(i<count)
  { 
  fprintf(fp,"%s %s %s %s",ctcs[i].name,ctcs[i].tel,ctcs[i].type,ctcs[i].mail);
  if(i<count-1)fprintf(fp,"\n");
  i++;
  }
  fclose(fp);
}
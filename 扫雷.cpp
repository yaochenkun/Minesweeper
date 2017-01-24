#include<stdio.h>
#include<graphics.h>
#include<conio.h>
#include<time.h>
#pragma comment(lib,"winmm.lib")
/***************************************************************************************************************************************/
/*�궨��*/
/***************************************************************************************************************************************/
#define NOMINE 0/*����*/
#define MINE 1/*����*/
#define UNHIT 2/*δ��*/
#define HIT 3/*�ѷ�*/
#define MARK 4/*����*/
#define UNDETERMINE 5/*�ʺ�*/
#define STOP 6/*��ͣ*/
#define KEEPON 7/*����*/
/***************************************************************************************************************************************/
/*��������*/
/***************************************************************************************************************************************/
int  first();/*��Ϸ��������*/
void menu();/*�˵���*/
void move();/*�Ѷȷ����ƶ�Ч��*/
void stop();/*��ͣͼ��*/
void keepon();/*����ͼ��*/
void picture(int x);/*�Ѷȷ���*/
void cover(int x);/*�����Ѷȷ���*/
void extend();/*��չ��ʼ*/
void amount9();/*9X9���*/
void cover9();/*9X9���Ǳ��*/
void amount16();/*16X16���*/
void cover16();/*16X16���Ǳ��*/
void clock(time_t t1);/*ʱ��*/
void minenumber();/*ʣ������*/
void mine(int x,int y);/*��ͼ��(����)*/
void blank(int a,int b);/*��긲��(�±�)*/
void remove(int a,int b);/*��껹ԭ(�±�)*/
void colornumber(int m,int x,int y);/*��ɫ����(�±�)*/
void sign(int a,int b);/*����ͼ��(�±�)*/
void remain(int a,int b);/*�ʺ�ͼ��(�±�)*/
void number9(int n,int a,int b);/*9X9���ַ���(�±�)*/
void number16(int n,int a,int b);/*16X16���ַ���(�±�)*/
void judge9(int i,int j);/*9X9����(�±�)*/
void open9(int i,int j);/*9X9����(�±�)*/
void judge16(int i,int j);/*16X16����(�±�)*/
void open16(int i,int j);/*16X16����(�±�)*/
void sound9(int i,int j);/*9X9��Ч*/
void sound16(int i,int j);/*16X16��Ч*/
/***************************************************************************************************************************************/
/*������*/
/***************************************************************************************************************************************/
/*����ȫ�ֶ�ά����*/			/*�洢����*/
int	map1[9][9],map2[16][16];/*MINE/NOMINE*/
int _map1[9][9],_map2[16][16];/*HIT/UNHIT/MARK/UNDETERMINE*/
int sum/*����ȫ�ֱ���ͳ���ѷ��������*/,minenum/*����ʣ������*/;
time_t t1,t2,t3,t4;/*t1��¼���ȿ�ʼʱ��,t2ˢ�µ�ǰʱ��,t3��¼��ͣ���µ�ʱ��,t4��¼�������µ�ʱ��*/
/***************************************************************************************************************************************/
void main()/*������*/
{
	initgraph(640, 480);
	if(first())
	{
		cleardevice();
		menu();/*���˵�*/
		stop();/*��ʼ��"��ͣͼ��"*/ 
		MOUSEMSG m; /*����������*/
		while(true)/*"һ������ѭ��"���Բ����"�˵���"�������Ϣ*/
		{     
			m=GetMouseMsg();
			if(m.uMsg==WM_LBUTTONDOWN)/*�������*/
				if((m.x>20&&m.x<140)&&(m.y>30&&m.y<80))/*ʶ�����"����"���"�Ѷ�"��Ϣ*/
				{
					printf("\a");
					move();/*����"�Ѷȷ����ƶ�Ч��"����*/
					extend();/*����"��չ��ʼ"����*/
				}
				else if((m.x>20&&m.x<140)&&(m.y>230&&m.y<280))/*ʶ�����"����"���"�˳�"��Ϣ*/
				{	
					printf("\a");
					closegraph();
					exit(0);/*�رմ��ڲ��˳�����ϵͳ*/
				}
		}
	}
}
/***************************************************************************************************************************************/
/*��������*/
/***************************************************************************************************************************************/
int  first()/*��Ϸ��������*/
{	
	int points1[6],points2[6];/*�������������εĵ�����*/
	int points3[6],points4[6];
	points1[0]=260;points1[1]=140;points1[2]=(int)(260+50*0.866);points1[3]=(int)(140+50*1.5);points1[4]=(int)(260-50*0.866);points1[5]=(int)(140+50*1.5);
	points2[0]=260;points2[1]=(int)(140+50*2);points2[2]=(int)(260-50*0.866);points2[3]=(int)(140+50*0.5);points2[4]=(int)(260+50*0.866);points2[5]=(int)(140+50*0.5);
	points3[0]=370;points3[1]=140;points3[2]=(int)(370+50*0.866);points3[3]=(int)(140+50*1.5);points3[4]=(int)(370-50*0.866);points3[5]=(int)(140+50*1.5);
	points4[0]=370;points4[1]=(int)(140+50*2);points4[2]=(int)(370-50*0.866);points4[3]=(int)(140+50*0.5);points4[4]=(int)(370+50*0.866);points4[5]=(int)(140+50*0.5);
	setfillstyle(WHITE);/*"ɨ��"����*/
	setcolor(WHITE);
	fillpolygon(3,points1);fillpolygon(3,points2);fillpolygon(3,points3);fillpolygon(3,points4);
	setfillstyle(BLACK);
	fillcircle(260,190,25);fillcircle(370,190,25);
	setcolor(WHITE);
	outtextxy(253,181,"ɨ");outtextxy(363,181,"��");/*"ɨ��"����*/
	outtextxy(279,250,"By Chicken");/*"125�����"����*/
	
	IMAGE tmp;
	getimage(&tmp,0,0,textwidth("�����������"),textheight("�����������"));/*���浱ǰͼ��*/
	while(true)/*��������������һֱ�ƶ�*/
	{
		for(int i=0;i<510;i++)/*�����ں�����0-510��Χ�ƶ�*/
		{
			outtextxy(i,450,"�����������");/*"�����������"����*/
			Sleep(20);/*��ʱ*/
			putimage(i,450,&tmp);/*��ӡ��ǰͼ��*/
			if(kbhit())/*������Ϣ*/
			{
				printf("\a");
				return 1;/*��������1*/
			}
		}
		for(;i>0;i--)/*ѭ���ƶ�*/
		{
			outtextxy(i,450,"�����������");
			Sleep(20); 
			putimage(i,450,&tmp);
			if(kbhit())
			{
				printf("\a");
				return 1;
			}
		}
	}
}
/***************************************************************************************************************************************/
void menu()/*�˵���*/
{
	setcolor(WHITE);
	setfillstyle(DARKGRAY,24);
	setbkmode(DARKGRAY);
	bar(20,30,140,80);/*�Ѷȿ�*/
	rectangle(20,30,140,80);/*�ӱ߿�*/
	bar(20,130,140,180);/*������*/
	rectangle(20,130,140,180);
	bar(20,230,140,280);/*�˳���*/
	rectangle(20,230,140,280);
	outtextxy(65,48,"�Ѷ�");/*"�Ѷ�"����*/
	outtextxy(65,148,"����");/*"����"����*/
	outtextxy(65,248,"�˳�");/*"�˳�"����*/
	int points1[6],points2[6];/*ʣ��ͼ��*/
	points1[0]=50;points1[1]=400;points1[2]=(int)(50+25*0.866);points1[3]=(int)(400+25*1.5);points1[4]=(int)(50-25*0.866);points1[5]=(int)(400+25*1.5);
	points2[0]=50;points2[1]=(int)(400+25*2);points2[2]=(int)(50-25*0.866);points2[3]=(int)(400+25*0.5);points2[4]=(int)(50+25*0.866);points2[5]=(int)(400+25*0.5);
	setfillstyle(WHITE);
	setcolor(WHITE);
	fillpolygon(3,points1);fillpolygon(3,points2);
	setfillstyle(BLACK);
	fillcircle(50,425,12.5);
}
/***************************************************************************************************************************************/
void move()/*�Ѷȷ����ƶ�Ч��*/
{
	int i;
	for(i=141;i<210;i++)/*��չ��9   X   9��16  X  16����*/
	{
		picture(i);
		Sleep(9);
		cover(i);
	}
		picture(i);
		setbkmode(DARKGRAY);
		outtextxy(i+36,48,"9   X   9");

	for(i=331;i<411;i++)
	{
		picture(i);
		Sleep(9);
		cover(i);
	}
		picture(i);
		setbkmode(DARKGRAY);
		outtextxy(i+36,48,"16  X  16");
}
/***************************************************************************************************************************************/
void stop()/*��ͣͼ��*/
{	
	setcolor(WHITE);
	setfillstyle(WHITE);
	bar(38,348,47,372);
	bar(53,348,62,372);
}
/***************************************************************************************************************************************/
void keepon()/*����ͼ��*/
{
	int points[6];
	points[0]=38;points[1]=348;points[2]=38;points[3]=372;points[4]=62;points[5]=360;
	setcolor(WHITE);
	setfillstyle(WHITE);
	fillpolygon(3,points);
}
/***************************************************************************************************************************************/
void picture(int x)/*�Ѷȷ���*/
{
	setcolor(WHITE);
	setfillstyle(DARKGRAY,24);
	bar(x,30,x+120,80);
	rectangle(x,30,x+120,80);
}
/***************************************************************************************************************************************/
void cover(int x)/*�����Ѷȷ���*/
{
	setcolor(BLACK);
    setfillstyle(BLACK);
	bar(x,30,x+120,80);
	rectangle(x,30,x+120,80);
}
/***************************************************************************************************************************************/
void extend()/*��չ��ʼ*/
{	
	/*"����"����*/
	setcolor(BLACK);setfillstyle(BLACK);bar(38,348,62,372);/*����ǰһ�ֲ����Ĳ���ͼ��*/stop();/*��ͣͼ��*/  
	setfillstyle(BLACK);bar(95,418,133,440);/*����ǰһ�ֲ�����ʣ������*/
	setfillstyle(BLACK);bar(95,353,133,373);/*����ǰһ�ֲ�����ʱ������*/
/***************************************************************************************************************************************/
	MOUSEMSG m; /*����������*/

	int  lastx=1,lasty=1;/*�洢��һʱ���������λ��*/
	while(true)/*"��������ѭ��"���Բ����"�Ѷ�"�������Ϣ*/
	{
		m=GetMouseMsg();
		if(m.uMsg==WM_LBUTTONDOWN)/*�������*/
			if((m.x>211&&m.x<331)&&(m.y>30&&m.y<80))/*ʶ�����"ѡ�Ѷ�ʱ"���"9   X   9"��Ϣ*/
			{
				PlaySound("\\ɨ��\\��Ч\\Start.wav",NULL,SND_FILENAME|SND_ASYNC); 
				amount9();/*����*/
				picture(210);/*�����ѶȾ��θ���(Ϊ�˽���ɫ����ת���ɺ�ɫ����)*/
				setcolor(LIGHTRED);
				outtextxy(211+36,48,"9   X   9");
/********************************************************����************************************************************/
				int x,y/*�����±�*/,s=0;/*��������*/
				sum=0;/*��ʼ���ѷ��������*/
				minenum=10;/*��ʼ��ʣ������*/minenumber();/*ʣ������������*/
				
				for(x=0;x<9;x++)/*��ʼ�����з���"δ��"*/
					for(y=0;y<9;y++)
						_map1[x][y]=UNHIT;/*UNHIT��ʾ"δ��"*/
			
				for(x=0;x<9;x++)/*��ʼ�����з���"����"*/
					for(y=0;y<9;y++)
						map1[x][y]=NOMINE;/*NOMINE��ʾ"����"*/
				
				srand((unsigned)time(NULL));/*����time(NULL)��ȡʱ��ʵ�ֲ���*/ 
				while(true)
				{
					if(s<10)/*��������10��*/
					{
						x=rand()%9;y=rand()%9;/*�����±�Ϊ0-8���������*/
						if(map1[x][y]!=MINE)/*MINE��ʾ"����"*/
						{
							map1[x][y]=MINE;
							s++;/*ͳ���Ѳ��׵ĸ���*/
						}
					}
					else break;
				}
/********************************************************��ʼ************************************************************/
				t1=time(NULL);/*��ȡ��ʼϵͳʱ��*/
				int onoff=KEEPON;/*�����Ǳ�����¼�Ƿ���ͣ��(KEEPON��ʾδ��ͣ,STOP��ʾ��ͣ��)*/
				while(true)
				{
					if(onoff==KEEPON)/*֮ǰδ��ͣ*/
						clock(t1);/*��ȡ��ǰʱ��*/
					else/*֮ǰ��ͣ��*/
					{
						t1=t1+(t4-t3);/*�ֲ���ͣ��ʱ��*/
						clock(t1);
					}
					onoff=KEEPON;/*���ü�����־*/
					m=GetMouseMsg();
					if(_map1[(lasty-130)/20][(lastx-210)/20]==UNHIT)/*��һ���ǳ���,֮��ÿһ�ζ�Ҫ������һʱ���������λ���Ƿ�ɨ��*/
						remove((lasty-130)/20,(lastx-210)/20);/*��ԭ��ɫ:��һ���ǳ���,֮��ÿһ�ζ�Ҫ����һʱ�����������Ĺ�긲�ǻ�ԭ�ɵ�ɫ*/
					if((m.x>210&&m.x<390)&&(m.y>130&&m.y<310))/*�����9X9���Χ��*/
					{
						if(_map1[(m.y-130)/20][(m.x-210)/20]==UNHIT)/*�������λ����"δ��"*/
						{	
							blank((m.y-130)/20,(m.x-210)/20);
							lastx=m.x;lasty=m.y;/*�洢��ǰʱ������������,�Ա���һ�θ���ʹ��*/
						}
						if(m.uMsg==WM_LBUTTONDOWN)/*������*/
						{
							x=(m.y-130)/20;y=(m.x-210)/20;/*���������껻�������±�*/
							sound9(x,y);
							judge9(x,y);/*����9X9��������*/
						}
						if(m.uMsg==WM_RBUTTONDOWN)/*�Ҽ����*/
						{
							x=(m.y-130)/20;y=(m.x-210)/20;
							switch(_map1[x][y])
							{
								case UNHIT:/*�������λ����"δ��"*/
								{
									sign(x,y);/*����ͼ��*/
									_map1[x][y]=MARK;
									minenum--;
									minenumber();
								}break;
								case MARK:/*�������λ����"����"*/
								{
									remain(x,y);/*�ʺ�ͼ��*/
									_map1[x][y]=UNDETERMINE;
									minenum++;
									minenumber();
								}break;
								case UNDETERMINE:/*�������λ����"�ʺ�"*/
								{
									blank(x,y);/*�շ���*/
									_map1[x][y]=UNHIT;
								}break;
							}		
						}
						if(m.uMsg==WM_LBUTTONDBLCLK)/*���˫��*/
						{
							x=(m.y-130)/20;y=(m.x-210)/20;
							sound9(x,y);
							if(_map1[x][y]==HIT)/*�����ѷ�����*/
								open9(x,y);/*����9X9������*/
						}
					}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>40&&m.x<60)&&(m.y>350&&m.y<370))/*ʶ�����"��Ϸ��"���"��ͣ"��Ϣ*/
							{
								printf("\a");
								onoff=STOP;/*��ͣ���,�Ա��γɺ�����֧������ͣ�������ͬ�������*/
								t3=time(NULL);/*��ʱ��ȡ"��ͣʱ"��ϵͳʱ��*/
								setcolor(BLACK);setfillstyle(BLACK);bar(38,348,62,372);/*������ͣͼ��*/
								keepon();/*����ͼ��*/
								while(true)/*��"��ͣ��"�ȴ������Ӧ*/
								{
									m=GetMouseMsg();
									if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>40&&m.x<60)&&(m.y>350&&m.y<370))/*ʶ�����"��ͣ��"���"����"��Ϣ*/
									{
										printf("\a");
										t4=time(NULL);/*��ʱ��ȡ"����ʱ"��ϵͳʱ��*/
										setcolor(BLACK);setfillstyle(BLACK);bar(38,348,62,372);/*���Ǽ���ͼ��*/
										stop();/*��ͣͼ��*/
										break;
									}
									else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>130&&m.y<180))/*ʶ�����"��ͣ��"���"����"��Ϣ*/
											{outtextxy(211+36,48,"9   X   9");cover9();extend();}/*�����Ѷȷ���,�ع鵽������*/
									else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>230&&m.y<280))/*ʶ�����"��ͣ��"���"�˳�"��Ϣ*/
											{closegraph();exit(0);}/*�رմ��ڲ��˳�����ϵͳ*/
								}
							}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>130&&m.y<180))/*ʶ�����"��Ϸ��"���"����"��Ϣ*/
					{
						printf("\a");
						outtextxy(211+36,48,"9   X   9");cover9();extend();/*�����Ѷ�ѡ�񷽿飬�ع鵽������*/
					}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>230&&m.y<280))/*ʶ�����"��Ϸ��"���"�˳�"��Ϣ*/
					{	
						printf("\a");
						closegraph();
						exit(0);/*�رմ��ڲ��˳�����ϵͳ*/
					}
				}
			}
/***************************************************************************************************************************************/
			else if((m.x>411&&m.x<531)&&(m.y>30&&m.y<80))/*ʶ����ҡ�ѡ�Ѷ�ʱ�������16  X  16����Ϣ*/
			{
				PlaySound("\\ɨ��\\��Ч\\Start.wav",NULL,SND_FILENAME|SND_ASYNC); 
				amount16();
				picture(411);
				setcolor(LIGHTRED);
				outtextxy(410+36,48,"16  X  16");
/********************************************************����************************************************************/
				int x,y,s=0;
				sum=0;
				minenum=40;minenumber();
				
				for(x=0;x<16;x++)
					for(y=0;y<16;y++)
						_map2[x][y]=UNHIT;
			
				for(x=0;x<16;x++)
					for(y=0;y<16;y++)
						map2[x][y]=NOMINE;
				
				srand((unsigned)time(NULL));
				while(true)
				{
					if(s<40)/*��������40��*/
					{
						x=rand()%16;y=rand()%16;/*�����±�Ϊ0-15���������*/
						if(map2[x][y]!=MINE)
						{
							map2[x][y]=MINE;
							s++;
						}
					}
					else break;
				}
/********************************************************��ʼ************************************************************/
				t1=time(NULL);
				int onoff=KEEPON;
				while(true)
				{
					if(onoff==KEEPON)
						clock(t1);
					else	
					{
						t1=t1+(t4-t3);
						clock(t1);
					}
					onoff=KEEPON;
					m=GetMouseMsg();
					if(_map2[(lasty-130)/20][(lastx-210)/20]==UNHIT)
						remove((lasty-130)/20,(lastx-210)/20);
					if((m.x>210&&m.x<530)&&(m.y>130&&m.y<450))
					{
						if(_map2[(m.y-130)/20][(m.x-210)/20]==UNHIT)
						{	
							blank((m.y-130)/20,(m.x-210)/20);
							lastx=m.x;lasty=m.y;
						}
						if(m.uMsg==WM_LBUTTONDOWN)
						{
							x=(m.y-130)/20;y=(m.x-210)/20;
							sound16(x,y);
							judge16(x,y);/*����16X16��������*/
						}
						if(m.uMsg==WM_RBUTTONDOWN)
						{
							x=(m.y-130)/20;y=(m.x-210)/20;
							switch(_map2[x][y])
							{
								case UNHIT:
								{
									sign(x,y);
									_map2[x][y]=MARK;
									minenum--;
									minenumber();
								}break;
								case MARK:
								{
									remain(x,y);
									_map2[x][y]=UNDETERMINE;
									minenum++;
									minenumber();
								}break;
								case UNDETERMINE:
								{
									blank(x,y);
									_map2[x][y]=UNHIT;
								}break;
							}		
						}
						if(m.uMsg==WM_LBUTTONDBLCLK)
						{
							x=(m.y-130)/20;y=(m.x-210)/20;
							sound16(x,y);
							if((_map2[x][y]==HIT))
								open16(x,y);/*����16X16������*/
						}
					}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>40&&m.x<60)&&(m.y>350&&m.y<370))
							{
								printf("\a");
								onoff=STOP;
								t3=time(NULL);
								setcolor(BLACK);setfillstyle(BLACK);bar(38,348,62,372);
								keepon();
								while(true)
								{
									m=GetMouseMsg();
									if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>40&&m.x<60)&&(m.y>350&&m.y<370))
									{
										printf("\a");
										t4=time(NULL);
										setcolor(BLACK);setfillstyle(BLACK);bar(38,348,62,372);
										stop();
										break;
									}
									else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>130&&m.y<180))
											{outtextxy(410+36,48,"16  X  16");cover16();extend();}
									else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>230&&m.y<280))
											{closegraph();exit(0);}
								}
							}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>130&&m.y<180))
					{
						printf("\a");
						outtextxy(410+36,48,"16  X  16");cover16();extend();
					}
					else if((m.uMsg==WM_LBUTTONDOWN)&&(m.x>20&&m.x<140)&&(m.y>230&&m.y<280))
					{
						printf("\a");
						closegraph();exit(0);
					}
				}
/***************************************************************************************************************************************/				
			}
			else if((m.x>20&&m.x<140)&&(m.y>230&&m.y<280))/*ʶ����ҡ�ѡ�Ѷ�ʱ��������˳�����Ϣ*/
			{	
				printf("\a");
				closegraph();exit(0);
			}
	}
}
/***************************************************************************************************************************************/
void amount9()/*9X9���*/
{
	setcolor(WHITE);/*�������ڵı߿���ɫ*/
	setfillstyle(DARKGRAY,24);/*�������ڵ������ɫ*/
	bar(210,130,390,310);/*�����η�Χ*/
	for(int k=0;k<10;k++)/*��9x9�ĸ�����*/
	{
		 line(210+20*k,130,210+20*k,310);
		 line(210,130+20*k,390,130+20*k);
	}
}
/***************************************************************************************************************************************/
void cover9()/*9X9���Ǳ��*/
{
	setcolor(BLACK);
    setfillstyle(BLACK);
	bar(210,130,390,310);
	rectangle(210,130,390,310);
}
/***************************************************************************************************************************************/
void amount16()/*16X16���*/
{
	setcolor(WHITE);/*�������ڵı߿���ɫ*/
	setfillstyle(DARKGRAY,24);/*�������ڵ������ɫ*/
	bar(210,130,530,450);/*�����η�Χ*/
	for(int k=0;k<17;k++)/*��16x16�ĸ�����*/
	{
		line(210+20*k,130,210+20*k,450);
		line(210,130+20*k,530,130+20*k);
	}
}
/***************************************************************************************************************************************/
void cover16()/*16X16���Ǳ��*/
{
	setcolor(BLACK);
    setfillstyle(BLACK);
	bar(210,130,530,450);
	rectangle(210,130,530,450);
}
/***************************************************************************************************************************************/
void clock(time_t t1)/*ʱ��*/
{
	setcolor(WHITE);
	setfillstyle(BLACK);
	t2=time(NULL);
	char str[2];
	bar(95,353,133,373);
	sprintf(str,"%d",t2-t1);
	outtextxy(95,353,str);
}
/***************************************************************************************************************************************/
void minenumber()/*ʣ������*/
{
	char str[2];
	setcolor(WHITE);
	setfillstyle(BLACK);
	bar(95,418,133,440);
	sprintf(str,"%d",minenum);
	outtextxy(95,418,str);	
}
/***************************************************************************************************************************************/
void mine(int x,int y)/*��ͼ��(����)*/
{
	blank((y-130)/20,(x-210)/20);
	int points1[6],points2[6];
	points1[0]=x;points1[1]=y;points1[2]=(int)(x+10*0.866);points1[3]=(int)(y+10*1.5);points1[4]=(int)(x-10*0.866);points1[5]=(int)(y+10*1.5);
	points2[0]=x;points2[1]=(int)(y+10*2);points2[2]=(int)(x-10*0.866);points2[3]=(int)(y+10*0.5);points2[4]=(int)(x+10*0.866);points2[5]=(int)(y+10*0.5);
	setfillstyle(WHITE);
	setcolor(WHITE);
	fillpolygon(3,points1);fillpolygon(3,points2);
	setfillstyle(BLACK);
	fillcircle(x,y+10,5);
}
/***************************************************************************************************************************************/
void blank(int a,int b)/*��긲��(�±�)*/
{	
	setcolor(WHITE);
	setfillstyle(LIGHTGRAY,24);
	fillrectangle(210+20*b,130+20*a,210+20*b+20,130+20*a+20);	
}
/***************************************************************************************************************************************/
void remove(int a,int b)/*��껹ԭ(�±�)*/
{	
	setcolor(WHITE);
	setfillstyle(DARKGRAY,24);
	fillrectangle(210+20*b,130+20*a,210+20*b+20,130+20*a+20);	
}
/***************************************************************************************************************************************/
void colornumber(int m,int x,int y)/*��ɫ����(�±�)*/
{
	char str[2];
	blank(x,y);
	switch(m)/*���ݲ�ͬ������ʾ��ͬ��ɫ*/
	{
		case 1:
			{
				setcolor(WHITE);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 2:
			{
				setcolor(LIGHTGREEN);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 3:
			{
				setcolor(YELLOW);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 4:
			{
				setcolor(LIGHTCYAN);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 5:
			{
				setcolor(LIGHTRED);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 6:
			{
				setcolor(BLACK);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 7:
			{
				setcolor(CYAN);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
		case 8:
			{
				setcolor(LIGHTMAGENTA);
				setbkmode(TRANSPARENT);
				sprintf(str,"%d",m);
				outtextxy(210+20*y+6,130+20*x+3,str);
			}break;
	}
}
/***************************************************************************************************************************************/
void sign(int a,int b)/*����ͼ��(�±�)*/
{
	int points[6];
	points[0]=210+20*b+10;points[1]=130+20*a+5;points[2]=210+20*b+10;points[3]=130+20*a+11;points[4]=210+20*b+4;points[5]=130+20*a+11;
	blank(a,b);/*��ʾ�����ֵĿո�*/
	setcolor(LIGHTRED);
	setfillstyle(LIGHTRED);
	fillpolygon(3,points);
	setcolor(WHITE);
	line(210+20*b+6,130+20*a+15,210+20*b+14,130+20*a+15);/*�������*/
	line(210+20*b+6,130+20*a+16,210+20*b+14,130+20*a+16);/*�Ӵ�*/
	line(210+20*b+10,130+20*a+15,210+20*b+10,130+20*a+5);/*��������*/
	line(210+20*b+11,130+20*a+15,210+20*b+11,130+20*a+5);/*�Ӵ�*/
}
/***************************************************************************************************************************************/
void remain(int a,int b)/*�ʺ�ͼ��(�±�)*/
{
	blank(a,b);/*��ʾ�����ֵĿո�*/
	setbkmode(TRANSPARENT);
	outtextxy(210+20*b+6,130+20*a+3,"?");
}
/***************************************************************************************************************************************/
void number9(int n,int a,int b)/*9X9���ַ���(�±�)*/
{
	_map1[a][b]=HIT;/*�ѷ�������*/
	char str[20];/*��������*/
	int old;/*���վɼ�¼*/

	if(n==0)/*���Ź�����û����*/
		blank(a,b);/*��ʾ�ո�*/
	else
		colornumber(n,a,b);/*��ɫ����ͼ��*/
	sum++;/*�ѷ�������Ŀ��1*/
	if(sum==71)/*�ѷ�������Ŀ����ﵽ71����ʤ��*/
	{
		PlaySound("\\ɨ��\\��Ч\\Win.wav",NULL,SND_FILENAME|SND_ASYNC);

		/*��߼�¼�ж�*/
		FILE *fp1,*fp2;
		if((fp1=fopen("record9.txt","r"))==NULL)/*û���ļ�����*/
		{
			fp2=fopen("record9.txt","w");
			InputBox(str,10,"��ϲ������\n���¼�¼������\n���´����ɣ���","�¼�¼");
			fprintf(fp2,"%s %d",str,t2-t1);/*����߼�¼д���ļ�*/
			fclose(fp2);
		}
		else
		{
			fscanf(fp1,"%s %d",str,&old);/*����ɼ�¼*/
			if(t2-t1<old)/*�¼�¼*/
			{
				fp2=fopen("record9.txt","w");
				InputBox(str,10,"��ϲ������\n���¼�¼������\n���´����ɣ���","�¼�¼");
				fprintf(fp2,"%s %d",str,t2-t1);/*����߼�¼д���ļ�*/
				fclose(fp2);
			}
			else
			{	
				HWND wnd=GetHWnd();
				MessageBox(wnd,"����߼�¼�Ͳ�һ�����~\n�ٽ�����Ӵ~","��ʾ",MB_OK|MB_ICONASTERISK);
			}
			fclose(fp1);
		}

		HWND wnd=GetHWnd();/*��Ϸʤ���Ի���*/
		if (MessageBox(wnd,"ɨ�׳ɹ�!\n�Ƿ�����?","ѯ��",MB_YESNO|MB_ICONQUESTION)==IDYES)
			{setcolor(WHITE);outtextxy(211+36,48,"9   X   9");cover9();extend();}
		else {closegraph();exit(0);}
	}
}
/***************************************************************************************************************************************/
void number16(int n,int a,int b)/*16X16���ַ���(�±�)*/
{
	_map2[a][b]=HIT;
	char str[20];
	int old;

	if(n==0)
		blank(a,b);
	else
		colornumber(n,a,b);
	sum++;
	if(sum==216)/*�ѷ�������Ŀ����ﵽ216����ʤ��*/
	{
		PlaySound("\\ɨ��\\��Ч\\Win.wav",NULL,SND_FILENAME|SND_ASYNC);

		FILE *fp1,*fp2;
		if((fp1=fopen("record16.txt","r"))==NULL)
		{
			fp2=fopen("record16.txt","w");
			InputBox(str,10,"��ϲ������\n���¼�¼������\n���´����ɣ���","�¼�¼");
			fprintf(fp2,"%s %d",str,t2-t1);
			fclose(fp2);
		}
		else
		{
			fscanf(fp1,"%s %d",str,&old);
			if(t2-t1<old)
			{
				fp2=fopen("record16.txt","w");
				InputBox(str,10,"��ϲ������\n���¼�¼������\n���´����ɣ���","�¼�¼");
				fprintf(fp2,"%s %d",str,t2-t1);
				fclose(fp2);
			}
			else
			{	
				HWND wnd=GetHWnd();
				MessageBox(wnd,"����߼�¼�Ͳ�һ�����~\n�ٽ�����Ӵ~","��ʾ",MB_OK|MB_ICONASTERISK);
			}
			fclose(fp1);
		}		

		HWND wnd=GetHWnd();
		if (MessageBox(wnd,"ɨ�׳ɹ�!\n�Ƿ�����?","ѯ��",MB_YESNO|MB_ICONQUESTION)==IDYES)
			{setcolor(WHITE);outtextxy(410+36,48,"16  X  16");cover16();extend();}
		else {closegraph();exit(0);}
	}
}
/***************************************************************************************************************************************/
void judge9(int i,int j)/*9X9����(�±�)*/
{
	int num=0;/*ͳ�ƾŹ���������*/
	if(_map1[i][j]==UNHIT||_map1[i][j]==UNDETERMINE)/*��λ����δ����������ʺŷ���*/
	{
		switch(map1[i][j])
		{
			case MINE:/*��λ������*/
			{
				for(int e=0;e<9;e++)/*̯�Ʋ��µ���ͼ��*/
					for(int f=0;f<9;f++)
						if(map1[e][f]==1)
							mine(210+20*f+10,130+20*e);
				HWND wnd=GetHWnd();/*��Ϸ�����Ի���*/
				if (MessageBox(wnd,"ɨ��ʧ��!\n�Ƿ�����?","ѯ��",MB_YESNO|MB_ICONQUESTION)==IDYES)
					{outtextxy(211+36,48,"9   X   9");cover9();extend();}
				else 
					{closegraph();exit(0);}
			}
			case NOMINE:/*��λ�����ײ������Ź���������Ŀ*/
			{
				if(map1[i-1][j-1]==MINE&&((i-1)>=0&&(i-1)<=8)&&((j-1)>=0&&(j-1)<=8))/*�ų��߽����*/
					num++;/*��������num��1*/
				if(map1[i-1][j]==MINE&&((i-1)>=0&&(i-1)<=8)&&(j>=0&&j<=8))
					num++;
				if(map1[i-1][j+1]==MINE&&((i-1)>=0&&(i-1)<=8)&&((j+1)>=0&&(j+1)<=8))
					num++;
				if(map1[i][j-1]==MINE&&(i>=0&&i<=8)&&((j-1)>=0&&(j-1)<=8))
					num++;
				if(map1[i][j+1]==MINE&&(i>=0&&i<=8)&&((j+1)>=0&&(j+1)<=8))
					num++;
				if(map1[i+1][j-1]==MINE&&((i+1)>=0&&(i+1)<=8)&&((j-1)>=0&&(j-1)<=8))
					num++;
				if(map1[i+1][j]==MINE&&((i+1)>=0&&(i+1)<=8)&&(j>=0&&j<=8))
					num++;
				if(map1[i+1][j+1]==MINE&&((i+1)>=0&&(i+1)<=8)&&((j+1)>=0&&(j+1)<=8))
					num++;
			/*����λ�þŹ���������,�����õݹ�����ԾŹ���Ϊ���Ĳ�������8��������ԾŹ����ڵ�����Ŀ*/
				if(num==NOMINE)
				{
					number9(0,i,j);/*��ӡ�հ׷���ͼ��*/
					if((i-1)>=0&&(i-1)<=8&&((j-1)>=0&&(j-1)<=8))
						judge9(i-1,j-1);/*�ݹ����*/
					if((i-1)>=0&&(i-1)<=8&&(j>=0&&j<=8))
						judge9(i-1,j);			
					if((i-1)>=0&&(i-1)<=8&&((j+1)>=0&&(j+1)<=8))
						judge9(i-1,j+1);
					if((i>=0&&i<=8)&&((j-1)>=0&&(j-1)<=8))
						judge9(i,j-1);
					if((i>=0&&i<=8)&&((j+1)>=0&&(j+1)<=8))
						judge9(i,j+1);	
					if((i+1)>=0&&(i+1)<=8&&((j-1)>=0&&(j-1)<=8))
						judge9(i+1,j-1);
					if((i+1)>=0&&(i+1)<=8&&(j>=0&&j<=8))
						judge9(i+1,j);
					if((i+1)>=0&&(i+1)<=8&&((j+1)>=0&&(j+1)<=8))
						judge9(i+1,j+1);
				}
				else
				{
					number9(num,i,j);/*��ӡnum���ַ���ͼ��*/
					return;/*�˳��Ӻ���(�ݹ����)*/
				}
			}
		}
	}
}
/***************************************************************************************************************************************/
void open9(int i,int j)/*9X9����(�±�)*/
{
	int num=0/*��¼������Ŀ*/,all=0/*��¼���������ƥ����Ŀ*/;
	/*���������*/
	if(map1[i-1][j-1]==MINE&&((i-1)>=0&&(i-1)<=8)&&((j-1)>=0&&(j-1)<=8))
		num++;
	if(map1[i-1][j]==MINE&&((i-1)>=0&&(i-1)<=8)&&(j>=0&&j<=8))
		num++;
	if(map1[i-1][j+1]==MINE&&((i-1)>=0&&(i-1)<=8)&&((j+1)>=0&&(j+1)<=8))
		num++;
	if(map1[i][j-1]==MINE&&(i>=0&&i<=8)&&((j-1)>=0&&(j-1)<=8))
		num++;
	if(map1[i][j+1]==MINE&&(i>=0&&i<=8)&&((j+1)>=0&&(j+1)<=8))
		num++;
	if(map1[i+1][j-1]==MINE&&((i+1)>=0&&(i+1)<=8)&&((j-1)>=0&&(j-1)<=8))
		num++;
	if(map1[i+1][j]==MINE&&((i+1)>=0&&(i+1)<=8)&&(j>=0&&j<=8))
		num++;
	if(map1[i+1][j+1]==MINE&&((i+1)>=0&&(i+1)<=8)&&((j+1)>=0&&(j+1)<=8))
		num++;	
	/*�����������λ���Ƿ�ƥ��*/
	if(map1[i-1][j-1]==MINE&&_map1[i-1][j-1]==4&&((i-1)>=0&&(i-1)<=8)&&((j-1)>=0&&(j-1)<=8))
		all++;		
	if(map1[i-1][j]==MINE&&_map1[i-1][j]==4&&((i-1)>=0&&(i-1)<=8)&&(j>=0&&j<=8))
		all++;					
	if(map1[i-1][j+1]==MINE&&_map1[i-1][j+1]==4&&((i-1)>=0&&(i-1)<=8)&&((j+1)>=0&&(j+1)<=8))
		all++;			
	if(map1[i][j-1]==MINE&&_map1[i][j-1]==4&&(i>=0&&i<=8)&&((j-1)>=0&&(j-1)<=8))
		all++;					
	if(map1[i][j+1]==MINE&&_map1[i][j+1]==4&&(i>=0&&i<=8)&&((j+1)>=0&&(j+1)<=8))
		all++;				
	if(map1[i+1][j-1]==MINE&&_map1[i+1][j-1]==4&&((i+1)>=0&&(i+1)<=8)&&((j-1)>=0&&(j-1)<=8))
		all++;				
	if(map1[i+1][j]==MINE&&_map1[i+1][j]==4&&((i+1)>=0&&(i+1)<=8)&&(j>=0&&j<=8))
		all++;				
	if(map1[i+1][j+1]==MINE&&_map1[i+1][j+1]==4&&((i+1)>=0&&(i+1)<=8)&&((j+1)>=0&&(j+1)<=8))
		all++;		
	/*ƥ��*/
	if(all==num)
	{
		printf("\a");/*�����Ч*/
		if(map1[i-1][j-1]!=MINE&&((i-1)>=0&&(i-1)<=8)&&((j-1)>=0&&(j-1)<=8))/*�ų�����Ϊ����չ���Ĵ���ݹ�*/
			judge9(i-1,j-1);/*�ݹ����*/
		if(map1[i-1][j]!=MINE&&((i-1)>=0&&(i-1)<=8)&&(j>=0&&j<=8))
			judge9(i-1,j);	
		if(map1[i-1][j+1]!=MINE&&((i-1)>=0&&(i-1)<=8)&&((j+1)>=0&&(j+1)<=8))
			judge9(i-1,j+1);	
		if(map1[i][j-1]!=MINE&&(i>=0&&i<=8)&&((j-1)>=0&&(j-1)<=8))
			judge9(i,j-1);	
		if(map1[i][j+1]!=MINE&&(i>=0&&i<=8)&&((j+1)>=0&&(j+1)<=8))
			judge9(i,j+1);		
		if(map1[i+1][j-1]!=MINE&&((i+1)>=0&&(i+1)<=8)&&((j-1)>=0&&(j-1)<=8))
			judge9(i+1,j-1);	
		if(map1[i+1][j]!=MINE&&((i+1)>=0&&(i+1)<=8)&&(j>=0&&j<=8))
			judge9(i+1,j);	
		if(map1[i+1][j+1]!=MINE&&((i+1)>=0&&(i+1)<=8)&&((j+1)>=0&&(j+1)<=8))
			judge9(i+1,j+1);	
	}
	/*��ƥ��*/
	else 
	{
		PlaySound("\\ɨ��\\��Ч\\Lose.wav",NULL,SND_FILENAME|SND_ASYNC);/*��ը��Ч*/
		for(int e=0;e<9;e++)/*̯�Ʋ��µ���*/
			for(int f=0;f<9;f++)
				if(map1[e][f]==1)
					mine(210+20*f+10,130+20*e);
		HWND wnd=GetHWnd();/*��Ϸ�����Ի���*/
		if (MessageBox(wnd,"ɨ��ʧ��!\n�Ƿ�����?","ѯ��",MB_YESNO|MB_ICONQUESTION)==IDYES)
			{outtextxy(211+36,48,"9   X   9");cover9();extend();}
		else {closegraph();exit(0);}
	}
}
/***************************************************************************************************************************************/
void judge16(int i,int j)/*16X16����(�±�)*/
{
	int num=0;
	if(_map2[i][j]==UNHIT||_map2[i][j]==UNDETERMINE)
	{
		switch(map2[i][j])
		{
			case MINE:
			{
				for(int e=0;e<16;e++)/*̯�Ʋ��µ���*/
					for(int f=0;f<16;f++)
						if(map2[e][f]==1)
							mine(210+20*f+10,130+20*e);
				HWND wnd=GetHWnd();/*��Ϸ�����Ի���*/
				if (MessageBox(wnd,"ɨ��ʧ��!\n�Ƿ�����?","ѯ��",MB_YESNO|MB_ICONQUESTION)==IDYES)
					{outtextxy(410+36,48,"16  X  16");cover16();extend();}
				else {closegraph();exit(0);}
			}
			case NOMINE:
			{
				if(map2[i-1][j-1]==MINE&&((i-1)>=0&&(i-1)<=15)&&((j-1)>=0&&(j-1)<=15))
					num++;
				if(map2[i-1][j]==MINE&&((i-1)>=0&&(i-1)<=15)&&(j>=0&&j<=15))
					num++;
				if(map2[i-1][j+1]==MINE&&((i-1)>=0&&(i-1)<=15)&&((j+1)>=0&&(j+1)<=15))
					num++;
				if(map2[i][j-1]==MINE&&(i>=0&&i<=15)&&((j-1)>=0&&(j-1)<=15))
					num++;
				if(map2[i][j+1]==MINE&&(i>=0&&i<=15)&&((j+1)>=0&&(j+1)<=15))
					num++;
				if(map2[i+1][j-1]==MINE&&((i+1)>=0&&(i+1)<=15)&&((j-1)>=0&&(j-1)<=15))
					num++;
				if(map2[i+1][j]==MINE&&((i+1)>=0&&(i+1)<=15)&&(j>=0&&j<=15))
					num++;
				if(map2[i+1][j+1]==MINE&&((i+1)>=0&&(i+1)<=15)&&((j+1)>=0&&(j+1)<=15))
					num++;
				
				if(num==0)/*û����*/
				{
					number16(0,i,j);
					if((i-1)>=0&&(i-1)<=15&&((j-1)>=0&&(j-1)<=15))
						judge16(i-1,j-1);
					if((i-1)>=0&&(i-1)<=15&&(j>=0&&j<=15))
						judge16(i-1,j);			
					if((i-1)>=0&&(i-1)<=15&&((j+1)>=0&&(j+1)<=15))
						judge16(i-1,j+1);
					if((i>=0&&i<=15)&&((j-1)>=0&&(j-1)<=15))
						judge16(i,j-1);
					if((i>=0&&i<=15)&&((j+1)>=0&&(j+1)<=15))
						judge16(i,j+1);	
					if((i+1)>=0&&(i+1)<=15&&((j-1)>=0&&(j-1)<=15))
						judge16(i+1,j-1);
					if((i+1)>=0&&(i+1)<=15&&(j>=0&&j<=15))
						judge16(i+1,j);
					if((i+1)>=0&&(i+1)<=15&&((j+1)>=0&&(j+1)<=15))
						judge16(i+1,j+1);
				}
				else
				{
					number16(num,i,j);
					return;
				}
			}
		}
	}
}
/***************************************************************************************************************************************/
void open16(int i,int j)/*16X16����(�±�)*/
{
	int num=0,all=0;
	/*���������*/
	if(map2[i-1][j-1]==MINE&&((i-1)>=0&&(i-1)<=15)&&((j-1)>=0&&(j-1)<=15))
		num++;
	if(map2[i-1][j]==MINE&&((i-1)>=0&&(i-1)<=15)&&(j>=0&&j<=15))
		num++;
	if(map2[i-1][j+1]==MINE&&((i-1)>=0&&(i-1)<=15)&&((j+1)>=0&&(j+1)<=15))
		num++;
	if(map2[i][j-1]==MINE&&(i>=0&&i<=15)&&((j-1)>=0&&(j-1)<=15))
		num++;
	if(map2[i][j+1]==MINE&&(i>=0&&i<=15)&&((j+1)>=0&&(j+1)<=15))
		num++;
	if(map2[i+1][j-1]==MINE&&((i+1)>=0&&(i+1)<=15)&&((j-1)>=0&&(j-1)<=15))
		num++;
	if(map2[i+1][j]==MINE&&((i+1)>=0&&(i+1)<=15)&&(j>=0&&j<=15))
		num++;
	if(map2[i+1][j+1]==MINE&&((i+1)>=0&&(i+1)<=15)&&((j+1)>=0&&(j+1)<=15))
		num++;
	
	/*�����������λ���Ƿ�ƥ��*/
	if(map2[i-1][j-1]==MINE&&_map2[i-1][j-1]==4&&((i-1)>=0&&(i-1)<=15)&&((j-1)>=0&&(j-1)<=15))
		all++;		
	if(map2[i-1][j]==MINE&&_map2[i-1][j]==4&&((i-1)>=0&&(i-1)<=15)&&(j>=0&&j<=15))
		all++;					
	if(map2[i-1][j+1]==MINE&&_map2[i-1][j+1]==4&&((i-1)>=0&&(i-1)<=15)&&((j+1)>=0&&(j+1)<=15))
		all++;			
	if(map2[i][j-1]==MINE&&_map2[i][j-1]==4&&(i>=0&&i<=15)&&((j-1)>=0&&(j-1)<=15))
		all++;					
	if(map2[i][j+1]==MINE&&_map2[i][j+1]==4&&(i>=0&&i<=15)&&((j+1)>=0&&(j+1)<=15))
		all++;				
	if(map2[i+1][j-1]==MINE&&_map2[i+1][j-1]==4&&((i+1)>=0&&(i+1)<=15)&&((j-1)>=0&&(j-1)<=15))
		all++;				
	if(map2[i+1][j]==MINE&&_map2[i+1][j]==4&&((i+1)>=0&&(i+1)<=15)&&(j>=0&&j<=15))
		all++;				
	if(map2[i+1][j+1]==MINE&&_map2[i+1][j+1]==4&&((i+1)>=0&&(i+1)<=15)&&((j+1)>=0&&(j+1)<=15))
		all++;	
	/*ƥ��*/
	if(all==num)
	{
		printf("\a");
		if(map2[i-1][j-1]!=MINE&&((i-1)>=0&&(i-1)<=15)&&((j-1)>=0&&(j-1)<=15))
			judge16(i-1,j-1);
		if(map2[i-1][j]!=MINE&&((i-1)>=0&&(i-1)<=15)&&(j>=0&&j<=15))
			judge16(i-1,j);	
		if(map2[i-1][j+1]!=MINE&&((i-1)>=0&&(i-1)<=15)&&((j+1)>=0&&(j+1)<=15))
			judge16(i-1,j+1);	
		if(map2[i][j-1]!=MINE&&(i>=0&&i<=15)&&((j-1)>=0&&(j-1)<=15))
			judge16(i,j-1);	
		if(map2[i][j+1]!=MINE&&(i>=0&&i<=15)&&((j+1)>=0&&(j+1)<=15))
			judge16(i,j+1);		
		if(map2[i+1][j-1]!=MINE&&((i+1)>=0&&(i+1)<=15)&&((j-1)>=0&&(j-1)<=15))
			judge16(i+1,j-1);	
		if(map2[i+1][j]!=MINE&&((i+1)>=0&&(i+1)<=15)&&(j>=0&&j<=15))
			judge16(i+1,j);	
		if(map2[i+1][j+1]!=MINE&&((i+1)>=0&&(i+1)<=15)&&((j+1)>=0&&(j+1)<=15))
			judge16(i+1,j+1);	
	}
	/*��ƥ��*/
	else 
	{
		PlaySound("\\ɨ��\\��Ч\\Lose.wav",NULL,SND_FILENAME|SND_ASYNC);
		for(int e=0;e<16;e++)/*̯�Ʋ��µ���*/
			for(int f=0;f<16;f++)
				if(map2[e][f]==1)
					mine(210+20*f+10,130+20*e);
		HWND wnd=GetHWnd();/*��Ϸ�����Ի���*/
		if (MessageBox(wnd,"ɨ��ʧ��!\n�Ƿ�����?","ѯ��",MB_YESNO|MB_ICONQUESTION)==IDYES)
			{outtextxy(410+36,48,"16  X  16");cover16();extend();}
		else {closegraph();exit(0);}
	}
}
/***************************************************************************************************************************************/
void sound9(int i,int j)/*9X9��Ч*/
{
	if(map1[i][j]==MINE&&_map1[i][j]!=MARK)/*�����������δ���*/
	{
		PlaySound("\\ɨ��\\��Ч\\Lose.wav",NULL,SND_FILENAME|SND_ASYNC);/*��ը��Ч*/
		return;
	}
	if(_map1[i][j]==UNHIT||_map1[i][j]==UNDETERMINE)/*�����δ�����ʺ�*/
	{
		printf("\a");/*�����Ч*/
		return;
	}
}
/***************************************************************************************************************************************/
void sound16(int i,int j)/*16X16��Ч*/
{
	if(map2[i][j]==MINE&&_map2[i][j]!=MARK)
	{
		PlaySound("\\ɨ��\\��Ч\\Lose.wav",NULL,SND_FILENAME|SND_ASYNC);
		return;
	}
	if(_map2[i][j]==UNHIT||_map2[i][j]==UNDETERMINE)
	{
		printf("\a");
		return;
	}
}
/***************************************************************************************************************************************/

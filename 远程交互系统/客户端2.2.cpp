#include<WinSock2.h>     // winsock头文件
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include <winuser.h>
#include <time.h>
#include<Mmsystem.h>

#pragma comment(lib, "ws2_32.lib")    //连接库文件
#pragma comment(lib,"winmm.lib")

int OREO= 0;

//个人信息 
struct Person    
{
	char Name[20];
	char Sex[10];
	char Height[10];
	char Weihet[10];
	char Age[10];
	char address[100];
	
}person;

// 设置控制台光标位置
void SetXY(int x, int y)
{
	
	COORD POS;
	HANDLE obj;

	POS.X = x;
	POS.Y = y;
	obj = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(obj,POS);

}

// 获得控制台光标位置
COORD GetXY()
{
	
	HANDLE obj;
	CONSOLE_SCREEN_BUFFER_INFO buf;
	COORD res;

	obj = GetStdHandle(STD_OUTPUT_HANDLE);

	GetConsoleScreenBufferInfo(obj,&buf);
	res = buf.dwCursorPosition;

	return res;
	
}

//从指定位置开始，将大量字符复制到控制台屏幕缓冲区的连续单元格
void CopyWrite(const char * str,int x,int y)
{
	
	HANDLE obj=GetStdHandle(STD_OUTPUT_HANDLE);
	DWORD nLength=strlen(str);
	
	COORD pos;
	pos.X=x;
	pos.Y=y; 
	
	DWORD StrWrite;
	
	WriteConsoleOutputCharacter(obj,str,nLength,pos,&StrWrite);
	
}

//缓冲区中移动数据块
void ScrollText(int left,int top,int right,int bottom,int x,int y)
{
	
	HANDLE obj=GetStdHandle(STD_OUTPUT_HANDLE);
	SMALL_RECT old_pos;
	old_pos.Left=left;
	old_pos.Top=top;
	old_pos.Right=right;
	old_pos.Bottom=bottom;
	COORD new_pos;
	new_pos.X=x;
	new_pos.Y=y;
	CHAR_INFO QAQ;
	QAQ.Char.AsciiChar=(char)'\0';
//	QAQ.Char.UnicodeChar=' ';
	QAQ.Attributes=0;

	ScrollConsoleScreenBuffer(obj,&old_pos,NULL,new_pos,&QAQ);
	
}

//时间的结构体
typedef struct tm timeinfo;

void printTime()
{
	time_t rawtime; //时间类型
	timeinfo *timeinfos; //时间结构体 指针变量
	time(&rawtime);  //获取时间的秒数，从1970年1月1日开始，存入rawtime
	timeinfos = localtime(&rawtime);  //将秒数转为当地时间
	
//	printf("当前ASCII时间是: %s\n", asctime(timeinfos)); //转为ascii格式输出

	for(int i=1;i<3;i++)
	{
		CopyWrite("              ",101,i); 
	}
	
/*	printf("%d年%d月%d日",
			timeinfos->tm_year+1900,   //年是从1900开始的，要加1900
			timeinfos->tm_mon+1,       //月是从0开始的，要加1
			timeinfos->tm_mday);
	SetXY(102,2);
	printf("%d时%d分",
			timeinfos->tm_hour,
			timeinfos->tm_min);  */
			
	char nian[10];
	char yue[10];
	char ri[10];
	char miao[10];
	char fen[10];
	char shi[10];
	
	itoa(timeinfos->tm_year+1900,nian,10);
	itoa(timeinfos->tm_mon+1,yue,10);
	itoa(timeinfos->tm_mday,ri,10);
	itoa(timeinfos->tm_hour,shi,10);
	itoa(timeinfos->tm_min,fen,10);
	itoa(timeinfos->tm_sec,miao,10);
	
	CopyWrite(nian,102,1); 
	CopyWrite("年",106,1); 
	CopyWrite(yue,108,1); 
	CopyWrite("月",110,1); 
	CopyWrite(ri,112,1);
	CopyWrite("日",114,1); 
	CopyWrite(shi,102,2); 
	CopyWrite("时",104,2); 
	CopyWrite(fen,106,2); 
	CopyWrite("分",108,2);  
	CopyWrite(miao,110,2); 
	CopyWrite("秒",112,2); 
			 		
}

//  比较字符串是否相等
int judge(char str1[5],char str2[5])      
{
	int re=strcmp(str1,str2);
	if(re==0)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

// 歌曲清单 
void Music_Menu()
{
	for(int i=5;i<21;i++)
	{
		SetXY(102,i);
		puts("                ");
	}
	SetXY(102,5);
	puts("1.dge boy");
	SetXY(102,6);
	puts("2.Sustain");
	SetXY(102,7);
	puts("3.Longing");
	SetXY(102,8);
	puts("4.Shooting Star");
	SetXY(102,9);
	puts("5.星茶会");
	SetXY(102,10);
	puts("6.Aphasia");
	SetXY(102,11);
	puts("7.Pendant");
	SetXY(102,12);
	puts("8.Letter");
	SetXY(102,13);
	puts("9.夜の向日葵");
	SetXY(102,14);
	puts("10.满夏与距离");
	
}

// 播放功能目录 
void Music_Function()
{
	for(int i=5;i<21;i++)
	{
		SetXY(102,i);
		puts("                ");
	}
	SetXY(102,5);
	puts("1.Play_sound");
	SetXY(102,6);
	puts("2.Stop");
	SetXY(102,7);
	puts("3.Replay");
	SetXY(102,8);
	puts("4.Loop");
	SetXY(102,9);
	puts("4.退出");

}

//存入信息
void information(Person *person1)   
{
	for(int i=5;i<21;i++)
	{
		SetXY(102,i);
		puts("                ");
	}
	
	SetXY(102,5);
	printf("备注名：");
	SetXY(2,22);
	scanf("%s",person1->Name);
	SetXY(45,1);
	puts("                ");
	SetXY(45,1);
	puts(person1->Name);
	SetXY(2,22);
	puts("          ");
	SetXY(102,6);
	printf("%s",person1->Name);
	
	SetXY(102,7);
	printf("性别：");
	SetXY(2,22);
	scanf("%s",person1->Sex);
	SetXY(2,22);
	puts("          ");
	SetXY(102,8);
	printf("%s",person1->Sex);
	
	SetXY(102,9);
	printf("身高（cm）：");
	SetXY(2,22);
	scanf("%s",person1->Height);
	SetXY(2,22);
	puts("          ");
	SetXY(102,10);
	printf("%s",person1->Height);
	
	SetXY(102,11);
	printf("体重（kg）：");
	SetXY(2,22);
	scanf("%s",person1->Weihet);
	SetXY(2,22);
	puts("          ");
	SetXY(102,12);
	printf("%s",person1->Weihet);
	
	SetXY(102,13);
	printf("住址：");
	SetXY(2,22);
	scanf("%s",person1->address);
	SetXY(2,22);
	puts("          ");
	SetXY(102,14);
	printf("%s",person1->address);
	
	SetXY(102,15);
	printf("年龄：");
	SetXY(2,22);
	scanf("%s",person1->Age);
	SetXY(2,22);
	puts("          ");
	SetXY(102,16);
	printf("%s",person1->Age);
	
		FILE *FBI;
	FBI=fopen("C:\\远程交互系统\\客户端register.txt","w"); 
	fprintf(FBI,person1->Name);
	fprintf(FBI,"\n");
	fprintf(FBI,person1->Sex);
	fprintf(FBI,"\n");
	fprintf(FBI,person1->Age);
	fprintf(FBI,"\n");
	fprintf(FBI,person1->Height);
	fprintf(FBI,"\n");
	fprintf(FBI,person1->Weihet);
	fprintf(FBI,"\n");
	fprintf(FBI,person1->address);
	fprintf(FBI,"\n");
	fclose(FBI);
	
	SetXY(102,17);
	printf("登记完成");
	SetXY(2,22);
	system("pause");
	SetXY(2,22);
	puts("                          ");	
	OREO=1;
}

//显示信息 
void coutinformation(Person *person1)  
{
	for(int i=5;i<21;i++)
	{
		SetXY(102,i);
		puts("                ");
	}
	if(OREO==0)
	{
		FILE *FBI;
		FBI=fopen("C:\\远程交互系统\\客户端register.txt","r"); 
		char ch[6][20]={0};
		for(int i=0;i<6;i++)
		{
			fscanf(FBI,"%s",ch[i]);
		}
		if(strcmp(ch[0],"无联系人信息"))
		{
			strcpy(person1->Name,ch[0]);
			strcpy(person1->Sex,ch[1]);
			strcpy(person1->Age,ch[2]);
			strcpy(person1->Height,ch[3]);
			strcpy(person1->Weihet,ch[4]);
			strcpy(person1->address,ch[5]);
			
			SetXY(102,5);
		printf("备注名：");
		SetXY(102,6);
		printf("%s",person1->Name);
	
		SetXY(102,7);
		printf("性别：");
		SetXY(102,8);
		printf("%s",person1->Sex);
	
		SetXY(102,9);
		printf("身高（cm）：");
		SetXY(102,10);
		printf("%s",person1->Height);
	
		SetXY(102,11);
		printf("体重（kg）：");
		SetXY(102,12);
		printf("%s",person1->Weihet);
	
		SetXY(102,13);
		printf("住址：");
		SetXY(102,14);
		printf("%s",person1->address);
	
		SetXY(102,15);
		printf("年龄：");
		SetXY(102,16);
		printf("%s",person1->Age);
				
		}
		else
		{
			SetXY(102,5);
			puts(ch[0]);
		}
    	fclose(FBI);
		SetXY(2,22);
		system("pause");
	}
	else
	{
		SetXY(102,5);
		printf("备注名：");
		SetXY(102,6);
		printf("%s",person1->Name);
	
		SetXY(102,7);
		printf("性别：");
		SetXY(102,8);
		printf("%s",person1->Sex);
	
		SetXY(102,9);
		printf("身高（cm）：");
		SetXY(102,10);
		printf("%s",person1->Height);
	
		SetXY(102,11);
		printf("体重（kg）：");
		SetXY(102,12);
		printf("%s",person1->Weihet);
	
		SetXY(102,13);
		printf("住址：");
		SetXY(102,14);
		printf("%s",person1->address);
	
		SetXY(102,15);
		printf("年龄：");
		SetXY(102,16);
		printf("%s",person1->Age);
		
		SetXY(2,22);
		system("pause");
	}
	SetXY(2,22);
}

//修改信息
void cginformation(Person *person1)   
{
	
	for(int i=5;i<21;i++)
	{
		SetXY(102,i);
		puts("                ");
	}
	
	FILE *FBI;
    FBI=fopen("C:\\远程交互系统\\客户端register.txt","r");
    char ch1[20]={0};
    fscanf(FBI,"%s",ch1);
    fclose(FBI);
    
	if(OREO==1||strcmp(ch1,"无联系人信息"))
	{
		FILE *FBI;
    	FBI=fopen("C:\\远程交互系统\\客户端register.txt","r");
		char ch2[6][20]={0};
		for(int i=0;i<6;i++)
		{
			fscanf(FBI,"%s",ch2[i]);
		}
		strcpy(person1->Name,ch2[0]);
		strcpy(person1->Sex,ch2[1]);
		strcpy(person1->Age,ch2[2]);
		strcpy(person1->Height,ch2[3]);
		strcpy(person1->Weihet,ch2[4]);
		strcpy(person1->address,ch2[5]);
		fclose(FBI);
		
		char temp[20];
		char name[20] = {"备注名"};
		char sex[20] = {"性别"};
		char height[20] = {"身高"}; 
		char weight[20] = {"体重"};
		char address[20] = {"住址"};
		char age[20] = {"年龄"}; 
		while(true)
		{
			SetXY(102,5);
			printf("输入要修改的信息");
			for(int i=6;i<21;i++)
			{
				SetXY(102,i);
				puts("                ");
			}
			SetXY(2,22);
			scanf("%s",temp);
			if(!strcmp(temp,name))
			{
				SetXY(102,6);
				printf("修改备注名：");
				SetXY(2,22);
				puts("                    ");
				SetXY(2,22);
				scanf("%s",person1->Name);
				SetXY(45,1);
				puts("                ");
				SetXY(45,1);
				puts(person1->Name);
				SetXY(2,22);
				puts("                    ");
				SetXY(102,7);
				printf("%s",person1->Name);	
				SetXY(102,8); 
				printf("修改完成"); 
			}
			else if(!strcmp(temp,sex))
			{
				SetXY(102,6);
				printf("修改性别：");
				SetXY(2,22);
				puts("                    ");
				SetXY(2,22);
				scanf("%s",person1->Sex);
				SetXY(2,22);
				puts("                    ");
				SetXY(102,7);
				printf("%s",person1->Sex);
				SetXY(102,8); 
				printf("修改完成"); 
			}
			else if(!strcmp(temp,height))
			{
				SetXY(102,6);
				printf("修改身高：");
				SetXY(2,22);
				puts("                    ");
				SetXY(2,22);
				scanf("%s",person1->Height);
				SetXY(2,22);
				puts("                    ");
				SetXY(102,7);
				printf("%s",person1->Height);
				SetXY(102,8); 
				printf("修改完成"); 
			}
			else if(!strcmp(temp,weight))
			{
				SetXY(102,6);
				printf("修改体重：");
				SetXY(2,22);
				puts("                    ");
				SetXY(2,22);
				scanf("%s",person1->Weihet);
				SetXY(2,22);
				puts("                    ");
				SetXY(102,7);
				printf("%s",person1->Weihet);
				SetXY(102,8); 
				printf("修改完成"); 
			}
			else if(!strcmp(temp,address))
			{
				SetXY(102,6);
				printf("修改住址：");
				SetXY(2,22);
				puts("                    ");
				SetXY(2,22);
				scanf("%s",person1->address);
				SetXY(2,22);
				puts("                    ");
				SetXY(102,7);
				printf("%s",person1->address);
				SetXY(102,8); 
				printf("修改完成"); 
			}
			else if(!strcmp(temp,age))
			{
				SetXY(102,6);
				printf("修改年龄：");
				SetXY(2,22);
				puts("                    ");
				SetXY(2,22);
				scanf("%s",person1->Age);
				SetXY(2,22);
				puts("                    ");
				SetXY(102,7);
				printf("%s",person1->Age);
				SetXY(102,8); 
				printf("修改完成"); 
			}
			else if(!strcmp(temp,"退出"))
			{
				SetXY(2,22);
				system("pause");
				SetXY(2,22);
				puts("                          ");
				SetXY(102,6);
				printf("已退出修改");	
				return; 
			}
			else
			{
				SetXY(102,6);
				printf("错误");
			}
			SetXY(2,22);
			system("pause");
			SetXY(2,22);
			puts("                          ");	
			
			FILE *FBI;
			FBI=fopen("C:\\远程交互系统\\客户端register.txt","w"); 
			fprintf(FBI,person1->Name);
			fprintf(FBI,"\n");
			fprintf(FBI,person1->Sex);
			fprintf(FBI,"\n");
			fprintf(FBI,person1->Age);
			fprintf(FBI,"\n");
			fprintf(FBI,person1->Height);
			fprintf(FBI,"\n");
			fprintf(FBI,person1->Weihet);
			fprintf(FBI,"\n");
			fprintf(FBI,person1->address);
			fprintf(FBI,"\n");
			fclose(FBI);
			
		}
	}
	else
	{
		SetXY(102,5);
		puts("无联系人信息");
		SetXY(2,22);
		system("pause");
	}
	
}

// 菜单 
void menu()  
{
	for(int i=5;i<21;i++)
	{
		SetXY(102,i);
		puts("                ");
	}
	SetXY(102,5);
	puts("0.退出"); 
	SetXY(102,6) ;
	puts("1.登记"); 
	SetXY(102,7) ;
	puts("2.查看"); 
	SetXY(102,8) ;
	puts("3.修改"); 
	SetXY(102,9) ;
	puts("4.删除"); 
}

//接收信息 
void* myfunc1(void* args)
{
	SOCKET clientsocket = *(SOCKET*)args;
	int P_name=0;
	
	//创建记录聊天信息文件 
	FILE *Dialog;
	
here1:	

	char tail[5];
	recv(clientsocket,tail,5,0);   // 接收客户端发来的尾部信息 
	char receive[1024]={0};
		
	if(judge(tail,(char*)".jpg")||judge(tail,(char*)".exe")||judge(tail,(char*)".zip")||judge(tail,(char*)".rar")||judge(tail,(char*)".png")||judge(tail,(char*)".txt")||judge(tail,(char*)".doc")||judge(tail,(char*)".mp3")||judge(tail,(char*)".mp4")||judge(tail,(char*)".abr")||judge(tail,(char*)".pdf")) 
	{
		FILE * receive_file;
		int ret;
		int fsize;
		int size=0;
		char str1[99]="C:\\远程交互系统\\客户端接收文件夹\\" ;
		char str2[5];
		itoa(P_name,str2,10);
	
		FILE *fp1;
		FILE *fp2;
		char mem[5];
		int c;
		fp1=fopen("C:\\远程交互系统\\客户端接收文件夹\\计数器.txt","r");
	
		fgets(mem,5,fp1);
		c=atoi(mem);
		
		if(P_name>c)
		{
			fp2=fopen("C:\\远程交互系统\\客户端接收文件夹\\计数器.txt","w");
			fputs(str2,fp2);
			fclose(fp2);
		}
		else
		{
			P_name=c;
			itoa(P_name,str2,10);
		}
		
		fclose(fp1);
		strcat(str1,str2);
		strcat(str1,tail);
		receive_file=fopen(str1,"wb");
	
		int QAQ=recv(clientsocket,(char*)&fsize,sizeof(fsize),0);
		
		if(QAQ<=0)
		{
			goto here3;
		}
		
		while(size!=fsize)
		{
			ret=recv(clientsocket,receive,1024,0);
			size+=ret;
			fwrite(receive,1,ret,receive_file);
		}
		
		fclose(receive_file);
		P_name++;
		
		ScrollText(101,24,117,27,101,25);
		CopyWrite("收到传来的文件",102,24); 
		
	}
	else
	{
		int QAQ=recv(clientsocket, receive,1024, 0);
		if(QAQ<=0)
		{
			goto here3;
		}
		
		ScrollText(1,4,99,20,1,3);
		CopyWrite(receive,2,20); 
		
		//打开并存入聊天信息 
		Dialog=fopen("C:\\远程交互系统\\客户端dialog.txt","a+");
		fprintf(Dialog,"对方：");
		fprintf(Dialog,receive);
		fprintf(Dialog,"\n");
		//关闭文件 
		fclose(Dialog);	
		
	}
	goto here1;	
	
here3:
	system("cls");
	printf("客户端断开连接！！！"); 
	return NULL;
}

void Command_Menu()
{
	for(int i=5;i<21;i++)
	{
		SetXY(102,i);
		puts("                ");
	}
	SetXY(102,6);
	puts("/D_clear");
	SetXY(102,7);
	puts("/register");
	SetXY(102,8);
	puts("/Music");
	
}

//发送信息 
void* myfunc2(void* args)
{
	SOCKET clientsocket = *(SOCKET*)args;
	
	//创建记录聊天信息文件 
	FILE *Dialog;
	
//	ScrollText(101,3,117,19,101,4);
	SetXY(102,23);
	printf("成功连接!");
	SetXY(2,22);
	
	//  歌曲路径 
	int Music_num;
	const char* Music_List[15];
	Music_List[1]="C:\\远程交互系统\\Music\\June,夏小舟 - dge boy.wav";
	Music_List[2]="C:\\远程交互系统\\Music\\比特丧 - Sustain.wav";
	Music_List[3]="C:\\远程交互系统\\Music\\GIN - Longing.wav";
	Music_List[4]="C:\\远程交互系统\\Music\\Little End - Shooting Star.wav";
	Music_List[5]="C:\\远程交互系统\\Music\\灰澈 - 星茶会.wav";
	Music_List[6]="C:\\远程交互系统\\Music\\闫东炜 - Aphasia.wav";
	Music_List[7]="C:\\远程交互系统\\Music\\Arealy仁辰,南有乔木 - Pendant.wav";
	Music_List[8]="C:\\远程交互系统\\Music\\iris - Letter.wav";
	Music_List[9]="C:\\远程交互系统\\Music\\松本文紀 - 夜の向日葵.wav";
	Music_List[10]="C:\\远程交互系统\\Music\\闫东炜 - 满夏与距离.wav";
	
here2:	

	char news[1000]={0};       // 内容或者标题 
	char message[1024];
	
	SetXY(2,22);
	gets(news);
	SetXY(2,22);
		
	if(!strcmp(news,"/help"))
	{
		Command_Menu();
		SetXY(2,22);
		system("pause");
		SetXY(2,22);
		puts("                          ");	
		for(int i=5;i<21;i++)
		{
			SetXY(102,i);
			puts("                ");
		}
		goto here2;
		
	}	
	else if(!strcmp(news,"/register"))
	{
		puts("                          ");
		char choice;
		while(true)
		{
			menu(); 
			SetXY(2,22);
			scanf("%c",&choice);
			SetXY(2,22);
			puts("                     ");
			switch(choice)
			{
				case '1':
					information(&person);
					break;
				case '2':
					coutinformation(&person);
					break;
				case '3':
					cginformation(&person);
					break;
				case '4':
				{
					OREO = 0;
					
					FILE *FBI;
					FBI=fopen("C:\\远程交互系统\\客户端register.txt","w"); 
					fprintf(FBI,"无联系人信息"); 
					fclose(FBI); 
					
					for(int i=5;i<21;i++)
					{
						SetXY(102,i);
						puts("                ");
					}
					SetXY(45,1);
					puts("                ");
					SetXY(45,1);
					puts("未录入");
					SetXY(102,5);
					printf("删除成功");
					SetXY(2,22);
					system("pause");
					SetXY(2,22);
					puts("                          ");	 
				
				}
					break;
				case '0':
				{
					for(int i=5;i<21;i++)
					{
						SetXY(102,i);
						puts("                ");
					}
					SetXY(102,5); 
					printf("已退出");
					SetXY(2,22);
					puts("                          ");
					SetXY(102,5);
					printf("欧尼酱，欧尼酱");
					SetXY(102,6);
					printf("能再按一次回车吗");
					goto here2;
				}
				default:
					break; 
			}
		}
	}
	else if(!strcmp(news,"/D_clear"))
	{
		Dialog=fopen("C:\\远程交互系统\\客户端dialog.txt","w+");
		fclose(Dialog);
		for(int i=5;i<21;i++)
		{
			SetXY(102,i);
			puts("                ");
		}
		SetXY(102,5);
		puts("已清除聊天记录");
		SetXY(2,22);	
		system("pause");
		for(int i=5;i<21;i++)
		{
			SetXY(102,i);
			puts("                ");
		}
		SetXY(2,22);
		puts("                          ");
		goto here2;
		
	}
	else if (!strcmp(news,"/Music"))
	{	
		
		SetXY(2,22);
		puts("                          ");	
		SetXY(2,22);
		while(true)
		{
			Music_Function();
			SetXY(2,22);
			char functions[10];
			scanf("%s",functions);
			SetXY(2,22);
			puts("                          ");	
			if(!strcmp(functions,"/help"))
			{
				Music_Function();
				SetXY(2,22);
				system("pause")	;
				for(int i=5;i<21;i++)
				{
					SetXY(102,i);
					puts("                ");
				}
				SetXY(2,22);
				puts("                          ");
				SetXY(2,22);
				
			}
			else if(!strcmp(functions,"Play_sound"))
			{
				
here4:;
				Music_Menu();
				SetXY(2,22);
				scanf("%d",&Music_num);
				if(Music_num<=0||Music_num>10)
				{
					for(int i=5;i<21;i++)
					{
						SetXY(102,i);
						puts("                ");
					}
					SetXY(102,5);
					puts("无此歌曲");
					SetXY(102,6);
					puts("请重新选择");
					SetXY(2,22);
					puts("                          ");
					SetXY(2,22);
					Sleep(3000);
					goto here4;	
				} 
				PlaySoundA(NULL,NULL,0);  //暂停 
				PlaySoundA(Music_List[Music_num], NULL, SND_FILENAME | SND_ASYNC);
				for(int i=5;i<21;i++)
				{
					SetXY(102,i);
					puts("                ");
				}
				SetXY(102,5);
				puts("播放成功");
				SetXY(2,22);
				puts("                          ");
				SetXY(2,22);
				 
			}
			else if(!strcmp(functions,"Stop"))
			{
				PlaySoundA(NULL,NULL,0);  //暂停
				for(int i=5;i<21;i++)
				{
					SetXY(102,i);
					puts("                ");
				}
				SetXY(102,5);
				puts("暂停成功");
				SetXY(2,22);
				puts("                          ");
				SetXY(2,22);
				
			}
			else if(!strcmp(functions,"Replay"))
			{
			    PlaySoundA(Music_List[Music_num],NULL,SND_FILENAME|SND_PURGE|SND_ASYNC); 
			    for(int i=5;i<21;i++)
				{
					SetXY(102,i);
					puts("                ");
				}
				SetXY(102,5);
				puts("重放成功");
				SetXY(2,22);
				puts("                          ");
				SetXY(2,22);
				
			}
			else if(!strcmp(functions,"Loop"))
			{	
				Music_Menu();
				SetXY(2,22);
				scanf("%d",&Music_num);			
				PlaySoundA(Music_List[Music_num],NULL,SND_FILENAME|SND_LOOP|SND_ASYNC); 
				for(int i=5;i<21;i++)
				{
					SetXY(102,i);
					puts("                ");
				}
				SetXY(102,5);
				puts("循环成功");
				SetXY(2,22);
				puts("                          ");
				SetXY(2,22);
				
			}
			else if(!strcmp(functions,"退出")) 
			{
				for(int i=5;i<21;i++)
				{
					SetXY(102,i);
					puts("                ");
				}
				SetXY(102,5); 
				printf("已退出");
				SetXY(2,22);
				puts("                          ");
				goto here2;
					
			}
			else
			{
				for(int i=5;i<21;i++)
				{
					SetXY(102,i);
					puts("                ");
				}
				SetXY(102,5);
				puts("无此功能"); 
				SetXY(2,22);
				system("pause")	;
				SetXY(2,22);
				puts("                          ");
				SetXY(2,22);
			}
		}	
	}
	
	int length_n=strlen(news);   //输入内容长度 
	if(length_n==0)		//禁止发送空内容 
		goto here2;
		
	int Length_0=strlen(news);
		
		ScrollText(1,4,99,20,1,3);
						
		CopyWrite(news,120-Length_0-20,20);
					
		// 万事皆虚 万事皆允 行于暗夜 侍奉光明 
		for(int i=22;i<29;i++)
		{
			SetXY(2,i);
			for(int i=0;i<Length_0;i++)
			{
				printf(" ");
			}
		}	
	
	char tail[5];
	for(int i=0;i<4;i++)
	{
		tail[i]=news[length_n-4+i];
	}
	
	send(clientsocket,tail,5,0);   //  将尾部发送给客户端 
	
	if(judge(tail,(char*)".jpg")||judge(tail,(char*)".exe")||judge(tail,(char*)".zip")||judge(tail,(char*)".rar")||judge(tail,(char*)".png")||judge(tail,(char*)".txt")||judge(tail,(char*)".doc")||judge(tail,(char*)".mp3")||judge(tail,(char*)".mp4")||judge(tail,(char*)".abr")||judge(tail,(char*)".pdf"))
	{
		FILE *send_file;
		int size=0;               
		int ret=0; 
		int fsize=0;
		send_file=fopen(news,"rb");
		fseek(send_file,0,SEEK_END);    // 定位到文件末尾
		fsize=ftell(send_file);         // 得到文件大小 
		fseek(send_file,0,SEEK_SET);    // 指针指回文件开头 
		send(clientsocket,(char*)&fsize,sizeof(fsize),0);
		while(size!=fsize)
		{
			ret=fread(message,1,1024,send_file);
			size+=ret;
			send(clientsocket,message,ret,0);
		}
		
		fclose(send_file);
		
		ScrollText(101,24,117,27,101,25);
		SetXY(102,24);
		printf("文件传输成功");
		SetXY(2,22);
		 
	}
	else
	{		
		send(clientsocket,news,(int)strlen(news),0);
		
		//打开并存入聊天信息 
		Dialog=fopen("C:\\远程交互系统\\客户端dialog.txt","a+");
		fprintf(Dialog,"我：");
		fprintf(Dialog,news);
		fprintf(Dialog,"\n");
		//关闭文件 
		fclose(Dialog);	
		
	}
	
	goto here2;
	return NULL;
}

void* myfunc3(void* args)
{
	while(1)
	{
		printTime();
		Sleep(1000);
	}
	return NULL;
}

//打表 
void DaBiao()
{
	SetXY(0,21);
	for(int i=1;i<118;i++)
	{
		printf("═");
	}
	
	SetXY(0,0);
	for(int i=1;i<119;i++)
	{
		printf("═");
	}
	
	SetXY(1,29);
	for(int i=1;i<118;i++)
	{
		printf("═");
	}
	
	SetXY(1,2);
	for(int i=1;i<100;i++)
	{
		printf("═");
	}
	
	SetXY(100,3);
	for(int i=100;i<118;i++)
	{
		printf("═");
	}
	
	for(int i=1;i<29;i++)
	{
		SetXY(100,i);
		printf("║");
	}
	
	for(int i=1;i<29;i++)
	{
		SetXY(118,i);
		printf("║");
	}
	
	for(int i=1;i<29;i++)
	{
		SetXY(0,i);
		printf("║");
	}
	
	SetXY(100,21);
	puts("╩") ;
	
	SetXY(118,21);
	puts("╣") ;
	
	SetXY(100,0);
	puts("╦") ;
	
	SetXY(118,0);
	puts("╗") ;
	
	SetXY(0,0);
	puts("╔") ;
	
	SetXY(0,21);
	puts("╠") ;
	
	SetXY(100,21);
	puts("╩") ;
	
	SetXY(0,29);
	puts("╚") ;
	
	SetXY(118,29);
	puts("╝") ;
	
	SetXY(100,21);
	puts("╬") ;	
	
	SetXY(100,29);
	puts("╩") ;

//	SetXY(45,1);
//	puts("未录入");
	
	SetXY(101,4);
	puts("     /*设置*/");
	
	SetXY(101,22);
	puts(" //**系统消息**//");
	SetXY(2,22);
	
}  

int main()
{
	
	// 锁定控制台大小 
	HWND hWnd = GetConsoleWindow(); //获得cmd窗口句柄
    RECT rc;
    GetWindowRect(hWnd, &rc); //获得cmd窗口对应矩形
 
    //改变cmd窗口风格
    SetWindowLongPtrA(hWnd, 
        GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
    //因为风格涉及到边框改变，必须调用SetWindowPos，否则无效果
    SetWindowPos(hWnd,
        NULL,
        rc.left,
        rc.top,
        rc.right - rc.left, rc.bottom - rc.top,
        SWP_NOZORDER | SWP_NOMOVE);
        
        
    //调用表格    
    DaBiao(); 
    
    SetXY(45,1);
    FILE *FBI;
    FBI=fopen("C:\\远程交互系统\\客户端register.txt","r");
    char ch[20]={0};
    fscanf(FBI,"%s",ch);
    if(!strcmp(ch,"无联系人信息"))
	{
		puts("未录入"); 
	} 
	else
	{
		puts(ch);
	}
    fclose(FBI);
    SetXY(2,22);
	    
	    
	// 初始化DLL
	WSADATA wsadata;

	WSAStartup(MAKEWORD(2, 2), &wsadata);

	//  创建套接字 
	SOCKET clientsocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	//  绑定套接字
	struct sockaddr_in socketaddr;
	ZeroMemory(&socketaddr, sizeof(socketaddr));
	socketaddr.sin_family = PF_INET;
	socketaddr.sin_addr.s_addr = inet_addr("101.34.79.94");
	socketaddr.sin_port = htons(1234);

	connect(clientsocket, (SOCKADDR*)&socketaddr, sizeof(socketaddr));
	
	
	// 多线程 并行 
	pthread_t th1;
	pthread_t th2;
	pthread_t th3;
	
	pthread_create(&th1, NULL, myfunc1, &clientsocket);
	pthread_create(&th2, NULL, myfunc2, &clientsocket);
	pthread_create(&th3, NULL, myfunc3,NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);

	// 关闭套接字
	closesocket(clientsocket);
	
	// 停止使用
	WSACleanup();
	getchar();
	getchar();
	
	return 0;

}

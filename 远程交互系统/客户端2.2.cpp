#include<WinSock2.h>     // winsockͷ�ļ�
#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<string.h>
#include<windows.h>
#include<conio.h>
#include <winuser.h>
#include <time.h>
#include<Mmsystem.h>

#pragma comment(lib, "ws2_32.lib")    //���ӿ��ļ�
#pragma comment(lib,"winmm.lib")

int OREO= 0;

//������Ϣ 
struct Person    
{
	char Name[20];
	char Sex[10];
	char Height[10];
	char Weihet[10];
	char Age[10];
	char address[100];
	
}person;

// ���ÿ���̨���λ��
void SetXY(int x, int y)
{
	
	COORD POS;
	HANDLE obj;

	POS.X = x;
	POS.Y = y;
	obj = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(obj,POS);

}

// ��ÿ���̨���λ��
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

//��ָ��λ�ÿ�ʼ���������ַ����Ƶ�����̨��Ļ��������������Ԫ��
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

//���������ƶ����ݿ�
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

//ʱ��Ľṹ��
typedef struct tm timeinfo;

void printTime()
{
	time_t rawtime; //ʱ������
	timeinfo *timeinfos; //ʱ��ṹ�� ָ�����
	time(&rawtime);  //��ȡʱ�����������1970��1��1�տ�ʼ������rawtime
	timeinfos = localtime(&rawtime);  //������תΪ����ʱ��
	
//	printf("��ǰASCIIʱ����: %s\n", asctime(timeinfos)); //תΪascii��ʽ���

	for(int i=1;i<3;i++)
	{
		CopyWrite("              ",101,i); 
	}
	
/*	printf("%d��%d��%d��",
			timeinfos->tm_year+1900,   //���Ǵ�1900��ʼ�ģ�Ҫ��1900
			timeinfos->tm_mon+1,       //���Ǵ�0��ʼ�ģ�Ҫ��1
			timeinfos->tm_mday);
	SetXY(102,2);
	printf("%dʱ%d��",
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
	CopyWrite("��",106,1); 
	CopyWrite(yue,108,1); 
	CopyWrite("��",110,1); 
	CopyWrite(ri,112,1);
	CopyWrite("��",114,1); 
	CopyWrite(shi,102,2); 
	CopyWrite("ʱ",104,2); 
	CopyWrite(fen,106,2); 
	CopyWrite("��",108,2);  
	CopyWrite(miao,110,2); 
	CopyWrite("��",112,2); 
			 		
}

//  �Ƚ��ַ����Ƿ����
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

// �����嵥 
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
	puts("5.�ǲ��");
	SetXY(102,10);
	puts("6.Aphasia");
	SetXY(102,11);
	puts("7.Pendant");
	SetXY(102,12);
	puts("8.Letter");
	SetXY(102,13);
	puts("9.ҹ�����տ�");
	SetXY(102,14);
	puts("10.���������");
	
}

// ���Ź���Ŀ¼ 
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
	puts("4.�˳�");

}

//������Ϣ
void information(Person *person1)   
{
	for(int i=5;i<21;i++)
	{
		SetXY(102,i);
		puts("                ");
	}
	
	SetXY(102,5);
	printf("��ע����");
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
	printf("�Ա�");
	SetXY(2,22);
	scanf("%s",person1->Sex);
	SetXY(2,22);
	puts("          ");
	SetXY(102,8);
	printf("%s",person1->Sex);
	
	SetXY(102,9);
	printf("��ߣ�cm����");
	SetXY(2,22);
	scanf("%s",person1->Height);
	SetXY(2,22);
	puts("          ");
	SetXY(102,10);
	printf("%s",person1->Height);
	
	SetXY(102,11);
	printf("���أ�kg����");
	SetXY(2,22);
	scanf("%s",person1->Weihet);
	SetXY(2,22);
	puts("          ");
	SetXY(102,12);
	printf("%s",person1->Weihet);
	
	SetXY(102,13);
	printf("סַ��");
	SetXY(2,22);
	scanf("%s",person1->address);
	SetXY(2,22);
	puts("          ");
	SetXY(102,14);
	printf("%s",person1->address);
	
	SetXY(102,15);
	printf("���䣺");
	SetXY(2,22);
	scanf("%s",person1->Age);
	SetXY(2,22);
	puts("          ");
	SetXY(102,16);
	printf("%s",person1->Age);
	
		FILE *FBI;
	FBI=fopen("C:\\Զ�̽���ϵͳ\\�ͻ���register.txt","w"); 
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
	printf("�Ǽ����");
	SetXY(2,22);
	system("pause");
	SetXY(2,22);
	puts("                          ");	
	OREO=1;
}

//��ʾ��Ϣ 
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
		FBI=fopen("C:\\Զ�̽���ϵͳ\\�ͻ���register.txt","r"); 
		char ch[6][20]={0};
		for(int i=0;i<6;i++)
		{
			fscanf(FBI,"%s",ch[i]);
		}
		if(strcmp(ch[0],"����ϵ����Ϣ"))
		{
			strcpy(person1->Name,ch[0]);
			strcpy(person1->Sex,ch[1]);
			strcpy(person1->Age,ch[2]);
			strcpy(person1->Height,ch[3]);
			strcpy(person1->Weihet,ch[4]);
			strcpy(person1->address,ch[5]);
			
			SetXY(102,5);
		printf("��ע����");
		SetXY(102,6);
		printf("%s",person1->Name);
	
		SetXY(102,7);
		printf("�Ա�");
		SetXY(102,8);
		printf("%s",person1->Sex);
	
		SetXY(102,9);
		printf("��ߣ�cm����");
		SetXY(102,10);
		printf("%s",person1->Height);
	
		SetXY(102,11);
		printf("���أ�kg����");
		SetXY(102,12);
		printf("%s",person1->Weihet);
	
		SetXY(102,13);
		printf("סַ��");
		SetXY(102,14);
		printf("%s",person1->address);
	
		SetXY(102,15);
		printf("���䣺");
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
		printf("��ע����");
		SetXY(102,6);
		printf("%s",person1->Name);
	
		SetXY(102,7);
		printf("�Ա�");
		SetXY(102,8);
		printf("%s",person1->Sex);
	
		SetXY(102,9);
		printf("��ߣ�cm����");
		SetXY(102,10);
		printf("%s",person1->Height);
	
		SetXY(102,11);
		printf("���أ�kg����");
		SetXY(102,12);
		printf("%s",person1->Weihet);
	
		SetXY(102,13);
		printf("סַ��");
		SetXY(102,14);
		printf("%s",person1->address);
	
		SetXY(102,15);
		printf("���䣺");
		SetXY(102,16);
		printf("%s",person1->Age);
		
		SetXY(2,22);
		system("pause");
	}
	SetXY(2,22);
}

//�޸���Ϣ
void cginformation(Person *person1)   
{
	
	for(int i=5;i<21;i++)
	{
		SetXY(102,i);
		puts("                ");
	}
	
	FILE *FBI;
    FBI=fopen("C:\\Զ�̽���ϵͳ\\�ͻ���register.txt","r");
    char ch1[20]={0};
    fscanf(FBI,"%s",ch1);
    fclose(FBI);
    
	if(OREO==1||strcmp(ch1,"����ϵ����Ϣ"))
	{
		FILE *FBI;
    	FBI=fopen("C:\\Զ�̽���ϵͳ\\�ͻ���register.txt","r");
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
		char name[20] = {"��ע��"};
		char sex[20] = {"�Ա�"};
		char height[20] = {"���"}; 
		char weight[20] = {"����"};
		char address[20] = {"סַ"};
		char age[20] = {"����"}; 
		while(true)
		{
			SetXY(102,5);
			printf("����Ҫ�޸ĵ���Ϣ");
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
				printf("�޸ı�ע����");
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
				printf("�޸����"); 
			}
			else if(!strcmp(temp,sex))
			{
				SetXY(102,6);
				printf("�޸��Ա�");
				SetXY(2,22);
				puts("                    ");
				SetXY(2,22);
				scanf("%s",person1->Sex);
				SetXY(2,22);
				puts("                    ");
				SetXY(102,7);
				printf("%s",person1->Sex);
				SetXY(102,8); 
				printf("�޸����"); 
			}
			else if(!strcmp(temp,height))
			{
				SetXY(102,6);
				printf("�޸���ߣ�");
				SetXY(2,22);
				puts("                    ");
				SetXY(2,22);
				scanf("%s",person1->Height);
				SetXY(2,22);
				puts("                    ");
				SetXY(102,7);
				printf("%s",person1->Height);
				SetXY(102,8); 
				printf("�޸����"); 
			}
			else if(!strcmp(temp,weight))
			{
				SetXY(102,6);
				printf("�޸����أ�");
				SetXY(2,22);
				puts("                    ");
				SetXY(2,22);
				scanf("%s",person1->Weihet);
				SetXY(2,22);
				puts("                    ");
				SetXY(102,7);
				printf("%s",person1->Weihet);
				SetXY(102,8); 
				printf("�޸����"); 
			}
			else if(!strcmp(temp,address))
			{
				SetXY(102,6);
				printf("�޸�סַ��");
				SetXY(2,22);
				puts("                    ");
				SetXY(2,22);
				scanf("%s",person1->address);
				SetXY(2,22);
				puts("                    ");
				SetXY(102,7);
				printf("%s",person1->address);
				SetXY(102,8); 
				printf("�޸����"); 
			}
			else if(!strcmp(temp,age))
			{
				SetXY(102,6);
				printf("�޸����䣺");
				SetXY(2,22);
				puts("                    ");
				SetXY(2,22);
				scanf("%s",person1->Age);
				SetXY(2,22);
				puts("                    ");
				SetXY(102,7);
				printf("%s",person1->Age);
				SetXY(102,8); 
				printf("�޸����"); 
			}
			else if(!strcmp(temp,"�˳�"))
			{
				SetXY(2,22);
				system("pause");
				SetXY(2,22);
				puts("                          ");
				SetXY(102,6);
				printf("���˳��޸�");	
				return; 
			}
			else
			{
				SetXY(102,6);
				printf("����");
			}
			SetXY(2,22);
			system("pause");
			SetXY(2,22);
			puts("                          ");	
			
			FILE *FBI;
			FBI=fopen("C:\\Զ�̽���ϵͳ\\�ͻ���register.txt","w"); 
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
		puts("����ϵ����Ϣ");
		SetXY(2,22);
		system("pause");
	}
	
}

// �˵� 
void menu()  
{
	for(int i=5;i<21;i++)
	{
		SetXY(102,i);
		puts("                ");
	}
	SetXY(102,5);
	puts("0.�˳�"); 
	SetXY(102,6) ;
	puts("1.�Ǽ�"); 
	SetXY(102,7) ;
	puts("2.�鿴"); 
	SetXY(102,8) ;
	puts("3.�޸�"); 
	SetXY(102,9) ;
	puts("4.ɾ��"); 
}

//������Ϣ 
void* myfunc1(void* args)
{
	SOCKET clientsocket = *(SOCKET*)args;
	int P_name=0;
	
	//������¼������Ϣ�ļ� 
	FILE *Dialog;
	
here1:	

	char tail[5];
	recv(clientsocket,tail,5,0);   // ���տͻ��˷�����β����Ϣ 
	char receive[1024]={0};
		
	if(judge(tail,(char*)".jpg")||judge(tail,(char*)".exe")||judge(tail,(char*)".zip")||judge(tail,(char*)".rar")||judge(tail,(char*)".png")||judge(tail,(char*)".txt")||judge(tail,(char*)".doc")||judge(tail,(char*)".mp3")||judge(tail,(char*)".mp4")||judge(tail,(char*)".abr")||judge(tail,(char*)".pdf")) 
	{
		FILE * receive_file;
		int ret;
		int fsize;
		int size=0;
		char str1[99]="C:\\Զ�̽���ϵͳ\\�ͻ��˽����ļ���\\" ;
		char str2[5];
		itoa(P_name,str2,10);
	
		FILE *fp1;
		FILE *fp2;
		char mem[5];
		int c;
		fp1=fopen("C:\\Զ�̽���ϵͳ\\�ͻ��˽����ļ���\\������.txt","r");
	
		fgets(mem,5,fp1);
		c=atoi(mem);
		
		if(P_name>c)
		{
			fp2=fopen("C:\\Զ�̽���ϵͳ\\�ͻ��˽����ļ���\\������.txt","w");
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
		CopyWrite("�յ��������ļ�",102,24); 
		
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
		
		//�򿪲�����������Ϣ 
		Dialog=fopen("C:\\Զ�̽���ϵͳ\\�ͻ���dialog.txt","a+");
		fprintf(Dialog,"�Է���");
		fprintf(Dialog,receive);
		fprintf(Dialog,"\n");
		//�ر��ļ� 
		fclose(Dialog);	
		
	}
	goto here1;	
	
here3:
	system("cls");
	printf("�ͻ��˶Ͽ����ӣ�����"); 
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

//������Ϣ 
void* myfunc2(void* args)
{
	SOCKET clientsocket = *(SOCKET*)args;
	
	//������¼������Ϣ�ļ� 
	FILE *Dialog;
	
//	ScrollText(101,3,117,19,101,4);
	SetXY(102,23);
	printf("�ɹ�����!");
	SetXY(2,22);
	
	//  ����·�� 
	int Music_num;
	const char* Music_List[15];
	Music_List[1]="C:\\Զ�̽���ϵͳ\\Music\\June,��С�� - dge boy.wav";
	Music_List[2]="C:\\Զ�̽���ϵͳ\\Music\\����ɥ - Sustain.wav";
	Music_List[3]="C:\\Զ�̽���ϵͳ\\Music\\GIN - Longing.wav";
	Music_List[4]="C:\\Զ�̽���ϵͳ\\Music\\Little End - Shooting Star.wav";
	Music_List[5]="C:\\Զ�̽���ϵͳ\\Music\\�ҳ� - �ǲ��.wav";
	Music_List[6]="C:\\Զ�̽���ϵͳ\\Music\\�ƶ�� - Aphasia.wav";
	Music_List[7]="C:\\Զ�̽���ϵͳ\\Music\\Arealy�ʳ�,������ľ - Pendant.wav";
	Music_List[8]="C:\\Զ�̽���ϵͳ\\Music\\iris - Letter.wav";
	Music_List[9]="C:\\Զ�̽���ϵͳ\\Music\\�ɱ��ļo - ҹ�����տ�.wav";
	Music_List[10]="C:\\Զ�̽���ϵͳ\\Music\\�ƶ�� - ���������.wav";
	
here2:	

	char news[1000]={0};       // ���ݻ��߱��� 
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
					FBI=fopen("C:\\Զ�̽���ϵͳ\\�ͻ���register.txt","w"); 
					fprintf(FBI,"����ϵ����Ϣ"); 
					fclose(FBI); 
					
					for(int i=5;i<21;i++)
					{
						SetXY(102,i);
						puts("                ");
					}
					SetXY(45,1);
					puts("                ");
					SetXY(45,1);
					puts("δ¼��");
					SetXY(102,5);
					printf("ɾ���ɹ�");
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
					printf("���˳�");
					SetXY(2,22);
					puts("                          ");
					SetXY(102,5);
					printf("ŷ�ὴ��ŷ�ὴ");
					SetXY(102,6);
					printf("���ٰ�һ�λس���");
					goto here2;
				}
				default:
					break; 
			}
		}
	}
	else if(!strcmp(news,"/D_clear"))
	{
		Dialog=fopen("C:\\Զ�̽���ϵͳ\\�ͻ���dialog.txt","w+");
		fclose(Dialog);
		for(int i=5;i<21;i++)
		{
			SetXY(102,i);
			puts("                ");
		}
		SetXY(102,5);
		puts("����������¼");
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
					puts("�޴˸���");
					SetXY(102,6);
					puts("������ѡ��");
					SetXY(2,22);
					puts("                          ");
					SetXY(2,22);
					Sleep(3000);
					goto here4;	
				} 
				PlaySoundA(NULL,NULL,0);  //��ͣ 
				PlaySoundA(Music_List[Music_num], NULL, SND_FILENAME | SND_ASYNC);
				for(int i=5;i<21;i++)
				{
					SetXY(102,i);
					puts("                ");
				}
				SetXY(102,5);
				puts("���ųɹ�");
				SetXY(2,22);
				puts("                          ");
				SetXY(2,22);
				 
			}
			else if(!strcmp(functions,"Stop"))
			{
				PlaySoundA(NULL,NULL,0);  //��ͣ
				for(int i=5;i<21;i++)
				{
					SetXY(102,i);
					puts("                ");
				}
				SetXY(102,5);
				puts("��ͣ�ɹ�");
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
				puts("�طųɹ�");
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
				puts("ѭ���ɹ�");
				SetXY(2,22);
				puts("                          ");
				SetXY(2,22);
				
			}
			else if(!strcmp(functions,"�˳�")) 
			{
				for(int i=5;i<21;i++)
				{
					SetXY(102,i);
					puts("                ");
				}
				SetXY(102,5); 
				printf("���˳�");
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
				puts("�޴˹���"); 
				SetXY(2,22);
				system("pause")	;
				SetXY(2,22);
				puts("                          ");
				SetXY(2,22);
			}
		}	
	}
	
	int length_n=strlen(news);   //�������ݳ��� 
	if(length_n==0)		//��ֹ���Ϳ����� 
		goto here2;
		
	int Length_0=strlen(news);
		
		ScrollText(1,4,99,20,1,3);
						
		CopyWrite(news,120-Length_0-20,20);
					
		// ���½��� ���½��� ���ڰ�ҹ �̷���� 
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
	
	send(clientsocket,tail,5,0);   //  ��β�����͸��ͻ��� 
	
	if(judge(tail,(char*)".jpg")||judge(tail,(char*)".exe")||judge(tail,(char*)".zip")||judge(tail,(char*)".rar")||judge(tail,(char*)".png")||judge(tail,(char*)".txt")||judge(tail,(char*)".doc")||judge(tail,(char*)".mp3")||judge(tail,(char*)".mp4")||judge(tail,(char*)".abr")||judge(tail,(char*)".pdf"))
	{
		FILE *send_file;
		int size=0;               
		int ret=0; 
		int fsize=0;
		send_file=fopen(news,"rb");
		fseek(send_file,0,SEEK_END);    // ��λ���ļ�ĩβ
		fsize=ftell(send_file);         // �õ��ļ���С 
		fseek(send_file,0,SEEK_SET);    // ָ��ָ���ļ���ͷ 
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
		printf("�ļ�����ɹ�");
		SetXY(2,22);
		 
	}
	else
	{		
		send(clientsocket,news,(int)strlen(news),0);
		
		//�򿪲�����������Ϣ 
		Dialog=fopen("C:\\Զ�̽���ϵͳ\\�ͻ���dialog.txt","a+");
		fprintf(Dialog,"�ң�");
		fprintf(Dialog,news);
		fprintf(Dialog,"\n");
		//�ر��ļ� 
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

//��� 
void DaBiao()
{
	SetXY(0,21);
	for(int i=1;i<118;i++)
	{
		printf("�T");
	}
	
	SetXY(0,0);
	for(int i=1;i<119;i++)
	{
		printf("�T");
	}
	
	SetXY(1,29);
	for(int i=1;i<118;i++)
	{
		printf("�T");
	}
	
	SetXY(1,2);
	for(int i=1;i<100;i++)
	{
		printf("�T");
	}
	
	SetXY(100,3);
	for(int i=100;i<118;i++)
	{
		printf("�T");
	}
	
	for(int i=1;i<29;i++)
	{
		SetXY(100,i);
		printf("�U");
	}
	
	for(int i=1;i<29;i++)
	{
		SetXY(118,i);
		printf("�U");
	}
	
	for(int i=1;i<29;i++)
	{
		SetXY(0,i);
		printf("�U");
	}
	
	SetXY(100,21);
	puts("�m") ;
	
	SetXY(118,21);
	puts("�g") ;
	
	SetXY(100,0);
	puts("�j") ;
	
	SetXY(118,0);
	puts("�[") ;
	
	SetXY(0,0);
	puts("�X") ;
	
	SetXY(0,21);
	puts("�d") ;
	
	SetXY(100,21);
	puts("�m") ;
	
	SetXY(0,29);
	puts("�^") ;
	
	SetXY(118,29);
	puts("�a") ;
	
	SetXY(100,21);
	puts("�p") ;	
	
	SetXY(100,29);
	puts("�m") ;

//	SetXY(45,1);
//	puts("δ¼��");
	
	SetXY(101,4);
	puts("     /*����*/");
	
	SetXY(101,22);
	puts(" //**ϵͳ��Ϣ**//");
	SetXY(2,22);
	
}  

int main()
{
	
	// ��������̨��С 
	HWND hWnd = GetConsoleWindow(); //���cmd���ھ��
    RECT rc;
    GetWindowRect(hWnd, &rc); //���cmd���ڶ�Ӧ����
 
    //�ı�cmd���ڷ��
    SetWindowLongPtrA(hWnd, 
        GWL_STYLE, GetWindowLong(hWnd, GWL_STYLE) & ~WS_THICKFRAME & ~WS_MAXIMIZEBOX & ~WS_MINIMIZEBOX);
    //��Ϊ����漰���߿�ı䣬�������SetWindowPos��������Ч��
    SetWindowPos(hWnd,
        NULL,
        rc.left,
        rc.top,
        rc.right - rc.left, rc.bottom - rc.top,
        SWP_NOZORDER | SWP_NOMOVE);
        
        
    //���ñ��    
    DaBiao(); 
    
    SetXY(45,1);
    FILE *FBI;
    FBI=fopen("C:\\Զ�̽���ϵͳ\\�ͻ���register.txt","r");
    char ch[20]={0};
    fscanf(FBI,"%s",ch);
    if(!strcmp(ch,"����ϵ����Ϣ"))
	{
		puts("δ¼��"); 
	} 
	else
	{
		puts(ch);
	}
    fclose(FBI);
    SetXY(2,22);
	    
	    
	// ��ʼ��DLL
	WSADATA wsadata;

	WSAStartup(MAKEWORD(2, 2), &wsadata);

	//  �����׽��� 
	SOCKET clientsocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);
	
	//  ���׽���
	struct sockaddr_in socketaddr;
	ZeroMemory(&socketaddr, sizeof(socketaddr));
	socketaddr.sin_family = PF_INET;
	socketaddr.sin_addr.s_addr = inet_addr("101.34.79.94");
	socketaddr.sin_port = htons(1234);

	connect(clientsocket, (SOCKADDR*)&socketaddr, sizeof(socketaddr));
	
	
	// ���߳� ���� 
	pthread_t th1;
	pthread_t th2;
	pthread_t th3;
	
	pthread_create(&th1, NULL, myfunc1, &clientsocket);
	pthread_create(&th2, NULL, myfunc2, &clientsocket);
	pthread_create(&th3, NULL, myfunc3,NULL);

	pthread_join(th1, NULL);
	pthread_join(th2, NULL);
	pthread_join(th3, NULL);

	// �ر��׽���
	closesocket(clientsocket);
	
	// ֹͣʹ��
	WSACleanup();
	getchar();
	getchar();
	
	return 0;

}

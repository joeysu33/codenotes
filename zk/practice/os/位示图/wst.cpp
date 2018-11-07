#include <iostream.h>
#include <stdlib.h>
#include <fstream.h>
#include <string.h>
void main()
{
	int wst[10][16];
	char ch='\0';
	int i,j,find,flag,num,count,out_i,out_j;
	ifstream f1;
	ofstream f2;
	char fname[20];
	cout<<"请输入位视图文件的名称！\n";
	cin>>fname;
	f1.open(fname,ios::in|ios::nocreate);
    if(!f1)
	{
		cout<<"输入的位视图文件名错误！"<<endl;
		exit(1);
	} 
	for(i=0;i<10;i++)
	{
		for(j=0;j<16;j++)
		{
			f1.get(ch);
			if(ch=='1') wst[i][j]=1;
			else if(ch=='0') wst[i][j]=0;
			else if(ch=='\n')
			{
				f1.get(ch);
				if(ch=='1') wst[i][j]=1;
				else if(ch=='0') wst[i][j]=0;
			}
		}
	}
	for(i=0;i<10;i++)
	{
		for(j=0;j<16;j++)cout<<wst[i][j];
		cout<<endl;
	}
	f1.close();
	cout<<"输入申请空间的大小:";
	cin>>num;
	find=0;flag=0;count=0;
	for(i=0;i<10&&find==0;i++)
	{
		for(j=0;j<16&&find==0;j++)
		{
			if(wst[i][j]==0)
			{
				if(flag==0) 
				{
					flag=1;
					out_i=i;
					out_j=j;
					count++;
				}
				else count++; 
			}
			if(wst[i][j]==1) {flag=0;count=0;}
			if(count==num)  find=1;
		}
	}
	if(find==1)
	{
		cout<<"找到合适的空间!"<<endl;
		cout<<"该空间的起始地址为:"<<endl;
		cout<<"行号:"<<out_i<< endl;
		cout<<"列号:"<<out_j<<endl;
		cout<<"分配申请的空间后的位示图为:"<<endl;
		for(i=0;i<num;i++)
		{
			int bi=0,bj=0;
			bi=out_i+(out_j+i)/16;
			bj=(out_j+i)%16;
			wst[bi][bj]=1;
		}
		
		for(i=0;i<10;i++)
		{
			for(j=0;j<16;j++)
			{
				cout<<wst[i][j];
			}
			cout<<endl;
		}
		cout<<"输入存储文件的名称!"<<endl;
		cin>>fname;
		f2.open(fname,ios::out);
		if(!f2)
		{
			cout<<"输入的存储文件名错误！"<<endl;exit(1);
		}
		f2<<"找到合适的空间!"<<endl;
		f2<<"该空间的起始地址为:"<<endl;
		f2<<"行号:"<<out_i<< endl;
		f2<<"列号:"<<out_j<<endl;
		for(i=0;i<10;i++)
		{
			for(j=0;j<16;j++)
			{
				f2<<wst[i][j];
			}
			f2<<endl;
		} 
		cout<<"已将信息保存到指定文件!"<<endl;
		f2.close();
	}
	if(find==0) cout<<"未找到所需的空间!";
}


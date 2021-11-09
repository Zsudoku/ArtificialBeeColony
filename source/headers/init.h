/*
*11.3 �޸����ݣ�
	�����˶������к���
	��read()����������������
	��enSimpleCode()�����������˳�ʼ��������
*/

#include "../classes/Food.h"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <vector>
#include <sstream>
#include <algorithm>
#include <time.h>
#include <memory.h>
#include <string>
#include <random>
#include <functional>
#include <list>
using namespace std;
char judge_type(int p,int a);
char judge_type(int p);

//�����λ��Ϣ���ļ�
void getCargo_now(string File_name1,string File_name2){
    ofstream out1;
    ofstream out_sit;
    out1.open(File_name1);
    out_sit.open(File_name2);
    for(int i=0;i<CODELENGTH;i++){
        out1<<"{"<<cargo_now[i].x<<","<<cargo_now[i].y<<","<<cargo_now[i].z<<","<<cargo_now[i].s1<<","<<cargo_now[i].s2<<","<<cargo_now[i].num<<","<<"'a'"<<","<<cargo_now[i].model<<","<<cargo_now[i].time<<"}"<<",";
        out_sit<<cargo_now[i].x<<","<<cargo_now[i].y<<","<<cargo_now[i].z<<","<<judge_type(i)<<endl;
        if((i+1)%5==0){
            out1<<endl;
        }
    }
    out1.close();
    out_sit.close();
}

void getCargo(string file_name1,string file_name2){
    ofstream outf,outd;
    outf.open(file_name1);
    outd.open(file_name2);
    for(int i=0;i<n_total;i++){
        outf<<"{"<<cargo[i].x<<","<<cargo[i].y<<","<<cargo[i].z<<","<<cargo[i].s1<<","<<cargo[i].s2<<","<<cargo[i].num<<","<<"'a'"<<","<<cargo[i].model<<","<<cargo[i].time<<"}"<<",";
        outd<<cargo[i].x<<","<<cargo[i].y<<","<<cargo[i].z<<","<<judge_type(i,1)<<endl;
        if((i+1)%5==0){
            outf<<endl;
        }
    }
    outf.close();
    outd.close();
}

/*!
 * ��ʼ����λ
 * @param N ��λ����
 * @param r ����λ���ڵ��� pre~r
 * @param s �ͼ��λ���ڵ��� pre~s
 * @param h �ؿ��λ���ڵ��� pre~h
 * @param c �����λ���ڵ��� pre~c
 */
void startCargo(int N,int r,int s,int h,int c){//��λ����,��⡢�ͼ졢�ؿ⡢����
    for(int i=0;i<N;i++){
        if((cargo[i].y >= 1) && (r >= cargo[i].y)){ // �����л�λ���зֿ�
            cargo[i].s1 = 0;
            cargo[i].s2 = 0;
        }
        else if((cargo[i].y >= r) && (s >= cargo[i].y)){
            cargo[i].s1 = 0;
            cargo[i].s2 = 1;
        }
        else if((cargo[i].y >= s) && (h >= cargo[i].y)){
            cargo[i].s1 = 1;
            cargo[i].s2 = 0;
        }
        else if((cargo[i].y >= h) && (c >= cargo[i].y)){
            cargo[i].s1 = 1;
            cargo[i].s2 = 1;
        }
    }
}

//��ѡ��
void candidate(){
    int r=0,s=0,h=0,c=0;
    for(int i=0;i<n_total;i++){
        if(cargo[i].s1 == 0){
            if(cargo[i].s2 == 0){//00:���
                G_r[r++] = cargo[i];
            }
            else if(cargo[i].s2 == 1){//01���ͼ�
                G_s[s++] = cargo[i];
            }
        }
        else if(cargo[i].s1 == 1){
            if(cargo[i].s2 == 0){//10:���
                G_h[h++] = cargo[i];
            }
            else if(cargo[i].s2 == 1){//11���ͼ�
                G_c[c++] = cargo[i];
            }
        }
    }
}

//�����ѡ�����ļ�
void getCandidate(){
    ofstream out;
    out.open("output/candidate.txt");
    for(int i=0;i<3000;i++){
        out<<"{"<<G_r[i].x<<","<<G_r[i].y<<","<<G_r[i].z<<","<<G_r[i].s1<<","<<G_r[i].s2<<","<<G_r[i].num<<","<<"'a'"<<","<<G_r[i].model<<","<<G_r[i].time<<"}"<<",";
        if((i+1)%5==0){
            out<<endl;
        }
    }
    out<<endl;
    for(int i=0;i<3000;i++){
        out<<"{"<<G_s[i].x<<","<<G_s[i].y<<","<<G_s[i].z<<","<<G_s[i].s1<<","<<G_s[i].s2<<","<<G_s[i].num<<","<<"'a'"<<","<<G_s[i].model<<","<<G_s[i].time<<"}"<<",";
        if((i+1)%5==0){
            out<<endl;
        }
    }
    out<<endl;
    for(int i=0;i<3000;i++){
        out<<"{"<<G_h[i].x<<","<<G_h[i].y<<","<<G_h[i].z<<","<<G_h[i].s1<<","<<G_h[i].s2<<","<<G_h[i].num<<","<<"'a'"<<","<<G_h[i].model<<","<<G_h[i].time<<"}"<<",";
        if((i+1)%5==0){
            out<<endl;
        }
    }
    out<<endl;
    for(int i=0;i<3000;i++){
        out<<"{"<<G_c[i].x<<","<<G_c[i].y<<","<<G_c[i].z<<","<<G_c[i].s1<<","<<G_c[i].s2<<","<<G_c[i].num<<","<<"'a'"<<","<<G_c[i].model<<","<<G_c[i].time<<"}"<<",";
        if((i+1)%5==0){
            out<<endl;
        }
    }
}

// ���ݵ���ʱ�䣬�Ժ�ѡ���ڵ��ʲ���������
void selectCargo(int day){//����Ϊ����
    bool flag = true;
    int count = 0;//����
    int q = -1;//��������
    int cargo_now_i = 0;
    for(int i=0;i<R;i++){
        cargo_now[cargo_now_i++] = G_r[i];
    }

    while (flag){
        if(count == S){
            flag = false;
            continue;
        }
        else{
            q++;
            for(int i=0;i<3000 && count<S;i++){
                if(G_s[i].time == day + q){
                    count++;
                    cargo_now[cargo_now_i++] = G_s[i];
                }
            }
        }
    }
    for(int i=0;i<H;i++){
        cargo_now[cargo_now_i++] = G_h[i];
    }
    count = 0,q = -1,flag = true;;
    while (flag){
        if(count == C){
            flag = false;
            continue;
        }
        else{
            q++;
            for(int i=0;i<3000 && count<C;i++){
                if(G_c[i].time == day + q){
                    count++;
                    cargo_now[cargo_now_i++] = G_c[i];
                }
            }
        }
    }
}

//���»�λ��Ϣ
void updateCargo(){
    for(int i=0;i<CODELENGTH;i++){
        if((cargo_now[i].s1==0) && (cargo_now[i].s2 ==0)){//�����ͼ�
            cargo[cargo_now[i].num-1].s1 = 0;
            cargo[cargo_now[i].num-1].s2 = 1;
            cargo[cargo_now[i].num-1].time++;
        }
        else if((cargo_now[i].s1==0) && (cargo_now[i].s2 ==1)){//�ͼ��ؿ�
            cargo[cargo_now[i].num-1].s1 = 1;
            cargo[cargo_now[i].num-1].s2 = 0;
        }
        else if((cargo_now[i].s1==1) && (cargo_now[i].s2 ==0)){//�ؿ�����
            cargo[cargo_now[i].num-1].s1 = 1;
            cargo[cargo_now[i].num-1].s2 = 1;
            cargo[cargo_now[i].num-1].time++;
        }
        else if((cargo_now[i].s1==1) && (cargo_now[i].s2 ==1)){//��������
            cargo[cargo_now[i].num-1].s1 = 0;
            cargo[cargo_now[i].num-1].s2 = 0;
        }
    }
}

void cargoRule(string first,string second,string third,string fourth){
    int s11 = 0, s12 = 0,s21 = 0,s22 = 0,s31 = 0,s32 = 0,s41 = 0,s42 = 0;
    if(first == "R"){
        s11 = 0;
        s12 = 0;
    }
    else if(first == "S"){
        s21 = 0;
        s22 = 1;
    }
    else if(first == "H"){
        s31 = 1;
        s32 = 0;
    }
    else if(first == "C"){
        s41 = 1;
        s42 = 1;
    }
    if(second=="R"){
        s11 = 0;
        s12 = 0;
    }
    else if(second == "S"){
        s21 = 0;
        s22 = 1;
    }
    else if(second == "H"){
        s31 = 1;
        s32 = 0;
    }
    else if(second == "C"){
        s41 = 1;
        s42 = 1;
    }
    if(third=="R"){
        s11 = 0;
        s12 = 0;
    }
    else if(third == "S"){
        s21 = 0;
        s22 = 1;
    }
    else if(third == "H"){
        s31 = 1;
        s32 = 0;
    }
    else if(third == "C"){
        s41 = 1;
        s42 = 1;
    }
    if(fourth=="R"){
        s11 = 0;
        s12 = 0;
    }
    else if(fourth == "S"){
        s21 = 0;
        s22 = 1;
    }
    else if(fourth == "H"){
        s31 = 1;
        s32 = 0;
    }
    else if(fourth == "C"){
        s41 = 1;
        s42 = 1;
    }

    for(int i=0;i<8112;i++){
        if(cargo[i].z<=4){
            cargo[i].s1 = s11;
            cargo[i].s2 = s12;
        }
        else if(cargo[i].z<=8 && cargo[i].z>4){
            cargo[i].s1 = s21;
            cargo[i].s2 = s22;
        }
        else if(cargo[i].z<=12 && cargo[i].z>8){
            cargo[i].s1 = s31;
            cargo[i].s2 = s32;
        }
        else if(cargo[i].z<=16 && cargo[i].z>12){
            cargo[i].s1 = s41;
            cargo[i].s2 = s42;
        }
        else if(cargo[i].z == 17 || cargo[i].z == 21 || cargo[i].z == 25){
            cargo[i].s1 = s11;
            cargo[i].s2 = s12;
        }
        else if(cargo[i].z == 18 || cargo[i].z == 22 || cargo[i].z == 26){
            cargo[i].s1 = s21;
            cargo[i].s2 = s22;
        }
        else if(cargo[i].z == 19 || cargo[i].z == 23){
            cargo[i].s1 = s31;
            cargo[i].s2 = s32;
        }
        else if(cargo[i].z == 20 || cargo[i].z == 24){
            cargo[i].s1 = s41;
            cargo[i].s2 = s42;
        }
    }
}

//���ݶ������еĳ��Ⱥͳ����涨������������ִ���������Ӧ��ֵ����һ���̶ȵĳͷ�
void punish(){
	block_long = 0,block_times = 0;
	int temp2,sit;
	//�������飬�ҵ����������г��ȣ������㳬��������
	for(int i=0;i<CODELENGTH;i++){
        for(int j=0;j<CODELENGTH-i;j++){
            if(arr_p[j+1][1]>arr_p[j][1]){//��ʱ��Ϊ˳������
            temp2=arr_p[j+1][1];
            arr_p[j+1][1]=arr_p[j][1];
            arr_p[j][1]=temp2;

			sit = arr_p[j+1][0];
            arr_p[j+1][0] = arr_p[j][0];
            arr_p[j][0] = sit;

            // ddj = arr_p[j+1][2];
            // arr_p[j+1][2] = arr_p[j][2];
            // arr_p[j][2] = ddj;

			// TT = arr_p[j+1][3];
            // arr_p[j+1][3] = arr_p[j][3];
            // arr_p[j][3] = TT;
            }
        }
	}
	if(arr_p[0][1]>r_volume){
		block_long = arr_p[0][1] - r_volume;
	}
	else{
		block_long = 0;
	}
	for(int i=0;i<CODELENGTH;i++){
		if(arr_p[i][1]>r_volume){
			block_times++;
		}
	}
}

//�ɶѶ������ж϶Ѷ�������������
int g_number(int ddj){
	switch (ddj)
	{
	case 1:
		return g1_r;
		break;
	case 2:
		return g2_r;
		break;
	case 3:
		return g3_r;
		break;
	case 4:
		return g4_r;
		break;
	case 5:
		return g5_r;
		break;
	case 6:
		return g6_r;
		break;
	default:
		cout<<"g_number error!"<<endl;
		break;
		return -1;
	}
    cout<<"g_number error!"<<endl;
    return -1;
}
//�ж϶���
void arr_block(double TI,int ddj){
	block = 0;
	int gi_n = g_number(ddj);
	for(int i=0;i<gi_n;i++){//ѭ�������Ѷ����gp����
		if(gp[ddj-1][i][1]<TI){
			block++;
		}
	}
	arr_p[gpi][0] = gpi;
	arr_p[gpi][1] = block;
    arr_p[gpi][2] = ddj;
	arr_p[gpi][3] = TI;
	gpi++;
}

//��������
//ѡ���׼���ᣩ
int partition(double array[][2], int low, int high)
{
    while (low < high)
    {
        //lowλ��Ϊ��㣬low�ұߵĲ�С��low��ߵ�
        while (low < high&&array[low][1] <= array[high][1])
        {
            high--;
        }
        double temp = array[low][1];
        array[low][1] = array[high][1];
        array[high][1] = temp;

        temp = array[low][0];
        array[low][0] = array[high][0];
        array[high][0] = temp;
        //highλ��Ϊ��㣬high��ߵĲ�����high�ұߵ�
        while (low < high&&array[low][1] <= array[high][1])
        {
            low++;
        }
        temp = array[low][1];
        array[low][1] = array[high][1];
        array[high][1] = temp;

        temp = array[low][0];
        array[low][0] = array[high][0];
        array[high][0] = temp;
    }
    return low;
}

void quickSortHelp(double array[][2], int low, int high)
{
    if (low < high)
    {
        //������Ԫλ��
        int location = partition(array, low, high);
        //�ݹ����
        quickSortHelp(array, low, location - 1);
        quickSortHelp(array, location + 1, high);
    }
}

void quickSort(double array[][2], int sort_n)
{
    //�Ե�һ������Ԫ��Ϊ��׼���ᣩ
    quickSortHelp(array, 0, sort_n - 1);
}
//�жϻ�������
char judge_type(int p){
	if(cargo_now[p].s1==0 && cargo_now[p].s2==0)
		return 'R';
	else if(cargo_now[p].s1==0 && cargo_now[p].s2==1)
		return 'S';
	else if(cargo_now[p].s1==1 && cargo_now[p].s2==0)
		return 'H';
	else if(cargo_now[p].s1==1 && cargo_now[p].s2==1)
		return 'C';
	else{
		cout<<"judge_type error!"<<endl;
		cout<<p<<endl;
		return 'C';
	}
}
char judge_type(int p,int a){
	if(cargo[p].s1==0 && cargo[p].s2==0)
		return 'R';
	else if(cargo[p].s1==0 && cargo[p].s2==1)
		return 'S';
	else if(cargo[p].s1==1 && cargo[p].s2==0)
		return 'H';
	else if(cargo[p].s1==1 && cargo[p].s2==1)
		return 'C';
	else{
		cout<<"judge_type error!"<<endl;
		cout<<p<<endl;
		return 'C';
	}
}
//������λ����
void CS_swap(){
	srand((double)clock());
	for(int i=0; i < CODELENGTH / 2; i++){
		int sit = rand()%(CODELENGTH - 1);
		int temp_x=0,temp_y=0,temp_z=0;
		temp_x = cargo_now[i].x;
		temp_y = cargo_now[i].y;
		temp_z = cargo_now[i].z;
		cargo_now[i].x = cargo_now[sit].x;
		cargo_now[i].y = cargo_now[sit].y;
		cargo_now[i].z = cargo_now[sit].z;
		cargo_now[sit].x = temp_x;
		cargo_now[sit].y = temp_y;
		cargo_now[sit].z = temp_z;
	}
	ofstream out1;
	ofstream out_sit;
	out1.open("rand_2000_1.txt");
	out_sit.open("rand_2000_1_sit.txt");
	for(int i=0; i < CODELENGTH; i++){
		out1<<"{"<<cargo_now[i].x<<","<<cargo_now[i].y<<","<<cargo_now[i].z<<","<<cargo_now[i].s1<<","<<cargo_now[i].s2<<","<<cargo_now[i].num<<","<<"'a'"<<","<<cargo_now[i].model<<","<<cargo_now[i].time<<"}"<<",";
		out_sit<<cargo_now[i].x<<","<<cargo_now[i].y<<","<<cargo_now[i].z<<","<<judge_type(i)<<endl;
		if((i+1)%5==0){
			out1<<endl;	
		}
	}
	out1.close();
	out_sit.close();
}



//������

//���������
void get_R(int g[]){
	int j=0;
	for(int i=0; i < CODELENGTH; i++){
		if(g[i]<=R && j<R){//�������飬����������С��R����˵��Ϊ�ؿ����
			r_arry[j] = g[i];
			j++;
		}
	}
}
//�жϸñ���������̨�Ѷ��
int stacker(int p){
	int ddj = 0;
	if(cargo_now[p-1].x==1 || cargo_now[p-1].x==2)		//�����������Ϊ1��2����Ϊ�Ѷ��1
		ddj = 1;
	else if(cargo_now[p-1].x==3 || cargo_now[p-1].x==4)	//�����������Ϊ3��4����Ϊ�Ѷ��2
		ddj = 2;
	else if(cargo_now[p-1].x==5 || cargo_now[p-1].x==6)//�����������Ϊ5��6����Ϊ�Ѷ��3
		ddj = 3;
	else if(cargo_now[p-1].x==7 || cargo_now[p-1].x==8)//�����������Ϊ7��8����Ϊ�Ѷ��4
		ddj = 4;
	else if(cargo_now[p-1].x==10 || cargo_now[p-1].x==9)//�����������Ϊ9��10����Ϊ�Ѷ��5
		ddj = 5;
	else if(cargo_now[p-1].x==11 || cargo_now[p-1].x==12)//�����������Ϊ11��12����Ϊ�Ѷ��6
		ddj = 6;
	else{
		cout<<"ddj error!"<<endl;				//�����������λ������˵������
		ddj = 0;
	}
	return ddj;
}
//������ϻ��㵽�������ʱ��
void getT_load(int i,char type){
	//int n_load1 = R_n/fre; //���ϻ���1�����Ļ������� freΪÿ����һ��������������
	//int n_load2 = R_n - n_load1;//���ϻ���2�����Ļ������� 
		//�ж��Ƿ���ϻ���2����:
		//1: fre1 + t_load1
		//2: fre2 + t_load2
		//3: fre1*2 + t_load1
		//4: fre2*2 + t_load2
		//5: fre1*3 + t_load1
		//6: fre2*3 + t_load2
		if(i%2==0){
			t_R = fre2*(i/2) + t_load2;  
		}
		else{
			t_R = fre1*((i+1)/2) + t_load1;
		}
		temp_p++;
		if(type=='A'){//�������A���� 3���һ��
			if(temp_p==a_num){
				temp_p = 0;
				flag_R++;//����һ��
				send_t = t_R;//����ʱ��
			}
		}
		else{
			if(temp_p==b_num){//B���ͣ�5��һ��
				temp_p = 0;
				flag_R++;//����һ��
				send_t = t_R;
			}
		}
}
        
//����Ѷ������ţ����ص��öѶ����ʱ��
double getT(int ddj){
	switch(ddj){		//���ݵ���ͬ�Ѷ���ľ��룬���������Ѷ����ʱ��
		case 1:
			return r_ji1/v_R;
		case 2:
			return r_ji2/v_R;
		case 3:
			return r_ji3/v_R;
		case 4:
			return r_ji4/v_R;
		case 5:
			return r_ji5/v_R;
		case 6:
			return r_ji6/v_R;
		default:return 0;
	}
}
void R_Test(int r[]){
	int an=0;
	int ddj;
    int p1=0,p2=0,p3=0,p4=0,p5=0,p6=0;
    ofstream write;
	write.open("output/R.txt");//��ʾ��Ҫ�������������text.txt"����ļ��� ���û������ļ������Զ���������ļ�
	int p_R = 0;//�������±�
	for(int i =1;i<=R_n;i++){
		if(p_R>R)	//	��ֹ�����������Խ��
			break;
		if(an>R)	//	��ֹ�����������Խ��
			break;
        getT_load(i,'A');//�����ϻ������ı�ţ���1~R_n��ʼ�ϻ������A
        if(flag_R==2 && p_R<R){//�������� ��ʼ���㵽��Ѷ����ڵ�ʱ��
			flag_R = 0;	//����ǹ�0
            ddj = stacker(r[p_R]);//���������룬������Ѷ�����
			p_R++;
            get_t = send_t + getT(ddj);//���㵽��ʱ�� = ����ʱ��+����Ѷ����ʱ��
			//cout<<"get_t:"<<get_t<<endl;
        if(ddj==1){//�ж��Ƿ����ڶѶ��1
            //cout<<"The ddj is "<<ddj<<"\tThe num "<<p_R<<"\tstack arrive ddj time is "<<get_t<<endl;
            //write<<"The ddj is "<<ddj<<"\tThe num "<<p_R<<"\tstack arrive ddj time is "<<get_t<<endl;
				//cout<<1<<endl;
            a[an] = get_t;//д������a��
            an++;
            gp[0][p1][1] = get_t;//ͬʱд������gp��
            p1++;
            write<<an<<" "<<get_t<<endl;
            get_t = 0;//������ʱ�������0
            continue;//��߳���Ч�ʣ����ٽ���������ж�
        }
        if(ddj==2){
			a[an] = get_t;
            an++;
            gp[1][p2][1] = get_t;
            p2++;
            write<<an<<" "<<get_t<<endl;
            get_t = 0;
            continue;
        }
        if(ddj==3){
			a[an] = get_t;
            an++;
            gp[2][p3][1] = get_t;
            p3++;
            write<<an<<" "<<get_t<<endl;
            get_t = 0;
            continue;
        }
        if(ddj==4){
			a[an] = get_t;
			an++;
            gp[3][p4][1] = get_t;
			p4++;
            write<<an<<" "<<get_t<<endl;
            get_t = 0;
			continue;
        }
        if(ddj==5){
			a[an] = get_t;
            an++;
            gp[4][p5][1] = get_t;
            p5++;
            write<<an<<" "<<get_t<<endl;
            get_t = 0;
            continue;
        }
        if(ddj==6){
			a[an] = get_t;
            an++;
            gp[5][p6][1] = get_t;
			p6++;
            write<<an<<" "<<get_t<<endl;
            get_t = 0;
            continue;
        }
    }
	}
	write.close(); // �����Ϻ�ر�����ļ�
}

void randomArr(int G[],int len){    //������У�GΪ��������,lenΪ�������鳤��
    for(int i=0;i<len;i++){
        int sit = rand()%(len-1) +1;//���λ��
        int temp =G[i];		//������ǰλ�õı�������λ�õı���
        G[i] = G[sit];
        G[sit] = temp;
        //cout<<sit<<endl;
    }
}
//�춨ʱ��
void inspect(char type_inspect){//�����������
            switch(type_inspect){//���ݲ�ͬ�������ͣ����㲻ͬ�ļ춨ʱ��
                case 'a':
                    t_inspect = t_inspect_a * s_h;  //��a�ļ춨ʱ�䣨Сʱ��������� ��ֵ�� �춨ʱ��
                    break;
                case 'b':
                    t_inspect = t_inspect_b * s_h;
                    break;
                case 'c':
                    t_inspect = t_inspect_c * s_h;
                    break;
                case 'd':
                    t_inspect = t_inspect_d * s_h;
                    break;
                case 'e': 
                    t_inspect = t_inspect_e * s_h;
                    break;
                case 'f':
                    t_inspect = t_inspect_f * s_h;
                    break;    
                default:t_inspect = 0;
                break;
            }
}
//����ʱ��
double Walk_time(int y,int z){//���� y��z����
    float v1 = 2;//�Ѷ����ֱ�ƶ��ٶ�
    float v2 = 4;//�Ѷ��ˮƽ�ƶ��ٶ�
    float l = 0.5;//�� ����
    float h = 0.65;//���ܵ�һ����
    float d = 0.2;//��λ��ľ���
    int Yn = y;//y����
    int Zn = z;//z����
    float High_In = 0;//��ֱ�ƶ��ľ���
    float Long_In = 0;//ˮƽ�ƶ��ľ���
    float time_in_high = 0;//��ֱ�ƶ���ʱ��
    float time_in_long = 0;//ˮƽ�ƶ���ʱ��
    float time_in_run = 0;//�Ѷ���ƶ���ʱ��
    float time = 0;//�Ѷ���ƶ���ʱ�䣨������һ�����������ں������ԣ�
    High_In = Zn * h;//���㴹ֱ�ƶ��ľ���
    Long_In = Yn  * (l + d);//����ˮƽ�ƶ��ľ���
    time_in_high = High_In / v1;//���㴹ֱ�ƶ���ʱ��
    time_in_long = Long_In / v2;//����ˮƽ�ƶ���ʱ��
    time_in_run = max(time_in_high,time_in_long);//�Ѷ����ֱ�˶���ʱ����Ѷ��ˮƽ�ƶ���ʱ�� �������ʱ�伴Ϊ�Ѷ�����ƶ�ʱ��
    time = time_in_run;//��ֵ��time
    return time;//���ضѶ���˶���ʱ��
}
//���룬Ŀǰû���õ�
void insert_G(int G[],int sit,int value){  //���� ����ĳ�������в���һ��Ԫ�أ��������飬�����Ԫ�أ��Ͳ����λ�á�Ŀǰ�˺���û���õ�
    len++;
    int *a_n = new int[len];
    for(int i = 0;i<sit;i++)
        a_n[i] = G[i];
    a_n[sit] = value;
    for(int i = sit+1;i<len;i++)
        a_n[i] = G[i-1];
    for(int i=0;i<len;i++)
        G[i] = a_n[i];
    delete []a_n;
}
//�ͼ�ǰh-k�����룬�ؿ��h-k�����룬�γ�1-1��Ӧ��ϵ��
void S_H2(int G[]){//�����������
    int j = 0,p=0;
    for(int i=0; i < CODELENGTH; i++){//������������
        if(cargo_now[G[i]-1].s1==0 && cargo_now[G[i]-1].s2==1 && G[i]>=R+1 && G[i]<= R + H - _k){//���ձ����˳���жϱ����Ƿ����� �ͼ����,�Ҹ��ͼ��������ǰH-K
			s[j] = G[i];//���ñ���д�뵽�ͼ�������
			INum[j][0] = i;
			j++;//�ͼ������±�����1
		}
		else if(cargo_now[G[i]-1].s1==1 && cargo_now[G[i]-1].s2==0 && G[i]>= R + S + _k + 1 && G[i] <= R + S + H){//���ձ���˳���жϱ����Ƿ����ڻؿ���룬�һؿ�������ں�H-_k
			h[p] = G[i];//���ñ���д�뵽�ؿ����
			INum[p][1] = i;
			p++;//�ؿ������±�����1
		}
    }	
	for(int i=0;i< H - _k; i++){
		I[i][0] = s[i];
		I[i][1] = h[i];
	}		
}

//�ͼ�ǰh-k�����룬�ؿ��h-k�����룬�γ�1-1��Ӧ��ϵ��
void S_H(firefly f){//�ú�����S_H2�Ĺ���һ�£����������һ����Ⱥ
	int j = 0,p=0;
    for(int i=0; i < CODELENGTH; i++){
        if(cargo_now[f.G[i]-1].s1==0 && cargo_now[f.G[i]-1].s2==1 && f.G[i]>=R+1 && f.G[i]<= R + H - _k){
			s[j] = f.G[i];
			INum[j][0] = i;
			j++;
		}
		else if(cargo_now[f.G[i]-1].s1==1 && cargo_now[f.G[i]-1].s2==0 && f.G[i]>= R + S + _k + 1 && f.G[i] <= R + S + H){
			h[p] = f.G[i];
			INum[p][1] = i;
			p++;
		}
    }	
	for(int i=0;i< H - _k; i++){
		I[i][0] = s[i];
		I[i][1] = h[i];
	}	
}

// todo ���� S_H()
void S_H(Food f){//�ú�����S_H2�Ĺ���һ�£����������һ����Ⱥ
    int j = 0,p=0;
    for(int i=0; i < CODELENGTH; i++){
        // todo error: SIGSEGV (Segmentation fault)
        if(cargo_now[f.getSequence(i)-1].s1==0 && cargo_now[f.getSequence(i)-1].s2==1 && f.getSequence(i)>=R+1 && f.getSequence(i)<= R + H - _k){
            s[j] = f.getSequence(i);
            INum[j][0] = i;
            j++;
        }
        else if(cargo_now[f.getSequence(i)-1].s1==1 && cargo_now[f.getSequence(i)-1].s2==0 && f.getSequence(i)>= R + S + _k + 1 && f.getSequence(i) <= R + S + H){
            h[p] = f.getSequence(i);
            INum[p][1] = i;
            p++;
        }
    }
    for(int i=0;i< H - _k; i++){
        I[i][0] = s[i];
        I[i][1] = h[i];
    }
}

void check(int G[],int s[],int h[]){
	int i=0,temp=0;
	for(int j=0;j< H - _k; j++){
		if(INum[j][0]>INum[j][1]){//��Ҫ����
			temp = G[INum[j][0]];
			G[INum[j][0]] = G[INum[j][1]];
			G[INum[j][1]] = temp;
		}
	}	
}

double read(double TI,double TDI,int p,int nextp){
    char type,next_type;//��ǰ����Ļ������ͣ���һ������Ļ�������
	int ddj=0;//�Ѷ�����
	int i=0;
    double wait_time = 0;//�ȴ�ʱ��
    double grab_time = 1.5;//ץȡʱ��
    double walk_time1 = 0;//����ʱ��1
    double place_time = 1.5;//����ʱ��
    double walk_time2 = 0;//����ʱ��2
	bool flag = false;
	int gi_n = 0;
	//�жϵ�ǰ��ȡ�ı����������ֱ������ͣ�R��S��H��C
    if(1<=p && p<=R )
        type = 'R';
    else if (R+1<=p && p<=R+S)
        type = 'S';
    else if (R+S+1<=p && p<=R+S+H)
        type = 'H';
    else if(R+S+H+1<=p && p<=R+S+H+C)
        type = 'C';
    else
        cout<<"p error!"<<endl;
	//�ж���һ�������������ֻ�������
    if(1<=nextp && nextp<=R )
        next_type = 'R';
    else if (R+1<=nextp && nextp<=R+S)
        next_type = 'S';
    else if (R+S+1<=nextp && nextp<=R+S+H)
        next_type = 'H';
    else if(R+S+H+1<=nextp && nextp<=R+S+H+C)
        next_type = 'C';
    else
        cout<<"nextp error!"<<endl;
    switch (type){
        case 'R'://�ñ���Ϊ������
			ddj = stacker(p);//������ĵ���-ʱ����Ϊ���
			gi_n = g_number(ddj);
			for(int j=0;j<gi_n;j++){
				if(gp[ddj-1][j][0]==p){
					gp[ddj-1][j][1] = 999999;
					break;
				}
			}
            if(a[ai]<=TI)//�жϵȴ�ʱ�� ����a[ai]�д�ŵ����ʱ�������δ�С�����
                wait_time = 0;
            else
                wait_time = a[ai] - TI;
			ai++;//���� a�±�����
            walk_time1 = Walk_time(cargo_now[p-1].y,cargo_now[p-1].z);
            if(next_type=='R'||next_type=='H')
                walk_time2 = Walk_time(cargo_now[p-1].y,cargo_now[p-1].z);
            else
                walk_time2 = Walk_time(abs(cargo_now[p-1].y-cargo_now[nextp-1].y),abs(cargo_now[p-1].z-cargo_now[nextp-1].z));
            TI += wait_time + grab_time + walk_time1 + walk_time2 + place_time;
			TDI = grab_time + walk_time1 + walk_time2 + place_time + TD[0];
			TD[0] = TDI;
			ddj = stacker(p);
			arr_block(TI,ddj);
            break;
        case 'H':
			// ddj = stacker(p);//������ĵ���ʱ����Ϊ���
			// gi_n = g_number(ddj);
			// for(int j=0;j<gi_n;j++){
			// 	if(gp[ddj-1][j][0]==p){
			// 		gp[ddj-1][j][1] = 99999999;
			// 		break;
			// 	}
			// }
            for(i=0;i< H - _k; i++){//��h[]���ҵ��±�
                if(hi[i][0] == p){
					flag = true;
					break;
				}
            }
            if(hi[i][1]<=TI || flag==false)
                wait_time = 0;
            else    
                wait_time = hi[i][1] - TI;
            walk_time1 = Walk_time(cargo_now[p-1].y,cargo_now[p-1].z);
            if(next_type=='R'||next_type=='H')
                walk_time2 = Walk_time(cargo_now[p-1].y,cargo_now[p-1].z);
            else
                walk_time2 = Walk_time(abs(cargo_now[p-1].y-cargo_now[nextp-1].y),abs(cargo_now[p-1].z-cargo_now[nextp-1].z));
            TI += wait_time + grab_time + walk_time1 + walk_time2 + place_time;
			TDI = grab_time + walk_time1 + walk_time2 + place_time + TD[0];
			TD[0] = TDI;
			ddj = stacker(p);
			arr_block(TI,ddj);
            break;
        case 'C':
            walk_time1 = Walk_time(cargo_now[p-1].y,cargo_now[p-1].z);
            if(next_type=='R'||next_type=='H')
                walk_time2 = Walk_time(cargo_now[p-1].y,cargo_now[p-1].z);
            else
                walk_time2 = Walk_time(abs(cargo_now[p-1].y-cargo_now[nextp-1].y),abs(cargo_now[p-1].z-cargo_now[nextp-1].z));
            TI += grab_time + walk_time1 + place_time + walk_time2;
			TDI = grab_time + walk_time1 + walk_time2 + place_time + TD[0];
			TD[0] = TDI;
			ddj = stacker(p);
			arr_block(TI,ddj);
            break;
        case 'S':
            walk_time1 = Walk_time(cargo_now[p-1].y,cargo_now[p-1].z); //�Ѷ���ӵ�ǰλ���ƶ����ͼ�ڣ��˴�Ĭ���ͼ��Ϊ0,0
			if(next_type=='R'||next_type=='H')//�����һ��������������ؿ����
				walk_time2 = Walk_time(cargo_now[p-1].y,cargo_now[p-1].z);//***���޸�***�Ѷ������ƶ�����һ���������ʼλ�ã�Ҳ����0,0λ�ã��˴������ڿɸ��ݲ�ͬ�Ļؿ��ʲ���¥���öѶ���ƶ�����ͬ��λ�ã�
			else
				walk_time2 = Walk_time(abs(cargo_now[p-1].y-cargo_now[nextp-1].y),abs(cargo_now[p-1].z-cargo_now[nextp-1].z));//��������ͼ����⣬���ƶ����û���Ļ���λ��
			TI +=  grab_time + walk_time1 + place_time+ walk_time2;//��������ĶѶ���ܹ���ʱ��Ϊ �ȴ�ʱ��+��ȡʱ��+��������ʱ��+����ʱ��+���ߵ���һ�������ʱ��
			TDI =  grab_time + walk_time1 + place_time+ walk_time2 + TD[0];//�Ѷ��ʵ�ʹ���ʱ�� = �ܹ���ʱ��-�ȴ�ʱ��
			TD[0] = TDI;//��ʵ�ʹ���ʱ��д�뵽ʵ�ʹ��������У������������Ҫ�����������Ա���ÿһ̨�Ѷ����ʵ�ʹ���ʱ�䡣��ʱ��ÿ̨�Ѷ����ʵ�ʹ���ʱ����ӵ�TD[0]��
			//��ʼ���� �ͼ���� ����Ӧ�� �ؿ���� �� �ؿ�ʱ��
			for( i=0;i< H - _k; i++){
				if(s[i]==p){//���ݵ�ǰ���룬�ҵ��� �ͼ�������� �е��±� i�����±�ɶ�Ӧ�� �ؿ����� �еĻؿ�����λ��
					ddj = stacker(h[i]);//�жϸûؿ����������̨�Ѷ��������
					switch (ddj)
					{
					case 1://����ǵ�һ̨�Ѷ������
						inspect(cargo_now[p-1].type);//���ݸ��ͼ����Ļ������ͣ�������ͼ�ʱ��
						g1_H2[th1]=h[i];//���ûؿ����д�뵽�Ѷ��1�Ļؿ�������
						th1++;//�Ѷ��1�� �ؿ�������� �� �ؿ�ʱ������ �±�����
						// gp[0][gp1][0] = h[i];//�ؿ����д������gp��
						// gp[0][gp1][1] = TI + t_inspect;//�ؿ�ʱ��д������gp��
						// gp1++;
						break;
					case 2:
						inspect(cargo_now[p-1].type);
						g2_H2[th2]=h[i];
						th2++;
						// gp[1][gp2][0] = h[i];//�ؿ����д������gp��
						// gp[1][gp2][1] = TI + t_inspect;//�ؿ�ʱ��д������gp��
						// gp2++;
						break;
					case 3:
						inspect(cargo_now[p-1].type);
						g3_H2[th3]=h[i];
						th3++;
						// gp[2][gp3][0] = h[i];//�ؿ����д������gp��
						// gp[2][gp3][1] = TI + t_inspect;//�ؿ�ʱ��д������gp��
						// gp3++;
						break;
					case 4:
						inspect(cargo_now[p-1].type);
						g4_H2[th4]=h[i];
						th4++;
						// gp[3][gp4][0] = h[i];//�ؿ����д������gp��
						// gp[3][gp4][1] = TI + t_inspect;//�ؿ�ʱ��д������gp��
						// gp4++;
						break;
					case 5:
						inspect(cargo_now[p-1].type);
						g5_H2[th5]=h[i];
						th5++;
						// gp[4][gp5][0] = h[i];//�ؿ����д������gp��
						// gp[4][gp5][1] = TI + t_inspect;//�ؿ�ʱ��д������gp��
						// gp5++;
						break;
					case 6:
						inspect(cargo_now[p-1].type);
						g6_H2[th6]=h[i];
						th6++;
						// gp[5][gp6][0] = h[i];//�ؿ����д������gp��
						// gp[5][gp6][1] = TI + t_inspect;//�ؿ�ʱ��д������gp��
						// gp6++;
						break;
					default:
						cout<<"read code ddj error!"<<endl;
						break;
					}
					//cout<<"------------"<<h[i]<<"------------"<<endl;
					hi[v2][1] = TI + t_inspect;//�ؿ�ʱ��д�뵽hi[v2][1]��
					hi[v2][0] = h[i];//�ؿ���� д�뵽hi[v2][0]��
					v2++;//v2����
					th[i] = TI + t_inspect;//�ؿ�ʱ��ͳһд�뵽һ��������
					break;
				}
			}
		ddj = stacker(p);
		arr_block(TI,ddj);
		break;
        default:
            cout<<"read error!"<<endl;
            break;
    }
    return TI;//���ضѶ����ȡ�ñ����ʱ��
}

// todo ���� Storing_num()
void Storing_num(Food f){//������Ⱥ
    int p=0;
    char g=0;
    g1_s = 0,g2_s = 0,g3_s = 0,g4_s = 0,g5_s = 0,g6_s = 0;
    g1_h = 0,g2_h = 0,g3_h = 0,g4_h = 0,g5_h = 0,g6_h = 0;
    g1_r = 0,g2_r = 0,g3_r = 0,g4_r = 0,g5_r = 0,g6_r = 0;
    g1_n=0;g2_n=0;g3_n=0;g4_n=0;g5_n=0;g6_n=0;
    for(int i=0; i < CODELENGTH; i++){//�������л�λ
        p = cargo_now[f.getSequence(i)-1].x;//������Ϣ
        g = judge_type(f.getSequence(i)-1);//������� R��S��H��C
        switch (p)//�ж�������̨�Ѷ��
        {
            case 1:
            case 2://����1�ŶѶ��
                if(g=='S')//�ͼ�
                    g1_s++;
                else if(g=='H')//�ؿ�
                    g1_h++;
                else if(g=='R')//���
				    g1_r++;
                g1_n++;//�Ѷ��1������������
                break;
            case 3:
            case 4:
                if(g=='S')
                    g2_s++;
                else if(g=='H')
                    g2_h++;
                else if(g=='R')
				    g2_r++;
                g2_n++;
                break;
            case 5:
            case 6:
                if(g=='S')
                    g3_s++;
                else if(g=='H')
                    g3_h++;
                else if(g=='R')
				    g3_r++;
                g3_n++;
                break;
            case 7:
            case 8:
                if(g=='S')
                    g4_s++;
                else if(g=='H')
                    g4_h++;
                else if(g=='R')
				    g4_r++;
                g4_n++;
                break;
            case 9:
            case 10:
                if(g=='S')
                    g5_s++;
                else if(g=='H')
                    g5_h++;
                else if(g=='R')
				    g5_r++;
                g5_n++;
                break;
            case 11:
            case 12:
                if(g=='S')
                    g6_s++;
                else if(g=='H')
                    g6_h++;
                else if(g=='R')
				    g6_r++;
                g6_n++;
                break;
            default:
                cout<<"sort_num error!"<<endl;
                break;
        }
    }
}

// todo ���� Storing()
void Storing(Food f,int g1[],int g2[],int g3[],int g4[],int g5[],int g6[],int g1_S[],int g2_S[],int g3_S[],int g4_S[],int g5_S[],int g6_S[],int g1_H[],int g2_H[],int g3_H[],int g4_H[],int g5_H[],int g6_H[]){
    j_1=0, j_2=0, j_3=0, j_4=0, j_5=0, j_6=0;
    int g1s=0,g2s=0,g3s=0,g4s=0,g5s=0,g6s=0;
    int g1h=0,g2h=0,g3h=0,g4h=0,g5h=0,g6h=0;
    int g1r=0,g2r=0,g3r=0,g4r=0,g5r=0,g6r=0;
    int p=0;
    char g=0;
    for(int i=0; i < CODELENGTH; i++){//������������
        p = cargo_now[f.getSequence(i)-1].x;//������Ϣ
        g = judge_type(f.getSequence(i)-1);//������� R��S��H��C
        switch (p)//�жϱ���������̨�Ѷ��
        {
            case 1:
            case 2://���ڶѶ��1
                if(g=='S'){//�����ͼ����
                    g1_S[g1s] = f.getSequence(i);//���ñ���д��Ѷ��1���ͼ�����
                    g1s++;//�ͼ������±�����1
                }
                else if(g=='H'){//���ڻؿ����
                    g1_H[g1h] = f.getSequence(i);//�ñ���д��Ѷ��1�Ļؿ�����
                    g1h++;//�ؿ������±�����1
                }
                else if(g=='R'){//����������
				    gp[0][g1r][0] = f.getSequence(i);
				    //g1_R[g1r] = f.G[i];//���ñ���д��Ѷ��1���������
				    g1r++;
			    }   
                g1[j_1] = f.getSequence(i);//�ñ���д�뵽�Ѷ��1�� ����������
                j_1++;//�Ѷ��1�ı�����������1
                break;
            case 3:
            case 4:
                if(g=='S'){
                    g2_S[g2s] = f.getSequence(i);
                    g2s++;
                }
                else if(g=='H'){
                    g2_H[g2h] = f.getSequence(i);
                    g2h++;
                }
                else if(g=='R'){//����������
				    gp[1][g2r][0] = f.getSequence(i);
				    //g2_R[g2r] = f.G[i];//���ñ���д��Ѷ��2���������
				    g2r++;
			    }
                g2[j_2] = f.getSequence(i);
                j_2++;
                break;
            case 5:
            case 6:
                if(g=='S'){
                    g3_S[g3s] = f.getSequence(i);
                    g3s++;
                }
                else if(g=='H'){
                    g3_H[g3h] = f.getSequence(i);
                    g3h++;
                }
                else if(g=='R'){//����������
				    gp[2][g3r][0] = f.getSequence(i);
				    //g3_R[g3r] = f.G[i];//���ñ���д��Ѷ��3���������
				    g3r++;
			    }
                g3[j_3] = f.getSequence(i);
                j_3++;
                break;
            case 7:
            case 8:
                if(g=='S'){
                    g4_S[g4s] = f.getSequence(i);
                    g4s++;
                }
                else if(g=='H'){
                    g4_H[g4h] = f.getSequence(i);
                    g4h++;
                }
                else if(g=='R'){//����������
				    gp[3][g4r][0] = f.getSequence(i);
				    //g4_R[g4r] = f.G[i];//���ñ���д��Ѷ��4���������
				    g4r++;
			    }
                g4[j_4] = f.getSequence(i);
                j_4++;
                break;
            case 9:
            case 10:
                if(g=='S'){
                    g5_S[g5s] = f.getSequence(i);
                    g5s++;
                }
                else if(g=='H'){
                    g5_H[g5h] = f.getSequence(i);
                    g5h++;
                }
                else if(g=='R'){//����������
				    gp[4][g5r][0] = f.getSequence(i);
				    //g5_R[g5r] = f.G[i];//���ñ���д��Ѷ��5���������
				    g5r++;
			    }
                g5[j_5] = f.getSequence(i);
                j_5++;
                break;
            case 11:
            case 12:
                if(g=='S'){
                    g6_S[g6s] = f.getSequence(i);
                    g6s++;
                }
                else if(g=='H'){
                    g6_H[g6h] = f.getSequence(i);
                    g6h++;
                }
                else if(g=='R'){//����������
				    gp[5][g6r][0] = f.getSequence(i);
				    //g6_R[g6r] = f.G[i];//���ñ���д��Ѷ��6���������
				    g6r++;
			    }
                g6[j_6] = f.getSequence(i);
                j_6++;
                break;
            default:
                cout<<"sort error!"<<endl;
                break;
        }
    }
}

//����� Ŀǰû���õ�
void R_t(double a[]){
    int cnt = 0;
    double temp = 0;
    FILE *fp=fopen("Test.txt", "r");
    while(cnt<R){
        fscanf(fp, "%lf", &temp);
        a[cnt] = temp; 
        cnt++;
    }
    fclose(fp);
}

//�����Ӧ��ֵ���������*0.8 + �Ѷ��ʵ�ʹ���ʱ��*0.2��/60
int max2(double T[], Food &f){
	int i,j;
    double temp,G_fintess;
	double TT;
    for(i=0;i<5;i++)//��������Ԫ�أ��Ӵ�С����
        for(j=0;j<5-i;j++){
            if(T[j+1]>T[j]){
            temp=T[j+1];
            T[j+1]=T[j];
            T[j]=temp;
            }
        }
    int temp2=0;
    int sit = 0;
    int ddj = 0;
    for(int i=0;i<CODELENGTH;i++){
        for(int j=0;j<CODELENGTH-i;j++){
            if(arr_p[j+1][3]<arr_p[j][3]){//��ʱ��Ϊ˳������
            temp2=arr_p[j+1][1];
            arr_p[j+1][1]=arr_p[j][1];
            arr_p[j][1]=temp2;

			sit = arr_p[j+1][0];
            arr_p[j+1][0] = arr_p[j][0];
            arr_p[j][0] = sit;

            ddj = arr_p[j+1][2];
            arr_p[j+1][2] = arr_p[j][2];
            arr_p[j][2] = ddj;

			TT = arr_p[j+1][3];
            arr_p[j+1][3] = arr_p[j][3];
            arr_p[j][3] = TT;
            }
           
        }
	}
    ofstream out;
    out.open("output/out_block.txt");
    for(int i=1;i<CODELENGTH+1;i++){
        out<<"arr_p[][]:"<<arr_p[i][0]<<","<<arr_p[i][1]<<","<<arr_p[i][2]<<","<<arr_p[i][3]<<endl;
    }
	punish();
	//T[0] = T[0]/60.0;
	G_fintess = T[0]*0.95 + TD[0]*0.05 + block_long*block_times*10;//��Ӧ��ֵ���㣬��Ȩ��
//    cout << T[0] << endl;
    f.setTimeSpan(T[0] / 3600.0);
	//G_fintess = G_fintess/60.0;//����60 ����ת��Ϊ����
	//T[0] = T[0]/60.0;//�Ѷ��ʵ�ʹ���ʱ�� ����
	out.close();
	return G_fintess;
    //return G_fintess;
}

void read_ddj(int gi_H[],int ddj,int gi[]){
	switch (ddj)//�ж϶Ѷ�����
	{
	case 1:
		while(gi_H[h1]!=gi[j_1]){//���϶�ȡ��ֱ����ȡ��g1�е�һ��H����Ϊֹ

			if(j_1 < (g1_n - 1)){//���������һλ����
				T1 = read(T1, TD1, gi[j_1], gi[j_1 + 1]);//��ȡ����
				j_1++;//�Ѷ�������������1
			}
			else if(j_1 == (g1_n - 1)){//�����ȡ���öѶ�������һλ���룬����һ�������뵱ǰ������ͬ
				T1 = read(T1, TD1, gi[j_1], gi[j_1]);
				j_1++;
			}
			if(j_1 > g1_n - 1)//����öѶ���ı���ȫ����ȡ���
				break;//����ѭ��

		}
		h1++;
		break;

	case 2:
		while(gi_H[h2]!=gi[j_2]){ //���϶�ȡ��ֱ����ȡ��g2�е�һ��H����Ϊֹ

			if(j_2 < (g2_n - 1)){
				T2 = read(T2, TD2, gi[j_2], gi[j_2 + 1]);
				j_2++;
			}
			else if(j_2 == (g2_n - 1)){
				T2 = read(T2, TD2, gi[j_2], gi[j_2]);
				j_2++;
			}	
			if(j_2 > g2_n - 1)
				break;

		}
		h2++;	
		break;

	case 3:
		while(gi_H[h3]!=gi[j_3]){ //���϶�ȡ��ֱ����ȡ��g3�е�һ��H����Ϊֹ
			if(j_3 < (g3_n - 1)){
				T3 = read(T3, TD3, gi[j_3], gi[j_3 + 1]);
				j_3++;
			}
			else if(j_3 == (g3_n - 1)){
				T3 = read(T3, TD3, gi[j_3], gi[j_3]);
				j_3++;
			}	
			if(j_3 > g3_n - 1)
				break;
		}	
		h3++;
		break;

	case 4:
		while(gi_H[h4]!=gi[j_4]){ //���϶�ȡ��ֱ����ȡ��g4�е�һ��H����Ϊֹ
			if(j_4 < (g4_n - 1)){
				T4 = read(T4, TD4, gi[j_4], gi[j_4 + 1]);
				j_4++;
			}
			else if(j_4 == (g4_n - 1)){
				T4 = read(T4, TD4, gi[j_4], gi[j_4]);
				j_4++;
			}	
			if(j_4 > g4_n - 1)
				break;
		}
		h4++;
		break;

	case 5:
		while(gi_H[h5]!=gi[j_5]){ //���϶�ȡ��ֱ����ȡ��g5�е�һ��S����Ϊֹ
			if(j_5 < (g5_n - 1)){
				T5 = read(T5, TD5, gi[j_5], gi[j_5 + 1]);
				j_5++;
			}
			else if(j_5 == (g5_n - 1)){
				T5 = read(T5, TD5, gi[j_5], gi[j_5]);
				j_5++;
			}	
			if(j_5 > g5_n - 1)
				break;
		}
		h5++;
		break;

	case 6:
		while(gi_H[h6]!=gi[j_6]){ //���϶�ȡ��ֱ����ȡ��g6�е�һ��S����Ϊֹ
			if(j_6 < (g6_n - 1)){
				T6 = read(T6, TD6, gi[j_6], gi[j_6 + 1]);
				j_6++;
			}
			else if(j_6 == (g6_n - 1)){
				T6 = read(T6, TD6, gi[j_6], gi[j_6]);
				j_6++;
			}	
			if(j_6 > g6_n - 1)
				break;
		}	
		h6++;
		break;

	default:
		cout<<"read_ddj error!"<<endl;
		break;
	}
}

//�ж��Ƿ��������
void decide_swap(int g[], int gi[], int gi_H2[], int gi_th[], int gi_H[], int thi, int p, int gi_h, int hj,
                 int gi_n) {//hj��ʾ�Ѷ����ȡ�ĵ�ǰ�ؿ��������
    int u1 = 0, u2 = 0, temp = 0;//u1��u2��ʾ��Ҫ����������±�
    int p1 = 0;
    bool flag_u1 = false, flag_u2 = false;
    p1 = hi[v - 1][0];//ʱ����̵Ļؿ����
    int ddj = stacker(p1);//�ж����ʱ��ؿ����ĶѶ�����
    int p2 = 0;//Ҫ�����ı���
    for (int i = hj - 1; i < thi; i++) {//�Ӷ�ȡ����ǰ�ؿ�������� ��ʼ �����������ͼ����ƥ��Ļؿ��������Ϊֹ
        if (p1 == gi_H2[hj - 1])break;//����Ҫ����
        else {//��Ҫ����
            p2 = gi_H2[hj - 1];//���һλ�Ļؿ���뽻��
            for (int j = 0; j < CODELENGTH; j++) {
                if (g[j] == p1) {
                    u1 = j;
                    flag_u1 = true;
                    continue;
                }
                if (g[j] == p2) {
                    u2 = j;
                    flag_u2 = true;
                    continue;
                }
                if (flag_u1 == true && flag_u2 == true)
                    break;
            }
            //��G�н���λ��
            temp = g[u1];
            g[u1] = g[u2];
            g[u2] = temp;
            u1 = 0, u2 = 0;
            flag_u1 = false, flag_u2 = false;
            //��gi_h�н���
            for (int j = 0; j < gi_h; j++) {
                if (gi_H[j] == p1) {
                    u1 = j;
                    continue;
                }
                if (gi_H[j] == p2) {
                    u2 = j;
                    continue;
                }
                if (flag_u1 == true && flag_u2 == true)
                    break;
            }
            temp = gi_H[u1];
            gi_H[u1] = gi_H[u2];
            gi_H[u2] = temp;
            u1 = 0, u2 = 0;
            flag_u1 = false, flag_u2 = false;
            gi_H2[hj - 1] = p1;//�滻��gi_H2�еı���
            //��gi�н���
            for (int j = 0; j < gi_n; j++) {
                if (gi[j] == p1) {
                    u1 = j;
                    continue;
                }
                if (gi[j] == p2) {
                    u2 = j;
                    continue;
                }
                if (flag_u1 == true && flag_u2 == true)
                    break;
            }
            temp = gi[u1];
            gi[u1] = gi[u2];
            gi[u2] = temp;
            u1 = 0, u2 = 0;
            break;
        }
    }
}

//�ҵ�ʱ����̵Ļؿ����
int min_h(){
	int Th = th1+th2+th3+th4+th5+th6-v;//�����Ѷ�ȡ�ͼ���������
    int i,j,p=0,sit=0;
    double temp;
	//ð������
	for( i=v;i<Th-1;i++){//��ʼv��0����0��ʼѭ�����������Ѷ�ȡ���ͼ�����Ϊֹ����ʾ���� �����Ѷ�ȡ�ͼ�������� �� �ؿ���� �� �ؿ�ʱ��
	//��Ҫ�������Աȣ���hi[][]������ݻؿ�ʱ��������򣬲���������ʱ�����Ӧ�Ļؿ����Ҳ���Żؿ�ʱ��������򣬱�֤hi[v][0]ʼ��Ϊ �������лؿ��������ʱ��
        for(j=v;j<Th-1-i;j++){
            if(hi[j+1][1]<hi[j][1]){
            temp=hi[j+1][1];
            hi[j+1][1]=hi[j][1];
            hi[j][1]=temp;

			sit = hi[j+1][0];
            hi[j+1][0] = hi[j][0];
            hi[j][0] = sit;
            }
        }
	}
	
	//��������
	//quickSortHelp(hi, v, Th-1);
	v++;//���ζ�ȡ����̻ؿ����Ļؿ�ʱ�����ҵ����ƶ�����һλ���˺�λ��v֮ǰ�Ļؿ���벻�ٲ���Ƚ�
	if(hi[v-1][0]==9999)
		v--;
	return hi[v-1][0];//������̻ؿ�ʱ��Ļؿ����
}

// todo ���� Fitness()
double Fintess(Food& f,int g1[],int g2[],int g3[],int g4[],int g5[],int g6[],int g1_H[],int g2_H[],int g3_H[],int g4_H[],int g5_H[],int g6_H[],int g1_H2[],int g2_H2[],int g3_H2[],int g4_H2[],int g5_H2[],int g6_H2[],int g1_th[],int g2_th[],int g3_th[],int g4_th[],int g5_th[],int g6_th[]){
    T1=0,T2=0,T3=0,T4=0,T5=0,T6=0;
    TD1=0,TD2=0,TD3=0,TD4=0,TD5=0,TD6=0;
    j_1=0, j_2=0, j_3=0, j_4=0, j_5=0, j_6=0;
    h1=0,h2=0,h3=0,h4=0,h5=0,h6=0;
    th1=0,th2=0,th3=0,th4=0,th5=0,th6=0;
    int ddj=0,p=0;
    v = 0;v2=0;
    TD[0]=0;
    //���նѶ��˳�����ζ�ȡ���룬ֱ����ȡ���ؿ����Ϊֹ
    read_ddj(g1_H,1,g1);
    read_ddj(g2_H,2,g2);
    read_ddj(g3_H,3,g3);
    read_ddj(g4_H,4,g4);
    read_ddj(g5_H,5,g5);
    read_ddj(g6_H,6,g6);

    //void decide_swap(firefly& f,int gi_H2[],int gi_th[],int gi_H[],int thi,int p,int gi_h,int hi)
    for(int i=0;i< H - _k - 6; i++){
        p = min_h();//��̻ؿ�ʱ��Ļؿ����
        if(p==9999)
            break;
        ddj = stacker(cargo_now[p-1].x);//��ȡ�ñ���ĶѶ�����
        switch (ddj)//�ж� ��̻ؿ�ʱ��Ļؿ����� �Ѷ�����
        {
            case 1://�����1�ŶѶ���������ж��Ƿ���Ҫ�����ؿ�����Ϊֹ���ٶ����϶�ȡ1�ŶѶ���ı��룬ֱ����ȡ���ؿ����Ϊֹ
                decide_swap(f.getSequenceAddress(),g1,g1_H2,g1_th,g1_H,th1,p,g1_h,h1,g1_n);//�����ؿ����λ��
                read_ddj(g1_H,1,g1);//��ȡ���룬ֱ���ؿ����
                break;//���������������̻ؿ�ʱ��
            case 2:
                decide_swap(f.getSequenceAddress(),g2,g2_H2,g2_th,g2_H,th2,p,g2_h,h2,g2_n);
                read_ddj(g2_H,2,g2);
                break;
            case 3:
                decide_swap(f.getSequenceAddress(),g3,g3_H2,g3_th,g3_H,th3,p,g3_h,h3,g3_n);
                read_ddj(g3_H,3,g3);
                break;
            case 4:
                decide_swap(f.getSequenceAddress(),g4,g4_H2,g4_th,g4_H,th4,p,g4_h,h4,g4_n);
                read_ddj(g4_H,4,g4);
                break;
            case 5:
                decide_swap(f.getSequenceAddress(),g5,g5_H2,g5_th,g5_H,th5,p,g5_h,h5,g5_n);
                read_ddj(g5_H,5,g5);
                break;
            case 6:
                decide_swap(f.getSequenceAddress(),g6,g6_H2,g6_th,g6_H,th6,p,g6_h,h6,g6_n);
                read_ddj(g6_H,6,g6);
                break;
            default:
                cout<<"Fintess decide_swap error!"<<endl;
                break;
        }
    }

//�ж�6�������б����Ƿ�ȫ����ȡ���
    if(j_1 + j_2 + j_3 + j_4 + j_5 + j_6 == CODELENGTH){
        T[0] = T1;T[1] = T2;T[2] = T3;T[3] = T4;T[4] = T5;T[5] = T6;
        return max2(T, f);
    }
    if(j_1 < g1_n){
        while(j_1 != g1_n){
            if(j_1 == (g1_n - 1)){
                T1 = read(T1, TD1, g1[j_1], g1[j_1]);
                j_1++;
            }
            else if(j_1 < (g1_n - 1)){
                T1 = read(T1, TD1, g1[j_1], g1[j_1 + 1] );
                j_1++;
            }
        }
    }

    if(j_2 < g2_n){
        while(j_2 != g2_n){
            if(j_2 == (g2_n - 1)){
                T2 = read(T2, TD2, g2[j_2], g2[j_2] );
                j_2++;
            }
            else if(j_2 < (g2_n - 1)){
                T2 = read(T2, TD2, g2[j_2], g2[j_2 + 1] );
                j_2++;
            }
        }
    }

    if(j_3 < g3_n){
        while(j_3 != g3_n){
            if(j_3 == (g3_n - 1)){
                T3 = read(T3, TD3, g3[j_3], g3[j_3] );
                j_3++;
            }
            else if(j_3 < (g3_n - 1)){
                T3 = read(T3, TD3, g3[j_3], g3[j_3 + 1] );
                j_3++;
            }
        }
    }

    if(j_4 < g4_n){
        while(j_4 != g4_n){
            if(j_4 == (g4_n - 1)){
                T4 = read(T4, TD4, g4[j_4], g4[j_4] );
                j_4++;
            }
            else if(j_4 < (g4_n - 1)){
                T4 = read(T4, TD4, g4[j_4], g4[j_4 + 1] );
                j_4++;
            }
        }
    }

    if(j_5 < g5_n){
        while(j_5 != g5_n){
            if(j_5 == (g5_n - 1)){
                T5 = read(T5, TD5, g5[j_5], g5[j_5] );
                j_5++;
            }
            else if(j_5 < (g5_n - 1)){
                T5 = read(T5, TD5, g5[j_5], g5[j_5 + 1] );
                j_5++;
            }
        }
    }

    if(j_6 < g6_n){
        while(j_6 != g6_n){
            if(j_6 == (g6_n - 1)){
                T6 = read(T6, TD6, g6[j_6], g6[j_6] );
                j_6++;
            }
            else if(j_6 < (g6_n - 1)){
                T6 = read(T6, TD6, g6[j_6], g6[j_6 + 1] );
                j_6++;
            }
        }
    }


    T[0] = T1;T[1] = T2;T[2] = T3;T[3] = T4;T[4] = T5;T[5] = T6;
    return max2(T, f);
}

// todo ���� ensimpleCode()
void enSimpleCode(Food& f) {
    //��ʼ��һЩ����
    int b1 = INT32_MAX;
    ai = 0;
    flag_R = 0;
    t_R = 0;
	//11.3 go
	gp1 = 0,gp2 = 0,gp3 = 0,gp4 = 0,gp5 = 0,gp6 = 0;
	gpi=0;
	for(int i=0;i<6;i++)
		for(int j=0;j<ddj_num;j++)
			gp[i][j][1] = 9999999;
	//11.3 end
    for(int i=0;i<R;i++){
        r_arry[i] = 0;
        a[i] = 0;
    }
    for(int i=0;i<6;i++){
        T[i] = 0;
        TD[i] = 0;
    }
    for(int i=0;i<H;i++){
        th[i] = 0;
        hi[i][0]=9999;
        hi[i][1]=999999;
        I[i][0] = 0;
        I[i][1] = 0;
        INum[i][0] = 0;
        INum[i][1] = 0;
        g1_H2[i] = 0;
        g2_H2[i] = 0;
        g3_H2[i] = 0;
        g4_H2[i] = 0;
        g5_H2[i] = 0;
        g6_H2[i] = 0;
    }
    S_H(f);//�ͼ�ǰh-k�����룬�ؿ��h-k�����룬�γ�1-1��Ӧ��ϵ��
    check(f.getSequenceAddress(),s,h);
    get_R(f.getSequenceAddress());//�����������
    R_Test(r_arry);//����������ﵽ��Ѷ����ʱ�䣬��С��������
/*
	for(int i=0;i<R;i++){
		cout<<a[i]<<endl;
	}
	cout<<"---------"<<endl;
*/
    //cout<<endl;
    Storing_num(f);//�����ÿ̨�Ѷ�������������ͼ��������ؿ�����
    int g1_S[g1_s],g2_S[g2_s],g3_S[g3_s],g4_S[g4_s],g5_S[g5_s],g6_S[g6_s];//�ͼ�����ּ�6̨�Ѷ��
    int g1_H[g1_h],g2_H[g2_h],g3_H[g3_h],g4_H[g4_h],g5_H[g5_h],g6_H[g6_h];//�ؿ�����ּ�6̨�Ѷ��
    int g1_th[g1_h],g2_th[g2_h],g3_th[g3_h],g4_th[g4_h],g5_th[g5_h],g6_th[g6_h];//6̨�Ѷ���Ļؿ������ʱ��
    int g1[g1_n],g2[g2_n],g3[g3_n],g4[g4_n],g5[g5_n],g6[g6_n];//����ּ�6̨�Ѷ��

    for(int i=0;i<g1_h;i++){g1_th[i]=999999;g1_H2[i]=0;}
    for(int i=0;i<g2_h;i++){g2_th[i]=999999;g2_H2[i]=0;}
    for(int i=0;i<g3_h;i++){g3_th[i]=999999;g3_H2[i]=0;}
    for(int i=0;i<g4_h;i++){g4_th[i]=999999;g4_H2[i]=0;}
    for(int i=0;i<g5_h;i++){g5_th[i]=999999;g5_H2[i]=0;}
    for(int i=0;i<g6_h;i++){g6_th[i]=999999;g6_H2[i]=0;}

    Storing(f,g1,g2,g3,g4,g5,g6,g1_S,g2_S,g3_S,g4_S,g5_S,g6_S,g1_H,g2_H,g3_H,g4_H,g5_H,g6_H);//��ÿ̨�Ѷ���Ĺ������ͼ졢�ؿ��������ɲ�ͬ�����顣��18������
    //f.fitness=Fintess(f,g1,g2,g3,g4,g5,g6,g1_H,g2_H,g3_H,g4_H,g5_H,g6_H );
    f.setFitness(Fintess(f,g1,g2,g3,g4,g5,g6,g1_H,g2_H,g3_H,g4_H,g5_H,g6_H,g1_H2,g2_H2,g3_H2,g4_H2,g5_H2,g6_H2,g1_th,g2_th,g3_th,g4_th,g5_th,g6_th)); //������Ӧ��ֵ
//    f.fluorescein = (1-rou)*f.fluorescein + mgamma / f.fitness;

}

void enCode(Food *f) {
    //�����Լ��ķ����� ��ʼ��Ⱥ �е�ÿ��������н��룬�����Ŀ�꺯��
    //��д��һ������Ľ��룬��ѭ������
    for(int i=0;i<FoodsNum;i++){
        enSimpleCode(f[i]);
        //cout<<fly[0].G[1999];
    }
    // enSimpleCode(fly[0]);
    // enSimpleCode(fly[1]);
    // enSimpleCode(fly[2]);
}

void copyLink(LinkList L,LinkList &copyL) {
	copyL = new LNode;
	copyL->next = NULL;
	LNode* pL, * pCL, * p;
	pL = L->next;
	pCL = copyL;
	while (pL != NULL) {
		p = new LNode;
		p->data = pL->data;
		p->next = pCL->next;
		pCL->next = p;
		pCL = pCL->next;
		pL = pL->next;
	}
}

void linkToList(LinkList L,int G[NUMBER]) {//��ʽ�洢ת����˳��洢
	LNode * p;
	p = L->next;
	for (int i = 0; i < NUMBER; i++) {
		G[i] = p->data;
		p = p->next;
	}
}

void listToLink(firefly f,LinkList &L) { //˳��洢ת������ʽ�洢
	L = new LNode;
	L->next = NULL;
	LNode* pf;
	pf = L;
	pf->next = NULL;
	for (int i = 0; i < NUMBER; i++) {
		LNode* p;
		p = new LNode;
		p->data = f.G[i];
		p->next = pf->next;
		pf->next = p; //����Ľ��������
		pf = p;
		pf->next = p->next;
	}
}

void releasePoint(LinkList &L) {//�ͷ�L�ڴ�ռ�
	LNode* Lp1, * Lp2;
	Lp1 = L->next;
	Lp2 = L->next;
	while (Lp1 != NULL) {
		Lp1 = Lp2->next;
		delete Lp2;
		Lp2 = Lp1;
	}
	delete L;
}

void releaseRouteHead(LinkList &routeHead) {
	LinkList hd,hd2;
	hd = routeHead->head;
	hd2 = hd;
	LNode* Lp1, * Lp2;

	while (hd != NULL) {//����ͷ�ڵ�
		Lp1 = hd->next;
		Lp2 = hd->next;
		while (Lp1!=NULL) {//���ڿͻ��ڵ�
			Lp1 = Lp2->next;
			delete Lp2;
			Lp2 = Lp1;
		}
		hd = hd2->head;
		delete hd2;
		hd2 = hd;
	}
	delete routeHead;
}

int hammer_dis(int h1[NUMBER],int h2[NUMBER]) {
	int dis = NUMBER;
	for (int i = 0; i < NUMBER; i++) {
		if (h1[i] == h2[i]) dis--;
	}
	return dis;
}

double discode(int c1[],int c2[]) {//����֮���ƽ������
	double sum = 0;
	for (int i = 0; i < CODELENGTH; i++)
		sum = sum + dis[c1[i]][c2[i]];
	return sum / CODELENGTH;
}

int find(int arr[], int value) {
	int tag = 0;
	for (int i = 0; i < CODELENGTH; i++) {
		if (arr[i] == value) {
			tag = i;
			break;
		}
	}
	return tag;
}

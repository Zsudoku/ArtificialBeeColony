/*
 * @Date: 2022-02-20 15:17:20
 * @LastEditors: ZSudoku
 * @LastEditTime: 2022-04-10 10:31:29
 * @FilePath: \ArtificialBeeColony\source\test_ct.cpp
 */
#include<iostream>
#include"headers/head.h"
#include<fstream>
using namespace std;
// typedef struct P{
// 	float x;
// 	float y;
// 	float z;
// 	int id;
// 	double runtime;
// }Point;
// //A �� B ��
// //�ͼ�ؿ�ֻ����2�㣬������Ҫ���ǲ�����Ĺ���ʱ��
// typedef struct TP{
// 	float x;//��λ��x����
// 	float y;//��λ��y����
// 	float z;//��λ��z����
// 	int id;//��λ��Ψһ��ʶ
// 	int upPointCount;//�Ͻڵ������
// 	int downPointCount;//�½ڵ������
// 	Point upPoint[2];
// 	Point downPoint[2];
// 	char entityName[20]={0};
// }Traffic_Point;


// Traffic_Point traffic_point[] = {
// 	{1903.50, 0.71, 21.19,110,2,1,{{1903.51, 0.7, 19.49, 108, 68.23}, {1887.95, 0.7, 21.24, 109, 621.9}},{{1906.5, 0.71, 21.19, 107, 120.0}},"E��������46"},
// 	{1906.50, 0.71, 21.19,113,1,1,{{1903.5, 0.71, 21.19, 112, 120.0}},{{1906.5, 0.71, 23.98, 111, 111.28}},"E��������50"},
// 	{1906.5, 0.71, 23.98,111,1,1,{{1906.5, 0.71, 21.19 , 113, 111.28}},{{1906.5, 0.71, 52.2, 4, 1128.88}},"1�ŵ����"},
// 	{1906.50, 0.71, 52.2,5,1,1,{{1906.49, 0.71, 23.98, 4, 1128.88}},{{1905.88, 0.71, 52.2, 3, 24.6}},"F��������99"},
// 	{1905.88, 0.71, 52.2,51,1,1,{{1906.5, 0.71, 52.2, 50, 24.6}},{{1905.88, 0.71, 51.27, 49, 37.0}},"F��������56"},
// 	{1905.88, 0.71, 51.27,48,1,2,{{1905.88, 0.71, 52.2, 47, 37.0}},{{1902.9, 0.71, 51.27, 45, 119.36}, {1905.88, 0.71, 50.42, 46, 33.96}},"F��������57"},
// 	{1905.88, 0.71, 50.42,44,1,2,{{1905.88, 0.71, 51.27, 43, 33.96}},{{1902.9, 0.71, 50.42, 41, 119.36}, {1905.88, 0.71, 48.56, 42, 74.56}},"F��������58"},
// 	{1902.90, 0.71, 51.27,54,1,1,{{1905.88, 0.71, 51.27, 53, 119.36}},{{1902.25, 0.71, 51.27, 52, 25.84}},"F��������52"},
// 	{1905.88, 0.71, 48.56,40,1,2,{{1905.88, 0.71, 50.42, 39, 74.56}},{{1902.9, 0.71, 48.54, 37, 119.36}, {1905.88, 0.71, 47.7, 38, 34.52}},"F��������60"},
// 	{1905.88, 0.71, 38.41,12,1,2,{{1905.88, 0.71, 40.33, 11, 76.48}},{{1902.9, 0.71, 38.43, 9, 119.36}, {1905.88, 0.71, 36.53, 10, 75.44}},"F��������71"},
// 	{1905.88, 0.71, 36.53,8,1,1,{{1905.88, 0.71, 38.41, 7, 75.44}},{{1902.9, 0.71, 36.52, 6, 119.36}},"F��������73"},
// 	{1905.88, 0.71, 40.33,16,1,2,{{1905.88, 0.71, 42.23, 15, 76.24}},{{1902.9, 0.71, 40.34, 13, 119.36}, {1905.88, 0.71, 38.41, 14, 76.48}},"F��������69"},
// 	{1905.88, 0.71, 42.23,20,1,2,{{1905.88, 0.71, 43.09, 19, 34.36}},{{1902.9, 0.71, 42.23, 17, 119.36}, {1905.88, 0.71, 40.33, 18, 76.24}},"F��������67"},
// 	{1905.88, 0.71, 43.09,24,1,2,{{1905.88, 0.71, 44.96, 23, 74.6}},{{1902.25, 0.71, 43.08, 21, 145.2}, {1905.88, 0.71, 42.23, 22, 34.36}},"F��������66"},
// 	{1905.88, 0.71, 44.96,28,1,2,{{1905.88, 0.71, 45.82, 27, 34.76}},{{1902.9, 0.71, 44.96, 25, 119.36}, {1905.88, 0.71, 43.09, 26, 74.6}},"F��������64"},
// 	{1905.88, 0.71, 45.82,32,1,2,{{1905.88, 0.71, 47.7, 31, 74.88}},{{1902.9, 0.71, 45.81, 29, 119.36}, {1905.88, 0.71, 44.96, 30, 34.76}},"F��������63"},
// 	{1905.88, 0.71, 47.7,36,1,2,{{1905.88, 0.71, 48.56, 35, 34.52}},{{1902.9, 0.71, 47.69, 33, 119.36}, {1905.88, 0.71, 45.82, 34, 74.88}},"F��������61"},
// 	{1902.25, 0.71, 51.27,56,1,0,{{1902.9, 0.71, 51.27, 55, 25.84}},{},"F��������51"},
// 	{1902.90, 0.71, 50.42,59,1,1,{{1905.88, 0.71, 50.42, 58, 119.36}},{{1902.25, 0.71, 50.42, 57, 25.84}},"F��������49"},
// 	{1902.25, 0.71, 50.42,61,1,0,{{1902.9, 0.71, 50.42, 60, 25.84}},{},"F��������50"},
// 	{1902.90, 0.71, 48.54,64,1,1,{{1905.88, 0.71, 48.56, 63, 119.36}},{{1902.25, 0.71, 48.54, 62, 25.84}},"F��������42"},
// 	{1902.25, 0.71, 48.54,66,1,0,{{1902.9, 0.71, 48.54, 65, 25.84}},{},"F��������41"},
// 	{1902.90, 0.71, 47.69,69,1,1,{{1905.88, 0.71, 47.7, 68, 119.36}},{{1902.25, 0.71, 47.69, 67, 25.84}},"F��������39"},
// 	{1902.25, 0.71, 47.69,71,1,0,{{1902.9, 0.71, 47.69, 70, 25.84}},{},"F��������40"},
// 	{1902.90, 0.71, 45.81,74,1,1,{{1905.88, 0.71, 45.82, 73, 119.36}},{{1902.25, 0.71, 45.81, 72, 25.84}},"F��������32"},
// 	{1902.25, 0.71, 45.81,76,1,0,{{1902.9, 0.71, 45.81, 75, 25.84}},{},"F��������31"},
// 	{1902.90, 0.71, 44.96,79,1,1,{{1905.88, 0.71, 44.96, 78, 119.36}},{{1902.25, 0.71, 44.96, 77, 25.84}},"F��������29"},
// 	{1902.25, 0.71, 44.96,81,1,0,{{1902.9, 0.71, 44.96, 80, 25.84}},{},"F��������30"},
// 	{1902.90, 0.71, 43.08,84,1,1,{{1905.88, 0.71, 43.09, 83, 119.36}},{{1902.25, 0.71, 43.08, 82, 25.84}},"F��������22"},
// 	{1902.25, 0.71, 43.08,86,1,0,{{1902.9, 0.71, 43.08, 85, 25.84}},{},"F��������21"},
// 	{1902.90, 0.71, 42.23,89,1,1,{{1905.88, 0.71, 42.23, 88, 119.36}},{{1902.25, 0.71, 42.23, 87, 25.84}},"F��������19"},
// 	{1902.25, 0.71, 42.23,91,1,0,{{1902.9, 0.71, 42.23, 90, 25.84}},{},"F��������20"},
// 	{1902.90, 0.71, 40.34,94,1,1,{{1905.88, 0.71, 40.33, 93, 119.36}},{{1902.25, 0.71, 40.34, 92, 25.84}},"F��������12"},
// 	{1902.25, 0.71, 40.34,96,1,0,{{1902.9, 0.71, 40.34, 95, 25.84}},{},"F��������11"},
// 	{1902.90, 0.71, 38.43,99,1,1,{{1905.88, 0.71, 38.41, 98, 119.36}},{{1902.25, 0.71, 38.43, 97, 25.84}},"F��������9"},
// 	{1902.25, 0.71, 38.43,101,1,0,{{1902.9, 0.71, 38.43, 100, 25.84}},{},"F��������10"},
// 	{1902.90, 0.71, 36.52,104,1,1,{{1905.88, 0.71, 36.53, 103, 119.36}},{{1902.25, 0.71, 36.52, 102, 25.84}},"F��������2"},
// 	{1902.25, 0.71, 36.52,106,1,0,{{1902.9, 0.71, 36.52, 105, 25.84}},{},"F��������1"}
// };

// void sort_ct(){
//     for(int i = 0;i < 38;i++ ){
//         for(int j = 0;j < 38;j++){
//             if(traffic_point[i].downPointCount > 0 && i != j){
//                 if(traffic_point[i].downPoint[0].x == traffic_point[j].x && traffic_point[i].downPoint[0].y == traffic_point[j].y && traffic_point[i].downPoint[0].z == traffic_point[j].z){
//                     cout<<traffic_point[i].entityName<<"->"<<traffic_point[j].entityName<<endl;
//                 }
//             }
//         }
//     }
    
    
// }

int main(){
	ofstream mainout;
    mainout.open("output/testLine.txt"); 
    
    //sort_ct();
	int s[200];
	int r[200];
	int h[200];
	int c[200];
	int s1 = 0,r1 = 0,h1 = 0,c1 = 0;
	for(int i=1;i<801;i++){
		if(cargo_now[i-1].s1==0 && cargo_now[i-1].s2==0){
			r[r1++] = i;
		}
		else if(cargo_now[i-1].s1==0 && cargo_now[i-1].s2==1){
			s[s1++] = i;
		}
		else if(cargo_now[i-1].s1==1 && cargo_now[i-1].s2==0){
			h[h1++] = i;
		}
		else if(cargo_now[i-1].s1==1 && cargo_now[i-1].s2==1){
			c[c1++] = i;
		}
		else{
			cout<<cargo_now[i-1].id<<" error!"<<endl;
		}
	}
	for(int i=0;i<200;i++){
		mainout<<s[i]<<',';
	}
	//cout<<endl;
	for(int i=0;i<200;i++){
		mainout<<r[i]<<',';
	}
	//cout<<endl;
	for(int i=0;i<200;i++){
		mainout<<c[i]<<',';
	}
	//cout<<endl;
	for(int i=0;i<200;i++){
		mainout<<h[i]<<',';
	}
	mainout<<endl;
	mainout.close();
    system("pause");
    return 0;
}
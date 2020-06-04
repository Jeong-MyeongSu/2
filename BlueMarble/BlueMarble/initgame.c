#include "BMherder.h"


int pnum = 2;
int dice1, dice2;
int expocount = 1;

point playerxy[4][40] = {
	{{4,43},{4,39},{4,35},{4,31},{4,27},{4,23},{4,19},{4,15},{4,11},{4,7},{4,3},{12,3},{20,3},{28,3},{36,3},{44,3},{52,3},{60,3},{68,3},{76,3},{84,3},{84,7},{84,11},{84,15},{84,19},{84,23},{84,27},{84,31},{84,35},{84,39},{84,43},{76,43},{68,43},{60,43},{52,43},{44,43},{36,43},{28,43},{20,43},{12,43}},
	{{6,43},{6,39},{6,35},{6,31},{6,27},{6,23},{6,19},{6,15},{6,11},{6,7},{6,3},{14,3},{22,3},{30,3},{38,3},{46,3},{54,3},{62,3},{70,3},{78,3},{86,3},{86,7},{86,11},{86,15},{86,19},{86,23},{86,27},{86,31},{86,35},{86,39},{86,43},{78,43},{70,43},{62,43},{54,43},{46,43},{38,43},{30,43},{22,43},{14,43}},
	{{4,44},{4,40},{4,36},{4,32},{4,28},{4,24},{4,20},{4,16},{4,12},{4,8},{4,4},{12,4},{20,4},{28,4},{36,4},{44,4},{52,4},{60,4},{68,4},{76,4},{84,4},{84,8},{84,12},{84,16},{84,20},{84,24},{84,28},{84,32},{84,36},{84,40},{84,44},{76,44},{68,44},{60,44},{52,44},{44,44},{36,44},{28,44},{20,44},{12,44}},
	{{6,44},{6,40},{6,36},{6,32},{6,28},{6,24},{6,20},{6,16},{6,12},{6,8},{6,4},{14,4},{22,4},{30,4},{38,4},{46,4},{54,4},{62,4},{70,4},{78,4},{86,4},{86,8},{86,12},{86,16},{86,20},{86,24},{86,28},{86,32},{86,36},{86,40},{86,44},{78,44},{70,44},{62,44},{54,44},{46,44},{38,44},{30,44},{22,44},{14,44}}
};
land landinfo[40] = {
	{0,0,0,0,0,0,0,0,1,0}, {0,2,0,5,0,9,0,0,1,0},{0,0,0,0,0,0,0,0,1,0},{0,3,0,7,0,12,0,0,1,0},{0,0,0,0,0,0,0,0,1,0},{0,0,0,0,0,0,0,0,1,15},{0,5,0,11,0,18,0,0,1,0},{0,4,0,0,0,0,0,0,1,0},{0,6,0,13,0,20,0,0,1,0},{0,7,0,15,0,24,0,0,1,0},{0,0,0,0,0,0,0,0,1,0},{0,8,0,17,0,27,0,0,1,0},{0,9,0,19,0,30,0,0,1,0},{0,0,0,0,0,0,0,0,1,0},{0,10,0,21,0,32,0,0,1,0},{0,0,0,0,0,0,0,0,1,15},{0,11,0,23,0,36,0,0,1,0},{0,12,0,25,0,39,0,0,1,0},{0,0,0,0,0,0,0,0,1,0},{0,13,0,27,0,44,0,0,1,0},{0,0,0,0,0,0,0,0,1,0},{0,15,0,31,0,43,0,0,1,0},{0,0,0,0,0,0,0,0,1,0},{0,16,0,33,0,46,0,0,1,0},{0,17,0,35,0,49,0,0,1,0},{0,0,0,0,0,0,0,0,1,15},{0,18,0,37,0,52,0,0,1,0},{0,0,0,0,0,0,0,0,1,0},{0,19,0,39,0,55,0,0,1,0},{0,20,0,41,0,58,0,0,1,0},{0,0,0,0,0,0,0,0,1,0},{0,21,0,41,0,61,0,0,1,0},{0,22,0,43,0,64,0,0,1,0},{0,4,0,0,0,0,0,0,1,0},{0,23,0,45,0,67,0,0,1,0},{0,0,0,0,0,0,0,0,1,15},{0,0,0,0,0,0,0,0,1,0},{0,25,0,50,0,75,0,0,1,0},{0,0,0,0,0,0,0,0,1,0},{0,30,0,75,0,100,0,0,1,0}
};
info playerinfo[4] = { {0,0,0,0,0,0,0},{0,0,0,0,0,0,0},{0,0,0,0,0,0,0}, {0,0,0,0,0,0,0} }; 

buy buyselect[28] = { {0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "},{0,"      "} }; //ù�ڸ��� ����� �����ض� ����� ������

char* p[] = { "Start ", "������", "��  ��", "��  ��", "��  ��", "���ѻ�", "��  ��", "���� 1", "��  ��", "��  ��", "���ε�",  "��  ��", "��  ��", "��  ��", "��  õ", "���ǻ�", "û  ��", "õ  ��", "��  ��", "��  ��", "������", "��  ��", "��  ��", "��  ��", "��  ��", "������", "��  ��", "��  ��", "��  ��", "��  ��", "��  ��", "��  õ", "��  ��", "���� 2", "��  ��", "�Ѷ��", "��  ��", "��  ��", "��  ��", "��  ��" };

void InitGame() {



	

	

}
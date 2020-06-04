#include "BMherder.h"

point playerxy[4][40];
land landinfo[40];
info playerinfo[4];
buy buyselect[28];

extern pnum;
extern dice1, dice2;
extern *p[];
extern expocount;

int diecount = 0;

void playGame() {
	int ch;
	
	gotoxy(1, 51); puts("���� �ο��� ���� �ϼ��� ��   ��");
	gotoxy(28, 51); printf("%d", pnum);
	
	int flag = 1;
	while(flag) {
		ch = getch();
		if (ch == 0xE0 || ch == 0) {
			ch = getch();
			switch (ch) {
			case LEFT:
				if (pnum > 2) {
					pnum--;
				}
				gotoxy(28, 51); printf("%d", pnum);
				break;
			case RIGHT:
				if (pnum < 4) {
					pnum++;
				}
				gotoxy(28, 51); printf("%d", pnum);
				break;
			}
		}
		else {
			switch (ch) {
			case ' ':
				flag = 0;
				break;
			}
		}
	}
	if (pnum == 2) {
		UpdateCash(1, 400);
		UpdateCash(2, 400);
	}
	else if (pnum == 3) {
		UpdateCash(1, 350);
		UpdateCash(2, 350);
		UpdateCash(3, 350);
	}
	else {
		UpdateCash(1, 300);
		UpdateCash(2, 300);
		UpdateCash(3, 300);
		UpdateCash(4, 300);
	}
	printPlayer();
	printUserBox();
	
	for (int i = 0; i <= Maxturn; i++) {
		gotoxy(52, 13);  printf("%d ", Maxturn - i);
		if (pnum == 2) { 
			if (playerinfo[0].die == 0) {
				Player(1, playerinfo[0].cash);
			}
			if (playerinfo[1].die == 0) {
				Player(2, playerinfo[1].cash);
			}
			if (diecount == 1) {
				for (int j = 0; j < 2; j++) {
					if (playerinfo[j].die == 0) {
						gotoxy(40, 13);  printf("�����մϴ� %dp �¸��Դϴ�. ", j+1);
						gotoxy(40, 14);  printf("                           ");
						gotoxy(40, 51);  printf("                                      ");
						exit(0);
					}
				}
			}
		}
		else if (pnum == 3) {
			if (playerinfo[0].die == 0) {
				Player(1, playerinfo[0].cash);
			}
			if (playerinfo[1].die == 0) {
				Player(2, playerinfo[1].cash);
			}
			if (playerinfo[2].die == 0) {
				Player(3, playerinfo[2].cash);
			}
			if (diecount == 2) {
				for (int j = 0; j < 3; j++) {
					if (playerinfo[j].die == 0) {
						gotoxy(40, 13);  printf("�����մϴ� %dp �¸��Դϴ�. ", j + 1);
						gotoxy(40, 14);  printf("                           ");
						gotoxy(40, 51);  printf("                                      ");
						exit(0);
					}
				}
			}
			
		}
		else {
			if (playerinfo[0].die == 0) {
				Player(1, playerinfo[0].cash);
			}
			if (playerinfo[1].die == 0) {
				Player(2, playerinfo[1].cash);
			}
			if (playerinfo[2].die == 0) {
				Player(3, playerinfo[2].cash);
			}
			if (playerinfo[3].die == 0) {
				Player(4, playerinfo[3].cash);
			}
			if (diecount == 3) {
				for (int j = 0; j < 4; j++) {
					if (playerinfo[j].die == 0) {
						gotoxy(40, 13);  printf("�����մϴ� %dp �¸��Դϴ�. ", j + 1);
						gotoxy(40, 14);  printf("                           ");
						gotoxy(40, 51);  printf("                                      ");
						exit(0);
					}
				}
			}
		}
	}
	//���� ���� �ڻ� �¸�
	if (playerinfo[0].asset > playerinfo[1].asset && playerinfo[0].asset > playerinfo[2].asset && playerinfo[0].asset > playerinfo[3].asset) {
		gotoxy(40, 13);  printf("�����մϴ� %dp �¸��Դϴ�. ", 0 + 1);
		gotoxy(40, 14);  printf("                           ");
		gotoxy(40, 51);  printf("                                      ");
		exit(0);
	}
	if (playerinfo[1].asset > playerinfo[0].asset && playerinfo[1].asset > playerinfo[2].asset && playerinfo[1].asset > playerinfo[3].asset) {
		gotoxy(40, 13);  printf("�����մϴ� %dp �¸��Դϴ�. ", 1 + 1);
		gotoxy(40, 14);  printf("                           ");
		gotoxy(40, 51);  printf("                                      ");
		exit(0);
	}
	if (playerinfo[2].asset > playerinfo[0].asset && playerinfo[2].asset > playerinfo[1].asset && playerinfo[2].asset > playerinfo[3].asset) {
		gotoxy(40, 13);  printf("�����մϴ� %dp �¸��Դϴ�. ", 2 + 1);
		gotoxy(40, 14);  printf("                           ");
		gotoxy(40, 51);  printf("                                      ");
		exit(0);
	}
	if (playerinfo[3].asset > playerinfo[0].asset && playerinfo[3].asset > playerinfo[1].asset && playerinfo[3].asset > playerinfo[1].asset) {
		gotoxy(40, 13);  printf("�����մϴ� %dp �¸��Դϴ�. ", 3 + 1);
		gotoxy(40, 14);  printf("                           ");
		gotoxy(40, 51);  printf("                                      ");
		exit(0);
	}


}

void Player(int player , int cash) { //�÷��̾ �ֻ����� ������ �̵��ϴ� �Լ�, ���ε����� �������������� Ȯ���Ͽ� �����δ�.
	gotoxy(42, 14); printf("%dp �� �Դϴ�", player);
	if (playerinfo[player-1].tflag == 0) { //���� �������� Ȯ�� ���������̸� 1 �ƴϸ� 0
		ThrowDice();
		if (playerinfo[player - 1].unisland == 0 || dice1 == dice2) { // ���ε����� Ȯ�� ���ε��� �ƴϸ� 0, �����̸� ���ε� ��������
			MovePlayer(player);
			playerinfo[player - 1].unisland = 0;
			GetEvent(player, playerinfo[player-1].position);
		}
		else if (playerinfo[player - 1].unisland == 1) {
			gotoxy(1, 51); printf("���ε� ��.                            ");
			delay(500);
			playerinfo[player - 1].unisland = 0;
		}
		else {
			(playerinfo[player - 1].unisland)--;
			gotoxy(1, 51); printf("%d �� ���ҽ��ϴ�.                     ", playerinfo[player - 1].unisland);
			delay(500);
		}
	}
	else if (playerinfo[player - 1].tflag == 1 && cash >= 20) {
		GetTrain(player);
		GetEvent(player, playerinfo[player - 1].position);
	}
	else {
		gotoxy(1, 51); printf("�������� �� ������ �����մϴ�         ");
		playerinfo[player - 1].tflag = 0;
		delay(500);
		ThrowDice();
		MovePlayer(player);
		GetEvent(player, playerinfo[player - 1].position);
	}
}

void ThrowDice() { //�ֻ��� ������ �Լ�
	int ch;
	int flag = 1;
	

	gotoxy(1, 51); puts("�����̽��ٸ� ���� �ֻ����� ��������.  ");
	
	while (flag) {
		ch = getch();
		if (ch == 0xE0 || ch == 0) {
			ch = getch();
		}
		else {
			if (IsKeyDown(VK_SPACE)) {
				//dice1 = random(dice)+1;
				//dice2 = random(dice)+1;
				dice1 = random(dice)+1;
				dice2 = random(dice)+1;
					
				flag = 0;
			}
		}
	}
	
	gotoxy(1, 51); printf("%d, %d                                  ", dice1, dice2);
	delay(2000);
}
void MovePlayer(int player) { //�÷��̾ �����̴� �Լ� �ѹ��� ���� ���� �޴°͵� ������

	gotoxy(playerxy[player-1][playerinfo[player - 1].position].x, playerxy[player-1][playerinfo[player - 1].position].y); puts("  ");
	playerinfo[player - 1].position = playerinfo[player - 1].position + (dice1 + dice2);
	if (playerinfo[player - 1].position >= 40) {
		playerinfo[player - 1].position = playerinfo[player - 1].position - 40;
		UpdateCash(player, 30);
	}
	gotoxy(playerxy[player-1][playerinfo[player - 1].position].x, playerxy[player-1][playerinfo[player - 1].position].y);
	if (player == 1) {
		setColor(RED); puts("��");
	}
	else if (player == 2) {
		setColor(BLUE); puts("��");
	}
	else if (player == 3) {
		setColor(YELLOW); puts("��");
	}
	else {
		setColor(GREEN); puts("��");
	}
	setColor(WHITE);
	delay(500);
}

void GetEvent(int player, int position) { //�̺�Ʈ �߻� �Լ� ���ε�, ��������, ������, ����, ��, ���� ������ �̺�Ʈ �߻��ϰ� ����
	int revent;
	int pn;
	int i;
	int mountain = 0;
	int landcount = 0;
	if (position == 30) {
		playerinfo[player - 1].tflag = 1;
		gotoxy(101, 45); printf("��������             ");
		gotoxy(101, 46); printf("���� �Ͽ� 20 �� ���� ");
		gotoxy(101, 47); printf("�ϰ� ���ϴ� ������   ");
		gotoxy(101, 48); printf("�̵��Ѵ�             ");
		gotoxy(101, 49); printf("                     ");
	}
	if (position == 10 && playerinfo[player - 1].unisland == 0) {
		playerinfo[player - 1].unisland = 3;
		gotoxy(101, 45); printf("���ε�               ");
		gotoxy(101, 46); printf("������ ������ ������ ");
		gotoxy(101, 47); printf("3�ϵ��� �̵��Ҽ� ����");
		gotoxy(101, 48); printf("                     ");
		gotoxy(101, 49); printf("                     ");
	}
	if (position == 1 || position == 3 || position == 6 || position == 8 || position == 9 || position == 11 || position == 12 || position == 14 || position == 16 || position == 17 || position == 19 || position == 21 || position == 23 || position == 24 || position == 26 || position == 28 || position == 29 || position == 31 || position == 32 || position == 34 || position == 37 || position == 39) {
		if (landinfo[position].property == 0) {
			gotoxy(101, 45); printf("������ ���� �� ��    ");
			gotoxy(101, 46); printf("���� : %d            ", landinfo[position].vacationhome);
			gotoxy(101, 47); printf("���� : %d            ", landinfo[position].building);
			gotoxy(101, 48); printf("ȣ�� : %d            ", landinfo[position].hotel);
			gotoxy(101, 49); printf("�� �ݾ� : %d         ", (landinfo[position].vacationhome) + (landinfo[position].building) + (landinfo[position].hotel));
		}
		else if(landinfo[position].property == player){
			gotoxy(101, 45); printf("�ڽ��� �� �Դϴ�.    ");
			gotoxy(101, 46); printf("���� : %d            ", landinfo[position].vacationhome); 
			if (landinfo[position].vhflag == 1) { gotoxy(112, 46); printf("(o)");}
			else { gotoxy(112, 46); printf("(x)"); }
			gotoxy(101, 47); printf("���� : %d            ", landinfo[position].building);     
			if (landinfo[position].bdflag == 1) { gotoxy(112, 47); printf("(o)"); }
			else { gotoxy(112, 47); printf("(x)"); }
			gotoxy(101, 48); printf("ȣ�� : %d            ", landinfo[position].hotel);		 
			if (landinfo[position].htflag == 1) { gotoxy(112, 48); printf("(o)"); }
			else { gotoxy(112, 48); printf("(x)"); }
			gotoxy(101, 49); printf("�� �ݾ� : %d(%d)    ", (landinfo[position].vacationhome) + (landinfo[position].building) + (landinfo[position].hotel), (landinfo[position].vacationhome * landinfo[position].vhflag) + (landinfo[position].building * landinfo[position].bdflag) + (landinfo[position].hotel * landinfo[position].htflag));
		}
		else {
			gotoxy(101, 45); printf("%dp ������ �� �Դϴ�.",landinfo[position].property);
			gotoxy(101, 46); printf("���� : %d            ", landinfo[position].vacationhome * landinfo[position].vhflag);
			gotoxy(101, 47); printf("���� : %d            ", landinfo[position].building * landinfo[position].bdflag);
			gotoxy(101, 48); printf("ȣ�� : %d            ", landinfo[position].hotel * landinfo[position].htflag);
			gotoxy(101, 49); printf("�� �ݾ� : %d         ", (landinfo[position].vacationhome * landinfo[position].vhflag) + (landinfo[position].building * landinfo[position].bdflag) + (landinfo[position].hotel * landinfo[position].htflag));
		}
		TreadLand(player, playerinfo[player-1].position, playerinfo[player-1].cash);
	}
	if (position == 7 || position == 33) {
		if (landinfo[position].property == 0) {
			gotoxy(101, 45); printf("������ ���� �� ����  ");
			gotoxy(101, 46); printf("������ ���� ����     ");
			gotoxy(101, 47); printf("������ ������.       ");
			gotoxy(101, 48); printf("                     ");
			gotoxy(101, 49); printf("                     ");
			landinfo[position].pd = 0;
		}
		else if (landinfo[position].property == player) {
			gotoxy(101, 45); printf("�ڽ� �� ���� �Դϴ�  ");
			gotoxy(101, 46); printf("���� : %d            ", landinfo[position].vacationhome * landinfo[position].vhflag * landinfo[position].pd);
			gotoxy(101, 47); printf("������ ���� ����     ");
			gotoxy(101, 48); printf("������ ������.       ");
			gotoxy(101, 49); printf("x%d                  ",landinfo[position].pd);
		}
		else {
			gotoxy(101, 45); printf("%dp �� ���� �Դϴ�   ", landinfo[position].property);
			gotoxy(101, 46); printf("���� : %d            ", landinfo[position].vacationhome * landinfo[position].vhflag * landinfo[position].pd);
			gotoxy(101, 47); printf("������ ���� ����     ");
			gotoxy(101, 48); printf("������ ������.       ");
			gotoxy(101, 49); printf("x%d                  ", landinfo[position].pd+1);
		}
		if (landinfo[position].property > 0) {
			landinfo[position].pd += 1;
		}
		TreadPark(player, position, playerinfo[player - 1].cash);
	}
	if (position == 5 || position == 15 || position == 25 || position == 35) {
		if (landinfo[position].property == 0) {
			gotoxy(101, 45); printf("������ ���� �� ��    ");
			gotoxy(101, 46); printf("���� ���� ���� �ϰ�  ");
			gotoxy(101, 47); printf("���� ���� ������     ");
			gotoxy(101, 48); printf("������               ");
			gotoxy(101, 49); printf("�ݾ� : 15            ");
		}
		else if (landinfo[position].property == player) {
			gotoxy(101, 45); printf("�ڽ� �� ��   �Դϴ�  ");
			gotoxy(101, 46); printf("���� ���� ���� �ϰ�  ");
			gotoxy(101, 47); printf("���� ���� ������     ");
			gotoxy(101, 48); printf("������               ");
			gotoxy(101, 49); printf("                     ");
		}
		else {
			gotoxy(101, 45); printf("%dp �� ��   �Դϴ�   ", landinfo[position].property);
			for (i = 0; i < 40; i++) {
				if (landinfo[i].property == landinfo[position].property) {
					mountain += landinfo[i].mountain;
				}
			}
			gotoxy(101, 46); printf("���� : %d            ", mountain);
			gotoxy(101, 47); printf("���� ���� ���� �ϰ�  ");
			gotoxy(101, 48); printf("���� ���� ������     ");
			gotoxy(101, 49); printf("������               ");
		}
		TreadMountain(player, position, playerinfo[player - 1].cash);
	}
	if (position == 20) {
		gotoxy(101, 45); printf("������               ");
		gotoxy(101, 46); printf("���ϴ� ���� �������� ");
		gotoxy(101, 47); printf("�����Ͽ� ������      ");
		gotoxy(101, 48); printf("�ø���.              ");
		gotoxy(101, 49); printf("                     ");
		if (playerinfo[player - 1].cash >= 10 ) {
			for (i = 0; i < 40; i++) {
				if (i != 5 && i != 15 && i != 25 && i != 35 && i != 7 && i != 33) {
					if (landinfo[i].property == player) {
						landcount++;
					}
				}
		
			}
			if (landcount == 0) {
				gotoxy(1, 51); puts("������ ������ ���̾����ϴ�.           ");
			}
			else {
				UpdateCash(player, -10);
				Expo(player, position);
				expocount++;
				for (i = 0; i < 40; i++) {
					if (landinfo[i].expo != 1) {
						gotoxy(60, 6); printf("������ ���� : %s", p[i]);
						gotoxy(60, 7); printf("x%d", expocount);
					}
				}
			}
		}
		else {
			gotoxy(1, 51); puts("������ ������ ���� �����մϴ�.        ");
			delay(1000);
		}
	}
	if (position == 2 || position == 4 || position == 13 || position == 18 || position == 22 || position == 27 || position == 36 || position == 38) {
		gotoxy(101, 45); printf("��  ��               ");
		gotoxy(101, 46); printf("�����ϰ� �̵��Ѵ�    ");
		gotoxy(101, 47); printf("1~6ĭ �յ�, ���ε�,  ");
		gotoxy(101, 48); printf("������, ������ ����  ");
		gotoxy(101, 49); printf("                     ");
		revent = random(10) + 1; // 1~9 ���� 1~6 �̵� 7���ε� 8������ 9���� 10 �����
		pn = random(2) + 1;//1������ + 2������ -
		GetRandom(revent, pn, player);
		GetEvent(player, playerinfo[player - 1].position);
	}
}

void GetTrain(int player) { //�������� �̵� �Լ�
		UpdateCash(player, -20);
		int ch, flag, num;
		gotoxy(1, 51); puts("�̵��� ��ġ�� �����ϼ��� ��         ��");
		gotoxy(29, 51); printf("%s", p[0]);

		flag = 1;
		num = 0;
		while (flag) {
			ch = getch();
			if (ch == 0xE0 || ch == 0) {
				ch = getch();
				switch (ch) {
				case LEFT:
					if (num > 31) {
						num--;
					}
					else if (num == 31) {
						num = num - 2;
					}
					else if (num <= 29 && num >= 1) {
						num--;
					}
					else {
						num = 39;
					}
					gotoxy(29, 51); printf("%s", p[num]);
					break;
				case RIGHT:
					if (num < 29) {
						num++;
					}
					else if (num == 29) {
						num = num + 2;
					}
					else if (num >= 31 && num < 39) {
						num++;
					}
					else {
						num = 0;
					}
					gotoxy(29, 51); printf("%s", p[num]);
					break;
				}
			}
			else {
				if (IsKeyDown(VK_SPACE)) {
					flag = 0;
				}
			}
		}
		gotoxy(playerxy[player - 1][playerinfo[player-1].position].x, playerxy[player - 1][playerinfo[player - 1].position].y); puts("  ");
		playerinfo[player - 1].position = num;
		if (playerinfo[player - 1].position >= 0 && playerinfo[player - 1].position <= 29) {
			UpdateCash(player, 30);
		}
		playerinfo[player-1].tflag = 0;
		gotoxy(playerxy[player - 1][playerinfo[player - 1].position].x, playerxy[player - 1][playerinfo[player - 1].position].y);
		if (player == 1) {
			setColor(RED); puts("��");
		}
		else if (player == 2) {
			setColor(BLUE); puts("��");
		}
		else if (player == 3) {
			setColor(YELLOW); puts("��");
		}
		else {
			setColor(GREEN); puts("��");
		}

		setColor(WHITE);
		delay(500);
}

void GetRandom(int revent, int pn, int player) { //���� �̺�Ʈ ������� ���� ������ �޾� ��ĭ �̵��� Ư������ �̵��� ����(�غ��� ��������;)
	if (revent >= 1 && revent <=6 && pn == 1) {
		gotoxy(15, 40); printf("%d ĭ ������                          ",revent);
		delay(500);
		RandomMovePlayer(player, revent, 1);
		delay(500);
	}
	else if (revent >= 1 && revent <= 6 && pn == 2) {
		gotoxy(15, 40); printf("%d ĭ �ڷ�                            ", revent);
		delay(500);
		RandomMovePlayer(player, revent, -1);
		delay(500);
	}
	if (revent >= 7) {
		delay(500);
		RandomMovePlayer(player, revent, 1);
		delay(500);
	}
	
	
}

void RandomMovePlayer(int player,int revent, int pn) {  //���� �̺�Ʈ ������� ���� ������ �޾� �̵� ���� �Լ�
	
	gotoxy(playerxy[player-1][playerinfo[player - 1].position].x, playerxy[player-1][playerinfo[player - 1].position].y); puts("  ");
	if (revent >= 1 && revent <= 6) {
		playerinfo[player - 1].position = playerinfo[player - 1].position + revent * pn;
		if (playerinfo[player - 1].position >= 40) {
			playerinfo[player - 1].position = playerinfo[player - 1].position - 40;

			UpdateCash(player, 30);
		}
		if (playerinfo[player - 1].position == 0) {
			UpdateCash(player, 30);
		}
		if (playerinfo[player - 1].position < 0) {
			playerinfo[player - 1].position = 40 + playerinfo[player - 1].position;
		}
	}
	else if (revent == 7) {
		gotoxy(15, 40); printf("���ε��� ���ÿ�.                      ");
		if (playerinfo[player - 1].position == 13 || playerinfo[player - 1].position == 18 || playerinfo[player - 1].position == 22 || playerinfo[player - 1].position == 27 || playerinfo[player - 1].position == 36 || playerinfo[player - 1].position == 38) {
			UpdateCash(player, 30);
		}
		playerinfo[player - 1].position = 10;
	}
	else if (revent == 8) {
		gotoxy(15, 40); printf("�������� ���ÿ�.                      ");
		if (playerinfo[player - 1].position == 22 || playerinfo[player - 1].position == 27 || playerinfo[player - 1].position == 36 || playerinfo[player - 1].position == 38) {
			UpdateCash(player, 30);
		}
		playerinfo[player - 1].position = 20;
	}
	else if (revent == 9) {
		gotoxy(15, 40); printf("������������ ���ÿ�                   ");
		if (playerinfo[player - 1].position == 36 || playerinfo[player - 1].position == 38) {
			UpdateCash(player, 30);
		}
		playerinfo[player - 1].position = 30;
	}
	else {
		gotoxy(15, 40); printf("������� ���ÿ�.(+30)                 ");
		playerinfo[player - 1].position = 0;
		UpdateCash(player, 30);
	}
	gotoxy(playerxy[player-1][playerinfo[player - 1].position].x, playerxy[player-1][playerinfo[player - 1].position].y);
	if (player == 1) {
		setColor(RED); puts("��");
	}
	else if (player == 2) {
		setColor(BLUE); puts("��");
	}
	else if (player == 3) {
		setColor(YELLOW); puts("��");
	}
	else {
		setColor(GREEN); puts("��");
	}
	setColor(WHITE);
	delay(500);
}

void TreadLand(int player, int position, int cash) {   //���ø� ������� �̺�Ʈ �Լ�
	int ch, flag, num;
	num = 1;
	flag = 1;
	
	if (landinfo[position].property == 0) {
		gotoxy(1, 51); printf("���� ���� �Ͻðڽ��ϱ�?  ��        �� ");
		gotoxy(30, 51); printf("YES");
		while (flag) {
			ch = getch();
			if (ch == 0xE0 || ch == 0) {
				ch = getch();
				switch (ch) {
				case LEFT:
					num = num * (-1);
					if (num == 1) {
						gotoxy(30, 51); printf("YES");
					}
					else {
						gotoxy(30, 51); printf("N O");
					}
					break;
				case RIGHT:
					num = num * (-1);
					if (num == 1) {
						gotoxy(30, 51); printf("YES");
					}
					else {
						gotoxy(30, 51); printf("N O");
					}
					break;
				}
			}
			else {
				if (IsKeyDown(VK_SPACE)) {
					flag = 0;
				}
			}
		}
		if (num == 1 && landinfo[position].vacationhome <= cash) {
			buyland(player, position, playerinfo[player-1].cash);
		}
		else if (num == 1 && landinfo[position].vacationhome > cash) {
			gotoxy(1, 51); printf("�ǹ��� ������ ������ �����մϴ�.      ");
			delay(1000);
		}
	}
	else if (landinfo[position].property == player) {
		gotoxy(1, 51); printf("�ǹ��� �� �����Ͻðڽ��ϱ�?��      �� ");
		gotoxy(31, 51); printf("YES");
		while (flag) {
			ch = getch();
			if (ch == 0xE0 || ch == 0) {
				ch = getch();
				switch (ch) {
				case LEFT:
					num = num * (-1);
					if (num == 1) {
						gotoxy(31, 51); printf("YES");
					}
					else {
						gotoxy(31, 51); printf("N O");
					}
					break;
				case RIGHT:
					num = num * (-1);
					if (num == 1) {
						gotoxy(31, 51); printf("YES");
					}
					else {
						gotoxy(31, 51); printf("N O");
					}
					break;
				}
			}
			else {
				if (IsKeyDown(VK_SPACE)) {
					flag = 0;
				}
			}
		}
		if (num == 1) {
			if(landinfo[position].vhflag == 0 || landinfo[position].bdflag == 0 || landinfo[position].htflag == 0){
				if (landinfo[position].vhflag == 0 && (landinfo[position].vacationhome * (-(landinfo[position].vhflag - 1))) <= cash || landinfo[position].bdflag == 0 && (landinfo[position].building * (-(landinfo[position].bdflag - 1))) <= cash || landinfo[position].htflag == 0 && (landinfo[position].hotel * (-(landinfo[position].htflag - 1))) <= cash) {
					rebuyland(player, position, playerinfo[player-1].cash);
				}
				else {
					gotoxy(1, 51); printf("��� �ִ� �ǹ��� �����ϴ�.            ");
					delay(1000);
				}
			}
			else {
				gotoxy(1, 51); printf("��� �ǹ��� �����߽��ϴ�.             ");
				delay(1000);
			}
		}
	}
	else {
		gotoxy(1, 51); printf("�ٸ� �÷��̾��� ���Դϴ�.             ");
		gotoxy(1, 52); printf("-%d", ((landinfo[position].vacationhome * landinfo[position].vhflag) + (landinfo[position].building * landinfo[position].bdflag) + (landinfo[position].hotel * landinfo[position].htflag))*landinfo[position].expo);
		delay(2000);
		gotoxy(1, 52); printf("       ");
		if (cash >= ((landinfo[position].vacationhome * landinfo[position].vhflag) + (landinfo[position].building * landinfo[position].bdflag) + (landinfo[position].hotel * landinfo[position].htflag))*landinfo[position].expo) {
			UpdateCash(player, -(((landinfo[position].vacationhome * landinfo[position].vhflag) + (landinfo[position].building * landinfo[position].bdflag) + (landinfo[position].hotel * landinfo[position].htflag))*landinfo[position].expo));
			UpdateCash(landinfo[position].property, ((landinfo[position].vacationhome* landinfo[position].vhflag) + (landinfo[position].building * landinfo[position].bdflag) + (landinfo[position].hotel * landinfo[position].htflag))*landinfo[position].expo);
		}
		else {
			paylandevent(player, position, playerinfo[player-1].cash, ((landinfo[position].vacationhome* landinfo[position].vhflag) + (landinfo[position].building * landinfo[position].bdflag) + (landinfo[position].hotel * landinfo[position].htflag))*landinfo[position].expo);
			
		}
	}
}

void buyland(int player, int position, int cash) { //ó�� ���� �����Ҷ� ����ϴ� �Լ�
	landinfo[position].vhflag = 0;
	landinfo[position].bdflag = 0;
	landinfo[position].htflag = 0;
	int ch, num, flag, buy1, buy2, buy3;
	num = 1;
	flag = 1;
	buy1 = -1;
	buy2 = -1;
	buy3 = -1;
	gotoxy(1, 51); printf("������ �ǹ��� �����ϼ��� �� ��        ");
	gotoxy(3, 53); printf("����"); gotoxy(11, 53); printf("����"); gotoxy(19, 53); printf("ȣ��"); gotoxy(27, 53); printf("Ȯ��"); gotoxy(3, 53);
	while (flag) {
		ch = getch();
		if (ch == 0xE0 || ch == 0) {
			ch = getch();
			switch (ch) {
			case LEFT:
				if (num > 1) {
					num--;
					if (num == 1)
						gotoxy(3, 53);
					else if (num == 2)
						gotoxy(11, 53);
					else if (num == 3)
						gotoxy(19, 53);
					else
						gotoxy(27, 53);

				}
				break;
			case RIGHT:
				if (num < 4) {
					num++;
					if (num == 1)
						gotoxy(3, 53);
					else if (num == 2)
						gotoxy(11, 53);
					else if (num == 3)
						gotoxy(19, 53);
					else
						gotoxy(27, 53);

				}
				break;
			}
		}
		else {
			if (IsKeyDown(VK_SPACE) && num == 4) {
				flag = 0;
				setColor(WHITE);
				gotoxy(3, 53); printf("                                      ");
			}
			else if (IsKeyDown(VK_SPACE) && num == 3) {
				buy3 = buy3 * (-1);
				if (buy3 == 1) {
					setColor(GREEN);
					gotoxy(19, 53); printf("ȣ��");
				}
				else {
					setColor(WHITE);
					gotoxy(19, 53); printf("ȣ��");
				}
			}
			else if (IsKeyDown(VK_SPACE) && num == 2) {
				buy2 = buy2 * (-1);
				if (buy2 == 1) {
					setColor(GREEN);
					gotoxy(11, 53); printf("����");
				}
				else {
					setColor(WHITE);
					gotoxy(11, 53); printf("����");
				}
			}
			else if (IsKeyDown(VK_SPACE) && num == 1) {
				buy1 = buy1 * (-1);
				if (buy1 == 1) {
					setColor(GREEN);
					gotoxy(3, 53); printf("����");
				}
				else {
					setColor(WHITE);
					gotoxy(3, 53); printf("����");
				}
			}
		}
	}
	if (buy1 == 1 || buy2 == 1 || buy3 == 1) {
		landinfo[position].property = player;
	}
		
	if (buy1 == 1)
		landinfo[position].vhflag = buy1;
	if (buy2 == 1)
		landinfo[position].bdflag = buy2;
	if (buy3 == 1)
		landinfo[position].htflag = buy3;
	if (cash < ((landinfo[position].vacationhome * landinfo[position].vhflag) + (landinfo[position].building * landinfo[position].bdflag) + (landinfo[position].hotel * landinfo[position].htflag))) {
		gotoxy(1, 51); printf("�ǹ��� ������ ������ �����մϴ�.      ");
		delay(1000);
	
		buyland(player, position, cash);
	}
	else {
		UpdateCash(player, (-(landinfo[position].vacationhome * landinfo[position].vhflag) - (landinfo[position].building * landinfo[position].bdflag) - (landinfo[position].hotel * landinfo[position].htflag)));
	}
	PrintLand(player, position);
}


void rebuyland(int player, int position, int cash) {  //�ڽ��� ���� �ǹ��� ������ �� ����ϴ� �Լ�
	int ch, num, flag, buy1, buy2, buy3, buyflag1, buyflag2, buyflag3, buy;
	buy = 0;
	num = 1;
	flag = 1;
	buyflag1 = landinfo[position].vhflag;
	buyflag2 = landinfo[position].bdflag;
	buyflag3 = landinfo[position].htflag;
	buy1 = landinfo[position].vhflag;
	buy2 = landinfo[position].bdflag;
	buy3 = landinfo[position].htflag;
	gotoxy(1, 51); printf("������ �ǹ��� �����ϼ��� �� ��        ");
	if (buy1 == 0) {
		gotoxy(3, 53); printf("����");
	}
	if (buy2 == 0) {
		gotoxy(11, 53); printf("����");
	}
	if (buy3 == 0) {
		gotoxy(19, 53); printf("ȣ��");
	}
	gotoxy(27, 53); printf("Ȯ��"); gotoxy(3, 53);
	while (flag) {
		ch = getch();
		if (ch == 0xE0 || ch == 0) {
			ch = getch();
			switch (ch) {
			case LEFT:
				if (num > 1) {
					num--;
					if (num == 1)
						gotoxy(3, 53);
					else if (num == 2)
						gotoxy(11, 53);
					else if (num == 3)
						gotoxy(19, 53);
					else
						gotoxy(27, 53);

				}
				break;
			case RIGHT:
				if (num < 4) {
					num++;
					if (num == 1)
						gotoxy(3, 53);
					else if (num == 2)
						gotoxy(11, 53);
					else if (num == 3)
						gotoxy(19, 53);
					else
						gotoxy(27, 53);

				}
				break;
			}
		}
		else {
			if (IsKeyDown(VK_SPACE) && num == 4) {
				flag = 0;
				setColor(WHITE);
				gotoxy(3, 53); printf("                                      ");
			}
			else if (IsKeyDown(VK_SPACE) && num == 3) {
				if (buy3 == 0) {
					buy3++;
					setColor(GREEN);
					gotoxy(19, 53); printf("ȣ��");
				}
			}
			else if (IsKeyDown(VK_SPACE) && num == 2) {
				if (buy2 == 0) {
					buy2++;
					setColor(GREEN);
					gotoxy(11, 53); printf("����");
				}
			}
			else if (IsKeyDown(VK_SPACE) && num == 1) {
				if (buy1 == 0) {
					buy1++;
					setColor(GREEN);
					gotoxy(3, 53); printf("����");
				}
			}
		}
	}
	landinfo[position].vhflag = buy1;
	landinfo[position].bdflag = buy2;
	landinfo[position].htflag = buy3;
	
	if (buyflag1 != landinfo[position].vhflag) {
		buy += (landinfo[position].vhflag * landinfo[position].vacationhome);
	}
	if (buyflag2 != landinfo[position].bdflag) {
		buy += (landinfo[position].bdflag * landinfo[position].building);
	}
	if (buyflag3 != landinfo[position].htflag) {
		buy += (landinfo[position].htflag * landinfo[position].hotel);
	}
	if (buy <= cash) {
		UpdateCash(player, (-buy));
		PrintLand(player, position);
	}
	else {
		delay(1000);
		rebuyland(player, position, cash);
	}
}

void paylandevent(int player, int position, int cash, int debt) { //land �� �ɷȴµ� ������ ������ ���Ĵ� �Լ�
	int flag, num, ch;
	
	
	flag = 1; num = 1; 
	if (playerinfo[player - 1].cash + playerinfo[player - 1].landall < debt) {
		bankuptcy(player, position, cash, debt);
   }
	else {
		gotoxy(1, 51); printf("���� �Ǹ� �Ͻðڽ��ϱ�?  ��        �� ");
		gotoxy(30, 51); printf("yes ");
		while (flag) {
			ch = getch();
			if (ch == 0xE0 || ch == 0) {
				ch = getch();
				switch (ch) {
				case LEFT:
					num = num * (-1);
					if (num == 1) {
						gotoxy(30, 51); printf("yes ");
					}
					else {
						gotoxy(30, 51); printf("�Ļ�");
					}
					break;
				case RIGHT:
					num = num * (-1);
					if (num == 1) {
						gotoxy(30, 51); printf("yes ");
					}
					else {
						gotoxy(30, 51); printf("�Ļ�");
					}
					break;
				}
			}
			else {
				if (IsKeyDown(VK_SPACE)) {
					flag = 0;
				}
			}
		}
		if (num == 1) {
			payland(player,debt);
			UpdateCash(player, -debt);
			UpdateCash(landinfo[position].property, debt);
			
		}
		else {
			bankuptcy(player, position, cash, debt);
		}
	}
	DeleteAllLand(player);
}

void bankuptcy(int player, int position, int cash, int debt) {
	int i;
	gotoxy(1, 51); printf("�Ļ� �Ͽ����ϴ�.                      ");
	delay(2000);
	playerinfo[player - 1].die = 1;
	gotoxy(playerxy[player - 1][playerinfo[player - 1].position].x, playerxy[player - 1][playerinfo[player - 1].position].y); puts("  ");
	playerinfo[player - 1].cash = 0;
	playerinfo[player - 1].asset = 0;
	for (i = 0; i < 40; i++) {
		if (landinfo[i].property == player) {
			landinfo[i].vhflag = 0;
			landinfo[i].bdflag = 0;
			landinfo[i].htflag = 0;
			landinfo[i].property = 0;
		}
	}
	DeleteAllLand(player);
	UpdateCash(player, 0);
	UpdateCash(landinfo[position].property, debt);
	diecount++;
}

void payland(int player, int debt) {
	int i, num, flag, ch, landnum = 0, buy = 1;
	num = 1; flag = 1;
	gotoxy(1, 51); puts("�Ǹ��� ���� �����ϼ��� �� ��          ");
	for (i = 0; i < 40; i++) {
		if (landinfo[i].property == player) {
			landnum += 1;
			gotoxy((landnum * 9) - 3, 53); printf("%s", p[i]);
			buyselect[landnum].land = p[i];
		}
	}
	gotoxy((landnum + 1) * 9 - 3, 53); printf("�� ��");
	gotoxy(6, 53);
	while (flag) {
		ch = getch();
		if (ch == 0xE0 || ch == 0) {
			ch = getch();
			switch (ch) {
			case LEFT:
				if (num > 1) {
					num--;
					gotoxy((num * 9) - 3, 53);
				}
				break;
			case RIGHT:
				if (num < landnum + 1) {
					num++;
					gotoxy((num * 9) - 3, 53);
				}
				break;
			}
		}
		else {
			if (IsKeyDown(VK_SPACE) && num == landnum + 1) {
				flag = 0;
			}
			else if (IsKeyDown(VK_SPACE) && num != landnum + 1 && buyselect[num].select == 0) {
				buyselect[num].select = 1;
				setColor(GREEN);
				gotoxy((num * 9) - 3, 53); printf("%s", buyselect[num].land);
			}
			else if (IsKeyDown(VK_SPACE) && num != landnum + 1 && buyselect[num].select == 1) {
				buyselect[num].select = 0;
				setColor(WHITE);
				gotoxy((num * 9) - 3, 53); printf("%s", buyselect[num].land);
			}
		}
	}
	setColor(WHITE); gotoxy(1, 53); printf("                                                                                                                 ");
	for (i = 0; i < 40; i++) {
		if (landinfo[i].property == player) {
			if (buyselect[buy].select == 1) {
				UpdateCash(player, (landinfo[i].vhflag * landinfo[i].vacationhome) + (landinfo[i].bdflag * landinfo[i].building) + (landinfo[i].htflag * landinfo[i].hotel));
				
				landinfo[i].property = 0;
				landinfo[i].vhflag = 0;
				landinfo[i].bdflag = 0;
				landinfo[i].htflag = 0;
				landinfo[i].expo = 1;
				UpdateCash(player, 0);
			}
			buy++;
		}
	}
	for (i = 0; i < 28; i++) {
		buyselect[i].select = 0;
	}
	
	if (playerinfo[player-1].cash < debt) {
		gotoxy(1, 51); puts("���� �� �Ⱦƾ� �մϴ�.                ");
		delay(1000);
		payland(player, debt);
	}
	for (i = 0; i < 40; i++) {
		if (landinfo[i].expo != 1) {
			gotoxy(60, 6); printf("������ ���� : %s", p[i]);
			gotoxy(60, 7); printf("x%d", expocount);
			break;
		}
		else {
			gotoxy(60, 6); printf("������ ���� : ����  ");
			gotoxy(60, 7); printf("x%d", expocount);
		}
	}
}

void TreadPark(int player, int position, int cash) {
	int ch, flag, num;
	num = 1;
	flag = 1;

	if (landinfo[position].property == 0) {
		gotoxy(1, 51); printf("������ ���� �Ͻðڽ��ϱ�?��        �� ");
		gotoxy(30, 51); printf("YES");
		while (flag) {
			ch = getch();
			if (ch == 0xE0 || ch == 0) {
				ch = getch();
				switch (ch) {
				case LEFT:
					num = num * (-1);
					if (num == 1) {
						gotoxy(30, 51); printf("YES");
					}
					else {
						gotoxy(30, 51); printf("N O");
					}
					break;
				case RIGHT:
					num = num * (-1);
					if (num == 1) {
						gotoxy(30, 51); printf("YES");
					}
					else {
						gotoxy(30, 51); printf("N O");
					}
					break;
				}
			}
			else {
				if (IsKeyDown(VK_SPACE)) {
					flag = 0;
				}
			}
		}
		if (num == 1 && landinfo[position].vacationhome <= cash) {
			landinfo[position].property = player;
			landinfo[position].vhflag = 1;
			landinfo[position].pd = 1;
			UpdateCash(player, (-landinfo[position].vacationhome));
			PrintLand(player, position);
		}
		else if (num == 1 && landinfo[position].vacationhome > cash) {
			gotoxy(1, 51); printf("������ ������ ������ �����մϴ�.      ");
			delay(1000);
		}
	}
	else if (landinfo[position].property == player) {
		gotoxy(1, 51); printf("�̹� �ڽ��� ���� �Դϴ�.              ");
	}
	else {
		gotoxy(1, 51); printf("�ٸ� �÷��̾��� �����Դϴ�.           ");
		gotoxy(1, 52); printf("-%d", (landinfo[position].vacationhome * landinfo[position].vhflag * landinfo[position].pd ));
		delay(2000);
		gotoxy(1, 52); printf("      ");
		if (cash >= (landinfo[position].vacationhome * landinfo[position].vhflag * landinfo[position].pd )) {
			UpdateCash(player, (-(landinfo[position].vacationhome * landinfo[position].vhflag * landinfo[position].pd)));
			UpdateCash(landinfo[position].property, (landinfo[position].vacationhome * landinfo[position].vhflag * landinfo[position].pd));
		}
		else {
			paylandevent(player, position, playerinfo[player - 1].cash, (landinfo[position].vacationhome * landinfo[position].vhflag * landinfo[position].pd));
		}
	}
}

void TreadMountain(int player, int position, int cash) {
	int ch, flag, num, i, mountain = 0;
	num = 1;
	flag = 1;

	if (landinfo[position].property == 0) {
		gotoxy(1, 51); printf("���� ���� �Ͻðڽ��ϱ�?  ��        �� ");
		gotoxy(30, 51); printf("YES");
		while (flag) {
			ch = getch();
			if (ch == 0xE0 || ch == 0) {
				ch = getch();
				switch (ch) {
				case LEFT:
					num = num * (-1);
					if (num == 1) {
						gotoxy(30, 51); printf("YES");
					}
					else {
						gotoxy(30, 51); printf("N O");
					}
					break;
				case RIGHT:
					num = num * (-1);
					if (num == 1) {
						gotoxy(30, 51); printf("YES");
					}
					else {
						gotoxy(30, 51); printf("N O");
					}
					break;
				}
			}
			else {
				if (IsKeyDown(VK_SPACE)) {
					flag = 0;
				}
			}
		}
		if (num == 1 && landinfo[position].vacationhome <= cash) {
			landinfo[position].property = player;
			landinfo[position].vhflag = 1;
			UpdateCash(player, (-landinfo[position].mountain));
			PrintLand(player, position);
		}
		else if (num == 1 && landinfo[position].vacationhome > cash) {
			gotoxy(1, 51); printf("���� ������ ������ �����մϴ�.        ");
			delay(1000);
		}
	}
	else if (landinfo[position].property == player) {
		gotoxy(1, 51); printf("�̹� �ڽ��� �� �Դϴ�.                ");
		delay(500);
	}
	else {
		gotoxy(1, 51); printf("�ٸ� �÷��̾��� �� �Դϴ�.            ");
		for (i = 0; i < 40; i++) {
			if (landinfo[i].property == landinfo[position].property) {
				mountain += (landinfo[i].mountain);
			}
		}
		gotoxy(1, 52); printf("-%d", mountain);
		delay(2000);
		gotoxy(1, 52); printf("      ");
		if (cash >= mountain) {
			UpdateCash(player, (-mountain));
			UpdateCash(landinfo[position].property, mountain);
		}
		else {
			paylandevent(player, position, playerinfo[player - 1].cash, mountain);
		}

	}
}

void Expo(int player, int position) {
	int ch, flag, num, i;
	gotoxy(1, 51); puts("������ ��ġ�� �����ϼ��� ��         ��");
	gotoxy(29, 51); printf("%s", p[0]);

	flag = 1;
	num = 0;
	while (flag) {
		ch = getch();
		if (ch == 0xE0 || ch == 0) {
			ch = getch();
			switch (ch) {
			case LEFT:
				if (num > 31) {
					num--;
				}
				else if (num == 31) {
					num = num - 2;
				}
				else if (num <= 29 && num >= 1) {
					num--;
				}
				else {
					num = 39;
				}
				gotoxy(29, 51); printf("%s", p[num]);
				break;
			case RIGHT:
				if (num < 29) {
					num++;
				}
				else if (num == 29) {
					num = num + 2;
				}
				else if (num >= 31 && num < 39) {
					num++;
				}
				else {
					num = 0;
				}
				gotoxy(29, 51); printf("%s", p[num]);
				break;
			}
		}
		else {
			if (IsKeyDown(VK_SPACE)) {
				flag = 0;
			}
		}
	}
	if (num == 0 || num == 10 || num == 20 || num == 30 || num == 2 || num == 4 || num == 13 || num == 18 || num == 22 || num == 27 || num == 36 || num == 38 || num == 5 || num == 15 || num == 25 || num == 35 || num == 7 || num == 33 || landinfo[num].property != player) {
		gotoxy(1, 51); puts("�߸��� �����Դϴ�. �ٽ� ���� �ϼ���.  ");
		delay(1000);
		Expo(player, position);
	}
	else {
		for (i = 0; i < 40; i++) {
			landinfo[i].expo = 1;
		}
		landinfo[num].expo += expocount;
	}
	delay(500);
}
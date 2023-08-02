#include <iostream>
#include <vector>
#include <string>
#include <random>
#include <fstream>
using namespace std;

struct Status {
	int HP;
	int HPmax;
	int Atk;
	int Heal;
};

int hp;
int atk;
int heal;

void psetStatus() {
	cout << "���Ȃ�(�v���C���[)�̃X�e�[�^�X��ݒ肵�܂�." << endl;
	cout << "�u�̗�(HP)�v�𐮐��l�œ��͂��Ă�������." << endl;
	cin >> hp;
	cout << "�u�U����(Atk)�v�𐮐��l�œ��͂��Ă�������.�@�U���͂�1�`2�{���U���l�ɂȂ�܂�." << endl;
	cin >> atk;
	cout << "�u�񕜗�(Heal)�v�𐮐��l�œ��͂��Ă�������.�@�񕜗͂̒l�����̂܂܉񕜒l�ɂȂ�܂�." << endl;
	cin >> heal;
}

void esetStatus() {
	cout << "�u�̗�(HP)�v�𐮐��l�œ��͂��Ă�������." << endl;
	cin >> hp;
	cout << "�u�U����(Atk)�v�𐮐��l�œ��͂��Ă�������.�@�U���͂̂P�`�Q�{���U���l�ɂȂ�܂�." << endl;
	cin >> atk;
}

void Enter() {
	int enter = getchar();
}

int main() {
	cout << "RPG���o�g���V�~�����[�^�ւ悤����.�@�g�p����ۂɂ͑S��ʕ\�����������߂��܂�." << endl;
	cout << "�͂��߂�,�@�G�̐��𐮐��l�œ��͂��Ă�������." << endl;
	int e_num;
	cin >> e_num;
	cout << endl;

	//�X�e�[�^�X�ݒ�
	int i = 0;
	vector<Status> stat;
	while (i <= e_num) {
		//�v���C���[�̃X�e�[�^�X�ݒ�
		if (i == 0) {
			psetStatus();
			stat.emplace_back();
			stat[i].HP = hp;
			stat[i].Atk = atk;
			stat[i].Heal = heal;
			cout << endl;
			cout << "���Ȃ��̃X�e�[�^�X�͈ȉ��̒ʂ�ł�." << endl;
			cout << "HP:" << stat[i].HP << " Atk:" << stat[i].Atk << " Heal:" << stat[i].Heal << endl << endl << endl;
			stat[i].HPmax = hp;
			i++;
		}
		//�G�̃X�e�[�^�X�ݒ�
		else {
			cout << "�G" << i << "�̃X�e�[�^�X��ݒ肵�܂�." << endl;
			esetStatus();
			stat.emplace_back();
			stat[i].HP = hp;
			stat[i].Atk = atk;
			cout << endl;
			cout << "�G" << i << "�̃X�e�[�^�X�͈ȉ��̒ʂ�ł�." << endl;
			cout << "HP:" << stat[i].HP << " Atk:" << stat[i].Atk << endl << endl << endl;
			stat[i].HPmax = hp;
			i++;
		}
	}
	
	Enter();
	cout << "�o�g�����J�n���܂�.�@Enter�L�[�������Ă�������.��" << endl
		<< "(�ȍ~,�@��L�́u���v���t�������ł�Enter�L�[�������Ď��ɐi��ł�������.)";
	Enter();
	cout << endl;

	//�o�g���t�F�[�Y
	int huntrslt = 0;
	int atkrslt = 0;
	int dmgrslt = 0;
	int healrslt = 0;
	int turn = 0;
	while (1) {
		turn += 1;

		//�X�e�[�^�X�\��
		int j = 1;
		cout << endl;
		while (j <= e_num) {
			cout << "�G" << j << "�@HP:";
			if (stat[j].HP == 0) {
				cout << "����������" << " (���j)" << endl;
			}
			else if (stat[j].HP <= 0.2 * stat[j].HPmax) {
				cout << "����������" << endl;
			}
			else if (stat[j].HP <= 0.4 * stat[j].HPmax) {
				cout << "����������" << endl;
			}
			else if (stat[j].HP <= 0.6 * stat[j].HPmax) {
				cout << "����������" << endl;
			}
			else if (stat[j].HP <= 0.8 * stat[j].HPmax) {
				cout << "����������" << endl;
			}
			else {
				cout << "����������" << endl;
			}
			j++;
		}
		cout << "==============================" << endl;
		cout << "�v���C���[�@HP:";
		if (stat[0].HP <= 0.2 * stat[0].HPmax) {
			cout << "����������";
		}
		else if (stat[0].HP <= 0.4 * stat[0].HPmax) {
			cout << "����������";
		}
		else if (stat[0].HP <= 0.6 * stat[0].HPmax) {
			cout << "����������";
		}
		else if (stat[0].HP <= 0.8 * stat[0].HPmax) {
			cout << "����������";
		}
		else {
			cout << "����������";
		}
		cout << "(" << stat[0].HP << ")" << endl << endl;

		//�R�}���h����
		command:
		cout << "�s���R�}���h���ȉ��̃A���t�@�x�b�g�ɂ����͂��Ă�������." << endl;
		cout << "�U��:a�@�h��:d�@��:h�@���^�C�A:r" << endl;
		string cmd;
		cin >> cmd;
		cout << endl;

		//�U��
		attack:
		if (cmd == "a") {
			cout << "�U������G�̔ԍ�����͂��Ă�������." << endl;
			int enm;
			cin >> enm;
			cout << endl;
			if (stat[enm].HP == 0) {
				Enter();
				cout << "�G" << enm << "�͂��łɌ��j���Ă��܂�.�@�Ⴄ�G��I�����Ă�������.��";
				Enter();
				cout << endl;
				goto attack;
			}

			random_device engine;
			uniform_int_distribution<unsigned> patk(stat[0].Atk, 2 * stat[0].Atk);
			int edmg = patk(engine);
			int ehp = stat[enm].HP - edmg;

			Enter();
			if (edmg >= 1.5 * stat[0].Atk) {
				cout << "�N���e�B�J���I�G" << enm << "��" << edmg << "�̃_���[�W�I��";
			}
			else {
				cout << "�G" << enm << "��" << edmg << "�̃_���[�W�I��";
			}
			Enter();
			atkrslt += edmg;

			if (ehp <= 0) {
				stat[enm].HP = 0;
				huntrslt += 1;
				cout << "�G" << enm << "��|�����I��";
				Enter();
			}
			else {
				stat[enm].HP = ehp;
			}
		}

		//�h��
		int def = 0;
		if (cmd == "d") {
			def = 1;
			Enter();
			cout << "�h��̍\�����Ƃ����I��";
			Enter();
		}

		//��
		if (cmd == "h") {
			int actheal;
			int hpmax = stat[0].HPmax;
			int hhp = stat[0].HP + stat[0].Heal;
			if (hhp > hpmax) {
				actheal = hpmax - stat[0].HP;
				stat[0].HP = hpmax;
			}
			else {
				actheal = stat[0].Heal;
				stat[0].HP = hhp;
			}
			Enter();
			cout << "�̗͂�" << actheal << "�񕜂����I��";
			Enter();
			healrslt += actheal;
		}

		//���^�C�A
		if (cmd == "r") {
			cout << "�{���Ƀ��^�C�A���܂����H" << endl
				<< "�͂�:y�@������:n" << endl;
			string ret;
			cin >> ret;
			cout << endl;
			if (ret == "y") {
				Enter();
				cout << "���^�C�A���܂���.�@���U���g��\�����܂�.��";
				Enter();
				cout << endl;
				goto result;
			}
			if (ret == "n") {
				goto command;
			}
		}

		//�G�̍U��
		int k = 1;
		int pdmg;
		int php;
		while (k <= e_num) {
			random_device engine;
			uniform_int_distribution<unsigned> eatk(stat[k].Atk, 2 * stat[k].Atk);

			if (stat[k].HP == 0) {
				goto skip;
			}
			
			if (def == 1) {
				pdmg = eatk(engine) / 2;
			}
			else {
				pdmg = eatk(engine);
			}
			php = stat[0].HP - pdmg;

			if (pdmg >= 1.5 * stat[k].Atk) {
				cout << "�N���e�B�J���I�G" << k << "����" << pdmg << "�̃_���[�W�I��";
			}
			else {
				cout << "�G" << k << "����" << pdmg << "�̃_���[�W�I��";
			}
			Enter();
			dmgrslt += pdmg;

			if (php <= 0) {
				stat[0].HP = 0;
				cout << "�Q�[���I�[�o�[�I�@�̗͂�0�ɂȂ�܂���.�@���U���g��\�����܂�.��";
				Enter();
				cout << endl << endl;
				goto result;
			}
			else {
				stat[0].HP = php;
			}
			skip:
			k++;
		}

		if (huntrslt == e_num) {
			cout << "�Q�[���N���A�I�@���߂łƂ��������܂�.�@���U���g��\�����܂�.";
			Enter();
			cout << endl << endl;
			goto result;
		}
	}

	//���U���g
	result:
	ofstream outfile("results");
	outfile << "���Ȃ��̃X�e�[�^�X��"
		<< "�@HP:" << stat[0].HPmax << "�@Atk:" << stat[0].Atk << "�@Heal:" << stat[0].Heal << endl;
	int m = 1;
	while (m <= e_num) {
		outfile << "�G" << m << "�̃X�e�[�^�X��"
			<< "�@HP:" << stat[m].HPmax << "�@Atk:" << stat[m].Atk << endl;
		m++;
	}
	outfile << "���j��:" << huntrslt << "/" << e_num << endl;
	outfile << "�^�����_���[�W:" << atkrslt << endl;
	outfile << "�󂯂��_���[�W:" << dmgrslt << endl;
	outfile << "�̗͂̑��񕜒l:" << healrslt << endl;
	outfile << "�o�߃^�[����:" << turn << endl; 
	outfile.close();

	vector<string> results;
	ifstream infile("results");
	string line;
	while (getline(infile, line)) {
		results.push_back(line);
	}
	
	cout << "===���U���g===" << endl << endl;
	size_t s = results.size();
	for (size_t l = 0; l < s; ++l) {
		cout << *(results.begin() += l) << endl;
	}
}
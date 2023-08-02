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
	cout << "あなた(プレイヤー)のステータスを設定します." << endl;
	cout << "「体力(HP)」を整数値で入力してください." << endl;
	cin >> hp;
	cout << "「攻撃力(Atk)」を整数値で入力してください.　攻撃力の1～2倍が攻撃値になります." << endl;
	cin >> atk;
	cout << "「回復力(Heal)」を整数値で入力してください.　回復力の値がそのまま回復値になります." << endl;
	cin >> heal;
}

void esetStatus() {
	cout << "「体力(HP)」を整数値で入力してください." << endl;
	cin >> hp;
	cout << "「攻撃力(Atk)」を整数値で入力してください.　攻撃力の１～２倍が攻撃値になります." << endl;
	cin >> atk;
}

void Enter() {
	int enter = getchar();
}

int main() {
	cout << "RPG風バトルシミュレータへようこそ.　使用する際には全画面表示をおすすめします." << endl;
	cout << "はじめに,　敵の数を整数値で入力してください." << endl;
	int e_num;
	cin >> e_num;
	cout << endl;

	//ステータス設定
	int i = 0;
	vector<Status> stat;
	while (i <= e_num) {
		//プレイヤーのステータス設定
		if (i == 0) {
			psetStatus();
			stat.emplace_back();
			stat[i].HP = hp;
			stat[i].Atk = atk;
			stat[i].Heal = heal;
			cout << endl;
			cout << "あなたのステータスは以下の通りです." << endl;
			cout << "HP:" << stat[i].HP << " Atk:" << stat[i].Atk << " Heal:" << stat[i].Heal << endl << endl << endl;
			stat[i].HPmax = hp;
			i++;
		}
		//敵のステータス設定
		else {
			cout << "敵" << i << "のステータスを設定します." << endl;
			esetStatus();
			stat.emplace_back();
			stat[i].HP = hp;
			stat[i].Atk = atk;
			cout << endl;
			cout << "敵" << i << "のステータスは以下の通りです." << endl;
			cout << "HP:" << stat[i].HP << " Atk:" << stat[i].Atk << endl << endl << endl;
			stat[i].HPmax = hp;
			i++;
		}
	}
	
	Enter();
	cout << "バトルを開始します.　Enterキーを押してください.▽" << endl
		<< "(以降,　上記の「▽」が付いた文ではEnterキーを押して次に進んでください.)";
	Enter();
	cout << endl;

	//バトルフェーズ
	int huntrslt = 0;
	int atkrslt = 0;
	int dmgrslt = 0;
	int healrslt = 0;
	int turn = 0;
	while (1) {
		turn += 1;

		//ステータス表示
		int j = 1;
		cout << endl;
		while (j <= e_num) {
			cout << "敵" << j << "　HP:";
			if (stat[j].HP == 0) {
				cout << "□□□□□" << " (撃破)" << endl;
			}
			else if (stat[j].HP <= 0.2 * stat[j].HPmax) {
				cout << "■□□□□" << endl;
			}
			else if (stat[j].HP <= 0.4 * stat[j].HPmax) {
				cout << "■■□□□" << endl;
			}
			else if (stat[j].HP <= 0.6 * stat[j].HPmax) {
				cout << "■■■□□" << endl;
			}
			else if (stat[j].HP <= 0.8 * stat[j].HPmax) {
				cout << "■■■■□" << endl;
			}
			else {
				cout << "■■■■■" << endl;
			}
			j++;
		}
		cout << "==============================" << endl;
		cout << "プレイヤー　HP:";
		if (stat[0].HP <= 0.2 * stat[0].HPmax) {
			cout << "■□□□□";
		}
		else if (stat[0].HP <= 0.4 * stat[0].HPmax) {
			cout << "■■□□□";
		}
		else if (stat[0].HP <= 0.6 * stat[0].HPmax) {
			cout << "■■■□□";
		}
		else if (stat[0].HP <= 0.8 * stat[0].HPmax) {
			cout << "■■■■□";
		}
		else {
			cout << "■■■■■";
		}
		cout << "(" << stat[0].HP << ")" << endl << endl;

		//コマンド決定
		command:
		cout << "行動コマンドを以下のアルファベットにより入力してください." << endl;
		cout << "攻撃:a　防御:d　回復:h　リタイア:r" << endl;
		string cmd;
		cin >> cmd;
		cout << endl;

		//攻撃
		attack:
		if (cmd == "a") {
			cout << "攻撃する敵の番号を入力してください." << endl;
			int enm;
			cin >> enm;
			cout << endl;
			if (stat[enm].HP == 0) {
				Enter();
				cout << "敵" << enm << "はすでに撃破しています.　違う敵を選択してください.▽";
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
				cout << "クリティカル！敵" << enm << "に" << edmg << "のダメージ！▽";
			}
			else {
				cout << "敵" << enm << "に" << edmg << "のダメージ！▽";
			}
			Enter();
			atkrslt += edmg;

			if (ehp <= 0) {
				stat[enm].HP = 0;
				huntrslt += 1;
				cout << "敵" << enm << "を倒した！▽";
				Enter();
			}
			else {
				stat[enm].HP = ehp;
			}
		}

		//防御
		int def = 0;
		if (cmd == "d") {
			def = 1;
			Enter();
			cout << "防御の構えをとった！▽";
			Enter();
		}

		//回復
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
			cout << "体力を" << actheal << "回復した！▽";
			Enter();
			healrslt += actheal;
		}

		//リタイア
		if (cmd == "r") {
			cout << "本当にリタイアしますか？" << endl
				<< "はい:y　いいえ:n" << endl;
			string ret;
			cin >> ret;
			cout << endl;
			if (ret == "y") {
				Enter();
				cout << "リタイアしました.　リザルトを表示します.▽";
				Enter();
				cout << endl;
				goto result;
			}
			if (ret == "n") {
				goto command;
			}
		}

		//敵の攻撃
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
				cout << "クリティカル！敵" << k << "から" << pdmg << "のダメージ！▽";
			}
			else {
				cout << "敵" << k << "から" << pdmg << "のダメージ！▽";
			}
			Enter();
			dmgrslt += pdmg;

			if (php <= 0) {
				stat[0].HP = 0;
				cout << "ゲームオーバー！　体力が0になりました.　リザルトを表示します.▽";
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
			cout << "ゲームクリア！　おめでとうございます.　リザルトを表示します.";
			Enter();
			cout << endl << endl;
			goto result;
		}
	}

	//リザルト
	result:
	ofstream outfile("results");
	outfile << "あなたのステータス→"
		<< "　HP:" << stat[0].HPmax << "　Atk:" << stat[0].Atk << "　Heal:" << stat[0].Heal << endl;
	int m = 1;
	while (m <= e_num) {
		outfile << "敵" << m << "のステータス→"
			<< "　HP:" << stat[m].HPmax << "　Atk:" << stat[m].Atk << endl;
		m++;
	}
	outfile << "撃破数:" << huntrslt << "/" << e_num << endl;
	outfile << "与えたダメージ:" << atkrslt << endl;
	outfile << "受けたダメージ:" << dmgrslt << endl;
	outfile << "体力の総回復値:" << healrslt << endl;
	outfile << "経過ターン数:" << turn << endl; 
	outfile.close();

	vector<string> results;
	ifstream infile("results");
	string line;
	while (getline(infile, line)) {
		results.push_back(line);
	}
	
	cout << "===リザルト===" << endl << endl;
	size_t s = results.size();
	for (size_t l = 0; l < s; ++l) {
		cout << *(results.begin() += l) << endl;
	}
}
#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//二进制转换为十六进制函数实现
string twotosix(string str) {
	string shiliu = "";//用来存储最后生成的十六进制数
	int temp = 0;//用来存储每次四位二进制数的十进制值
	while (str.size() % 4 != 0) {//因为每四位二进制数就能够成为一个十六进制数，所以将二进制数长度转换为4的倍数
		str = "0" + str;//最高位添0直到长度为4的倍数
	}
	for (int i = 0; i < str.size(); i += 4) {
		temp = (str[i] - '0') * 8 + (str[i + 1] - '0') * 4 + (str[i + 2] - '0') * 2 + (str[i + 3] - '0') * 1;//判断出4位二进制数的十进制大小为多少
		if (temp < 10) {
			shiliu += to_string(temp);
		}
		else {//当得到的值大于10时，需要进行A-F的转换
			shiliu += 'A' + (temp - 10);
		}
	}
	return shiliu;
}

//十六进制转换为二进制函数实现
string sixtotwo(string str) {
	string bin = "";
	string tab[16] = { "0000","0001","0010","0011","0100","0101","0110","0111","1000","1001","1010","1011","1100","1101","1110","1111" };
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			bin += tab[str[i] - 'A' + 10];
		}
		else {
			bin += tab[str[i] - '0'];
		}
	}
	return bin;
}

//二进制转换为十进制的函数实现
int twoten(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		dec += (str[i] - '0') * pow(2, str.size() - i - 1);
	}
	return dec;
}

//十进制转换为二进制的函数实现
string tentotwo(int str) {
	string bin = "";
	while (str >= 1) {
		bin = to_string(str % 2) + bin;
		str = str / 2;
	}
	return bin;
}

//十六进制转换为十进制的函数实现
int sixtoten(string str) {
	int dec = 0;
	for (int i = 0; i < str.size(); i++) {
		if (str[i] >= 'A' && str[i] <= 'F') {
			dec += (str[i] - 'A' + 10) * pow(16, str.size() - i - 1);
		}
		else {
			dec += (str[i] - '0') * pow(16, str.size() - i - 1);
		}
	}
	return dec;
}

//十进制转换为十六进制的函数实现
string tentosix(int str) {
	string shiliu = "";
	int temp = 0;
	while (str >= 1) {
		temp = str % 16;
		if (temp < 10 && temp >= 0) {
			shiliu = to_string(temp) + shiliu;
		}
		else {
			shiliu += ('A' + (temp - 10));
		}
		str = str / 16;
	}
	return shiliu;
}

string tianchong(string str) {//对数据进行填充 
	string res = "";
	for (int i = 0; i < str.size(); i++) {//首先将输入值转换为16进制字符串
		res += tentosix((int)str[i]);
	}

	int res_length = res.size() * 4;//记录的长度为2进制下的长度
	res += "8";//在获得的数据后面添1，在16进制下相当于是添加8
	while (res.size() % 128 != 112) {
		res += "0";//“0”数据填充
	}
	string res_len = tentosix(res_length);//用于记录数据长度的字符串
	while (res_len.size() != 16) {
		res_len = "0" + res_len;
	}
	res += res_len;
	return res;
}

string LeftShift(string str, int len) {//实现循环左移len位功能
	string res = sixtotwo(str);
	res = res.substr(len) + res.substr(0, len);
	return twotosix(res);
}

string yihuo(string str1, string str2) {//实现异或操作
	string t1 = sixtotwo(str1);
	string t2 = sixtotwo(str2);
	string res = "";
	for (int i = 0; i < t1.size(); i++) {
		if (t1[i] == t2[i]) {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return twotosix(res);
}

string yu(string str1, string str2) {//实现与操作
	string t1 = sixtotwo(str1);
	string t2 = sixtotwo(str2);
	string res = "";
	for (int i = 0; i < t1.size(); i++) {
		if (t1[i] == '1' && t2[i] == '1') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return twotosix(res);
}

string OR(string str1, string str2) {//实现或操作
	string t1 = sixtotwo(str1);
	string t2 = sixtotwo(str2);
	string res = "";
	for (int i = 0; i < t1.size(); i++) {
		if (t1[i] == '0' && t2[i] == '0') {
			res += "0";
		}
		else {
			res += "1";
		}
	}
	return twotosix(res);
}

string fei(string str) {//实现非操作
	string t1 = sixtotwo(str);
	string res = "";
	for (int i = 0; i < t1.size(); i++) {
		if (t1[i] == '0') {
			res += "1";
		}
		else {
			res += "0";
		}
	}
	return twotosix(res);
}

char binyihuo(char str1, char str2) {//实现单比特的异或操作
	return str1 == str2 ? '0' : '1';
}

char bityu(char str1, char str2) {//实现单比特的与操作
	return (str1 == '1' && str2 == '1') ? '1' : '0';
}

string ModAdd(string str1, string str2) {//mod 2^32运算的函数实现
	string t1 = sixtotwo(str1);
	string t2 = sixtotwo(str2);
	char temp = '0';
	string res = "";
	for (int i = t1.size() - 1; i >= 0; i--) {
		res = binyihuo(binyihuo(t1[i], t2[i]), temp) + res;
		if (bityu(t1[i], t2[i]) == '1') {
			temp = '1';
		}
		else {
			if (binyihuo(t1[i], t2[i]) == '1') {
				temp = bityu('1', temp);
			}
			else {
				temp = '0';
			}
		}
	}
	return twotosix(res);
}

string P1(string str) {//实现置换功能P1（X）
	return yihuo(yihuo(str, LeftShift(str, 15)), LeftShift(str, 23));
}

string P0(string str) {//实现置换功能P0（X）
	return yihuo(yihuo(str, LeftShift(str, 9)), LeftShift(str, 17));
}

string T(int j) {//返回Tj常量值的函数实现
	if (0 <= j && j <= 15) {
		return "79CC4519";
	}
	else {
		return "7A879D8A";
	}
}

string FF(string str1, string str2, string str3, int j) {//实现布尔函数FF功能
	if (0 <= j && j <= 15) {
		return yihuo(yihuo(str1, str2), str3);
	}
	else {
		return OR(OR(yu(str1, str2), yu(str1, str3)), yu(str2, str3));
	}
}

string buer(string str1, string str2, string str3, int j) {//实现布尔函数buer功能
	if (0 <= j && j <= 15) {
		return yihuo(yihuo(str1, str2), str3);
	}
	else {
		return OR(yu(str1, str2), yu(fei(str1), str3));
	}
}
string extension(string str) {//消息扩展函数
	string res = str;//字符串类型存储前68位存储扩展字W值
	for (int i = 16; i < 68; i++) {//根据公式生成第17位到第68位的W值
		res += yihuo(yihuo(P1(yihuo(yihuo(res.substr((i - 16) * 8, 8), res.substr((i - 9) * 8, 8)), LeftShift(res.substr((i - 3) * 8, 8), 15))), LeftShift(res.substr((i - 13) * 8, 8), 7)), res.substr((i - 6) * 8, 8));
	}

	for (int i = 0; i < 64; i++) {//根据公式生成64位W'值
		res += yihuo(res.substr(i * 8, 8), res.substr((i + 4) * 8, 8));
	}

	return res;
}

string compress(string str1, string str2) {//消息压缩函数
	string IV = str2;
	string A = IV.substr(0, 8), B = IV.substr(8, 8), C = IV.substr(16, 8), D = IV.substr(24, 8), E = IV.substr(32, 8), F = IV.substr(40, 8), G = IV.substr(48, 8), H = IV.substr(56, 8);
	string SS1 = "", SS2 = "", TT1 = "", TT2 = "";

	for (int j = 0; j < 64; j++) {
		SS1 = LeftShift(ModAdd(ModAdd(LeftShift(A, 12), E), LeftShift(T(j), (j % 32))), 7);
		SS2 = yihuo(SS1, LeftShift(A, 12));
		TT1 = ModAdd(ModAdd(ModAdd(FF(A, B, C, j), D), SS2), str1.substr((j + 68) * 8, 8));
		TT2 = ModAdd(ModAdd(ModAdd(buer(E, F, G, j), H), SS1), str1.substr(j * 8, 8));
		D = C;
		C = LeftShift(B, 9);
		B = A;
		A = TT1;
		H = G;
		G = LeftShift(F, 19);
		F = E;
		E = P0(TT2);
		//cout << A << "  " << B << "  " << C << "  " << D << "  " << E << "  " << F << "  " << G << "  " << H << endl;
	}
	string res = (A + B + C + D + E + F + G + H);
	cout << endl;
	return res;
}

string yasuo(string str) {//迭代压缩函数实现
	int num = str.size() / 128;
	/*cout << "消息经过填充之后共有 " + to_string(num) + " 个消息分组。" << endl;
	cout << endl;*/
	string V = "3452666F4914B2B0859442D7DA8A0600A96F30BC163138AAE38DEE4DB0FB0E4E";
	string B = "", extensionB = "", compressB = "";
	for (int i = 0; i < num; i++) {

		B = str.substr(i * 128, 128);
		extensionB = extension(B);
		compressB = compress(extensionB, V);
		V = yihuo(V, compressB);
	}
	return V;
}

int main() {//主函数
	clock_t start, end;

	string str[5];
	str[0] = "fqc";
	str[1] = "fqchfqchfqchfqchfqchfqchfqchfqchfqchfqchfqchfqchfqchfqchfqchfqch";
	str[2] = "sieofsefsdreffd";
	str[3] = "890jojlkjouwoeu";
	str[4] = "890jojlkj3eroe4";
	string uu[5][5];
	for (int num = 0; num < 5; num++) {

		string tianchongValue = tianchong(str[num]);
		cout << "填充后的消息为：" << endl;
		for (int i = 0; i < tianchongValue.size() / 64; i++) {
			for (int j = 0; j < 8; j++) {
				cout << tianchongValue.substr(i * 64 + j * 8, 8) << "  ";
			}
			
		}
		
		start = clock();
		string result = yasuo(tianchongValue);
		cout << "杂凑值：" << endl;
		for (int i = 0; i < 8; i++) {
			cout << result.substr(i * 8, 8) << "  ";
			uu[num][i] = result.substr(i * 8, 8);
		}
		cout << endl;
		cout << endl;
		end = clock();
	}
	int qq = 1;
	//多个hash值碰撞
	for (int hh = 0; hh < 5; hh++)
	{
		for (int vv = qq; vv < 5; vv++)
		{
			if (uu[hh] == uu[vv])
			{
				cout << "成功" << endl;
			}

		}
		qq++;
	}


	cout << endl;
	cout << "运行时间: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl;
}


#include <iostream>
#include <cstring>
//5+7*3-(6*2+1)/10    =24.7
//23-32*7/8           =-5
//(2+3)*4             =20
//2+3                 =5
#define StrExtFloat_flen 64
#define StrExtFloat_slen 512
using namespace std;
void StrExtFloat(float* num, string S)
{
	int Fflag = 0;
	int Fnum = 0;
	char num_start = 0, num_point = 0;
	for (char c : S)
	{
		Fflag++;
		if (Fflag > StrExtFloat_slen)
			break;
		if (c >= '0' && c <= '9')
		{
			//printf("%c",*Str);
			num_start = 1;
			if (num_point >= 1)
			{
				num_point++;
				float fpoint = c - '0';
				for (int i = 1; i < num_point; i++)
				{
					fpoint = fpoint / 10.;
				}
				num[Fnum + 1] = num[Fnum + 1] + fpoint;
			}
			else
			{
				num[Fnum + 1] = num[Fnum + 1] * 10 + (c - '0');
			}
		}
		else if (c == '.')
		{
			if (num_start == 1)
			{
				num_point = 1;
			}
		}
		else
		{
			if (num_start == 1)
			{
				Fnum++;
			}
			num_start = 0;
			num_point = 0;
		}
	}
	if (num_start == 1)
	{
		Fnum++;
	}
	num[0] = Fnum;
}

/*
Certainly! Here are some test cases for the given code:

Test Case 1:
Input: "(2+3)*4"
Expected Output:
×óÐ¡À¨ºÅ
²Ù×÷Êý:2
¼ÓºÅ
²Ù×÷Êý:3
ÓÒÐ¡À¨ºÅ
³ËºÅ
²Ù×÷Êý:4
À¨ºÅÆ¥Åä!

Test Case 2:
Input: "{2+3]*4"
Expected Output:
×ó´óÀ¨ºÅ
¼ÓºÅ
²Ù×÷Êý: 2
²Ù×÷Êý: 3
ÓÒÖÐÀ¨ºÅ²»Æ¥Åä!

Test Case 3:
Input: "2+3)*4"
Expected Output:
²Ù×÷Êý:2
¼ÓºÅ
²Ù×÷Êý:3
ÓÒÐ¡À¨ºÅ²»Æ¥Åä!

Test Case 4:
Input: "2+3"
Expected Output:
²Ù×÷Êý:2
¼ÓºÅ
²Ù×÷Êý:3
À¨ºÅÆ¥Åä!

Please note that these are just a few examples, and you can create additional test cases based on your specific requirements.
*/

//bool isValid(const std::string& S, char* Ope, float* num) {
bool isValid(const std::string& S, float* num) {
	int pos = 0;
	int POS = 0;
	int numpos = 1;
	char Ope[255] = { '\0' };
	float Opn[255] = { 0 };
	for (int i = 0; i < S.length(); i++) {
		//////////////////////////////////////////////////////////
		if (S[i] == '+')
		{
			if (pos == 0)
			{
				Ope[pos++] = S[i];
			}
			else if (Ope[pos - 1] != '*' && Ope[pos - 1] != '/')
			{
				Ope[pos++] = S[i];
			}
			else if (Ope[pos - 1] == '*' || Ope[pos - 1] == '/')
			{
				while (pos > 0 && Ope[pos-1] != '(')
				{
					pos--;
					switch (Ope[pos])
					{
					case'+':
						Opn[POS - 2] = Opn[POS-2] + Opn[POS - 1];
						break;
					case'-':
						Opn[POS - 2] = Opn[POS-2] - Opn[POS - 1];
						break;
					case'*':
						Opn[POS - 2] = Opn[POS-2] * Opn[POS - 1];
						break;
					case'/':
						Opn[POS - 2] = Opn[POS-2] / Opn[POS - 1];
						break;
					default:
						break;
					}
					POS--;
				}
				Ope[pos++] = S[i];
			}
		}
		else if (S[i] == '-')
		{
			if (pos == 0)
			{
				Ope[pos++] = S[i];
			}
			else if (Ope[pos - 1] != '*' && Ope[pos - 1] != '/')
			{
				Ope[pos++] = S[i];
			}
			else if (Ope[pos - 1] == '*' || Ope[pos - 1] == '/')
			{
				while (pos > 0 && Ope[pos] != '(')
				{
					pos--;
					switch (Ope[pos])
					{
					case'+':
						Opn[POS - 2] = Opn[POS-2] + Opn[POS - 1];
						//cout << Opn[POS - 1] << endl;
						break;
					case'-':
						Opn[POS - 2] = Opn[POS-2] - Opn[POS - 1];
						//cout << Opn[POS - 1] << endl;
						break;
					case'*':
						Opn[POS - 2] = Opn[POS-2] * Opn[POS - 1];
						//cout << Opn[POS - 1] << endl;
						break;
					case'/':
						Opn[POS - 2] = Opn[POS-2] / Opn[POS - 1];
						//cout << Opn[POS - 1] << endl;
						break;
					default:
						break;
					}
					POS--;
				}
				Ope[pos++] = S[i];
			}
		}
		else if (S[i] == '*' || S[i] == '/')
		{
			Ope[pos++] = S[i];
		}
		else if (S[i] == '(')
		{
			Ope[pos++] = S[i];
		}
		else if (S[i] == ')')
		{
			while (pos > 0 && Ope[pos-1] != '(')
			{
				pos--;
				switch (Ope[pos])
				{
				case'+':
					Opn[POS - 2] = Opn[POS-2] + Opn[POS - 1];
					break;
				case'-':
					Opn[POS - 2] = Opn[POS-2] - Opn[POS - 1];
					break;
				case'*':
					Opn[POS - 2] = Opn[POS-2] * Opn[POS - 1];
					break;
				case'/':
					Opn[POS - 2] = Opn[POS-2] / Opn[POS - 1];
					break;
				default:
					break;
				}
				POS--;
			}
			Ope[pos++] = S[i];
			pos = pos - 2;
		}
		else if (numpos <= num[0] && ((S[i + 1] < '0' || S[i + 1]>'9') && S[i + 1] != '.'))
		{
			Opn[POS++] = num[numpos++];
		}
	}
	while (pos > 0 && Ope[pos - 1] != '(')
	{
		pos--;
		switch (Ope[pos])
		{
		case'+':
			Opn[POS - 2] = Opn[POS - 2] + Opn[POS - 1];
			break;
		case'-':
			Opn[POS - 2] = Opn[POS - 2] - Opn[POS - 1];
			break;
		case'*':
			Opn[POS - 2] = Opn[POS - 2] * Opn[POS - 1];
			break;
		case'/':
			Opn[POS - 2] = Opn[POS - 2] / Opn[POS - 1];
			break;
		default:
			break;
		}
		POS--;
	}
	cout <<"answer: " << Opn[0] << endl;
	return pos == 0;
}
//5+7*3-(6*2+1)/10
int main() {
	std::string S;
	std::cout << "ÇëÊäÈëËãÊý±í´ïÊ½:";
	std::cin >> S;
	char* Ope = new char[S.length()];
	float num[StrExtFloat_flen] = { 0. };
	StrExtFloat(num, S);
	//printf("\n Total:%2.0f", num[0]);
	//for (int i = 1; i <= num[0]; i++)
	//	printf("\n %d:%.4f", i, num[i]);
	//bool flag = isValid(S, Ope, num);
	bool flag = isValid(S,num);
	if (!flag) {
		delete[] Ope;
		return -1;
	}
	else {
		//std::cout << "À¨ºÅÆ¥Åä!";
		delete[] Ope;
		return 0;
	}
}
/*
		switch (S[i]) {
		case'+'://std::cout << "¼ÓºÅ\n";
			if (pos == 0 || (Ope[pos - 1] != '*' && Ope[pos - 1] != '/'))
			{
				Ope[pos++] = S[i];
			}
			else if ((Ope[pos - 1] == '*' || Ope[pos - 1] == '/'))
			{
				while (pos >= 0)
				{
					pos--;
					if (Ope[pos] == '*')
					{
						Opn[POS - 1] = Opn[POS] * Opn[POS - 1];
					}
					if (Ope[pos] == '/')
					{
						Opn[POS - 1] = Opn[POS] / Opn[POS - 1];
					}
				}
			}
				break;
		case'-'://std::cout << "¼õºÅ\n";
			Ope[pos++] = S[i];
			break;
		case'*'://std::cout << "³ËºÅ\n";
			Ope[pos++] = S[i];
			break;
		case'/'://std::cout << "³ýºÅ\n";
			Ope[pos++] = S[i];
			break;
		case '('://std::cout << "×óÐ¡À¨ºÅ\n";
			Ope[pos++] = S[i];
			break;
		case '['://std::cout << "×óÖÐÀ¨ºÅ\n";
			Ope[pos++] = S[i];
			break;
		case '{'://std::cout << "×ó´óÀ¨ºÅ\n";
			Ope[pos++] = S[i];
			break;
		case ')':
			if (pos == 0 || Ope[pos - 1] != '(') {
				std::cout << "ÓÒÐ¡À¨ºÅ²»Æ¥Åä!";
				return false;
			}
			else {
				//std::cout << "ÓÒÐ¡À¨ºÅ\n";
				pos--;
			}
			break;
		case ']':
			if (pos == 0 || Ope[pos - 1] != '[') {
				std::cout << "ÓÒÖÐÀ¨ºÅ²»Æ¥Åä!";
				return false;
			}
			else {
				//std::cout << "ÓÒÖÐÀ¨ºÅ\n";
				pos--;
			}
			break;
		case '}':
			if (pos == 0 || Ope[pos - 1] != '{') {
				std::cout << "ÓÒ´óÀ¨ºÅ²»Æ¥Åä!";
				return false;
			}
			else {
				//std::cout << "ÓÒ´óÀ¨ºÅ\n";
				pos--;
			}
			break;
		default:
			if (numpos <= num[0] && ((S[i + 1] < '0' || S[i + 1]>'9') && S[i + 1] != '.'))
			{
				//std::cout << "²Ù×÷Êý:" << num[numpos++] << std::endl;
				Opn[POS++] = num[numpos++];
			}
			break;
		}
		*/
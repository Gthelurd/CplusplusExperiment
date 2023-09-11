#include <iostream>
#include <cstring>

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
��С����
������:2
�Ӻ�
������:3
��С����
�˺�
������:4
����ƥ��!

Test Case 2:
Input: "{2+3]*4"
Expected Output:
�������
�Ӻ�
������: 2
������: 3
�������Ų�ƥ��!

Test Case 3:
Input: "2+3)*4"
Expected Output:
������:2
�Ӻ�
������:3
��С���Ų�ƥ��!

Test Case 4:
Input: "2+3"
Expected Output:
������:2
�Ӻ�
������:3
����ƥ��!

Please note that these are just a few examples, and you can create additional test cases based on your specific requirements.
*/

bool isValid(const std::string& S, char* Ope,float *num) {
	int pos = 0;
	int numpos = 1;
	for (int i = 0; i < S.length(); i++) {
		switch (S[i]) {
		case'+':std::cout << "�Ӻ�\n";
			break;
		case'-':std::cout << "����\n";
			break;
		case'*':std::cout << "�˺�\n";
			break;
		case'/':std::cout << "����\n";
			break;
		case '(':std::cout << "��С����\n";
			Ope[pos++] = S[i];
			break;
		case '[':std::cout << "��������\n";
			Ope[pos++] = S[i];
			break;
		case '{':std::cout << "�������\n";
			Ope[pos++] = S[i];
			break;
		case ')':
			if (pos == 0 || Ope[pos - 1] != '(') {
				std::cout << "��С���Ų�ƥ��!";
				return false;
			}
			else {
				std::cout << "��С����\n";
				pos--;
			}
			break;
		case ']':
			if (pos == 0 || Ope[pos - 1] != '[') {
				std::cout << "�������Ų�ƥ��!";
				return false;
			}
			else {
				std::cout << "��������\n";
				pos--;
			}
			break;
		case '}':
			if (pos == 0 || Ope[pos - 1] != '{') {
				std::cout << "�Ҵ����Ų�ƥ��!";
				return false;
			}
			else {
				std::cout << "�Ҵ�����\n";
				pos--;
			}
			break;
		default:
			if (numpos <= num[0] && ((S[i + 1] < '0' || S[i + 1]>'9')&&S[i+1]!='.'))
			{
				std::cout <<"������:" << num[numpos++] << std::endl;
			}
			break;
		}
	}
	return pos == 0;
}

int main() {
	std::string S;
	std::cout << "�������������ʽ:";
	std::cin >> S;
	char* Ope = new char[S.length()];
	float num[StrExtFloat_flen] = { 0. };
	StrExtFloat(num, S);
	//printf("\n Total:%2.0f", num[0]);
	//for (int i = 1; i <= num[0]; i++)
	//	printf("\n %d:%.4f", i, num[i]);
	bool flag = isValid(S, Ope,num);
	if (!flag) {
		delete[] Ope;
		return -1;
	}
	else {
		std::cout << "����ƥ��!";
		delete[] Ope;
		return 0;
	}
}

/*
Sure! Here are some simplified test cases for the  `isValid`  function:

1. Test Case:  `"{[()({[]})]}"`
   - Expected Output: No error message

2. Test Case:  `"{[(()(]})]}"`
   - Expected Output: "�������Ų�ƥ��!"

3. Test Case:  `"{1+2.4*(3+4]/5-8}"`
   - Expected Output: "�������Ų�ƥ��!"

4. Test Case:  `"{1+2.4*(3+4)/5-8}"`
   - Expected Output: No error message

5. Test Case:  `"((()))"`
   - Expected Output: No error message

6. Test Case:  `"(())()"`
   - Expected Output: No error message

7. Test Case:  `"())("`
   - Expected Output: "��С���Ų�ƥ��!"

8. Test Case:  `"[[]]"`
   - Expected Output: No error message

9. Test Case:  `"[[]"`
   - Expected Output: "�������Ų�ƥ��!"

10. Test Case:  `"{()}"`
	- Expected Output: No error message

Please note that these test cases cover various scenarios, including different types of brackets and mismatched brackets.
*/

#include "lb_8.h"

void lb_8::display_exercise(const int num)
{
	switch (num)
	{
	case 1:
		ex1();
		break;
	case 2:
		ex2();
		break;
	case 3:
		ex3();
		break;
	default: 
		break;
	}
}

void lb_8::ex1()
{
	long X = 4;							// ������ ������ ��� ���������
	long REZ[6];						// 6 ����� ������ ��� �����������

	_asm
	{
		lea	EBX, REZ					; �������� ������ ����������� � ������� EBX
		mov	ECX, 6						; ������� ���������� ���������� �����

		m1 :
			mov	EAX, 3					; EAX = 3
			imul	X					; EAX = 3 * x
			imul	X					; EAX = 3 * x ^ 2
			add	EAX, 20					; EAX = 3 * x ^ 2 + 20
			mov	EDI, EAX				; ��������� ����������� � ������� EDI

			mov	EAX, 2500				; EAX = 2500
			imul	X					; EAX = 2500 * x
			sub	EAX, 8					; EAX = 2500 * x � 8

			cdq							; ���������� �������� - �������� � EAX - EDX
			div	EDI						; ������� � EAX, ������� � EDX

			shr	EDI, 1					; ������� �����������(��������) �� 2
			cmp	EDI, EDX				; ��������� �������� �������� � ��������
			adc	EAX, 0					; ���������� � �������� ����� �� ���������
			mov	dword ptr[EBX], EAX		; ��������� ���������� � ������
			add	EBX, 4					; ���������� ������ �����������
			add	X, 3					; ���������� ���������
		loop m1							; ������������ �� �������� � ���
	}

	for (auto element : REZ)
		std::cout << element << " ";
	std::cout << std::endl;
}

void lb_8::ex2()
{
	long	X = 1;							// ������ ������ ��� ���������
	long	P = 1; 							// ������ ��� ���������� 7^x	
		// Y = (7^x) / (5 * x^2)  >> 300
	_asm
	{
		m1: inc X							; ���������� ���������

			mov	EAX, 5						; EAX = 5
			imul	X						; EAX = 5 * x
			imul	X						; EAX = 5 * x ^ 2
			mov	EDI, EAX					; ��������� ����������� � ������� EDI

			mov	EAX, 7						; EAX = 7
			mul	P							; ��������� � 7^x
			mov	P, EAX						; ��������� 7^x � ������ ������ �

			cdq
			div	EDI							; ������� � EAX, ������� � EDX

			cmp	AL, 300						; ��������� ������� � 300
		jc	m1								; �������, ���� ������� ������ 300
	}
	std::cout << X << std::endl;
}

void lb_8::ex3()
{
	long const x_count = 12;
	long	x[x_count] = { 1,2,3,4,5,6,7,8,9,10,11,12 };
	//long	x[x_count] = { 9,20,3,6,8,5,11,7,4,1,2,5 };

	long	S = 0;
	long res;

	_asm
	{
		lea	EBX, x							; ��������� ����� ������� � � ���
		mov	ECX, 12							; ������� ����������

		cycle :
			mov	EAX, dword ptr[EBX]			;������ ������� � � ���
			add	S, EAX						; ���������� �����
			mov	EDI, EBX					; ����� �������� � � EDI
			add EBX, 4						; ���������� ������
		loop	cycle						; ������������ �� ��������

		mov EAX, S
		mov EDI, x_count

		cdq
		div EDI

		shr	EDI, 1							; ������� �����������(��������) �� 2
		cmp	EDI, EDX						; ��������� �������� �������� � ��������
		adc	EAX, 0							; ���������� � �������� ����� �� ���������

		mov res, EAX
	}
	std::cout << res << std::endl;
}
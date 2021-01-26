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
	long X = 4;							// €чейка пам€ти дл€ аргумента
	long REZ[6];						// 6 €чеек пам€ти дл€ результатов

	_asm
	{
		lea	EBX, REZ					; загрузка адреса результатов в регистр EBX
		mov	ECX, 6						; счетчик количества повторений цикла

		m1 :
			mov	EAX, 3					; EAX = 3
			imul	X					; EAX = 3 * x
			imul	X					; EAX = 3 * x ^ 2
			add	EAX, 20					; EAX = 3 * x ^ 2 + 20
			mov	EDI, EAX				; пересылка знаменател€ в регистр EDI

			mov	EAX, 2500				; EAX = 2500
			imul	X					; EAX = 2500 * x
			sub	EAX, 8					; EAX = 2500 * x Ц 8

			cdq							; расширение операнда - делимого в EAX - EDX
			div	EDI						; частное Ц EAX, остаток Ц EDX

			shr	EDI, 1					; деление знаменател€(делител€) на 2
			cmp	EDI, EDX				; сравнение половины делител€ с остатком
			adc	EAX, 0					; добавление к частному заема от сравнени€
			mov	dword ptr[EBX], EAX		; пересылка результата в пам€ть
			add	EBX, 4					; увеличение адреса результатов
			add	X, 3					; увеличение аргумента
		loop m1							; зацикливание по счетчику в ≈—’
	}

	for (auto element : REZ)
		std::cout << element << " ";
	std::cout << std::endl;
}

void lb_8::ex2()
{
	long	X = 1;							// €чейка пам€ти дл€ аргумента
	long	P = 1; 							// €чейка дл€ накоплени€ 7^x	
		// Y = (7^x) / (5 * x^2)  >> 300
	_asm
	{
		m1: inc X							; увеличение аргумента

			mov	EAX, 5						; EAX = 5
			imul	X						; EAX = 5 * x
			imul	X						; EAX = 5 * x ^ 2
			mov	EDI, EAX					; пересылка знаменател€ в регистр EDI

			mov	EAX, 7						; EAX = 7
			mul	P							; умножение Ц 7^x
			mov	P, EAX						; пересылка 7^x в €чейку пам€ти –

			cdq
			div	EDI							; частное Ц EAX, остаток Ц EDX

			cmp	AL, 300						; сравнение функции с 300
		jc	m1								; переход, если функци€ меньше 300
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
		lea	EBX, x							; начальный адрес массива Ц в ≈¬’
		mov	ECX, 12							; счетчик повторений

		cycle :
			mov	EAX, dword ptr[EBX]			;первый элемент Ц в ≈ј’
			add	S, EAX						; накопление суммы
			mov	EDI, EBX					; адрес элемента Ц в EDI
			add EBX, 4						; увеличение адреса
		loop	cycle						; зацикливание по счетчику

		mov EAX, S
		mov EDI, x_count

		cdq
		div EDI

		shr	EDI, 1							; деление знаменател€(делител€) на 2
		cmp	EDI, EDX						; сравнение половины делител€ с остатком
		adc	EAX, 0							; добавление к частному заема от сравнени€

		mov res, EAX
	}
	std::cout << res << std::endl;
}
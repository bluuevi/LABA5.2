#include <iostream>
using namespace std;
unsigned long check_with_borders(unsigned long a, unsigned long min, unsigned long max)
{
    while (!(cin >> a) || (a < min) || (a > max)) // пока не будет введено число больше мин и меньше макс
    {
        if (((cin.fail())) || (a < min) || (a > max)) // если ошибка ввода 
        {
            cout << "Повторите попытку" << endl;
            cin.clear(); // Очищаем буфер ввода 
            cin.ignore(1000, '\n'); // Убирает новую строку из cin 
        }
    } return a; // возвращение функцией числа, прошедшего проверку 
}
void DecToBin32(unsigned long Dec)
{
    unsigned long mask = 1 << 31; // 2147483648 или же число где в старшем бите 1, остальные 0
    for (int i = 0; i < 32; i++) // перебор всех битов числа
    {  
        if (Dec & mask) // бит, который проверяется, умножается на 1, остальные на 0
            cout << '1'; // если ненулевое число, значит на месте бита, который проверяется, стоит 1
        else
            cout << '0'; // иначе 0
        mask >>= 1;
        if ((i + 1) % 8 == 0) //если конец строки
       {
        cout << endl; //новая строка
       }
    }
    cout << endl;
}
void DecToBin64(unsigned long long Dec)
{
    unsigned long long mask = 9223372036854775808;
    for (int i = 0; i < 64; i++) 
    {
            if (Dec & mask) // бит, который проверяется, умножается на 1, остальные на 0
                cout << '1'; // если ненулевое число, значит на месте бита, который проверяется, стоит 1
            else
                cout << '0'; // иначе 0
            mask >>= 1;
            if ((i + 1) % 8 == 0)
            {
                 cout << endl;
            }
    }
    cout << endl;
}

unsigned long long column_xor(unsigned long long in, unsigned long long result, int ii, int kk )
{
    for (int i = 0; i < ii; i++) // будем проводить операции искл или 4 раза
    {
       unsigned long long xoor = 0; // вот в этой перемменной
       unsigned long long  maskxor = 1 << i; // двигаем маску на тот бит, оторый нам дальше нужен
        for (int k = 0; k < kk; k++) // будем брать по 1 биту в каждой последовательности из 4
        {
            xoor = xoor ^ (in & maskxor); // делаем искл или нужных элементов
            maskxor <<= ii; // двигаем на 4
            xoor <<= ii;
        }
        result |= xoor; // складываем
        maskxor <<= 1; // двигаем
        xoor <<= 1;
    }
    result |= in; // прибавляем первый результат, чтобы получилось то что нам надо
    return result;
}

int main()
{
    setlocale(LC_ALL, "Russian");
    cout << "Введите число от 1 до 134217727, это и будет исходное сообщение: "; //до 27битного числа сост из единиц
    unsigned long num = 0; 
    num = check_with_borders(num, 1, 134217727); //проверка на число
    cout << "Вы ввели: " << num << endl;
    cout << "Ваше сообщение в двоичной системе: " << endl;
   DecToBin32(num);
   unsigned long long num64 = num; //перевод в ячейку на 64 бит
   unsigned long long result1 = 0; 
   unsigned long long mask = 1; //маска для переписывания цифр
   unsigned long long maskxor = 1; // маска для искл или
   
    for (int i = 0; i < 9; i++) // для каджой тройки бит (всего 9 троек тк 27 бит)
    { 
        unsigned long long xoor = 0; // переменная для искл или
        for (int j = 0; j < 3; j++) // по 3 бита
        {
            result1 |= num64 & mask; //преписываем бит в перменную для результата
            mask <<=1; // двигаем максу
            xoor ^= num64 & maskxor; // искл или этого бита
            maskxor <<= 1; // двигаем маску искл или
            xoor <<= 1; // двигаем искл или, чтобы проделать операцию над следующим битом
        }
        result1 |= xoor; // добавляем искл или предыдущих трех бит в следующий
        maskxor <<= 1; //  двигаем маску искл или
        num64 <<= 1; // двигаем число, так как в нем мы посмотрели 3 бита, а вв результат написали 4
        mask <<= 1; // двигаем маску
    }
   
    unsigned long long result2 = 0; // работаем с предыдущим результатом, поэтому нужна новая переменная
    result2 = column_xor(result1, result2, 4, 9);
    unsigned long long result3 = 0; // работаем с предыдущим результатом, поэтому нужна новая переменная
    result3 = column_xor(result2, result3, 8, 5);

    cout << endl << "Результат: " << result3 << endl << "В двоичной системе: " << endl; 
    DecToBin64(result3);
}



/*
Задание 4. Реализация симуляции банкомата
Что нужно сделать
Требуется реализовать упрощённую симуляцию работы банкомата. В банкомате могут храниться только бумажные купюры номиналом от 100 до 
5000 рублей. Максимально в банкомате может храниться только 1000 купюр. Все они записываются в отдельный файл. У банкомата, 
как у устройства, две основных операции — снятие денег пользователем и наполнение деньгами инкассаторами банка.

Наполнение банкомата происходит, если при старте программы в консоль вводится символ плюс “+”. Количество купюр рассчитывается так, 
чтобы банкомат был заполнен полностью. Все купюры при этом выбираются случайным образом.
Если на старте программы в консоль вводится минус (“-”), то симулируется снятие пользователем денег. Пользователь указывает сумму с 
точностью до 100 рублей. Мы будем считать, что каждый клиент обладает неограниченным балансом в системе и теоретически может снять 
любую сумму. На практике, если данная сумма не может быть снята из-за отсутствия подходящих денег в машине, показывается сообщение, 
что эта операция невозможна.
После выполнения любой из операций программа завершает выполнение. Состояние банкомата должно храниться в отдельном бинарном файле, 
автономно.

Советы и рекомендации
Вы можете хранить массив купюр целиком, помечая отсутствующие позиции нулями.

Что оценивается
Корректность работы программы симуляции банкомата. Инкассация и снятие денег должны работать корректно.
*/

#include <iostream>
#include <fstream>
#include <ctime>
#include <vector>

using namespace std;

int get_sum_money_in_ATM(vector<int>& ATM){
    int sum = 0;
    sum = ATM[5] * 5000 + ATM[4] * 2000 + ATM[3]*1000+ ATM[2] * 500 + ATM[1] * 200 + ATM[0] * 100;
    return sum;
}

void print_file(vector<int>& ATM){
    cout << "Состояние банкомата: "<< endl;
    cout << "100 руб. - " << ATM[0] << endl;
    cout << "200 руб. - " << ATM[1] << endl;
    cout << "500 руб. - " << ATM[2] << endl;
    cout << "1000 руб. - " << ATM[3] << endl;
    cout << "2000 руб. - " << ATM[4] << endl;
    cout << "5000 руб. - " << ATM[5] << endl;
    cout << "Общее количество денег: " << get_sum_money_in_ATM(ATM) << endl;
    cout << endl;
}

void counting_issued_banknotes(int& index_in_vector, int denomination, int& sum){
        if (sum / denomination !=0){
            if (sum / denomination <= index_in_vector){
            index_in_vector = index_in_vector - (sum / denomination);
            cout << denomination << " руб. - " << sum / denomination << endl;
            sum = sum - (sum / denomination)*denomination;
            }
            else {
                cout << denomination << " руб. - " << index_in_vector << endl;
                index_in_vector = 0;
                sum = sum - index_in_vector*denomination;
            }
        } 
}

void give_money_to_client(vector<int>& ATM){
    ifstream file ("ATM.bin", ios::binary);
    if (file.is_open()){
        file.read((char*) &ATM[0], sizeof(ATM[0])*6);
    }
    else {
        cout << "Файл не открыт" << endl;
    }
    
    file.close();

    print_file(ATM);

    if (get_sum_money_in_ATM(ATM) == 0){
        cout << "В банкомате нет наличных" << endl;
    }
    else {

        cout << "Введите сумму кратную 100 руб.: ";
        int sum;
        cin >> sum;
        while (sum % 100 !=0){
            cout << "Сумма должна быть кратна 100." << endl << "Введите сумму кратную 100 руб.: ";
            cin >> sum;
        }

        while (sum > get_sum_money_in_ATM(ATM)){
            cout << "В банкомате не хватает наличных. Введите сумму меньшую или равную " << get_sum_money_in_ATM(ATM) << endl;
            cin >> sum;
        }

        print_file(ATM);

        cout << "Выданы купюры: " << endl;

        counting_issued_banknotes(ATM[5],5000,sum);
        counting_issued_banknotes(ATM[4],2000,sum);
        counting_issued_banknotes(ATM[3],1000,sum);
        counting_issued_banknotes(ATM[2],500,sum);
        counting_issued_banknotes(ATM[1],200,sum);
        counting_issued_banknotes(ATM[0],5000,sum);
        cout << endl;

        ofstream out_file ("ATM.bin", ios::binary);
        if (out_file.is_open()){
            out_file.write((char*) &ATM[0], sizeof(ATM[0])*6);
        }
        else {
            cout << "Файл не открыт" << endl;
        }
        out_file.close();

        print_file(ATM);
    }
}

void fill_ATM_money(vector<int>& ATM){
    srand(time(0));
        for (int i=0; i<1000; ++i){
            ++ATM[rand() % 6];

        }
        ofstream file("ATM.bin", ios::binary);
        if (file.is_open()){
            file.write((char*) &ATM[0], sizeof(ATM[0])*6);
        }
        else {
        cout << "Файл не открыт" << endl;
        }
        file.close();

        print_file(ATM);
}

int main(){
    setlocale(LC_ALL, "Russian");
    vector<int> ATM (6); /*будет хранить количетво купюр. Элемент с индексом "0" соответствует 100 руб. купюре, 
                1- 200 руб., 2 - 500 руб., 3 - 1000 руб.,  4 - 2000 руб., 5 - 5000 руб. */
    
    cout << "Какую оперцию вы желаете выполнить: " << endl << "введите символ \"+\" чтобы наполнить банкомат;" << 
            endl << "введите символ \"-\" чтобы снять наличные." << endl;
    char operation;
    cin >> operation;
    while (operation != '+' && operation != '-'){
        cout << "Введите символ + или -" << endl;
        cin >> operation;
    }

    if (operation == '+'){
        fill_ATM_money(ATM);
    }

    if (operation == '-'){
        give_money_to_client(ATM);
    }
}
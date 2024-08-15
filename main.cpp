/*
������� 4. ���������� ��������� ���������
��� ����� �������
��������� ����������� ���������� ��������� ������ ���������. � ��������� ����� ��������� ������ �������� ������ ��������� �� 100 �� 
5000 ������. ����������� � ��������� ����� ��������� ������ 1000 �����. ��� ��� ������������ � ��������� ����. � ���������, 
��� � ����������, ��� �������� �������� � ������ ����� ������������� � ���������� �������� ������������� �����.

���������� ��������� ����������, ���� ��� ������ ��������� � ������� �������� ������ ���� �+�. ���������� ����� �������������� ���, 
����� �������� ��� �������� ���������. ��� ������ ��� ���� ���������� ��������� �������.
���� �� ������ ��������� � ������� �������� ����� (�-�), �� ������������ ������ ������������� �����. ������������ ��������� ����� � 
��������� �� 100 ������. �� ����� �������, ��� ������ ������ �������� �������������� �������� � ������� � ������������ ����� ����� 
����� �����. �� ��������, ���� ������ ����� �� ����� ���� ����� ��-�� ���������� ���������� ����� � ������, ������������ ���������, 
��� ��� �������� ����������.
����� ���������� ����� �� �������� ��������� ��������� ����������. ��������� ��������� ������ ��������� � ��������� �������� �����, 
���������.

������ � ������������
�� ������ ������� ������ ����� �������, ������� ������������� ������� ������.

��� �����������
������������ ������ ��������� ��������� ���������. ���������� � ������ ����� ������ �������� ���������.
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
    cout << "��������� ���������: "<< endl;
    cout << "100 ���. - " << ATM[0] << endl;
    cout << "200 ���. - " << ATM[1] << endl;
    cout << "500 ���. - " << ATM[2] << endl;
    cout << "1000 ���. - " << ATM[3] << endl;
    cout << "2000 ���. - " << ATM[4] << endl;
    cout << "5000 ���. - " << ATM[5] << endl;
    cout << "����� ���������� �����: " << get_sum_money_in_ATM(ATM) << endl;
    cout << endl;
}

void counting_issued_banknotes(int& index_in_vector, int denomination, int& sum){
        if (sum / denomination !=0){
            if (sum / denomination <= index_in_vector){
            index_in_vector = index_in_vector - (sum / denomination);
            cout << denomination << " ���. - " << sum / denomination << endl;
            sum = sum - (sum / denomination)*denomination;
            }
            else {
                cout << denomination << " ���. - " << index_in_vector << endl;
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
        cout << "���� �� ������" << endl;
    }
    
    file.close();

    print_file(ATM);

    if (get_sum_money_in_ATM(ATM) == 0){
        cout << "� ��������� ��� ��������" << endl;
    }
    else {

        cout << "������� ����� ������� 100 ���.: ";
        int sum;
        cin >> sum;
        while (sum % 100 !=0){
            cout << "����� ������ ���� ������ 100." << endl << "������� ����� ������� 100 ���.: ";
            cin >> sum;
        }

        while (sum > get_sum_money_in_ATM(ATM)){
            cout << "� ��������� �� ������� ��������. ������� ����� ������� ��� ������ " << get_sum_money_in_ATM(ATM) << endl;
            cin >> sum;
        }

        print_file(ATM);

        cout << "������ ������: " << endl;

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
            cout << "���� �� ������" << endl;
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
        cout << "���� �� ������" << endl;
        }
        file.close();

        print_file(ATM);
}

int main(){
    setlocale(LC_ALL, "Russian");
    vector<int> ATM (6); /*����� ������� ��������� �����. ������� � �������� "0" ������������� 100 ���. ������, 
                1- 200 ���., 2 - 500 ���., 3 - 1000 ���.,  4 - 2000 ���., 5 - 5000 ���. */
    
    cout << "����� ������� �� ������� ���������: " << endl << "������� ������ \"+\" ����� ��������� ��������;" << 
            endl << "������� ������ \"-\" ����� ����� ��������." << endl;
    char operation;
    cin >> operation;
    while (operation != '+' && operation != '-'){
        cout << "������� ������ + ��� -" << endl;
        cin >> operation;
    }

    if (operation == '+'){
        fill_ATM_money(ATM);
    }

    if (operation == '-'){
        give_money_to_client(ATM);
    }
}
#include <iostream>
#include <fstream>
#include "./ofb_encr.h"
#include "../Libs/get_time.h"
using namespace std;


vector<bitset<16>> get_bitset_vector(string &str);
string get_string_(vector<bitset<16>> &set);
int get_sum(string str);


int main(){
    int menu; string path, key, iv;
    
    while (true){
        cout << 
        "2. Дешифровать файл, используя ECB." << endl << 
        "4. Дешифровать файл, используя OFB." << endl << 
        "5. Выйти из программы." << endl;
        cout << "> "; cin >> menu;

        switch (menu){
            case 2:{
                getline(cin, path);
                cout << "Введите путь к файлу: "; getline(cin, path);
                cout << "Введие пароль: "; getline(cin, key);

                ifstream in(path);
                if (in.is_open()) {
                    int sum;
                    in >> sum;

                    string cipher((istreambuf_iterator<char>(in)),
                        (istreambuf_iterator<char>())); cipher.erase(0, 1);

                    vector<bitset<16>> CIPHER = get_bitset_vector(cipher);
                    vector<bitset<16>> KEY = get_bitset_vector(key);
                    start_clock();
                    vector<bitset<16>> PL_TEXT = permute_decrypt(CIPHER, KEY);
                    cout << "Дешифрование длилось "; stop_clock(); cout << "c.\n";
                    
                    string plain_str = get_string_(PL_TEXT);
                    if(get_sum(plain_str) == sum){
                        ofstream out(path+"_decr");
                        out << get_string_(PL_TEXT);
                        out.close();
                        cout << "\033[32m" << "Успешно!" << "\033[0m\n";
                    } else cout << "\033[31m" << "Указан неверный пароль или iv!" << "\033[0m\n";
                } else 
                    cout << "Не удалось открыть файл!\n";
            }  break;
            case 4:{
                getline(cin, path);
                cout << "Введите путь к файлу: "; getline(cin, path);
                cout << "Введие пароль: "; getline(cin, key);
                cout << "Введите iv: "; getline(cin, iv);

                ifstream in(path);
                if (in.is_open()) {
                    int sum;
                    in >> sum;

                    string cipher((istreambuf_iterator<char>(in)),
                        (istreambuf_iterator<char>())); cipher.erase(0, 1);

                    vector<bitset<16>> CIPHER = get_bitset_vector(cipher);
                    vector<bitset<16>> KEY = get_bitset_vector(key);
                    vector<bitset<16>> IV = get_bitset_vector(iv);
                    start_clock();
                    vector<bitset<16>> PL_TEXT = ofb(CIPHER, KEY, IV);
                    cout << "Дешифрование длилось "; stop_clock(); cout << "c.\n";

                    string plain_str = get_string_(PL_TEXT);
                    if(get_sum(plain_str) == sum){
                        ofstream out(path+"_decr");
                        out << get_string_(PL_TEXT);
                        out.close();
                        cout << "\033[32m" << "Успешно!" << "\033[0m\n";
                    } else cout << "\033[31m" << "Указан неверный пароль или iv!" << "\033[0m\n";
                } else 
                    cout << "Не удалось открыть файл!\n";
            }  break;
            case 5:{
                return 0;
            } break;
        }
    }
}



vector<bitset<16>> get_bitset_vector(string &str){
    vector<bitset<16>> set;
    for (char symb: str)
        set.push_back(bitset<16>(symb));
    return set;
}
string get_string_(vector<bitset<16>> &set){
    string str;
    for(bitset<16> &el: set)
        str += el.to_int();
    return str;
}
int get_sum(string str){
    int sum = 0;
    for(char symb: str)
        sum+= symb;
    return sum;
}
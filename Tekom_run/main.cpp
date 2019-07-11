#include <iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>
#include<stdio.h>


using namespace std;
string token[100][3];
int i = 0;

//fungsi untuk mengecek keyword
string cekKeyword(string key){
    string keyword[33][2]=
    {
        {"if","if_fy"},
        {"do","do_fy"},
        {"downto","downto_fy"},
        {"div","div_fy"},
        {"repeat","repeat_fy"},
        {"record","record_fy"},
        {"begin","begin_fy"},
        {"case","case_fy"},
        {"const","const_fy"},
        {"string","string_fy"},
        {"then","thenfy"},
        {"type","type_fy"},
        {"to","to_fy"},
        {"while","while_fy"},
        {"function","function_fy"},
        {"for","for_fy"},
        {"procedure","procedure_fy"},
        {"program","program_fy"},
        {"array","array_fy"},
        {"and","and_fy"},
        {"not","not_fy"},
        {"or","or_fy"},
        {"of","of_fy"},
        {"mod","mod_fy"},
        {"var","var_fy"},
        {"end","end_fy"},
        {"else","else_fy"},
        {"until","until_fy"},
        {"ident","indent_fy"},
        {"integer","tipedata"},
        {"string","tipedata"},
        {"real","tipedata"},
        {"int","integer_fy"}
    };

    //pengecekan
    string result = "identifier";
    for(int i=0;i<=33;i++){
        if(keyword[i][0]==key){
            result = keyword[i][1];
        }
    }
    return result;
}

//fungsi untuk mengecek operator
string cekOperator(string key){
    string opr[10][2]=
    {
        {"<","operator_<"},
        {"<=","operator_<="},
        {"<>","operator_<>"},
        {"==","operator_=="},
        {">","operator_>"},
        {">=","operator_>="},
        {"*","operator_*"},
        {"/","operator_div>"},
        {"+","operator_+"},
        {"-","operator_-"}
    };

    //pengecekan
    string result = "unknow";
    for(int i=0;i<10;i++){
        if(opr[i][0]==key){
            result = opr[i][1];
        }
    }
    return result;
}

//fungsi untuk mengecek delimiter
string cekDelimiter(string key){
    string delimiter[10][2]=
    {
        {"(","l_parent"},
        {")","r_parent"},
        {"[","l_siku"},
        {"]","r_siku"},
        {";","semicolon"},
        {":","colon"},
        {",","coma"},
        {".","periode"},
        {":=","becomes"}
    };

    //pengecekan
    string result = "unknow";
    for(int i=0;i<9;i++){
        if(delimiter[i][0]==key){
            result = delimiter[i][1];
        }
    }
    return result;
}

//fungsi untuk menampilkan array token
void tampil_scanner(){
    cout << "HASIL DARI SCANNER \n";
    cout << "==================================\n";
    for(int j=0;j<i;j++){
        if(token[j][1] == "string"){
            cout << j << ".  \'" << token[j][0] << "\' = " << token[j][1] << " = " << token[j][2] << "\n";
        }else{
            cout << j << ".  " << token[j][0] << " = " << token[j][1] << " = " << token[j][2] << "\n";
        }

    }
    cout << "==================================\n";
    cout << "\n\n\n\n\n";
}

//funcsi untuk melakukan proses scanner
void scanner(){
    char ch = ' ';
    bool first = true;
    string kata = "";

    //mengambil text
    ifstream Myfile("program2.pas");

    //pengecekan apakah file ada atau tidak
	if(!Myfile.is_open()){
		cout<<"file program tidak ditemukan, harap periksa kembali\n";
		exit(0);
	}


    //melakukan pengecekan perkarakter
	while(!Myfile.eof()){
        if(first){
            ch = Myfile.get();
        }
        first = false;

        if(ch == '{'){
            ch = Myfile.get();
        }else
        if(ch == '\''){
            ch = Myfile.get();
            while(ch != '\''){
                kata = kata + ch;
                ch = Myfile.get();
            }
            token[i][0]=kata;
            token[i][1]="string";
            token[i][2]="identifier";
            i++;
            kata = "";
            ch = Myfile.get();
            //cout << "masuk ke sini inih " << ch << "\n";
            //ch = Myfile.get();
        }else
        if((ch>='A' && ch<='Z')||(ch>='a' && ch<='z')||ch=='_'){

            while((ch>='A' && ch<='Z')||(ch>='a' && ch<='z')||ch=='_'){
                kata = kata + ch;
                ch = Myfile.get();
            }
            string res = cekKeyword(kata);
            token[i][0]=kata;
            token[i][1]=res;
            if(res == "identifier"){
                token[i][2]="identifier";
            }else{
                token[i][2]="Keyword";
            }

            i++;
            kata = "";
        }else
        if(ch>='0' && ch<='9'){
            while(ch>='0' && ch<='9'){
                kata = kata + ch;
                ch = Myfile.get();
            }
            token[i][0]=kata;
            token[i][1]="integer";
            token[i][2]="identifier";
            i++;
            kata = "";
        }else
        if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'||ch=='='||ch=='<'||ch=='>'){
            while(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'||ch=='='||ch=='<'||ch=='>'){
                kata = kata + ch;
                ch = Myfile.get();
            }
            // cek apakah komentar ( // )
            if(kata == "//"){
                while(ch != '\n'){
                    ch = Myfile.get();
                    kata = "";
                }
            }else if(kata == "/*"){ //cek komentar ( /* ...... */ )
                while(kata != "*/" && !Myfile.eof()){
                    kata = "";
                    if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'||ch=='='||ch=='<'||ch=='>'){
                        while(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'||ch=='='||ch=='<'||ch=='>'){
                            kata = kata + ch;
                            ch = Myfile.get();
                        }
                    }else{
                        ch = Myfile.get();
                    }
                };
                kata = "";
            }else{
                string res = cekOperator(kata);
                token[i][0]=kata;
                token[i][1]=res;
                token[i][2]="Operator";
                i++;
                kata = "";
            }
        }else
        if(ch=='('||ch==')'||ch=='['||ch==']'||ch==':'||ch==';'||ch=='.'||ch==','){
            while(ch=='('||ch==')'||ch=='['||ch==']'||ch==':'||ch==';'||ch=='.'||ch==','||ch=='='){
                kata = kata + ch;
                ch = Myfile.get();
            }
            string res = cekDelimiter(kata);
            token[i][0]=kata;
            token[i][1]=res;
            token[i][2]="Delimiter";
            i++;
            kata="";
        }else{
            ch = Myfile.get();
        }
	}
}

int checkTitle(int num){
    if(token[num][0] != "program"){
        cout << "eror : program tidak dideklarasikan, token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;
    if(token[num][2] != "identifier"){
        cout << "eror : nama program [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;
    if(token[num][0] != ";"){
        cout << "eror : program not declared, token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;

    return num;
}

int checkVariable(int num){
    if(token[num][1] != "identifier"){
        cout << "eror : nama variabel [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;
    if(token[num][1] != "colon"){
        cout << "eror : colon tidak ditemukan [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;
    if(token[num][1] != "tipedata"){
        cout << "eror : tipedata tidak terdefinisi [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;
    if(token[num][1] != "semicolon"){
        cout << "eror : semicolon tidak terdefinisi [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;
    return num;
}

int checkVar(int num){
    cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    num++;
    while(token[num][0] != "begin"){
        num = checkVariable(num);
    }
    return num;
}

int checkIf(int num){
    cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    num++;
    if(token[num][1] != "l_parent"){
        cout << "eror : l_parent not found [" << token[num][0] << "[, token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;
    if(token[num][2] != "identifier"){
        cout << "eror : variable [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;
    if(token[num][2] != "Operator"){
        cout << "eror : operator  [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;
    if(token[num][2] != "identifier"){
        cout << "eror : variable [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;
    if(token[num][1] != "r_parent"){
        cout << "eror : r_parent not found [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;
    if(token[num][1] != "thenfy"){
        cout << "eror : then_fy not found [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
    }else{
        cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    }
    num++;

    return num;
}

int checkInput(int num){
    cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    num++;

    if(token[num][1] != "semicolon"){
        if(token[num][1] != "becomes"){
            cout << "eror : becomes [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
        }else{
            cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
        }
        num++;
        if(token[num][2] != "identifier"){
            cout << "eror : undefinied variable [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
        }else{
            cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
        }
        num++;
        while(token[num][2] == "Operator"){
            cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
            num++;
            if(token[num][2] != "identifier"){
            cout << "eror : undefinied variable [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
            }else{
                cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
            }
            num++;
        }
        if(token[num][1] != "semicolon"){
            cout << "eror : undefinied variable [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
        }else{
            cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
        }
        num++;
    }else{
        if(token[num][1] != "semicolon"){
            cout << "eror : undefinied variable [" << token[num][0] << "], token number : " << num << " [tidak diterima]\n"; exit(0);
        }else{
            cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
        }
        num++;
    }



    return num;
}

int checkBody(int num){
    cout << "token number "<< num << " - " << token[num][0] <<" [diterima] \n";
    num++;
    while((token[num][0] != "end" && token[num+1][0] != ".") && num <= i){
        if(token[num][1] == "if_fy"){
            num = checkIf(num);
        }else if(token[num][2] == "identifier"){
            num = checkInput(num);
        }else{
            num++;
        }
    }

    return num;
}

//melakukan pengecekan parser;
void Parser(){
    cout << "PARSER \n";
    cout << "=============================\n";
    int token_number = 0;
    token_number = checkTitle(token_number);
    if(token[token_number][0] == "var"){
        token_number = checkVar(token_number);
    };
    if(token[token_number][0] == "begin"){
        token_number = checkBody(token_number);
    };
    if(token[token_number][0] == "end" && token[token_number+1][0] == "." && token_number <= i){
        cout << "token number "<< token_number << " - " << token[token_number][0] <<" [diterima] \n";
        cout << "token number "<< token_number+1 << " - " << token[token_number+1][0] <<" [diterima] \n";
        cout << "String Diterima \n\n\n";
    }else{
        cout << "eror : end file not found, token number : " << token_number << " [tidak diterima]\n"; exit(0);
    }
}


//fungsi utama
int main()
{
    scanner();
	tampil_scanner();
	Parser();

	system("pause");
    return 0;
}



#include <iostream>
#include<fstream>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

using namespace std;
string token[100][3];
int i = 0;

//fungsi untuk mengecek keyword
string cekKeyword(string key){
    string keyword[30][2]=
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
        {"ident","indent_fy"}
    };

    //pengecekan
    string result = "identifier";
    for(int i=0;i<=30;i++){
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
    for(int j=0;j<i;j++){
        cout << token[j][0] << " = " << token[j][1] << " = " << token[j][2] << "\n";
    }
}


//fungsi utama
int main()
{
    char ch;
    string kata = "";

    //mengambil text
    ifstream Myfile("program.txt");

    //pengecekan apakah file ada atau tidak
	if(!Myfile.is_open()){
		cout<<"file program tidak ditemukan, harap periksa kembali\n";
		exit(0);
	}


    //melakukan pengecekan perkarakter
	while(!Myfile.eof()){
        if(i == 0){
            ch = Myfile.get();
            cout << "kepanggil nih \n";
        }else{
            ch = ' ';
            cout << "gak kepanggil nih \n";
        }



        if(ch == '{'){
            //isi disini
        }
        if(ch == '\''){
            //isi disini
        }
        if((ch>='A' && ch<='Z')||(ch>='a' && ch<='z')||ch=='_'){
            while((ch>='A' && ch<='Z')||(ch>='a' && ch<='z')||ch=='_'){
                kata = kata + ch;
                ch = Myfile.get();
            }
            string res = cekKeyword(kata);
            token[i][0]=kata;
            token[i][1]=res;
            token[i][2]="Keyword";
            i++;
            kata = "";
        }
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
        }
        if(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'||ch=='='||ch=='<'||ch=='>'){
            while(ch=='+'||ch=='-'||ch=='*'||ch=='/'||ch=='^'||ch=='='||ch=='<'||ch=='>'){
                kata = kata + ch;
                ch = Myfile.get();
            }
            //cek jika komentar

            string res = cekOperator(kata);
            token[i][0]=kata;
            token[i][1]=res;
            token[i][2]="Operator";
            i++;
            kata = "";
        }
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
        }
	}
	tampil_scanner();
    return 0;
}



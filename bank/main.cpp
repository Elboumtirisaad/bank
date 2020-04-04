//
// Created by saad on 22/03/2020.
//

//ifndef UNTITLED_BANK_H
//#define UNTITLED_BANK_H

#include <string>
#include<iostream>
#include<fstream>
#include<cstdlib>

using namespace std;
/*
using std::cout;
using std::cin;
using std::endl;
using std::fstream;
using std::ofstream;
using std::ifstream;
using std::ios;
*/
class Bank{
public :
    void enter_data() ;
    void show_data() const ;
    void write_rec();
    void read_rec()  ;
    void search_rec();
    void edit_rec();
    void delete_rec();
    //Bank(string id,const string& firsname,const string& lastname, float total):_id(id),_firstName(firsname),_lastName(lastname),_total_balance(total){}
private :
    char account_number[20];
    char firstName[10];
    char lastName[10];
    float total_Balance;
};

void Bank::enter_data ()
{
    cout<<"\nEnter the id oh the account : ";
    cin>>account_number;
    cout<<"Enter your First Name: ";
    cin>>firstName;
    cout<<"Enter your Last Name: ";
    cin>>lastName;
    cout<<"Enter your total Balance: ";
    cin>>total_Balance;
    cout<<endl;
}
void Bank::show_data() const {
    cout<<"Account Number: "<<account_number<<endl;
    cout<<"First Name: "<<firstName<<endl;
    cout<<"Last Name: "<<lastName<<endl;
    cout<<"Current Balance: Rs.  "<<total_Balance<<endl;
    cout<<"-------------------------------"<<endl;
}
void Bank::write_rec()
{
    ofstream outfile;
    outfile.open("record.bank", ios::binary|ios::app);
    enter_data();
    outfile.write(reinterpret_cast<char *>(this), sizeof(*this));
    outfile.close();
}
void Bank::read_rec()
{
    ifstream infile;
    infile.open("record.bank", ios::binary);
    if(!infile)
    {
        cout<<"Error in Opening! File Not Found!!"<<endl;
        return;
    }
    cout<<"\n****Data from file****"<<endl;
    while(!infile.eof())
    {
        if(infile.read(reinterpret_cast<char*>(this), sizeof(*this)) )//
        {
            show_data();
        }
    }
    infile.close();
}
void Bank::search_rec()
{

    ifstream file;
    int n;

    file.open("record.bank", ios::binary);
    if(!file)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    file.seekg(0,ios::end);
    int count = file.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Search: ";
    cin>>n;
    file.seekg((n-1)*sizeof(*this));
    file.read(reinterpret_cast<char*>(this), sizeof(*this));
    show_data();
}
void Bank::edit_rec()
{
    int n;
    fstream file;
    file.open("record.bank", ios::in|ios::binary);
    if(!file)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    file.seekg(0, ios::end);
    int count = file.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to edit: ";
    cin>>n;
    file.seekg((n-1)*sizeof(*this));
    file.read(reinterpret_cast<char*>(this), sizeof(*this));
    cout<<"Record "<<n<<" has following data"<<endl;
    show_data();
    file.close();
    file.open("record.bank", ios::out|ios::in|ios::binary);
    file.seekp((n-1)*sizeof(*this));
    cout<<"\nEnter data to Modify "<<endl;
    enter_data();
    file.write(reinterpret_cast<char*>(this), sizeof(*this));
}
void Bank::delete_rec()
{
    int n;
    ifstream file;
    file.open("record.bank", ios::binary);
    if(!file)
    {
        cout<<"\nError in opening! File Not Found!!"<<endl;
        return;
    }
    file.seekg(0,ios::end);
    int count = file.tellg()/sizeof(*this);
    cout<<"\n There are "<<count<<" record in the file";
    cout<<"\n Enter Record Number to Delete: ";
    cin>>n;
    fstream tmpfile;
    tmpfile.open("tmpfile.bank", ios::out|ios::binary);
    file.seekg(0);
    for(int i=0; i<count; i++)
    {
        file.read(reinterpret_cast<char*>(this),sizeof(*this));
        if(i==(n-1))
            continue;
        tmpfile.write(reinterpret_cast<char*>(this), sizeof(*this));
    }
    file.close();
    tmpfile.close();
    remove("record.bank");
    rename("tmpfile.bank", "record.bank");
}
int main() {
    Bank B;
    int choice;
    cout<<"***Acount Information System***"<<endl;
    while(true)
    {
        cout<<"Select one option below ";
        cout<<"\n\t1-->Add record to file";
        cout<<"\n\t2-->Show record from file";
        cout<<"\n\t3-->Search Record from file";
        cout<<"\n\t4-->Update Record";
        cout<<"\n\t5-->Delete Record";
        cout<<"\n\t6-->Quit";
        cout<<"\nEnter your choice: ";
        cin>>choice;
        switch(choice)
        {
            case 1:
                B.write_rec();
                break;
            case 2:
                B.read_rec();
                break;
            case 3:
                B.search_rec();
                break;
            case 4:
                B.edit_rec();
                break;
            case 5:
                B.delete_rec();
                break;
            case 6:
                break;
            default:
                cout<<"\nEnter corret choice";
                exit(0);

        }

    }
    return 0;
}

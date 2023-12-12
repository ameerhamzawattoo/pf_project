#include <iostream>
#include <string>
#include <fstream>
#include <conio.h>
using namespace std;
class customer
{
    string name;
    string contact;
    string address;
    char gender;

public:
    void setdata(int rno, ofstream &fin)
    {
        fin.open("CUSTOMER_DATA.txt", ios::app);
        cout << "DATA FOR ROOM NO: " << rno;
        cout << endl
             << "ENTER CUSTOMER NAME: ";
        cin.ignore();
        getline(cin, name);
        fin << endl
            << "ROOM NO :" << rno << endl
            << name << endl;
        cout << "ENTER CUSTOMER GENDER: ";
        cin >> gender; // EXCEPTION HANDLING
        fin << gender << endl;
        cout << "ENTER CUSTOMER CONTACT NUMBER : ";
        cin >> contact;
        fin << contact << endl;
        cout << "ENTER CUSTOMER Address: ";
        cin.ignore();
        getline(cin, address);
        fin << address << endl
            << "**************";
        fin.close();
    }
    void getdata()
    {
        cout << "CUSTOMER NAME: " << name;
        cout << endl
             << "GENDER: " << gender;
        cout << endl
             << "CONTACT NUMBER: " << contact;
        cout << endl
             << "ADDRESS: " << address;
    }
    void comp_file_data_retriving(int counter, ifstream &fout)
    {
        string datfr;
        cout << endl
             << "YOU HAVE TOTAL " << counter << " CUSTOMERS" << endl;
        fout.open("CUSTOMER_DATA.txt");
        while (!fout.eof())
        {
            getline(fout, datfr);
            cout << datfr << endl;
        }
        fout.close();
        cout << "PRESS ANY KEY TO CONTINUE....";
        getch();
    }
};
class hotel
{
protected:
    bool r[35] = {0};
    int counter = 0;
    ofstream fin;
    ifstream fout;

public:
    virtual void main_menu() = 0;
    static int count;
};
class room : public hotel
{
    customer c[100];
    int *saveroom[1000];
    customer getdata;
    int temp;

public:
    void a_rooms()
    {
        cout << "ROOM NO:   \t STATUS\n";
        for (int i = 0; i <= 34; i++)
        {
            cout << i + 1 << "  ";
            cout << "\t \t";
            if (r[i] == 0)
            {
                cout << " AVAILLABLE";
            }
            else if (r[i] == 1)
            {
                cout << " OCCUPIED";
            }
            else
            {
                cout << " NO STATUS";
            }
            cout << endl;
        }
    }
    void main_menu()
    {
        bool l1 = true;
        do
        {
            system("CLS");
            cout << "\tMENU" << endl;
            cout << "1. ROOMS STATUS " << endl;
            cout << "2. CHECK IN " << endl;
            cout << "3. CUSTOMERS INFO" << endl;
            cout << "4. EXIT THE PROGRAM" << endl;
            cin >> temp;
            switch (temp)
            {
            case 1:
                a_rooms();
                int temp1;
                while (true)
                {
                    cout << "ENTER 1 TO CHECK IN" << endl;
                    cout << "ENTER 2 TO GO BACK TO PREVIOUS MENU" << endl;
                    cout << "ENTER 3 TO EXIT THE PROGRAM" << endl;
                    cin >> temp1;
                    if (temp1 == 1)
                    {
                        checkin();
                        break;
                    }
                    else if (temp1 == 2)
                    {
                        break;
                    }
                    else if (temp)
                    {
                        l1 = false;
                        break;
                    }
                    else
                    {
                        cout << "WRONG INPUT--TRY AGAIN " << endl;
                    }
                }
                break;
            case 2:
                checkin();
                break;
            case 3:
                int search;
                cout << "1.ROOM DATA INFO  \n2.FULL DATABASE \n3.SEARCH BY CUSTOMER NAME\n";
                cin >> search;
                switch (search)
                {
                case 1:
                    int inin;
                    bool boolin;
                    while (true)
                    {
                        a_rooms();
                        cout << "ENTER ROOM NUMBER TO SEARCH DATA: ";
                        cin >> inin;
                        boolin = room_check(inin);
                        if (boolin == 1)
                        {
                            int tt = *saveroom[inin];
                            c[tt].getdata();
                            cout << endl
                                 << "PRESS ENTER TO CONTINUE....";
                            getch();
                            break;
                        }
                        else if (boolin == 0)
                        {
                            cout << endl
                                 << "ROOM IS AVAILLABLE FOR CHECK IN" << endl;
                            getch(); // add some functionality
                            checkin();
                            break;
                        }
                        else
                            cout << "WRONG INPUT";
                    }
                    break;
                case 2:
                    getdata.comp_file_data_retriving(counter, fout);
                    break;
                case 3:
                    // complete this part
                    break;
                default:
                    cout << "imp?";
                }
                break;
            case 4:
                l1 = false;
                break;
            default:
                cout << "INVALID INPUT";
            }
        } while (l1 == true);
    }

    void checkin()
    {
        int tempin;
        bool ch;
        do
        {
            system("CLS");
            a_rooms();
            cout << "ENTER ROOM NO:";
            cin >> tempin;
            ch = room_check(tempin);
            if (ch == 0)
            {
                int tempc = counter;
                counter++;
                r[tempin - 1] = 1;
                c[tempc].setdata(tempin, fin);
                saveroom[tempin] = new int(tempc);
                cout << endl
                     << endl
                     << "YOUR DATA SAVED SUCCESSFULLY.....";
                cout << endl
                     << "press any key to continue...";
                getch();
            }
            else if (ch = 1)
            {

                cout << "ALREADY OCCUPIED \n PLEASE CHOOSE ANOTHER ROOM\n";
                char tchk;
                cout << "PRESS ANY KEY TO CONTINUE..."
                     << " OR  ENTER * FOR MAIN MENU" << endl;
                tchk = getch();
                ch = (tchk == '*') ? 0 : 1;
            }
            else
                cout << endl
                     << "wrong input TRY again" << endl;
        } while (ch != 0);
    }
    bool room_check(int in)
    {
        for (int i = 0; i < 34; i++)
        {
            if (r[in - 1] == 0)
            {
                return 0;
            }
        }
        return 1;
    }
};
int main()
{
    hotel *h1;
    room r1;
    h1 = &r1;
    h1->main_menu();
}
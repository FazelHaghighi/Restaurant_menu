#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <fstream>
using namespace std;

void welcome(int &j);
void orderslist(int j,string key);
void allorders(vector <string> orders,vector<double> numbers, int j);
void byebye();
void firstpage(vector <string> orders, vector<double> numbers, int j);
void mainmenu(vector <string> orders, vector<double> numbers, int j);
void managementmenu(int j);
void foodmenu(vector <string> orders, vector<double> numbers, int j);
void pizza(vector <string> orders, vector<double> numbers, int j);
void burger(vector <string> orders, vector<double> numbers, int j);
void fried(vector <string> orders, vector<double> numbers, int j);
void appetizer(vector <string> orders, vector<double> numbers, int j);
void drink(vector <string> orders, vector<double> numbers, int j);
void Select(int j);

int main()
{
    int j;
    ofstream all ("all.txt",ios::app);
    all.close();
    ifstream ID ("ID.txt");
    if(!ID.is_open())
    {
        ofstream Id ("ID.TXT");
        Id << "1\n";
        Id.close();
    }
    Select(j);
}
void Select(int j)
{
    system("cls");
    cout << "\x1b[36m* WELCOME *\n";
    cout << "\n\x1b[33m1. Customer Menu" << "\n\x1b[32m2. Management Menu" << "\n\x1b[0m0. Exit\n\n";
    int opt;
    cin >> opt;
    if(opt == 1) welcome(j);
    if (opt == 2) managementmenu(j);
    if (opt == 0) byebye();
}
void welcome(int &j)
{
    
    int sure,exit=1;
    vector <string> orders; 
    vector<double> numbers;
    ifstream id ("ID.txt");
    id >> j;
    id.close();
    system("cls");
    while(exit)
    {
        cout << "\x1b[36m* WELCOME *\n\n" << "\x1b[0mNew receipt number is: " << j << "\n\nEnter your receipt number for assurance: " << "\n\n0. Back\n\n";
        cin >> sure;
        ifstream check (to_string(sure).c_str());
        if(sure == 0)
        {
            Select(j);
            exit = 0;
            return;
        }
        if(check.is_open())
        {
            orderslist(j,to_string(sure));
            exit = 0;
        }
        else if ( sure == j) 
        {
            exit = 0;
            firstpage(orders, numbers, j);
        }
        else
        {
            system("cls");
            cout << "\x1b[31mReceipt Not Found!\n\x1b[0m";
        }
    }
    
}
void orderslist(int j,string key)
{
    vector <string> orders; 
    vector<double> numbers;
    
    int payoption, waiting = 0, waiting1 = 0, waiting2 = 0, waiting3 = 0, waiting4 = 0;
    string receipt,line,item,payment;
    double total = 0;
    if (key == "no")
    {
        do
        {
            cout << "\nPlease enter your receipt number:\n\n" << "0. Back\n";
            cin >> receipt;
            if ( receipt == "0") allorders(orders, numbers, j);
            ifstream find (receipt.c_str());
            if(find.is_open()) break;
            else
            {
                system("cls");
                cout << "Receipt Not Found!\n\n";
            }
        } while ( receipt != "0");
    }
    else receipt = key;
    ifstream Receipt (receipt.c_str());
    if (Receipt.is_open())
    {   
        getline(Receipt,payment);
        while(getline(Receipt,line))
        {
            stringstream LINE (line);
            orders.push_back(string());
            numbers.push_back(double());
            getline(LINE,orders[orders.size()-1],'#');
            getline(LINE,item,'#');
            numbers[numbers.size()-1] = stod(item);
        }
        system("cls");
        cout << receipt << ".\n";
        for ( int i = 0; i < numbers.size(); i++)
        {
            if ( orders[i] == "Neapolitan Pizza" || orders[i] == "Veggie Pizza" || orders[i] == "Pepperoni Pizza" || orders[i] == "Meat Pizza" || orders[i] == "Margherita Pizza" || orders[i] == "Greek Pizza") 
            {
                waiting1 = 20;
                if ( waiting1 > waiting) waiting = waiting1;
            }
            else if ( orders[i] == "Cheeseburger" || orders[i] == "Hamburger" || orders[i] == "Beef Burger" || orders[i] == "Elk Burger" || orders[i] == "Veggie Burger" || orders[i] == "Bison Burger")
            {
                waiting2 = 18;
                if ( waiting2 > waiting) waiting = waiting2;
            }
            else if ( orders[i] == "2 pieces" || orders[i] == "3 pieces" || orders[i] == "5 pieces" || orders[i] == "Chicken Strip" || orders[i] == "Fillet Strip")
            {
                waiting3 = 15;
                if ( waiting3 > waiting) waiting = waiting3;
            }
            else if ( orders[i] == "French Fries" || orders[i] == "Salad" || orders[i] == "Garlic Bread")
            {
                waiting4 = 10;
                if ( waiting4 > waiting) waiting = waiting4;
            }
            cout << orders[i] << " .............................. \x1b[35m$" << numbers[i] << "\x1b[0m\n";
        }
        for ( int i = 0; i < numbers.size(); i++)
        {
            total += numbers[i];
        }
        cout << "\nTotal Price: \x1b[35m$" << total << "\n\x1b[0mPreparing time:\x1b[35m " << waiting << " min\x1b[0m";
        cout << "\n\nPlease select the option you want:\n\n";
        if (payment == "0") cout << "1. Pay the bill\n" ;
        else cout << "\x1b[36m **Payment Done**\x1b[0m\n\n";
        cout << "0. Back\n";
        cin >> payoption;
        if (payment == "0" && payoption == 1 )
        {
            ofstream update (receipt.c_str());
            update << "1\n";
            for (int i = 0; i < orders.size(); i++) update << orders[i] << "#" << numbers[i] << endl;
            update.close();
            cout << "\x1b[32mPayed\x1b[0m\n\n0. Exit\n";
            cin >> payoption;
            welcome(j);
        }
        else if (payoption == 0 && key != "no") welcome(j);
        else if ( payoption == 0) allorders (orders, numbers, j);
    }
    
}
void allorders(vector <string> orders,vector<double> numbers, int j)
{
    // vector <string> orders; 
    // vector<double> numbers;
    system("cls");
    int n;
    cout << "\x1b[33m* Customer *\x1b[0m\n\n";
    cout << "Please select the option you want:\n\n";
    cout << "1. New Orders\n" << "2. Orders List\n" << "0. Back\n";
    cin >> n;
    if ( n == 1) foodmenu(orders, numbers, j);
    else if ( n == 2) orderslist(j,"no");
    else Select(j);

}
void byebye()
{
    system("cls");
    cout << "Thanks for choosing us and hope you enjoy your food.";
    return;
}
void firstpage(vector <string> orders, vector<double> numbers, int j)
{
    mainmenu(orders, numbers, j);
    // system("cls");
    // int n;
    // cout << "Yo, Wassup man? welcome to our restaurant and thanks for choosing us.\n\n" << "Please select the option you want:\n\n";
    // cout << "1. Main menu\n" << "0. Back\n";
    // cin >> n;
    // if ( n == 1) mainmenu(orders, numbers, j);
    // else welcome(j);
}
void mainmenu(vector <string> orders, vector<double> numbers, int j)
{
    allorders(orders,numbers, j);
    // system("cls");
    // int n;
    // cout << "* Main Menu *\n\n";
    // cout << "Please select the option you want:\n\n";
    // cout << "1. Getting Fat Menu\n" << "0. Back\n";
    // cin >> n;
    // if ( n == 1) allorders(orders,numbers, j);
    // else welcome(j);

}
void managementmenu(int j)
{
    system("cls");
    int pass = 1234, n;
    string anyth;
    do
    {
        cout << "Please Enter The Password: (0 to go back)\n\n";
        cin >> n;
        if(n == 0) Select(j);
        system("cls");
        cout << "\x1b[31mWrong Password!\x1b[0m\n\n";
    }
    while ( n != pass);
    vector<string> ids;
    vector<string> readys;
    vector<string> pays;
    string id,ready,pay;
    ifstream iall("all.txt");
    while(iall >> id >> ready)
    {
        ifstream Receipt(id.c_str());
        Receipt >> pay;
        Receipt.close();
        ids.push_back(id);
        readys.push_back(ready);
        pays.push_back(pay);
    }
    system("cls");
    if(id.size()==0)
    {
        cout << "\x1b[31mNo Orders Availabe!\x1b[0m\nType Anything To Go Back.\n";
        cin >> anyth;
        Select(j);
    }
    int inp;
    do
    {
        cout << "\x1b[33mYo Bro, Welcome Back.\x1b[0m\n\nReceipt Number ---------- Is Ready ---------- Payed\n\n";
        for (int i = 0; i < ids.size(); i++)
        {
            cout <<"     \x1b[36m " << ids[i] << " \x1b[0m       .......... ";
            if(readys[i]=="1") cout << "   \x1b[32mYES \x1b[0m  ";
            else cout << "   \x1b[31mNO \x1b[0m   ";
            cout << ".......... ";
            if(pays[i]=="1") cout << " \x1b[32mYES\x1b[0m \n";
            else cout << " \x1b[31mNO\x1b[0m  \n";
        } 
        cout << "\nWhich One is Ready? (0 to Go Back)\n";
        cin >> inp;
        if(inp <= ids.size() && inp > 0)
        {
            readys[inp-1] = "1";
            system("cls");
            cout << "\x1b[32mOrder Number \x1b[36m" << ids[inp-1] << "\x1b[32m is Ready!\x1b[0m\n";
        }
    } while (inp != 0);
    ofstream All ("all.txt");
    for (int i = 0; i < ids.size(); i++) All << ids[i] << " " << readys[i] << endl;
    Select(j);
}
void foodmenu(vector <string> orders, vector<double> numbers, int j)
{
    system("cls");
    int n;
    cout << "\x1b[33m* Food Menu *\x1b[0m\n\n";
    cout << "Please select the category you want:\n\n";
    cout << "1. \x1b[36mPizza\x1b[0m\n" << "2. \x1b[36mBurger\x1b[0m\n" << "3. \x1b[36mFried Chicken\x1b[0m\n" "4. \x1b[36mAppetizer\x1b[0m\n" << "5. \x1b[36mDrink\x1b[0m\n" << "0. Back\n";
    cin >> n;
    if ( n == 1) pizza(orders,numbers, j);
    else if ( n == 2) burger(orders, numbers, j);
    else if ( n == 3) fried(orders, numbers, j);
    else if ( n == 4) appetizer(orders, numbers, j);
    else if ( n == 5) drink(orders, numbers, j);
    else if ( n == 0) allorders(orders,numbers, j);
}
void pizza(vector <string> orders, vector<double> numbers, int j)
{
    system("cls");
    bool isnew = false;
    ifstream check (to_string(j).c_str());
    if(!check.is_open())
    {
        isnew = true;
        ofstream id ("ID.txt");
        id << j+1;
        id.close();
        ofstream addtoall ("all.txt",ios::app);
        addtoall << j << " " << 0 << endl;
        addtoall.close();
        check.close();
    }
    ofstream Receipt (to_string(j).c_str(),ios::app);
    if(isnew) Receipt << "0\n";
    int n, ordernumber;
    double number;
    cout << "\x1b[33m* Pizza Menu *\x1b[0m\n\n";
    cout << "Please select the kind of Pizza you want:\n\n";
    cout << "1. Neapolitan Pizza\n" << "Ingredients:\n" << "a basic dough, raw tomatoes, fresh mozzarella cheese, fresh basil, and olive oil\n" << "Price: $31.99\n" << "Preparing Time: 20 min\n\n";
    cout << "2. Veggie Pizza\n" << "Ingredients:\n" << "roasted red peppers, baby spinach, onions, mushrooms, tomatoes, and black olives\n" << "Price: $29.99\n" << "Preparing Time: 20 min\n\n";
    cout << "3. Pepperoni Pizza\n" << "Ingredients:\n" << "a meat mixture of beef and pork that has been cured and seasoned with paprika and chili powder\n" << "Price: $27.99\n" << "Preparing Time: 20 min\n\n";
    cout << "4. Meat Pizza\n" << "Ingredients:\n" << "cooked and crumbled Italian sausage or ground beef, bacon, pepperoni, and sometimes sliced ham\n" << "Price: $25.99\n" << "Preparing Time: 20 min\n\n";
    cout << "5. Margherita Pizza\n" << "Ingredients:\n" << "a bubbly crust, crushed San Marzano tomato sauce, fresh mozzarella and basil, a drizzle of olive oil, and a sprinkle of salt\n" << "Price: $23.99\n" << "Preparing Time: 20 min\n\n";
    cout << "6. Greek Pizza\n" << "Ingredients:\n" << "Dough, sauce (tomato sauce), cheese\n" << "Price: $21.99\n" << "Preparing Time: 20 min\n\n";
    cout << "0. Back\n\n";
    cin >> n;
    if ( n == 1)
    {
        orders.push_back( "Neapolitan Pizza");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*31.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering pizza\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) pizza(orders,numbers, j);
        else if ( ordernumber == 2) foodmenu(orders,numbers, j);
    }
    else if ( n == 2)
    {
        orders.push_back( "Veggie Pizza");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*29.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering pizza\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) pizza(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 3)
    {
        orders.push_back( "Pepperoni Pizza");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*27.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering pizza\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) pizza(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 4)
    {
        orders.push_back( "Meat Pizza");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*25.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering pizza\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) pizza(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 5)
    {
        orders.push_back( "Margherita Pizza");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*23.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering pizza\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) pizza(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 6)
    {
        orders.push_back( "Greek Pizza");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*21.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering pizza\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) pizza(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 0) foodmenu(orders, numbers, j);
}
void burger(vector <string> orders, vector<double> numbers, int j)
{
    system("cls");
    int n, ordernumber;
    double number;
    bool isnew = false;
    ifstream check (to_string(j).c_str());
    if(!check.is_open())
    {
        isnew = true;
        ofstream addtoall ("all.txt",ios::app);
        addtoall << j << " " << 0 << endl;
        addtoall.close();
        ofstream id ("ID.txt");
        id << j+1;
        id.close();
        check.close();
    }
    ofstream Receipt (to_string(j).c_str(),ios::app);
    if(isnew) Receipt << "0\n";
    cout << "\x1b[33m* Burger Menu *\x1b[0m\n\n";
    cout << "Please select the kind of Burger you want:\n\n";
    cout << "1. Cheeseburger\n" << "Ingredients:\n" << "Bacon, Chilies, Avocado, Lettuce, Chili, Eggs, Tomatoes, Mushrooms\n" << "Price: $19.99\n" << "Preparing Time: 18 min\n\n";
    cout << "2. Hamburger\n" << "Ingredients:\n" << "tomato, romaine lettuces, onions, cheese, pickle, ketchup, mayonnaise\n" << "Price: $18.99\n" << "Preparing Time: 18 min\n\n";
    cout << "3. Beef Burger\n" << "Ingredients:\n" << "Egg, Bacon, Onions, Bread Crumbs, Worcestershire sauce, Garlic, shredded cheese, Barbecue sauce.\n" << "Price: $17.99\n" << "Preparing Time: 18 min\n\n";
    cout << "4. Elk Burger\n" << "Ingredients:\n" << "just elk, fat (pork or beef) and salt\n" << "Price: $16.99\n" << "Preparing Time: 18 min\n\n";
    cout << "5. Veggie Burger\n" << "Ingredients:\n" << "Cucumber, Avocado, Lettuce, Tomato.Pickles, Shredded cabbage, Arugula, Raw onion.\n" << "Price: $15.99\n" << "Preparing Time: 18 min\n\n";
    cout << "6. Bison Burger\n" << "Ingredients:\n" << "garlic, salt, pepper, rosemary, smoked paprika, tomato paste, and fennel seeds\n" << "Price: $14.99\n" << "Preparing Time: 18 min\n\n";
    cout << "0. Back\n";
    cin >> n;
    if ( n == 1)
    {
        orders.push_back( "Cheeseburger");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*19.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering burger\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) burger(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 2)
    {
        orders.push_back( "Hamburger");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*18.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering burger\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) burger(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 3)
    {
        orders.push_back( "Beef Burger");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*17.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering burger\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) burger(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 4)
    {
        orders.push_back( "Elk Burger");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*16.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering burger\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) burger(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 5)
    {
        orders.push_back( "Veggie Burger");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*15.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering burger\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) burger(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 6)
    {
        orders.push_back( "Bison Burger");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*14.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering burger\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) burger(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 0) foodmenu(orders, numbers, j);
}
void fried(vector <string> orders, vector<double> numbers, int j)
{
    system("cls");
    int n, ordernumber;
    double number;
    bool isnew = false;
    ifstream check (to_string(j).c_str());
    if(!check.is_open())
    {
        isnew = true;
        ofstream addtoall ("all.txt",ios::app);
        addtoall << j << " " << 0 << endl;
        addtoall.close();
        ofstream id ("ID.txt");
        id << j+1;
        id.close();
        check.close();
    }
    ofstream Receipt (to_string(j).c_str(),ios::app);
    if(isnew) Receipt << "0\n";
    cout << "\x1b[33m* Fried Chicken Menu *\x1b[0m\n\n";
    cout << "Please select the kind of Fried Chicken you want:\n\n";
    cout << "1. 2 pieces\n" << "Ingredients:\n" << "Chicken, seasoned flour\n" << "Price: $9.99\n" << "Preparing Time: 15 min\n\n";
    cout << "2. 3 pieces\n" << "Ingredients:\n" << "Chicken, seasoned flour\n" << "Price: $10.99\n" << "Preparing Time: 15 min\n\n";
    cout << "3. 5 pieces\n" << "Ingredients:\n" << "Chicken, seasoned flour\n" << "Price: $11.99\n" << "Preparing Time: 15 min\n\n";
    cout << "4. Chicken Strip\n" << "Ingredients:\n" << "Chicken tenderloins, chicken broth powder, carrot, onion, celery, garlic powder, vinegar\n" << "Price: $12.99\n" << "Preparing Time: 15 min\n\n";
    cout << "5. Fillet Strip\n" << "Ingredients:\n" << "Basa, Batter, Maize Flour, Garlic Powder, Onion\n" << "Price: $13.99\n" << "Preparing Time: 15 min\n\n";
    cout << "0. Back\n";
    cin >> n;
    if ( n == 1)
    {
        orders.push_back("2 pieces");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*9.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering fried chicken\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) fried(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 2)
    {
        orders.push_back("3 pieces");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*10.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering fried chicken\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) fried(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 3)
    {
        orders.push_back("5 pieces");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*11.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering fried chicken\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) fried(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 4)
    {
        orders.push_back("Chicken Strip");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*12.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering fried chicken\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) fried(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 5)
    {
        orders.push_back("Fillet Strip");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*13.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering fried chicken\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) fried(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 0) foodmenu(orders, numbers, j);
}
void appetizer(vector <string> orders, vector<double> numbers, int j)
{
    system("cls");
    int n, ordernumber;
    double number;
    bool isnew = false;
    ifstream check (to_string(j).c_str());
    if(!check.is_open())
    {
        isnew = true;
        ofstream addtoall ("all.txt",ios::app);
        addtoall << j << " " << 0 << endl;
        addtoall.close();
        ofstream id ("ID.txt");
        id << j+1;
        id.close();
        check.close();
    }
    ofstream Receipt (to_string(j).c_str(),ios::app);
    if(isnew) Receipt << "0\n";
    cout << "\x1b[33m* Appetizer Menu *\x1b[0m\n\n";
    cout << "Please select the kind of Appetizer you want:\n\n";
    cout << "1. French Fries\n" << "Price: $7.99\n" << "Preparing Time: 10 min\n\n"; 
    cout << "2. Salad\n" << "Price: $6.99\n" << "Preparing Time: 10 min\n\n";
    cout << "3. Garlic Bread\n" << "Price: $5.99\n" << "Preparing Time: 10 min\n\n";
    cout << "0. Back\n";
    cin >> n;
    if ( n == 1)
    {
        orders.push_back("French Fries");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*7.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering appetizer\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) appetizer(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 2)
    {
        orders.push_back("Salad");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*6.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering appetizer\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) appetizer(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 3)
    {
        orders.push_back("Garlic Bread");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*5.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering appetizer\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) appetizer(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 0) foodmenu(orders, numbers, j);
}
void drink(vector <string> orders, vector<double> numbers, int j)
{
    system("cls");
    int n, ordernumber;
    double number;
    ifstream check (to_string(j).c_str());
    bool isnew = false;
    if(!check.is_open())
    {
        isnew = true;
        ofstream addtoall ("all.txt",ios::app);
        addtoall << j << " " << 0 << endl;
        addtoall.close();
        ofstream id ("ID.txt");
        id << j+1;
        id.close();
        check.close();
    }
    ofstream Receipt (to_string(j).c_str(),ios::app);
    if(isnew) Receipt << "0\n";
    cout << "\x1b[33m* Drink Menu *\x1b[0m\n\n";
    cout << "Please select the kind of Drink you want:\n\n";
    cout << "1. Coca-Cola\n" << "Price: $1.99\n\n";
    cout << "2. Pepsi\n" << "Price: $1.99\n\n";
    cout << "3. Fanta\n" << "Price: $1.99\n\n";
    cout << "4. Dough\n" << "Price: $1.99\n\n";
    cout << "5. Water\n" << "Price: $1.99\n\n";
    cout << "0. Back\n\n";
    cin >> n;
    if ( n == 1)
    {
        orders.push_back("Coca-Cola");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*1.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering drink\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) drink(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 2)
    {
        orders.push_back("Pepsi");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*1.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering drink\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) drink(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 3)
    {
        orders.push_back("Fanta");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*1.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering drink\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) drink(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 4)
    {
        orders.push_back("Dough");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*1.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering drink\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) drink(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 5)
    {
        orders.push_back("Water");
        cout << "\nPlease enter how many numbers you want:\n\n";
        cin >> number;
        numbers.push_back(number*1.99);
        Receipt << orders[orders.size()-1] << "#" << numbers[numbers.size()-1] << endl;
        Receipt.close();
        cout << "\n\nPlease select the option you want:\n\n" << "1. Continue ordering drink\n" << "2. Food Menu\n\n";
        cin >> ordernumber;
        if ( ordernumber == 1) drink(orders, numbers, j);
        else if ( ordernumber == 2) foodmenu(orders, numbers, j);
    }
    else if ( n == 0) foodmenu(orders, numbers, j);
}

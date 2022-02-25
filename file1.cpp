#include<iostream>
#include<fstream>

using namespace std;


class shopping{
    private:
        int pcode;
        float price;
        float discount;
        string pname;

    public:
        void menu();
        void admin();
        void buyer();
        void add();
        void edit();
        void deleteproduct();
        void list();
        void receipt();

};

void shopping :: menu()
{
    m:
    int choice;
    string email;
    string password;

    cout<<"********SuperMarket Main Menu********\n";
    cout<<"        1) Admin                     \n";
    cout<<"        2) Buyer                     \n";
    cout<<"        3) Exit                      \n";

    cout<<"        Please select:               \n";
    cin>>choice;

    switch(choice)
    {
        case 1:
            cout<<"  Please login\n";
            cout<<"  Enter email\n";
            cin>>email;
            cout<<"  Enter password\n";
            cin>>password;

            if(email == "admin@gmail.com" && password == "admin@20")
            {
                admin();
            }
            else
            {
                cout<<"  Invalid email or password\n";
            }
            break;
        
        case 2:
            buyer();
            break;
        
        case 3:
            exit(0);
            break;
        
        default:
            cout <<"  Please select from the given options\n";

    }

    goto m;

}

void shopping ::admin()
{
    m:
    int choice;
    cout<<"********Admin Menu********   \n";
    cout<<"        1) Add the product   \n";
    cout<<"        2) Modify the product\n";
    cout<<"        3) Delete the product\n";
    cout<<"        4) back to main menu \n";

    cout<<"        Please select:       \n";
    cin>>choice;

     switch(choice)
    {
        case 1:
            add();
            break;
        
        case 2:
            edit();
            break;
        
        case 3:
            deleteproduct();
            break;
        
        case 4:
            menu();
            break;
        
        default:
            cout <<"  Please select from the given options\n";

    }

    goto m;

}

void shopping :: buyer()
{
    m:
    int choice;
    cout<<"********Buyer Menu********   \n";
    cout<<"        1) Buy the product   \n";
    cout<<"        2) back to main menu \n";

    cout<<"        Please select:       \n";
    cin>>choice;

     switch(choice)
    {
        case 1:
            receipt();
            break;
        
        case 2:
            menu();
            break;
        
        default:
            cout <<"  Please select from the given options\n";

    }

    goto m;
}

void shopping :: add()
{
    m:
    fstream data;  //object of fstream class
    int c;//code
    int token =0;
    float p; //price
    float d; //discount
    string n; //name

    cout <<"  Add new product\n";
    cout <<"  Product code of the product\n";
    cin>>pcode;
    cout<<"  Name of the product\n";
    cin>>pname;
    cout<<"  Price of the product\n";
    cin>>price;
    cout<<"  Discount on the product\n";
    cin>>discount;

    data.open("database.txt",ios::in);//open file in reading mode

    if(!data) //if this file doesn't exist
    {
        data.open("database.txt",ios::app|ios::out);
        //app for append mode
        //out for write mode
        data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<discount<<"\n";
        data.close();
    }
    else
    {
        data>>c>>n>>p>>d;//initializing the index of file

        while(!data.eof())
        {
            if(c == pcode)
            {
                token++;
            }
            data>>c>>n>>p>>d; //for iteration purpose reading from file
        }

        data.close();

        if(token == 1)
        {
            cout<<"  record already exist with that product code.\n";
            cout<<"  Please enter different product code.\n";
            goto m;
        } //if product already existed then got back to menu
         //else write data to file
        else{
         data.open("database.txt",ios::app|ios::out);
         data<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<discount<<"\n";
         data.close();
         }
    }

    

    cout<<"Record inserted\n";
}


void shopping :: edit()
{
    fstream data,data1;  //object of fstream class
    int c;//code
    int pkey;
    int token =0;
    float p; //price
    float d; //discount
    string n; //name

    cout <<"  Modify the record of product\n";
    cout <<"  Product code of the product\n";
    cin>>pkey;
    

    data.open("database.txt",ios::in);//open file in reading mode

    if(!data) //if this file doesn't exist
    {
        cout << "  File doesn't exist\n";
    }
    else
    {
        data1.open("database1.txt",ios::app|ios::out);
        
        data>>pcode>>pname>>price>>discount;

        while(!data.eof())
        {
            if(pkey == pcode)
            {
                cout << "  New code of product\n";
                cin>>c;
                cout << "  Name of product\n";
                cin>>n;
                cout << "  Price of product\n";
                cin>>p;
                cout << "  discount of product\n";
                cin>>d;

                data1<<" "<<c<<" "<<n<<" "<<p<<" "<<d<<"\n";
                cout<<"  Record edited\n";
                token++;
            }
            else
            {
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<discount<<"\n";
            }

            data>>pcode>>pname>>price>>discount;
            
        }

        data.close();
        data1.close();

        //rename data1 as data
        remove("database.txt");
        rename("database1.txt","database.txt");

            if(token == 0)
          {
             cout<<"  Record not found\n";
          }

    }

   
    
}


void shopping::deleteproduct()
{
    fstream data,data1;  //object of fstream class
    int pkey;
    int token =0;
    
    cout <<"  Delete the record of product\n";
    cout <<"  Product code of the product\n";
    cin>>pkey;
    

    data.open("database.txt",ios::in);//open file in reading mode

    if(!data) //if this file doesn't exist
    {
        cout << "  File doesn't exist\n";
    }
    else
    {
        data1.open("database1.txt",ios::app|ios::out);
        
        data>>pcode>>pname>>price>>discount;

        while(!data.eof())
        {
            if(pkey == pcode)
            {
                cout << "  product deleted succesfully\n";
                token++;
            }
            else //except that others will be copied in database1
            {
                data1<<" "<<pcode<<" "<<pname<<" "<<price<<" "<<discount<<"\n";
            }

            data>>pcode>>pname>>price>>discount;
            
        }

        data.close();
        data1.close();

        //rename data1 as data
        remove("database.txt");
        rename("database1.txt","database.txt");

    }

    if(token == 0)
    {
        cout<<"  Record not found\n";
    }
}



void shopping::list()
{
    fstream data;  //object of fstream class
    
    data.open("database.txt",ios::in);//open file in reading mode

    cout<<"\t\t"<<"ProNo\t\tName\t\tPrice\n";
    data>>pcode>>pname>>price>>discount;
   
   while (!data.eof())
   {
      cout<<"\t\t"<<pcode<<"\t\t"<<pname<<"\t\t"<<price<<"\n";

      data>>pcode>>pname>>price>>discount;
   }
   
   
    data.close();
       
}

void shopping :: receipt()
{
    m:
    fstream data;
    int arrayc[100]; //array of codes
    int arrayq[100]; //array of quatity

    char choice;
    int c=0;
    float amount =0;
    float dis=0;
    float total;

    cout<<"_______________Menu_______________\n";

    data.open("database.txt",ios::in);

    if(!data)
    {
        cout<<"Empty Database\n";
    }
    else
    {
        data.close();

        list();
        cout<<"________________________\n";
        cout<<"                        \n";
        cout<<"   Please place order   \n";
        cout<<"                        \n";
        cout<<"________________________\n";
       

        do
        {
            cout<<"\n  Enter Product code\n";
            cin>>arrayc[c];
            cout<<"\n  Enter the product quantity\n";
            cin>>arrayq[c];

            for (int i = 0; i < c; i++)
            {
                if(arrayc[c]==arrayc[i])
                {
                    cout<<"\n  Duplicate product code. Please try again\n";
                    goto m;
                }
            }
            c=c+1;
            cout<<"\nDo you want to buy another product? if yes then press y else n\n";
            cin>>choice;

        } while (choice =='y');
        

        cout<<"________________________RECEIPT_______________________\n";
        cout<<"                                                      \n";
        cout<<"\t\t"<<"Product No\tProduct Name\tProduct Quantity\tPrice\tAmount\tAmount with discount  \n";
        
        for (int i = 0; i < c; i++)
        {
            data.open("database.txt",ios::in);
            data>>pcode>>pname>>price>>discount;

            while (!data.eof())
            {
                if(arrayc[i]==pcode)
                {
                    amount=price*arrayq[i];
                    dis=amount -(amount*discount/100);
                    total = total+dis;

                    cout<<"\t\t"<<pcode<<"\t\t"<<pname<<"\t\t"<<arrayq[i]<<"\t\t\t"<<price<<"\t\t"<<amount<<"\t\t"<<dis<<"\n";
                }

                data>>pcode>>pname>>price>>discount;
            }
            data.close();
        }
       
        cout<<"                                                      \n";
        cout<<"______________________________________________________\n";
        
        cout<<"  Total Amount : "<<total<<"\n";
        
    }
}

int main(){
    shopping s;
    s.menu();
}

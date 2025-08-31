/*
Student Names: Gruner, Sabrina (W1759808) Moore, Dominique (W1032697) Nguyen, Sophia (W1743568) Saludo, Kaylyn (W1721175) Sigheti, Anthony (W1499492) Wei, Heather (W1892097) 

CISP 360 - Course # 17062 - Group 1

Project File Name: Group1_Final_FruitStand
Project Description: This program allows the user to view a menu of fruits and prices. The user can edit and add items to their list and get their total.
*/
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <iomanip>
#include <stdlib.h>

using namespace std;
void gettingArrays(string fruit[], double price[], int n);
void displayMenu(string *fruit, double *price, 
vector<string>& userList, vector<int>& numOfEachFruit, 
int& loop, vector<double>& costOfEachUserItem, int &i);
void createList(string *fruit, double *price, 
vector<string>& userList, vector<int>& numOfEachFruit, 
int& loop, vector<double>& costOfEachUserItem, int &i);
bool check(string userInput, int amount, vector<string> userList, vector<int>& numOfEachFruit);
void editList(string fruit[], double price[], int n,vector<string>& userList, vector<int>& numOfEachFruit, vector<double>& costOfEachUserItem, int a);
double calculateTotal(string fruit[], double price[], int n, vector<string>& userList, vector<int>& numOfEachFruit, 
vector<double>& costOfEachUserItem);
void viewList(string fruit[], double price[], int n,vector<string>& userList, vector<int>& numOfEachFruit, vector<double>& costOfEachUserItem, int a);
void center(string text);

int main()
{   
    int input = 0;  //user decide what to do 
    int n = 19;     //size of the array and how many type of                    fruits we sell and number of price
    string fruit[n];  //Will hold list of fruit we sell
    double price[n];  //Will hold the price of each fruit
    int loop = 0;   /*How many time a user go into 
                      createList()*/
    vector<string> userList;  //Userinput of fruits
    
    /*User input of number of each fruits they want*/
    vector<int> numOfEachFruit;

    /* Ex: Each Fig cost $5 and if user buy 2 Then 10 will be store into this vector.*/
    vector<double> costOfEachUserItem;  
    
    gettingArrays(fruit, price, n); //Open file to fill arrays

    int i=0;  //to see if user viewmenu from CreateList 
    int a=0; //to see if user view list from viewList or editList
    string *fruitPointer = fruit;
    double *pricePointer = price;

  //Coding block for the ASCII Word Art
   center(" _____          _ _     _____ _                   _ ");
   center("|  ___|        (_) |   /  ___| |                 | |");
   center("| |_ _ __ _   _ _| |_  | `--.| |_ __ _ _ ___   __| |");
   center("|  _| '__| | | | | __|  `--. | __/ _` | '_  | / _` |");
   center("| | | |  | |_| | | |_  /|__/ / || (_| | | | |( |_| |");
   center("|_| |_|  |___,_|_||__| |____/ |__|__,_|_| |_| |_,_ |");
   center("by");
   center("Sabrina G, Dominique M, Sophia N,");
   center("Kaylyn S, Anthony S, & Heather W.");
   cout << endl << endl;

    cout << "Let's make your grocery list!\n";
    do
    {   
    cout <<"Choose from the following to continue: \n";
    cout << "1 - View our list of fruits!\n";
    cout << "2 - Create a list\n";
    cout << "3 - Edit existing list\n"; 
    cout << "4 - View an existing list\n";
    cout << "5 - Exit\n";
    
    cin>>input;
    system("clear");
    
    switch (input)
    {
           case 1:
                displayMenu(fruitPointer, pricePointer, userList, numOfEachFruit, loop, costOfEachUserItem, i);
                break;
           case 2:
                createList(fruit, price, userList, numOfEachFruit, loop, costOfEachUserItem, i);
                break;
           case 3:
                editList(fruit, price, n, userList, numOfEachFruit, costOfEachUserItem, a);
                break;
           case 4:
                viewList(fruit, price, n,userList, numOfEachFruit, costOfEachUserItem, a);
                break;
           case 5:
                cout << "Thank you for using our program! Good bye! :)\n";
                cout << endl << endl;
                center(" ______ __   __ ______ __   _  __   _   _   _  _____  _   _          .:'");
                center("|      || | | ||  _  || |  | ||  | | | | | | ||     || | | |     __ :'__");
                center("   |_    _|| | | || | | ||  | | ||  |_| | | | | ||  _  || | | |  .'`  `-' .``.");
                center("       |  |  | |_| || |_| ||  |_| ||     _| | |_| || | | || |_| | :          :  :");
                center("      |  |  |     ||     ||  _   ||    |_  |_   _|| |_| ||     | :             :");
                center("     |  |  |  _  ||   _ || | |  ||   _  |   | |  |     ||     |  :           :");
                center("    |__|  |_| |_||_| |_||_|  |_||__| |_|   |_|  |_____||_____|   `.__.-.__.'");   
                exit(0);
                return 0;
           default:
                   cout<<"ERROR! Enter a number 1-5...\n";
                   break;
    }
    }
    while (input != 5);
    return 0;
}

//Centers the text inside the parameters when you call center("example")
void center(string text)
{
  //padding variable
  const int padding = (90-text.length())/2;
  
  //for loop that creates blank spaces.
  for (int i = 0; i < padding; i++)
  {
    cout << " ";
  }
  cout << text << endl;
}

/* Gets the list of fruits our stand sells and the price of each fruits. Then put each in their own 1D array */
void gettingArrays(string fruit[], double price[], int n)
{
     ifstream inFile;
    inFile.open("fruitList.txt");
    int index = 0;   //index of the array

    if(inFile.fail())   //to test if the file open
    {
      cerr << "Error opening the file" << endl;
      exit(1);
    }

    while(!inFile.eof())  //input from file to array
    {
         inFile >> fruit[index]; 
         index++;
    }

    inFile.close();
    inFile.open("fruitPrice.txt");
    index = 0;

    while(!inFile.eof())
    {
         inFile >> price[index];
         index++;
    }
}

/*  Displays the menu of the fruit we sell + the price of each fruit*/
void displayMenu(string *fruit, double *price, 
vector<string>& userList, vector<int>& numOfEachFruit, 
int& loop, vector<double>& costOfEachUserItem, int &i)
{
    int input;
        cout << "Here is our list of fruits with their prices!:\n";
        for (int i = 0; i < 19; i++)
        {
            cout << setprecision(2) << fixed; 
            cout << left << setw (15) <<*(fruit + i) << "\t" << "$" << *(price + i) << "\n";
        }

        if(i == 0)
        {
            cout << "Would you like to make your list now?\n";
            cout << "1. To Create List\n";
            cout << "2. Exit\n";
            cin >> input;
            system("clear");
            if (input < 2)
            {
                createList(fruit, price, userList, numOfEachFruit, loop, costOfEachUserItem, i);
            }
            else
            {
                cout << "Thank you for using our program! Good bye! :)\n";
                cout << endl << endl;
                center(" ______ __   __ ______ __   _  __   _   _   _  _____  _   _          .:'");
                center("|      || | | ||  _  || |  | ||  | | | | | | ||     || | | |     __ :'__");
                center("   |_    _|| | | || | | ||  | | ||  |_| | | | | ||  _  || | | |  .'`  `-' .``.");
                center("       |  |  | |_| || |_| ||  |_| ||     _| | |_| || | | || |_| | :          :  :");
                center("      |  |  |     ||     ||  _   ||    |_  |_   _|| |_| ||     | :             :");
                center("     |  |  |  _  ||   _ || | |  ||   _  |   | |  |     ||     |  :           :");
                center("    |__|  |_| |_||_| |_||_|  |_||__| |_|   |_|  |_____||_____|   `.__.-.__.'");   
                exit(1);
            }
        }
        i = 0;
        
}


/* User create their list*/
void createList(string *fruit, double *price, 
vector<string>& userList, vector<int>& numOfEachFruit, 
int& loop, vector<double>& costOfEachUserItem, int &i)
{
     string fruitInput;  //User input of each fruit

    //For the user to decide to clearlist or go back to menu
     int decision = 0;  

    //User input for amount of a each type of fruit they want
     int amount;

    //To check if user input the same fruit twice
     bool flag = false; 

     if(loop > 0) //If user open createList more than once
     {    
          while(decision < 1 || decision > 2)
          {
               cout << "WARNING: This is about to clear your entire list \n";
               cout << "1. Clear entire list \n";
               cout << "2. Exit to main menu \n";
               cin >> decision;

               if(decision < 1 || decision > 2)
               {
                 cout << "ERROR! Enter a number 1-2...\n";
               }
          }
          system("clear");  //clear the screen
     }

    
    //Lets user start creating their list
     if(loop == 0 || decision == 1)
     {
          /*To make sure "do u want to create list" doesn't display in DisplayMenu*/
          i = 1;  
          displayMenu(fruit, price, userList, numOfEachFruit, loop, costOfEachUserItem, i);

          userList.clear(); //Clear the entire list
          numOfEachFruit.clear();
          costOfEachUserItem.clear();
          cout << "Please enter the word as shown in the menu\n"; 
          cout << "and put how many of that fruit you want: \n";
          cout << "(Example: Apple 5)\n";
          cout << "Put End to stop \n";

          while(fruitInput != "End")
          {
               cin >> fruitInput;
               if(fruitInput != "End") 
               {
                    cin >> amount;
                    flag = check(fruitInput, amount, userList, numOfEachFruit);
                    if(flag != true)
                    {
                    userList.push_back(fruitInput);
                    numOfEachFruit.push_back(amount);
                    }
               }
          }
          system("clear");
     }
    /*Add 1 each time user enter CreateList to give them an option to clear the list when they enter CreateList for more than 1 time*/
     loop++; 
}


/*Check to see if user input 2 of the same fruit. If so, correct the list.
EX: if User input: Apple 2 Mango 2 Apple 1
This will correct the vector numOfEachFruit to 3 (apples) */
bool check(string fruitInput, int amount, vector<string> userList, vector<int>& numOfEachFruit)
{
  bool flag = false;

  for(int i = 0; i < numOfEachFruit.size(); i++)
  {
    if(fruitInput == userList[i])
    {
      numOfEachFruit[i] = (numOfEachFruit[i] + amount);
      flag = true;
    }
  }

  return flag;
}

// Lets the user add or subtract fruits from list (vector)
void editList(string fruit[], double price[], int n,vector<string>& userList, vector<int>& numOfEachFruit, vector<double>& costOfEachUserItem, int a)
{
    string fruitInput;  //User input of each fruit

    //For the user to decide to add or subtract from list
    int decision = 0;  

    //User input for amount of a each type of fruit they want
    int amount;

    //To check if user input the same fruit twice
    bool flag = false; 


    while(decision != 3)
    {
          //to let user view list without exit menu popping up in editList
          a = 1; 

          cout << "How would you like to edit your list: \n";
          cout << "1. Add to your list\n";
          cout << "2. Subtract from your list\n";
          cout << "3. Go back to main menu\n";
          cin >> decision;
          system("clear");

          /* Need this to get costOfEachItem vector*/
          double total = calculateTotal(fruit, price,  n, userList, numOfEachFruit,costOfEachUserItem); 

          if(decision == 1)
          {
            viewList(fruit, price, n,userList, numOfEachFruit, costOfEachUserItem, a);
            cout << endl;
            
            cout << "What Would you like to ADD to your list: \n";
               cout << "(Ex: Apple 3)\n";
               cout << "Put End to stop \n";

               while(fruitInput != "End")
               {
                    cin >> fruitInput;
                    if(fruitInput != "End")
                    {
                         cin >> amount;
                         flag = check(fruitInput, amount, userList, numOfEachFruit);
                         if(flag != true)
                         {
                         userList.push_back(fruitInput);
                         numOfEachFruit.push_back(amount);
                         }
                    }
               }
              system("clear");
               fruitInput = "nothing";  //reset fruitInput
          }
          else if(decision == 2)
          {
            viewList(fruit, price, n,userList, numOfEachFruit, costOfEachUserItem, a);
            cout << endl;
            cout << "What would you like to DELETE from your list:\n ";
            cout << "Note: This delete the whole item\n";
            cout << "Put End to stop\n";

            while(fruitInput != "End")
            {
             cin >> fruitInput;
             if(fruitInput != "End")
             {
              for(int i = 0; i < userList.size(); i++)
               {
                if(fruitInput == userList[i])
                 {
                   userList.erase(userList.begin()+i);
                   numOfEachFruit.erase(numOfEachFruit.begin()+i);
                   costOfEachUserItem.erase(costOfEachUserItem.begin() + i );
                    i = userList.size();
                  }
                }
             }
          }
            system("clear");
            fruitInput = "nothing"; //reset fruitInput
          }
          else if(decision < 1 || decision > 3)
          {
               cout << "ERROR!...Enter a number 1-3\n";
          }     
     }
}


/* Calculate the total*/
double calculateTotal(string fruit[], double price[], int n, vector<string>& userList, vector<int>& numOfEachFruit, 
vector<double>& costOfEachUserItem)
{
     double total = 0;      //total
     double cost;       //cost of each user item
     for(int i =0; i < userList.size(); i++)
     {
          for(int a = 0; a < n; a++)
          {
               if(userList[i] == fruit[a])
               {
                 cost = (numOfEachFruit[i] * price[a]);   
                 costOfEachUserItem.insert(costOfEachUserItem.begin()+i, cost);
              
                    total += (numOfEachFruit[i] * price[a]);
               }
          }
     }

     return total;
}

/* Shows the user the "receipt" of the user list*/
void viewList(string fruit[], double price[], int n,vector<string>& userList, vector<int>& numOfEachFruit, vector<double>& costOfEachUserItem, int a)
{
  double count = 0;

  cout << setprecision(2) << fixed;
  double total = calculateTotal(fruit, price,  n, userList, numOfEachFruit,costOfEachUserItem);


  cout << left << setw(20) << "ITEM" << "QTY\t\t" << "TOTAL" << endl;   
  cout << "----------------------------------------\n";
  for(int i = 0; i < userList.size(); i++)
  {
    cout << left << setw(15);
    cout << userList[i] << "\t\t" <<  right << setw(3)<< numOfEachFruit[i] << "\t\t" << right << setw(6)<< costOfEachUserItem[i] << endl;
    count += costOfEachUserItem[i];
    
  }
  cout << "----------------------------------------\n";
  cout << right << setw(20) << "Total: " << count << endl;
  cout << "----------------------------------------\n";
  cout << endl << endl;

  //to see if the user is viewing the list from Edit or ViewList
  if(a == 0) 
  {
  int input; 
  cout << "To return to the main menu, enter 1." << endl;
  cout << "To quit the program, enter 2." << endl;
  cin >> input;

  
    if (input == 1) 
    {
    system("clear");
    }
    else if (input == 2)
    {
    system("clear");
    cout << "Thank you for using our program! Good bye! :)\n";
    cout << endl << endl;
    center(" ______ __   __ ______ __   _  __   _   _   _  _____  _   _          .:'");
    center("|      || | | ||  _  || |  | ||  | | | | | | ||     || | | |     __ :'__");
    center("   |_    _|| | | || | | ||  | | ||  |_| | | | | ||  _  || | | |  .'`  `-' .``.");
    center("       |  |  | |_| || |_| ||  |_| ||     _| | |_| || | | || |_| | :          :  :");
    center("      |  |  |     ||     ||  _   ||    |_  |_   _|| |_| ||     | :             :");
    center("     |  |  |  _  ||   _ || | |  ||   _  |   | |  |     ||     |  :           :");
    center("    |__|  |_| |_||_| |_||_|  |_||__| |_|   |_|  |_____||_____|   `.__.-.__.'");                            

    exit(0);
    }
  }
  a=0;
}




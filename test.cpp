#include <stdio.h>
#include <cstdlib>
#include <array>
#include <iostream>
#include <sstream>
#include <vector>
#include <random>
#include <unistd.h>
#include <memory>
#include <string>
#include <tuple>
using namespace std;

int cash = 200;
int debit = 200;
int price[5] = {10, 20, 17, 15, 25};
string fruits[5] = {"Apple", "Banana", "Orange", "Pear", "Watermelon"};
vector<tuple<string, int, int>> basket;
vector<int> total;
vector<string> fruit;
vector<int> amt;
vector<int> guessed;
vector<tuple<string, int>> fridge;
vector<string> aa;

const vector<string> item = {"Rectangle cake mold","Round cake mold", "Love cake mold", "White chocolate", "Dark chocolate", "Hazelnuts", "Almonds", "Peanuts", "Cashews", "Pistachios", "Chocolate sprinkles", "Rainbow sprinkles", "Granola", "Candy", "Nutella", "Dark chocolate", "Milk chocolate","Food coloring"};
const vector<int> item_p = {100, 100, 100, 50, 50, 50, 30, 45, 78, 38, 29, 79, 34, 12, 15, 31, 43, 8, 20};

vector<tuple<string, int>> bought;
vector<int> total_p;
vector<tuple<string, int>> shelves;


// Template for make_unique

template<typename T, typename... Args>
std::unique_ptr<T> make_unique(Args&&... args) {
    return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}
// Template for make_unique

class Cake{
protected:
string shape;
string color;
string topping;

public:

// addon
virtual ~Cake() = default;

Cake(string s, string c, string t) : shape(s), color(c), topping(t){}

virtual void cake_info(){
  cout << "Shape: " << shape << endl;
  cout << "Color: " << color << endl;
  cout << "Topping: " << topping << endl;
}

virtual void cake_result() = 0;

};

class ChocolateCake : public Cake{
private:
string chocolate_type;
public:
ChocolateCake(string s, string c, string t, string ct) : Cake(s, c, t), chocolate_type(ct){}
void cake_result() override {
  cout << "This is a chocolate cake\n";
}
void cake_info() override{
  Cake::cake_info();
  cout << "Chocolate type: " << chocolate_type << endl;
}
};

class StrawberryCake : public Cake{
private:
string frosting;
string fruits;
public:
StrawberryCake(string s, string c, string t, string f, string ff) : Cake(s, c, t), frosting(f), fruits(ff){}
void cake_result() override{
  cout << "This is a strawberry cake\n";
}
void cake_info() override{
  Cake::cake_info();
  cout << "Frosting: " << frosting << endl;
  cout << "Fruits: " << fruits << endl;
}
};


class VanillaCake : public Cake{
private:
string nuts;
public:
VanillaCake(string s, string c, string t, string n) : Cake(s, c, t), nuts(n){}
void cake_result() override{
  cout << "This is a vanilla cake" << endl;
}
void cake_info() override{
  Cake::cake_info();
  cout << "Nuts: " << nuts << endl;
}
};

string cap(string a){
  for(int i = 0; i < a.size();i++){
    if (i == 0){
      a[i] = toupper(a[i]);
    }
  }
  return a;
};









void market()
{
  cout << "Welcome to the market!" << endl;
  cout << "You have $" << cash << " in cash and $" << debit << " in debit." << endl;
  cout << "-----------------------------" << endl;
  for (int i = 0; i < item.size(); ++i)
  {
    cout << to_string(i + 1) + ". " + item[i] + " $" + to_string(item_p[i]) + "\n";
  }
  cout << "-----------------------------" << endl;
  cout << "Choice: " << endl;
  int choice;
  cin >> choice;
  if (choice > 0 && choice <= item.size())
  {
    cout << "How many " + item[choice - 1] + " would you like to buy? " << endl;
    int amount;
    int total_;
    cin >> amount;
    if (amount > 0)
    {
      total_ = item_p[choice - 1] * amount;
      bought.push_back(make_tuple(item[choice - 1], amount));
      total_p.push_back(total_);
      cout << "Would you like to buy anything else? (y/n)" << endl;
      string ans;
      cin >> ans;
      if (ans == "y")
      {
        cout << "\033[2J\033[1;1H";
        market();
      }
      else
      {
        cout << "\033[2J\033[1;1H";
        cout << "-----------------------------" << endl;
        for (int i = 0; i < bought.size(); i++)
        {
          cout << get<0>(bought[i]) << " " << get<1>(bought[i]) << "  $" << total_p[i] << endl;
        }
        cout << "-----------------------------" << endl;
        int final_ = 0;
        for (int i = 0; i < total_p.size(); i++)
        {
          final_ += total_p[i];
        }
        cout << "Total: $" << final_ << endl;
        cout << "Would you like to pay with cash or debit? (c/d)" << endl;
        string ans2;
        cin >> ans2;
        if (ans2 == "c")
        {
          if (final_ > cash)
          {
            cout << "You don't have enough cash!" << endl;
          }
          else
          {
            cash -= final_;
            for (const auto &item : bought)
            {
              bool flag = false;
              for (auto &shelf_item : shelves)
              {
                if (get<0>(item) == get<0>(shelf_item))
                {
                  get<1>(shelf_item) += get<1>(item);
                  flag = true;
                  break;
                }
              }
              if (!flag)
              {
                shelves.push_back(item);
              }
            }
            cout << "You have $" << cash << " left in cash." << endl;
            cout << "Press enter to continue" << endl;
            cin.ignore();
            cin.get();
          }
        }
        else
        {
          if (final_ > debit)
          {
            cout << "You don't have enough debit!" << endl;
          }
          else
          {
            debit -= final_;
            for (const auto &item : bought)
            {
              bool flag = false;
              for (auto &shelf_item : shelves)
              {
                if (get<0>(item) == get<0>(shelf_item))
                {
                  get<1>(shelf_item) += get<1>(item);
                  flag = true;
                  break;
                }
              }
              if (!flag)
              {
                shelves.push_back(item);
              }
            }

            cout << "You have $" << debit << " left." << endl;
            cout << "Press enter to continue" << endl;
            cin.ignore();
            cin.get();
          }
        }
      }
    }
    bought.clear();
    total_p.clear();
  }
};

void shop()
{
  cout << "Welcome to the shop! What would you like to buy?" << endl;
  cout << "You have $" << cash << " left." << endl;
  cout << "-----------------------------" << endl;
  for (int i = 0; i < 5; i++)
  {
    cout << i + 1 << '.' << " " << fruits[i] << " $" << price[i] << endl;
  }
  cout << "-----------------------------" << endl;
  cout << "Choice: " << endl;
  int choice;
  cin >> choice;
  cout << "Enter the quantity: " << endl;
  int quantity;
  cin >> quantity;
  bool found = false;
  for (int i = 0; i < basket.size(); i++)
  {
    if (get<0>(basket[i]) == fruits[choice - 1])
    {
      get<1>(basket[i]) += quantity;
      get<2>(basket[i]) += price[choice - 1] * quantity;
      found = true;
      break;
    }
  }
  if (!found)
  {
    basket.push_back(make_tuple(fruits[choice - 1], quantity, price[choice - 1] * quantity));
  }

  cout << "Would you like to buy anything else? (y/n)" << endl;
  char ans;
  cin >> ans;
  if (ans == 'y')
  {
    cout << "\033[2J\033[1;1H";
    shop();
  }
  else
  {
    cout << "\033[2J\033[1;1H";
    cout << "----------------------------" << endl;
    for (int i = 0; i < basket.size(); i++)
    {
      cout << get<0>(basket[i]) << " " << get<1>(basket[i]) << " $" << get<2>(basket[i]) << endl;
      cout << "-----------------------------" << endl;
    }
    int endprice = 0;
    for (int i = 0; i < basket.size(); i++)
    {
      endprice += get<2>(basket[i]);
    }
    if (endprice > cash)
    {
      cout << "You don't have enough money!" << endl;
    }
    else
    {
      cout << "Total: $" << endprice << endl;
      cash -= endprice;
      cout << "You have $" << cash << " remaining" << endl;
      cout << "Thank you for shopping!" << endl;
      for (const auto &item : basket)
      {
        bool found = false;
        for (auto &fridgeItem : fridge)
        {
          if (get<0>(item) == get<0>(fridgeItem))
          {
            get<1>(fridgeItem) += get<1>(item);
            found = true;
            break;
          }
        }
        if (!found)
        {
          fridge.push_back(make_tuple(get<0>(item), get<1>(item)));
        }
      }
    }
    total.clear();
    fruit.clear();
    amt.clear();
    basket.clear();
    cout << "Press enter to continue" << endl;
    cin.ignore();
    cin.get();
  }
}
void guessing_game()
{
  int chance = 3;
  int num = rand() % 50 + 1;
  while (true)
  {
    cout << "\033[2J\033[1;1H";
    cout << "Welcome to the guessing game!" << endl;
    cout << "Guess the number from 1-50" << endl;
    cout << "Guessed number: ";
    for (int i = 0; i < guessed.size(); i++)
    {
      cout << guessed[i] << " ";
    }
    cout << endl;
    cout << "Your guess: " << endl;
    int guess;
    cin >> guess;
    if (guess == num)
    {
      cout << "You guessed the correct number!" << endl;
      cout << "You received $150! " << endl;
      debit += 150;
      break;
    }
    else if (guess < num)
    {
      cout << "Your guess was too low!" << endl;
      guessed.push_back(guess);
      chance -= 1;
      if (chance == 0)
      {
        cout << "You lose!" << endl;
        cout << "The number was " << num << endl;
        break;
      }
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();
    }
    else
    {
      cout << "Your guess was too high!" << endl;
      guessed.push_back(guess);
      chance -= 1;
      if (chance == 0)
      {
        cout << "You lose!" << endl;
        cout << "The number was " << num << endl;
        break;
      }
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();
    }
  }
  guessed.clear();
  cout << "Press enter to continue" << endl;
  cin.ignore();
  cin.get();
}
void dice_game()
{
  cout << "Welcome to the dice game!" << endl;
  cout << "Press enter to play!" << endl;
  cin.ignore();
  cin.get();
  int roll = 0;
  int num = 0;

  while (roll <= 5)
  {
    cout << "\033[2J\033[1;1H";
    roll++;
    num = rand() % 6 + 1;
    switch (num)
    {
    case 1:

      cout << "\033[2J\033[1;1H";
      usleep(1000000);
      cout << "-------" << endl;
      cout << "|     |" << endl;
      cout << "|  *  |" << endl;
      cout << "|     |" << endl;
      cout << "-------" << endl;

      break;

    case 2:

      cout << "\033[2J\033[1;1H";
      usleep(1000000);
      cout << "-------" << endl;
      cout << "|*    |" << endl;
      cout << "|     |" << endl;
      cout << "|    *|" << endl;
      cout << "-------" << endl;
      break;

    case 3:
      cout << "\033[2J\033[1;1H";
      usleep(1000000);
      cout << "-------" << endl;
      cout << "|*    |" << endl;
      cout << "|  *  |" << endl;
      cout << "|    *|" << endl;
      cout << "-------" << endl;
      break;
    case 4:
      cout << "\033[2J\033[1;1H";
      usleep(1000000);
      cout << "-------" << endl;
      cout << "|*   *|" << endl;
      cout << "|     |" << endl;
      cout << "|*   *|" << endl;
      cout << "-------" << endl;
      break;

    case 5:

      cout << "\033[2J\033[1;1H";
      usleep(1000000);
      cout << "-------" << endl;
      cout << "|*   *|" << endl;
      cout << "|  *  |" << endl;
      cout << "|*   *|" << endl;
      cout << "-------" << endl;
      break;

    default:
      cout << "\033[2J\033[1;1H";
      usleep(1000000);
      cout << "-------" << endl;
      cout << "|*   *|" << endl;
      cout << "|*   *|" << endl;
      cout << "|*   *|" << endl;
      cout << "-------" << endl;
      break;
    }
  }
  int reward = num * 20;
  cout << "You won $" << reward << endl;
  debit += reward;
  cout << "Press enter to continue" << endl;
  cin.ignore();
  cin.get();
}
void typing_game()
{
  string type;
  int time = 2;
  cout << "Welcome to the typing game!" << endl;
  cout << "You will have 2 seconds to type as many word as you can!" << endl;
  cout << "Time: " << time << " seconds" << endl;
  cout << "Press enter to continue" << endl;
  cin.ignore();
  cin.get();
  cout << "Type as many words as you can: " << endl;

  while (time > 0)
  {
    cout << "\033[2J\033[1;1H";
    cout << "Time: " << time << " seconds" << endl;
    sleep(1);
    time--;
    if (time == 0)
    {
      cout << "\033[2J\033[1;1H";
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();
    }
  }
  cin >> type;
  debit += type.size();
  cout << "You earned $" << type.size() << endl;
  cout << "Press enter to continue" << endl;
  cin.ignore();
  cin.get();
}
void atm()
{
  cout << "Welcome to the ATM" << endl;
  cout << "1. Check balance" << endl;
  cout << "2. Withdraw" << endl;
  cout << "Choice: " << endl;
  int choice;
  cin >> choice;
  if (choice == 1)
  {
    cout << "You have $" << cash << " cash remaining" << endl;
    cout << "You have $" << debit << " remaining in your debit" << endl;
    cout << "Press enter to continue" << endl;
    cin.ignore();
    cin.get();
  }
  else
  {
    cout << "You have $" << debit << " remaining in your debit" << endl;
    cout << "How much would you like to withdraw" << endl;
    int withdraw;
    cin >> withdraw;
    if (withdraw > debit)
    {
      cout << "You dont have enought money" << endl;
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();
    }
    else
    {
      debit -= withdraw;
      cash += withdraw;
      cout << "You have $" << cash << " cash remaining" << endl;
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();
    }
  }
}
void fr()
{
  if (fridge.empty())
  {
    cout << "The fridge is empty" << endl;
  }
  else
  {
    for (int i = 0; i < fridge.size(); i++)
    {
      cout << "Fruit: " << get<0>(fridge[i]) << endl;
      cout << "Amount: " << get<1>(fridge[i]) << endl;
      cout << endl;
    }
  }
  cout << "Press enter to continue" << endl;
  cin.ignore();
  cin.get();
}

void s()
{
  if (shelves.empty())
  {
    cout << "The fridge is empty" << endl;
  }
  else
  {
    for (int i = 0; i < shelves.size(); i++)
    {
      cout << "Item: " << get<0>(shelves[i]) << endl;
      cout << "Amount: " << get<1>(shelves[i]) << endl;
      cout << endl;
    }
  }
  cout << "Press enter to continue" << endl;
  cin.ignore();
  cin.get();
}

bool check(string a){
  for (string i:fruits){
    if (a == i){
      for (auto& fruit: fridge){
        if (get<0>(fruit) == a && get<1>(fruit) >= 1){
          get<1>(fruit) -= 1;
          return true;
        }

      }
    }
    else{
      for (auto& item: shelves){
        if (get<0>(item) == a && get<1>(item) >= 1){
          if (a != "Rectangle cake mold" && a != "Round cake mold" && a != "Love cake mold") {
            get<1>(item) -= 1;
            return true;
}
          else if (a == "Rectangle cake mold" || a == "Round cake mold" || a == "Love cake mold"){
          return true;
          }
        }
      }
    }
  }
  return false;
}

void bake(){
  vector<unique_ptr<Cake>> cakes;
    cout << "\033[2J\033[1;1H";
    cout << "Enter cake type" << endl;
    cout << "1. Chocolate Cake" << endl;
    cout << "2. Strawberry Cake" << endl;
    cout << "3. Vanilla Cake" << endl;
    int cake_type;
    cin >> cake_type;


    cout << "Enter shape (rectangle,round,love): " << endl;
    cout << "1. Rectangle" << endl;
    cout << "2. Round" << endl;
    cout << "3. Love" << endl;
    string shape;
    int shapes;
    cout << "Choice: " << endl;
    cin >> shapes;
    if (shapes == 1){
      shape = "Rectangle cake mold";
    }
    else if (shapes == 2){
      shape = "Round cake mold";
    }
    else{
      shape = "Love cake mold";
    }
    if (!check(shape)){
      cout << "You dont have the correct mold" << endl;
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();
      return;
    }
    cout << "Press enter to continue" << endl;
    cin.ignore();
    cin.get();

    

    cout << "Enter color: " << endl;
    string color;
    cin >> color;
    if (!check("Food coloring")){
      cout << "You dont have the food coloring" << endl;
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();
      return;
    }
    cout << "Press enter to continue" << endl;
    cin.ignore();
    cin.get();

    if (cake_type == 1){
      cout << "Enter topping (chocolate sprinkles, nutella): " << endl;
      cout << "1. Chocolate sprinkles" << endl;
      cout << "2. Nutella" << endl;
      cout << "Choice: " << endl;
      int top;
      string topping;
      cin >> top;
      if (top == 1){
        topping = "Chocolate sprinkles";
        if (!check(topping)){
          cout << "You dont have enough " << topping << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
        
      }
      else{
        topping = "Nutella";
        if (!check(topping)){
          cout << "You dont have enough " << topping << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();
      

      cout << "Enter chocolate type (dark, milk): " << endl;
      string choc_type;
      cout << "1. Dark" << endl;
      cout << "2. Milk" << endl;
      cout << "Choice: " << endl;
      int choc;
      cin >> choc;
      if (choc == 1){
        choc_type = "Dark chocolate";
        if (!check(choc_type)){
          cout << "You dont have enough" << choc_type << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }

      }
      else{
        choc_type = "Milk chocolate";
        if (!check(choc_type)){
          cout << "You dont have enough" << choc_type << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }
      cout << "Press enter to continue" << endl;
        cin.ignore();
        cin.get();
      cakes.push_back(make_unique<ChocolateCake>(shape, color, topping, choc_type));
    }

    else if (cake_type == 2){
      cout << "Enter topping (rainbow sprinkles, candy): " << endl;
      string topping;
      cout << "1. Rainbow sprinkles" << endl;
      cout << "2. Candy" << endl;
      cout << "Choice: " << endl;
      int t;
      cin >> t;
      if (t == 1){
        topping = "Rainbow sprinkles";
        if (!check(topping)){
          cout << "You dont have enough" << topping << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }

      }
      else{
        topping = "Nutella";
        if (!check(topping)){
          cout << "You dont have enough" << topping << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();

      cout << "Enter frosting (vanilla, chocolate): " << endl;
      string frosting;
      cout << "1. Vanilla" << endl;
      cout << "2. Chocolate" << endl;
      cout << "Choice: " << endl;
      int f;
      cin >> f;
      if (f == 1){
        frosting = "Vanilla";
        if (!check(frosting)){
          cout << "You dont have enough" << frosting << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }
      else{
        frosting = "Chocolate";
        if (!check(frosting)){
          cout << "You dont have enough" << frosting << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }

      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();



      cout << "Enter fruits (strawberries, blueberries): " << endl;
      string fruits;
      cout << "1. Strawberries" << endl;
      cout << "2. Blueberries" << endl;
      cout << "Choice: " << endl;
      int fr;
      cin >> fr;
      if (fr == 1){
        fruits = "Strawberries";
        if (!check(fruits)){
          cout << "You dont have enough" << fruits << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }
      else{
        fruits = "Blueberries";
        fruits = "Strawberries";
        if (!check(fruits)){
          cout << "You dont have enough" << fruits << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();

      cakes.push_back(make_unique<StrawberryCake>(shape, color, topping, frosting, fruits));

    }

    else{
      cout << "Enter topping (Granola, rainbow sprinkles): " << endl;
      string topping;
      cout << "1. Granola" << endl;
      cout << "2. Rainbow sprinkles" << endl;
      cout << "Choice: " << endl;
      int topp;
      cin >> topp;
      if (topp == 1){
        topping = "Granola";
        if (!check(topping)){
          cout << "You dont have enough" << topping << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }
      else{
        topping = "Rainbow sprinkles";
        if (!check(topping)){
          cout << "You dont have enough" << topping << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();

      cout << "Enter nuts (almonds, hazelnuts, pistachio): " << endl;
      string nuts;
      cout << "1. Almonds" << endl;
      cout << "2. Hazel nuts" << endl;
      cout << "3. Pistachio" << endl;
      cout << "Choice: " << endl;
      int nu;
      cin >> nu;
      if (nu == 1){
        nuts = "Almonds";
        if (!check(nuts)){
          cout << "You dont have enough" << nuts << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }
      else if (nu == 2){
        nuts = "Hazel nuts";
        if (!check(nuts)){
          cout << "You dont have enough" << nuts << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }
      else{
        nuts = "Pistachio";
        if (!check(nuts)){
          cout << "You dont have enough" << nuts << endl;
          cout << "Press enter to continue" << endl;
          cin.ignore();
          cin.get();
          return;
        }
      }
      cout << "Press enter to continue" << endl;
      cin.ignore();
      cin.get();
      cakes.push_back(make_unique<VanillaCake>(shape, color, topping, nuts));

    }

    cout << "View displayed cakes? (y/n): " << endl;
    string view;
    cin >> view;
    if (view == "y"){
      cout << "\033[2J\033[1;1H";
    for (auto& cake : cakes){
      cake->cake_info();
      cake->cake_result();
      cout << endl;
    }
    cout << "Press enter to continue.." << endl;
    cin.ignore();
    cin.get();
    }
    else{
      cout << "Thank you for playing" << endl;
      cout << "Press enter to continue.." << endl;
      cin.ignore();
      cin.get();
      return;
    }

}

int main()
{
  srand(time(0));
  while (true)
  {
    cout << "\033[2J\033[1;1H";
    cout << "Work in real life simulator" << endl;
    cout << "You have $" << cash << " cash remaining" << endl;
    cout << "You have $" << debit << " remaining in your debit" << endl;
    cout << "1. Market" << endl;
    cout << "2. Work (Guessing Number (100), Dice Game (* = 20), Typing(2 Sec, as much u type))" << endl;
    cout << "3. ATM (cek debit, withdraw)" << endl;
    cout << "4. Inventory" << endl;
    cout << "5. Bake" << endl;
    cout << "Choice: " << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
      cout << "\033[2J\033[1;1H";
      cout << "1. Fruit Market(Cash)" << endl;
      cout << "2. Ingredient shop(Cash and Debit)" << endl;
      int choice6;
      cin >> choice6;
      if (choice6 == 1)
      {
        cout << "\033[2J\033[1;1H";
        shop();
      }
      else
      {
        cout << "\033[2J\033[1;1H";
        market();
      }
    }
    else if (choice == 2)
    {
      cout << "\033[2J\033[1;1H";
      cout << "1. Guessing number" << endl;
      cout << "2. Dice game" << endl;
      cout << "3. Typing game" << endl;
      cout << "Choice: " << endl;
      int choice2;
      cin >> choice2;
      if (choice2 == 1)
      {
        cout << "\033[2J\033[1;1H";
        guessing_game();
      }
      else if (choice2 == 2)
      {
        cout << "\033[2J\033[1;1H";
        dice_game();
      }
      else
      {
        cout << "\033[2J\033[1;1H";
        typing_game();
      }
    }
    else if (choice == 3)
    {
      cout << "\033[2J\033[1;1H";
      atm();
    }
    else if (choice == 4)
    {
      cout << "\033[2J\033[1;1H";
      cout << "1. Fridge" << endl;
      cout << "2. Shelves" << endl;
      int choice5;
      cin >> choice5;
      if (choice5 == 1)
      {
        cout << "\033[2J\033[1;1H";
        fr();
      }
      else
      {
        cout << "\033[2J\033[1;1H";
        s();
      }
    }
    else
    {
      cout << "\033[2J\033[1;1H";
      bake();
    }
  }
}
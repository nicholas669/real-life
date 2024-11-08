#include <iostream>

#include <vector>
#include <memory>
#include <string>
using namespace std;

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



int main(){
  vector<unique_ptr<Cake>> cakes;
  while (true){
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
      shape = "Rectangle";
    }
    else if (shapes == 2){
      shape = "Round";
    }
    else{
      shape = "Love";
    }
    cout << "Enter color: " << endl;
    string color;
    cin >> color;
    color = cap(color);
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
      }
      else{
        topping = "Nutella";
      }

      cout << "Enter chocolate type (dark, milk): " << endl;
      string choc_type;
      cout << "1. Dark" << endl;
      cout << "2. Milk" << endl;
      cout << "Choice: " << endl;
      int choc;
      cin >> choc;
      if (choc == 1){
        choc_type = "Dark";
      }
      else{
        choc_type = "Milk";
      }
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
      }
      else{
        topping = "Nutella";
      }

      cout << "Enter frosting (vanilla, chocolate): " << endl;
      string frosting;
      cout << "1. Vanilla" << endl;
      cout << "2. Chocolate" << endl;
      cout << "Choice: " << endl;
      int f;
      cin >> f;
      if (f == 1){
        frosting = "Vanilla";
      }
      else{
        frosting = "Chocolate";
      }

      cout << "Enter fruits (strawberries, blueberries): " << endl;
      string fruits;
      cout << "1. Strawberries" << endl;
      cout << "2. Blueberries" << endl;
      cout << "Choice: " << endl;
      int fr;
      cin >> fr;
      if (fr == 1){
        fruits = "Strawberries";
      }
      else{
        fruits = "Blueberries";
      }

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
      }
      else{
        topping = "Rainbow sprinkles";
      }
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
      }
      else if (nu == 2){
        nuts = "Hazel nuts";
      }
      else{
        nuts = "Pistachio";
      }
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
    }

  }


  return 0;
}
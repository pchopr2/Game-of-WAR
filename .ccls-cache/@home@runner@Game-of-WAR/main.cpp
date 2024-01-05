#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <time.h>
using namespace std;

class card  {
  public:
  string name;
  int powerlevel;
  bool assigned=false;
  card() {}
  card(string name, int pow);
};

card::card(string n, int pow){
  name = n;
  powerlevel = pow;
}

class unit: public card{
  public:
  int quantity;
};



void customRanks(){}

vector <unit> reading(){
  ifstream reading;
  reading.open("rank.txt");
  
  string reading2;
  string reading3;

  vector<unit>units;
  
  while(getline(reading,reading2)){
    reading3=reading3+reading2+",";
  }

  stringstream read(reading3);

  int i=1;
  
  string temp;
  unit bolus;
  
  while(getline(read,temp,',')){

    
    if(i==1){
      bolus.name=temp;
    }
    else if(i==2){
      int x=0;
      stringstream st(temp);
      st>>x;
      bolus.powerlevel=x;
    }
    else if(i==3){
      int x=0;
      stringstream st(temp);
      st>>x;
      bolus.quantity=x;
      units.push_back(bolus);
      i=0;
    }
    i++;
  }   
  cout<<"=====================================================\n"<<endl;
  cout<<"==========================deck=======================\n"<<endl;
  cout<<"=====================================================\n"<<endl;
  cout<<"=Rank=====================Skill===============Number=\n";
    cout.setf(ios::left);
    cout.width(10);cout<<" ";
    cout.setf(ios::right);
    cout.width(15);cout<<" ";
    cout.width(15);cout<<" "<<endl;
  
  for(int i=0;i<units.size();i++){
    cout.setf(ios::left);
    cout.width(10);cout<<units[i].name;
    cout.setf(ios::right);
    cout.width(21);cout<<units[i].powerlevel;
    cout.width(21);cout<<units[i].quantity<<endl;
  }
  return units;
}

vector<card> setDeck(vector<unit>units){
 vector<card>deck;
  for (auto unit: units) {
    for (int i = 0; i < unit.quantity; i++) {
      deck.push_back(card(unit.name, unit.powerlevel));
    }
  }
  return deck;
}

void printDeck(vector<card> d) {
  cout << "[";
  for (int i = 0; i < d.size(); i++) {
    cout << d[i].name;
    if (i != (d.size() - 1)){
      cout << ", ";
    }
  }
  cout << "]" << endl;
  
}



vector<vector<card>> splitDeck(vector<card>deck){
  // seed rng
  srand (time(NULL));
  vector<card>p1;
  vector<card>p2;
  card holder;
  int random=0;
  
  for(int i = 0;i<deck.size()/2;i++){
    bool condition1=false;
    bool condition2=false;

    while (condition1==false){
      random=rand()%deck.size();
      if(deck[random].assigned==false){
        holder=deck[random];
        p1.push_back(holder);
        deck[random].assigned=true;
        condition1=true;
        break;
      }
      else{
        continue;
      }
    }
    
    while (condition2==false){
      random=rand()%deck.size();
      if(deck[random].assigned==false){
        holder=deck[random];
        p2.push_back(holder);
        deck[random].assigned=true;
        condition2=true;
        break;
      }
      else{
        continue;
      }
    }  
  }

  vector<vector<card>> r = {p1, p2};
  
  return r;
}

void intro(){
  cout<<"           Lets being the CARD GAME\n";
  cout<<"The player with the most power cards shall win!\n";
}

int playGame(vector<card> p1, vector<card> p2) {
  bool gameOver = false;
  int p1_score = 0;
  int p2_score = 0;
  while (!gameOver) {
    card c1 = p1.back();
    card c2 = p2.back();
    p1.pop_back();
    p2.pop_back();
    cout << "Player 1 plays card \"" << c1.name << "\" that has power " << c1.powerlevel << endl;
        cout << "Player 2 plays card \"" << c2.name << "\" that has power " << c2.powerlevel << endl;
    if (c1.powerlevel > c2.powerlevel) {
      cout << "Player 1 wins the round" << endl;
      p1_score++;
    } else if (c1.powerlevel < c2.powerlevel) {
      cout << "Player 2 wins the round" << endl;
      p2_score++;
    } else {
      cout << "Tie: trying again with next cards..." << endl;
    }

    if(p1.size() == 0 || p2.size() == 0) {
      gameOver = true;
    }

    
  }

  if (p1_score > p2_score) {
    return 1;
  } else if (p2_score > p1_score) {
    return -1;
  }
  return 0;
}


int main() {
  // Set DeckT to be an alias for vector<card>
  typedef vector<card> DeckT; 
  
  intro();
  
  vector<unit>units = reading();
  
  DeckT deck = setDeck(units);
  
  printDeck(deck);

  // Shuffles and deals hand to both players
  vector<DeckT> hands = splitDeck(deck);

  DeckT p1 = hands.at(0);
  DeckT p2 = hands.at(1);

  cout << endl;
  cout << "Player 1 dealt:" << endl;
  printDeck(p1);

  cout << endl;
  cout << "Player 2 dealt:" << endl;
  printDeck(p2);

  int result = playGame(p1, p2);
  
  if(result == 1){
    cout<<"\nPlayer One Wins"<<endl;
  }
  else if(result == -1){
    cout<<"\nPlayer Two Wins"<<endl;
  } else {
    cout << "\nTie Game" << endl;
  }
}    
//szachy zrodlo

// Krzysztof Urbañczyk,IZ04P02
#include <vector>
#include <iostream>
#include <iomanip>
#include <string>
#include <stdexcept>

using namespace std;

class pionek{
public:
	string name;
	string color;

pionek(string n, string c);

virtual void ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8])=0;//przyjmuje globalne wektory ruchu, czysci i uzupelnia o nowe ruchy
};

class pawn : public pionek{
public:
pawn(string c);
void ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]);
};

class king : public pionek{
public:
king(string c);
void ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]);
};

class knight : public pionek{
public:
knight(string c);
void ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]);
};

class bishop : public pionek{
public:
bishop(string c);
void ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]);
};

class rook : public pionek{
public:
rook(string c);
void ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]);
};

class queen : public pionek{
public:
queen(string c);
void ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]);
};


class szachownica{
public:
	pionek *plan[8][8];

szachownica();
void show();
friend szachownica& operator<<(szachownica &P,const szachownica &M);
};


szachownica& operator<<(szachownica &P,const szachownica &M);
void show_ruchy(const szachownica &A, const short tab[8][8]);
void tab_polozen(short tab[8][8], const szachownica &p1);
bool ruchy(szachownica &p1,const short &x, const short &y); // przyjmuje polozenie pionka i sugeruje dostepne ruchy. W przypadku braku pionka wypisuje komentarz.



int main(){
bool gra,tura;

short rx, ry;
short tab[8][8] = {0};
szachownica p1; // p1 - tablica glowna, p2 - tablica probnego ruchu, p3 - tablica mozliwego bicia bicia


// gra:
gra=true;tura=false;

while(gra==true){
	while(tura==false){
		p1.show();
		cout << "wybierz element\nrzad: ";
		cin >> rx;
		cout << "kolumne: ";
		cin >> ry;
		system("CLS");
		tura=ruchy(p1,--rx,--ry);
		cout<<endl;
		system("PAUSE");
		system("CLS");
	}
	tura=false;
}
}


//dopisac awans, szach lub szach mat.

pionek::pionek(string n,string c):name(n),color(c){}

pawn::pawn(string c):pionek("P",c){}
king::king(string c):pionek("K",c){}
knight::knight(string c):pionek("H",c){}
bishop::bishop(string c):pionek("G",c){}
rook::rook(string c):pionek("W",c){}
queen::queen(string c):pionek("H",c){}

szachownica::szachownica(){
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			plan[i][j]=0;
		}
	}
	for(i=0;i<8;i++){
		plan[1][i]= new pawn("b");
		plan[6][i]= new pawn("c");
	}

	plan[0][0]=new rook("b");
	plan[0][1]=new knight("b");
	plan[0][2]=new bishop("b");
	plan[0][3]=new queen("b");
	plan[0][4]=new king("b");
	plan[0][5]=new bishop("b");
	plan[0][6]=new knight("b");
	plan[0][7]=new rook("b");

	plan[7][0]=new rook("c");
	plan[7][1]=new knight("c");
	plan[7][2]=new bishop("c");
	plan[7][3]=new queen("c");
	plan[7][4]=new king("c");
	plan[7][5]=new bishop("c");
	plan[7][6]=new knight("c");
	plan[7][7]=new rook("c");


}

void szachownica::show(){
	for(int i=7;i>-1;i--){
		cout << i +1 << "|";
		for(int j=0;j<8;j++){
			plan[i][j]==0 ? cout << "   |" : cout << " " << plan[i][j]->name << plan[i][j]->color <<"|";
			
		}cout << endl;
	}	cout << " | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |" << endl << endl;
}

szachownica& operator<<(szachownica &P,const szachownica &M){
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
		P.plan[i][j]=M.plan[i][j];
		}
	}
}


void show_ruchy(const szachownica &A, const short tab[8][8]){ //wypisuje szachownice z dostepnymi ruchami i zaznazonym pionkiem
	for(int i=7;i>-1;i--){
		cout << i +1 << "|";
		for(int j=0;j<8;j++){
			tab[i][j]==1 ? cout << "X" :  (tab[i][j]==2 ? cout << "*" : cout <<" ");
			A.plan[i][j]==0 ? cout << "  |" : cout << A.plan[i][j]->name << A.plan[i][j]->color <<"|";
			
		}cout << endl;
	}	cout << " | 1 | 2 | 3 | 4 | 5 | 6 | 7 | 8 |" << endl << endl;
}
void tab_polozen(short tab[8][8], const szachownica &p1){
	for(int i=0;i<8;i++){
		for(int j=0;j<8;j++){
			if(p1.plan[i][j]!=0){
				if(p1.plan[i][j]->color=="b")
					tab[i][j]=1;
				else tab[i][j]=2;
			}
		}
	}
}


bool ruchy(szachownica &p1,const short &x, const short &y){ // x,y - polozenia wybranego pionka
	short ruchy[8][8] = {0},polozenia[8][8]={0},rx,ry;
	char confirm;
	vector<int> H,V;
	szachownica p2;
	p2<<p1;
	tab_polozen(polozenia,p1);//generuje tablice polozen, gdzie biale = 1, a czarne = 2.
	if(p1.plan[x][y]!=0){
		p1.plan[x][y]->ruchy(H,V,x,y,polozenia); // modyfikuje wektory H i V w oparciu o tablice polozen. Zwracane wektory sa zbiorem wspolrzednych dostepnych ruchow.
		if(V.size()!=0){
			for(int k=0;k<V.size();k++){ // przepisanie wektorow do tablicy dostepnych ruchow.
				ruchy[x+H[k]][y+V[k]]=1;
			}
			ruchy[x][y]=2; //zaznaczam polozenie wybranego pionka
			show_ruchy(p1,ruchy); //pokazuje p1 z dostepnymi ruchami w oparciu o tablice ruchy
			cout << "podaj miejsce, gdzie chcesz sie ruszyc. \nrzad: ";	cin >> rx;
			cout << "kolumna: "; cin >> ry; 
			if(ruchy[--rx][--ry]==1){
				p2.plan[rx][ry]=p2.plan[x][y];p2.plan[x][y]=0;
			p2.show();
			cout << "Czy potwierdzasz ten ruch? (t)" << endl;
			cin >> confirm;
				if(confirm=='t'){
					p1<<p2; return true;
				}else return false;

			}else{ cout << "taki ruch nie jest dostepny" << endl; return false;}
		}else{cout << "ten element nie ma dostepnych ruchów" << endl; return false;}
	}else{cout << "w tym miejscu nie ma nic do wybrania" << endl; return false;}
}

void pawn::ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]){
	short a[2];
	V.clear();H.clear();
	
if(this->color=="b"){
//bicie lewo
	if(y>0 && tab_polozen[x+1][y-1]==2){
		a[0]=1;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo
	if(y<7 && tab_polozen[x+1][y+1]==2){
		a[0]=1;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//ruch do przodu
	if(tab_polozen[x+1][y]==0){
		a[0]=1; //0 dla pionu
		a[1]=0; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//ruch do przodu x2
	if(x==1 && tab_polozen[x+2][y]==0){
		a[0]=2;	//0 dla pionu
		a[1]=0; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
}

if(this->color=="c"){
//bicie lewo
	if(y>0 && tab_polozen[x-1][y-1]==1){
		a[0]=-1;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo
	if(y<7 && tab_polozen[x-1][y+1]==1){
		a[0]=-1;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//ruch do przodu
	if(tab_polozen[x-1][y]==0){
		a[0]=-1;	//0 dla pionu
		a[1]=0; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//ruch do przodu x2
	if(x==6 && tab_polozen[x-2][y]==0){
		a[0]=-2;	//0 dla pionu
		a[1]=0; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
}

}




void king::ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]){
	short a[2];
	V.clear();H.clear();
	
if(this->color=="b"){ //tab_polozen =2 dla czarnych, =1 dla bialych
//bicie lewo gora
	if(y>0 && x<7 && tab_polozen[x+1][y-1]!=1){
		a[0]=1;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie lewo
	if(y>0  && tab_polozen[x][y-1]!=1){
		a[0]=0;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie lewo dol
	if(y>0  && x>0 && tab_polozen[x-1][y-1]!=1){
		a[0]=-1;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo gora
	if(y<7 && x<7 && tab_polozen[x+1][y+1]!=1){
		a[0]=1;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo
	if(y<7  && tab_polozen[x][y+1]!=1){
		a[0]=0;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo dol
	if(y<7  && x>0 && tab_polozen[x-1][y+1]!=1){
		a[0]=-1;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie dol
	if( x>0 && tab_polozen[x-1][y]!=1){
		a[0]=-1;	//0 dla pionu
		a[1]=0; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie gora
	if(x<7 && tab_polozen[x+1][y]!=1){
		a[0]=1;	//0 dla pionu
		a[1]=0; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
}

if(this->color=="c"){ //tab_polozen =2 dla czarnych, =1 dla bialych
//bicie lewo gora
	if(y>0 && x<7 && tab_polozen[x+1][y-1]!=2){
		a[0]=1;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie lewo
	if(y>0  && tab_polozen[x][y-1]!=2){
		a[0]=0;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie lewo dol
	if(y>0  && x>0 && tab_polozen[x-1][y-1]!=2){
		a[0]=-1;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo gora
	if(y<7 && x<7 && tab_polozen[x+1][y+1]!=2){
		a[0]=1;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo
	if(y<7  && tab_polozen[x][y+1]!=2){
		a[0]=0;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo dol
	if(y<7  && x>0 && tab_polozen[x-1][y+1]!=2){
		a[0]=-1;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie dol
	if(x>0 && tab_polozen[x-1][y]!=2){
		a[0]=-1;	//0 dla pionu
		a[1]=0; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie gora
	if(x<7 && tab_polozen[x+1][y]!=2){
		a[0]=1;	//0 dla pionu
		a[1]=0; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
}

}


void knight::ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]){
	short a[2];
	V.clear();H.clear();
	
if(this->color=="b"){ //tab_polozen =2 dla czarnych, =1 dla bialych
//bicie gora lewo
	if(x<6 && y>0 && tab_polozen[x+2][y-1]!=1){
		a[0]=2;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie gora prawo
	if(x<6 && y<7 && tab_polozen[x+2][y+1]!=1){
		a[0]=2;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo gora
	if(x<7 && y<6 && tab_polozen[x+1][y+2]!=1){
		a[0]=1;	//0 dla pionu
		a[1]=2; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo dol
	if(x>0 && y<6 && tab_polozen[x-1][y+2]!=1){
		a[0]=-1;	//0 dla pionu
		a[1]=2; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie dol prawo
	if(x>1 && y<7 && tab_polozen[x-2][y+1]!=1){
		a[0]=-2;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie dol lewo
	if(x>1 && y>0 && tab_polozen[x-2][y-1]!=1){
		a[0]=-2;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie lewo dol
	if(x>0 && y>1 && tab_polozen[x-1][y-2]!=1){
		a[0]=-1;	//0 dla pionu
		a[1]=-2; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie lewo gora
	if(x<7 && y>1 && tab_polozen[x+1][y-2]!=1){
		a[0]=1;	//0 dla pionu
		a[1]=-2; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
}

if(this->color=="c"){ //tab_polozen =2 dla czarnych, =1 dla bialych
//bicie gora lewo
	if(x<6 && y>0 && tab_polozen[x+2][y-1]!=2){
		a[0]=2;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie gora prawo
	if(x<6 && y<7 && tab_polozen[x+2][y+1]!=2){
		a[0]=2;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo gora
	if(x<7 && y<6 && tab_polozen[x+1][y+2]!=2){
		a[0]=1;	//0 dla pionu
		a[1]=2; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie prawo dol
	if(x>0 && y<6 && tab_polozen[x-1][y+2]!=2){
		a[0]=-1;	//0 dla pionu
		a[1]=2; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie dol prawo
	if(x>1 && y<7 && tab_polozen[x-2][y+1]!=2){
		a[0]=-2;	//0 dla pionu
		a[1]=1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie dol lewo
	if(x>1 && y>0 && tab_polozen[x-2][y-1]!=2){
		a[0]=-2;	//0 dla pionu
		a[1]=-1; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie lewo dol
	if(x>0 && y>1 && tab_polozen[x-1][y-2]!=2){
		a[0]=-1;	//0 dla pionu
		a[1]=-2; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
//bicie lewo gora
	if(x<7 && y>1 && tab_polozen[x+1][y-2]!=2){
		a[0]=1;	//0 dla pionu
		a[1]=-2; // 1 dla poziomu
	V.push_back(a[0]);H.push_back(a[1]);
	}
}

}



void bishop::ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]){
	short a[2],i,j;
	V.clear();H.clear();
	
if(this->color=="b"){ //tab_polozen =2 dla czarnych, =1 dla bialych
//bicie gora prawo
	if(x<7 && y<7){
		i=x;j=y;
		while(i<7 && j<7){
		i++;j++;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==1){
				i=7;
			}
			if(tab_polozen[i][j]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=7;
			}
		}
	}
//bicie dol lewo
	if(x>0 && y>0){
		i=x;j=y;
		while(i>0 && j>0){
		i--;j--;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==1){
				i=0;
			}
			if(tab_polozen[i][j]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=0;
			}
		}
	}
//bicie gora lewo
	if(x<7 && y>0){
		i=x;j=y;
		while(i<7 && j>0){
		i++;j--;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==1){
				i=7;
			}
			if(tab_polozen[i][j]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=7;
			}
		}
	}
//bicie dol prawo lewo
	if(x>0 && y<7){
		i=x;j=y;
		while(i>0 && j<7){
		i--;j++;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==1){
				i=0;
			}
			if(tab_polozen[i][j]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=0;
			}
		}
	}
}

if(this->color=="c"){ //tab_polozen =2 dla czarnych, =1 dla bialych
//bicie gora prawo
	if(y<7 && x<7){
		i=x;j=y;
		while(i<7 && j<7){
		i++;j++;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==2){
				i=7;
			}
			if(tab_polozen[i][j]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=7;
			}
		}
	}
//bicie dol lewo
	if(x>0 && y>0){
		i=x;j=y;
		while(i>0 && j>0){
		i--;j--;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==2){
				i=0;
			}
			if(tab_polozen[i][j]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=0;
			}
		}
	}
//bicie gora lewo
	if(x<7 && y>0){
		i=x;j=y;
		while(i<7 && j>0){
		i++;j--;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==2){
				i=7;
			}
			if(tab_polozen[i][j]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=7;
			}
		}
	}
//bicie dol prawo lewo
	if(x>0 && y<7){
		i=x;j=y;
		while(i>0 && j<7){
		i--;j++;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==2){
				i=0;
			}
			if(tab_polozen[i][j]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=0;
			}
		}
	}
}
}


void rook::ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]){
	short a[2],i;
	V.clear();H.clear();
	
if(this->color=="b"){ //tab_polozen =2 dla czarnych, =1 dla bialych
//bicie lewo
	if(y>0){
		i=y;
		while(i>0){
		i--;
			if(tab_polozen[x][i]==0){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[x][i]==1){
			break;
			}
			if(tab_polozen[x][i]==2){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie prawo
	if(y<7){
		i=y;
		while(i<7){
		i++;
			if(tab_polozen[x][i]==0){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[x][i]==1){
			break;
			}
			if(tab_polozen[x][i]==2){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie gora
	if(x>0){
		i=x;
		while(i>0){
		i--;
			if(tab_polozen[i][y]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][y]==1){
			break;
			}
			if(tab_polozen[i][y]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie dol
	if(x<7){
		i=x;
		while(i<7){
		i++;
			if(tab_polozen[i][y]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][y]==1){
			break;
			}
			if(tab_polozen[i][y]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
}

if(this->color=="c"){ //tab_polozen =2 dla czarnych, =1 dla bialych
//bicie lewo
	if(y>0){
		i=y;
		while(i>0){
		i--;
			if(tab_polozen[x][i]==0){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[x][i]==2){
			break;
			}
			if(tab_polozen[x][i]==1){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie prawo
	if(y<7){
		i=y;
		while(i<7){
		i++;
			if(tab_polozen[x][i]==0){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[x][i]==2){
			break;
			}
			if(tab_polozen[x][i]==1){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie gora
	if(x>0){
		i=x;
		while(i>0){
		i--;
			if(tab_polozen[i][y]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][y]==2){
			break;
			}
			if(tab_polozen[i][y]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie dol
	if(x<7){
		i=x;
		while(i<7){
		i++;
			if(tab_polozen[i][y]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][y]==2){
				break;
			}
			if(tab_polozen[i][y]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
}

}



void queen::ruchy(vector<int> &V, vector<int> &H,const short &x, const short &y, const short tab_polozen[8][8]){
	short a[2],i,j;
	V.clear();H.clear();

if(this->color=="b"){ //tab_polozen =2 dla czarnych, =1 dla bialych
//bicie gora prawo
	if(x<7 && y<7){
		i=x;j=y;
		while(i<7 && j<7){
		i++;j++;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==1){
				i=7;
			}
			if(tab_polozen[i][j]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=7;
			}
		}
	}
//bicie dol lewo
	if(x>0 && y>0){
		i=x;j=y;
		while(i>0 && j>0){
		i--;j--;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==1){
				i=0;
			}
			if(tab_polozen[i][j]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=0;
			}
		}
	}
//bicie gora lewo
	if(x<7 && y>0){
		i=x;j=y;
		while(i<7 && j>0){
		i++;j--;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==1){
				i=7;
			}
			if(tab_polozen[i][j]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=7;
			}
		}
	}
//bicie dol prawo
	if(x>0 && y<7){
		i=x;j=y;
		while(i>0 && j<7){
		i--;j++;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==1){
				i=0;
			}
			if(tab_polozen[i][j]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=0;
			}
		}
	}

//bicie lewo
	if(y>0){
		i=y;
		while(i>0){
		i--;
			if(tab_polozen[x][i]==0){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[x][i]==1){
			break;
			}
			if(tab_polozen[x][i]==2){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie prawo
	if(y<7){
		i=y;
		while(i<7){
		i++;
			if(tab_polozen[x][i]==0){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[x][i]==1){
			break;
			}
			if(tab_polozen[x][i]==2){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie gora
	if(x>0){
		i=x;
		while(i>0){
		i--;
			if(tab_polozen[i][y]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][y]==1){
			break;
			}
			if(tab_polozen[i][y]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie dol
	if(x<7){
		i=x;
		while(i<7){
		i++;
			if(tab_polozen[i][y]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][y]==1){
			break;
			}
			if(tab_polozen[i][y]==2){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
}

if(this->color=="c"){ //tab_polozen =2 dla czarnych, =1 dla bialych
//bicie gora prawo
	if(y<7 && x<7){
		i=x;j=y;
		while(i<7 && j<7){
		i++;j++;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==2){
				i=7;
			}
			if(tab_polozen[i][j]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=7;
			}
		}
	}
//bicie dol lewo
	if(x>0 && y>0){
		i=x;j=y;
		while(i>0 && j>0){
		i--;j--;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==2){
				i=0;
			}
			if(tab_polozen[i][j]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=0;
			}
		}
	}
//bicie gora lewo
	if(x<7 && y>0){
		i=x;j=y;
		while(i<7 && j>0){
		i++;j--;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==2){
				i=7;
			}
			if(tab_polozen[i][j]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=7;
			}
		}
	}
//bicie dol prawo
	if(x>0 && y<7){
		i=x;j=y;
		while(i>0 && j<7){
		i--;j++;
			if(tab_polozen[i][j]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][j]==2){
				i=0;
			}
			if(tab_polozen[i][j]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=j-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			i=0;
			}
		}
	}

//bicie lewo
	if(y>0){
		i=y;
		while(i>0){
		i--;
			if(tab_polozen[x][i]==0){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[x][i]==2){
			break;
			}
			if(tab_polozen[x][i]==1){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie prawo
	if(y<7){
		i=y;
		while(i<7){
		i++;
			if(tab_polozen[x][i]==0){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[x][i]==2){
			break;
			}
			if(tab_polozen[x][i]==1){
				a[0]=0;	//0 dla pionu
				a[1]=i-y; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie gora
	if(x>0){
		i=x;
		while(i>0){
		i--;
			if(tab_polozen[i][y]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][y]==2){
			break;
			}
			if(tab_polozen[i][y]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
//bicie dol
	if(x<7){
		i=x;
		while(i<7){
		i++;
			if(tab_polozen[i][y]==0){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			}
			if(tab_polozen[i][y]==2){
				break;
			}
			if(tab_polozen[i][y]==1){
				a[0]=i-x;	//0 dla pionu
				a[1]=0; // 1 dla poziomu
			V.push_back(a[0]);H.push_back(a[1]);
			break;
			}
		}
	}
}

}


/*
Nama	    : Hanifan Ayusti Khairunnisa
NPM		    : 140810200065
Kelas	    : A
*/

#include <iostream>
#include <limits>
#include <math.h>
#include <vector>

using matrix = std::vector<std::vector<int>>;

void menu();
void encryption(int);
void decryption(int);
void getCofactor(matrix&, matrix&, int, int);
int determinant(matrix&, int);
void adjoint(matrix&, matrix&);
void displayMatrix(matrix);
int mod(int, int);
void findKeyMatrix(int);
void ignoreLine();
void errorMessage(std::string);

int main() {
  char yesNo;

  do {
    yesNo = ' ';

    std::cout << "\n====== Hill Cipher ======\n" << std::endl;
    menu();

    while (toupper(yesNo) != 'Y' && toupper(yesNo) != 'N') {
      std::cout << "\nMulai lagi (Y/N)\t: ";
      std::cin >> yesNo;
      std::cin.ignore();
    }
  } while(toupper(yesNo) == 'Y');

  return 0;
}

void menu() {
  int m;

  std::cout << "Ukuran matriks (x,y)\t: ";
  std::cin >> m;

  int operation;
  std::cout << "\n==========================" << std::endl;
  std::cout << "1. Enkripsi\n";
  std::cout << "2. Dekripsi\n";
  std::cout << "3. Cari Kunci\n";
  std::cout << "Pilih operasi\t: ";
  std::cin >> operation;

  if(operation==1){
    encryption(m);
  } else if(operation==2){
    decryption(m);
  } else if(operation==3){
    findKeyMatrix(m);
  } else{
    errorMessage("Invalid operation, please try again");
  }
}

void encryption(int m) {
  std::cout << "\n------Enkripsi------\n";
  std::string text;
  int msg[m][1], hasil[m][1];
  matrix key;

  std::cout << "Pesan\t\t: ";
  std::cin >> text;

  std::cout << "Matriks Kunci\t:\n";
  int temp;
  for(int i=0; i<m; i++){
    std::vector<int> row;
    for(int j=0; j<m; j++){
      std::cin >> temp;
      row.push_back(temp);
    } key.push_back(row);
  }

  std::cout << "\n==========================" << std::endl;
  std::cout << "Pesan\t\t: " << text << std::endl;
  std::cout << "Matriks Kunci\t:\n";
  displayMatrix(key);

  std::string encryp="";

  while(text.length()!=0){
    for(int i=0; i<m; i++){
      if(isupper(text[i]))
        msg[i][0] = text[i]-65;
      else
        msg[i][0] = text[i]-97;
    }

    for(int i=0; i<m; i++){
      for(int j=0; j<1; j++){
        hasil[i][j]=0;
        for(int k=0; k<m; k++){
          hasil[i][j] += key[i][k] * msg[k][j];
        }
        hasil[i][j]=hasil[i][j]%26;
      }
    }

    for(int i=0; i<m; i++){
      if(isupper(text[i]))
        encryp += hasil[i][0]+65;
      else
        encryp += hasil[i][0]+97;
    }
    text.erase(0,m);
  }

  std::cout << "Ciphertext\t: " << encryp << std::endl;
}

void decryption(int m) {
  std::cout << "\n------Dekripsi------\n";
  std::string text;
  int msg[m][1], hasil[m][1];
  matrix key;

  std::cout << "Pesan\t\t: ";
  std::cin >> text;

  std::cout << "Matriks Kunci\t:\n";
  int temp;
  for(int i=0; i<m; i++){
    std::vector<int> row;
    for(int j=0; j<m; j++){
      std::cin >> temp;
      row.push_back(temp);
    } key.push_back(row);
  }

  std::cout << "\n==========================" << std::endl;
  std::cout << "Pesan\t\t: " << text << std::endl;
  std::cout << "Matriks Kunci\t:\n";
  displayMatrix(key);

  matrix adj(key.size(), std::vector<int>(key.size()));

  int det = determinant(key, m);
  adjoint(key, adj);

  int det_inv = 0;
  int flag = 0;

  for(int i=0; i<26; i++){
    flag = mod((det*i),26);

    if(flag == 1){
      det_inv = i;
    }
  }

  matrix i_mtx(key.size(), std::vector<int>(key.size()));

  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      i_mtx[i][j] = mod((adj[i][j]*det_inv),26);
    }
  }

  std::cout << "\nKunci baru :\n";
  displayMatrix(i_mtx);

  std::string decryp="";

  while(text.length()!=0){
    for(int i=0; i<m; i++){
      if(isupper(text[i]))
        msg[i][0] = text[i]-65;
      else
        msg[i][0] = text[i]-97;
    }

    for(int i=0; i<m; i++){
      for(int j=0; j<1; j++){
        hasil[i][j]=0;
        for(int k=0; k<m; k++){
          hasil[i][j] += i_mtx[i][k] * msg[k][j];
        }
        hasil[i][j]=hasil[i][j]%26;
      }
    }
    for(int i=0; i<m; i++){
      if(isupper(text[i]))
        decryp += hasil[i][0]+65;
      else
        decryp += hasil[i][0]+97;
    }
    text.erase(0,m);
  }

  std::cout << "\nPlaintext\t: " << decryp << std::endl;
}

void findKeyMatrix(int m) {
  std::cout << "\n------Cari Kunci------\n";
  std::string plain, cipher;
  int pln[m][1], cpr[m][1];
  matrix key(m, std::vector<int>(m)), c(m, std::vector<int>(m)), p(m, std::vector<int>(m)), adj(p.size(), std::vector<int>(p.size())), p_inv(p.size(), std::vector<int>(p.size()));

  std::cout << "Plaintext\t: ";
  std::cin >> plain;
  std::cout << "Ciphertext\t: ";
  std::cin >> cipher;

  std::cout << "\n==========================" << std::endl;
  std::cout << "Plaintext\t: " << plain << std::endl;
  std::cout << "Ciphertext\t: " << cipher << std::endl;

  if(plain.length()==cipher.length()){
    for(int i=0; i<m*m; i++){
      if(isupper(plain[i])){
        pln[i][0] = plain[i]-65;
      }
      else
        pln[i][0] = plain[i]-97;
    }
    for(int i=0; i<m*m; i++){
      if(isupper(cipher[i])){
        cpr[i][0] = cipher[i]-65;
      }
      else
        cpr[i][0] = cipher[i]-97;
    }
  } else{
    errorMessage("Panjang Plaintext dan Ciphertext Harus Sama!");
  }

  int k=0;
  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      c[j][i] = cpr[k][0];
      k++;
    }
  }

  k=0;
  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      p[j][i] = pln[k][0];
      k++;
    }
  }

  int det = determinant(p, m);
  adjoint(p, adj);

  int det_inv = 0;
  int flag = 0;

  for(int i=0; i<26; i++){
    flag = mod((det*i),26);

    if(flag == 1){
      det_inv = i;
    }
  }

  for(int i=0; i<m; i++){
    for(int j=0; j<m; j++){
      p_inv[i][j] = mod((adj[i][j]*det_inv),26);
    }
  }

  for(int i=0; i<c.size(); i++){
    for(int j=0; j<p_inv.size(); j++){
      for(int k=0; k<c.size(); k++){
        key[i][j] = mod((key[i][j]+c[i][k]*p_inv[k][j]),26);
      }
    }
  }

  std::cout << "\nMatriks Kunci\t:\n";
  displayMatrix(key);
}

void getCofactor(matrix &key, matrix &temp, int p, int q) {
  int i=0, j=0;
  for(int r=0; r<key.size(); r++){
    for (int c=0; c<key.size(); c++){
      if(r!=p && c!=q){
        temp[i][j++] = key[r][c];
      }
      if (j==key.size()-1){
        j=0;
        i++;
      }
    }
  }
}

int determinant(matrix &key, int n) {
  if(n==1){
    return key[0][0];
  }
  int det=0;
  matrix temp(3, std::vector<int>(3));
  int sign=1;

  for(int i=0; i<key.size(); i++){
    getCofactor(key, temp, 0, i);
    det += sign*key[0][i]*determinant(temp, n-1);
    sign = -sign;
  }
  return det;
}

void adjoint(matrix &key, matrix &adj) {
  if(key.size()==1){
    adj[0][0]=1;
    return;
  }
  int sign=1;
  matrix temp(key.size(), std::vector<int>(key.size()));
  for(int i=0; i<key.size(); i++){
    for(int j=0; j<key.size(); j++){
      getCofactor(key, temp, i, j);
      sign = ((i+j)%2==0)? 1: -1;
      adj[j][i] = (sign)*(determinant(temp, key.size()-1));
    }
  }
}

void displayMatrix(matrix mtx) {
  for(int i=0; i<mtx.size(); i++){
    for(int j=0; j<mtx.size(); j++){
      std::cout << mtx[i][j] << "\t";
    } std::cout << "\n";
  }
}

int mod(int a, int b) { return (a%b+b)%b;};

void ignoreLine() {
  std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void errorMessage(std::string s) {
  std::cout << "\n//ERROR\n";
  std::cout << s.c_str() << '\n';
}
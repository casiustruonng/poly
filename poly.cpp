#include <bits/stdc++h>
using namespace std;
struct Pair{
    float degree, cof;
};
struct Poly_o{
    int terms;
    float max_deg;
    Pair arr[100];
};
void display(Pair* arr, int n){
    for (int i = 0; i < n; i++){
        cout << arr[i].degree << " " << arr[i].cof << '\n';
    }
}
void input_arr(Pair* arr, int n, float& max_deg){
    for (int i = 0; i < n; i++){k
        cout << "Enter the degree: "; cin >> arr[i].degree;
        cout << "Enter the coefficent: "; cin >> arr[i].cof;
    }
    float max = arr[0].degree;
    for (int i = 0; i < n; i++){
        if (arr[i].degree > max) max = arr[i].degree;
    }
    max_deg = max;
}
void Into_bin(Poly_o* arr, int count){
    ofstream out;
    out.open("POLY.bin",ios::binary);
    if (out.is_open()){
        out.write((char*)& count, 2);
        for (int i = 0; i < count; i++){
            out.write((char*)& arr[i].terms,2);
            out.write((char*)& arr[i].max_deg,4);
            out.write((char*) arr[i].arr, 8*arr[i].terms);
        }
    }
    out.close();
}
void Out_bin(Poly_o* arr, int&count){
    ifstream in;
    in.open("POLY.bin",ios::binary);
    if (in.is_open()){
        in.read((char*)& count,2);
        for (int i = 0; i < count; i++){
            in.read((char*)& arr[i].terms,2);
            in.read((char*)& arr[i].max_deg,4);
            in.read((char*) arr[i].arr, 8*arr[i].terms);
        }
    }
    in.close();
}
void Into_bin_max_deg(Poly_o* arr, int&n){
    float cur = arr[0].max_deg; int count = 0;
    for (int i = 0; i < n; i++){
        if (arr[i].max_deg >= cur) {
            cur = arr[i].max_deg;
            count ++;
        }
    }
    ofstream out;
    out.open("POLY_LARGEST.bin",ios::binary);
    for (int i = 0; i < n; i++){
        if (arr[i].max_deg == cur){
            out.write((char*)& arr[i].terms,2);
            out.write((char*)& arr[i].max_deg,4);
            out.write((char*) arr[i].arr, 8*arr[i].terms);
        }
    }
    out.close();
    n = count;
}
void Out_bin_max_deg(Poly_o*arr,int n2){
    ifstream in;
    in.open("POLY_LARGEST.bin",ios::binary);
    if (in.is_open()){
        for (int i = 0; i < n2; i++){
            in.read((char*)& arr[i].terms,2);
            in.read((char*)& arr[i].max_deg,4);
            in.read((char*) arr[i].arr, 8*arr[i].terms);
        }
    }
    in.close();
}
void display_poly(Poly_o* arr, int count){
    for (int i = 0; i < count; i++){
        cout << arr[i].terms << '\n';
        cout << "Max deg: " << arr[i].max_deg << endl;
        display(arr[i].arr,arr[i].terms); 
    }
}
int main(){
    int base; int count = 0;Poly_o allPoly[100];
    while (true){
        cout << "Enter the number of elements in polynominal#"<<count+1 <<" or enter -1 to stop: "; 
        cin >> base;
        if (base == -1){
            break;
        }
        allPoly[count].terms = base;
        input_arr(allPoly[count].arr,base,allPoly[count].max_deg);
        count ++;
    }
    Poly_o allPoly2[100]; int count2;

    // NORMAL ALL POLY
    /*Into_bin(allPoly,count);
    Out_bin(allPoly2,count2);
    display_poly(allPoly2,count2);
    /*cout << count << endl;
    display_poly(allPoly,count);*/

    // 2. MAX DEG POLY
    Into_bin_max_deg(allPoly,count);
    Out_bin_max_deg(allPoly2,count);
    display_poly(allPoly2,count);
}
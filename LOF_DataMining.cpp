#include<bits/stdc++.h>

#define ll long long
using namespace std;

//init array
double dist[1002][1002];
int sortID[1002][1002] = {0};;

//swap index
void swapIndex(int *a, int *b){  
    int temp = *a;  
    *a = *b;  
    *b = temp;
}

//swap value
void swapValue(double *a, double *b){  
    double temp = *a;  
    *a = *b;  
    *b = temp;
}  

//custom bubble sort
void customSort(double dist[], int sortID[], int n){  
    int i,j;  
    for (i=0;i<n-1;i++){
	    for (j=0;j<n-i-1;j++){
	    	if (dist[j] > dist[j+1]){
	    		swapIndex(&sortID[j], &sortID[j+1]);
	    		swapValue(&dist[j], &dist[j+1]);
			}
		}
	} 
} 

int main(){
	//main menu
	int menu;
	
	cout << "LOCAL OUTLIER FACTOR\n";
	cout << "=====================\n";
	
	cout << "1. Sample Data dan Peringkat\n";
	cout << "2. Custom Data dan Peringkat\n";
	cout << "Pilihan Menu : ";
	cin >> menu;
	
	//init data
	int n,k;
	double x[1002],y[1002];
	
	if(menu == 1){
		n = 10;
		k = 3;
		
		x[0] = 26; y[0] = 35;
		x[1] = 13; y[1] = 12;
		x[2] = 11; y[2] = 5;
		x[3] = 10; y[3] = 15;
		x[4] = 50; y[4] = 45;
		x[5] = 200; y[5] = 200;
		x[6] = 18; y[6] = 20;
		x[7] = 21; y[7] = 14;
		x[8] = 16; y[8] = 20;
		x[9] = 21; y[9] = 75;
	} else {
		cout << "\nBanyak Data = ";
		cin >> n;
		
		for(int i=0;i<n;i++){
			cout << "Data ke-" << i+1 << " : ";
			cin >> x[i] >> y[i];
		}
		
		cout << "Peringkat : ";
		cin >> k;
	}
	
	cout << "\n";
	//show data
	cout << "Data Input\n";
	cout << "id\tx[i]\ty[i]\n";
	for(int i=0;i<n;i++){
		cout << i+1 << "\t" << x[i] << "\t" << y[i] << "\n";
	}
	cout << "\nPeringkat (k) = " << k << "\n";
	
	cout << "\n";
	//step 1. proximity matrix
	cout << "\nStep 1. Proximity Matrix\n";
	for(int i=0;i<n;i++){
		for(int j=0;j<n;j++){
			dist[i][j] = sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2));
			sortID[i][j] = j;
			printf("%4.3f\t",dist[i][j]);
		}
		cout << "\n";
	}
	
	cout << "\n";
	//step 2. mengurutkan kedekatan dengan masing-masing data
	cout << "\nStep 2. Mengurutkan kedekatan dengan masing-masing data\n";
	for(int i=0;i<n;i++){
		customSort(dist[i],sortID[i],n);
		for(int j=1;j<n;j++){
			printf("%4.3f\t",dist[i][j]);
		}
		cout << "\n";
	}
	
	cout << "\nHasil Data berdasarkan Peringkat (k = " << k << ")\n";
	for(int i=0;i<n;i++){
		for(int j=1;j<=k;j++){
			printf("%4.3f\t",dist[i][j]);
			cout << "(" << sortID[i][j]+1 << ")\t";
		}
		cout << "\n";
	}
	
	cout << "\n";
	//step 3. menghitung average density sampai peringkat k (by default: k = 3)
	cout << "\nStep 3. Menghitung average density sampai peringkat " << k << "\n";
	
	double sumDist[1002]={0}, avgDensity[1002];
	
	for(int i=0;i<n;i++){
		for(int j=1;j<=k;j++){
			sumDist[i] += dist[i][j];
		}
		avgDensity[i] = k / sumDist[i];
		printf("%4.5f\n",avgDensity[i]);
	}
	
	cout << "\n";
	//step 4. menghitung average relative density
	cout << "\nStep 4. Menghitung average relative density\n";
	
	double sumRelative[1002]={0}, avgRelative[1002];
	
	cout << "id\tx[i]\ty[i]\tAvg Relative Density\n";
	for(int i=0;i<n;i++){
		for(int j=1;j<=k;j++){
			sumRelative[i] += avgDensity[sortID[i][j]];
		}
		avgRelative[i] = sumRelative[i] / k / avgDensity[i];
		cout << i+1 << "\t" << x[i] << "\t" << y[i] << "\t";
		printf("%4.9f\n",avgRelative[i]);
	}
	
	cout << "\n";
	//step 5. menentukan outlier berdasarkan threshold
	cout << "\nStep 5. Menentukan Outlier berdasarkan Threshold\n";
	
	double threshold;
	string res;
	
	cout << "Threshold : ";
	cin >> threshold;
	
	cout << "id\tx[i]\ty[i]\tAvg Relative Density\tOutlier\n";
	for(int i=0;i<n;i++){
		(avgRelative[i] >= threshold) ? res = "Yes" : res = "No";
		
		cout << i+1 << "\t" << x[i] << "\t" << y[i] << "\t";
		printf("%4.9f\t\t",avgRelative[i]);
		cout << res << "\n";
	}
	
	cout << "\n";
	
	cout << "Tekan ENTER untuk keluar\n";
	system("pause");
	
	return 0;
}


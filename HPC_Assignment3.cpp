#include <iostream>
#include <omp.h>
#include<chrono>

using namespace std;
using namespace std::chrono;

void sequentialMin(int arr[], int n) {
    int min_val = arr[0];
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    cout << "sequential Minimum Value: " << min_val << endl;
}
void parallelMin(int arr[], int n) {
    int min_val = arr[0];

    #pragma omp parallel for reduction(min:min_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] < min_val) {
            min_val = arr[i];
        }
    }

    cout << "Parallel Minimum Value: " << min_val << endl;
}

////////////////////////////////////////////////////////////////////////// 
void sequentialMax(int arr[], int n) {
    int max_val = arr[0];

    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    cout << "sequential Maximum Value: " << max_val << endl;
}
void parallelMax(int arr[], int n) {
    int max_val = arr[0];

    #pragma omp parallel for reduction(max:max_val)
    for (int i = 1; i < n; i++) {
        if (arr[i] > max_val) {
            max_val = arr[i];
        }
    }

    cout << "Parallel Maximum Value: " << max_val << endl;
}

////////////////////////////////////////////////////////////////////////////////
 void sequentialSum(int arr[], int n) {
    int sum = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    cout << "sequential Sum: " << sum << endl;
}
 void parallelSum(int arr[], int n) {
    int sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    cout << "Parallel Sum: " << sum << endl;
}

////////////////////////////////////////////////////////////////////////////////////////
void sequentialAverage(int arr[], int n) {
    double sum = 0;

    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    double average = sum / n;

    cout << "sequential Average: " << average << endl;
}
void parallelAverage(int arr[], int n) {
    double sum = 0;

    #pragma omp parallel for reduction(+:sum)
    for (int i = 0; i < n; i++) {
        sum += arr[i];
    }

    double average = sum / n;

    cout << "Parallel Average: " << average << endl;
}

int main() {
    const int n = 10; // Size of the array
    int arr[n] = { 12, 11, 13, 5, 6, 7, 4, 2, 9, 10 };

    //Sequential minimum
    auto smin_start=high_resolution_clock::now();
    sequentialMin(arr,n);
    auto smin_end=high_resolution_clock::now();

    auto smin_dur=duration_cast<microseconds>(smin_end-smin_start);
    cout<<"Sequential min calculation time is "<<smin_dur.count()<<" seconds"<<endl;

    // Parallel minimum
    auto pmin_start=high_resolution_clock::now();
    parallelMin(arr, n);
    auto pmin_end=high_resolution_clock::now();

    auto pmin_dur=duration_cast<microseconds>(pmin_end-pmin_start);
    cout<<"Parallel min calculation time is "<<pmin_dur.count()<<" seconds"<<endl;


    // Parallel maximum
    parallelMax(arr, n);

    // Parallel sum
    parallelSum(arr, n);

    // Parallel average
    parallelAverage(arr, n);

    return 0;
}

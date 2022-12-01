#include <iostream>
using namespace std;
void quickSort(int* a, int i, int j) //快速排序
{
    if (j <= i || j <= 0)
        return;
    int m = i, n = j, s = a[m];
    while (m < n)
    {
        while (m < n && a[n] >= s)
        {
            n--;
        }
        //从右向左找到比标准数小的数
        if (m < n)
        {
            a[m++] = a[n];
        }
        while (m < n && a[m] < s)
        {
            m++;
        }
        //从左向右找到比标准数大的数
        if (m < n)
        {
            a[n--] = a[m];
        }
    }
    a[m] = s;
    //经过这一轮的排序，m左侧都比它小，右侧都比它大
    quickSort(a, i, m - 1);
    quickSort(a, m + 1, j);
    //再从m左右两侧分别进行排序
}
void Classify(int* a, int n)
{
    if (n <= 1)
        return;
    int i = 0, j = n - 1;
    while (i < j)
    {
        while (a[j] % 2 == 0 && i < j)
            j--;
        while (a[i] % 2 && i < j)
            i++;
        if (i != j)
            swap(a[i], a[j]);
        i++;
        j--;
    }
}
int main()
{
    int n;
    cin >> n;
    int* a = new int[n];
    for (int i = 0; i < n; i++)
        cin >> a[i];
    for (int i = 0; i < n; i++)
    {
        if (a[i] < 0)
        {
            cout << "ERROR";
            return 0;
        }
    }
    Classify(a, n);//奇偶分离
    int f = 0;
    while (a[f] % 2 && f < n)
        f++;
    //最后一个奇数的位置为f-1
    quickSort(a, 0, f - 1);
    quickSort(a, f, n - 1);
    //奇偶数分别排序
    for (int i = 0; i < n; i++)
        cout << a[i] << ' ';
    delete[] a;
    return 0;
}
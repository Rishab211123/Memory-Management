#include <iostream>
using namespace std;

class FirstFit
{
private:
    int frag[10], block[10], file[10], no_blocks, no_files, temp;
    int firstFit[10],Fit[10];

public:
    void firstfit()
    {
        cout << "\nMemory Management Scheme - First Fit";
        cout << "\nEnter the number of blocks:";
        cin >> no_blocks;
        cout << "Enter the number of files:";
        cin >> no_files;
        cout << "\nEnter the size of the blocks:-\n";
        for (int i = 1; i <= no_blocks; i++)
        {
            cout << "Block " << i << ":";
            cin >> block[i];
        }
        cout << "Enter the size of the files :-\n";
        for (int i = 1; i <= no_files; i++)
        {
            cout << "File " << i << ":";
            cin >> file[i];
        }
        for (int i = 1; i <= no_files; i++)
        {
        temp = -1;
        for (int j = 1; j <= no_blocks; j++)
        {
                if (firstFit[j] != 1)
                {
                    if (block[j] >= file[i])
                    {
                        if (temp == -1)
                        {
                            temp = j;
                        }
                        else if (block[temp] > block[j])
                        {
                            temp = j;
                        }
                    }
                }
            }
            if (temp != -1)
            {
                Fit[i] = temp;
                frag[i] = block[temp] - file[i];
                firstFit[temp] = 1;
            }
        }
        cout << "\nFile no\tFile size \tBlock no:\tBlock size\tFragment\n";
        for (int i = 1; i <= no_files; i++)
        {
            cout << i << "\t\t" << file[i] << "\t\t" << Fit[i] << "\t\t" << block[Fit[i]] << "\t\t" << frag[i] << "\n";
        }
    }
};

class BestFit:public FirstFit
{
private:
    int frag[10], block[10], file[10], no_blocks,i,j, no_files, temp, lowest=1000;
    int bestFit[10], Fit[10];
public:
    void bestfit()
    {
    cout << "\nMemory Management Scheme - Best Fit";
    cout << "\nEnter the number of blocks:";
    cin >> no_blocks;
    cout << "Enter the number of files:";
    cin >> no_files;
    cout << "\nEnter the size of the blocks:-\n";
    for (int i = 1; i <= no_blocks; i++)
    {
        cout << "Block " << i << ":";
        cin >> block[i];
    }
    cout << "Enter the size of the files :-\n";
    for (int i = 1; i <= no_files; i++)
    {
        cout << "File " << i << ":";
        cin >> file[i];
    }
    for(i=1;i<=no_files;i++)
    {
        for(j=1;j<=no_blocks;j++)
        {
            if(bestFit[j]!=1)
            {
                temp=block[j]-file[i];
                if(temp>=0)
                    if(lowest>temp)
                    {
                        Fit[i]=j;
                        lowest=temp;
                    }
            }
        }
        frag[i]=lowest;
        bestFit[Fit[i]]=1;
        lowest=10000;
        }

        cout << "\nFile no:\tFile size \tBlock no \tBlock_size \tFragment\n";
        for (int i = 1; i <= no_files; i++)
        {
            cout << i << "\t\t" << file[i] << "\t\t" << Fit[i] << "\t\t" << block[Fit[i]] << "\t\t" << frag[i] << "\n";
        }
    }
};

class WorstFit: public FirstFit
{
private:
    int frag[10], block[10], file[10],no_blocks,i,j,no_files, temp, highest=1000;
    int worstFit[10], Fit[10];
public:
    void worstfit()
    {
    cout << "\nMemory Management Scheme - Worst Fit";
    cout << "\nEnter the number of blocks:";
    cin >> no_blocks;
    cout << "Enter the number of files:";
    cin >> no_files;
    cout << "\nEnter the size of the blocks:-\n";
    for (int i = 1; i <= no_blocks; i++)
    {
        cout << "Block " << i << ":";
        cin >> block[i];
    }
    cout << "Enter the size of the files :-\n";
    for (int i = 1; i <= no_files; i++)
    {
        cout << "File " << i << ":";
        cin >> file[i];
    }
    for(i=1;i<=no_files;i++)
    {
        for(j=1;j<=no_blocks;j++)
        {
            if(worstFit[j]!=1)
            {
                temp=block[j]-file[i];
                if(temp>=0)
                    if(highest<temp)
                    {
                        Fit[i]=j;
                        highest=temp;
                    }
            }
        }
        frag[i]=highest;
        worstFit[Fit[i]]=1;
        highest=0;
    }

        cout << "\nFile no \tFile size \tBlock no\tBlock size\tFragment\n";
        for (int i = 1; i <= no_files; i++)
        {
            cout << i << "\t\t" << file[i] << "\t\t" << Fit[i] << "\t\t" << block[Fit[i]] << "\t\t" << frag[i] << "\n";
        }
    }
};


int main()
{
    int choice;
    FirstFit obj1;
    BestFit obj2;
    WorstFit obj3;
    while (1)
        {
        cout << "\n\nMemory Management Algorithms";
        cout << "\n1.First Fit\n2.Best Fit\n3.Worst Fit\n4.Exit\nEnter your choice:";
        cin >> choice;
        switch (choice)
        {
            case 1:
                obj1.firstfit();
                break;
            case 2:
                obj2.bestfit();
                break;
            case 3:
                obj3.worstfit();
                break;
            case 4:
                break;
            default:
                cout << "\nEnter a valid choice!!";
                break;
        }
    }
   
}
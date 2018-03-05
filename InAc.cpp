#include<bits/stdc++.h>
#include <stdio.h>
#include <string.h>
#include <windows.h>
#include <iostream>
#include <shlobj.h>
#include<dos.h>
using namespace std;
int i=0;//To keep track of number of files
string type[100000];//To find file type in desktop
int r=0;//To keep track of number of types of files present in desktop
struct detail
{
    char FName[1024];
    ULONGLONG FSize;
}D[1000000];
bool acompare(detail lhs, detail rhs) { return lhs.FSize > rhs.FSize; }
void listDir(const char * dirn);
void sortDir();
void desktopSort();
int main()
{
    cout<<"All the files of the system (windows) are:\n";
    listDir("C:\\Users\\"); //function to recursively access all files of a system and display their name
    sortDir();//function to sort files according to size and find and display top 10 files according to size
    desktopSort();//To sort files of Desktop according to type
    return 0;
}

void listDir(const char * dirn)
{
    wchar_t documents[1024];
    string str2;
    SHGetFolderPathW(0, CSIDL_PERSONAL, 0, 0, documents);
    wstring ws(documents);
string str3(ws.begin(), ws.end());
    int k,flag=0;
    std::size_t found,fo;
    string demo;
    ULONGLONG FileSize;
    char dirnPath[1024];
    sprintf(dirnPath, "%s\\*", dirn); //Content of dirn (i.e. name of main root directory) is stored in dirnPath
    WIN32_FIND_DATA f;
    HANDLE h = FindFirstFile(dirnPath, &f); //Stores information about main directory in h

    if (h == INVALID_HANDLE_VALUE) { return; }


    do
    {
        const char * name = f.cFileName;

        if (strcmp(name, ".") == 0 || strcmp(name, "..") == 0) { continue; }

        char filePath[1024];
        sprintf(filePath, "%s%s%s", dirn,"\\", name);// Stores file name in filepath
        //Computing the Size of the File and Storing in FileSize
        FileSize=f.nFileSizeHigh;
        FileSize <<= sizeof( f.nFileSizeHigh ) * 8; // Push by count of bits
      FileSize |= f.nFileSizeLow;
      i++;
        for(k=0;filePath[k]!='\0';k++)
        {
            D[i].FName[k]=filePath[k];
        }
        D[i].FSize=FileSize;
        string str(filePath);
        found=str.find("Desktop");
        if(found!=std::string::npos )
        {
            for(k=0;k<r;k++)
            {
                if(type[k]==str.substr(str.find_last_of(".")+1))
                {

                    MoveFile(str.c_str(),(str3+"\\"+type[k]+str.substr(str.find_last_of("Desktop")+1)).c_str());
                    flag=1;
                    break;
                }
            }
                if(flag==0)
                {
                    if((str.substr(str.find_last_of(".")+1)).find("\\")==string::npos)
                    type[r++]=str.substr(str.find_last_of(".")+1);
                    str2=str3+"\\"+type[r];
                    CreateDirectory((str3+"\\"+type[r]).c_str(),NULL);
                    MoveFile(str.c_str(),(str3+"\\"+type[k]+str.substr(str.find_last_of("Desktop")+1)).c_str());
                }


        }
        flag=0;
        cout<<filePath<<endl;
        if (f.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY) // On finding a directory again calls the function
        {
            listDir(filePath);
        }

    } while (FindNextFile(h, &f));
    FindClose(h);
}

void sortDir()
{
    int j;
    cout<<"\n\n\nThe top ten largest files are:\n";
    sort(D,D+i,acompare);
    for(j=0;j<10;j++)
    {
        cout<<"Name: "<<D[j].FName<<"\n";
        cout<<"Size: "<<D[j].FSize<<"\n";
    }
}

void desktopSort()
{
     wchar_t documents[1024];
    string str2;
    SHGetFolderPathW(0, CSIDL_PERSONAL, 0, 0, documents);
    wstring ws(documents);
string str3(ws.begin(), ws.end());
    int j;
    cout<<"\n\n The types of file extensions present in Desktop are: \n";
    for(j=0;j<r;j++)
    {
        cout<<type[j]<<"\n";
        str2=str3+"\\"+type[j];
                    CreateDirectory((str3+"\\"+type[j]).c_str(),NULL);
    }
}

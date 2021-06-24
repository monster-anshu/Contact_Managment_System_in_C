// This code is Uploaded on github by Himanshu Gunwant
// Reach me at https://github.com/monster-anshu

#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <string.h>
#include <conio.h>

FILE *fp, *ft;
int ch;
struct contact
{
    char name[30], add[30], email[40], ph[15];
} list;

char real[] = "contact.dll", temp[] = "temp.dat";

void mainMenu()
{
    printf("\n\t\t\t**** Welcome to Contact Managment System ****\t\t\t");
    printf("\n\n");
    printf("\n\t\t\t\t\t Main Menu");
    printf("\n\t\t\t\t========================");
    printf("\n\t\t\t\t[1] Create A new contact");
    printf("\n\t\t\t\t[2] List all contact");
    printf("\n\t\t\t\t[3] Search a contact");
    printf("\n\t\t\t\t[4] Edit a contact");
    printf("\n\t\t\t\t[5] Delete a contact");
    printf("\n\t\t\t\t[0] Exit");
    printf("\n\t\t\t\t========================");
    printf("\n\t\t\t\tEnter Your choise : ");
}
void CreateNew()
{

    system("cls");
    fp = fopen(real, "a");
    while (1)
    {
        fflush(stdin);
        printf("\n\t To exit Enter black space in Name !!");
        printf("\nEnter name : ");
        gets(list.name);
        if (strcmp(list.name, "") == 0 || strcmp(list.name, " ") == 0)
            break;
        fflush(stdin);
        printf("Enter phone Number : ");
        gets(list.ph);
        printf("Enter address : ");
        gets(list.add);
        fflush(stdin);
        printf("Enter email : ");
        gets(list.email);
        fflush(stdin);
        fwrite(&list, sizeof(list), 1, fp);
    }
    fclose(fp);
}

void DisplayAll()
{
    int found = 0, numCon = 0;
    fflush(stdout);
    system("cls");
    printf("\n\n\t====================================\n\t\tLIST OF CONTACT\n\t====================================\n\n");
    for (int i = 97; i <= 122; i++)
    {
        fp = fopen(real, "r");
        fflush(stdin);
        found = 0;
        while (fread(&list, sizeof(list), 1, fp) == 1)
        {
            if (list.name[0] == i || list.name[0] == i - 32)
            {
                fflush(stdout);
                printf("\n\n Name : \t %s \n Phone :\t %s \n Address :\t %s \n Email :\t %s \n", list.name, list.ph, list.add, list.email);
                found++;
                numCon++;
            }
        }
        if (found != 0)
            printf("============================================================[%c] - (%d)\n\n", i, found);
        fclose(fp);
    }
    if (numCon == 0)
    {
        printf("\n--------------\n No Contact found \n--------------\n");
    }
}
void searchCon()
{
    char quary[20], name[20], found = 0;
    do
    {
        system("cls");
        found = 0;
        fflush(stdin);
        printf("\n\n\t..::CONTACT SEARCH \n\t=============================\n\t..::Name of contact to search :");
        gets(quary);
        int len = strlen(quary);
        fp = fopen(real, "r");
        while (fread(&list, sizeof(list), 1, fp) == 1)
        {
            strcpy(name, list.name);
            if (strcmp(name, quary) == 0)
            {
                printf("\n Name : \t%s \n Phone : \t%s \n Email : \t%s \n Address : \t%s \n\n", list.name, list.ph, list.email, list.add);
                found++;

                if (found % 4 == 0)
                {
                    printf("\n\t..:: Press any key to continue...");
                    getch();
                    system("cls");
                }
            }
        }

        if (found == 0)
        {
            printf("\n\t..:: Not contact found of : %s \n", quary);
        }
        else
        {
            printf("================================[%d] - Result Found", found);
        }
        printf("\n\t..::try again ? \n \t [1] Yes \t [2] No \n\t");
        scanf("%d", &ch);
    } while (ch == 1);
}

void editCon()
{
    system("cls");
    char name[20] = {'\0'};
    fp = fopen(real, "r");
    ft = fopen(temp, "w");
    printf("\n\t===================\n\t    Edit Contact \n\t===================\n");
    printf("\n ..::Enter Contact Name : ");
    fflush(stdin);
    gets(name);
    while (fread(&list, sizeof(list), 1, fp) == 1)
    {
        if (stricmp(list.name, name) != 0)
        {
            fwrite(&list, sizeof(list), 1, ft);
        }
    }
    fclose(fp);
    printf("..::Editing \n");
    fflush(stdin);
    printf(" >> Enter new name : \t");
    gets(list.name);
    fflush(stdin);
    printf(" >>Enter Phone : \t");
    gets(list.ph);
    fflush(stdin);
    printf(" >>Enter email : \t");
    gets(list.email);
    fflush(stdin);
    printf(" >>Enter address : \t");
    gets(list.add);
    printf("\n ..::Edited Successful !!");
    fwrite(&list, sizeof(list), 1, ft);
    fclose(ft);
    remove(real);
    rename(temp, real);
}

void deleteCon()
{
    char name[20] = {'\0'};
    system("cls");
    printf("\n\t===================\n\t   Delete Contact \n\t===================\n");
    printf(">> Enter contact name to delete : ");
    fflush(stdin);
    gets(name);
    fp = fopen(real, "r");
    ft = fopen(temp, "w");
    while (fread(&list, sizeof(list), 1, fp) == 1)
    {
        if (strcmp(list.name, name) != 0)
        {
            fwrite(&list, sizeof(list), 1, ft);
        }
    }
    fclose(ft);
    fclose(fp);
    remove(real);
    rename(temp, real);
    printf("\n>>>> Contact deleted !");
}
int main()
{
main:
    system("cls");
    mainMenu();
    scanf("%d", &ch);
    switch (ch)
    {
    case 1:
        CreateNew();
        break;
    case 2:
        DisplayAll();
        break;
    case 3:
        searchCon();
        break;
    case 4:
        editCon();
        break;
    case 5:
        deleteCon();
        break;
    default:
        printf("\n\t\t\t\tEnter Valid choise");
        break;
    }
    printf("\n\n\t[1] Main Menu \t\t [0] Exit \n");
    fflush(stdin);
    scanf("%d", &ch);
    switch (ch)
    {
    case 0:
        exit(1);
    case 1:
        goto main;
    default:
        system("cls");
        printf("Invalid code ");
        getch();
        goto main;
    }
    return 0;
}

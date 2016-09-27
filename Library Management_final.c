/*Library Management Program By Sounak-Suprotik-Roshan-Sohan*/
#include<stdio.h>
#include<string.h>
#include <Windows.h>
#define m 50


/*structures declared*/
typedef struct book
{
	long int BookNo;
	char BName[m];
	char BAuthor[m];
	float BPrice;
	char BLanguage[m];
	char BCategory[m];
	int BCount;
/*BCount stores the no. of copies of book available*/
}Book;

typedef struct date
{
	int Day;
	int Month;
	int Year;
}Date;

typedef struct borrow
{
	long int BookNo;
	Date IDate;
	Date RDate;
}Borrow;

typedef struct address
{
	char BldgNum[m], Street[m], City[m];
	long int PIN;
}Address;

typedef struct member
{
	int MID;
	char MName[m];
	Address MAddress;
	char MPhone[10];
	int MType,quota;
	float MFee;
	Borrow BorrowRec[6];
}Member;

/*Declaring functions*/
void enroll();/*enrollment of member*/
void storeInfo();/*storing detail of a new book*/
void issueBk();/*issuing of a book*/
void returnBk();/*returning of book*/
void dispDefaulter();/*displaying defaulters' list*/
void dispAvailable();/*displaying list of available books*/
void returnBk();/*returning of a book*/
void renewBk();/*renewing of a book*/
void memList();/*displaying enrolled list of members*/
void updateMem();/*update details of a member*/
void delBkCount();/*deleting a copy of a book when it is torn or deleted*/

Date AddDt(Date d);/*adding a week to current date or return date*/
int checkNull(Borrow b);/*checking whether borrow types in member are null*/
void nextLine(FILE *fp);/*going to next line*/
int dateCrossed(Date d);/*checking whether date for return has crossed*/
void refresh();/*refresh page*/

FILE *fm,*fb,*fi,*id;/*declaring file pointers*/
Date dt;
SYSTEMTIME str_t;/*declaring systemtime type variable for storing local time*/



void main()
{
     FILE *fpw;

     int opt,i,count,flag;
     char ch, pw[m],pw1[m];
     GetLocalTime(&str_t);
     dt.Day=str_t.wDay;
     dt.Month=str_t.wMonth;
     dt.Year=str_t.wYear;
     /*displaying start-up page*/
	 printf("Date: %d/%d/%d \t\t\t\t\t\t   Time: %2d:%2d \n",str_t.wDay,str_t.wMonth,str_t.wYear,str_t.wHour,str_t.wMinute);
     puts("###############################################################################");
  	 puts("                                    VER: 1.02                             ");
     puts("###############################################################################\n");
     printf("         **     ******  ***       **         *         **    **   **\n");
     printf("        **       **     ****     ****       **        ****    ** **\n");
     printf("       **       **     ** **    ** ***     * *       ** ***    ***\n");
     printf("      **       **     ****     *****      ****      *****      **\n");
     printf("     **       **     **       ***        *****     ***        **\n");
     printf("    **       **     ****     ****       **  **    ****       **\n");
     printf("   **       **     ** **    **  **     **   **   **  **     **\n");
     printf("  ******   **     ****     **    **   **    **  **   **    **\n");
     printf(" ****** ******  ****      **      ** **     ** **     **  ** MANAGEMENT SOFTWARE\n");
     puts("################################################################################");
     puts("                                                                by U. F.  TEAM  ");/*unfamous four ;)*/
     puts("################################################################################");
     printf("\nPress ENTER to continue...");
     getch();
     refresh();



/*checking for a librarian*/
     printf("\n\tAre you a LIBRARIAN?(y/n):");
     scanf("%c",&ch);
     if(ch=='y'||ch=='Y')
     { fpw=fopen("pwd.txt","rb+");
       if(fpw==NULL)
                 {
                     printf("Cannot open file!!");
                     exit(1);
                 }
       count=1;
       do
       {/*asking for password*/
            printf("\n\tEnter password:");
            i=0;
            while (1)
                {
                    if (i < 0)
                            i = 0;
                    ch = getch();
                    if (ch == 13)
                        break;
                    if (ch == 8)
                    {
                        putch('\b');/*entering backspace for a backspace input*/
                        putch(NULL);
                        putch('\b');/*entering backspace for a backspace input*/
                        i--;
                        continue;
                    }
                    pw[i++] = ch;
                    ch = '*';
                    putch(ch);
                }
        pw[i] = '\0';
        fread(pw1,sizeof(pw1),1,fpw);
        flag=strcmp(pw,pw1);
        if(flag!=0)
            {
                puts("\nWrong password!!");
                count++;
                if(count>=5)
                {
                    puts("\nYou have entered wrong password 5 times!!Press any key to end..");
                    getch();
                exit(0);/*exit if wrong password is entered 5 times*/
                }
            }
        }while(flag!=0);

        if(flag==0)
        {
             refresh();
             puts("\nDo you want to change password(y/n):");
             ch=getche();/*asking for change of password*/
             if(ch=='y'||ch=='Y')
                {
                    puts("\nEnter new password:");
                    fflush(stdin);
                    gets(pw);
                    rewind(fpw);
                    count= fwrite(pw,sizeof(pw),1,fpw);
                    if( count==1)
                        puts("\nNew password saved succesfully,press any key.");
                    else
                        puts("\nNew password was not saved succesfully,press any key.");
                    getch();
                }
            do
                {
                    refresh();
                    printf("\n\n<0> Exit\n<1> Enroll a member\n<2> Store book info\n<3> Issue a book\n<4> Return a book\n<5> Renew book");
                    printf("\n<6> Display available books\n<7> Display defaulters' list\n<8> Display Members' List\n<9> Update Member Details\n<10> Remove a book");
                    puts("\n################################################################################");
                    printf("\n\nEnter Choice:");
                    scanf("%d",&opt);/*asking for option. Selection of operation done by switch case*/
                    switch(opt)
                    {
                        case 0: break;
                        case 1: enroll();
                                break;
                        case 2: storeInfo();
                                break;
                        case 3: issueBk();
                                break;
                        case 4: returnBk();
                                break;
                        case 5: renewBk();
                                break;
                        case 6: dispAvailable();
                                break;
                        case 7: dispDefaulter();
                                break;
                        case 8: memList();
                                break;
                        case 9: updateMem();
                                break;
                        case 10:delBkCount();
                                break;
                        default: printf("\nInvalid Choice!!");
                    }
                }while(opt);
        }
        fclose(fpw);
     }
     else
     {
         puts("\nDo you want to see list of available books(y/n):");
         /*Allows a non-librarian to see list of books only*/
         ch=getch();
         if(ch=='y'||ch=='Y')
            dispAvailable();

         printf("\nPress any key to end program...");
         getch();
     }

}


void enroll()
{
     fm=fopen("Members.txt","a+");/*opening members.txt in read & modify mode*/
     id=fopen("Id.txt","r");
     int i,j;
     Member mem;
     /*asking for details of member*/
     printf("\nEnter <1> for Gold, <2> for Silver, <3> for Bronze membership:");
     scanf("%d",&mem.MType);
     printf("\nEnter name:");
     fflush(stdin);
     gets(mem.MName);
     printf("\nEnter address:");
     printf("\nEnter Building no.:");
     fflush(stdin);
     gets(mem.MAddress.BldgNum);
      printf("\nEnter Street:");
     fflush(stdin);
     gets(mem.MAddress.Street);
     printf("\nEnter City:");
     fflush(stdin);
     gets(mem.MAddress.City);
     printf("\nEnter PIN:");
     scanf("%ld",&mem.MAddress.PIN);
     j=0;
     do
     {    if(j)
     puts("\nPhone no. to be of ten digits!!");
        printf("\nEnter phone :");
        fflush(stdin);
        scanf("%s",mem.MPhone);
        j=1;
     }while(strlen(mem.MPhone)!=10);
     /*checking if phone no. is 10 digit*/
     fscanf(id,"%d",&mem.MID);
     fclose(id);
     mem.MID++;
     id=fopen("Id.txt","w");
     fprintf(id,"%d",mem.MID);
     mem.quota=(mem.MType==1)?(6):((mem.MType==2)? 4:2);
     /*checking using conditional operator to get MFee*/
     mem.MFee=(mem.MType==1)?(4000):((mem.MType==2)? 3000:2000);


     fprintf(fm,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum, mem.MAddress.Street, mem.MAddress.City, mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,mem.quota);

     for(i=0;i<6;i++)
     {
         fprintf(fm,"\t0\t0/0/0\t0/0/0");
         /*filling null values in BorrowRec*/
     }

     printf("\nPay Rs.%.2f. Press ENTER to continue...",mem.MFee);
     getch();
     printf("\n\nMember enrolled.\nPlease note down your Member ID:%d\nPress ENTER to continue...",mem.MID);

     fclose(fm);
     fclose(id);
     getch();
}
void storeInfo()
{
     fb=fopen("Books.txt","a+");
     Book bk;
     /*entering books details*/
     printf("\nEnter book info:");
     printf("\nEnter 6 digit book id:");
     scanf("%ld",&bk.BookNo);
     printf("\nEnter book name:");
     fflush(stdin);
     gets(bk.BName);
     printf("\nEnter author name:");
     fflush(stdin);
     gets(bk.BAuthor);
     printf("\nEnter price:");
     scanf("%f",&bk.BPrice);
     printf("\nEnter book language:");
     fflush(stdin);
     gets(bk.BLanguage);
     printf("\nEnter book category:");
     fflush(stdin);
     gets(bk.BCategory);
     printf("\nEnter no. of copies of book:");
     scanf("%d",&bk.BCount);/*writing in file*/
     fprintf(fb,"\n%ld\t%s\t%s\t%f\t%s\t%s\t%d",bk.BookNo,bk.BName,bk.BAuthor,bk.BPrice,bk.BLanguage,bk.BCategory,bk.BCount);
     printf("\nBook information stored. Press ENTER to continue...");
     fclose(fb);
     getch();
}

  void issueBk()
{
     FILE *fb2,*fm2;
     fb=fopen("Books.txt","r");
     fm=fopen("Members.txt","r");
     fb2=fopen("Books_temp.txt","w");
     fm2=fopen("Members_temp.txt","w");
     fi=fopen("Issue.txt","a");
     int memID,i;
     long int bkID;
     Book bk;
     Member mem;
     Date temp;

     printf("Enter member ID:");
     scanf("%d",&memID);
     printf("Enter book ID to be issued:");
     scanf("%ld",&bkID);
     while(1)
     {
           if(fscanf(fb,"\n%ld\t%[^\t]\t%[^\t]\t%f\t%[^\t]\t%[^\t]\t%d",&bk.BookNo,bk.BName,bk.BAuthor,&bk.BPrice,bk.BLanguage,bk.BCategory,&bk.BCount)==EOF || bk.BookNo==bkID)
                  break;
           fprintf(fb2,"\n%ld\t%s\t%s\t%f\t%s\t%s\t%d",bk.BookNo,bk.BName,bk.BAuthor,bk.BPrice,bk.BLanguage,bk.BCategory,bk.BCount);

     }/*moving to the desired tuple in Books*/

     while(1)
     {
           if(fscanf(fm,"\n%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%ld\t%[^\t]\t%d\t%f\t%d",&mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,&mem.MAddress.PIN,mem.MPhone,&mem.MType,&mem.MFee,&mem.quota)==EOF || mem.MID==memID)
                  break;

            fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,mem.quota);
            for(i=0;i<6;i++)
            {
                fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
                fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);

            }

     }/*moving to the desired tuple in Members*/

     if(bk.BCount!=0 && mem.quota!=0 && bk.BookNo==bkID && mem.MID==memID)
     {
    /*checks if member and books are valid*/
                     fprintf(fb2,"\n%ld\t%s\t%s\t%f\t%s\t%s\t%d",bk.BookNo,bk.BName,bk.BAuthor,bk.BPrice,bk.BLanguage,bk.BCategory,--bk.BCount);
                     fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum, mem.MAddress.Street, mem.MAddress.City, mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,--mem.quota);

                     for(i=0;i<6;i++)
                    {

                        fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
                        /*fills issue details in non-null position*/
                        if(checkNull(mem.BorrowRec[i])!=0)
                           fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);
                        else
                        {
                            fprintf(fm2,"\t%ld\t%d/%d/%d",bkID,dt.Day,dt.Month,dt.Year);
                            temp=AddDt(dt);
                            fprintf(fm2,"\t%d/%d/%d",temp.Day,temp.Month,temp.Year);
                            break;
                        }
                    }
                     printf("\nBook successfully issued!\nReturn date: %d/%d/%d",temp.Day,temp.Month,temp.Year);
     }
     else
         {
            printf("\nCould not issue book! Press ENTER to continue...");
            fclose(fb);
            fclose(fm);
            fclose(fb2);
            fclose(fm2);
            fclose(fi);
            remove("Members_temp.txt");
            remove("Books_temp.txt");
            getch();
            return;
        }

    i++;
    for(;i<6;i++)
            {
                fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
                fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);            }
    fprintf(fi,"\n%d\t%ld\t%d/%d/%d\t%d/%d/%d",memID,bkID,dt.Day,dt.Month,dt.Year,temp.Day,temp.Month,temp.Year);/*updating the issue file*/

    while(fscanf(fb,"\n%ld\t%[^\t]\t%[^\t]\t%f\t%[^\t]\t%[^\t]\t%d",&bk.BookNo,bk.BName,bk.BAuthor,&bk.BPrice,bk.BLanguage,bk.BCategory,&bk.BCount)!=EOF)
    {
       fprintf(fb2,"\n%ld\t%s\t%s\t%f\t%s\t%s\t%d",bk.BookNo,bk.BName,bk.BAuthor,bk.BPrice,bk.BLanguage,bk.BCategory,bk.BCount);
    }/*copying remaining tuples to temporary file for books*/

    while(fscanf(fm,"\n%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%ld\t%[^\t]\t%d\t%f\t%d",&mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,&mem.MAddress.PIN,mem.MPhone,&mem.MType,&mem.MFee,&mem.quota)!=EOF)
    {
        fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum, mem.MAddress.Street, mem.MAddress.City, mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,mem.quota);
        for(i=0;i<6;i++)
            {fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
            fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);
            }
    }/*copying remaining tuples to temporary file for members*/

     fclose(fb);
     fclose(fm);
     fclose(fb2);
     fclose(fm2);
     fclose(fi);
     remove("Members.txt");
     rename("Members_temp.txt","Members.txt");
     remove("Books.txt");
     rename("Books_temp.txt","Books.txt");
     printf("\nPress ENTER to continue...");
     getch();

 }


void dispDefaulter()
{
    fi=fopen("Issue.txt","r");
    fm=fopen("Members.txt","r");
    int memID;
    long int bkID;
    Date temp1,temp2;
    Member mem;
    printf("\n\n\t***DEAFULTERS' LIST***\n\nBOOKID\tMEMBER ID\tNAME\t\t\tRETURN DATE\n");
    while(fscanf(fi,"\n%d\t%ld\t%d/%d/%d\t%d/%d/%d",&memID,&bkID,&temp1.Day,&temp1.Month,&temp1.Year,&temp2.Day,&temp2.Month,&temp2.Year)!=EOF)
    {
        if(dateCrossed(temp2))/*checking whether date has been crossed*/
        {
            nextLine(fm);
            while(fscanf(fm,"%d\t%[^\t]",&mem.MID,mem.MName)!=EOF && memID!=mem.MID)
                    nextLine(fm);
            printf("\n%ld\t%d\t\t%s\t\t%d/%d/%d",bkID,memID,mem.MName,temp2.Day,temp2.Month,temp2.Year);

        }
    }
    fclose(fi);
    fclose(fm);
    printf("\n\nPress ENTER to continue...");
    getch();

}
/*[^\t] escape sequence used to scan spaces too; scans until \t is reached*/
void dispAvailable()
{
     fb=fopen("Books.txt","r");
     Book bk;
     printf("\n\nBOOK ID\t\tNAME\t\t\tAUTHOR\t\tNO. OF COPIES AVAILABLE\n\t\t\t\t");
     while(fscanf(fb,"\n%ld\t%[^\t]\t%[^\t]\t%f\t%[^\t]\t%[^\t]\t%d",&bk.BookNo,bk.BName,bk.BAuthor,&bk.BPrice,bk.BLanguage,bk.BCategory,&bk.BCount)!=EOF)
          {if(bk.BCount!=0)/*checking for no. of copies of book*/
               printf("\n%d\t\t%s\t\t\t%s\t\t%d",bk.BookNo,bk.BName,bk.BAuthor,bk.BCount);
          }
    printf("\n\nPress ENTER to continue...");
    fclose(fb);
    getch();
}


Date AddDt(Date d)
{
    Date temp;
    int days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
    /*initialisation of an array for storing the no. of days present in each month in a year*/
    temp=d;
    temp.Day+=7;
    if(temp.Day>days[temp.Month-1])
    {
        if(temp.Year%4!=0 || temp.Year%400==0 ||temp.Month!=2)
        /*if the year is a leap year and the month is February*/
        {
        temp.Day=temp.Day%days[temp.Month-1];
        temp.Month++;
        }
        else
        {
        temp.Day=temp.Day%days[29];
        temp.Month++;
        }
         if(temp.Month>12)
        {
        temp.Month=1;
        temp.Year++;
        }

    }
    return temp;
}
int checkNull(Borrow b)
{
    int flag=7;
    if(b.BookNo==0)
        flag--;
    if(b.IDate.Day==0)
        flag--;
    if(b.IDate.Month==0)
        flag--;
    if(b.IDate.Year==0)
        flag--;
    if(b.RDate.Day==0)
        flag--;
    if(b.RDate.Month==0)
        flag--;
    if(b.RDate.Year==0)
        flag--;
    return flag;
}
void nextLine(FILE *fp)
{

    char c;
    while((c=fgetc(fp))!='\n' && c!=EOF);
    /*shifts until newline is reached*/
}
int dateCrossed(Date d)
{
    if(d.Year>dt.Year)
        return 0;
    if(d.Year<dt.Year)
        return 1;
    if(d.Year=dt.Year)
        {
            if(d.Month>dt.Month)
                return 0;
            if(d.Month<dt.Month)
                return 1;
            if(d.Month=dt.Month)
                {
                    if(d.Day>=dt.Day)
                        return 0;
                    if(d.Day<dt.Day)
                        return 1;
                }
        }
}

void renewBk()
{
    FILE *fm2,*fi2;
     fm=fopen("Members.txt","r");
     fm2=fopen("Members_temp.txt","w");
     fi=fopen("Issue.txt","r");
     fi2=fopen("Issue_temp.txt","w");

     int memID,i;
     long int bkID, bkID2;
     Member mem;
     Date temp;

     printf("Enter member ID:");
     scanf("%d",&memID);
     printf("Enter book ID to be renewed:");
     scanf("%ld",&bkID);

     while(1)
     {
           if(fscanf(fm,"\n%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%ld\t%[^\t]\t%d\t%f\t%d",&mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,&mem.MAddress.PIN,mem.MPhone,&mem.MType,&mem.MFee,&mem.quota)==EOF || mem.MID==memID)
                  break;

            fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,mem.quota);
            for(i=0;i<6;i++)
            {
                fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
                fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);

            }

     }/*moving to the desired tuple*/
     if(mem.MID==memID)
     {

                     fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum, mem.MAddress.Street, mem.MAddress.City, mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,--mem.quota);

                     for(i=0;i<6;i++)
                    {/*copies the required tuple with change in issue date*/
                        fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
                        if(mem.BorrowRec[i].BookNo!=bkID)
                           {
                               fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);
                                 if(i==5)
                                {
                                    printf("\nInvalid Book ID! Press ENTER to continue...");
                                    fclose(fm);
                                    fclose(fm2);
                                    fclose(fi);
                                    fclose(fi2);
                                    remove("Members_temp.txt");
                                    remove("Issue_temp.txt");
                                    getch();
                                    return;
                                }
                            }
                        else
                        {
                            fprintf(fm2,"\t%ld\t%d/%d/%d",bkID,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year);
                            temp=AddDt(mem.BorrowRec[i].RDate);
                            /*new return date by adding date to issue date*/
                            if(dateCrossed(temp))
                                temp=AddDt(dt);
                            /*if return date is crossed, new return date becomes current date+7days*/
                            fprintf(fm2,"\t%d/%d/%d",temp.Day,temp.Month,temp.Year);
                            break;
                        }
                    }
                     printf("\nBook successfully renewed!\n Return date: %d/%d/%d",temp.Day,temp.Month,temp.Year);
     }
     else
         {
            printf("\nInvalid Member ID! Press ENTER to continue...");
            fclose(fm);
            fclose(fm2);
            fclose(fi);
            fclose(fi2);
            remove("Members_temp.txt");
            remove("Issue_temp.txt");
            getch();
            return;
        }

    i++;
    for(;i<6;i++)
            {
                fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
                fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);

            }/*copying the remaining issue details*/

    while(fscanf(fm,"\n%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%ld\t%[^\t]\t%d\t%f\t%d",&mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,&mem.MAddress.PIN,mem.MPhone,&mem.MType,&mem.MFee,&mem.quota)!=EOF)
    {
        fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum, mem.MAddress.Street, mem.MAddress.City, mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,mem.quota);
        for(i=0;i<6;i++)
        {
            fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
            fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);
        }
    }/*copying remaining tuples to temporary file for members*/

    while(1)
        {
             fscanf(fi,"\n%d\t%ld\t%d/%d/%d",&mem.MID,&bkID2,&temp.Day,&temp.Month,&temp.Year);
             fprintf(fi2,"\n%d\t%ld\t%d/%d/%d",mem.MID,bkID2,temp.Day,temp.Month,temp.Year);
             fscanf(fi,"\t%d/%d/%d",&temp.Day,&temp.Month,&temp.Year);
             if(mem.MID==memID && bkID2==bkID)
                    break;
             fprintf(fi2,"\t%d/%d/%d",temp.Day,temp.Month,temp.Year);
        }
     temp=AddDt(temp);
     fprintf(fi2,"\t%d/%d/%d",temp.Day,temp.Month,temp.Year);
     /*updating the issue file*/
     while(fscanf(fi,"\n%d\t%ld\t%d/%d/%d",&mem.MID,&bkID2,&temp.Day,&temp.Month,&temp.Year)!=EOF)
        {

             fprintf(fi2,"\n%d\t%ld\t%d/%d/%d",mem.MID,bkID2,temp.Day,temp.Month,temp.Year);
             fscanf(fi,"\t%d/%d/%d",&temp.Day,&temp.Month,&temp.Year);
             fprintf(fi2,"\t%d/%d/%d",temp.Day,temp.Month,temp.Year);
        }

     fclose(fm);
     fclose(fm2);
     fclose(fi);
     fclose(fi2);
     remove("Members.txt");
     rename("Members_temp.txt","Members.txt");
     remove("Issue.txt");
     rename("Issue_temp.txt","Issue.txt");
     printf("\nPress ENTER to continue...");
     getch();
}
void refresh()
 {
     GetLocalTime(&str_t);
     system("cls");/*clearing the screen*/
     printf("Date: %d/%d/%d \t\t\t\t\t\t   Time: %d:%d \n",str_t.wDay,str_t.wMonth,str_t.wYear,str_t.wHour,str_t.wMinute);
     puts("###############################################################################");


 }

 void memList()
{
     Member mem;
     fm=fopen("Members.txt","r");
     if(fm==NULL)
                 {printf("Cannot open file!!");
                       exit(1);
                 }
     printf("\nMID\tName        \tType    \tQuota");
     nextLine(fm);
     while(1)
     {
     if(fscanf(fm,"%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%ld\t%[^\t]\t%d\t%f\t%d",&mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,&mem.MAddress.PIN,mem.MPhone,&mem.MType,&mem.MFee,&mem.quota)!=EOF)
       {
/*printing the necessary member details*/
            printf("\n%d\t%s\t",mem.MID,mem.MName);
            (mem.MType==1)?(printf("\tGold")):((mem.MType==2)? (printf("\tSilver")):(printf("\tBronze")));
            printf("\t\t%d",mem.quota);
            nextLine(fm);
       }
     else
            break;
     }

     printf("\nPress ENTER to continue...");
     getch();
     fclose(fm);
}



void updateMem()
{
     FILE *fm2;
     fm=fopen("Members.txt","r");
     fm2=fopen("Members_temp.txt","w");
     int memID,i;
     char ch;
     Member mem;
     printf("Enter member ID:");
     scanf("%d",&memID);
     while(1)
     {
           if(fscanf(fm,"\n%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%ld\t%[^\t]\t%d\t%f\t%d",&mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,&mem.MAddress.PIN,mem.MPhone,&mem.MType,&mem.MFee,&mem.quota)==EOF  || mem.MID==memID)
                  break;
            fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,mem.quota);
            for(i=0;i<6;i++)
            {
                fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
                fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);

            }

     }/*moving to the desired tuple*/
     if(mem.MID==memID)
     {

            /*asks for change in every member detail. Updated if asked to*/
            printf("\nMember Name:%s. Do you want to update this? (y/n):",mem.MName);
            ch=getche();
            if(ch=='y'||ch=='Y')
            {
                printf("\nEnter new name:");
                fflush(stdin);gets(mem.MName);
            }
            printf("\nBuilding No.:%s. Do you want to update this? (y/n):",mem.MAddress.BldgNum);
            ch=getche();
            if(ch=='y'||ch=='Y')
            {
                printf("\nEnter new no:");
                fflush(stdin);gets(mem.MAddress.BldgNum);
            }
            printf("\nStreet:%s. Do you want to update this? (y/n):",mem.MAddress.Street);
            ch=getche();
            if(ch=='y'||ch=='Y')
            {
                printf("\nEnter new street:");
                fflush(stdin);
                gets(mem.MAddress.Street);
            }
            printf("\nCity.:%s. Do you want to update this? (y/n):",mem.MAddress.City);
            ch=getche();
            if(ch=='y'||ch=='Y')
            {
                printf("\nEnter new city:");
                fflush(stdin);
                gets(mem.MAddress.City);
            }
            printf("\nPIN:%ld. Do you want to update this? (y/n):",mem.MAddress.PIN);
            ch=getche();
            if(ch=='y'||ch=='Y')
            {
                printf("\nEnter PIN:");
                scanf("%ld",&mem.MAddress.PIN);
            }
            printf("\nPhone no:%s. Do you want to update this? (y/n):",mem.MPhone);
            ch=getche();
            if(ch=='y'||ch=='Y')
            {
                printf("\nEnter new phone no.:");
                fflush(stdin);
                gets(mem.MPhone);

            }
            printf("\nMembership type:");
            (mem.MType==1)?(printf("\tGold")):((mem.MType==2)? (printf("\tSilver")):(printf("\tBronze")));
            printf("\nDo you want to upgrade? (y/n):");
            ch=getche();
            if(ch=='y'||ch=='Y')
            {
                printf("\n\nEnter <1> for Gold, <2> for Silver:");
                scanf("%d",&i);
                /*membership type cannot be downgraded*/
                if(i>=mem.MType)
                    printf("\nYou cannot downgrade membership type!!");
                else
                {
                    mem.quota+=(mem.MType-i)*2;
                    mem.MFee+=(mem.MType-i)*1000;
                    /*calculating extra money to be paid*/
                    printf("\nPay Rs. %.2f extra. Press ENTER to continue...",(mem.MType-i)*1000.00);
                    mem.MType=i;

                }

            }
            /*printing modified details*/

            fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum, mem.MAddress.Street, mem.MAddress.City, mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,mem.quota);
            for(i=0;i<6;i++)
            {
                fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
                fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);
            }
            printf("\nMember details successfully updated!");
     }
     else
         {
            printf("\nMember not found!! Press ENTER to continue...");
            getch();
            fclose(fm);
            fclose(fm2);
            remove("Members_temp.txt");
            return;
        }
    while(fscanf(fm,"\n%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%ld\t%[^\t]\t%d\t%f\t%d",&mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,&mem.MAddress.PIN,mem.MPhone,&mem.MType,&mem.MFee,&mem.quota)!=EOF)
    {
        fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum, mem.MAddress.Street, mem.MAddress.City, mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,mem.quota);

        for(i=0;i<6;i++)
            {fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
            fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);
            }
    }/*copying remaining tuples to temporary file for members*/
     fclose(fm);
     fclose(fm2);
     remove("Members.txt");
     rename("Members_temp.txt","Members.txt");
     printf("Press ENTER to continue...");
     getch();
}

void returnBk()
{

     FILE *fb2,*fm2,*fi2;
     fb=fopen("Books.txt","r");
     fm=fopen("Members.txt","r");
     fb2=fopen("Books_temp.txt","w");
     fm2=fopen("Members_temp.txt","w");
     fi=fopen("Issue.txt","r");
     fi2=fopen("Issue_temp.txt","w");
     int memID,i,flag=0;;
     long int bkID,bkID2;
     Book bk;
     Member mem;
     Date temp1,temp2;

     printf("Enter member ID:");
     scanf("%d",&memID);
     printf("Enter book ID to be returned:");
     scanf("%ld",&bkID);
     while(1)
     {
           if(fscanf(fb,"\n%ld\t%[^\t]\t%[^\t]\t%f\t%[^\t]\t%[^\t]\t%d",&bk.BookNo,bk.BName,bk.BAuthor,&bk.BPrice,bk.BLanguage,bk.BCategory,&bk.BCount)==EOF || bk.BookNo==bkID)
                  break;
           fprintf(fb2,"\n%ld\t%s\t%s\t%f\t%s\t%s\t%d",bk.BookNo,bk.BName,bk.BAuthor,bk.BPrice,bk.BLanguage,bk.BCategory,bk.BCount);

     }/*moving to the desired tuple*/

     while(1)
     {
           if(fscanf(fm,"\n%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%ld\t%[^\t]\t%d\t%f\t%d",&mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,&mem.MAddress.PIN,mem.MPhone,&mem.MType,&mem.MFee,&mem.quota)==EOF || mem.MID==memID)
                  break;

            fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,mem.quota);
            for(i=0;i<6;i++)
            {
                fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
                fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);

            }

     }/*moving to the desired tuple*/
     if(bk.BookNo==bkID && mem.MID==memID)/*checks for valid IDs*/
     {

                     fprintf(fb2,"\n%ld\t%s\t%s\t%f\t%s\t%s\t%d",bk.BookNo,bk.BName,bk.BAuthor,bk.BPrice,bk.BLanguage,bk.BCategory,++bk.BCount);
                     fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum, mem.MAddress.Street, mem.MAddress.City, mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,++mem.quota);

                     for(i=0;i<6;i++)
                    {
                        fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
                        if(mem.BorrowRec[i].BookNo==bkID)
                            {fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",0,0,0,0,0,0,0);
                             flag=1;
                            }
                        else
                            fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);
                    }
                    if(flag==0)
                        {
                            printf("\nInvalid Book ID! Press ENTER to continue...");
                            fclose(fb);
                            fclose(fm);
                            fclose(fb2);
                            fclose(fm2);
                            fclose(fi);
                            fclose(fi2);
                            remove("Members_temp.txt");
                            remove("Books_temp.txt");
                            remove("Issue_temp.txt");
                            getch();
                            return;
                        }
                     printf("\nBook successfully returned!");
     }
     else
         {
            printf("\nCould not return book! Press ENTER to continue...");
            fclose(fb);
            fclose(fm);
            fclose(fb2);
            fclose(fm2);
            fclose(fi);
            fclose(fi2);
            remove("Members_temp.txt");
            remove("Books_temp.txt");
            remove("Issue_temp.txt");
            getch();
            return;
        }

    while(fscanf(fi,"\n%d\t%ld\t%d/%d/%d\t%d/%d/%d",&i,&bkID2,&temp1.Day,&temp1.Month,&temp1.Year,&temp2.Day,&temp2.Month,&temp2.Year)!=EOF)
    {
        if(memID!=i || bkID2!=bkID)
            fprintf(fi2,"\n%d\t%ld\t%d/%d/%d\t%d/%d/%d",i,bkID2,temp1.Day,temp1.Month,temp1.Year,temp2.Day,temp2.Month,temp2.Year);
    }
    /*updating the issue file*/

    while(fscanf(fb,"\n%ld\t%[^\t]\t%[^\t]\t%f\t%[^\t]\t%[^\t]\t%d",&bk.BookNo,bk.BName,bk.BAuthor,&bk.BPrice,bk.BLanguage,bk.BCategory,&bk.BCount)!=EOF)
    {
       fprintf(fb2,"\n%ld\t%s\t%s\t%f\t%s\t%s\t%d",bk.BookNo,bk.BName,bk.BAuthor,bk.BPrice,bk.BLanguage,bk.BCategory,bk.BCount);
    }/*copying remaining tuples to temporary file for books*/

    while(fscanf(fm,"\n%d\t%[^\t]\t%[^\t]\t%[^\t]\t%[^\t]\t%ld\t%[^\t]\t%d\t%f\t%d",&mem.MID,mem.MName,mem.MAddress.BldgNum,mem.MAddress.Street,mem.MAddress.City,&mem.MAddress.PIN,mem.MPhone,&mem.MType,&mem.MFee,&mem.quota)!=EOF)
    {
        fprintf(fm2,"\n%d\t%s\t%s\t%s\t%s\t%ld\t%s\t%d\t%f\t%d",mem.MID,mem.MName,mem.MAddress.BldgNum, mem.MAddress.Street, mem.MAddress.City, mem.MAddress.PIN,mem.MPhone,mem.MType,mem.MFee,mem.quota);
        for(i=0;i<6;i++)
            {fscanf(fm,"\t%ld\t%d/%d/%d\t%d/%d/%d",&mem.BorrowRec[i].BookNo,&mem.BorrowRec[i].IDate.Day,&mem.BorrowRec[i].IDate.Month,&mem.BorrowRec[i].IDate.Year,&mem.BorrowRec[i].RDate.Day,&mem.BorrowRec[i].RDate.Month,&mem.BorrowRec[i].RDate.Year);
            fprintf(fm2,"\t%ld\t%d/%d/%d\t%d/%d/%d",mem.BorrowRec[i].BookNo,mem.BorrowRec[i].IDate.Day,mem.BorrowRec[i].IDate.Month,mem.BorrowRec[i].IDate.Year,mem.BorrowRec[i].RDate.Day,mem.BorrowRec[i].RDate.Month,mem.BorrowRec[i].RDate.Year);
            }
    }/*copying remaining tuples to temporary file for members*/

     fclose(fb);
     fclose(fm);
     fclose(fi);
     fclose(fb2);
     fclose(fm2);
     fclose(fi2);
     remove("Members.txt");
     rename("Members_temp.txt","Members.txt");
     remove("Books.txt");
     remove("Issue.txt");
     rename("Issue_temp.txt","Issue.txt");
     rename("Books_temp.txt","Books.txt");
     printf("Press ENTER to continue...");
     getch();

}

void delBkCount()
{
     FILE *fb2,*fm2;
     long int bkID;
     Book bk;
     /*removing book for issuing in case of lost or torn book*/
     printf("\nEnter Book ID of lost or torn book:");
     scanf("%ld",&bkID);
     fb=fopen("Books.txt","r");
     fb2=fopen("Books_temp.txt","w");
     while(1)
     {
           if(fscanf(fb,"\n%ld\t%[^\t]\t%[^\t]\t%f\t%[^\t]\t%[^\t]\t%d",&bk.BookNo,bk.BName,bk.BAuthor,&bk.BPrice,bk.BLanguage,bk.BCategory,&bk.BCount)==EOF || bk.BookNo==bkID)
                  break;
           fprintf(fb2,"\n%ld\t%s\t%s\t%f\t%s\t%s\t%d",bk.BookNo,bk.BName,bk.BAuthor,bk.BPrice,bk.BLanguage,bk.BCategory,bk.BCount);

     }

     if(bk.BCount!=0)
     {
        /*moving to the desired tuple*/
        if(bk.BookNo==bkID)
            {

                     fprintf(fb2,"\n%ld\t%s\t%s\t%f\t%s\t%s\t%d",bk.BookNo,bk.BName,bk.BAuthor,bk.BPrice,bk.BLanguage,bk.BCategory,--bk.BCount);
                     printf("\nBook count successfully reduced!");
            }
        else
            {
            printf("\nID not found.Could not reduce book count! Press ENTER to continue...");
            getch();
            fclose(fb);
            fclose(fb2);
            remove("Books_temp.txt");
            return;
            }

        }
    else
    {
      printf("\nSome mistake might have occurred. No remaining book in record. Could not reduce book count! Press ENTER to continue...");
      getch();
      fclose(fb);
      fclose(fb2);
      remove("Books_temp.txt");
      return;

    }
    while(fscanf(fb,"\n%ld\t%[^\t]\t%[^\t]\t%f\t%[^\t]\t%[^\t]\t%d",&bk.BookNo,bk.BName,bk.BAuthor,&bk.BPrice,bk.BLanguage,bk.BCategory,&bk.BCount)!=EOF)
        {
            fprintf(fb2,"\n%ld\t%s\t%s\t%f\t%s\t%s\t%d",bk.BookNo,bk.BName,bk.BAuthor,bk.BPrice,bk.BLanguage,bk.BCategory,bk.BCount);
        }/*copying remaining tuples to temporary file for books*/
     fclose(fb);
     fclose(fb2);
     remove("Books.txt");
     rename("Books_temp.txt","Books.txt");
     printf("Press ENTER to continue...");
     getch();
}


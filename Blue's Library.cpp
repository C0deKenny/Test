#include <stdio.h>
#include <string.h>
#include <stdlib.h> 

//Declare new structure
typedef struct{
    char bookName[50];
    int bookQty;
    int bookPrice;
}
library; //New type name

//Prototypes declaration
void printHeading(int n);
void printList(library list[], int n, double code);
void printBottom(void);
int garageSale(library list[], int n);
void deleteIndex(library list[], int n, int deleted);

int main(void)
{
    //List deafult elements
    library list[10]; //New variable name list, type library
    strcpy(list[0].bookName, "Harry Potter");
    list[0].bookPrice = 100;
    list[0].bookQty = 15;
    strcpy(list[1].bookName, "Indiana Jones");  
    list[1].bookPrice = 200;
    list[1].bookQty = 20;    
    strcpy(list[2].bookName, "Hannibal");   
    list[2].bookPrice = 150;
    list[2].bookQty = 12;
    strcpy(list[3].bookName, "Hunger Games");
    list[3].bookPrice = 250;
    list[3].bookQty = 13;

    //Prerequisites initialization
    int count = 4; //Keeps count of list
    
    char ans[10]; //Placeholder for case 3 answer
    
    int n; //Determines loop

    int j = 3; //Prerequisite for case 1

    int total = 0; //Total profit for garage sales

    int index2, qty2; //Case 2 prerequisites

    int index4, qty4; //Case 4 prerequisites

    int deleted; //Case 5 prerequisites
    
    while(n != 6)
    {
        start: //Break for when list = 10 & delete book < 4 &
        printHeading(70);
        //void printList(library asal[], int n, double code);
        printList(list, count, 1);
        printBottom();
        scanf("%i", &n);

        switch(n)
        {
            case 1 : //Adds book to list
                if(j == 9) //indeks mulai dari 0, 9 = 10
                {
                    printf("You've reached maximum book amount!\n");
                    goto start;
                }
                j++;
                printf("\n\nTitle [must be filled] : ");
                scanf(" %[^\n]", list[j].bookName); 
                getchar();

                qty0:
                printf("\nQuantity [10..100] : ");
                scanf(" %i", &list[j].bookQty); 
                getchar();

                if(list[j].bookQty > 100 || list[j].bookQty < 10) //Validation
                {
                    printf("Please input the correct amount (10 - 100)\n");
                    goto qty0;
                }

                price0 ://Prompt user for correct price input
                printf("\nPrice [100..1000] : ");
                scanf(" %i", &list[j].bookPrice); 
                getchar();

                if(list[j].bookPrice > 1000 || list[j].bookPrice < 100) //Validation
                {
                    printf("Please input the correct price (100 - 1000)\n");
                    goto price0;
                }

                printf("Insert book success!\n");

                count++; //buku + 1 , count + 1
                getchar();
            break;

            case 2 : //Sell book
                printHeading(70);
                printList(list, count, 1);

                start2:
                printf("Selling book number.. [1..%i] : ", count);
                scanf("%i", &index2);

                if(list[index2-1].bookQty == 0 || index2 > count) //Validation
                {
                    printf("\n\nSorry! The book you are looking for isn't available!\n\n");
                    if(index2 > count) goto start2;
                    else goto start;
                }

                break2 : 
                printf("\n\nHow much [1..%i] : ", list[index2-1].bookQty);
                scanf("%i", &qty2);

                if(qty2 > list[index2-1].bookQty) //Checks if quantity isn't greater than the listed count
                {
                    printf("Please enter the correct amount (1 - %i)\n", list[index2-1].bookQty);
                    goto break2;
                }

                printf("\n\nSelling Success\n");
                printf("Selling %s : %i books\n", list[index2-1].bookName, qty2);
                printf("Total income : %i$\n", list[index2-1].bookPrice * qty2);
				
                list[index2-1].bookQty = list[index2-1].bookQty - qty2;
                getchar();
            break;

            case 3 : //Garage sale
                total = 0;
                printf("\nDiscount 50%% for all Books\n");
                printHeading(70);
                printList(list, count, 0.5);
                printf("Proceed Garage Sale? [yes/no]\n");
                scanf("%s", ans);
                getchar();
                for(int i = 0; i < count; i++)
                {
                    total = total + list[i].bookQty;
                }
                if(total == 0) //Validation
                {
                    printf("\n\nSorry! We are all out of stock!\n\n");
                    goto start;
                }
                if((strcmp(ans, "yes") == 0) || strcmp(ans,"y") == 0 || strcmp(ans, "YES") == 0)
                {
                    printf("\nGarage Sale Success\n");
                    printf("Total Income : %i$\n", garageSale(list, count));
                }
                getchar();
            break;

            case 4 : //Purchase book (to iventory)
                printf("\nPurchase price is 10%% lesser than selling price\n");
                printHeading(70);
                printList(list, count, 0.9);

                qty4:
                printf("Purchase book number [1..%i] :", count);
                scanf(" %i", &index4);
                if(index4 > count || index4 <= 0)
                {
                    printf("Please input the right number (1 - %i)\n", count);
                    goto qty4;
                }

                qty41: //Valiadtion for amount of books
                printf("\nHow much [1..20] : ");
                scanf(" %i", &qty4);
                if(qty4 > 20 || qty4 <= 0)
                {
                    printf("Please input the right amount of books (1 - 20)\n");
                    goto qty41;
                }

                list[index4-1].bookQty = list[index4-1].bookQty + qty4;
                printf("\nPurchase success!\n");
                printf("Purchase %s : %i books\n", list[index4-1].bookName, qty4);
                printf("Total purchase : %.0lf$\n", qty4 * (list[index4-1].bookPrice * 0.9));
                getchar();
            break;

            case 5 : //Delete book from list
                if(j < 4)
                {
                    printf("\n\nSorry! You dont have enough books to sell, yet! (%i)\n\n\n", j+1);
                    goto start;
                }
                printHeading(70);
                printList(list, count, 1);
                printf("Delete book number [1..%i] : ", count);
                scanf("%i", &deleted);
                //put delete function here
                deleteIndex(list, count, deleted);
                printf("\nDelete Book Succeed!\n\n\n");

                //reset count and j 
                count--;
                j--;
                getchar();
            break;

            case 6 :
            break;

            default :
                printf("\n\n\nPlease input the right option (1 - 6)\n\n\n");
            break;
        }
    }
    return 0;
}

//Prints heading
void printHeading(int n) // printHeading();
{
	printf ("                                 Blue's Library\n");
	printf ("\n");
	printf ("\n");
	printf ("\n");
    printf("No. Title\t\t\t\t   Quantity\t   Price\n");
    for(int i = 0; i < n; i++) 
    {
        printf("=");
    }
    printf("\n");
}

//Prints table
void printList(library list[], int n, double code)
{
    //DEFAULT CODE VALUE = 1
    for(int i = 0; i < n; i++)
    {
        printf("%-3i %-45s%-10i%4.0lf$\n", i+1, list[i].bookName, list[i].bookQty, (list[i].bookPrice * code));
    }
    for(int i = 0; i < 70; i++) 
    {
        printf("=");
    }
    printf("\n");
}

void printBottom(void)
{
    printf("NB: Max 10 Books Allowed\n");
    printf("\n");
    printf("1. Insert New Book\n");
    printf("2. Sell\n");
    printf("3. Garage Sell\n");
    printf("4. Purchase Book\n");
    printf("5. Delete Data\n");
    printf("6. Exit\n");
    printf("Choice : ");
}
//return namaFungsi(parameternya apa)

int garageSale(library list[], int n)
{
    int total = 0;
    for(int i = 0; i < n; i++)
    {
        total = total + ((list[i].bookPrice * 0.5) * list[i].bookQty);
        list[i].bookQty = 0;
    }
    return total;
}

void deleteIndex(library list[], int n, int deleted)
{
    //deleted = 1;
    int x = deleted-1; //ngakses index (0)
    printf("N: %i\n", n);
    for(int i = x; i < n; i++) // n = 5
    {
        strcpy(list[i].bookName, list[i+1].bookName);
        // x = 0                        1
        // x = 1                        2   
        // x = 2                        3 
        // x = 3                        4
        // x = 4                        5
        list[i].bookPrice = list[i+1].bookPrice;
        list[i].bookQty = list[i+1].bookQty;
    }
}  

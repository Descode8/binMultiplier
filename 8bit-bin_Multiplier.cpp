/*****************************************************************************************************************************
Jaden D. Humphries(jdhumph)                                                                                                  *
CPSC 2310 Section 1                                                                                                          *
Programming Assignment 2 - Hardware Multiplication Algorithm                                                                 *
Due: June 11, 2023                                                                                                           *
Purpose: This program is designed to perform multiplication on two 8-bit binary numbers and simulate the steps that the CPU  *
uses to perform binary multiplication.                                                                                       *
******************************************************************************************************************************/
#include <iostream>
/***********
Prototypes *
************/
bool check_Val(int);
bool check_Range(int);
void init_Check(int, int);
void prt_Bin(int, int);
void shift_Bits(int&, int&, int&);
void border();
void divider();
int add(int);
int bin_Add(int, int, int&);
void check_Section(int, int);
void step(int, int, int, int);
void hardware_Mult_Table(int, int, int, int);
/************************************************************************************************************************
This function will prompt the user for the input of the multiplicand and multiplier and verify if the inputs are valid. *
If the inputs are valid, the program will continue to process the multiplication steps. If not, an error message will   *
output to the console and suggest to restart the program; then the program will safely and successful end.              *
*************************************************************************************************************************/
int main(){
  puts("\n****************** BINARY MULTIPLIER ******************");
  int c = 0, acc = 00000000, mdr, mq;
  // prompt user for input
  printf("multiplicand: ");
  scanf("%d", &mdr);
  printf("multiplier: ");
  scanf("%d", &mq);
  // verify valid inputs
  init_Check(mdr, mq);
  // call hardware_multi to print each step of binary multiplication
  hardware_Mult_Table(c, acc, mdr, mq);
  return 0;
}
/*********************************************************************************
This function will check if the decimal value is 0-255; an 8-bit representation  *
**********************************************************************************/
bool check_Val(int val){
    return (val <= 255 && val > 0) ? true : false;
}
/***********************************************************************************************************
This function will check if the value of of mdr and mq are in range of 8-bit binary representation, 0-255  *
************************************************************************************************************/
bool check_Range(int val){
    return check_Val(val) ? true : false;
}
/*********************************************************************************************************************
This function will check the user input values and determine if the program should continue or to terminate program  *
**********************************************************************************************************************/
void init_Check(int mdr, int mq){
    if(!check_Range(mdr) && !check_Range(mq)){
        puts("Multiplicand and Multiplier are not in range of 0 - 255 for an 8-bit binary number. Please restart program.");
        exit(EXIT_FAILURE);
    }
    else if(!check_Range(mdr)){
        puts("Multiplicand is not in range of 0 - 255 for an 8-bit binary number. Please restart program.");
        exit(EXIT_FAILURE);
    }
    else if(!check_Range(mq)){
        puts("Multiplier is not in range of 0 - 255 for an 8-bit binary number. Please restart program.");
        exit(EXIT_FAILURE);
    }
}
/*************************************************************************************************************
This function will take in a decimal value and print it's binary equivalence representation with characters. *
**************************************************************************************************************/
void prt_Bin(int value, int length){
    int i;
    for(i = (length - 1); i >= 0; i--){
        if((value >> i) & 1){
            putchar('1');
        }else{
            putchar('0');
        }
    }
  printf(" ");
}
/******************************************************************************************
This function will shift c, acc and mq and will update the values in the calling function *
*******************************************************************************************/
void shift_Bits(int& c, int& acc, int& mq){
    if((acc & 1) == 1){
        mq >>= 1;
        mq += 128;
    }else{
        mq >>= 1;
    }
    acc >>= 1;
    c = 0;
}
/**************************************************************
This function will print the divider that separates each step *
***************************************************************/
void border(){
    for(int i = 0; i < 50; i++){
        putchar('-');
        if(i == 49){
            putchar('\n');
        }
    }
}
/*******************************************************************************************
This function will print the divider that is used as the bottom separator for the addition *
********************************************************************************************/
void divider(){
    printf("\n\t ");
    for(int i = 0; i < 10; i++){
        putchar('-');
        if(i == 9){
            putchar('\n');
        }
    }
}
/**************************************************************
This function will determine if addition is needed for a step *
***************************************************************/
int add(int mq){
    return (mq % 2 == 1) ? 1 : 0;
}
/******************************************************************************************************************************
This function will add acc and mdr and returns the sum. It also sets c equal to 0 or 1 depending on the values of acc and mdr *
*******************************************************************************************************************************/
int bin_Add(int acc, int mdr, int& c){
    int sum = acc + mdr;
    c = (sum > 255) ? 1 : 0;
    return sum;
}
/*************************************************************************************************************************
This function will print a check section that shows a summary of the multiplication in binary as well as decimal and end *
the program                                                                                                              *
**************************************************************************************************************************/
void check_Section(int mdr, int mq){
    int product = mdr * mq;
    border();
    printf("check:\t\t      binary\tdecimal\n\t\t    ");
    prt_Bin(mdr, 8);
    printf("     %5d\n\t  x\t    ", mdr);
    prt_Bin(mq, 8);
    printf(" x   %5d\n\t   ", mq);
    printf(" ----------------     ------\n\t    ");
    prt_Bin(product, 16);
    printf("\t  %5d\n", product);
    // safely end program
    exit(0);
}
/***************************************************************************************************************************
This function will print each step of the multiplication process and call other 'helper'functions to make the calculations *
****************************************************************************************************************************/
void step(int c, int acc, int mdr, int mq){
    // use temp to hold the starting value of mq; mq will be passed by reference to update its value during function calls
    int temp = mq;
    for(int i = 1; i <= 8; i++){
        // print line border
        border();
        printf("step %d:\t ", i);
        // print c acc mq before addition
        printf("%d ", c);
        prt_Bin(acc, 8);
        prt_Bin(mq, 8);
        // print second line with addition info '+' mdr       ^ add based on lsb=1
        if(add(mq)){
            printf("\n\t+  ");
            prt_Bin(mdr, 8); // since add(mq), mdr value is printed
            printf("\t   ^ add based on lsb=%d", add(mq));
            acc = bin_Add(acc, mdr, c);
        }else{ // !add(mq), 00000000 is printed indicating 'no addition'
            printf("\n\t+  00000000\t   ^ no add based on lsb=%d", add(mq));
        }
        // print divider
        puts("");
        divider();
        // print c acc and mq after addition
        printf("\t %d ", c);
        prt_Bin(acc, 8);
        prt_Bin(mq, 8);
        // print shift step labels
        printf("\n       >>\t\t     shift right\n");
        // print shifted values
        shift_Bits(c, acc, mq);
        printf("\t %d ",c);
        prt_Bin(acc, 8);
        prt_Bin(mq, 8);
        puts("");
    }
    // all 8 multiplication steps are now complete; call check_Section to print the summary
    check_Section(mdr, temp);
}
/****************************************************************************************************************************
This function prints the initial information of the multiplication table(before step 1:); shows the values of each variable *
*****************************************************************************************************************************/
void hardware_Mult_Table(int c, int acc, int mdr, int mq){
    puts("\nc and acc set to 0");
    // display mq
    printf("mq set to multiplier\t= %d decimal and ", mq);
    prt_Bin(mq, 8);
    puts(" binary");
    // display mdr
    printf("mdr set to multiplicand\t= %d decimal and ", mdr);
    prt_Bin(mdr, 8);
    puts(" binary");
    // call step to perform each multiplication step in the process
    step(c, acc, mdr, mq);
}

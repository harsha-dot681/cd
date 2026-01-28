%{
 #include<stdio.h>
 int flag=1;
%}

%%

[0-9]+  printf("number");

%%

int yywrap()
{
   if(flag==1){
   printf("you are taking input for the second time from the console");
   clearerr(stdin); //to clear the EOF which is in the console and start again 
   yyin=stdin;
   flag=0;
   return 0;
   }
   else
    return 1;
}

int main()
{
   yyin = stdin;
   yylex();
   return 1;
}

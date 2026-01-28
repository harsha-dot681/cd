%{
 #include<stdio.h>
 char *file1;
 int flag=0;
%}

%%

[0-9]+  printf("number");

%%

int yywrap()
{
  if(flag==0){
  	yyin=stdin;
  	flag=1;
  	return 0;
   }
   else
    return 1;
}

int main()
{
 file1="input_file.l";
   yyin = fopen("input_file.l","r");
   yylex();
   return 1;
}

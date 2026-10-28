%{
    #include <stdio.h>
    #include <stdlib.h>
    int i, j;
%}

%%
[0-9]*\.[0-9]+
    {
        for (i = 0; i < 10; i++)
        {
            if (yytext[i] == '.')
            {
                for (j = 0; j <= i - 1; j++)
                {
                    printf("%c", yytext[j]);
                }
            }
        }
        exit(0);
    }
%%

int main()
{
    yylex();
    return 0;
}

int yywrap()
{
    return 1;
}

Compilation:lex realtoint.l
            cc lex.yy.c -ll
            ./a.out 
            24.12 
            12

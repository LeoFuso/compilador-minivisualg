#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "compiler.h"
#include "stack.h"

int
main(int argc, char *argv[])
{
    /*
     *  Tenta ler o arquivo
     */
    if (argc != 2)
    {
        printf ("Syntax: main [file] (.visualg is implicit) \n");
        printf ("No specified to_parse file ending ... \n");
        exit (0);
    }

    compile(argv[1]);


    return 0;

}
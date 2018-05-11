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

   /*
    struct Node* root = NULL;

    push(&root, "oi");
    push(&root, "nessa");
    push(&root, "ordem");

    printf("%s popped from stack\n", pop(&root));
    printf("%s popped from stack\n", pop(&root));
    printf("%s popped from stack\n", pop(&root));
    printf("%s popped from stack\n", pop(&root));
    push(&root, "oi");

    printf("Top element is %s\n", peek(root));
*/
    return 0;

}
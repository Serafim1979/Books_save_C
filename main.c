#include <stdio.h>
#include <stdlib.h>
#define MAXTITL  40
#define MAXAUTL  40
#define MAXBKS   10
////////////////////////////////////////
struct book{
    char title[MAXTITL];
    char author[MAXAUTL];
    float value;
};
////////////////////////////////////////
int main()
{
    struct book library[MAXBKS];
    int count = 0;
    int index, filecount;
    FILE * pbooks;
    int size = sizeof(struct book);

    if((pbooks = fopen("book.dat", "a+b")) == NULL)
    {
        fputs("Cannot open file book.dat\n", stderr);
        exit(1);
    }
    rewind(pbooks);

    while(count < MAXBKS && fread(&library[count], size, 1, pbooks) == 1)
    {
        if(count == 0)
            puts("Current file contents book.dat: ");
        printf("%s by %s: $%.2f\n", library[count].title, library[count].author, library[count].value );
        count++;
    }
    filecount = count;

    if(count == MAXBKS)
    {
        fputs("File book.dat is full.", stderr);
        exit(2);
    }

    puts("Enter the names of the new books.");
    puts("Press [ enter] at the beginning of the line to exit the program.");

    while(count < MAXBKS && gets(library[count].title) != NULL && library[count].title[0] != '\0')
    {
        puts("Now enter the name of the author.");
        gets(library[count].author);
        puts("Now enter the price of the book.");
        scanf("%f", &library[count++].value);
        while(getchar() != '\n')
            continue;
        if(count < MAXBKS)
            puts("Enter the title of the next book.");
    }
    if(count > 0)
    {
        puts("Catalogue your books: ");
        for(index = 0; index < count; index++)
            printf("%s by %s: $%.2f\n", library[index].title, library[index].author, library[index].value);
        fwrite(&library[filecount], size, count - filecount, pbooks);
    }
    else
        puts("No books at all ? Very badly.\n");
    puts("All the best.");
    fclose(pbooks);
    return 0;
}

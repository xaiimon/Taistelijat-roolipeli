//Fighters roleplaying game by Samu Nyman:
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
// struct which has all the elements of one character
typedef struct fighter{
    char name[1000];
    int HP;
    char gun[1000];
    int gun_damage;
    int XP;
}gamer;
int add_player(int arraysize, struct fighter *w, char *sentence, struct fighter **c) // add character
{
    // w = array of players
    // **c = pointer to the array of players
    // u indicates if the player is on the database
    *c = realloc(w, (arraysize+1)*sizeof(gamer));
    w = *c;
    int scanffsize = 0;
    int u = 0;
    char character;
    int hp = 0;
    char gun[1000];
    int gun_damage;
    char name[1000];
    scanffsize = sscanf(sentence, "%c %s %d %s %d", &character, name, &hp, gun, &gun_damage);
    // checks if the character is already in the database
    for(int k = 0; k < arraysize; k++)
    {
        if(strcmp(name, w[k].name) == 0){
            u = -1;
        }
    }
    // adds the fighter if the conditions in below are fine
    if((scanffsize == 5) && (hp > 0) && (u != -1) && (gun_damage>0))
    {
        memset(&w[arraysize], 0, sizeof(gamer)); // allocates the memory
        strcpy(w[arraysize].name, name);
        w[arraysize].HP = hp;
        strcpy(w[arraysize].gun, gun);
        w[arraysize].gun_damage = gun_damage;
        w[arraysize].XP = 0;
        printf("SUCCESS\n");
        return 1;
        
    }
    else if ((arraysize != 5) && ((name[1]== '\0') || (name[2] == '\0')))
    {
        printf("A should be followed by exactly 4 arguments.\n");
        return 0;
        
    }
    else if ((gun[1] == '\0') || (gun[2] == '\0'))
    {
        printf("Weapon name cannot be empty or space.\n");
        return 0;
       
    }
    else if (gun_damage < 1)
    {
        printf("Max damage cannot be lower than 1\n");
        return 0;
    }
    else if(hp < 1 )
    {
        printf("HP cannot be lower than 1\n");
        return 0;
    }
    else if (u == -1)
    {
        printf("Fighter \"%s\" is already in the database.\n", name);
        return 0;
    }
    else if(name == '\0')
    {
        printf("A should be followed by exactly 4 arguments.\n");
        return 0;
    }
    else
    {
        return 0;
    }
}
int fight(char *sentence, struct fighter *w, int arraysize) // Fight 
{
    // w = array of players
    // g and u are just reference to if the player is not in the database. I didn't want to change those, because I can't think of any.
    char character;
    char attacker[1000];
    char target[1000];
    int sscanfsize = 0;
    sscanfsize = sscanf(sentence, "%c %s %s", &character, attacker, target);    
    int attacker_position;
    int target_position;
    char asd[1000];
    int k = 0;
    char dd[1000];
    int u = 0;
    int g = 0;
    // finds the attacker in the database and it's index
    while(k < arraysize)
    {
        memset(dd, 0, sizeof(dd));
        strcpy(dd, w[k].name);
        if (strcmp(attacker, dd) == 0) // checks if attacker is not in the database
        {
            attacker_position = k;
            g = 0;
            break;
        }
        else
        {
            g = -1;
        }
        k++;
    }
    // finds the target in the database
    for(int x = 0; x < arraysize; x++)
    {
        memset(asd, 0, sizeof(asd));
        strcpy(asd, w[x].name);
        if(strcmp(target, asd) == 0) // checks if target is not in the database
        {
            target_position = x;
            u = 0;
            break;
        }
        else 
        {
            u = -1;
        }
    }
    // if the below conditions are fine, it calculates the new hp of the target and adds the amount of hp lost from the target to the attacker xp.
    if((sscanfsize==3) && (u != -1) && (g != -1) && (w[attacker_position].name != w[target_position].name) && (w[attacker_position].HP > 0) && (w[target_position].HP > 0) && (w[target_position].name != NULL) && (w[attacker_position].name != NULL))
    {
        w[target_position].HP = w[target_position].HP - w[attacker_position].gun_damage;
        w[attacker_position].XP = w[attacker_position].XP + w[attacker_position].gun_damage;
        printf("%s attacked %s with %s by %i damage.\n%s has %i hit points remaining.\n%s gained %i experience points. \n", attacker, target, w[attacker_position].gun, w[attacker_position].gun_damage, target, w[target_position].HP, attacker, w[attacker_position].gun_damage);
        printf(" SUCCESS");
    }
    else if(sscanfsize != 3)
    {
      printf("H should be followed by exactly 2 arguments.");
    }
    else if(attacker_position == target_position)
    {
        printf("Attacker \"%s\" cannot attack to itself.", w[attacker_position].name);
    }
    else if(g == -1)
    {
        printf("Attacker \"%s\" is not in the database.", attacker);
    }
    else if(u== -1)
    {
        printf("Target \"%s\" is not in the database.", target);
    }
    else{
        return 0;
    }
    return 1;
}
int cmpfunc(const void *a, const void *b) //compares the xp with each of the characters with the qsort()- function.
{ 
    gamer *oa = (gamer *)a;
    gamer *ob = (gamer *)b;

    return (ob->XP - oa->XP); 
}

int print_players(struct fighter *w, int arraysize) //prints fighters.
{
    //w = array of players
    struct fighter *a;
    a = malloc(arraysize*sizeof(struct fighter));
    memcpy(a, w, (arraysize)*sizeof(gamer));
    qsort(a, arraysize, sizeof(gamer), cmpfunc); // sorts the array a
    int j = 0;
    for (int l = 0; ((l<arraysize) && (w[l].HP != 0)); l++) // prints fighters that are not dead
    {
        printf("%s %d %d %s %d\n", a[l].name, a[l].HP, a[l].XP, a[l].gun, a[l].gun_damage);
        j++;
    }
    for (int k = 0; arraysize-j-k != 0; k++) // prints fighters that are dead
    {
        printf("%s %d %d %s %d\n", a[j+k].name, a[j+k].HP, a[j+k].XP, a[j+k].gun, a[j+k].gun_damage);
    }
    free(a);
    return 1;
}

int write_players(struct fighter *w, int arraysize, char *sentence)//Writes to a file.
{
    // w is the array of players and a is a sorted version of it.
    struct fighter *a;
    a = malloc(arraysize*sizeof(struct fighter));
    memcpy(a, w, (arraysize)*sizeof(gamer));
    qsort(a, arraysize, sizeof(gamer), cmpfunc);
    char file_name[1000];
    char character;
    sscanf(sentence, "%c %s", &character, file_name);    
    FILE *fp;
    fp = fopen(file_name, "w");
    // checks if fp returns NULL pointer
    if(fp == NULL)
    {
        fprintf(stderr, "Opening file failed. Nothing writed to the file.\n");
        return 0;
    }
    else
    {
        // prints to the file.
        for(int i = 0; i < arraysize; i++){
            fprintf(fp, "%s %d %d %s %d\n", a[i].name, a[i].HP, a[i].XP, a[i].gun, a[i].gun_damage);
        }
        printf("SUCCESS\n");
    }
    fclose(fp);
    free(a);
    return 1;
}
/*int O(struct taistelija *w, struct taistelija **c)//overwrites the data, I didn't impelement the function, but I leaved it here if I want to impelement it in the future.
{
    FILE *fp;
    fp = fopen("tiedosto", "r");
    if (fp == NULL)
    {
        printf("\nError opening the file");
        exit(1);
    }
    int k= 0;
    struct taistelija *o;
    struct taistelija *f;
    f = *o;
    char n[strlen("\n")];
    while (fread(&f, sizeof(gamer), 1, fp) == 1)
    {
        *c = realloc(w, (k+1)*sizeof(gamer));
        strcpy(w[k].nimi, o->nimi);
        strcpy(w[k].ase, o->ase);
        w[k].HP = o->HP;
        w[k].asevahinko = o->asevahinko;
        w[k].XP = o->XP;
        k++;
        fread(n, sizeof(char[strlen("\n")]), 1, fp);
        
    }
    fclose(fp);
    
}*/
int quit(struct fighter *a) // frees the memory and quits the program
{
    free(a);
    printf("SUCCESS\n");
    return 1;
}
int main()
{
    int arraysize1 = 0;
    struct fighter *array;
    array = calloc(1, sizeof(gamer));
    char sentence1[1000];
    char character = 0;
    int sccanfvalue = 0;
    // checks the character input
    while (character != 'Q')
    {
        fgets(sentence1, sizeof(sentence1), stdin); 
        sccanfvalue = sscanf(sentence1, "%c", &character);
        if(character == 'A')
        {
            if(add_player(arraysize1, array, sentence1, &array))
            {
                arraysize1++;
            }
        }
        else if (character == 'H')
        {
            fight(sentence1, array, arraysize1);
            printf("\n");
        }
        else if (character == 'L')
        {
            print_players(array, arraysize1);
            printf("SUCCESS\n");
        }
        else if(character == 'W')
        {
            write_players(array, arraysize1, sentence1);
        }
        else if(character == 'Q')
        {
            continue;
        }
        else 
        {
            // if end of the file is present, this ends the program
            if (sccanfvalue == EOF)
            {
                printf("End of the file. Program ends.");
                break;
            }
            else
            {
            printf("Invalid command %c \n", character);
            }
        }
        
    }
    // final free and print before the main function ends
    quit(array);
    return 1;
}

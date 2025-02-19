#include "main.h"

const char *type[] = { "Small", "Large"};

int add_flavour(char *str, flavours *f, float small, float large)
{
    flavour *tmp = (flavour *)malloc(sizeof(flavour));
    tmp->key = f->size + 1;
    tmp->name = (char *)malloc((strlen(str) + 1));
    
    memcpy(tmp->name, str, strlen(str) + 1);

    //initialize type
    tmp->prices[0] = small;
    tmp->prices[1] = large;

    if (f->capacity <= f->size){
        f->capacity *= 2;
        f->container = (flavour **)realloc(f->container, f->capacity * sizeof(flavour *));
        if (f->container == NULL)
            return (-1);
    }
    f->container[f->size] = tmp;

    f->size++;
    
    return (0);
}

flavours *init_flavours(size_t s){
    flavours *f= (flavours *)malloc(sizeof(flavours));
    f->container = (flavour **)malloc(sizeof(flavour) * s);
    f->size = 0;
    f->capacity = s;
    return (f);
}

char *get_flavours(char *buf, flavours *f){
    int len = 0, index = 1;
    char *ptr = buf;
    while(index <= f->size){
        len = sprintf(ptr, "%d - %s\n", index, f->container[index- 1]->name);
        ptr += len;
        index++;
    }
    return (buf);    
}

void delete_flavours(flavours *f){
    int index = 0;
    while (index < f->size)
    {
        /* code */
        free(f->container[index]->name);
        free(f->container[index]);
        index++;
    }
    free((f->container));
    free(f);
}


void delete_flavour(flavours *f, char *name){
    int n = 0, index = 0, key = 0;
    while (index < f->size)
    {
        n = strcasecmp(f->container[index]->name, name);
        if (n == 0){
            key = index;
            break;
        }
        index++;
    }
    while (index < (f->size - 1)){
        f->container[index] = f->container[index + 1];
        index += 1;
    }

    if (key){
        free(f->container[--(f->size)]); //free last element and decrease size
    }
}
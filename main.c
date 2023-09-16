#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void destroy(char **words)
{
    if (words==NULL) return;
    if (*words==NULL)
    {
        free(words);
        words=NULL;
        return;
    }
    int i =0;
    while (*(words+i)!=NULL)
    {
        free(*(words+i));
        i++;
    }
    free(words);
    words=NULL;
}

int create_leading_word_cross(const char *first, const char *second, char ***result)
{
    if (first==NULL || second==NULL || result==NULL)
    {
        if (result!=NULL) *result=NULL;
        return -1;
    }
    int c=0;
    while (*(first+c)!='\0')
    {
        if (isupper(*(first+c))==0 || isalpha(*(first+c))==0)
        {
            *result=NULL;
            return -1;
        }
        c++;
    }
    c=0;
    while (*(second+c)!='\0')
    {
        if (isupper(*(second+c))==0 || isalpha(*(second+c))==0)
        {
            *result=NULL;
            return -1;
        }
        c++;
    }

    int posSt=0, posNd=0, flag=0;
    while (*(second+posNd)!='\0')
    {
        posSt=0;
        while (*(first+posSt)!='\0')
        {
            if (*(first+posSt)==*(second+posNd))
            {
                flag=1;
                break;
            }
            posSt++;
        }
        if (flag==1) break;
        posNd++;
    }
    if (flag==0)
    {
        *result=NULL;
        return -2;
    }
    int height = strlen(first), width = posNd+2;

    *result = (char**) calloc(height+1, sizeof(char*));
    if (*result==NULL)
    {
        *result=NULL;
        return -3;
    }

    for (int i = 0; i < height; ++i)
    {
        if (i==posSt)
        {
            *(*result+i) = (char*)calloc(strlen(second)+1, sizeof(char));
        }
        else
        {
            *(*result+i) = (char*)calloc(width, sizeof(char));
        }
        if (*(*result+i)==NULL)
        {
            for (int j = 0; j < i; j++)
            {
                free(*(*result+j));
            }
            free(*result);
            *result=NULL;
            return -3;
        }

    }
    int stIt = 0, ndIt = 0;
    int i=0, j=0;
    while (i!=height)
    {
        j=0;
        while (j!=width)
        {
            if (i==posSt)
            {
                for (int k = 0; k < (int)strlen(second); ++k)
                {
                    *(*(*result + i) + k) = *(second + ndIt);
                    ndIt++;
                }
                j = strlen(second);
                stIt++;
                break;
            }
            else if (j==posNd)
            {
                *(*(*result + i) + j) = *(first + stIt);
                stIt++;
                j++;
                break;
            }
            else
            {
                *(*(*result + i) + j) = ' ';
            }
            j++;
        }
        *(*(*result + i) + j)='\0';
        i++;
    }

    *(*result+height)=NULL;
    return posSt;
}
int create_double_leading_word_cross(const char *first, const char *second, const char *third, const char *fourth, char ***result, char ***first_cross, char ***second_cross)
{
    if (first==NULL || second==NULL || third==NULL || fourth==NULL || result==NULL) return 1;
    int check = create_leading_word_cross(second, first, first_cross);
    int check1 = create_leading_word_cross(fourth, third, second_cross);
    if (check==-3 || check1==-3)
    {
        if (check1==-3) destroy(*first_cross);
        else if (check==-3) destroy(*second_cross);
        *result=NULL;
        return 3;
    }
    else if (check==-2 || check1==-2)
    {
        if (check1==-2) destroy(*first_cross);
        else if (check==-2) destroy(*second_cross);
        *result=NULL;
        return 2;
    }
    else if (check==-1 || check1==-1)
    {
        if (check1==-1) destroy(*first_cross);
        else if (check==-1) destroy(*second_cross);
        *result=NULL;
        return 1;
    }


    int height, h1=0, h2=0;
    while (*(*first_cross+h1)!=NULL) h1++;
    while (*(*second_cross+h2)!=NULL) h2++;
    int i1=0, j1=0, i2=0, j2=0, j1R=0, j2R=0;

    while (*(*(*first_cross+i1)+j1)!='\0')//znalezienie skrzyzowania first_cross
    {
        if (strlen(first)==1 || strlen(second)==1)
        {
            j1=0;
            i1=0;
            break;
        }
        j1R=0;
        while (isalpha(*(*(*first_cross+i1)+j1R))==0)
        {
            j1R++;
        }
        if (*(*(*first_cross+i1)+j1R+1)==' ' || *(*(*first_cross+i1)+j1R+1)=='\0')
        {
            i1++;
        }
        else break;
        j1=j1R;
    }
    j1R=0;
    if (j1==0 && i1==0 && strlen(first)!=1 && strlen(second)!=1)
    {
        while (isalpha(*(*(*first_cross+1)+j1R))==0)
        {
            j1R++;
        }
        j1=j1R;
    }
    if (strlen(first)==1)
    {
        while (i1!=h1-1)
        {
            if (*(second+i1)==*(first)) break;
            i1++;
        }
    }
    while (*(*(*second_cross+i2)+j2R)!='\0')//znalezienie skrzyzowania second_cross
    {
        if (strlen(third)==1 || strlen(fourth)==1)
        {
            j2=0;
            i2=0;
            break;
        }
        j2R=0;
        while (isalpha(*(*(*second_cross+i2)+j2R))==0)
        {
            j2R++;
        }
        if (*(*(*second_cross+i2)+j2R+1)==' ' || *(*(*second_cross+i2)+j2R+1)=='\0')
        {
            i2++;
        }
        else break;
        j2=j2R;
    }
    if (j2==0 && i2==0 && strlen(third)!=1 && strlen(fourth)!=1)
    {
        while (isalpha(*(*(*second_cross+1)+j2R))==0)
        {
            j2R++;
        }
        j2=j2R;
    }
    if (strlen(third)==1)
    {
        while (i2!=h1-1)
        {
            if (*(fourth+i2)==*(third)) break;
            i2++;
        }
    }


    int dom;
    if (i1!=0 && i2==0) dom=1;
    else if (i1==0 && i2!=0) dom=2;
    else if (i2>i1) dom=2;
    else if (i1>i2) dom=1;
    else dom = 1;
    //i1-wiersz krzyża 1. | i2-wiersz krzyża 2.
    if (i1==0 && i2==0 || i1==i2)
    {
        if (h1>h2) height=h1;
        else height=h2;
    }
    else if ((i1==h1-1)&&(i2==0) || i1==0&&(i2==h2-1))
    {
        height=h1+h2-1;
    }
    else
    {
        if (h1-i1>h2-i2 && i1!=0 && i1>i2)
        {
            height=h1;
        }
        else if (h2-i2>h1-i1 && i2!=0 && i2>i1)
        {
            height=h2;
        }
        else if (dom==1)
        {
            height=h1+h2-1-(h1-i1-1)-i2;
        }
        else
        {
            height=h1+h2-1-(h2-i2-1)-i1;
        }
    }
    *result=(char**)calloc(height+1, sizeof(char*));
    if (*result==NULL)
    {
        destroy(*first_cross);
        destroy(*second_cross);
        return 3;
    }
    int i=0, j=0;

    int longest = strlen(first)+ strlen(third)+4;
    int mid = strlen(first)+4+(j2+1);
    int mini = j1+2;

    while (i!=height)
    {
        if (dom==1)
        {
            if (i==i1)
            {
                *(*result+i)=(char*) calloc(longest, sizeof(char));
                if (*(*result+i)==NULL)
                {
                    for (int k = 0; k < i; ++k) {
                        free(*(*result+k));
                    }
                    free(*result);
                    destroy(*first_cross);
                    destroy(*second_cross);
                    *result=NULL;
                    return 3;
                }
                i++;
            }
            else if (i<i1-i2 || i>=(h2+i1) || i>i1+(h2-i2-1))
            {
                *(*result+i)=(char*) calloc(mini, sizeof(char));
                if (*(*result+i)==NULL)
                {
                    for (int k = 0; k < i; ++k) {
                        free(*(*result+k));
                    }
                    free(*result);
                    destroy(*first_cross);
                    destroy(*second_cross);
                    *result=NULL;
                    return 3;
                }
                i++;
            }
            else
            {
                *(*result+i)=(char*) calloc(mid, sizeof(char));
                if (*(*result+i)==NULL)
                {
                    for (int k = 0; k < i; ++k) {
                        free(*(*result+k));
                    }
                    free(*result);
                    destroy(*first_cross);
                    destroy(*second_cross);
                    *result=NULL;
                    return 3;
                }
                i++;
            }
        }
        else
        {
            if (i==i2)
            {
                *(*result+i)=(char*) calloc(longest, sizeof(char));
                if (*(*result+i)==NULL)
                {
                    for (int k = 0; k < i; ++k) {
                        free(*(*result+k));
                    }
                    free(*result);
                    destroy(*first_cross);
                    destroy(*second_cross);
                    *result=NULL;
                    return 3;
                }
                i++;
            }
            else if ((h1-i1)<=(h2-i2) || (i1==0 && i<i2) || (h2-i)>0)
            {
                *(*result+i)=(char*) calloc(mid, sizeof(char));
                if (*(*result+i)==NULL)
                {
                    for (int k = 0; k < i; ++k)
                    {
                        free(*(*result+k));
                    }
                    free(*result);
                    destroy(*first_cross);
                    destroy(*second_cross);
                    *result=NULL;
                    return 3;
                }
                i++;
            }
            else
            {
                *(*result+i)=(char*) calloc(mini, sizeof(char));
                if (*(*result+i)==NULL)
                {
                    for (int k = 0; k < i; ++k) {
                        free(*(*result+k));
                    }
                    free(*result);
                    destroy(*first_cross);
                    destroy(*second_cross);
                    *result=NULL;
                    return 3;
                }
                i++;
            }
        }
    }
    i = 0;
    int w2 = 0, w4 = 0;

    while (i!=height)
    {
        j=0;
        while (1)
        {
            if (dom==1)
            {
                if (i==i1)//max
                {
                    for (int k = 0; k < (int) strlen(first); ++k)
                    {
                        *(*(*result+i)+k)= *(first+k);
                        j++;
                    }
                    int c = j;
                    for (int k = j; k < 3+c; ++k)
                    {
                        *(*(*result+i)+k)=' ';
                        j++;
                    }
                    c=0;
                    for (int k = j; k < (int) strlen(third)+j; ++k)
                    {
                        *(*(*result+i)+k)= *(third+c);
                        c++;
                    }
                    *(*(*result+i)+longest-1)='\0';
                    w2++;
                    w4++;
                    break;
                }
                else if (i<i1 && i<(i1-i2) || *(second+w2)!='\0' && *(fourth+w4)=='\0')//min
                {
                    for (int k = 0; k < mini-2; ++k)
                    {
                        *(*(*result+i)+k)=' ';
                        j++;
                    }
                    *(*(*result+i)+j)= *(second+w2);
                    w2++;
                    *(*(*result+i)+mini-1)='\0';
                    break;
                }
                else if(*(second+w2)=='\0' && *(fourth+w4)!='\0')
                {
                    for (int k = 0; k < mid-2; ++k)
                    {
                        *(*(*result+i)+k)=' ';
                        j++;
                    }
                    *(*(*result+i)+j)= *(fourth+w4);
                    w4++;
                    *(*(*result+i)+mid-1)='\0';
                    break;
                }
                else
                {
                    for (int k = 0; k < mini-2; ++k)
                    {
                        *(*(*result+i)+k)=' ';
                        j++;
                    }
                    *(*(*result+i)+j)= *(second+w2);
                    j++;
                    w2++;
                    for (int k = j; k < mid-2; ++k)
                    {
                        *(*(*result+i)+k)=' ';
                        j++;
                    }
                    *(*(*result+i)+j)= *(fourth+w4);
                    w4++;
                    *(*(*result+i)+mid-1)='\0';
                    break;
                }
            }
            else
            {
                if (i==i2)//max
                {
                    for (int k = 0; k < (int) strlen(first); ++k)
                    {
                        *(*(*result+i)+k)= *(first+k);
                        j++;
                    }
                    int c = j;
                    for (int k = j; k < 3+c; ++k)
                    {
                        *(*(*result+i)+k)=' ';
                        j++;
                    }
                    c=0;
                    for (int k = j; k < (int) strlen(third)+j; ++k)
                    {
                        *(*(*result+i)+k)= *(third+c);
                        c++;
                    }
                    w2++;
                    w4++;
                    *(*(*result+i)+longest-1)='\0';
                    break;
                }
                else if ((h1-i1)<=(h2-i2) || (i1==0 &&i<i2) || (h2-i)>0)
                {
                    if ((i1+i)<i2 || *(second+w2)=='\0' && *(fourth+w4)!='\0')
                    {
                        for (int k = 0; k < mid-2; ++k)
                        {
                            *(*(*result+i)+k)=' ';
                            j++;
                        }
                        if (w4==i2) w4++;
                        *(*(*result+i)+j)= *(fourth+w4);
                        w4++;
                        *(*(*result+i)+mid-1)='\0';
                        break;
                    }
                    else
                    {
                        for (int k = 0; k < mini-2; ++k)
                        {
                            *(*(*result+i)+k)=' ';
                            j++;
                        }
                        if (w2==i1) w2++;
                        *(*(*result+i)+j)= *(second+w2);
                        j++;
                        w2++;
                        for (int k = j; k < mid-2; ++k)
                        {
                            *(*(*result+i)+k)=' ';
                            j++;
                        }
                        if (w4==i2) w4++;
                        *(*(*result+i)+j)= *(fourth+w4);
                        w4++;
                        *(*(*result+i)+mid-1)='\0';
                        break;
                    }
                }
                else
                {
                    for (int k = 0; k < mini-2; ++k)
                    {
                        *(*(*result+i)+k)=' ';
                        j++;
                    }
                    if (w2==i1) w2++;
                    *(*(*result+i)+j)= *(second+w2);
                    w2++;
                    *(*(*result+i)+mini-1)='\0';
                    break;
                }
            }
        }
        i++;
    }
    *(*result+i)=NULL;
    return 0;
}

int main()
{
    char **output, **output_first, **output_second;
    char *name1 = malloc(11* sizeof(char));
    if (name1==NULL)
    {
        printf("Failed to allocate memory");
        return 8;
    }
    char *name2 = malloc(11* sizeof(char));
    if (name2==NULL)
    {
        free(name1);
        printf("Failed to allocate memory");
        return 8;
    }
    char *name3 = malloc(11* sizeof(char));
    if (name3==NULL)
    {
        free(name1);
        free(name2);
        printf("Failed to allocate memory");
        return 8;
    }
    char *name4 = malloc(11* sizeof(char));
    if (name4==NULL)
    {
        free(name1);
        free(name2);
        free(name3);
        printf("Failed to allocate memory");
        return 8;
    }
    printf("Podaj slowa: ");
    scanf("%10s %10s %10s %10s", name1, name2, name3, name4);
    int it=0, up=0;
    while (*(name1+it)!='\0')
    {
        if (isupper(*(name1+it))==0 || isalpha(*(name1+it))==0)
        {
            up=1;
            break;
        }
        it++;
    }
    while (*(name2+it)!='\0')
    {
        if (isupper(*(name2+it))==0 || isalpha(*(name2+it))==0)
        {
            up=1;
            break;
        }
        it++;
    }
    while (*(name3+it)!='\0')
    {
        if (isupper(*(name3+it))==0 || isalpha(*(name3+it))==0)
        {
            up=1;
            break;
        }
        it++;
    }
    while (*(name4+it)!='\0')
    {
        if (isupper(*(name4+it))==0 || isalpha(*(name4+it))==0)
        {
            up=1;
            break;
        }
        it++;
    }
    if (up==1)
    {
        free(name1);
        free(name2);
        free(name3);
        free(name4);
        printf("Incorrect input");
        return 1;
    }

    int check = create_double_leading_word_cross(name1, name2, name3, name4, &output, &output_first, &output_second);
    if (check==1)
    {
        free(name1);
        free(name2);
        free(name3);
        free(name4);
        printf("Incorrect input");
        return 1;
    }
    else if (check==2)
    {
        free(name1);
        free(name2);
        free(name3);
        free(name4);
        printf("Unable to make two crosses");
        return 0;
    }
    else if (check==3)
    {
        free(name1);
        free(name2);
        free(name3);
        free(name4);
        printf("Failed to allocate memory");
        return 8;
    }

    for (int i = 0; *(output_first+i) ; i++)
    {
        printf("%s\n", *(output_first+i));
    }
    printf("\n");
    for (int i = 0; *(output_second+i) ; i++)
    {
        printf("%s\n", *(output_second+i));
    }
    printf("\n");
    for (int i = 0; *(output+i) ; i++)
    {
        printf("%s\n", *(output + i));
    }
    free(name1);
    free(name2);
    free(name3);
    free(name4);
    destroy(output);
    destroy(output_first);
    destroy(output_second);
    return 0;
}
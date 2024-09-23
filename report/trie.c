#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 26

typedef struct TrieNode
{
    struct TrieNode *child[MAX];
    int end;
}TN;
TN* Getnode()
{
    TN *node = (struct TrieNode *)malloc(sizeof(struct TrieNode));

    node->end= 0;
    for(int i = 0; i < MAX; i++)
    {
        node->child[i] = NULL;
    }
    return node;
}
void recommend_check()
{
    char * best[100];

}
void Insert(TN ** root, const char * word)   //노드를 삽입하는 함수.
{
    TN * curr = (*root);
    int index =0;
    while (word[index])  //단어의 첫번째 문자~마지막문자까지 반복문을 돌린다.
    {
        int idx = word[index] -'a';   //단어의 첫번째 문자 - a하면 알파벳상의 그 문자의 index가 나온다.   예)  c-a -> 2
        if (curr ->child[idx] ==NULL)   //문자가 들어갈 공간이 비어있다면 채워준다.
        {
            curr->child[idx] = Getnode(); //이 때 위에 선언한 Get_node()가 나온다.
        }                                  //배열에 알파벳 인덱스에 해당하는 자리에 노드 생성.
        curr = curr ->child[idx];  //그 다음 문자를 삽입하기 위해 자식노드로 넘어간다. 
        index = index +1;
    }
    curr->end =1;    //while문이 끝났다는건 단어삽입이 끝났다는 것이니까 마지막문자라고 표기해주기위해 word_end 값을 1로 표기해준다.
}
int alph_start(TN * root, char alphabet) 
{
    TN *curr = root->child[alphabet - 'a']; // 해당 알파벳의 자식 노드로 이동

    // 만약 해당 알파벳으로 시작하는 노드가 없으면 0 반환
    if (curr == NULL) 
        return 0;

    // num 변수는 단어의 개수를 저장
    int num = 0;

    // 현재 노드가 단어의 끝이면 개수를 1 증가
    if (curr->end == 1) 
        num++;

    // 모든 자식 노드를 재귀적으로 탐색 (DFS)
    for (int i = 0; i < 26; i++) {
        if (curr->child[i] != NULL) {
            num += alph_start(curr, 'a' + i); // 재귀적으로 자식 노드 탐색
        }
    }
    return num;
}
int Search(TN * root, char *word)
{
    char select;
    if(root == NULL)
    {
        return 0;
    }
    TN * curr = root;
    int i = 0;
    while(word[i])
    {
        int idx = word[i] - 'a';
        if(curr->child[idx] == NULL) // 찾는 문자가 없음. 0 반환
        {
            printf("단어 '%s' 가 저장되지 않음 , 저장[Y/N]\n", word);
            scanf(" %c",&select);
            if(select == 'y' || select == 'Y') //단어가 저장되어 있지 않다면 저장할지 물어봄
            {
                Insert(&root,word);
                printf("단어 '%s' 저장 완료\n",word);
            }
            return 0;
        }
        curr = curr->child[idx]; // 있음. 다음 문자로 넘어감.
        i++;
    }
    if(curr->end) // 단어의 끝인지 확인
    {
        printf("단어 '%s' 가 저장되어 있음\n", word);
        return 1; // 단어가 존재함
    }
    printf("단어 '%s' 가 저장되지 않음 , 저장[Y/N]\n", word);
    scanf(" %c",&select);
    if(select == 'y' || select == 'Y') //단어가 저장되어 있지 않다면 저장할지 물어봄
    {
        Insert(&root,word);
        printf("단어 '%s' 저장 완료\n",word);
    }
    return 0; // 단어의 끝이 아니므로 저장되지 않음
}
int no_child(TN * curr)
{
    for(int i = 0; i < MAX; i++)
    {
        if(curr->child[i])
        {
            return 0; //자식있음 0반환
        }
    }
    return 1;   //자식없음 1반환
}
TN* Delete(TN ** curr, char * word)
{
    // 1. 현재 노드가 NULL인 경우
    if ((*curr) == NULL)
    {
        return NULL; // 단어를 찾지 못함
    }

    // 2. 문자열의 끝에 도달한 경우
    if ((*word) == '\0')
    {
        // 자식 노드가 없고 단어의 끝인 경우
        if (no_child(*curr) && (*curr)->end == 1)
        {
            free(*curr); // 노드 메모리 해제
            (*curr) = NULL; // 포인터를 NULL로 설정
            return NULL;
        }
        // 자식 노드가 있지만 단어의 끝인 경우
        else if ((*curr)->end == 1)
        {
            (*curr)->end = 0; // 단어의 끝 플래그를 0으로 설정
            return *curr;
        }
        else
        {
            return NULL; // 단어가 아닌 문자열
        }
    }
    // 3. 다음 문자로 넘어가기
    int idx = (*word) - 'a'; // 현재 문자에 해당하는 인덱스 계산
    (*curr)->child[idx] = Delete(&((*curr)->child[idx]), word + 1); // 재귀 호출로 다음 문자 삭제

    // 4. 현재 노드의 상태 확인
    if (no_child(*curr) && (*curr)->end == 0)
    {
        free(*curr); // 현재 노드가 더 이상 필요 없으므로 삭제
        (*curr) = NULL; // 포인터를 NULL로 설정
    }

    return *curr; // 현재 노드 반환
}
void display(TN * root , int level)
{
    TN * curr = root;
    if(curr == NULL)
    {
        printf("--저장된 단어 없음--\n");
        return;
    }
    if(!no_child(curr))
    {
        for(int alph = 0; alph < MAX; alph++) 
        {
            if(curr->child[alph])   //자식노드가 있으면
            {
                for(int l = 0; l< level; l++)
                   printf(" ");    //레벨만큼 공백을 출력

                printf("%c", alph + 'a');

                if(curr->child[alph]->end == 1)
                        printf(" end\n");   //단어의 끝이면 end출력
                else
                    printf("\n");
                display(curr->child[alph], level +1);
            }
        }
    }
}
char * miss_recommend(TN * root, char * word)   //입력에 실수했을경우 비슷한 저장된단어 출력
{
    
}
void play()
{
    TN * root = Getnode();
    char word[100];
    int choice;
    while(1)
    {
        printf("1.삽입 2.검색 3.삭제 4.단어 출력 5.종료\n");
        scanf("%d",&choice);
        switch(choice)
        {
            case 1:
                printf("삽입할 단어 입력\n");
                scanf("%s",word);
                Insert(&root,word);
                break;
            case 2:
                printf("검색할 단어 입력\n");
                scanf("%s",word);
                Search(root,word);
                break;
            case 3:
                printf("삭제할 단어 입력\n");
                scanf("%s",word);
                Delete(&root,word);
                break;
            case 4:
                printf("모든 단어 출력\n");
                display(root,0);
                break;
            case 5:
                return;
        }
    }
}
int main()
{
    play();
    return 0;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#define MAX_CHARACTERS 1005
#define MAX_PARAGRAPHS 5

struct word {
    char* data;
};

struct sentence {
    struct word* data;
    int word_count;//denotes number of words in a sentence
};

struct paragraph {
    struct sentence* data  ;
    int sentence_count;//denotes number of sentences in a paragraph
};

struct document {
    struct paragraph* data;
    int paragraph_count;//denotes number of paragraphs in a document
};

typedef char * string;
typedef struct word word;
typedef struct sentence sentence;
typedef struct paragraph paragraph;
typedef struct document document;

struct document get_document(char* text) {
    // string para[MAX_PARAGRAPHS][256][256];
    word * w;
    w =  (word *)malloc(sizeof(word));
    sentence *s;
    s = (sentence *)malloc(sizeof(sentence));
    paragraph *p;
    p = (paragraph *)malloc(sizeof(paragraph));
    document d;
    char *para = text;
    char *sente = text;
    char *Word = text;
    string seppara = "\n";
    string sepsent = ".";
    string sepword = " ";
    char * one_para;
    char * one_sente;
    char * one_word;
    int i, j, k;

    for(i = 0; one_para != NULL; i++){
        one_para = strtok_r(para, seppara, &para);
        if (one_para == NULL){
            i --;
            continue;
        }
        sente = one_para;
        one_sente = sente;
        for (j = 0; (sente != NULL)&&(one_sente != NULL); j++){
            one_sente = strtok_r(sente, sepsent, &sente);
            if(one_sente == NULL){
                j --;
                continue;
            }
            Word = one_sente;
            one_word = Word;
            for(k = 0; (Word != NULL) && (one_word != NULL); k++){
                one_word = strtok_r(Word, sepword, &Word);
                word* tmpw = (word *)realloc(w, (k + 1) * sizeof(word));
                assert(tmpw != NULL);
                w = tmpw;
                w[k].data = one_word; // need to get rid of '\n'
            }
            sentence * tmps = (sentence *)realloc(s, (j + 1) * sizeof(sentence));
            assert(tmps != NULL);
            s = tmps;
            s[j].data = w;
            s[j].word_count = k;
            w =  (word *)malloc(sizeof(word));
        }
        paragraph * tmpp = (paragraph *)realloc(p, (i + 1) * sizeof(paragraph));
        assert(tmpp != NULL);
        p = tmpp;
        p[i].data = s;
        p[i].sentence_count = j;
        s = (sentence *)malloc(sizeof(sentence));
    }
    d.data = p;
    d.paragraph_count = i;

    free(w);
    free(s);

    return d;
}

struct word kth_word_in_mth_sentence_of_nth_paragraph(struct document Doc, int k, int m, int n) {
    word w;
    w.data = NULL;
    k -= 1;
    m -= 1;
    n -= 1;
    if(n < Doc.paragraph_count){
        if (m < Doc.data[n].sentence_count){
            if (k < Doc.data[n].data[m].word_count){
                w = Doc.data[n].data[m].data[k];
            }
        }
    }
    return w;
}

struct sentence kth_sentence_in_mth_paragraph(struct document Doc, int k, int m) { 
    sentence s;
    s.data = NULL;
    s.word_count = 0;
    k -= 1;
    m -= 1;
    if(m < Doc.paragraph_count){
        if(k < Doc.data[m].sentence_count){
            s = Doc.data[m].data[k];
        }
    }
    return s;
}

struct paragraph kth_paragraph(struct document Doc, int k) {
    paragraph p;
    p.data = NULL;
    p.sentence_count = 0;
    k -= 1;
    if (k < Doc.paragraph_count){
        p = Doc.data[k];
    }
    return p;
}


void print_word(struct word w) {
    printf("%s", w.data);
}

void print_sentence(struct sentence sen) {
    for(int i = 0; i < sen.word_count; i++) {
        print_word(sen.data[i]);
        if (i != sen.word_count - 1) {
            printf(" ");
        }
    }
}

void print_paragraph(struct paragraph para) {
    for(int i = 0; i < para.sentence_count; i++){
        print_sentence(para.data[i]);
        printf(".");
    }
}

void print_document(struct document doc) {
    for(int i = 0; i < doc.paragraph_count; i++) {
        print_paragraph(doc.data[i]);
        if (i != doc.paragraph_count - 1)
            printf("\n");
    }
}

char* get_input_text() {	
    int paragraph_count;
    scanf("%d", &paragraph_count);

    char p[MAX_PARAGRAPHS][MAX_CHARACTERS], doc[MAX_CHARACTERS];
    memset(doc, 0, sizeof(doc));
    getchar();
    for (int i = 0; i < paragraph_count; i++) {
        scanf("%[^\n]%*c", p[i]);
        strcat(doc, p[i]);
        if (i != paragraph_count - 1)
            strcat(doc, "\n");
    }

    char* returnDoc = (char*)malloc((strlen (doc)+1) * (sizeof(char)));
    strcpy(returnDoc, doc);
    return returnDoc;
}

int main() 
{
    char* text = get_input_text();
    struct document Doc = get_document(text);

    // print_document(Doc);
    // printf("\n");
    // struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, 3, 1, 2);
    // print_word(w);
    // printf("\n");
    // struct sentence sen= kth_sentence_in_mth_paragraph(Doc, 2, 2);
    // print_sentence(sen);
    // printf("\n");
    // struct paragraph para = kth_paragraph(Doc, 2);
    // print_paragraph(para);
    // printf("\n");

    int q;
    scanf("%d", &q);

    while (q--) {
        int type;
        scanf("%d", &type);

        if (type == 3){
            int k, m, n;
            scanf("%d %d %d", &k, &m, &n);
            struct word w = kth_word_in_mth_sentence_of_nth_paragraph(Doc, k, m, n);
            print_word(w);
        }

        else if (type == 2) {
            int k, m;
            scanf("%d %d", &k, &m);
            struct sentence sen= kth_sentence_in_mth_paragraph(Doc, k, m);
            print_sentence(sen);
        }

        else{
            int k;
            scanf("%d", &k);
            struct paragraph para = kth_paragraph(Doc, k);
            print_paragraph(para);
        }
        printf("\n");
    }
}
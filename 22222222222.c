#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define MAX_BOOKS 100
#define FILENAME "library.dat"
#define MAX_BORROW_RECORDS 10  
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "admin123"
#define STUDENT_USERNAME "student"
#define STUDENT_PASSWORD "student123"

typedef struct {
    char borrower[50];  
    time_t borrow_time; 
    time_t return_time; 
} BorrowRecord;

typedef struct {
    char title[50];          
    char author[50];         
    char isbn[13];           
    int stock;               
    int borrowed;            
    BorrowRecord records[MAX_BORROW_RECORDS];  
    int record_count;        
} Book;

Book books[MAX_BOOKS];
int count = 0;
int is_admin = 0;

void loadData();
void saveData();
void addBook();
void deleteBook();
void modifyBook();
void searchBook();
void showAllBooks();
void sortBooks();
void menu();
void borrowBook();
void returnBook();
void printBook(const Book *book);
void formatTime(time_t t, char *str);
void login();

int main() {
    loadData();
    login();
    menu();
    return 0;
}

void loadData() {
    FILE *fp = fopen(FILENAME, "r");
    if (fp == NULL) {
        perror("�޷����ļ�");
        return;
    }

    // ��ȡ�鼮����
    fscanf(fp, "%d\n", &count);

    // ��ȡÿ�������ϸ��Ϣ
    for (int i = 0; i < count; i++) {
        fgets(books[i].title, sizeof(books[i].title), fp);
        books[i].title[strcspn(books[i].title, "\n")] = 0; // ȥ�����з�

        fgets(books[i].author, sizeof(books[i].author), fp);
        books[i].author[strcspn(books[i].author, "\n")] = 0;

        fgets(books[i].isbn, sizeof(books[i].isbn), fp);
        books[i].isbn[strcspn(books[i].isbn, "\n")] = 0;

        fscanf(fp, "%d\n", &books[i].stock);
        fscanf(fp, "%d\n", &books[i].borrowed);
        fscanf(fp, "%d\n", &books[i].record_count);

        // ��ȡ���ļ�¼
        for (int j = 0; j < books[i].record_count; j++) {
            fgets(books[i].records[j].borrower, sizeof(books[i].records[j].borrower), fp);
            books[i].records[j].borrower[strcspn(books[i].records[j].borrower, "\n")] = 0;

            fscanf(fp, "%ld\n", &books[i].records[j].borrow_time);
            fscanf(fp, "%ld\n", &books[i].records[j].return_time);
        }
    }

    fclose(fp);
    printf("�����Ѵ��ļ����أ�\n");
}

void saveData() {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        perror("�޷����ļ�");
        return;
    }

    // д���鼮����
    fprintf(fp, "%d\n", count);

    // д��ÿ�������ϸ��Ϣ
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", books[i].title);
        fprintf(fp, "%s\n", books[i].author);
        fprintf(fp, "%s\n", books[i].isbn);
        fprintf(fp, "%d\n", books[i].stock);
        fprintf(fp, "%d\n", books[i].borrowed);
        fprintf(fp, "%d\n", books[i].record_count);

        // д����ļ�¼
        for (int j = 0; j < books[i].record_count; j++) {
            fprintf(fp, "%s\n", books[i].records[j].borrower);
            fprintf(fp, "%ld\n", books[i].records[j].borrow_time);
            fprintf(fp, "%ld\n", books[i].records[j].return_time);
        }
    }

    fclose(fp);
    printf("�����ѱ��浽�ļ���\n");
}

void addBook() {
    if (count >= MAX_BOOKS) {
        printf("ͼ����������޷�������飡\n");
        return;
    }

    Book newBook;
    printf("\n������������");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;
    printf("���������ߣ�");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;
    printf("������ISBN��");
    fgets(newBook.isbn, sizeof(newBook.isbn), stdin);
    newBook.isbn[strcspn(newBook.isbn, "\n")] = 0;
    printf("������������");
    scanf("%d", &newBook.stock);
    while (getchar() != '\n'); 
    newBook.borrowed = 0;
    newBook.record_count = 0;

    books[count++] = newBook;
    printf("��ӳɹ���\n");
}

void deleteBook() {
    char isbn[13];
    printf("\n������Ҫɾ����ISBN��");
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            for (int j = i; j < count - 1; j++) {
                books[j] = books[j + 1];
            }
            count--;
            printf("ɾ���ɹ���\n");
            return;
        }
    }
    printf("δ�ҵ����鼮��\n");
}

void modifyBook() {
    char isbn[13];
    printf("\n������Ҫ�޸ĵ�ISBN��");
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            printf("�������¿������");
            scanf("%d", &books[i].stock);
            while (getchar() != '\n'); 
            printf("�޸ĳɹ���\n");
            return;
        }
    }
    printf("δ�ҵ����鼮��\n");
}

void searchBook() {
    char keyword[50];
    printf("\n�������ѯ�ؼ��ʣ�����/����/ISBN����");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    printf("\n��ѯ�����\n");
    printf("%-20s %-15s %-13s %-8s %-8s\n",
           "����", "����", "ISBN", "���", "�ѽ��");

    for (int i = 0; i < count; i++) {
        if (strstr(books[i].title, keyword) ||
            strstr(books[i].author, keyword) ||
            strstr(books[i].isbn, keyword)) {
            printBook(&books[i]);
        }
    }
}

void showAllBooks() {
    printf("\n��ǰ�ݲأ�\n");
    printf("%-20s %-15s %-13s %-8s %-8s\n",
           "����", "����", "ISBN", "���", "�ѽ��");

    for (int i = 0; i < count; i++) {
        printBook(&books[i]);
    }
}

void printBook(const Book *book) {
    printf("%-20s %-15s %-13s %-8d %-8d\n",
           book->title,
           book->author,
           book->isbn,
           book->stock,
           book->borrowed);
    if (book->record_count > 0) {
        printf("  ���ļ�¼��\n");
        for (int i = 0; i < book->record_count; i++) {
            char borrow_time_str[26];
            char return_time_str[26];
            formatTime(book->records[i].borrow_time, borrow_time_str);
            formatTime(book->records[i].return_time, return_time_str);
            printf("    �����ˣ�%-20s ����ʱ�䣺%-26s �黹ʱ�䣺%-26s\n",
                   book->records[i].borrower, borrow_time_str, return_time_str);
        }
    }
}

void formatTime(time_t t, char *str) {
    if (t == 0) {
        strcpy(str, "δ�黹");
    } else {
        struct tm *tm_info = localtime(&t);
        strftime(str, 26, "%Y-%m-%d %H:%M:%S", tm_info);
    }
}

int compareByTitle(const void *a, const void *b) {
    return strcmp(((Book *)a)->title, ((Book *)b)->title);
}

void sortBooks() {
    qsort(books, count, sizeof(Book), compareByTitle);
    printf("������������ɣ�\n");
    showAllBooks();
}

void borrowBook() {
    char isbn[13];
    printf("\n������Ҫ���ĵ��鼮��ISBN��");
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            if (books[i].stock > 0) {
                if (books[i].record_count >= MAX_BORROW_RECORDS) {
                    printf("���鼮�Ľ��ļ�¼�������޷��������ģ�\n");
                    return;
                }
                printf("�����������������");
                fgets(books[i].records[books[i].record_count].borrower, sizeof(books[i].records[books[i].record_count].borrower), stdin);
                books[i].records[books[i].record_count].borrower[strcspn(books[i].records[books[i].record_count].borrower, "\n")] = 0;
                books[i].records[books[i].record_count].borrow_time = time(NULL);
                books[i].records[books[i].record_count].return_time = 0;
                books[i].stock--;
                books[i].borrowed++;
                books[i].record_count++;
                printf("���ĳɹ�����ǰ�����棺%d���ѽ��������%d\n", books[i].stock, books[i].borrowed);
                saveData(); 
                return;
            } else {
                printf("�������޿�棬�޷����ģ�\n");
                return;
            }
        }
    }
    printf("δ�ҵ����鼮��\n");
}

void returnBook() {
    char isbn[13];
    char borrower[50];
    printf("\n������Ҫ�黹���鼮��ISBN��");
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;
    printf("�����������������");
    fgets(borrower, sizeof(borrower), stdin);
    borrower[strcspn(borrower, "\n")] = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            for (int j = 0; j < books[i].record_count; j++) {
                if (strcmp(books[i].records[j].borrower, borrower) == 0 && books[i].records[j].return_time == 0) {
                    books[i].records[j].return_time = time(NULL);
                    books[i].stock++;
                    books[i].borrowed--;
                    printf("�黹�ɹ�����ǰ�����棺%d���ѽ��������%d\n", books[i].stock, books[i].borrowed);
                    saveData(); 
                    return;
                }
            }
            printf("δ�ҵ��ý��ļ�¼��\n");
            return;
        }
    }
    printf("δ�ҵ����鼮��\n");
}

void login() {
    char username[50];
    char password[50];
    int mode;

    printf("��ѡ���¼ģʽ��\n");
    printf("1. ѧ��\n");
    printf("2. ����Ա\n");
    scanf("%d", &mode);
    while (getchar() != '\n'); 

    printf("�������û�����");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;
    printf("���������룺");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (mode == 1) {
        if (strcmp(username, STUDENT_USERNAME) == 0 && strcmp(password, STUDENT_PASSWORD) == 0) {
            printf("ѧ����¼�ɹ���\n");
            is_admin = 0;
        } else {
            printf("ѧ����¼ʧ�ܣ������û��������룡\n");
            exit(1);
        }
    } else if (mode == 2) {
        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("����Ա��¼�ɹ���\n");
            is_admin = 1;
        } else {
            printf("����Ա��¼ʧ�ܣ������û��������룡\n");
            exit(1);
        }
    } else {
        printf("��Ч�ĵ�¼ģʽѡ��\n");
        exit(1);
    }
}

void menu() {
    int choice;
    do {
        printf("\n===== ͼ��ݹ���ϵͳ =====\n");
        if (is_admin) {
            printf("1. ����鼮\n");
            printf("2. ɾ���鼮\n");
            printf("3. �޸��鼮\n");
        }
        printf("4. ��ѯ�鼮\n");
        printf("5. ��ʾ�����鼮\n");
        if (is_admin) {
            printf("6. �����鼮\n");
        }
        printf("7. �����鼮\n");
        printf("8. �黹�鼮\n");
        printf("0. �˳�ϵͳ\n");
        printf("��ѡ�������");
        scanf("%d", &choice);
        while (getchar() != '\n'); 

        switch (choice) {
            case 1:
                if (is_admin) {
                    addBook();
                } else {
                    printf("��û��Ȩ�޽��д˲�����\n");
                }
                break;
            case 2:
                if (is_admin) {
                    deleteBook();
                } else {
                    printf("��û��Ȩ�޽��д˲�����\n");
                }
                break;
            case 3:
                if (is_admin) {
                    modifyBook();
                } else {
                    printf("��û��Ȩ�޽��д˲�����\n");
                }
                break;
            case 4:
                searchBook();
                break;
            case 5:
                showAllBooks();
                break;
            case 6:
                if (is_admin) {
                    sortBooks();
                } else {
                    printf("��û��Ȩ�޽��д˲�����\n");
                }
                break;
            case 7:
                borrowBook();
                break;
            case 8:
                returnBook();
                break;
            case 0:
                saveData();
                printf("��лʹ�ã�\n");
                break;
            default:
                printf("��Чѡ��\n");
        }
    } while (choice != 0);
}

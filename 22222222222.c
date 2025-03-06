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
        perror("无法打开文件");
        return;
    }

    // 读取书籍数量
    fscanf(fp, "%d\n", &count);

    // 读取每本书的详细信息
    for (int i = 0; i < count; i++) {
        fgets(books[i].title, sizeof(books[i].title), fp);
        books[i].title[strcspn(books[i].title, "\n")] = 0; // 去掉换行符

        fgets(books[i].author, sizeof(books[i].author), fp);
        books[i].author[strcspn(books[i].author, "\n")] = 0;

        fgets(books[i].isbn, sizeof(books[i].isbn), fp);
        books[i].isbn[strcspn(books[i].isbn, "\n")] = 0;

        fscanf(fp, "%d\n", &books[i].stock);
        fscanf(fp, "%d\n", &books[i].borrowed);
        fscanf(fp, "%d\n", &books[i].record_count);

        // 读取借阅记录
        for (int j = 0; j < books[i].record_count; j++) {
            fgets(books[i].records[j].borrower, sizeof(books[i].records[j].borrower), fp);
            books[i].records[j].borrower[strcspn(books[i].records[j].borrower, "\n")] = 0;

            fscanf(fp, "%ld\n", &books[i].records[j].borrow_time);
            fscanf(fp, "%ld\n", &books[i].records[j].return_time);
        }
    }

    fclose(fp);
    printf("数据已从文件加载！\n");
}

void saveData() {
    FILE *fp = fopen(FILENAME, "w");
    if (fp == NULL) {
        perror("无法打开文件");
        return;
    }

    // 写入书籍数量
    fprintf(fp, "%d\n", count);

    // 写入每本书的详细信息
    for (int i = 0; i < count; i++) {
        fprintf(fp, "%s\n", books[i].title);
        fprintf(fp, "%s\n", books[i].author);
        fprintf(fp, "%s\n", books[i].isbn);
        fprintf(fp, "%d\n", books[i].stock);
        fprintf(fp, "%d\n", books[i].borrowed);
        fprintf(fp, "%d\n", books[i].record_count);

        // 写入借阅记录
        for (int j = 0; j < books[i].record_count; j++) {
            fprintf(fp, "%s\n", books[i].records[j].borrower);
            fprintf(fp, "%ld\n", books[i].records[j].borrow_time);
            fprintf(fp, "%ld\n", books[i].records[j].return_time);
        }
    }

    fclose(fp);
    printf("数据已保存到文件！\n");
}

void addBook() {
    if (count >= MAX_BOOKS) {
        printf("图书馆已满，无法添加新书！\n");
        return;
    }

    Book newBook;
    printf("\n请输入书名：");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = 0;
    printf("请输入作者：");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = 0;
    printf("请输入ISBN：");
    fgets(newBook.isbn, sizeof(newBook.isbn), stdin);
    newBook.isbn[strcspn(newBook.isbn, "\n")] = 0;
    printf("请输入库存量：");
    scanf("%d", &newBook.stock);
    while (getchar() != '\n'); 
    newBook.borrowed = 0;
    newBook.record_count = 0;

    books[count++] = newBook;
    printf("添加成功！\n");
}

void deleteBook() {
    char isbn[13];
    printf("\n请输入要删除的ISBN：");
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            for (int j = i; j < count - 1; j++) {
                books[j] = books[j + 1];
            }
            count--;
            printf("删除成功！\n");
            return;
        }
    }
    printf("未找到该书籍！\n");
}

void modifyBook() {
    char isbn[13];
    printf("\n请输入要修改的ISBN：");
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            printf("请输入新库存量：");
            scanf("%d", &books[i].stock);
            while (getchar() != '\n'); 
            printf("修改成功！\n");
            return;
        }
    }
    printf("未找到该书籍！\n");
}

void searchBook() {
    char keyword[50];
    printf("\n请输入查询关键词（书名/作者/ISBN）：");
    fgets(keyword, sizeof(keyword), stdin);
    keyword[strcspn(keyword, "\n")] = 0;

    printf("\n查询结果：\n");
    printf("%-20s %-15s %-13s %-8s %-8s\n",
           "书名", "作者", "ISBN", "库存", "已借出");

    for (int i = 0; i < count; i++) {
        if (strstr(books[i].title, keyword) ||
            strstr(books[i].author, keyword) ||
            strstr(books[i].isbn, keyword)) {
            printBook(&books[i]);
        }
    }
}

void showAllBooks() {
    printf("\n当前馆藏：\n");
    printf("%-20s %-15s %-13s %-8s %-8s\n",
           "书名", "作者", "ISBN", "库存", "已借出");

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
        printf("  借阅记录：\n");
        for (int i = 0; i < book->record_count; i++) {
            char borrow_time_str[26];
            char return_time_str[26];
            formatTime(book->records[i].borrow_time, borrow_time_str);
            formatTime(book->records[i].return_time, return_time_str);
            printf("    借阅人：%-20s 借阅时间：%-26s 归还时间：%-26s\n",
                   book->records[i].borrower, borrow_time_str, return_time_str);
        }
    }
}

void formatTime(time_t t, char *str) {
    if (t == 0) {
        strcpy(str, "未归还");
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
    printf("按书名排序完成！\n");
    showAllBooks();
}

void borrowBook() {
    char isbn[13];
    printf("\n请输入要借阅的书籍的ISBN：");
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            if (books[i].stock > 0) {
                if (books[i].record_count >= MAX_BORROW_RECORDS) {
                    printf("该书籍的借阅记录已满，无法继续借阅！\n");
                    return;
                }
                printf("请输入借阅人姓名：");
                fgets(books[i].records[books[i].record_count].borrower, sizeof(books[i].records[books[i].record_count].borrower), stdin);
                books[i].records[books[i].record_count].borrower[strcspn(books[i].records[books[i].record_count].borrower, "\n")] = 0;
                books[i].records[books[i].record_count].borrow_time = time(NULL);
                books[i].records[books[i].record_count].return_time = 0;
                books[i].stock--;
                books[i].borrowed++;
                books[i].record_count++;
                printf("借阅成功！当前该书库存：%d，已借出数量：%d\n", books[i].stock, books[i].borrowed);
                saveData(); 
                return;
            } else {
                printf("该书已无库存，无法借阅！\n");
                return;
            }
        }
    }
    printf("未找到该书籍！\n");
}

void returnBook() {
    char isbn[13];
    char borrower[50];
    printf("\n请输入要归还的书籍的ISBN：");
    fgets(isbn, sizeof(isbn), stdin);
    isbn[strcspn(isbn, "\n")] = 0;
    printf("请输入借阅人姓名：");
    fgets(borrower, sizeof(borrower), stdin);
    borrower[strcspn(borrower, "\n")] = 0;

    for (int i = 0; i < count; i++) {
        if (strcmp(books[i].isbn, isbn) == 0) {
            for (int j = 0; j < books[i].record_count; j++) {
                if (strcmp(books[i].records[j].borrower, borrower) == 0 && books[i].records[j].return_time == 0) {
                    books[i].records[j].return_time = time(NULL);
                    books[i].stock++;
                    books[i].borrowed--;
                    printf("归还成功！当前该书库存：%d，已借出数量：%d\n", books[i].stock, books[i].borrowed);
                    saveData(); 
                    return;
                }
            }
            printf("未找到该借阅记录！\n");
            return;
        }
    }
    printf("未找到该书籍！\n");
}

void login() {
    char username[50];
    char password[50];
    int mode;

    printf("请选择登录模式：\n");
    printf("1. 学生\n");
    printf("2. 管理员\n");
    scanf("%d", &mode);
    while (getchar() != '\n'); 

    printf("请输入用户名：");
    fgets(username, sizeof(username), stdin);
    username[strcspn(username, "\n")] = 0;
    printf("请输入密码：");
    fgets(password, sizeof(password), stdin);
    password[strcspn(password, "\n")] = 0;

    if (mode == 1) {
        if (strcmp(username, STUDENT_USERNAME) == 0 && strcmp(password, STUDENT_PASSWORD) == 0) {
            printf("学生登录成功！\n");
            is_admin = 0;
        } else {
            printf("学生登录失败，请检查用户名和密码！\n");
            exit(1);
        }
    } else if (mode == 2) {
        if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
            printf("管理员登录成功！\n");
            is_admin = 1;
        } else {
            printf("管理员登录失败，请检查用户名和密码！\n");
            exit(1);
        }
    } else {
        printf("无效的登录模式选择！\n");
        exit(1);
    }
}

void menu() {
    int choice;
    do {
        printf("\n===== 图书馆管理系统 =====\n");
        if (is_admin) {
            printf("1. 添加书籍\n");
            printf("2. 删除书籍\n");
            printf("3. 修改书籍\n");
        }
        printf("4. 查询书籍\n");
        printf("5. 显示所有书籍\n");
        if (is_admin) {
            printf("6. 排序书籍\n");
        }
        printf("7. 借阅书籍\n");
        printf("8. 归还书籍\n");
        printf("0. 退出系统\n");
        printf("请选择操作：");
        scanf("%d", &choice);
        while (getchar() != '\n'); 

        switch (choice) {
            case 1:
                if (is_admin) {
                    addBook();
                } else {
                    printf("你没有权限进行此操作！\n");
                }
                break;
            case 2:
                if (is_admin) {
                    deleteBook();
                } else {
                    printf("你没有权限进行此操作！\n");
                }
                break;
            case 3:
                if (is_admin) {
                    modifyBook();
                } else {
                    printf("你没有权限进行此操作！\n");
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
                    printf("你没有权限进行此操作！\n");
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
                printf("感谢使用！\n");
                break;
            default:
                printf("无效选择！\n");
        }
    } while (choice != 0);
}

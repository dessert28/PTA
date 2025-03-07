#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISHES 100
#define MAX_ORDERS 100
#define ADMIN_USERNAME "admin"
#define ADMIN_PASSWORD "123456"

typedef struct 
{
    int dish_id;
    char name[50];
    char category[50];
    float price;
    int total_quantity;
} Dish;

typedef struct 
{
    int order_id;
    char phone[15];
    char address[100];
    char dish_name[50];
    int quantity;
    float total_price;
} Order;



Dish menu[MAX_DISHES];
Order orders[MAX_ORDERS];
int dish_count = 0;
int order_count = 0;
int is_admin_logged_in = 0; //guanli



// ����˵����ݵ��ļ�
void save_menu_to_file() 
{
    FILE *file = fopen("menu.txt", "w");
    if (file == NULL) 
    {
        printf("�޷��򿪲˵��ļ���\n");
        return;
    }
    int i;
    for (i = 0; i < dish_count; i++) 
    {
        fprintf(file, "%d %s %s %.2f %d\n", menu[i].dish_id, menu[i].name, menu[i].category, menu[i].price, menu[i].total_quantity);
    }

    fclose(file);
    printf("�˵������ѱ��浽�ļ���\n");
}



// ���ļ����ز˵�����
void load_menu_from_file() 
{
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) 
    {
        printf("�˵��ļ������ڣ��������ء�\n");
        return;
    }

    while (fscanf(file, "%d %s %s %f %d", &menu[dish_count].dish_id, menu[dish_count].name, menu[dish_count].category, &menu[dish_count].price, &menu[dish_count].total_quantity) != EOF) 
    {
        dish_count++;
    }

    fclose(file);
    printf("�˵������Ѵ��ļ����أ�\n");
}

// ���涩�����ݵ��ļ�
void save_orders_to_file() 
{
    FILE *file = fopen("orders.txt", "w");
    if (file == NULL) 
    {
        printf("�޷��򿪶����ļ���\n");
        return;
    }
    int i;
    for (i = 0; i < order_count; i++) 
    {
        fprintf(file, "%d %s %s %s %d %.2f\n", orders[i].order_id, orders[i].phone, orders[i].address, orders[i].dish_name, orders[i].quantity, orders[i].total_price);
    }

    fclose(file);
    printf("���������ѱ��浽�ļ���\n");
}


// ���ļ����ض�������
void load_orders_from_file() 
{
    FILE *file = fopen("orders.txt", "r");
    if (file == NULL) 
    {
        printf("�����ļ������ڣ��������ء�\n");
        return;
    }

    while (fscanf(file, "%d %s %s %s %d %f", &orders[order_count].order_id, orders[order_count].phone, orders[order_count].address, orders[order_count].dish_name, &orders[order_count].quantity, &orders[order_count].total_price) != EOF) 
    {
        order_count++;
    }

    fclose(file);
    printf("���������Ѵ��ļ����أ�\n");
}

void add_dish() 
{
    if (dish_count >= MAX_DISHES) 
    {
        printf("�˵��������޷�����²�Ʒ��\n");
        return;
    }

    Dish new_dish;//new��
    new_dish.dish_id = dish_count + 1;

    printf("���������: ");
    scanf("%s", new_dish.name);
    printf("���������: ");
    scanf("%s", new_dish.category);
    printf("�����뵥��: ");
    scanf("%f", &new_dish.price);
    printf("������������: ");
    scanf("%d", &new_dish.total_quantity);

    menu[dish_count++] = new_dish;
    save_menu_to_file(); // ����˵����ݵ��ļ�
    printf("��Ʒ��ӳɹ���\n");
}

void modify_dish() {
    int id;
    printf("������Ҫ�޸ĵĲ�Ʒ��� (dish_id): ");
    scanf("%d", &id);

    // ���Ҳ�Ʒ
    int index = -1;
    for (int i = 0; i < dish_count; i++) {
        if (menu[i].dish_id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("δ�ҵ����Ϊ %d �Ĳ�Ʒ��\n", id);
        return;
    }

    // ��ʾ��ǰ��Ʒ��Ϣ
    printf("\n��ǰ��Ʒ��Ϣ:\n");
    printf("+--------+----------------------+----------------------+--------+--------------+\n");
    printf("| ���   | ����                 | ���                 | ����   | �������     |\n");
    printf("+--------+----------------------+----------------------+--------+--------------+\n");
    printf("| %-6d | %-20s | %-20s | %-6.2f | %-12d |\n",
           menu[index].dish_id, menu[index].name, menu[index].category, menu[index].price, menu[index].total_quantity);
    printf("+--------+----------------------+----------------------+--------+--------------+\n");

    // ѡ�����
    printf("\n��ѡ�����:\n");
    printf("1. ɾ����Ʒ\n");
    printf("2. �޸Ĳ���\n");
    printf("3. �޸����\n");
    printf("4. �޸ĵ���\n");
    printf("5. �޸Ŀ������\n");
    printf("6. �޸Ĳ�Ʒ���\n");
    printf("7. ����\n");
    printf("������ѡ��: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1: // ɾ����Ʒ
            for (int i = index; i < dish_count - 1; i++) {
                menu[i] = menu[i + 1]; // ������Ĳ�Ʒǰ��
            }
            dish_count--; // ��Ʒ������ 1
            printf("��Ʒɾ���ɹ���\n");
            break;
        case 2: // �޸Ĳ���
            printf("��ǰ����: %s\n", menu[index].name);
            printf("�������²���: ");
            scanf("%s", menu[index].name);
            printf("�����޸ĳɹ���\n");
            break;
        case 3: // �޸����
            printf("��ǰ���: %s\n", menu[index].category);
            printf("�����������: ");
            scanf("%s", menu[index].category);
            printf("����޸ĳɹ���\n");
            break;
        case 4: // �޸ĵ���
            printf("��ǰ����: %.2f\n", menu[index].price);
            printf("�������µ���: ");
            scanf("%f", &menu[index].price);
            printf("�����޸ĳɹ���\n");
            break;
        case 5: // �޸Ŀ������
            printf("��ǰ�������: %d\n", menu[index].total_quantity);
            printf("�������¿������: ");
            scanf("%d", &menu[index].total_quantity);
            printf("��������޸ĳɹ���\n");
            break;
        case 6: // �޸Ĳ�Ʒ���
            printf("��ǰ��Ʒ���: %d\n", menu[index].dish_id);
            printf("�������²�Ʒ���: ");
            int new_id;
            scanf("%d", &new_id);

            // ����±���Ƿ��Ѵ���
            for (int i = 0; i < dish_count; i++) {
                if (menu[i].dish_id == new_id) {
                    printf("��� %d �Ѵ��ڣ����������룡\n", new_id);
                    return;
                }
            }

            menu[index].dish_id = new_id; // ���²�Ʒ���
            printf("��Ʒ����޸ĳɹ���\n");
            break;
        case 7: // ����
            printf("�����ϼ��˵���\n");
            return;
        default:
            printf("��Ч��ѡ�����������룡\n");
            return;
    }

    save_menu_to_file(); // �����޸ĺ�Ĳ˵����ݵ��ļ�
}


void browse_menu() {
    if (dish_count == 0) {
        printf("��ǰ�˵�Ϊ�գ�\n");
        return;
    }

    // ��ͷ
    printf("\n�˵��б�:\n");
    printf("+--------+----------------------+----------------------+--------+--------------+\n");
    printf("| ���   | ����                 | ���                 | ����   | �������     |\n");
    printf("+--------+----------------------+----------------------+--------+--------------+\n");

    // �������
    for (int i = 0; i < dish_count; i++) {
        printf("| %-6d | %-20s | %-20s | %-6.2f | %-12d |\n",
               menu[i].dish_id, menu[i].name, menu[i].category, menu[i].price, menu[i].total_quantity);
    }

    // ��β
    printf("+--------+----------------------+----------------------+--------+--------------+\n");
}


void view_all_orders() 
{
    if (order_count == 0) {
        printf("��ǰû�ж�����\n");
        return;
    }

    printf("\n���ж���:\n");
    printf("---------------------------------\n");
    for (int i = 0; i < order_count; i++) {
        printf("�������: %d\n", orders[i].order_id);
        printf("�ͻ��绰: %s\n", orders[i].phone);
        printf("�ͻ���ַ: %s\n", orders[i].address);
        printf("��Ʒ: %s\n", orders[i].dish_name);
        printf("����: %d\n", orders[i].quantity);
        printf("�ܼ�: %.2f\n", orders[i].total_price);
        printf("---------------------------------\n");
    }
}

void delete_orders_by_phone() {
    if (order_count == 0) {
        printf("��ǰû�ж�����\n");
        return;
    }

    char phone[15];
    printf("������Ҫɾ�������Ŀͻ��绰: ");
    scanf("%s", phone);

    int deleted_count = 0;
    for (int i = 0; i < order_count; i++) {
        if (strcmp(orders[i].phone, phone) == 0) {
            // �ҵ�ƥ��Ķ�����������������Ƴ�
            for (int j = i; j < order_count - 1; j++) {
                orders[j] = orders[j + 1];
            }
            order_count--;
            i--; // ��Ϊ����ǰ�ƣ���Ҫ���¼�鵱ǰλ��
            deleted_count++;
        }
    }

    if (deleted_count > 0) {
        save_orders_to_file(); // ������º�Ķ������ݵ��ļ�
        printf("�ɹ�ɾ�� %d ��������\n", deleted_count);
    } else {
        printf("δ�ҵ��ÿͻ��Ķ�����\n");
    }
}



// �鿴���ﳵ
void view_cart(Order *cart, int cart_count) {
    if (cart_count == 0) {
        printf("���ﳵΪ�գ�\n");
        return;
    }

    printf("\n��ǰ���ﳵ����:\n");
    printf("---------------------------------\n");
    float total_price = 0;
    for (int i = 0; i < cart_count; i++) {
        printf("��Ʒ: %s\n", cart[i].dish_name);
        printf("����: %d\n", cart[i].quantity);
        printf("����: %.2f\n", cart[i].total_price / cart[i].quantity);
        printf("�ܼ�: %.2f\n", cart[i].total_price);
        printf("---------------------------------\n");
        total_price += cart[i].total_price;
    }
    printf("���ﳵ�ܽ��: %.2f\n", total_price);
}

void add_to_cart(Order *cart, int *cart_count) {
    int id, quantity;
    char choice;

    while (1) {
        printf("������Ҫ���빺�ﳵ�Ĳ�Ʒ���: ");
        scanf("%d", &id);
        printf("������Ҫ����ķ���: ");
        scanf("%d", &quantity);

        // ���Ҳ�Ʒ
        int index = -1;
        for (int i = 0; i < dish_count; i++) {
            if (menu[i].dish_id == id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            printf("��Ч�Ĳ�Ʒ��ţ�\n");
            continue; // ��������
        }

        if (menu[index].total_quantity < quantity) {
            printf("��治�㣬�޷�����\n");
            continue; // ��������
        }

        // ����Ʒ���빺�ﳵ
        cart[*cart_count].order_id = *cart_count + 1; // ��ʱ�������
        strcpy(cart[*cart_count].dish_name, menu[index].name);
        cart[*cart_count].quantity = quantity;
        cart[*cart_count].total_price = menu[index].price * quantity;

        menu[index].total_quantity -= quantity; // ���ٿ��
        (*cart_count)++;

        printf("��Ʒ�Ѽ��빺�ﳵ��\n");

        // ѯ���Ƿ�����㵥��鿴���ﳵ
        printf("��ѡ�����:\n");
        printf("1. �����㵥\n");
        printf("2. �鿴���ﳵ\n");
        printf("3. �����㵥\n");
        printf("������ѡ��: ");
        scanf(" %c", &choice); // ע��ո񣬱����ȡ֮ǰ�Ļ��з�

        if (choice == '2') {
            view_cart(cart, *cart_count); // �鿴���ﳵ
            printf("��ѡ�����:\n");
            printf("1. �����㵥\n");
            printf("2. �����㵥\n");
            printf("������ѡ��: ");
            scanf(" %c", &choice);
            if (choice == '2') {
                break; // �����㵥
            }
        } else if (choice == '3') {
            break; // �����㵥
        }
    }

    // ����绰�͵�ַ
    char phone[15];
    printf("������ͻ��绰: ");
    scanf("%s", phone);
    printf("������ͻ���ַ: ");
    scanf("%s", cart[0].address);

    // ���ɶ�����ţ����ڵ绰��
    int order_id = atoi(phone + strlen(phone) - 4); // ȡ�绰�� 4 λ��Ϊ�������

    // �����ﳵ�еĶ������浽 orders ����
    for (int i = 0; i < *cart_count; i++) {
        orders[order_count].order_id = order_id; // ͬһ�û��Ķ��������ͬ
        strcpy(orders[order_count].phone, phone);
        strcpy(orders[order_count].address, cart[0].address);
        strcpy(orders[order_count].dish_name, cart[i].dish_name);
        orders[order_count].quantity = cart[i].quantity;
        orders[order_count].total_price = cart[i].total_price;
        order_count++;
    }

    *cart_count = 0; // ��չ��ﳵ
    save_orders_to_file(); // ���涩�����ݵ��ļ�
    printf("�µ��ɹ���\n");
}

void place_order(Order *cart, int *cart_count) 
{
    if (*cart_count == 0) 
    {
        printf("���ﳵΪ�գ��޷��µ���\n");
        return;
    }

    int i;
    for (i = 0; i < *cart_count; i++) {
        orders[order_count++] = cart[i];
    }

    *cart_count = 0;
    save_orders_to_file(); // ���涩�����ݵ��ļ�
    printf("�µ��ɹ���\n");
}


void simulate_payment() {
    float total_revenue = 0;
    int i;
    for (i = 0; i < order_count; i++) {
        total_revenue += orders[i].total_price;
    }
    printf("ģ��֧����ɣ��ܼ�: %.2f\n", total_revenue);
}




void analyze_revenue() {
    float total_revenue = 0;
    int i;
    for (i = 0; i < order_count; i++) {
        total_revenue += orders[i].total_price;
    }
    printf("��Ӫҵ��: %.2f\n", total_revenue);
}

//��
void sort_menu_by_price() {
    int i, j;
    Dish temp;
    for (i = 0; i < dish_count - 1; i++) {
        for (j = 0; j < dish_count - 1 - i; j++)
            {
            if (menu[j].price > menu[j + 1].price) {
                temp = menu[j];
                menu[j] = menu[j + 1];
                menu[j + 1] = temp;
            }
        }
    }
    printf("�˵��Ѱ���������\n");
}

//�ܵ�
void admin_login() {
    char username[50];
    char password[50];

    printf("�������û���: ");
    scanf("%s", username);
    printf("����������: ");
    scanf("%s", password);

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        is_admin_logged_in = 1;
        printf("��¼�ɹ���\n");
    } else {
        printf("�û�����������󣬵�¼ʧ��\n");
    }
}

void admin_logout() {
    is_admin_logged_in = 0;
    printf("����Ա���˳���¼\n");
}

void customer_interface(Order *cart, int *cart_count) {
    int choice;

    while (1) {
        printf("\n");
        printf("+--------------------------------------+\n");
        printf("|            �ͻ�����               |\n");
        printf("+--------------------------------------+\n");
        printf("|            1. ����˵�            |\n");
        printf("|            2. ���빺�ﳵ          |\n");
        // printf("|            3. �鿴���ﳵ          |\n");
        // printf("|              4. �µ�              |\n");
        printf("|            3. ģ��֧��            |\n");
        printf("|          4. ����������            |\n");
        printf("+--------------------------------------+\n");
        printf("��ѡ�����: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                browse_menu();
                break;
            case 2:
                add_to_cart(cart, cart_count);
                break;
            // case 3:
            //     view_cart(cart, *cart_count);
            //     break;
            // case 4:
            //     place_order(cart, cart_count);
            //     break;
            case 3:
                simulate_payment();
                break;
            case 4:
                return; // ����������
            default:
                printf("��Ч��ѡ�����������룡\n");
        }
    }
}
void admin_interface() {
    int choice;

    // ����Ա��¼
    admin_login();
    if (!is_admin_logged_in) {
        return; // ��¼ʧ�ܣ�����������
    }

    while (1) {
        printf("\n");
        printf("+--------------------------------------+\n");
        printf("|            ����Ա����             |\n");
        printf("+--------------------------------------+\n");
        printf("|            1. ��Ӳ�Ʒ            |\n");
        printf("|            2. �޸Ĳ�Ʒ            |\n");
        printf("|            3. ����˵�            |\n");
        printf("|          4. �鿴���ж���          |\n");
        printf("|      5. ɾ��ͬһ�û��Ķ���        |\n");
        printf("|          6. Ӫҵ�����            |\n");
        printf("|        7. ����������˵�          |\n");
        printf("|            8. �˳���¼            |\n");
        printf("+--------------------------------------+\n");
        printf("��ѡ�����: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                add_dish();
                break;
            case 2:
                modify_dish();
                break;
            case 3:
                browse_menu();
                break;
            case 4:
                view_all_orders();
                break;
            case 5:
                delete_orders_by_phone();
                break;
            case 6:
                analyze_revenue();
                break;
            case 7:
                sort_menu_by_price();
                break;
            case 8:
                admin_logout();
                return; // ����������
            default:
                printf("��Ч��ѡ�����������룡\n");
        }
    }
}

int main() {
    int choice;
    Order cart[MAX_ORDERS];
    int cart_count = 0;

    // ���ز˵��Ͷ�������
    load_menu_from_file();
    load_orders_from_file();

    while (1) {
        // ������
        printf("\n");
        printf("+--------------------------------------+\n");
        printf("|        ��ӭʹ������ϵͳ��         |\n");
        printf("+--------------------------------------+\n");
        printf("|            1. �ͻ�����            |\n");
        printf("|            2. ����Ա����          |\n");
        printf("|              3. �˳�              |\n");
        printf("+--------------------------------------+\n");
        printf("��ѡ�����: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                customer_interface(cart, &cart_count); // ����ͻ�����
                break;
            case 2:
                admin_interface(); // �������Ա����
                break;
            case 3:
                printf("�˳�ϵͳ��\n");
                save_menu_to_file();
                save_orders_to_file();
                exit(0);
            default:
                printf("��Ч��ѡ�����������룡\n");
        }
    }
    return 0;
}
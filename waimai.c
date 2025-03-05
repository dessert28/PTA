#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_DISHES 100
#define MAX_ORDERS 100

typedef struct {
    int dish_id;
    char name[50];
    char category[50];
    float price;
    int total_quantity;
} Dish;

typedef struct {
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

// ����˵����ݵ��ļ�
void save_menu_to_file() {
    FILE *file = fopen("menu.txt", "w");
    if (file == NULL) {
        printf("�޷��򿪲˵��ļ���\n");
        return;
    }
	int i;
    for (i = 0; i < dish_count; i++) {
        fprintf(file, "%d %s %s %.2f %d\n", menu[i].dish_id, menu[i].name, menu[i].category, menu[i].price, menu[i].total_quantity);
    }

    fclose(file);
    printf("�˵������ѱ��浽�ļ���\n");
}

// ���ļ����ز˵�����
void load_menu_from_file() {
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("�˵��ļ������ڣ��������ء�\n");
        return;
    }

    while (fscanf(file, "%d %s %s %f %d", &menu[dish_count].dish_id, menu[dish_count].name, menu[dish_count].category, &menu[dish_count].price, &menu[dish_count].total_quantity) != EOF) {
        dish_count++;
    }

    fclose(file);
    printf("�˵������Ѵ��ļ����أ�\n");
}

// ���涩�����ݵ��ļ�
void save_orders_to_file() {
    FILE *file = fopen("orders.txt", "w");
    if (file == NULL) {
        printf("�޷��򿪶����ļ���\n");
        return;
    }
	int i;
    for (i = 0; i < order_count; i++) {
        fprintf(file, "%d %s %s %s %d %.2f\n", orders[i].order_id, orders[i].phone, orders[i].address, orders[i].dish_name, orders[i].quantity, orders[i].total_price);
    }

    fclose(file);
    printf("���������ѱ��浽�ļ���\n");
}

// ���ļ����ض�������
void load_orders_from_file() {
    FILE *file = fopen("orders.txt", "r");
    if (file == NULL) {
        printf("�����ļ������ڣ��������ء�\n");
        return;
    }

    while (fscanf(file, "%d %s %s %s %d %f", &orders[order_count].order_id, orders[order_count].phone, orders[order_count].address, orders[order_count].dish_name, &orders[order_count].quantity, &orders[order_count].total_price) != EOF) {
        order_count++;
    }

    fclose(file);
    printf("���������Ѵ��ļ����أ�\n");
}

void add_dish() {
    if (dish_count >= MAX_DISHES) {
        printf("�˵��������޷�����²�Ʒ��\n");
        return;
    }

    Dish new_dish;
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
    printf("������Ҫ�޸ĵĲ�Ʒ���: ");
    scanf("%d", &id);

    if (id < 1 || id > dish_count) {
        printf("��Ч�Ĳ�Ʒ��ţ�\n");
        return;
    }

    Dish *dish = &menu[id - 1];
    printf("��ǰ����: %s\n", dish->name);
    printf("�������²���: ");
    scanf("%s", dish->name);
    printf("��ǰ���: %s\n", dish->category);
    printf("�����������: ");
    scanf("%s", dish->category);
    printf("��ǰ����: %.2f\n", dish->price);
    printf("�������µ���: ");
    scanf("%f", &dish->price);
    printf("��ǰ������: %d\n", dish->total_quantity);
    printf("��������������: ");
    scanf("%d", &dish->total_quantity);

    save_menu_to_file(); // ����˵����ݵ��ļ�
    printf("��Ʒ�޸ĳɹ���\n");
}

void browse_menu() {
    printf("�˵��б�:\n");
    int i;
	for (i = 0; i < dish_count; i++) {
        printf("��Ʒ���: %d, ����: %s, ���: %s, ����: %.2f, ������: %d\n",
               menu[i].dish_id, menu[i].name, menu[i].category, menu[i].price, menu[i].total_quantity);
    }
}

void add_to_cart(Order *cart, int *cart_count) {
    int id, quantity;
    printf("������Ҫ���빺�ﳵ�Ĳ�Ʒ���: ");
    scanf("%d", &id);
    printf("������Ҫ����ķ���: ");
    scanf("%d", &quantity);

    if (id < 1 || id > dish_count) {
        printf("��Ч�Ĳ�Ʒ��ţ�\n");
        return;
    }

    Dish *dish = &menu[id - 1];
    if (dish->total_quantity < quantity) {
        printf("��治�㣬�޷�����\n");
        return;
    }

    cart[*cart_count].order_id = *cart_count + 1;
    printf("������ͻ��绰: ");
    scanf("%s", cart[*cart_count].phone);
    printf("������ͻ���ַ: ");
    scanf("%s", cart[*cart_count].address);
    strcpy(cart[*cart_count].dish_name, dish->name);
    cart[*cart_count].quantity = quantity;
    cart[*cart_count].total_price = dish->price * quantity;

    dish->total_quantity -= quantity;
    (*cart_count)++;
    printf("��Ʒ�Ѽ��빺�ﳵ��\n");
}

void place_order(Order *cart, int *cart_count) {
    if (*cart_count == 0) {
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

int main() {
    int choice;
    Order cart[MAX_ORDERS];
    int cart_count = 0;

    // ���ز˵��Ͷ�������
    load_menu_from_file();
    load_orders_from_file();

    while (1) {
        printf("\n����ϵͳ\n");
        printf("1. ��Ӳ�Ʒ\n");
        printf("2. �޸Ĳ�Ʒ\n");
        printf("3. ����˵�\n");
        printf("4. ���빺�ﳵ\n");
        printf("5. �µ�\n");
        printf("6. ģ��֧��\n");
        printf("7. Ӫҵ�����\n");
        printf("8. �˳�\n");
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
                add_to_cart(cart, &cart_count);
                break;
            case 5:
                place_order(cart, &cart_count);
                break;
            case 6:
                simulate_payment();
                break;
            case 7:
                analyze_revenue();
                break;
            case 8:
                printf("�˳�ϵͳ��\n");
                save_menu_to_file(); // �˳�ǰ����˵�����
                save_orders_to_file(); // �˳�ǰ���涩������
                exit(0);
            default:
                printf("��Ч��ѡ�����������룡\n");
        }
    }

    return 0;
}
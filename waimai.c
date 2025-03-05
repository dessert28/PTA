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

// 保存菜单数据到文件
void save_menu_to_file() {
    FILE *file = fopen("menu.txt", "w");
    if (file == NULL) {
        printf("无法打开菜单文件！\n");
        return;
    }
	int i;
    for (i = 0; i < dish_count; i++) {
        fprintf(file, "%d %s %s %.2f %d\n", menu[i].dish_id, menu[i].name, menu[i].category, menu[i].price, menu[i].total_quantity);
    }

    fclose(file);
    printf("菜单数据已保存到文件！\n");
}

// 从文件加载菜单数据
void load_menu_from_file() {
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) {
        printf("菜单文件不存在，跳过加载。\n");
        return;
    }

    while (fscanf(file, "%d %s %s %f %d", &menu[dish_count].dish_id, menu[dish_count].name, menu[dish_count].category, &menu[dish_count].price, &menu[dish_count].total_quantity) != EOF) {
        dish_count++;
    }

    fclose(file);
    printf("菜单数据已从文件加载！\n");
}

// 保存订单数据到文件
void save_orders_to_file() {
    FILE *file = fopen("orders.txt", "w");
    if (file == NULL) {
        printf("无法打开订单文件！\n");
        return;
    }
	int i;
    for (i = 0; i < order_count; i++) {
        fprintf(file, "%d %s %s %s %d %.2f\n", orders[i].order_id, orders[i].phone, orders[i].address, orders[i].dish_name, orders[i].quantity, orders[i].total_price);
    }

    fclose(file);
    printf("订单数据已保存到文件！\n");
}

// 从文件加载订单数据
void load_orders_from_file() {
    FILE *file = fopen("orders.txt", "r");
    if (file == NULL) {
        printf("订单文件不存在，跳过加载。\n");
        return;
    }

    while (fscanf(file, "%d %s %s %s %d %f", &orders[order_count].order_id, orders[order_count].phone, orders[order_count].address, orders[order_count].dish_name, &orders[order_count].quantity, &orders[order_count].total_price) != EOF) {
        order_count++;
    }

    fclose(file);
    printf("订单数据已从文件加载！\n");
}

void add_dish() {
    if (dish_count >= MAX_DISHES) {
        printf("菜单已满，无法添加新菜品！\n");
        return;
    }

    Dish new_dish;
    new_dish.dish_id = dish_count + 1;

    printf("请输入菜名: ");
    scanf("%s", new_dish.name);
    printf("请输入类别: ");
    scanf("%s", new_dish.category);
    printf("请输入单价: ");
    scanf("%f", &new_dish.price);
    printf("请输入总数量: ");
    scanf("%d", &new_dish.total_quantity);

    menu[dish_count++] = new_dish;
    save_menu_to_file(); // 保存菜单数据到文件
    printf("菜品添加成功！\n");
}

void modify_dish() {
    int id;
    printf("请输入要修改的菜品编号: ");
    scanf("%d", &id);

    if (id < 1 || id > dish_count) {
        printf("无效的菜品编号！\n");
        return;
    }

    Dish *dish = &menu[id - 1];
    printf("当前菜名: %s\n", dish->name);
    printf("请输入新菜名: ");
    scanf("%s", dish->name);
    printf("当前类别: %s\n", dish->category);
    printf("请输入新类别: ");
    scanf("%s", dish->category);
    printf("当前单价: %.2f\n", dish->price);
    printf("请输入新单价: ");
    scanf("%f", &dish->price);
    printf("当前总数量: %d\n", dish->total_quantity);
    printf("请输入新总数量: ");
    scanf("%d", &dish->total_quantity);

    save_menu_to_file(); // 保存菜单数据到文件
    printf("菜品修改成功！\n");
}

void browse_menu() {
    printf("菜单列表:\n");
    int i;
	for (i = 0; i < dish_count; i++) {
        printf("菜品编号: %d, 菜名: %s, 类别: %s, 单价: %.2f, 总数量: %d\n",
               menu[i].dish_id, menu[i].name, menu[i].category, menu[i].price, menu[i].total_quantity);
    }
}

void add_to_cart(Order *cart, int *cart_count) {
    int id, quantity;
    printf("请输入要加入购物车的菜品编号: ");
    scanf("%d", &id);
    printf("请输入要购买的份数: ");
    scanf("%d", &quantity);

    if (id < 1 || id > dish_count) {
        printf("无效的菜品编号！\n");
        return;
    }

    Dish *dish = &menu[id - 1];
    if (dish->total_quantity < quantity) {
        printf("库存不足，无法购买！\n");
        return;
    }

    cart[*cart_count].order_id = *cart_count + 1;
    printf("请输入客户电话: ");
    scanf("%s", cart[*cart_count].phone);
    printf("请输入客户地址: ");
    scanf("%s", cart[*cart_count].address);
    strcpy(cart[*cart_count].dish_name, dish->name);
    cart[*cart_count].quantity = quantity;
    cart[*cart_count].total_price = dish->price * quantity;

    dish->total_quantity -= quantity;
    (*cart_count)++;
    printf("菜品已加入购物车！\n");
}

void place_order(Order *cart, int *cart_count) {
    if (*cart_count == 0) {
        printf("购物车为空，无法下单！\n");
        return;
    }

    int i;
	for (i = 0; i < *cart_count; i++) {
        orders[order_count++] = cart[i];
    }

    *cart_count = 0;
    save_orders_to_file(); // 保存订单数据到文件
    printf("下单成功！\n");
}

void simulate_payment() {
    float total_revenue = 0;
    	int i;
		for (i = 0; i < order_count; i++) {
        total_revenue += orders[i].total_price;
    }
    printf("模拟支付完成，总价: %.2f\n", total_revenue);
}

void analyze_revenue() {
    float total_revenue = 0;
    int i;
    for (i = 0; i < order_count; i++) {
        total_revenue += orders[i].total_price;
    }
    printf("总营业额: %.2f\n", total_revenue);
}

int main() {
    int choice;
    Order cart[MAX_ORDERS];
    int cart_count = 0;

    // 加载菜单和订单数据
    load_menu_from_file();
    load_orders_from_file();

    while (1) {
        printf("\n外卖系统\n");
        printf("1. 添加菜品\n");
        printf("2. 修改菜品\n");
        printf("3. 浏览菜单\n");
        printf("4. 加入购物车\n");
        printf("5. 下单\n");
        printf("6. 模拟支付\n");
        printf("7. 营业额分析\n");
        printf("8. 退出\n");
        printf("请选择操作: ");
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
                printf("退出系统。\n");
                save_menu_to_file(); // 退出前保存菜单数据
                save_orders_to_file(); // 退出前保存订单数据
                exit(0);
            default:
                printf("无效的选择，请重新输入！\n");
        }
    }

    return 0;
}
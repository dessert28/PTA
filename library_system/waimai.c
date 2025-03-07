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



// 保存菜单数据到文件
void save_menu_to_file() 
{
    FILE *file = fopen("menu.txt", "w");
    if (file == NULL) 
    {
        printf("无法打开菜单文件！\n");
        return;
    }
    int i;
    for (i = 0; i < dish_count; i++) 
    {
        fprintf(file, "%d %s %s %.2f %d\n", menu[i].dish_id, menu[i].name, menu[i].category, menu[i].price, menu[i].total_quantity);
    }

    fclose(file);
    printf("菜单数据已保存到文件！\n");
}



// 从文件加载菜单数据
void load_menu_from_file() 
{
    FILE *file = fopen("menu.txt", "r");
    if (file == NULL) 
    {
        printf("菜单文件不存在，跳过加载。\n");
        return;
    }

    while (fscanf(file, "%d %s %s %f %d", &menu[dish_count].dish_id, menu[dish_count].name, menu[dish_count].category, &menu[dish_count].price, &menu[dish_count].total_quantity) != EOF) 
    {
        dish_count++;
    }

    fclose(file);
    printf("菜单数据已从文件加载！\n");
}

// 保存订单数据到文件
void save_orders_to_file() 
{
    FILE *file = fopen("orders.txt", "w");
    if (file == NULL) 
    {
        printf("无法打开订单文件！\n");
        return;
    }
    int i;
    for (i = 0; i < order_count; i++) 
    {
        fprintf(file, "%d %s %s %s %d %.2f\n", orders[i].order_id, orders[i].phone, orders[i].address, orders[i].dish_name, orders[i].quantity, orders[i].total_price);
    }

    fclose(file);
    printf("订单数据已保存到文件！\n");
}


// 从文件加载订单数据
void load_orders_from_file() 
{
    FILE *file = fopen("orders.txt", "r");
    if (file == NULL) 
    {
        printf("订单文件不存在，跳过加载。\n");
        return;
    }

    while (fscanf(file, "%d %s %s %s %d %f", &orders[order_count].order_id, orders[order_count].phone, orders[order_count].address, orders[order_count].dish_name, &orders[order_count].quantity, &orders[order_count].total_price) != EOF) 
    {
        order_count++;
    }

    fclose(file);
    printf("订单数据已从文件加载！\n");
}

void add_dish() 
{
    if (dish_count >= MAX_DISHES) 
    {
        printf("菜单已满，无法添加新菜品！\n");
        return;
    }

    Dish new_dish;//new结
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
    printf("请输入要修改的菜品编号 (dish_id): ");
    scanf("%d", &id);

    // 查找菜品
    int index = -1;
    for (int i = 0; i < dish_count; i++) {
        if (menu[i].dish_id == id) {
            index = i;
            break;
        }
    }

    if (index == -1) {
        printf("未找到编号为 %d 的菜品！\n", id);
        return;
    }

    // 显示当前菜品信息
    printf("\n当前菜品信息:\n");
    printf("+--------+----------------------+----------------------+--------+--------------+\n");
    printf("| 编号   | 菜名                 | 类别                 | 单价   | 库存数量     |\n");
    printf("+--------+----------------------+----------------------+--------+--------------+\n");
    printf("| %-6d | %-20s | %-20s | %-6.2f | %-12d |\n",
           menu[index].dish_id, menu[index].name, menu[index].category, menu[index].price, menu[index].total_quantity);
    printf("+--------+----------------------+----------------------+--------+--------------+\n");

    // 选择操作
    printf("\n请选择操作:\n");
    printf("1. 删除菜品\n");
    printf("2. 修改菜名\n");
    printf("3. 修改类别\n");
    printf("4. 修改单价\n");
    printf("5. 修改库存数量\n");
    printf("6. 修改菜品编号\n");
    printf("7. 返回\n");
    printf("请输入选项: ");
    int choice;
    scanf("%d", &choice);

    switch (choice) {
        case 1: // 删除菜品
            for (int i = index; i < dish_count - 1; i++) {
                menu[i] = menu[i + 1]; // 将后面的菜品前移
            }
            dish_count--; // 菜品数量减 1
            printf("菜品删除成功！\n");
            break;
        case 2: // 修改菜名
            printf("当前菜名: %s\n", menu[index].name);
            printf("请输入新菜名: ");
            scanf("%s", menu[index].name);
            printf("菜名修改成功！\n");
            break;
        case 3: // 修改类别
            printf("当前类别: %s\n", menu[index].category);
            printf("请输入新类别: ");
            scanf("%s", menu[index].category);
            printf("类别修改成功！\n");
            break;
        case 4: // 修改单价
            printf("当前单价: %.2f\n", menu[index].price);
            printf("请输入新单价: ");
            scanf("%f", &menu[index].price);
            printf("单价修改成功！\n");
            break;
        case 5: // 修改库存数量
            printf("当前库存数量: %d\n", menu[index].total_quantity);
            printf("请输入新库存数量: ");
            scanf("%d", &menu[index].total_quantity);
            printf("库存数量修改成功！\n");
            break;
        case 6: // 修改菜品编号
            printf("当前菜品编号: %d\n", menu[index].dish_id);
            printf("请输入新菜品编号: ");
            int new_id;
            scanf("%d", &new_id);

            // 检查新编号是否已存在
            for (int i = 0; i < dish_count; i++) {
                if (menu[i].dish_id == new_id) {
                    printf("编号 %d 已存在，请重新输入！\n", new_id);
                    return;
                }
            }

            menu[index].dish_id = new_id; // 更新菜品编号
            printf("菜品编号修改成功！\n");
            break;
        case 7: // 返回
            printf("返回上级菜单。\n");
            return;
        default:
            printf("无效的选择，请重新输入！\n");
            return;
    }

    save_menu_to_file(); // 保存修改后的菜单数据到文件
}


void browse_menu() {
    if (dish_count == 0) {
        printf("当前菜单为空！\n");
        return;
    }

    // 表头
    printf("\n菜单列表:\n");
    printf("+--------+----------------------+----------------------+--------+--------------+\n");
    printf("| 编号   | 菜名                 | 类别                 | 单价   | 库存数量     |\n");
    printf("+--------+----------------------+----------------------+--------+--------------+\n");

    // 表格内容
    for (int i = 0; i < dish_count; i++) {
        printf("| %-6d | %-20s | %-20s | %-6.2f | %-12d |\n",
               menu[i].dish_id, menu[i].name, menu[i].category, menu[i].price, menu[i].total_quantity);
    }

    // 表尾
    printf("+--------+----------------------+----------------------+--------+--------------+\n");
}


void view_all_orders() 
{
    if (order_count == 0) {
        printf("当前没有订单！\n");
        return;
    }

    printf("\n所有订单:\n");
    printf("---------------------------------\n");
    for (int i = 0; i < order_count; i++) {
        printf("订单编号: %d\n", orders[i].order_id);
        printf("客户电话: %s\n", orders[i].phone);
        printf("客户地址: %s\n", orders[i].address);
        printf("菜品: %s\n", orders[i].dish_name);
        printf("数量: %d\n", orders[i].quantity);
        printf("总价: %.2f\n", orders[i].total_price);
        printf("---------------------------------\n");
    }
}

void delete_orders_by_phone() {
    if (order_count == 0) {
        printf("当前没有订单！\n");
        return;
    }

    char phone[15];
    printf("请输入要删除订单的客户电话: ");
    scanf("%s", phone);

    int deleted_count = 0;
    for (int i = 0; i < order_count; i++) {
        if (strcmp(orders[i].phone, phone) == 0) {
            // 找到匹配的订单，将其从数组中移除
            for (int j = i; j < order_count - 1; j++) {
                orders[j] = orders[j + 1];
            }
            order_count--;
            i--; // 因为数组前移，需要重新检查当前位置
            deleted_count++;
        }
    }

    if (deleted_count > 0) {
        save_orders_to_file(); // 保存更新后的订单数据到文件
        printf("成功删除 %d 个订单！\n", deleted_count);
    } else {
        printf("未找到该客户的订单！\n");
    }
}



// 查看购物车
void view_cart(Order *cart, int cart_count) {
    if (cart_count == 0) {
        printf("购物车为空！\n");
        return;
    }

    printf("\n当前购物车内容:\n");
    printf("---------------------------------\n");
    float total_price = 0;
    for (int i = 0; i < cart_count; i++) {
        printf("菜品: %s\n", cart[i].dish_name);
        printf("数量: %d\n", cart[i].quantity);
        printf("单价: %.2f\n", cart[i].total_price / cart[i].quantity);
        printf("总价: %.2f\n", cart[i].total_price);
        printf("---------------------------------\n");
        total_price += cart[i].total_price;
    }
    printf("购物车总金额: %.2f\n", total_price);
}

void add_to_cart(Order *cart, int *cart_count) {
    int id, quantity;
    char choice;

    while (1) {
        printf("请输入要加入购物车的菜品编号: ");
        scanf("%d", &id);
        printf("请输入要购买的份数: ");
        scanf("%d", &quantity);

        // 查找菜品
        int index = -1;
        for (int i = 0; i < dish_count; i++) {
            if (menu[i].dish_id == id) {
                index = i;
                break;
            }
        }

        if (index == -1) {
            printf("无效的菜品编号！\n");
            continue; // 重新输入
        }

        if (menu[index].total_quantity < quantity) {
            printf("库存不足，无法购买！\n");
            continue; // 重新输入
        }

        // 将菜品加入购物车
        cart[*cart_count].order_id = *cart_count + 1; // 临时订单编号
        strcpy(cart[*cart_count].dish_name, menu[index].name);
        cart[*cart_count].quantity = quantity;
        cart[*cart_count].total_price = menu[index].price * quantity;

        menu[index].total_quantity -= quantity; // 减少库存
        (*cart_count)++;

        printf("菜品已加入购物车！\n");

        // 询问是否继续点单或查看购物车
        printf("请选择操作:\n");
        printf("1. 继续点单\n");
        printf("2. 查看购物车\n");
        printf("3. 结束点单\n");
        printf("请输入选项: ");
        scanf(" %c", &choice); // 注意空格，避免读取之前的换行符

        if (choice == '2') {
            view_cart(cart, *cart_count); // 查看购物车
            printf("请选择操作:\n");
            printf("1. 继续点单\n");
            printf("2. 结束点单\n");
            printf("请输入选项: ");
            scanf(" %c", &choice);
            if (choice == '2') {
                break; // 结束点单
            }
        } else if (choice == '3') {
            break; // 结束点单
        }
    }

    // 输入电话和地址
    char phone[15];
    printf("请输入客户电话: ");
    scanf("%s", phone);
    printf("请输入客户地址: ");
    scanf("%s", cart[0].address);

    // 生成订单编号（基于电话）
    int order_id = atoi(phone + strlen(phone) - 4); // 取电话后 4 位作为订单编号

    // 将购物车中的订单保存到 orders 数组
    for (int i = 0; i < *cart_count; i++) {
        orders[order_count].order_id = order_id; // 同一用户的订单编号相同
        strcpy(orders[order_count].phone, phone);
        strcpy(orders[order_count].address, cart[0].address);
        strcpy(orders[order_count].dish_name, cart[i].dish_name);
        orders[order_count].quantity = cart[i].quantity;
        orders[order_count].total_price = cart[i].total_price;
        order_count++;
    }

    *cart_count = 0; // 清空购物车
    save_orders_to_file(); // 保存订单数据到文件
    printf("下单成功！\n");
}

void place_order(Order *cart, int *cart_count) 
{
    if (*cart_count == 0) 
    {
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

//排
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
    printf("菜单已按单价排序\n");
}

//管登
void admin_login() {
    char username[50];
    char password[50];

    printf("请输入用户名: ");
    scanf("%s", username);
    printf("请输入密码: ");
    scanf("%s", password);

    if (strcmp(username, ADMIN_USERNAME) == 0 && strcmp(password, ADMIN_PASSWORD) == 0) {
        is_admin_logged_in = 1;
        printf("登录成功！\n");
    } else {
        printf("用户名或密码错误，登录失败\n");
    }
}

void admin_logout() {
    is_admin_logged_in = 0;
    printf("管理员已退出登录\n");
}

void customer_interface(Order *cart, int *cart_count) {
    int choice;

    while (1) {
        printf("\n");
        printf("+--------------------------------------+\n");
        printf("|            客户界面               |\n");
        printf("+--------------------------------------+\n");
        printf("|            1. 浏览菜单            |\n");
        printf("|            2. 加入购物车          |\n");
        // printf("|            3. 查看购物车          |\n");
        // printf("|              4. 下单              |\n");
        printf("|            3. 模拟支付            |\n");
        printf("|          4. 返回主界面            |\n");
        printf("+--------------------------------------+\n");
        printf("请选择操作: ");
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
                return; // 返回主界面
            default:
                printf("无效的选择，请重新输入！\n");
        }
    }
}
void admin_interface() {
    int choice;

    // 管理员登录
    admin_login();
    if (!is_admin_logged_in) {
        return; // 登录失败，返回主界面
    }

    while (1) {
        printf("\n");
        printf("+--------------------------------------+\n");
        printf("|            管理员界面             |\n");
        printf("+--------------------------------------+\n");
        printf("|            1. 添加菜品            |\n");
        printf("|            2. 修改菜品            |\n");
        printf("|            3. 浏览菜单            |\n");
        printf("|          4. 查看所有订单          |\n");
        printf("|      5. 删除同一用户的订单        |\n");
        printf("|          6. 营业额分析            |\n");
        printf("|        7. 按单价排序菜单          |\n");
        printf("|            8. 退出登录            |\n");
        printf("+--------------------------------------+\n");
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
                return; // 返回主界面
            default:
                printf("无效的选择，请重新输入！\n");
        }
    }
}

int main() {
    int choice;
    Order cart[MAX_ORDERS];
    int cart_count = 0;

    // 加载菜单和订单数据
    load_menu_from_file();
    load_orders_from_file();

    while (1) {
        // 主界面
        printf("\n");
        printf("+--------------------------------------+\n");
        printf("|        欢迎使用外卖系统！         |\n");
        printf("+--------------------------------------+\n");
        printf("|            1. 客户界面            |\n");
        printf("|            2. 管理员界面          |\n");
        printf("|              3. 退出              |\n");
        printf("+--------------------------------------+\n");
        printf("请选择操作: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                customer_interface(cart, &cart_count); // 进入客户界面
                break;
            case 2:
                admin_interface(); // 进入管理员界面
                break;
            case 3:
                printf("退出系统。\n");
                save_menu_to_file();
                save_orders_to_file();
                exit(0);
            default:
                printf("无效的选择，请重新输入！\n");
        }
    }
    return 0;
}
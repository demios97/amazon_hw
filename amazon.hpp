#ifndef AMAZON_HPP
#define AMAZON_HPP

enum class Category{
    ELECTRONICS,
    CLOTHING,
    BOOKS,
    BEAUTY
};

class Product{
private:
    char *name;
    double price;
    Category category;
public:
    Product(const char *name, double price, Category category);
    ~Product();
    const char *getName() const;
    void setName(const char *name);
    double getPrice() const;
    void setPrice(double price);
    Category getCategory() const;
    void setCategory(Category category);
};

class ShoppingCart{
private:
    static const int MAX_PRODUCTS = 100; // Maximum number of products in the shopping cart
    Product *products[MAX_PRODUCTS];
    int numProducts;
public:
    ShoppingCart();
    ~ShoppingCart();
    void addProduct(Product *product);
    void removeProduct(Product *product);
    double calculateTotalPrice() const;
    void displayCart() const;
};

class User{
private:
    char *name;
    ShoppingCart cart;
public:
    User(const char *name);
    ~User();
    const char *getName() const;
    void setName(const char *name);
    ShoppingCart &getShoppingCart();
};

class OnlineShoppingSystem
{
private:
    static const int MAX_PRODUCTS = 1000; // Maximum number of products in the system
    static const int MAX_USERS = 100; // Maximum number of users in the system
    Product *products[MAX_PRODUCTS];
    User *users[MAX_USERS];
    int numProducts;
    int numUsers;
public:
    OnlineShoppingSystem();
    ~OnlineShoppingSystem();
    void addProduct(Product *product);
    void removeProduct(Product *product);
    void addUser(User *user);
    void removeUser(User *user);
    void displayProducts() const;
    void displayUsers() const;
};

#endif
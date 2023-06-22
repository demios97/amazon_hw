//
#include <iostream>
#include <cstring>
#include "amazon.hpp"

Product::Product(const char *name, double price, Category category){
    if(!name || price<0 || category>Category::BEAUTY || category<Category::ELECTRONICS) return;
    this->name = new char[strlen(name)+1];
    if(!this->name){
        delete[] this->name;
        return;
    }
    strcpy(this->name, name);
    this->price = price;
    this->category = category;
}

Product::~Product(){
    delete[] name;
}

const char *Product::getName() const{
    return name;
}

void Product::setName(const char *name){
    if(!name) return;
    delete[] this->name;
    this->name = new char[strlen(name)+1];
    if(!this->name){
        delete[] this->name;
        return;
    }
    strcpy(this->name, name);
}

double Product::getPrice() const{
    return price;
}

void Product::setPrice(double price){
    if(price<0) return;
    this->price = price;
}

Category Product::getCategory() const{
    return category;
}

void Product::setCategory(Category category){
    if(category>Category::BEAUTY || category<Category::ELECTRONICS) return;
    this->category = category;
}

ShoppingCart::ShoppingCart(){
    this->products = new Product[MAX_PRODUCTS];
    this->numProducts = 0;
}

ShoppingCart::~ShoppingCart(){
    delete[] products;
}

void OnlineShoppingSystem::addUser(User *user){
    if(!user)return;

    numUsers++;
}


int main() {
// Create an instance of the OnlineShoppingSystem
OnlineShoppingSystem shoppingSystem;
// Create some products
Product* product1 = new Product("Laptop", 1000.0, Category::ELECTRONICS);
Product* product2 = new Product("T-Shirt", 19.99, Category::CLOTHING);
Product* product3 = new Product("Book", 29.99, Category::BOOKS);
// Add the products to the system
shoppingSystem.addProduct(product1);
shoppingSystem.addProduct(product2);
shoppingSystem.addProduct(product3);
// Create a user
User* user = new User("John");
// Add the user to the system
shoppingSystem.addUser(user);
// Simulate online shopping
shoppingSystem.simulateOnlineShopping();
// Display the products and users in the system
shoppingSystem.displayProducts();
shoppingSystem.displayUsers();
// Clean up memory
delete product1;
delete product2;
delete product3;
delete user;
return 0;
}
//
#include <iostream>
#include <cstring>
#include "amazon.hpp"

std::string enumToString(Category cat) {
    switch(cat){
        case Category::ELECTRONICS:
            return "ELECTRONICS";
        case Category::CLOTHING:
            return "CLOTHING";
        case Category::BOOKS:
            return "BOOKS";
        case Category::BEAUTY:
         	return "BEAUTY";
        default:
            return "Unknown";
    }
}

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
    this->numProducts = 0;
}

ShoppingCart::~ShoppingCart(){
    delete[] products;
}

void ShoppingCart::addProduct(Product *product){
    if(!product || numProducts==MAX_PRODUCTS) return;
    products[numProducts]->setName(product->getName());
    products[numProducts]->setPrice(product->getPrice());
    products[numProducts]->setCategory(product->getCategory());
    numProducts++;
}

void ShoppingCart::removeProduct(Product *product){
    if(!product) return;
    int count = numProducts;
    while(count>0){
        if(strcmp(products[count]->getName(), product->getName())==0){
            products[count]->~Product();
            for (int i = count; i < numProducts - 1; ++i)
                products[i] = products[i + 1];
        }
        count--;
    }
}

double ShoppingCart::calculateTotalPrice() const{
    int count = numProducts;
    double total = 0;
    while(count>0){
        total += products[count]->getPrice();
        count--;
    }
    return total;
}

void ShoppingCart::displayCart() const{
    int count = 0;
    std::cout << "Cart:" << std::endl;
    while(count != numProducts+1){
        std::cout << count << ". Name: " << products[count]->getName();
        std::cout << " Price: " << products[count]->getPrice();
        std::cout << " Category: " << enumToString(products[count]->getCategory()) << std::endl;
        count++;
    }
}

User::User(const char *name){
    setName(name);
}

User::~User(){
    delete[] name;
}

const char* User::getName()const{
    return name;
}

void User::setName(const char *name){
    if(!name) return;
    this->name = new char[strlen(name)+1];
    if(!this->name){
        delete[] this->name;
        return;
    }
    strcpy(this->name, name);
}

ShoppingCart& User::getShoppingCart(){
    return cart;
}

OnlineShoppingSystem::OnlineShoppingSystem(){
    this->numProducts = 0;
    this->numUsers = 0;
}

OnlineShoppingSystem::~OnlineShoppingSystem(){
    delete[] products;//TODO do we need? because he already deletes product in main
}

void OnlineShoppingSystem::addProduct(Product* product){
    if(!product || numProducts==MAX_PRODUCTS) return;
    products[numProducts]->setName(product->getName());
    products[numProducts]->setPrice(product->getPrice());
    products[numProducts]->setCategory(product->getCategory());
    ShoppingCart cart = users[numUsers]->getShoppingCart();
    cart.addProduct(product);
    numProducts++;
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
//shoppingSystem.simulateOnlineShopping();
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
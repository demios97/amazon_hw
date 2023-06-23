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
    setName(name);
    setPrice(price);
    setCategory(category);
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
    if(!product || numProducts==MAX_PRODUCTS){
        std::cout << "Product cannot be added to cart" << std::endl;
        return;
    }
    products[numProducts++] = product;
    std::cout << "Product added to cart successfully" << std::endl;
}

void ShoppingCart::removeProduct(Product *product){
    if(!product || numProducts==0){
        std::cout << "Product cannot be removed from cart" << std::endl;
        return;
    }
    int count = numProducts-1;
    while(count>=0){
        if(strcmp(products[count]->getName(), product->getName())==0){
            for (int i = count; i < numProducts-1; i++)
                products[i] = products[i + 1];
            products[--numProducts] = nullptr;
        }
        count--;
    }
    std::cout << "Product removed from cart successfully" << std::endl;
}

double ShoppingCart::calculateTotalPrice() const{
    int count = numProducts-1;
    double total = 0;
    while(count>=0)
        total += products[count--]->getPrice();
    return total;
}

void ShoppingCart::displayCart() const{
    int count = 0;
    std::cout << "Cart:" << std::endl;
    while(count != numProducts){
        std::cout << count+1 << ". Name: " << products[count]->getName();
        std::cout << " Price: " << products[count]->getPrice();
        std::cout << " Category: " << enumToString(products[count]->getCategory()) << std::endl;
        count++;
    }
    std::cout << "Total price: " << calculateTotalPrice() << std::endl;
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
    if(!name){
        return;
    }
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
    delete[] products;
    delete[] users;
}

void OnlineShoppingSystem::addProduct(Product* product){
    if(!product || numProducts==MAX_PRODUCTS) {
        std::cout << "Product cannot be added" << std::endl;
        return;
    }
    for(int i = 0; i < numProducts; i++)
        if(strcmp(products[i]->getName(), product->getName())==0){
            std::cout << "Product already exist" << std::endl;
            return;
        }
    products[numProducts++] = product;
    std::cout << "Product added successfully" << std::endl;
}

void OnlineShoppingSystem::removeProduct(Product *product){
    if(!product || numProducts==0){
        std::cout << "Product cannot be removed" << std::endl;
        return;
    }
    int count = numProducts-1;
    while(count>=0){
        if(strcmp(products[count]->getName(), product->getName())==0){
            for (int i = count; i < numProducts-1; i++)
                products[i] = products[i + 1];
            products[--numProducts] = nullptr;
        }
        count--;
    }
    count = numUsers-1;
    while(count>=0)
        users[count--]->getShoppingCart().removeProduct(product);
    std::cout << "Product removed successfully" << std::endl;
}

void OnlineShoppingSystem::addUser(User *user){
    if(!user || numUsers==MAX_USERS){
        std::cout << "User cannot be added" << std::endl;
        return;
    }
    for(int i = 0; i < numUsers; i++)
        if(strcmp(users[i]->getName(), user->getName())==0){
            std::cout << "User already exist" << std::endl;
            return;
        }
    users[numUsers++] = user;
    std::cout << "User added successfully" << std::endl;

}

void OnlineShoppingSystem::removeUser(User *user){
    if(!user || numUsers==0){
        std::cout << "User cannot be removed" << std::endl;
        return;
    }
    int count = numUsers-1;
    while(count>=0){
        if(strcmp(users[count]->getName(), user->getName())==0){
            for (int i = count; i < numUsers-1; i++)
                users[i] = users[i + 1];
            users[--numUsers] = nullptr;
        }
        count--;
    }
    std::cout << "User removed successfully" << std::endl;
}

void OnlineShoppingSystem::displayProducts() const{
    int count = 0;
    std::cout << "Amazon Products:" << std::endl;
    while(count != numProducts){
        std::cout << count+1 << ". Name: " << products[count]->getName();
        std::cout << " Price: " << products[count]->getPrice();
        std::cout << " Category: " << enumToString(products[count]->getCategory()) << std::endl;
        count++;
    }
}

void OnlineShoppingSystem::displayUsers() const{
    int count = 0;
    std::cout << "Amazon Users:" << std::endl;
    while(count != numUsers){
        std::cout << count+1 << ". Name: " << users[count]->getName() << std::endl;
        count++;
    }
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
User* user1 = new User("John1");
User* user2 = new User("John2");
User* user3 = new User("John3");
User* user4 = new User("John4");
// Add the user to the system
shoppingSystem.addUser(user1);
shoppingSystem.addUser(user2);
shoppingSystem.addUser(user3);
shoppingSystem.addUser(user4);
// Simulate online shopping
user1->getShoppingCart().addProduct(product1);
user1->getShoppingCart().addProduct(product2);
user1->getShoppingCart().addProduct(product3);
user2->getShoppingCart().addProduct(product3);
user2->getShoppingCart().addProduct(product3);
user2->getShoppingCart().addProduct(product3);
user1->getShoppingCart().displayCart();
user2->getShoppingCart().displayCart();
shoppingSystem.removeProduct(product3);
shoppingSystem.removeUser(user1);
user2->getShoppingCart().displayCart();
// Display the products and users in the system
shoppingSystem.displayProducts();
shoppingSystem.displayUsers();
// Clean up memory
delete product1;
delete product2;
delete product3;
delete user1;
delete user2;
delete user3;
delete user4;
return 0;
}
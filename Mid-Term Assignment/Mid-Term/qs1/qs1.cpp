#include <iostream>
#include <string>
#include <algorithm>
using namespace std;
class Book {
public:
    string title;
    string author;
    string isbn;

    Book* next;

    Book(string title, string author, string isbn)
        : title(title), author(author), isbn(isbn), next(NULL) {}
};

class BookManager {
private:
    Book* head;

public:
    BookManager() : head(NULL) {}

    // 添加图书
    void addBook(string title, string author, string isbn);

    // 删除图书
    void deleteBook(string isbn);

    // 修改图书信息
    void modifyBook(string isbn, string newTitle, string newAuthor);

    // 排序图书
    void sortBooks();

    // 查询图书
    Book* searchBook(string isbn);

    // 显示所有图书
    void displayBooks();

    // 析构函数
    ~BookManager();
};

void BookManager::addBook(string title, string author, string isbn) {
    // 检查是否存在相同ISBN的图书
    if (searchBook(isbn) != NULL) {
        cout << "错误：已存在ISBN为 " << isbn << " 的图书。" << endl;
        return;
    }

    // 创建新图书节点
    Book* newBook = new Book(title, author, isbn);

    // 如果链表为空，新节点为头结点
    if (head == NULL) {
        head = newBook;
    }
    else {
        // 否则，在链表末尾添加新节点
        Book* temp = head;
        while (temp->next != NULL) {
            temp = temp->next;
        }
        temp->next = newBook;
    }
}

void BookManager::deleteBook(string isbn) {
    Book* temp = head;
    Book* prev = NULL;

    // 如果要删除的图书是头结点
    if (temp != NULL && temp->isbn == isbn) {
        head = temp->next;
        delete temp;
        return;
    }

    // 遍历链表查找要删除的图书
    while (temp != NULL && temp->isbn != isbn) {
        prev = temp;
        temp = temp->next;
    }

    // 如果找到要删除的图书
    if (temp != NULL) {
        prev->next = temp->next;
        delete temp;
        cout << "图书 ISBN " << isbn << " 已删除。" << endl;
    }
    else {
        cout << "错误：未找到要删除的图书。" << endl;
    }
}

void BookManager::modifyBook(string isbn, string newTitle, string newAuthor) {
    Book* book = searchBook(isbn);
    if (book != NULL) {
        book->title = newTitle;
        book->author = newAuthor;
        cout << "图书 ISBN " << isbn << " 的信息已修改。" << endl;
    }
    else {
        cout << "错误：未找到要修改的图书。" << endl;
    }
}

void BookManager::sortBooks() {
    if (head == NULL || head->next == NULL) {
        return;
    }

    // 使用冒泡排序按ISBN号排序图书
    bool swapped;
    Book* temp;
    Book* prev = NULL;

    do {
        swapped = false;
        temp = head;

        while (temp->next != prev) {
            if (temp->isbn > temp->next->isbn) {
                swap(temp->title, temp->next->title);
                swap(temp->author, temp->next->author);
                swap(temp->isbn, temp->next->isbn);
                swapped = true;
            }
            temp = temp->next;
        }
        prev = temp;
    } while (swapped);

    cout << "图书已按ISBN号排序。" << endl;
}

Book* BookManager::searchBook(string isbn) {
    Book* temp = head;
    while (temp != NULL) {
        if (temp->isbn == isbn) {
            return temp;
        }
        temp = temp->next;
    }
    return NULL;
}

void BookManager::displayBooks() {
    if (head == NULL) {
        cout << "图书馆中没有图书。" << endl;
        return;
    }

    Book* temp = head;
    while (temp != NULL) {
        cout << "标题：" << temp->title << "，作者：" << temp->author << "，ISBN：" << temp->isbn << endl;
        temp = temp->next;
    }
}

BookManager::~BookManager() {
    // 释放链表内存
    while (head != NULL) {
        Book* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // 在这里可以测试你的 BookManager 类的各个函数
    return 0;
}

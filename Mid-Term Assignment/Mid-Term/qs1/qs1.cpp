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

    // ���ͼ��
    void addBook(string title, string author, string isbn);

    // ɾ��ͼ��
    void deleteBook(string isbn);

    // �޸�ͼ����Ϣ
    void modifyBook(string isbn, string newTitle, string newAuthor);

    // ����ͼ��
    void sortBooks();

    // ��ѯͼ��
    Book* searchBook(string isbn);

    // ��ʾ����ͼ��
    void displayBooks();

    // ��������
    ~BookManager();
};

void BookManager::addBook(string title, string author, string isbn) {
    // ����Ƿ������ͬISBN��ͼ��
    if (searchBook(isbn) != NULL) {
        cout << "�����Ѵ���ISBNΪ " << isbn << " ��ͼ�顣" << endl;
        return;
    }

    // ������ͼ��ڵ�
    Book* newBook = new Book(title, author, isbn);

    // �������Ϊ�գ��½ڵ�Ϊͷ���
    if (head == NULL) {
        head = newBook;
    }
    else {
        // ����������ĩβ����½ڵ�
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

    // ���Ҫɾ����ͼ����ͷ���
    if (temp != NULL && temp->isbn == isbn) {
        head = temp->next;
        delete temp;
        return;
    }

    // �����������Ҫɾ����ͼ��
    while (temp != NULL && temp->isbn != isbn) {
        prev = temp;
        temp = temp->next;
    }

    // ����ҵ�Ҫɾ����ͼ��
    if (temp != NULL) {
        prev->next = temp->next;
        delete temp;
        cout << "ͼ�� ISBN " << isbn << " ��ɾ����" << endl;
    }
    else {
        cout << "����δ�ҵ�Ҫɾ����ͼ�顣" << endl;
    }
}

void BookManager::modifyBook(string isbn, string newTitle, string newAuthor) {
    Book* book = searchBook(isbn);
    if (book != NULL) {
        book->title = newTitle;
        book->author = newAuthor;
        cout << "ͼ�� ISBN " << isbn << " ����Ϣ���޸ġ�" << endl;
    }
    else {
        cout << "����δ�ҵ�Ҫ�޸ĵ�ͼ�顣" << endl;
    }
}

void BookManager::sortBooks() {
    if (head == NULL || head->next == NULL) {
        return;
    }

    // ʹ��ð������ISBN������ͼ��
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

    cout << "ͼ���Ѱ�ISBN������" << endl;
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
        cout << "ͼ�����û��ͼ�顣" << endl;
        return;
    }

    Book* temp = head;
    while (temp != NULL) {
        cout << "���⣺" << temp->title << "�����ߣ�" << temp->author << "��ISBN��" << temp->isbn << endl;
        temp = temp->next;
    }
}

BookManager::~BookManager() {
    // �ͷ������ڴ�
    while (head != NULL) {
        Book* temp = head;
        head = head->next;
        delete temp;
    }
}

int main() {
    // ��������Բ������ BookManager ��ĸ�������
    return 0;
}

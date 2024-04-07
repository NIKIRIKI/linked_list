# Документация к классу `Linked_list`

## Описание
`Linked_list` - это класс, реализующий односвязный список. Он содержит вложенный класс `Node`, который представляет узел списка. Каждый узел содержит данные и ссылку на следующий узел в списке.

## Конструкторы
- `Linked_list()` - Создает пустой список.
- `Linked_list(Node* head)` - Создает список с одним узлом.
- `Linked_list(Node* head, Node* tail)` - Создает список с двумя узлами.
- `Linked_list(const Linked_list& list)` - Создает копию существующего списка.
- `Linked_list(initializer_list<int> init_list)` - Создает список из списка инициализаторов.

## Методы
- `int get_size() const` - Возвращает размер списка.
- `bool is_empty() const` - Проверяет, является ли список пустым.
- `void append(const int data)` - Добавляет элемент в конец списка.
- `void prepend(const int data)` - Добавляет элемент в начало списка.
- `void extend(Linked_list& list)` - Расширяет текущий список, добавляя в конец все элементы из другого списка.
- `void insert(const int index, const int data)` - Вставляет элемент на указанную позицию.
- `void insert_sorted(const int value)` - Вставляет элемент в отсортированный список так, чтобы список остался отсортированным.
- `void remove_tail()` - Удаляет последний элемент списка.
- `void remove_head()` - Удаляет первый элемент списка.
- `void remove_value(const int value)` - Удаляет первый элемент в списке, равный указанному значению.
- `void remove_at(const int index)` - Удаляет элемент на указанной позиции.
- `int pop()` - Удаляет и возвращает первый элемент списка.
- `void print() const` - Выводит все элементы списка.
- `Linked_list slice(const int start, const int end)` - Возвращает новый список, содержащий элементы текущего списка от начального до конечного индекса.
- `int get_element(const int index) const` - Возвращает элемент на указанной позиции.
- `Node* find(int value)` - Возвращает первый узел в списке, равный указанному значению.
- `void sort()` - Сортирует список.
- `void reverse()` - Переворачивает список.
- `void swap(const int index1, const int index2)` - Меняет местами элементы на указанных позициях.
- `Linked_list& operator=(const Linked_list& list)` - Оператор присваивания.
- `int operator[](const int index) const` - Оператор индексации.
- `bool contains(const int value) const` - Проверяет, содержит ли список указанное значение.
- `int index_of(const int value) const` - Возвращает индекс первого вхождения указанного значения в список.
- `void clear()` - Очищает список.
- `vector<int> to_vector() const` - Преобразует список в вектор.
- `string to_string() const` - Преобразует список в строку.
- `bool operator==(const Linked_list& list) const` - Оператор равенства.
- `bool operator!=(const Linked_list& list) const` - Оператор неравенства.
- `Linked_list copy() const` - Возвращает копию списка.

## Примеры использования

```cpp
// Создание списка
Linked_list list;

// Добавление элементов
list.append(8);
list.append(9);
list.append(2);
list.append(100);
list.append(54);

// Сортировка списка
list.sort();

// Вывод списка
list.print();  // Вывод: 2 8 9 54 100

// Реверс списка
list.reverse();

// Вывод списка
list.print();  // Вывод: 100 54 9 8 2
```

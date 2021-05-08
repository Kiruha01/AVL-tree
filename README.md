# AVL дерево
Реализация самобалансирующегося бинарного дерева поиска.

Дерево представляет собой связанные между собой структуры 
`Node<T>`. Левое поддерево каждой `Node` содержит элементы, 
большие текущего, а правое - меньшие. 

**Для типа данных `T` должна быть определена операция `<`**

## ```Node<T>```
Класс `Node<T>` является приватным в классе `AVL`.


### Конструктор

Создание ноды со значением 42 и родителем `parent`:
```c++
Node* new_node = new Node(42, parent);
```

### Поля

* `Node* parent` - Указатель на родителя ноды
* `Node* left` - Указатель на корень левого поддерева
* `Node* right` - Указатель на корень правого поддерева
* `T data` - Значение ноды
* `short diff` - Значение разницы высот левого и правого поддерева

## ```AVL<T>``` 

### Поля

* `Node* head` - Указатель на корень дерева

### Конструктор

Пустое дерево
```c++
AVL<int> a = AVL<int>();
```
Дерево с корнем `3`
```c++
AVL<int> a = AVL<int>(3);
```

### Открытые методы
#### Добавление элемента

```c++
a.add(42);
```

#### Удаление элемента

```c++
a.remove(42);
```

#### Проверка наличия элемента

```c++
a.contain(42);
```

```c++
a.add(42);
a.contain(42); // true
a.remove(42);
a.contaion(42); // false
```

При поптыке удалить несуществующий элемент дерево останется
без изменения.

### Закрытые методы

#### Поиск элемента в дереве
```c++
Node* find(T item);
```

При нахождении элемента возвращается указатель на него, 
иначе - `nullptr`.

#### Повороты
```c++
void small_left_turn(Node* node);
void small_right_turn(Node* node);
void big_left_turn(Node* node);
void big_right_turn(Node* node);
```

*Малый левый, малый правый, большой левый* и *большой правый*
повороты сооветственно. Используются для балансировки дерева.

Выбор подходящего поворота происходит в функции
```c++
bool do_rotation(Node* node);
```
При выполнении поворота возвращает `true`, иначе `false`.

Подробнее о поворотах [тут](https://ru.wikipedia.org/wiki/АВЛ-дерево#Балансировка).
Используя обозначения из ссылки, можно выписать таблицу 
выбора поворота исходя из значений поля `diff` узлов **a** и **b**

|  a  |   b  |   Поворот          |
| --- | ---- |  :--------------   |
|  2  | +1/0 | `small_right_turn` |
|  2  |  -1  | `big_right_turn`   |
|  -2 | 0/-1 | `small_left_turn`  |
|  -2 |  +1  | `big_left_turn`    |

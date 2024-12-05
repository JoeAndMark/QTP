# 代码规范

本仓库决定使用 [Google C++ Style Guide](https://google.github.io/styleguide/cppguide.html)，同时结合 Qt 的命名规范，并对其中比较 “自由” 的地方作出一些修改，予以明确规范。

## 命名规则

### 类名和结构体名

遵循 `CamelCase`，即大驼峰命名风格。

### 函数命名

为了与 Qt 已有的代码搭配，本仓库规定函数命名统一使用小驼峰风格。

### 变量命名

变量命名采用 `snake_case` 风格，类的成员变量需要在最后附加一个下划线 `_`，以便于区分成员变量和其余变量。

常量变量采用全大写字母加下划线的格式，例如 `MAX_COUNT`。

布尔类型变量采用 `is_`、`can_`、`has_` 等前缀，使变量含义更明确。

指针类型变量使用 `ptr` 后缀来区分，将所有的 `pointer` 都换成 `ptr`。

## 格式化规范

### 缩进

使用 4 空格缩进，不允许使用制表符缩进，所有的制表符必须转换为空格。

### 括号风格

使用 K&R 风格，即大括号在控制语句同一侧，例如：

```cpp
while () {
    ...
}

for () {
	...   
}

void example() {
    ...
}
```

## 注释规范

### 文件级注释

在文件开头使用 Doxygen 风格的注释，简要说明文件的目的、功能和作者信息：

```cpp
/*!
 * @file 文件名，需要后缀
 * @brief 简要描述文件的目的和功能
 * 
 * 对该文件目的和功能的详细描述
 *
 * @author 作者
 * @email 邮箱
 * @data 创建文件的日期
 * @license 遵循的开源协议，本仓库使用 MIT 开源协议，所以直接填写 MIT
 */
```

### 类级注释

每个类的定义前使用 `@class`、`@brief` 等标记，说明类的目的和功能：

```cpp
/*!
 * @class 类名
 * @brief 简要描述类的目的和功能
 *
 * 详细描述类的目的和功能
 */
class MyClass : public QWidget {
    ...
}
```

### 成员函数注释

成员函数（方法）注释应当包含 `@brief`、`@param` 和 `@return` 等标签，简要说明函数的功能和参数的用途：

```cpp
/*!
 * @brief 该方法的简要说明
 * 
 * 该方法的详细说明
 */
void MyClass::initializeWidget() {
    ...
}

/*!
 * @brief 方法的简要说明
 * @param 方法参数的说明
 * @return 该方法返回值的说明
 */
bool MyClass::setTitle(const QString& title) {
    ...
}
```

### 信号和槽的注释

对于 Qt 的信号和槽，可以使用 `@signal` 和 `@slot` 标识来进行文档化：

```cpp
class MyClass : public QWidget {
    Q_OBJECT
       
public:
    /*!
     * @brief 方法的简要说明
     * @param 方法参数的说明
     * @signal （标记该方法是一个信号，使用时不需要在后面撰写内容）
     */
    void valueChanged(int value);

public slots:
    /*!
     * @brief 方法的简要说明
     * @param 方法参数的说明
     * @slot （标记该方法是一个槽函数，使用时不需要在后面撰写内容）
     */
    void onValueChanged(int value);
}
```

### 参数注释

使用 `@param` 标注每个函数参数，说明其含义和用途：

```cpp
/*!
 * @brief 函数的简要说明
 * @param 函数参数的说明
 * @param 函数参数的说明
 * @return 返回值的说明
 */
QString processData(const QString& inputData, const QString& filter);
```

### 返回值注释

使用 `@return` 来标注函数的返回值：

```cpp
/*!
 * @brief 函数的简要说明
 * @return 函数返回值的说明
 */
QString getTitle() const;
```

### 常量和宏的注释

对于常量和宏的注释，使用 `@def` 和 `@const` 来进行标注：

```cpp
/*!
 * @def 宏的名称
 * @brief 宏的简要说明
 */
#define MAX_WIDGET_COUNT 100
```

### 详细描述

对于复杂的函数或类，可以在简短的 `@brief` 之后添加详细描述，以便更清晰地说明功能和设计意图：

```cpp
/*!
 * @brief 函数的简要说明
 * @details 函数的详细说明
 * （函数的详细说明）
 * @param 函数参数的说明
 * @param 函数参数的说明
 * @return 函数返回值的说明
 */
int add(int a, int b);
```

### 自定义标签

使用 Doxygen 支持的自定义标签来增强文档的可读性和结构性：

```cpp
/*!
 * @brief 函数的简要说明
 * @ details 函数的详细说明
 * @warning 警告
 * @throws 抛出的异常
 */
void initializeDatabase();
```

### 其他说明

以上注释规范并不一定能够覆盖开发过程中的每一个场景，使用时，需要根据上述规范进行组合和搭配。

对于其他情况下，注释使用 `//` 还是 `/*! */` 在此作出规定：

+ 单行注释使用 `//`
+ 多行注释使用 `/*! */`
+ 连续的单行注释视为多行注释




## image_processor

This is a console application for processing 24-bit BMP files.

## Description

[image_processor.cpp](https://github.com/A1darI/image_processor/blob/012ecaeb51d8c96ae99dc8248fb0e9c9dace86e8/image_processor.cpp) - initial source file

filters - all filters implementation

examples - filter application example

file_handling - implementation of reading and writing BMP files

[image.h](https://github.com/A1darI/image_processor/blob/bb41d152d47e1a3b0ba57b9ae46dad3ac8549dbf/image.h) - image representation

[cmd_parser.h](https://github.com/A1darI/image_processor/blob/bb41d152d47e1a3b0ba57b9ae46dad3ac8549dbf/cmd_parser.h) - command line parsing


### Supported image format

Input and output graphic files must be in the format [BMP](http://en.wikipedia.org/wiki/BMP_file_format).

A 24-bit BMP file is used without compression and without a color table. The type of `DIB header` used is `BITMAPINFOHEADER`.

### Arguments format

When run without arguments, the program displays help.

### Filters

#### Crop (-crop width height)
Crop the image to the specified width and height. The top left of the image is used.

If the requested width or height exceeds the dimensions of the original image, the available portion of the image is returned.

#### Grayscale (-gs)
Converts an image to grayscale using a formula

![encoding](https://latex.codecogs.com/svg.image?R'%20=%20G'%20=%20B'%20=0.299%20R%20&plus;%200%20.587%20G%20&plus ;%200%20.%20114%20B)

#### Negative (-neg)
Converts an image to a negative using the formula

![encoding](https://latex.codecogs.com/svg.image?R'%20=%201%20-%20R,%20G'%20=%201%20-%20G,%20B'%20=%201%20-%20B)

#### Sharpening (-sharp)
Sharpening. Achieved by using a matrix

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%205%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

#### Edge Detection (-edge threshold)
Boundary selection. The image is converted to grayscale and a matrix is applied

![encoding](https://latex.codecogs.com/svg.image?%5Cbegin%7Bbmatrix%7D%20&%20-1%20&%20%20%5C%5C-1%20&%204%20&%20-1%20%5C%5C%20&%20-1%20&%20%20%5C%5C%5Cend%7Bbmatrix%7D)

Pixels with a value that exceeds `threshold` are painted white, the rest are black.

#### Gaussian Blur (-blur sigma)
[Гауссово размытие](https://ru.wikipedia.org/wiki/Размытие_по_Гауссу),
параметр – сигма.

Значение каждого из цветов пикселя `C[x0][y0]` определяется формулой

![encoding](https://latex.codecogs.com/svg.image?C%5Bx_0%5D%5By_0%5D%20=%20%5Csum_%7Bx=0,y=0%7D%5E%7Bwidth-1,%20height-1%7DC%5Bx%5D%5By%5D%5Cfrac%7B1%7D%7B%5Csqrt%5B%5D%7B2%5Cpi%5Csigma%5E2%7D%7De%5E%7B-%5Cfrac%7B%5Cleft%7Cx_o-x%5Cright%7C%5E2%20&plus;%20%5Cleft%7Cy_o-y%5Cright%7C%5E2%7D%7B2%5Csigma%5E2%7D%7D)

Существуют различные варианты релализации и оптимизации вычисления этого фильтра, описание есть [в Википедии](https://ru.wikipedia.org/wiki/Размытие_по_Гауссу).

### Дополнительные фильтры

Дополнительно надо сделать как минимум один собственный фильтр.

Фильтр должен быть нетривиальным. Идеи можно взять
[здесь](https://developer.apple.com/library/mac/documentation/graphicsimaging/reference/CoreImageFilterReference/Reference/reference.html).

Хорошие примеры: [Crystallize](https://developer.apple.com/library/archive/documentation/GraphicsImaging/Reference/CoreImageFilterReference/index.html#//apple_ref/doc/filter/ci/CICrystallize), [Glass Distortion](https://developer.apple.com/library/archive/documentation/GraphicsImaging/Reference/CoreImageFilterReference/index.html#//apple_ref/doc/filter/ci/CIGlassDistortion).

Выбор собственного фильтра надо согласовать с семинаристом.

Авторы самых интересных (по мнению лектора) фильтров получат бонус к баллам.

## Реализация

Применять сторонние библиотеки для работы с изображениями запрещено.

Старайтесь делать все компоненты программы по возможности более универсальными и не привязанными к специфике конкретной задачи.

Все исключительные ситуации должны корректно обрабатываться с выводом понятного пользователю сообщения об ошибке.
Никакие сценарии, включая использование файлов с форматом, не соответствующим спецификации, не должны приводить к "падению" программы.

Скорее всего, вам понадобятся следующие компоненты:
- Класс, представляющий изображение и обеспечивающий работу с ним
- Классы для чтения и записи формата BMP
- Фильтры
- Контроллер, управляющий последовательным применением фильтров

Общие части следует выделить через наследование.

Подробный дизайн программы рекомендуется обсудить с преподавателем на семинарах.

## Сдача и оценивание

Все сдачи будут проходить код ревью.

Вам предстоит написать всю программу с нуля.
В корневом `CMakeLists.txt` задачи должен быть описан исполняемый файл с именем `image_processor`,
в остальном вы можете менять файлы `CMakeLists.txt` как угодно.

Для отправки кода проекта используйте ветку `projects/image_processor`.

Статус проекта не будет отображаться на сайте https://cpp-hse.ru, поэтому после загрузки решения
вам надо будет самостоятельно создать MR, назначить семинариста ревьюером и попросить его проверить ваш код.

### Принципы начисления баллов

Минимальная реализация проекта оценивается в **3 балла** и должна содержать:
- Класс для представления цвета
- Класс для представления изображения
- Классы или функции для загрузки изображения из формата BMP и сохранения изображения в BMP
- Один класс фильтра

Решения, не удовлетворяющие требованиям к минимальной реализации, оцениваются в 0 баллов.

Если решение удовлетворяет требованиям к минимальной реализации, дополнительно начисляется
0.6 балла за каждый реализованный базовый фильтр (кроме входящего в минимальную реализацию). Таким образом,
за фильтры можно получить еще до **3 баллов**.

Если реализовано не менее 5 фильтров и фильтры образуют полную иерархию наследования,
начисляется еще **2 балла**.

За реализованный дополнительный фильтр начисляется **1 балл**. Дополнительный фильтр можно сдавать,
если реализовано не менее 5 базовых фильтров.

За покрытие юнит тестами всех критичных компонентов начисляется **1 балл**.
Ваш семинарист поможет с определением достаточности покрытия.

Баллы могут быть сняты за серьезные недочеты, например:
- Отсутствие или неверную декомпозицию на файлы, классы, методы и функции
- Утечки памяти
- Падение программы
  - на файлах неверного формата
  - при вызове фильтров с некорректными аргументами
  - при вызове некорректных фильтров
- Неверный результат работы фильтров
- Нечитаемый код
- Нарушение стиля кодирования
- UB на каком-либо входе или наборе аргументов функции
- Выбор неэффективных структур данных или их неэффективное использование
- Лишние копирования объектов
- Неверные сигнатуры методов

## Дедлайн

Для проекта установлен **жесткий** дедлайн `23:59 27.03.2022` - это означает, что решения,
отправленные после этого времени, не будут оцениваться.

Дополнительных штрафов за время сдачи нет.
#� �i�m�a�g�e�_�p�r�o�c�e�s�s�o�r�
�
�

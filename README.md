# Введение
Проектная работа по предмету Конструирование программного обеспечения - Адаптер нейроинтерфейса. 

Группа: 3530904/70101

Студенты: Аверин Л.В, Альмухаметов Р.У, Се Чжуан 

# Описание
Язык: C++ с использованием Qt 
Данный проект представляет собой реализацию адаптера нейроинтерфейса. Сигнал с классификатора ЭЭГ (внешняя зависимость, тестовый эмулятор представлен в виде TestSender.exe) поступает программу по протоколу TCP/IP и в зависимости от этого сигнала происходит нажатие клавиш или движение мышью, заданное пользователем изначально. Всего доступно 4 вида различных действий. Данное ПО позволяет осуществлять управление ПК без использования клавиатуры и мыши. 

# Тестирование 

В проекте настроены действия на сигналы 44, 3, 10, 12. Тестовый эмулятор отправлет только 0, 44, 4. 
То есть действие должно происходить только когда эмулятор отправляет сигнал 44, что соответствует первому пункту в ComboBox. При стандартных настройках эмилируется нажатие клавиш s t o l и enter, что можно увидеть например открыв блокнот. 

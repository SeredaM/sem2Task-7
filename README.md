# sem2Task-7
Создал
Расчеты моделирования
1) поступление заявок: a1=0 a2=2
обработка АО1: b1=0 b2=4
обработка АО2: c1=0 c2=2
при поступлении 1000 заявок примерно 600 из них попадают в АО1 и 400 в АО2 (минуя очередь в АО1). В таком состоянии время обработки заявок в АО1 600*2=1200 е.в, в АО2 400*1 = 400 е.в. Время моделирования определяется очередью AO1, оно будет примерно 1200 (программа выдает 1134)
2) поступление заявок: a1=0 a2=2
обработка АО1: b1=0 b2=2
обработка АО2: c1=0 c2=4
при поступлении 1000 заявок примерно 600 из них попадают в АО1 и 400 в АО2 (минуя очередь в АО1). В таком состоянии время обработки заявок в АО1 600*1=600 е.в, в АО2 400*2 = 800 е.в. Время моделирования определяется очередью AO2, причем в AO2 поступят еще 600 заявок из АО1. Тогда время моделирования будет примерно 800+600*2=2000 (программа выдала 2000.6)

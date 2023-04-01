# Scientific-Calculator
Scientific calculator project using Atmega328p

This project is running at my free time, which is lower than I would like. 
The ideas to implement:
* Keyboard (implemented)
* Reverse Polonese Notation mode (implemented) [https://en.wikipedia.org/wiki/Reverse_Polish_notation or https://pt.wikipedia.org/wiki/Nota%C3%A7%C3%A3o_polonesa_inversa]
* Basic scientific calculations (implemented)
* Simple Matrix Solver (implemented)
* Integrator (under implementation)
* Derivator (under implementation)
* Complex Number arithmetics (under implementation)
* Lagrange Interpolation (under implementation)
* To store or send/receive data to/from external device (under implementation)
* Equations expression solver (maybe will not be possible)
* Plot graphics into .txt file in SD card (possible but little hard to implement)

Now the project is at the 5th attempt, and up to achieve new possibilities.
The first prototype, called Pinnacle I is showed bellow.
It is pushed by a 3.7v Litium Battery (model 18650), contain 40 buttons + reset push button and Power switch, and has a 16x2 characters LCD screen with backlight.
It's in RPN mode with a array up to 20 numbers. Has a Rectangular to Polar converter such as is able to sum, subtract, multplicate, divide and elevate Complex Numbers.
Also it's able to solver Linear systens discribed as Matrix with variable order (single root per variable).
The values can be showed in fix, scientific and engeenering notation.

Now I am developing Complex Numbers Matrix Solver in parallel to methods to achive complex roots from given equations (from family version 4. and 5.).
![imagem2](https://github.com/PJbourne/Scientific-Calc-avr/blob/main/WhatsApp%20Image%202023-04-01%20at%2012.48.39.jpeg)


Bellow, is following the last version, yet in breadboard.


At this 4th model, version 1.2.1, it's possible to use a 31 buttons kayboard without loss of IOs. There are yet four IOs up to be used for other porpuses [digital 0 (Rx), 1 (Tx), 2, 3, 4, and 13 (Sck)].
The stack in the code actually has twenty positions, what can be improved.
It's still possible to add others stacks, or maybe to create a matrixial representation system, matrixial solver, etc. The sky is the limit (I mean, the memory).

![imagem2](https://github.com/PJbourne/Scientific-Calc-avr/blob/main/20220701_153534.jpg)

![imagem2](https://github.com/PJbourne/Scientific-Calc-avr/blob/main/20220701_153918.jpg)



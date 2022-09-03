# Raccoon's Alternative PIO for RC6502

## Features (wo/ HW Mod)
- <code>beginClassic()</code> should be called in <code>setup()</code>.

```c++
void setup(void)
{
  RC6502Pio.beginClassic();
}
```

- ISR and State Pattern based 'KBD_READY' handling.

<img src="https://www.plantuml.com/plantuml/svg/ZP91IuT044Vl-odcV_iR617K8J14wo1AYHqyH2nhEzhGkiew7lhs9T5ftV3wuxstXvrqOULu7OqG1di6di3HyC6WoU4xqsI5UBruWpY-1ocR_FRcwhhiz0iNsg3m5jZ3u0u-EtqfQSdMlaVtECxyTOuEsAqZtlHJmFTGBw282yjYRmp1V--HPKQtpYoFwVLaJ6vGkP-0v-zn_nOq3SJADAZqkIwUP9azoBng8ZWbK3stmMJW0uAvv3SdKhHwEuDl"/>

## Features (w/ HW Mod)
- <code>begin()</code> should be called in <code>setup()</code>.

```c++
void setup(void)
{
  RC6502Pio.begin();
}
```

- CSV based 'Program Loader'. You can load 'HEX' files from the storage (micro-sd).
- Built-in 1MHz Clock Generator (not PIN6. PIN9 is used instead of it.)

## HW Modification
- Remove 'X14' - 1MHz Clock Oscillator
- Short or Connect using a small register (10Ohm is used) between 'PIN 6' and 'PIN 9' of Arduino.
- Connect Micro-SD card module uisng a 'SPI' interface.
  - 'PIN 7' is used for 'CS'
- Pictures
  - WIP...

## Screenshots
![RC6502-00](./images/rc6502-00.png)

![RC6502-00](./images/rc6502-01.png)

![RC6502-00](./images/rc6502-02.png)

![RC6502-00](./images/rc6502-04.png)

![RC6502-00](./images/rc6502-03.png)

![RC6502-00](./images/rc6502-05.png)

![RC6502-00](./images/rc6502-06.png)

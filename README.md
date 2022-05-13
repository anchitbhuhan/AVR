# Timers
     Timers are used everywhere. Without timers, you would end up nowhere! The range of timers vary from a few microseconds (like the ticks of a processor) to many hours (like the lecture classes :( ), and AVR is suitable for the whole range! AVR boasts of having a very accurate timer, accurate to the resolution of microseconds! This feature makes them suitable for timer applications.
     Let’s see how.
     
     You come across timers everyday. Simplest example hangs on your wall or maybe tied around your wrist. You can say that they have a unique property to measure time. Everything in this world is synchronized with time. You wake up at, say, 6 o’clock; you work everyday for 8 hours; you need to drink water every 4 hours, etc. But the concept of timers isn’t confined to your daily routines. Every electronic component works on a time base. This time base helps to keep all the work synchronized. Without a time base, you would have no idea as to when to do a particular thing.
     
     Thus, timers is an important concept in the field of electronics. You can generate a time base using a timer circuit, using a microcontroller, etc. Since all the microcontrollers work at some predefined clock frequency, they all have a provision to set up timers.
     
     AVR boasts of having a timer which is very accurate, precise and reliable. It offers loads of features in it, thus making it a vast topic. In this tutorial, we will discuss the basic concepts of AVR Timers. We will not be dealing with any code in this tutorial, just the concepts. The procedure of generating timers and their codes will be discussed in subsequent posts.
     
## Timers as registers
     So basically, a timer is a register, but not a normal one. The value of this register increases/decreases automatically. In AVR, timers are of 2 types - 8 bit and 16 bit. In an 8 bit timer, the register used for counting is 8 bits whereas in 16 bit the register used for counting is 16 bits.
     Therefore the 8 bit timer can count from 0-255 and 16 bit timer can count from 0-65535. Due to this feature, timers are also called counters. When the value of these register reaches max value, it return to its initial value of 0. At this point we say that the timer/counter has overflowed.
     
     
     In ATMEGA32 and 16 , there are 3 timers
      - TIMER0
      - TIMER1
      - TIMER2
      The best part is that the timer is totally independent of the CPU. Thus, it runs parallel to the CPU and there is no CPU’s intervention, which makes the timer quite accurate.
      Apart from normal operation, these three timers can be either operated in normal mode, CTC mode or PWM mode. We will discuss them one by one.
      
## Timer Concepts
### Time Period = 1 / Frequency
    Now suppose, we need to flash an LED every 10 ms. This implies that its frequency is 1/10ms = 10Hz. Now let's assume that we have an external crystal of 4MHz. Hence the CPU frequency is said to be 4MHz.
    The value in the counter register increments with each clock pulse. Since the XTAL = 4MHz, therefore time period for 1 pulse = 1/4MHz = 0.00025ms. So the time it takes for increasing counter value from 1 to 2 or 2 to 3 ..so on is 0.00025ms.
    
    Q) How much time does it take for the overflow to occur in case of 8 bit timer?
    Ans- 256*0.00025ms = 0.0615ms
    
    Q) How much we have to count to get a delay of 10ms ?
    Ans- 0.00025ms  ---------------> 1 count
         1ms        ---------------> 1/0.00025 count
         10ms       ---------------> 1*10/0.00025 = 40000 counts
         
         40000 - 1 = 39999 counts
         
         Formula
                - Timer Count = Required Delay
                                ----------------    - 1
                                Clock Time Period
    
    Now to count upto 39999, we cannot use  8 bit timer, since it counts only upto 255, so we have to use 16 bit timer (MAX=65535).
    
2. **Timer0**

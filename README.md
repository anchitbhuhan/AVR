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
#### The Prescaler
     Q) What is the maximum delay that can be achieved using 8 bit and 16 bit timer, given XTAL = 4MHz ?
     Ans - for 8 bit
                    255 = Delay
                         -------    - 1
                         4MHz
                    
                    256*1
                    ------ seconds   = Max Delay
                    4 x 10^6
                    
                    0.000064  = Max Delay
                    
                    Max Delay = 0.064ms
           for 16 bit
                    65535 =  Delay
                            -------    - 1
                             4MHz
                    
                    65535*1
                    ------ seconds   = Max Delay
                    4 x 10^6
                    
                    0.01638375  = Max Delay
                    
                    Max Delay = 16.4ms
           
           What if we need more delay than 16.4ms ???
           
           We can try to decrease the XTAL Value
           
           4MHz ------------> 3MHz
           
           for 16 bit
                     65535 =  Delay
                            -------    - 1
                             3MHz
                    
                    65535*1
                    ------ seconds   = Max Delay
                    3 x 10^6
                    
                    0.021845  = Max Delay
                    
                    Max Delay = 21.8ms
            
            4MHz ------------> 2MHz
           
            for 16 bit
                     65535 =  Delay
                            -------    - 1
                             2MHz
                    
                    65535*1
                    ------ seconds   = Max Delay
                    2 x 10^6
                    
                    0.0327675  = Max Delay
                    
                    Max Delay = 32.7ms
          
         So as we decrease the XTAL, we can achieve greater delay.
         
         But we cannot simply decrease the XTAL frequency, that is a hardware property.
         So we use Prescalers.
         
         
         We do not reduce the actual F_CPU. The actual F_CPU remains the same (at 4 MHz in this case). So basically,
         we derive a frequency from it to run the timer.
         
         Thus, while doing so, we divide the frequency and use it. There is a provision to do so in AVR by setting some bits which we will discuss later.
           
         But don’t think that you can use prescaler freely. It comes at a cost. There is a trade-off between resolution and duration. As you must have seen above, the          overall duration of measurement has increased from a mere 16.384 ms to 131.072 ms. So has the resolution. The resolution has also increased from 0.00025 ms to          0.002 ms (technically the resolution has actually decreased). This means each tick will take 0.002 ms. So, what’s the problem with this? The problem is that            the accuracy has decreased. Earlier, you were able to measure duration like 0.1125 ms accurately (0.1125/0.00025 = 450), but now you cannot (0.1125/0.002 =            56.25). The new timer can measure 0.112 ms and then 0.114 ms. No other value in between.
         
 
 ## Choosing Prescalers
         Let’s take an example. We need a delay of 184 ms (I have chosen any random number). We have F_CPU = 4 MHz. The AVR offers us the following prescaler values to          choose from: 8, 64, 256 and 1024. A prescaler of 8 means the effective clock frequency will be F_CPU/8. Now substituting each of these values into the above            formula, we get different values of timer value. The results are summarized as below:
         
         Case 1 : Prescaler = 8
                  
                  Effective Freq = 4MHz/8 = 500KHz.
                  
                  Count = Delay
                         -------   - 1
                         Clock_Freq
                         
                        = 184ms
                          ------    -1 
                          500KHz
                        = 184 * 10^-3 * 500 * 10 ^ 3  - 1
                        = 184*500 - 1
                        = 92000 - 1
                        = 91999 timer counts
           
          Case 2 : Prescaler = 64
                  
                  Effective Freq = 4MHz/64 = 62.5KHz.
                  
                  Count = Delay
                         -------   - 1
                         Clock_Freq
                         
                        = 184ms
                          ------    -1 
                          62.5KHz
                        = 184 * 10^-3 * 62.5 * 10 ^ 3  - 1
                        = 184*62.5 - 1
                        = 11500 - 1
                        = 11499 timer counts
                        
           Case 3 : Prescaler = 256
                  
                  Effective Freq = 4MHz/256 = 15.625KHz.
                  
                  Count = Delay
                         -------   - 1
                         Clock_Freq
                         
                        = 184ms
                          ------    -1 
                          15.625KHz
                        = 184 * 10^-3 * 15.625 * 10 ^ 3  - 1
                        = 184*15.625 - 1
                        = 2875 - 1
                        = 2874 timer counts
                        
             Case 4 : Prescaler = 1024
                  
                  Effective Freq = 4MHz/1024 = 3906.25Hz.
                  
                  Count = Delay
                         -------   - 1
                         Clock_Freq
                         
                        = 184ms
                          ------    -1 
                          3906.25Hz
                        = 184 * 10^-3 * 3906.25   - 1
                        = 184*3906.25*10^-3 - 1
                        = 718.750 - 1
                        = 717.750 timer counts
                        
               Now out of these four prescalers, 8 cannot be used as the timer value exceeds the limit of 65535. Also, since the timer always takes up integer values,                we cannot choose 1024 as the timer count is a decimal digit. Hence, we see that prescaler values of 64 and 256 are feasible. But out of these two, we                  choose 64 as it provides us with greater resolution. We can choose 256 if we need the timer for a greater duration elsewhere.

               Thus, we always choose prescaler which gives the counter value within the feasible limit (255 or 65535) and the counter value should always be an                      integer.
                  
 ### Interrupts
          Well, this is not exclusively related to timers, but I thought of discussing it as it is used in a variety of places. Let me explain it using an analogy. Say           now you are reading my post. It’s dinner time and your mom (only if you live with your mom ;)) calls you for dinner. What do you do (if she gets too creepy)?           You save your work and attend to your mom’s call, then return and resume reading. This is an example of interrupt.

          In most microcontrollers, there is something called interrupt. This interrupt can be fired whenever certain conditions are met. Now whenever an interrupt is           fired, the AVR stops and saves its execution of the main routine,  attends to the interrupt call (by executing a special routine, called the Interrupt                 Service Routine, ISR) and once it is done with it, returns to the main routine and continues executing it.

          For example, in the condition of counter overflow, we can set up a bit to fire an interrupt whenever an overflow occurs. Now, during execution of the                   program, whenever an overflow occurs, an interrupt is fired and the CPU attends to the corresponding ISR. Now it’s up to us what do we want to do inside the           ISR. We can toggle the value of a pin, or increment a counter, etc etc.

          If you didn’t get the concept of interrupts and ISR, behold for sometime till we discuss it how to implement it in hardware.

          So folks, I guess this much is enough for you to get a hold of what timers are and the features of AVR Timers. From the next post, we will implement these             concepts and learn how to code the AVR!

2. **Timer0**
     Let’s define a problem statement for us. The simplest one being the LED flasher. Let’s say, we need to flash an LED every 6 ms and we are have a CPU clock frequency of 32 kHz.
          
          Timer Count =        Required Delay
                                ----------------    - 1
                                Clock Time Period
                                
          Timer Count =         6ms
                              -----------------    -1
                              32 KHz
                      
                      =      6 * 10^-3 * 32 * 10^3 - 1
                      =      191
          
          We can achieve this count by using 8 bit register since it can count maximum upto 255.
          
          
      #### TCNT0 Register
          This is the 8 bit counter register. The value stored in this register increase/decreases automatically. 
          
          But this register won’t be activated unless we activate the timer! Thus we need to set the timer up. How?
          
      #### TCCR0 Register
          
               FOCO      WGM00     COM01     COM00     WGM01     CS02      CS01      CS00
               
               
               
               CS02      CS01      CS00           Description
               0         0         0              No Clock Source(Timer/Counter Stopped)
               0         0         1              clk(No Prescaling)
               0         1         1              clk/8(From Prescaler)
               1         0         0              clk/64(From Prescaler)
               1         0         1              clk/256(From Prescaler)
               1         1         0              clk/1024(From Prescaler)
               1         1         0              External Clock Source on T0 Pin. Clock on Falling Edge
               1         1         1              External Clock Source on T0 Pin. Clock on Rising Edge
               
               
               For Choosig No Prescaling, we set TCCR0 as
               
               TCCR0 |= (1 << CS00);
               
               Please note that if you do not initialize this register, all the bits will remain as zero and the timer/counter will remain stopped.
               
               
               https://maxembedded.wordpress.com/2011/06/10/port-operations-in-avr/
               
               Code to generate 6ms delay. [[code]](https://github.com/anchitbhuhan/AVR/blob/main/timer0_6ms.c)
               
               
       Now let’s change the above problem statement to the following. We need to flash an LED every 8 ms and we have an XTAL of 16 MHz. Well, 8 ms is still low, but it’s good enough for the following illustration.
       
               
            case 1 : No Prescalar
               Timer Count =        Required Delay
                                ----------------    - 1
                                Clock Time Period
                                
                            =      8ms
                                -----------    -1
                                16MHz
                            =  8 * 10^-3 * 16*10^6 -1
                            = 128 * 10^3 -1
                            = 127999
           
               case 2 : 16MHz/8 = 2MHz
                    Timer Count =        Required Delay
                                        ----------------    - 1
                                        Clock Time Period
                                
                                 =      8ms
                                     -----------    -1
                                     2MHz
                                 =  8 * 10^-3 * 2*10^6 -1
                                 = 16 * 10^3 -1
                                 = 15999
                                 
                                 
                case 3 : 16MHz/64 = 250KHz
                    Timer Count =        Required Delay
                                        ----------------    - 1
                                        Clock Time Period
                                
                                 =      8ms
                                     -----------    -1
                                      250KHz
                                 =  8 * 10^-3 * 250*10^3 -1
                                 = 2000  -1
                                 = 1999
                 
                 
                 case 4 : 16MHz/256 = 62.5KHz
                    Timer Count =        Required Delay
                                        ----------------    - 1
                                        Clock Time Period
                                
                                 =      8ms
                                     -----------    -1
                                      62.5KHz
                                 =  8 * 10^-3 * 62.5*10^3 -1
                                 = 500  -1
                                 = 499
                   
                  case 4 : 16MHz/1024 = 15625Hz
                    Timer Count =        Required Delay
                                        ----------------    - 1
                                        Clock Time Period
                                
                                 =      8ms
                                     -----------    -1
                                      15625Hz
                                 =  8 * 10^-3 * 15625 -1
                                 = 125000*10^-3  -1
                                 = 124
                            
           We can use 1024 Prescaler.
           
          Code to generate 6ms delay. [[code]](https://github.com/anchitbhuhan/AVR/blob/main/timer0_8ms.c)

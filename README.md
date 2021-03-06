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
          
          
          
          
          
     Now let’s change the problem statement to something you can actually see! Let’s flash an LED every 50 ms (you can surely see the LED flashing this time ;)). We have an XTAL of 16 MHz.
     
          case 1 : No Prescalar
               Timer Count =        Required Delay
                                ----------------    - 1
                                Clock Time Period
                                
                            =      50ms
                                -----------    -1
                                16MHz
                            =  50 * 10^-3 * 16*10^6 -1
                            = 800 * 10^3 -1
                            = 799999
           
               case 2 : 16MHz/8 = 2MHz
                    Timer Count =        Required Delay
                                        ----------------    - 1
                                        Clock Time Period
                                
                                 =      50ms
                                     -----------    -1
                                     2MHz
                                 =  50 * 10^-3 * 2*10^6 -1
                                 = 100 * 10^3 -1
                                 = 99999
                                 
                                 
                case 3 : 16MHz/64 = 250KHz
                    Timer Count =        Required Delay
                                        ----------------    - 1
                                        Clock Time Period
                                
                                 =      50ms
                                     -----------    -1
                                      250KHz
                                 =  50 * 10^-3 * 250*10^3 -1
                                 = 12500  -1
                                 = 12499
                 
                 
                 case 4 : 16MHz/256 = 62.5KHz
                    Timer Count =        Required Delay
                                        ----------------    - 1
                                        Clock Time Period
                                
                                 =      50ms
                                     -----------    -1
                                      62.5KHz
                                 =  50 * 10^-3 * 62.5*10^3 -1
                                 = 3125  -1
                                 = 3124
                   
                  case 4 : 16MHz/1024 = 15625Hz
                    Timer Count =        Required Delay
                                        ----------------    - 1
                                        Clock Time Period
                                
                                 =      50ms
                                     -----------    -1
                                      15625Hz
                                 =  50 * 10^-3 * 15625 -1
                                 = 781250*10^-3  -1
                                 = 780.250
                                 
                                 
                    None of the prescaler seems to work, we have to use interrupts here.
                    
                    
                    The concept here is that the hardware generates an interrupt every time the timer overflows. Since the required delay is greater than the maximum possible delay, obviously the timer will overflow. And whenever the timer overflows, an interrupt is fired. Now the question is how many times should the interrupt be fired?
                    
                    Lets choose prescaler of 256
                              Max delay  = (255+1) * 62.5KHz
                              Max delay = 256/62500
                                        = 0.004096
                                        = 4.096ms
                      
                      
                      
                      50ms / 4.096ms = 12.207
                      
                      Thus the timer has to overflow 12 times(12*4.096 = 49.152ms), 
                      Remaining time = 50-49.152 = 0.848ms
                      
                      remaining counr = 0.848ms/62.5KHz -1
                                     = (0.848 * 10^-3 * 62.5 * 10^-3) -1
                                     = 53-1
                                     = 52 counts
                                     
                                     we take 53
                        
                                     
               https://github.com/anchitbhuhan/AVR/blob/main/timer0_50ms.c
               
               
               
               
3. **Timer1**
         
         Okay, let’s make it loud and clear. We need to flash an LED every 2 seconds, i.e. at a frequency of 0.5 Hz. We have an XTAL of 16 MHz.
         
         
               XTAL = 16MHz
               
               Prescaler           Max delay
               ______________________________
               No Prescaler        4.096ms
               8                   32.768ms
               
               
               2000ms/32.768ms = 61.035 overflows
               
               We have blink LED after every approx 61 overflows
               
               https://github.com/anchitbhuhan/AVR/blob/main/timer1_1s.c
               
               
               
4. **Timer2**


         In this post, we will discuss about TIMER2. Since TIMER2 is an 8-bit timer (like TIMER0), most of the registers are similar to that of TIMER0 registers. Apart from that, TIMER2 offers a special feature which other timers don’t – Asynchronous Operation. We will discuss about it later.
         
         
         
      In this post, we will discuss about TIMER2. Since TIMER2 is an 8-bit timer (like TIMER0), most of the registers are similar to that of TIMER0 registers. Apart from that, TIMER2 offers a special feature which other timers don’t – Asynchronous Operation. We will discuss about it later.
      
      
      Same as Timer0
      
      


## CTC Mode

Timer0

          So till now, we have dealt with the basic concepts. We had two timer values with us – Set Point (SP) and Process Value (PV). In every iteration, we used to compare the process value with the set point. Once the process value becomes equal (or exceeds) the set point, the process value is reset. The following code snippet explains it:
          
          
          max = 39999;   // max timer value set  <--- set point

// some code here
// ...
// ...
// ...

// TCNT1 <--- process value
if (TCNT1 >= max)   // process value compared with the set point
{
    TCNT1 = 0;      // process value is reset
}

// ...



Here, we have used the example of TIMER1. Since TIMER1 is a 16-bit timer, it can count upto a maximum of 65535. Here, what we desire is that the timer (process value) should reset as soon as its value becomes equal to (or greater than) the set point of 39999.


So basically, the CTC Mode implements the same thing, but unlike the above example, it implements it in hardware. Which means that we no longer need to worry about comparing the process value with the set point every time! This will not only avoid unnecessary wastage of cycles, but also ensure greater accuracy (i.e. no missed compares, no double increment, etc).

Hence, this comparison takes place in the hardware itself, inside the AVR CPU! Once the process value becomes equal to the set point, a flag in the status register is set and the timer is reset automatically! Thus goes the name – CTC – Clear Timer on Compare! Thus, all we need to do is to take care of the flag, which is much more faster to execute.

Let us analyze this CTC Mode in detail with the help of a problem statement



Let’s take up a problem statement to understand this concept. We need to flash an LED every 100 ms. We have a crystal of XTAL 16 MHz.


Now, given XTAL = 16 MHz, with a prescaler of 64, the frequency of the clock pulse reduces to 250 kHz. With a Required Delay = 100 ms, we get the Timer Count to be equal to 24999. Up until now, we would have let the value of the timer increment, and check its value every iteration, whether it’s equal to 24999 or not, and then reset the timer. Now, the same will be done in hardware! We won’t check its value every time in software! We will simply check whether the flag bit is set or not, that’s all. Confused, eh? Well, don’t worry, just read on! 😉


TCCR0

FOCO    WGM00   COM01   COM00   WGM01   CS02    CS01    CS00

In order to program timer0 in CTC mode, we need to program bits WGM00 and WGM01
to 0 and 1

TCCR0 |= (1 << WGM01)

TIFR

OCF2    TOV2    ICF1    OCF1A   OCF1B   TOV1    OCF0    TOV0

When the compare occurs this OCF0 flag is set. So we need to observe this flag.

IN CTC mode, in the TCNT0 we are going to load 0
In OCR0 , the desired value is loaded.

When a compare occurs between TCNT0 and OCR0, OCF0 flag is set.

Q) Assuming that XTAL = 8MHz. Write a program to generate a square wave with a period of 2ms in pin PB3.


        <---1ms---->
         ________           ________
        |        |         |        |
        |        |         |        |
        |        |         |        |
--------         ----------         ----------
        <-------2ms--------->



Use Prescaler = 64

Required delay = 1ms

count =  1ms
        -----   -  1
        125KHz
count = 125 -1 = 124

https://github.com/anchitbhuhan/AVR/blob/main/timer0_square_wave_ctc.c


**Timer 1 CTC**
https://github.com/anchitbhuhan/AVR/blob/main/timer1_square_wave_ctc.c




## Using Interrupts with CTC Mode

In the previous methodology, we simply used the CTC Mode of operation. We used to check every time for the flag bit (OCF1A). Now let’s shift this responsibility to the AVR itself! Yes, now we do not need to check for the flag bit at all! The AVR will compare TCNT1 with OCR1A. Whenever a match occurs, it sets the flag bit OCF1A, and also fires an interrupt! We just need to attend to that interrupt, that’s it! No other headache of comparing and stuffs!

There are three kinds of interrupts in AVR – overflow, compare and capture. We have already discussed the overflow interrupt in previous posts. For this case, we need to enable the compare interrupt. The following register is used to enable interrupts.

We have already come across TOIE1 bit. Now, the Bit 4:3 – OCIE1A:B – Timer/Counter1, Output Compare A/B Match Interrupt Enable bits are of our interest here. Enabling it ensures that an interrupt is fired whenever a match occurs. Since there are two CTC channels, we have two different bits OCIE1A and OCIE1B for them.

Thus, to summarize, whenever a match occurs (TCNT1 becomes equal to OCR1A = 24999), an interrupt is fired (as OCIE1A is set) and the OCF1A flag is set. Now since an interrupt is fired, we need an Interrupt Service Routine (ISR) to attend to the interrupt. Executing the ISR clears the OCF1A flag bit automatically and the timer value (TCNT1) is reset.


Timer 0



Timer 1
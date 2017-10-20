int sense; 				//to observe and calibrate system
int sense2;
int sense3;
int c=0; 				//classification variable
int ppl1=0;                             //to count number of people in room1    
int ppl2=0;				//to count number of people in room2

void setup() 				
{
  pinMode(A0, INPUT);
  pinMode(A1,INPUT);
  pinMode(A2,INPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  digitalWrite(7,1);
  digitalWrite(8,1);
  digitalWrite(9,1);
  digitalWrite(10,1);
  Serial.begin(9600);
}

void display()			
{Serial.print("sense=");
 Serial.print(sense);
 Serial.print("\t");
 Serial.print("sense2=");
 Serial.print(sense2);
 Serial.print("\t");
 Serial.print("sense3=");
 Serial.print(sense3);
 Serial.println();
}

void yug_room_off()
{
  digitalWrite(9,1);
  digitalWrite(10,1);
  }

void yug_room_on()
{
  digitalWrite(9,0);
  digitalWrite(10,0);
  }

void sak_room_off()
{
  digitalWrite(7,1);
  digitalWrite(8,1);
  }

void sak_room_on()
{
  digitalWrite(7,0);
  digitalWrite(8,0);
  }

  


void loop() 
{
  sense= analogRead(A0);
  sense2=analogRead(A1);
  sense3=analogRead(A2);
  display();
   if (sense<900 or sense2<900 or sense3<900)
  {
    if (sense<900)
    {   
        while(sense<900)sense=analogRead(A0);
        while(sense2>900 and sense3>900)
        { 
          sense2=analogRead(A1);
          sense3=analogRead(A2);
          sense=analogRead(A0);
          display();
          if(sense<900)
          {break;}
        }  
        if(sense<900);
        else{
        if(sense2<900)
        {                                         //out of first into lobby
        while(sense2<910)
        {
          sense2=analogRead(A1);
          display();
        }
        ppl1--;
        if(ppl1==0)
        {
        sak_room_off();
        }
        }
        if(sense3<900)
        {
                                 //out of first into second
          while(sense3<900)
          { sense3=analogRead(A2);
            display();
          }
          ppl1--;
          ppl2++;          
          if(ppl1==0)
          {
          sak_room_off();
          }
          yug_room_on();

        }
    }
    }
   
    else if(sense3<900)
    {
      while(sense3<900){sense3=analogRead(A2); display();}
      while(sense>900 and sense2>900)
      {
        sense=analogRead(A0);
        sense2=analogRead(A1);
        sense3=analogRead(A2);
        display();
        if(sense3<900)
        break;        
      }
      if(sense3<900);
      else{
        if(sense<900)
         {//from room2 to room1
        while(sense<900)
        {
          sense=analogRead(A0);
          display();
         }
        ppl2--;
        ppl1++;
        if(ppl2==0)
        {         
        yug_room_off();
        }
        sak_room_on();

      }
      if(sense2<900)
      {//from room2 to lobby
        while(sense2<900)
        {
          sense2=analogRead(A1);
          display();
        } 
        ppl2--;
        if(ppl2==0)
        {
        yug_room_off();
        }
      }
          
    }
    }
     else if (sense2<900)
    {while(sense2<900 ){sense2=analogRead(A1); display();}
      while(sense>900 and sense3>900)
      { 
        sense=analogRead(A0);
        sense2=analogRead(A1);
        sense3=analogRead(A2);
        display();
        if(sense2<900)
        {break;}
     }
     if (sense2<900);
     else{
      if(sense<910)
      {//from lobby to room1
     while(sense<910 )
        {
          sense=analogRead(A0);
          display();
        }
        sak_room_on();
        ppl1++; 
    }
    if(sense3<900)
    {//from lobby to room2
      while(sense3<900)
      {
        sense3=analogRead(A2);
        display();
      }
      yug_room_on();
      ppl2++;
    } 
    }
    }
  }
  delay(50);
  
}

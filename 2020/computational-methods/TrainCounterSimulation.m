function s = TrainCounterSimulation()
%Initialize ticket information table   
tkt_type1 = [20,40,35];
tkt_type2 = [50,20,30];
tkt_type3 = [30,40,35];
days = [1,2,3];

%Initialize service table   
svc_time = [1,2,3,4,5,6];
svc_prob = [0.10,0.10,0.30,0.25,0.10,0.15];
svc_cdf = [0.10,0.20,0.50,0.75,0.85,1];
svc_range1 = [1,11,21,51,76,86];
svc_range2 = [10,20,50,75,85,100];

%Initialize inter-arrival table   
intarr_time = [1,2,3,4,5,6,7,8];
intarr_prob = [0.20,0.10,0.10,0.20,0.10,0.10,0.05,0.15];
intarr_cdf = [0.20,0.30,0.40,0.60,0.70,0.80,0.85,1];
intarr_range1 = [1,21,31,41,61,71,81,86];
intarr_range2 = [20,30,40,60,70,80,85,100];

%Initialize ticketslot table   
tkt_slot = [1,2,3];
tkt_prob = [0.30,0.50,0.20];
tkt_cdf = [0.30,0.80,1];
tkt_range1 = [1,31,81];
tkt_range2 = [30,80,100];


%Initialize ticketype table   
tkt_type_num = [1,2,3];
tkt_type_prob = [0.40,0.20,0.40];
tkt_type_cdf = [0.40,0.60,1];
tkt_type_range1 = [1,41,61];
tkt_type_range2 = [40,60,100];

%Initialize tickeamount table   
tkt_amt_num = [2,3,4];
tkt_amt_prob = [0.40,0.20,0.40];
tkt_amt_cdf = [0.40,0.60,1];
tkt_amt_range1 = [1,41,61];
tkt_amt_range2 = [40,60,100];
price= [20,30,40];
%Variables
svc_times=[];
cust_rn =[];
cust_number=[];
intarr_arr_time=[];
tkt_slot_day=[];
tkt_type=[];
tkt_amt=[];
total_paid=[];
%Get user inputs
cust_num = input ('Enter the number of customer: '); 

disp(' ') 

disp('--------------------------') 
disp(' TYPE OF RANDOM GENERATOR ')
disp('--------------------------') 
disp('1.Uniformly distributed integers')
disp('2.LCG ')
disp('3. ')

disp(' ')

d=3;
rand_type = input ('Select the type of random generator: '); 

%Random Number for Slot, Inter and Type from selected generator
if rand_type == 1
    intarr_rn = floor(1+ (100-1).*rand(cust_num,1));
    slot_rn = floor(1+ (100-1).*rand(cust_num,1));
    type_rn = floor(1+ (100-1).*rand(cust_num,1));
    svc_rn = floor(1+ (100-1).*rand(cust_num,1));
    amount_rn =  floor(1+ (100-1).*rand(cust_num,1));

end
if rand_type == 2
    disp('TYPE 2')
    
end

k=1;
%Mapping
for k=1:cust_num
for i=1:6
       if (svc_rn(k) >= svc_range1(i) & svc_rn(k) <= svc_range2(i))
           svc_times(k)=i;
       end
       
end
end
for k=1:cust_num
for i=1:3
       if (amount_rn(k) >= tkt_amt_range1(i) & amount_rn(k) <= tkt_amt_range2(i))
           tkt_amt(k)=tkt_amt_num(i);
           total_paid(k)=price(i);
       end
       
end
end
       
       disp('Amount')

       disp(tkt_amt)
for k=2:cust_num
for i=1:8
       if (intarr_rn(k) >= intarr_range1(i) & intarr_rn(k) <= intarr_range2(i))
       intarr_arr_time(k)=i;
       end
       
end
end
       disp('Inter')

       disp(intarr_arr_time)
       
for k=1:cust_num
for i=1:3
       if (slot_rn(k) >= tkt_range1(i) & slot_rn(k) <= tkt_range2(i))
       tkt_slot_day(k)=i;
       end
       
end
end
       disp('Slot')

       disp(tkt_slot_day)
for k=1:cust_num
for i=1:3
       if (type_rn(k) >= tkt_type_range1(i) & type_rn(k) <= tkt_type_range2(i))
           tkt_type(k)=i;
       end
       
end
cust_number(k)=k;
end
       disp('Type')

       disp(tkt_type)
       
%Get arrival time
arrival_time = [];
total_arr=0;
for i=1:cust_num
    total_arr=total_arr+intarr_arr_time(i);
    arrival_time(i)=total_arr;
end
disp('                                      TABLE OF TICKETS INFORMATION                                                                ') 
disp('------------------------------------------------------------------------------------------------------') 
disp(' Day/slot    |    Total ticket type 1    |     Total ticket type 2       |    Total ticket type 3       |')   
disp('------------------------------------------------------------------------------------------------------') 
for i=1:length(days)
printf('   %d                 %d                              %d                             %d\n',days(i), tkt_type1(i), tkt_type2(i), tkt_type3(i))
end
disp('------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 

disp('                                      TABLE OF SERVICE TIME                                                                ') 
disp('------------------------------------------------------------------------------------------------------') 
disp(' Service time    |    Probability    |         CDF             |              Range                   |                     ') 
disp('------------------------------------------------------------------------------------------------------') 
for i=1:length(svc_time)
    printf('   %d                       %.2f                  %.2f                         %d-%d\n',svc_time(i), svc_prob(i), svc_cdf(i), svc_range1(i),svc_range2(i))
end
disp('------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 

disp('                                      TABLE OF INTER-ARRIVAL TIME                                                               ') 
disp('------------------------------------------------------------------------------------------------------') 
disp(' Inter arrival time    |    Probability    |         CDF             |              Range             |                           ') 
disp('------------------------------------------------------------------------------------------------------') 
for i=1:length(intarr_time)
 printf('   %d                           %.2f                  %.2f                         %d-%d\n',intarr_time(i), intarr_prob(i), intarr_cdf(i), intarr_range1(i),intarr_range2(i))
end
disp('------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 

disp('                                      TABLE OF TICKET SLOT                                                             ') 
disp('------------------------------------------------------------------------------------------------------') 
disp(' Ticket slot/day    |    Probability    |         CDF             |              Range               |                         ') 
disp('------------------------------------------------------------------------------------------------------') 
for i=1:length(days)
    printf('   %d                         %.2f                  %.2f                         %d-%d\n',tkt_slot(i), tkt_prob(i), tkt_cdf(i), tkt_range1(i),tkt_range2(i))
end
disp('------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 

disp('                                      TABLE OF TICKET TYPE                                                            ') 
disp('------------------------------------------------------------------------------------------------------') 
disp(' Ticket type    |    Probability    |         CDF             |              Range                    |                    ') 
disp('------------------------------------------------------------------------------------------------------') 
for i=1:length(days)
    printf('   %d                          %.2f                  %.2f                         %d-%d\n',tkt_type_num(i), tkt_type_prob(i), tkt_type_cdf(i), tkt_type_range1(i),tkt_type_range2(i))
end
disp('------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 

disp('                                      TABLE OF TICKET AMOUNT AND PRICE                                                           ') 
disp('----------------------------------------------------------------------------------------------------------------') 
disp(' Quantity    |    Probability    |         CDF             |              Range             |          Price    |      ') 
disp('----------------------------------------------------------------------------------------------------------------') 
for i=1:length(days)
    printf('   %d                 %.2f                  %.2f                         %d-%d                    %d\n',tkt_amt_num(i), tkt_amt_prob(i), tkt_amt_cdf(i), tkt_amt_range1(i),tkt_amt_range2(i),price(i))
end
disp('----------------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 
disp('Service')
disp(svc_times)
%Q Simulation
%Busy = 1, not busy = 0
counter_required=0;
overllaped = 0;
counter1_spent=[];
counter1_waiting=[];
counter1_begin=[];
counter1_begin(1)=0;
counter1_end=[];
counter1_end(1)=svc_times(1);
counter1_svc_rn=[];
counter1_svc_rn(1)=svc_rn(1);
counter1_service=[];
counter1_service(1)=svc_times(1);
counter1=[];
counter1(1)=1;
counter2_spent=[];
counter2_waiting=[];
counter2_begin=[];
counter2_begin(1)=0;
counter2_end=[];
counter2_end(1)=svc_times(1);
counter2_svc_rn=[];
counter2_service=[];
counter3_spent=[];
counter3_waiting=[];
counter3_begin=[];
counter3_begin(1)=0;
counter3_end=[];
counter3_end(1)=svc_times(1);
counter3_svc_rn=[];
counter3_service=[];
c1=2;
c2=1;
c3=1;
t=2;
counter2=[];
counter2temp=[];
counter3=[];
allcounters_busy = 0;

time_begin1 = [];
time_begin_count=0;
time_end_count=svc_times(1);
time_end1 = [];
q=2;
loop =1;
disp('Counter 1 and Counter 2 are in operation')
fprintf('Arrival of customer number %d at minute %d\n',[cust_number(1),arrival_time(1)])
for k=2:cust_num
     
 for i=q:cust_num
    if (arrival_time(i)<=time_end_count)
        counter2(c2)=i;
        c2=c2+1;
        q=q+1;
        counter_required=counter_required+1;
     
    end
        overllaped = 0;   
 end


    if (q>cust_num)
        break
    end
      
     if (overllaped==0)
        counter1(c1)=q;
        counter1_svc_rn(c1)=svc_rn(q);
        counter1_service(c1)=svc_times(q);
         c1=c1+1;
         overllaped = 1;   
    end
   
    if (time_end_count<arrival_time(q))
    time_end_count=arrival_time(q);
    time_end_count=time_end_count+svc_times(q);
    else
        time_end_count=time_end_count+svc_times(q);
    end
    q=q+1;
end



disp('counter1:');
printf('%d\n',counter1);
disp('counter2:');
printf('%d\n',counter2);

k=1;
time_end_count=0;
for i=1:length(counter1)
    if (arrival_time(counter1(i))<=time_end_count)
        counter1_begin(i)=time_end_count;
    else
        counter1_begin(i)=arrival_time(counter1(i));
    end
    time_end_count=counter1_begin(i)+svc_times(counter1(i));
    if (time_end_count<counter1_begin(i))
        time_end_count=counter1_begin(i)+svc_times(counter1(i));
    end
    counter1_end(k)=time_end_count;
    counter1_spent(k)=time_end_count-arrival_time(counter1(i));
    counter1_waiting(i)=counter1_begin(i)-arrival_time(counter1(i));
    k=k+1;
  
end
g=2;
o=1;
k=1;
time_end_count=arrival_time(counter2(k));
for i=1:length(counter2)
    if (arrival_time(counter2(i))<=time_end_count)
        counter2_begin(i)=time_end_count;
    else
        counter2_begin(i)=arrival_time(counter2(i));
    end
    time_end_count=counter2_begin(i)+svc_times(counter2(i));
    if (time_end_count<counter2_begin(i))
        time_end_count=counter2_begin(i)+svc_times(counter2(i));
    end
    for z=g:length(counter2)
        if (arrival_time(counter2(z))<=time_end_count)
             disp('ttttttt:');
             disp(arrival_time(counter2(z)));
        allcounters_busy=1;
        counter3(o)=counter2(z);
        o=o+1;
        end
    end
    g=g+1;
    k=k+1;
end


same=0;
c=1;
counter2temp=counter2;
for i=1:length(counter3)
    counter2(counter2==counter3(i))=[];
end
counter3=unique(counter3);
g=2;
o=1;
k=1;
time_end_count=arrival_time(counter2(k));
for i=1:length(counter2)
     disp('arrival:')
        disp(arrival_time(counter2(i)))
    if (arrival_time(counter2(i))<=time_end_count)
        counter2_begin(i)=time_end_count;
    else
        counter2_begin(i)=arrival_time(counter2(i));
    end
    time_end_count=counter2_begin(i)+svc_times(counter2(i));
    if (time_end_count<counter2_begin(i))
        time_end_count=counter2_begin(i)+svc_times(counter2(i));
    end
    counter2_svc_rn(i)=svc_rn(counter2(i));
    counter2_service(i)=svc_times(counter2(i));
    counter2_end(k)=time_end_count;
    counter2_spent(k)=time_end_count-arrival_time(counter2(i));
    counter2_waiting(i)=counter2_begin(i)-arrival_time(counter2(i));
   
    g=g+1;
    k=k+1;
  
end


if (allcounters_busy==1)
k=1;
time_end_count=arrival_time(counter3(k));
for i=1:length(counter3)
    if (arrival_time(counter3(i))<=time_end_count)
        counter3_begin(i)=time_end_count;
    else
        counter3_begin(i)=arrival_time(counter3(i));
    end
    time_end_count=counter3_begin(i)+svc_times(counter3(i));
    if (time_end_count<counter3_begin(i))
        time_end_count=counter3_begin(i)+svc_times(counter3(i));
    end
    counter3_svc_rn(i)=svc_rn(counter3(i));
    counter3_service(i)=svc_times(counter3(i));
    counter3_end(k)=time_end_count;
    counter3_spent(k)=time_end_count-arrival_time(counter3(i));
    counter3_waiting(i)=counter3_begin(i)-arrival_time(counter3(i));

    k=k+1;
  
end
end
disp('counter3:');
printf('%d\n',counter3);
disp('                                      RESULTS                                                            ') 
disp('----------------------------------------------------------------------------------------------------------------------------------------------------------------') 
disp(' N | RN-Inter arrival time |  Inter arrival time  |  Arrival time |  RN-Ticket slot  | Ticket slot | RN-Ticket type | Ticket type | Tickets bought | Total paid') 
disp('----------------------------------------------------------------------------------------------------------------------------------------------------------------') 
for i=1:cust_num
printf('%2d         %2d                   %2d                      %2d                  %2d            %2d              %2d                %2d               %2d           %d\n',i, intarr_rn(i), intarr_arr_time(i),arrival_time(i),slot_rn(i),tkt_slot_day(i),type_rn(i),tkt_type(i),tkt_amt(i),total_paid(i))
end
disp('----------------------------------------------------------------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 

disp('                                      COUNTER 1                                                            ') 
disp('------------------------------------------------------------------------------------------------------------------------') 
disp(' N |    RN-Service time    | Service time  |    Service begin    |    Service end   |    Waiting time  | Time spent   |      ') 
disp('------------------------------------------------------------------------------------------------------------------------') 
for i=1:length(counter1)
    printf(' %d         %d                     %d                  %d                  %d                 %d                %d\n',counter1(i),counter1_svc_rn(i),counter1_service(i),counter1_begin(i),counter1_end(i),counter1_waiting(i),counter1_spent(i))
end
disp('------------------------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 


disp('                                      COUNTER 2                                                            ') 
disp('------------------------------------------------------------------------------------------------------------------------') 
disp(' N |    RN-Service time    | Service time  |    Service begin    |    Service end   |    Waiting time  | Time spent   |      ') 
disp('------------------------------------------------------------------------------------------------------------------------') 
for i=1:length(counter2)
    printf(' %d         %d                     %d                  %d                  %d                 %d                %d\n',counter2(i),counter2_svc_rn(i),counter2_service(i),counter2_begin(i),counter2_end(i),counter2_waiting(i),counter2_spent(i))
end
disp('------------------------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 

if (allcounters_busy==1)

disp('                                      COUNTER 3                                                            ') 
disp('------------------------------------------------------------------------------------------------------------------------') 
disp(' N |    RN-Service time    | Service time  |    Service begin    |    Service end   |    Waiting time  | Time spent   |      ') 
disp('------------------------------------------------------------------------------------------------------------------------') 
for i=1:length(counter3)
    printf(' %d         %d                     %d                  %d                  %d                 %d                %d\n',counter3(i),counter3_svc_rn(i),counter3_service(i),counter3_begin(i),counter3_end(i),counter3_waiting(i),counter3_spent(i))
end
disp('------------------------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 
end
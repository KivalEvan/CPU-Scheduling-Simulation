
function s = TrainSimulation()    
%Initialize ticket information table   
ticket_type1 = [20,40,35];
ticket_type2 = [50,20,30];
ticket_type3 = [30,40,35];
days = [1,2,3];

%Initialize service table   
service_time = [1,2,3,4,5,6];
service_prob = [0.10,0.10,0.30,0.25,0.10,0.15];
service_cdf = [0.10,0.20,0.50,0.75,0.85,1];
service_range1 = [1,11,21,51,76,86];
service_range2 = [10,20,50,75,85,100];

%Initialize inter-arrival table   
inter_time = [1,2,3,4,5,6];
inter_prob = [0.25,0.35,0.10,0.10,0.10,0.10];
inter_cdf = [0.25,0.60,0.70,0.80,0.90,1];
inter_range1 = [1,26,61,71,81,91];
inter_range2 = [25,60,70,80,90,100];

%Initialize ticketslot table   
ticket_slot = [1,2,3];
ticket_prob = [0.30,0.50,0.20];
ticket_cdf = [0.30,0.80,1];
ticket_range1 = [1,31,81];
ticket_range2 = [30,80,100];


%Initialize ticketype table   
ticket_type_num = [1,2,3];
tickettype_prob = [0.40,0.20,0.40];
tickettype_cdf = [0.40,0.60,1];
tickettype_range1 = [1,41,61];
tickettype_range2 = [40,60,100];

%Initialize tickeamount table   
ticket_amount_num = [1,2,3];
ticketamount_prob = [0.40,0.20,0.40];
ticketamount_cdf = [0.40,0.60,1];
ticketamount_range1 = [1,41,61];
ticketamount_range2 = [40,60,100];
price= [10,20,30];

%Initialize member table   
member_status = [0,1];
member_prob = [0.60,0.40];
member_cdf = [0.60,0.40,1];
member_range1 = [1,61];
member_range2 = [60,100];

%Variables
cust_num=0;
service_times=[];
cust_rn =[];
cust_number=[];
inter_arr_time=[];
ticket_slot_day=[];
ticket_type=[];
ticket_amount=[];
total_paid=[];
member_statuses=[];
%Get user inputs
while cust_num<=2
    cust_num = input ('Enter the number of customer: '); 
    if cust_num>2
        break
    else
        disp('Number of customer must be more than 2')
    end

end
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
disp(' ') 
disp(' ') 
%Random Number for Slot, Inter and Type from selected generator
inter_rn = zeros(cust_num,1);
slot_rn = zeros(cust_num,1);
type_rn = zeros(cust_num,1);
service_rn = zeros(cust_num,1);
amount_rn = zeros(cust_num,1);
member_rn = zeros(cust_num,1);
% Uniformly Distributed Integer
if rand_type == 1
	for i=1:cust_num
		service_rn(i) = randi(1,100);
		inter_rn(i) = randi(1,100);
		slot_rn(i) = randi(1,100);
		type_rn(i) = randi(1,100);
		amount_rn(i) = randi(1,100);
		member_rn(i) = randi(1,100);
	end
end
% Linear Congruential Generator
if rand_type == 2
	for i=1:cust_num
		service_rn(i) = round(mod(rand.*100,100-1)+1);
		inter_rn(i) = round(mod(rand.*100,100-1)+1);
		slot_rn(i) = round(mod(rand.*100,100-1)+1);
		type_rn(i) = round(mod(rand.*100,100-1)+1);
		amount_rn(i) = round(mod(rand.*100,100-1)+1);
		member_rn(i) = round(mod(rand.*100,100-1)+1);
	end
end
% Floor Function
if rand_type == 3
	for i=1:cust_num
		service_rn(i) = floor((100-1).*rand(1)+1);
		inter_rn(i) = floor((100-1).*rand(1)+1);
		slot_rn(i) = floor((100-1).*rand(1)+1);
		type_rn(i) = floor((100-1).*rand(1)+1);
		amount_rn(i) = floor((100-1).*rand(1)+1);
		member_rn(i) = floor((100-1).*rand(1)+1);
	end
end
k=1;
%Mapping
for k=1:cust_num
for i=1:6
       if (service_rn(k) >= service_range1(i) & service_rn(k) <= service_range2(i))
           service_times(k)=i;
       end
       
end
end
for k=1:cust_num
for i=1:3
       if (amount_rn(k) >= ticketamount_range1(i) & amount_rn(k) <= ticketamount_range2(i))
           ticket_amount(k)=ticket_amount_num(i);
           total_paid(k)=price(i);
       end
       
end
end
       
      
for k=2:cust_num
for i=1:6
       if (inter_rn(k) >= inter_range1(i) & inter_rn(k) <= inter_range2(i))
       inter_arr_time(k)=i;
       end
       
end
end
   
for k=1:cust_num
for i=1:3
       if (slot_rn(k) >= ticket_range1(i) & slot_rn(k) <= ticket_range2(i))
       ticket_slot_day(k)=i;
       end
       
end
end
   
for k=1:cust_num
for i=1:3
       if (type_rn(k) >= tickettype_range1(i) & type_rn(k) <= tickettype_range2(i))
           ticket_type(k)=i;
       end
       
end

cust_number(k)=k;
end
for k=1:cust_num
for i=1:2
       if (member_rn(k) >= member_range1(i) & member_rn(k) <= member_range2(i))
           member_statuses(k)=member_status(i);
       end
       
end
end
      
       
%Get arrival time
arrival_time = [];
total_arr=0;
for i=1:cust_num
    total_arr=total_arr+inter_arr_time(i);
    arrival_time(i)=total_arr;
end
%Q Simulation

counter1_spent=[];
counter1_waiting=[];
counter1_begin=[];
counter1_begin(1)=0;
counter1_end=[];
counter1_end(1)=service_times(1);
counter1_service_rn=[];
counter1_service_rn(1)=service_rn(1);
counter1_service=[];
counter1_service(1)=service_times(1);
counter1_status=[];
counter1=[];
counter1(1)=1;
counter2_status=[];
counter2_spent=[];
counter2_waiting=[];
counter2_begin=[];
counter2_begin(1)=0;
counter2_end=[];
counter2_end(1)=service_times(1);
counter2_service_rn=[];
counter2_service=[];
counter3_spent=[];
counter3_waiting=[];
counter3_begin=[];
counter3_begin(1)=0;
counter3_end=[];
counter3_end(1)=service_times(1);
counter3_service_rn=[];
counter3_service=[];
c1=2;
c2=1;
c3=1;
c=0;
counter2=[];
counter3=[];
time_end_count1=service_times(1);
time_end_count2=0;
time_end_count3=10;
total_waiting=0;
prob_waiting=0;
disp('Counter 1 and Counter 2 are in operation')
fprintf('Arrival of customer number %d at minute %d and %d tickets were purchased\n',[1,arrival_time(1),ticket_amount(1)])
fprintf('Departure of customer number %d at minute %d\n',[1,service_times(1)])

for i=2:cust_num
%Message
if (arrival_time(i)>=10&c==0)
    disp('Counter 3 (Member only) started operation at minute 10')
c=1;
end
fprintf('Arrival of customer number %d at minute %d and %d tickets were purchased\n',[i,arrival_time(i),ticket_amount(i)])

    if (arrival_time(i)>=time_end_count1)
        counter1(c1)=i; 
        counter1_begin(c1)=arrival_time(i);
        time_end_count1=arrival_time(i)+service_times(i);
        counter1_service_rn(c1)=service_rn(i);
        counter1_service(c1)=service_times(i);
        counter1_end(c1)=time_end_count1;
        counter1_spent(c1)=time_end_count1-arrival_time(i);
        counter1_waiting(c1)=counter1_begin(c1)-arrival_time(i);
        total_waiting = total_waiting+counter1_waiting(c1);
        counter1_status(c1)=member_statuses(i);
        fprintf('Service for customer number %d started at minute %d\n',[i,counter1_begin(c1)])
        fprintf('Departure of customer number %d at minute %d\n',[i,counter1_end(c1)])

        if (counter1_waiting(c1)>0)
            prob_waiting=prob_waiting+1;
        end
        c1=c1+1;
        

   else
       if (arrival_time(i)>=time_end_count2)
        counter2(c2)=i;
        counter2_begin(c2)=arrival_time(i);
        time_end_count2=arrival_time(i)+service_times(i);
        counter2_service_rn(c2)=service_rn(i);
        counter2_service(c2)=service_times(i);
        counter2_end(c2)=time_end_count2;
        counter2_spent(c2)=time_end_count2-arrival_time(i);
        counter2_waiting(c2)=counter2_begin(c2)-arrival_time(i);
        total_waiting = total_waiting+counter2_waiting(c2);
        counter2_status(c2)=member_statuses(i);
        fprintf('Service for customer number %d started at minute %d\n',[i,counter2_begin(c2)])
        fprintf('Departure of customer number %d at minute %d\n',[i,counter2_end(c2)])

         if (counter2_waiting(c2)>0)
            prob_waiting=prob_waiting+1;
        end
        c2=c2+1;
       else if (time_end_count3<=time_end_count1&time_end_count3<=time_end_count2&member_statuses(i)==1)
                 counter3(c3)=i; 
                 if(arrival_time(i)>time_end_count3)
                    counter3_begin(c3)=arrival_time(i);
                 else
                     counter3_begin(c3)=time_end_count3
                 end
                 time_end_count3=counter3_begin(c3)+service_times(i);
                 counter3_service_rn(c3)=service_rn(i);
                 counter3_service(c3)=service_times(i);
                 counter3_end(c3)=time_end_count3;
                 counter3_spent(c3)=time_end_count3-arrival_time(i);
                 counter3_waiting(c3)=counter3_begin(c3)-arrival_time(i);
                 total_waiting = total_waiting+counter3_waiting(c3);
                 counter3_status(c3)=member_statuses(i);
                 fprintf('Service for customer number %d started at minute %d\n',[i,counter3_begin(c3)])
                 fprintf('Departure of customer number %d at minute %d\n',[i,counter3_end(c3)])
                  if (counter3_waiting(c3)>0)
                      prob_waiting=prob_waiting+1;
                  end
                 c3=c3+1;
               
           else   
            if (time_end_count1<=time_end_count2)
                 counter1(c1)=i; 
                 counter1_begin(c1)=time_end_count1;
                 time_end_count1=time_end_count1+service_times(i);
                 counter1_service_rn(c1)=service_rn(i);
                 counter1_service(c1)=service_times(i);
                 counter1_end(c1)=time_end_count1;
                 counter1_spent(c1)=time_end_count1-arrival_time(i);
                 counter1_waiting(c1)=counter1_begin(c1)-arrival_time(i);
                 total_waiting = total_waiting+counter1_waiting(c1);
                 counter1_status(c1)=member_statuses(i);
                 fprintf('Service for customer number %d started at minute %d\n',[i,counter1_begin(c1)])
                 fprintf('Departure of customer number %d at minute %d\n',[i,counter1_end(c1)])

                  if (counter1_waiting(c1)>0)
                      prob_waiting=prob_waiting+1;
                  end
                 c1=c1+1;
        
            else
                 counter2(c2)=i;
                 counter2_begin(c2)=time_end_count2;
                 time_end_count2=time_end_count2+service_times(i);
                 counter2_service_rn(c2)=service_rn(i);
                 counter2_service(c2)=service_times(i);
                 counter2_end(c2)=time_end_count2;
                 counter2_spent(c2)=time_end_count2-arrival_time(i);
                 counter2_waiting(c2)=counter2_begin(c2)-arrival_time(i);
                 total_waiting = total_waiting+counter2_waiting(c2);
                 counter2_status(c2)=member_statuses(i);
                 fprintf('Service for customer number %d started at minute %d\n',[i,counter2_begin(c2)])
                 fprintf('Departure of customer number %d at minute %d\n',[i,counter2_end(c2)])
                  if (counter2_waiting(c2)>0)
                      prob_waiting=prob_waiting+1;
                  end
                 c2=c2+1;
            end
           end
       end
    end
%Buying tickets    
 if (ticket_type(i)==1)
    if (ticket_type1(ticket_slot_day(i))<=ticket_amount(i))
        amount_left=ticket_amount(i)-ticket_type1(ticket_slot_day(i));
        amount_left=max(amount_left,0);
        ticket_amount(i)=amount_left;
        total_paid(i)=amount_left*10;
    end
    ticket_type1(ticket_slot_day(i))= ticket_type1(ticket_slot_day(i))-ticket_amount(i);
 end
 if (ticket_type(i)==2)
    if (ticket_type2(ticket_slot_day(i))<=ticket_amount(i))
        amount_left=ticket_amount(i)-ticket_type2(ticket_slot_day(i));
        amount_left=max(amount_left,0);
        ticket_amount(i)=amount_left;
        total_paid(i)=amount_left*10;

    end
        ticket_type2(ticket_slot_day(i))= ticket_type2(ticket_slot_day(i))-ticket_amount(i);
 end
 if (ticket_type(i)==3)
    if (ticket_type3(ticket_slot_day(i))<=ticket_amount(i))
        amount_left=ticket_amount(i)-ticket_type3(ticket_slot_day(i));
        amount_left=max(amount_left,0);
        ticket_amount(i)=amount_left;
        total_paid(i)=amount_left*10;
    end
        ticket_type3(ticket_slot_day(i))= ticket_type3(ticket_slot_day(i))-ticket_amount(i);
 end
ticket_type3 = max(ticket_type3,0);
ticket_type2 = max(ticket_type2,0);
ticket_type1 = max(ticket_type1,0);

end
disp(' ') 
disp(' ') 
disp('                                             RESULTS                                                            ') 
disp('----------------------------------------------------------------------------------------------------------------------------------------------------------------') 
disp(' N | RN-Inter arrival time |  Inter arrival time  |  Arrival time |  RN-Ticket slot  | Ticket slot | RN-Ticket type | Ticket type | Tickets bought | Total paid') 
disp('----------------------------------------------------------------------------------------------------------------------------------------------------------------') 
for i=1:cust_num
printf('%2d         %2d                   %2d                      %2d                  %2d            %2d              %2d                %2d               %2d           %d\n',i, inter_rn(i), inter_arr_time(i),arrival_time(i),slot_rn(i),ticket_slot_day(i),type_rn(i),ticket_type(i),ticket_amount(i),total_paid(i))
end
disp('----------------------------------------------------------------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 

disp('                                              COUNTER 1                                                            ') 
disp('--------------------------------------------------------------------------------------------------------------------------------------') 
disp(' N |   Membership    | RN-Service time    | Service time  |    Service begin    |    Service end   |    Waiting time  | Time spent   |      ') 
disp('--------------------------------------------------------------------------------------------------------------------------------------') 
for i=1:length(counter1)
    printf(' %2d         %2d                  %2d                  %3d                  %3d               %2d                %2d          %2d\n',counter1(i),counter1_status(i),counter1_service_rn(i),counter1_service(i),counter1_begin(i),counter1_end(i),counter1_waiting(i),counter1_spent(i))
end
disp('--------------------------------------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 

disp('                                               COUNTER 2                                                            ') 
disp('--------------------------------------------------------------------------------------------------------------------------------------') 
disp(' N |   Membership    | RN-Service time    | Service time  |    Service begin    |    Service end   |    Waiting time  | Time spent   |      ') 
disp('--------------------------------------------------------------------------------------------------------------------------------------') 
for i=1:length(counter2)
    printf(' %2d         %2d                  %2d                  %3d                  %3d               %2d                %2d          %2d\n',counter2(i),counter2_status(i),counter2_service_rn(i),counter2_service(i),counter2_begin(i),counter2_end(i),counter2_waiting(i),counter2_spent(i))
end
disp('--------------------------------------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 
if (length(counter3)>=1)
disp('                                                COUNTER 3                                                            ') 
disp('--------------------------------------------------------------------------------------------------------------------------------------') 
disp(' N |   Membership    | RN-Service time    | Service time  |    Service begin    |    Service end   |    Waiting time  | Time spent   |      ') 
disp('--------------------------------------------------------------------------------------------------------------------------------------') 
for i=1:length(counter3)
    printf(' %2d         %2d                  %2d                  %3d                  %3d               %2d                %2d          %2d\n',counter3(i),counter3_status(i),counter3_service_rn(i),counter3_service(i),counter3_begin(i),counter3_end(i),counter3_waiting(i),counter3_spent(i))
end
disp('--------------------------------------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 
end
disp('                                               REMAINING TICKET                                                               ') 
disp('------------------------------------------------------------------------------------------------------') 
disp(' Day/slot    |    Total ticket type 1    |     Total ticket type 2       |    Total ticket type 3       |')   
disp('------------------------------------------------------------------------------------------------------') 
for i=1:length(days)
printf('   %2d                 %2d                              %2d                             %2d\n',days(i), ticket_type1(i), ticket_type2(i), ticket_type3(i))
end
disp('------------------------------------------------------------------------------------------------------') 

disp(' ') 
disp(' ') 
sale1=0;
sale2=0;
sale3=0;
for i=1:length(counter1)
    sale1=total_paid(counter1(i))+sale1;
end
for i=1:length(counter2)
    sale2=total_paid(counter2(i))+sale2;
end
for i=1:length(counter3)
    sale3=total_paid(counter3(i))+sale3;
        disp(sale3);

end
avg_ser1=sum(counter1_service)/cust_num;
avg_ser2=sum(counter2_service)/cust_num;
avg_ser3=sum(counter3_service)/cust_num;
z=sum(counter1_spent)+sum(counter2_spent)+sum(counter3_spent);
avg_spent=z/cust_num;
avg_wait=total_waiting/cust_num;
avg_inter=total_arr/(cust_num-1);
prob_wait=prob_waiting/cust_num;
printf(' Average waiting time for a customer:%2d/%2d=%.2f\n',total_waiting,cust_num,avg_wait)
printf(' Average inter arrival time:%2d/%d=%.2f\n',total_arr,cust_num-1,avg_inter)
printf(' Average time spent:%2d/%d=%.2f\n',z,cust_num,avg_spent)
printf(' Probability that a customer has to wait:%2d/%d=%.2f\n',prob_waiting,cust_num,prob_wait)
printf(' Average service time for Counter 1 :%2d/%d=%.2f\n',sum(counter1_service),cust_num,avg_ser1)
printf(' Average service time for Counter 2 :%2d/%d=%.2f\n',sum(counter2_service),cust_num,avg_ser2)
printf(' Average service time for Counter 3 :%2d/%d=%.2f\n',sum(counter3_service),cust_num,avg_ser3)
printf(' Sales for Counter 1 :%2d\n',sale1)
printf(' Sales for Counter 2 :%2d\n',sale2)
printf(' Sales for Counter 3 :%2d\n',sale3)


function simulationSystem()
% initialise table for tickets' information
tkt_type1 = [20,40,35];
tkt_type2 = [50,20,40];
tkt_type3 = [30,40,35];
tkt_day = [1,2,3];

% initialise table for service time
svc_time = [1,2,3,4,5,6];
svc_prob = [0.10,0.10,0.30,0.25,0.10,0.15];
svc_range = [0,10,20,50,75,85,100];

% initialise table for inter-arrival
intarr_time = [1,2,3,4,5,6];
intarr_prob = [0.25,0.35,0.10,0.10,0.10,0.10];
intarr_range = [0,25,60,70,80,90,100];

% initialise table for ticket slot
tkt_slot_num = [1,2,3];
tkt_slot_prob = [0.30,0.50,0.20];
tkt_slot_range = [0,30,80,100];

% initialise table for ticket type
tkt_type_num = [1,2,3];
tkt_type_prob = [0.40,0.20,0.40];
tkt_type_range = [0,40,60,100];

% initialise table for ticket amount
tkt_amt_num = [1,2,3];
tkt_amt_prob = [0.40,0.20,0.40];
tkt_amt_range = [0,40,60,100];
tkt_price= [10,20,30];

% initialise table for membership
member_status = [0,1];
member_prob = [0.60,0.40];
member_range = [0,60,100];

% draw table for tickets' information
printf('\n >  TABLE OF TICKETS INFORMATION\n')
printf('---------------------------------------------------------------------------------\n')
printf(' Day/Slot  | Total ticket type 1  | Total ticket type 2  | Total ticket type 3\n')
printf('---------------------------------------------------------------------------------\n')
for i=1:length(tkt_day)
	printf(' %4d      | %4d                 | %4d                 | %4d               \n',tkt_day(i),tkt_type1(i),tkt_type2(i),tkt_type3(i))
end
printf('---------------------------------------------------------------------------------\n\n\n')

% draw table for service time
printf(' >  TABLE OF SERVICE TIME\n') 
printf('------------------------------------------------------\n')
printf(' Service time        | Probability  | CDF   | Range\n')
printf('------------------------------------------------------\n')
for i=1:length(svc_time)
	printf(' %4d                | %.2f         | %.2f  | %2d-%d\n',svc_time(i),svc_prob(i),accumulate(svc_prob,i),svc_range(i)+1,svc_range(i+1))
end
printf('------------------------------------------------------\n\n\n')

% draw table for inter-arrival
printf(' >  TABLE OF INTER-ARRIVAL TIME\n')
printf('------------------------------------------------------\n')
printf(' Inter-arrival time  | Probability  | CDF   | Range\n')
printf('------------------------------------------------------\n')
for i=1:length(intarr_time)
	printf(' %4d                | %.2f         | %.2f  | %2d-%d\n',intarr_time(i),intarr_prob(i),accumulate(intarr_prob,i),intarr_range(i)+1,intarr_range(i+1))
end
printf('------------------------------------------------------\n\n\n')

% draw table for ticket slot
printf(' >  TABLE OF TICKET SLOT\n') 
printf('------------------------------------------------------\n')
printf(' Ticket slot/day     | Probability  | CDF   | Range\n')
printf('------------------------------------------------------\n')
for i=1:length(tkt_day)
	printf(' %4d                | %.2f         | %.2f  | %2d-%d\n',tkt_slot_num(i),tkt_slot_prob(i),accumulate(tkt_slot_prob,i),tkt_slot_range(i)+1,tkt_slot_range(i+1))
end
printf('------------------------------------------------------\n\n\n')

% draw table for ticket type
printf(' >  TABLE OF TICKET TYPE\n') 
printf('------------------------------------------------------\n')
printf(' Ticket type         | Probability  | CDF   | Range\n')
printf('------------------------------------------------------\n')
for i=1:length(tkt_day)
	printf(' %4d                | %.2f         | %.2f  | %2d-%d\n',tkt_type_num(i),tkt_type_prob(i),accumulate(tkt_type_prob,i),tkt_type_range(i)+1,tkt_type_range(i+1))
end
printf('------------------------------------------------------\n\n\n')

% draw table for ticket amount
printf(' >  TABLE OF TICKET AMOUNT AND PRICE\n') 
printf('------------------------------------------------------\n')
printf(' Quantity  | Price   | Probability  | CDF   | Range\n')
printf('------------------------------------------------------\n')
for i=1:length(tkt_day)
    printf(' %4d      | %4.2f   | %.2f         | %.2f  | %2d-%d\n',tkt_amt_num(i),tkt_price(i),tkt_amt_prob(i),accumulate(tkt_amt_prob,i),tkt_amt_range(i)+1,tkt_amt_range(i+1))
end
printf('------------------------------------------------------\n\n\n')

% draw table for membership
printf(' >  TABLE OF MEMBERSHIP\n') 
printf('------------------------------------------------------\n')
printf(' Status              | Probability  | CDF   | Range\n') 
printf('------------------------------------------------------\n')
for i=1:2
	printf(' %4d                | %.2f         | %.2f  | %2d-%d\n',member_status(i),member_prob(i),accumulate(member_prob,i),member_range(i)+1,member_range(i+1))
end
printf('------------------------------------------------------\n\n\n')

% draw prompt menu
printf('\n--------------------------\n')
printf(' TYPE OF RANDOM GENERATOR\n')
printf('--------------------------\n')
printf(' [ 1 ] Uniformly Distributed Integer\n')
printf(' [ 2 ] Linear Congruential Generator\n')
printf(' [ 3 ] Floor Function\n\n')
% get user inputs; only accepting specific value.
input_random = 0;
while input_random < 1 | input_random > 3
	input_random = input('Select the type of random generator: ');
	if input_random >= 1 & input_random <= 3
		break
	else
		printf('Invalid random generator input...\n\n')
	end
end
printf('\n\n')
cust_num = 0;
while cust_num <= 2
	cust_num = input('Enter the number of customer: ');
	if cust_num > 2
		break
	else
		printf('Number of customer must be more than 2...\n\n')
	end
end

% RANDOM NUMBER GENERATOR
% the value will be randomised between the initial and final range value of the variable.
% initial_range according to range variable by default starts at 0, therefore requiring addition by 1.
% initialise the variables with array of zero with size of cust_num.
inter_rn = zeros(cust_num,1);
slot_rn = zeros(cust_num,1);
type_rn = zeros(cust_num,1);
service_rn = zeros(cust_num,1);
amount_rn = zeros(cust_num,1);
member_rn = zeros(cust_num,1);
% Uniformly Distributed Integer
% randi(initial_range+1,final_range)
if input_random == 1
	for i=1:cust_num
		service_rn(i) = randi(svc_range(1)+1,svc_range(length(svc_range)));
		inter_rn(i) = randi(intarr_range(1)+1,intarr_range(length(intarr_range)));
		slot_rn(i) = randi(tkt_slot_range(1)+1,tkt_slot_range(length(tkt_slot_range)));
		type_rn(i) = randi(tkt_type_range(1)+1,tkt_type_range(length(tkt_type_range)));
		amount_rn(i) = randi(tkt_amt_range(1)+1,tkt_amt_range(length(tkt_amt_range)));
		member_rn(i) = randi(member_range(1)+1,member_range(length(member_range)));
	end
end
% Linear Congruential Generator
% round(mod(rand.*final_range,final_range-1)+initial_range+1)
if input_random == 2
	for i=1:cust_num
		service_rn(i) = round(mod(rand.*svc_range(length(svc_range)),svc_range(length(svc_range))-1)+svc_range(1)+1);
		inter_rn(i) = round(mod(rand.*intarr_range(length(intarr_range)),intarr_range(length(intarr_range))-1)+intarr_range(1)+1);
		slot_rn(i) = round(mod(rand.*tkt_slot_range(length(tkt_slot_range)),tkt_slot_range(length(tkt_slot_range))-1)+tkt_slot_range(1)+1);
		type_rn(i) = round(mod(rand.*tkt_type_range(length(tkt_type_range)),tkt_type_range(length(tkt_type_range))-1)+tkt_type_range(1)+1);
		amount_rn(i) = round(mod(rand.*tkt_amt_range(length(tkt_amt_range)),tkt_amt_range(length(tkt_amt_range))-1)+tkt_amt_range(1)+1);
		member_rn(i) = round(mod(rand.*member_range(length(member_range)),member_range(length(member_range))-1)+member_range(1)+1);
	end
end
% Floor Function
% floor((final_range-initial_range).*rand(1)+initial_range+1)
if input_random == 3
	for i=1:cust_num
		service_rn(i) = floor((svc_range(length(svc_range))-svc_range(1)).*rand(1)+svc_range(1)+1);
		inter_rn(i) = floor((intarr_range(length(intarr_range))-intarr_range(1)).*rand(1)+intarr_range(1)+1);
		slot_rn(i) = floor((tkt_slot_range(length(tkt_slot_range))-tkt_slot_range(1)).*rand(1)+tkt_slot_range(1)+1);
		type_rn(i) = floor((tkt_type_range(length(tkt_type_range))-tkt_type_range(1)).*rand(1)+tkt_type_range(1)+1);
		amount_rn(i) = floor((tkt_amt_range(length(tkt_amt_range))-tkt_amt_range(1)).*rand(1)+tkt_amt_range(1)+1);
		member_rn(i) = floor((member_range(length(member_range))-member_range(1)).*rand(1)+member_range(1)+1);
	end
end

% the generated random number is compared to specific range, then insert matching value into variable.
% initialise the variables with array of zero with size of cust_num.
map_svc_time = zeros(cust_num,1);
map_intarr_time = zeros(cust_num,1);
map_tkt_slot = zeros(cust_num,1);
map_tkt_type = zeros(cust_num,1);
map_tkt_amt = zeros(cust_num,1);
map_total_paid = zeros(cust_num,1);
map_member_status = zeros(cust_num,1);
% VISUALISED EXAMPLE :-
% var_range = [0,20,50,100]
% var_range(i)+1 = 21
% var_range(i+1) = 50
% var_rn(k) = 5
% (var_rn(k) >= var_range(i)+1 & var_rn(k) <= var_range(i+1)
% (5 >= 21 & 5 <= 50)
for k=1:cust_num
	for i=1:length(svc_time)
		if (service_rn(k) >= svc_range(i)+1 & service_rn(k) <= svc_range(i+1))
			map_svc_time(k)=svc_time(i);
		end
	end
	for i=1:length(tkt_amt_num)
		if (amount_rn(k) >= tkt_amt_range(i)+1 & amount_rn(k) <= tkt_amt_range(i+1))
			map_tkt_amt(k)=tkt_amt_num(i);
			map_total_paid(k)=tkt_price(i);
		end
	end
	for i=1:length(tkt_slot_num)
		if (slot_rn(k) >= tkt_slot_range(i)+1 & slot_rn(k) <= tkt_slot_range(i+1))
			map_tkt_slot(k)=tkt_slot_num(i);
		end
	end
	for i=1:length(tkt_type_num)
		if (type_rn(k) >= tkt_type_range(i)+1 & type_rn(k) <= tkt_type_range(i+1))
			map_tkt_type(k)=tkt_type_num(i);
		end
	end
	for i=1:length(member_status)
		if (member_rn(k) >= member_range(i)+1 & member_rn(k) <= member_range(i+1))
			map_member_status(k)=member_status(i);
		end
	end
end
% assuming the first customer arrive at minute 0, skips to second customer.
for k=2:cust_num
	for i=1:length(intarr_time)
		if (inter_rn(k) >= intarr_range(i)+1 & inter_rn(k) <= intarr_range(i+1))
			map_intarr_time(k)=intarr_time(i);
		end
	end
end

% calculate total_arrival and arrival_time by inter-arrival.
arrival_time = zeros(cust_num,1);
total_arrival = 0;
for i=1:cust_num
	total_arrival = total_arrival + map_intarr_time(i);
	arrival_time(i) = total_arrival;
end

% counter variables
% initialise the variables with array of zero with size of cust_num.
counter_1_spent = zeros(cust_num,1);
counter_1_waiting = zeros(cust_num,1);
counter_1_begin = zeros(cust_num,1);
counter_1_begin(1) = 0;
counter_1_end = zeros(cust_num,1);
counter_1_end(1) = map_svc_time(1);
counter_1_service_rn = zeros(cust_num,1);
counter_1_service_rn(1) = service_rn(1);
counter_1_service = zeros(cust_num,1);
counter_1_service(1) = map_svc_time(1);
counter_1_status = zeros(cust_num,1);
counter_1 = zeros(cust_num,1);
counter_1(1) = 1;

counter_2_status = zeros(cust_num,1);
counter_2_spent = zeros(cust_num,1);
counter_2_waiting = zeros(cust_num,1);
counter_2_begin = zeros(cust_num,1);
counter_2_begin(1) = 0;
counter_2_end = zeros(cust_num,1);
counter_2_end(1) = map_svc_time(1);
counter_2_service_rn = zeros(cust_num,1);
counter_2_service = zeros(cust_num,1);
counter_2 = zeros(cust_num,1);

counter_3_spent = zeros(cust_num,1);
counter_3_waiting = zeros(cust_num,1);
counter_3_begin = zeros(cust_num,1);
counter_3_begin(1) = 0;
counter_3_end = zeros(cust_num,1);
counter_3_end(1) = map_svc_time(1);
counter_3_service_rn = zeros(cust_num,1);
counter_3_service = zeros(cust_num,1);
counter_3_flag = 0;
counter_3 = zeros(cust_num,1);

% variables for time the service session ends for specific counter
time_end_counter_1 = map_svc_time(1);
time_end_counter_2 = 0;
time_end_counter_3 = 30;
total_waiting = 0;
prob_waiting = 0;

% count variables
c1 = 1;
c2 = 0;
c3 = 0;
result_num = 1;

% simulation starts here...
% assume the first customer arrived and made a purchase at counter_1
if (map_tkt_type(i) == 1)
	if (tkt_type1(map_tkt_slot(i)) <= map_tkt_amt(i))
		map_tkt_amt(i) = tkt_type1(map_tkt_slot(i));
		map_total_paid(i) = map_tkt_amt(i)*10;
	end
	tkt_type1(map_tkt_slot(i)) = tkt_type1(map_tkt_slot(i)) - map_tkt_amt(i);
end
if (map_tkt_type(i) == 2)
	if (tkt_type2(map_tkt_slot(i)) <= map_tkt_amt(i))
		map_tkt_amt(i) = tkt_type2(map_tkt_slot(i));
		map_total_paid(i) = map_tkt_amt(i)*10;
	end
	tkt_type2(map_tkt_slot(i)) = tkt_type2(map_tkt_slot(i)) - map_tkt_amt(i);
end
if (map_tkt_type(i) == 3)
	if (tkt_type3(map_tkt_slot(i)) <= map_tkt_amt(i))
		map_tkt_amt(i) = tkt_type3(map_tkt_slot(i));
		map_total_paid(i) = map_tkt_amt(i)*10;
	end
	tkt_type3(map_tkt_slot(i)) = tkt_type3(map_tkt_slot(i)) - map_tkt_amt(i);
end
printf('\n\n\n [Counter 1] and [Counter 2] are in operation')
printf('\n > Arrival of customer number %d at minute %d',1,arrival_time(1))
if (map_tkt_amt(1) > 0)
	printf(' and %d [ticket type %d slot %d] were purchased\n',map_tkt_amt(1),map_tkt_slot(1),map_tkt_type(1))
else
	printf('\n')
end
printf(' [Counter 1] Departure of customer number %d at minute %d\n',[1,map_svc_time(1)])
for i=2:cust_num
	% Counter 3 will be opened after 30 minute since initial simulation.
	if (arrival_time(i) >= time_end_counter_3 & counter_3_flag == 0)
		printf('\n [Counter 3] Member-exclusive counter has started operation at minute %d\n',time_end_counter_3)
		counter_3_flag = 1;
	end
	result_num = result_num + 1;
	
	% the ticket purchasing calculation.
	% assume customer will still purchase remaining ticket if it exceeds their initial. (case: customer buys 3 but only 2 left, therefore purchase remaining)
	% if there are no ticket left, the customer won't make a purchase.
	% updates ticket price after changes.
	if (map_tkt_type(i) == 1)
		if (tkt_type1(map_tkt_slot(i)) <= map_tkt_amt(i))
			map_tkt_amt(i) = tkt_type1(map_tkt_slot(i));
			map_total_paid(i) = map_tkt_amt(i)*10;
		end
		tkt_type1(map_tkt_slot(i)) = tkt_type1(map_tkt_slot(i)) - map_tkt_amt(i);
	else
		if (map_tkt_type(i) == 2)
			if (tkt_type2(map_tkt_slot(i)) <= map_tkt_amt(i))
				map_tkt_amt(i) = tkt_type2(map_tkt_slot(i));
				map_total_paid(i) = map_tkt_amt(i)*10;
			end
			tkt_type2(map_tkt_slot(i)) = tkt_type2(map_tkt_slot(i)) - map_tkt_amt(i);
		else
			if (map_tkt_type(i) == 3)
				if (tkt_type3(map_tkt_slot(i)) <= map_tkt_amt(i))
					map_tkt_amt(i) = tkt_type3(map_tkt_slot(i));
					map_total_paid(i) = map_tkt_amt(i)*10;
				end
				tkt_type3(map_tkt_slot(i)) = tkt_type3(map_tkt_slot(i)) - map_tkt_amt(i);
			end
		end
	end
	printf('\n > Arrival of customer number %d at minute %d',i,arrival_time(i))
	if (map_tkt_amt(i) > 0)
		printf(' and %d [ticket type %d slot %d] were purchased\n',map_tkt_amt(i),map_tkt_slot(i),map_tkt_type(i))
	else
		printf('\n')
	end
	
	% the customer arrive and/or queue up for the counter.
	% assuming priority from highest to lowest for counter_1, counter_2 and counter_3.
	% check if counter_1 is available on arrival.
	if (arrival_time(i) >= time_end_counter_1)
		c1 = c1 + 1;
		counter_1(c1) = i;
		counter_1_begin(c1) = arrival_time(i);
		time_end_counter_1 = arrival_time(i) + map_svc_time(i);
		counter_1_service_rn(c1) = service_rn(i);
		counter_1_service(c1) = map_svc_time(i);
		counter_1_end(c1) = time_end_counter_1;
		counter_1_spent(c1) = time_end_counter_1 - arrival_time(i);
		counter_1_waiting(c1) = counter_1_begin(c1) - arrival_time(i);
		total_waiting = total_waiting + counter_1_waiting(c1);
		counter_1_status(c1) = map_member_status(i);
		printf(' [Counter 1] Service for customer number %d started at minute %d\n',[i,counter_1_begin(c1)])
		printf(' [Counter 1] Departure of customer number %d at minute %d\n',[i,counter_1_end(c1)])
		if (counter_1_waiting(c1) > 0)
			prob_waiting = prob_waiting + 1;
		end
	else
		% check if counter_2 is available on arrival.
		if (arrival_time(i) >= time_end_counter_2)
			c2 = c2 + 1;
			counter_2(c2) = i;
			counter_2_begin(c2) = arrival_time(i);
			time_end_counter_2 = arrival_time(i) + map_svc_time(i);
			counter_2_service_rn(c2) = service_rn(i);
			counter_2_service(c2) = map_svc_time(i);
			counter_2_end(c2) = time_end_counter_2;
			counter_2_spent(c2) = time_end_counter_2 - arrival_time(i);
			counter_2_waiting(c2) = counter_2_begin(c2) - arrival_time(i);
			total_waiting = total_waiting + counter_2_waiting(c2);
			counter_2_status(c2) = map_member_status(i);
			printf(' [Counter 2] Service for customer number %d started at minute %d\n',[i,counter_2_begin(c2)])
			printf(' [Counter 2] Departure of customer number %d at minute %d\n',[i,counter_2_end(c2)])
			if (counter_2_waiting(c2) > 0)
				prob_waiting = prob_waiting + 1;
			end
		else
			% check if counter_3 is available on arrival.
			% counter_3 is member-exclusive.
			if (time_end_counter_3 <= time_end_counter_1 & time_end_counter_3 <= time_end_counter_2 & map_member_status(i) == 1 & counter_3_flag == 1)
				c3 = c3 + 1;
				counter_3(c3) = i;
				if(arrival_time(i) > time_end_counter_3)
					counter_3_begin(c3) = arrival_time(i);
				else
					counter_3_begin(c3) = time_end_counter_3;
				end
				time_end_counter_3 = counter_3_begin(c3) + map_svc_time(i);
				counter_3_service_rn(c3) = service_rn(i);
				counter_3_service(c3) = map_svc_time(i);
				counter_3_end(c3) = time_end_counter_3;
				counter_3_spent(c3) = time_end_counter_3 - arrival_time(i);
				counter_3_waiting(c3) = counter_3_begin(c3) - arrival_time(i);
				total_waiting = total_waiting + counter_3_waiting(c3);
				counter_3_status(c3) = map_member_status(i);
				printf(' [Counter 3] Service for customer number %d started at minute %d\n',[i,counter_3_begin(c3)])
				printf(' [Counter 3] Departure of customer number %d at minute %d\n',[i,counter_3_end(c3)])
				if (counter_3_waiting(c3) > 0)
					prob_waiting = prob_waiting + 1;
				end
			else
				% check and queue for counter_1 if it ends earlier than counter_2.
				if (time_end_counter_1 <= time_end_counter_2)
					c1 = c1 + 1;
					counter_1(c1) = i;
					counter_1_begin(c1) = time_end_counter_1;
					time_end_counter_1 = time_end_counter_1 + map_svc_time(i);
					counter_1_service_rn(c1) = service_rn(i);
					counter_1_service(c1) = map_svc_time(i);
					counter_1_end(c1) = time_end_counter_1;
					counter_1_spent(c1) = time_end_counter_1 - arrival_time(i);
					counter_1_waiting(c1) = counter_1_begin(c1) - arrival_time(i);
					total_waiting = total_waiting + counter_1_waiting(c1);
					counter_1_status(c1) = map_member_status(i);
					printf(' [Counter 1] Service for customer number %d started at minute %d\n',[i,counter_1_begin(c1)])
					printf(' [Counter 1] Departure of customer number %d at minute %d\n',[i,counter_1_end(c1)])
					if (counter_1_waiting(c1) > 0)
						prob_waiting = prob_waiting + 1;
					end
				% queue for counter_2.
				else
					c2 = c2 + 1;
					counter_2(c2) = i;
					counter_2_begin(c2) = time_end_counter_2;
					time_end_counter_2 = time_end_counter_2 + map_svc_time(i);
					counter_2_service_rn(c2) = service_rn(i);
					counter_2_service(c2) = map_svc_time(i);
					counter_2_end(c2) = time_end_counter_2;
					counter_2_spent(c2) = time_end_counter_2 - arrival_time(i);
					counter_2_waiting(c2) = counter_2_begin(c2) - arrival_time(i);
					total_waiting = total_waiting + counter_2_waiting(c2);
					counter_2_status(c2) = map_member_status(i);
					printf(' [Counter 2] Service for customer number %d started at minute %d\n',[i,counter_2_begin(c2)])
					printf(' [Counter 2] Departure of customer number %d at minute %d\n',[i,counter_2_end(c2)])
					if (counter_2_waiting(c2) > 0)
						prob_waiting = prob_waiting + 1;
					end
				end
			end
		end
	end
	% when the ticket runs out, end the simulation.
	if((sum(tkt_type1)+sum(tkt_type2)+sum(tkt_type3)) <= 0)
		printf('\n!! All the tickets are sold out !!\n')
		printf('      Ending the simulation.\n')
		break;
	end
end

% draw table for overall results
printf('\n >  RESULTS\n')
printf('---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n')
printf('      N  | RN-Inter arrival time  | Inter arrival time  | Arrival time  | RN-Ticket slot  | Ticket slot  | RN-Ticket type  | Ticket type  | Tickets bought  | Total paid\n')
printf('---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n')
for i=1:result_num
	printf(' %7d | %4d                   | %2d                  | %4d          | %4d            | %2d           | %4d            | %2d           | %2d              | %4d\n',i,inter_rn(i),map_intarr_time(i),arrival_time(i),slot_rn(i),map_tkt_slot(i),type_rn(i),map_tkt_type(i),map_tkt_amt(i),map_total_paid(i))
end
printf('---------------------------------------------------------------------------------------------------------------------------------------------------------------------------\n\n\n')

% draw table for counter 1
printf(' >  COUNTER 1\n')
printf('------------------------------------------------------------------------------------------------------------------------\n')
printf('      N  | Membership  | RN-Service time  | Service time  | Service begin  | Service end  | Waiting time  | Time spent\n')
printf('------------------------------------------------------------------------------------------------------------------------\n')
for i=1:c1
	printf(' %7d | %4d        | %4d             | %4d          | %4d           | %4d         | %4d          | %4d\n',counter_1(i),counter_1_status(i),counter_1_service_rn(i),counter_1_service(i),counter_1_begin(i),counter_1_end(i),counter_1_waiting(i),counter_1_spent(i))
end
printf('------------------------------------------------------------------------------------------------------------------------\n\n\n')

% draw table for counter 2
printf(' >  COUNTER 2\n')
printf('------------------------------------------------------------------------------------------------------------------------\n')
printf('      N  | Membership  | RN-Service time  | Service time  | Service begin  | Service end  | Waiting time  | Time spent\n')
printf('------------------------------------------------------------------------------------------------------------------------\n')
for i=1:c2
	printf(' %7d | %4d        | %4d             | %4d          | %4d           | %4d         | %4d          | %4d\n',counter_2(i),counter_2_status(i),counter_2_service_rn(i),counter_2_service(i),counter_2_begin(i),counter_2_end(i),counter_2_waiting(i),counter_2_spent(i))
end
printf('------------------------------------------------------------------------------------------------------------------------\n\n\n')

% draw table for counter 3
if (c3>=1)
printf(' >  COUNTER 3\n')
printf('------------------------------------------------------------------------------------------------------------------------\n')
printf('      N  | Membership  | RN-Service time  | Service time  | Service begin  | Service end  | Waiting time  | Time spent\n')
printf('------------------------------------------------------------------------------------------------------------------------\n')
for i=1:c3
	printf(' %7d | %4d        | %4d             | %4d          | %4d           | %4d         | %4d          | %4d\n',counter_3(i),counter_3_status(i),counter_3_service_rn(i),counter_3_service(i),counter_3_begin(i),counter_3_end(i),counter_3_waiting(i),counter_3_spent(i))
end
printf('------------------------------------------------------------------------------------------------------------------------\n\n\n')
end

% draw table for amount of ticket left
printf(' >  TICKET LEFT\n')
printf('---------------------------------------------------------------------------------\n')
printf(' Day/Slot  | Total ticket type 1  | Total ticket type 2  | Total ticket type 3\n')
printf('---------------------------------------------------------------------------------\n')
for i=1:length(tkt_day)
	printf(' %4d      | %4d                 | %4d                 | %4d               \n',tkt_day(i),tkt_type1(i),tkt_type2(i),tkt_type3(i))
end
printf('---------------------------------------------------------------------------------\n\n\n')

sale1 = 0;
sale2 = 0;
sale3 = 0;
for i=1:c1
	sale1 = map_total_paid(counter_1(i)) + sale1;
end
for i=1:c2
	sale2 = map_total_paid(counter_2(i)) + sale2;
end
for i=1:c3
	sale3 = map_total_paid(counter_3(i)) + sale3;
end
avg_ser1 = sum(counter_1_service) / c1;
avg_ser2 = sum(counter_2_service) / c2;
avg_ser3 = sum(counter_3_service) / c3;
z = sum(counter_1_spent) + sum(counter_2_spent) + sum(counter_3_spent);
avg_spent = z / result_num;
avg_wait = total_waiting / result_num;
avg_inter = total_arrival / (result_num-1);
prob_wait = prob_waiting / result_num;

printf(' Average waiting time for a customer: %.2f\n',avg_wait)
printf(' Average inter arrival time: %.2f\n',avg_inter)
printf(' Average time spent: %.2f\n',avg_spent)
printf(' Probability that a customer has to wait: %.2f\n',prob_wait)
printf(' Average service time for Counter 1 : %.2f\n',avg_ser1)
printf(' Average service time for Counter 2 : %.2f\n',avg_ser2)
printf(' Average service time for Counter 3 : %.2f\n',avg_ser3)
printf(' Sales for Counter 1 : %2d\n',sale1)
printf(' Sales for Counter 2 : %2d\n',sale2)
printf(' Sales for Counter 3 : %2d\n',sale3)
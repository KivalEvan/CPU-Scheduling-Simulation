function simulationSystemCopy()
% initialise table for tickets' information
days = [1,2,3];
tkt_type = [20,40,35;50,20,30;30,40,35];

% initialise table for service time
svc_time = [1,2,3,4,5,6];
svc_prob = [0.10,0.10,0.30,0.25,0.10,0.15];
svc_cdf = [0.10,0.20,0.50,0.75,0.85,1];
svc_range = [1,10;11,20;21,50;51,75;76,85;86,100];

% initialise table for inter-arrival
intarr_time = [1,2,3,4,5,6,7,8];
intarr_prob = [0.20,0.10,0.10,0.20,0.10,0.10,0.05,0.15];
intarr_cdf = [0.20,0.30,0.40,0.60,0.70,0.80,0.85,1];
intarr_range = [1,20;21,30;31,40;41,60;61,70;71,80;81,85;86,100];

% initialise table for ticket slot
tkt_slot = [1,2,3];
tkt_prob = [0.30,0.50,0.20];
tkt_cdf = [0.30,0.80,1];
tkt_range = [1,30;31,80;81,100];

% initialise table for ticket type
tkt_type_num = [1,2,3];
tkt_type_prob = [0.40,0.20,0.40];
tkt_type_cdf = [0.40,0.60,1];
tkt_type_range = [1,40;41,60;61,100];

% initialise table for ticket amount
tkt_amt_num = [2,3,4];
tkt_amt_prob = [0.40,0.20,0.40];
tkt_amt_cdf = [0.40,0.60,1];
tkt_amt_range = [1,40;41,60;61,100];
price = [20,30,40];

% variables
svc_times = [];
cust_rn = [];
cust_number = [];
intarr_arr_time = [];
tkt_slot_day = [];
tkt_amt = [];
map_tkt_type = [];
total_paid = [];

clc;

printf('\n >  TABLE OF TICKETS INFORMATION\n')
printf('---------------------------------------------------------------------------------\n')
printf(' Day/Slot')
for i=1:length(tkt_type)
	printf('  | Total ticket type %d',i)
end
printf('\n---------------------------------------------------------------------------------\n')
for i=1:length(days)
	printf(' %4d    ',days(i))
	for j=1:length(tkt_type)
		printf('  | %4d               ',tkt_type(j,i))
	end
	printf('\n')
end
printf('---------------------------------------------------------------------------------\n\n\n')

printf(' >  TABLE OF SERVICE TIME\n') 
printf('------------------------------------------------------\n')
printf(' Service time        | Probability  | CDF   | Range\n')
printf('------------------------------------------------------\n')
for i=1:length(svc_time)
	printf(' %4d                | %.2f         | %.2f  | %2d-%d\n',svc_time(i),svc_prob(i),svc_cdf(i),svc_range(i,1),svc_range(i,2))
end
printf('------------------------------------------------------\n\n\n')

printf(' >  TABLE OF INTER-ARRIVAL TIME\n')
printf('------------------------------------------------------\n')
printf(' Inter-arrival time  | Probability  | CDF   | Range\n')
printf('------------------------------------------------------\n')
for i=1:length(intarr_time)
	printf(' %4d                | %.2f         | %.2f  | %2d-%d\n',intarr_time(i),intarr_prob(i),intarr_cdf(i),intarr_range(i,1),intarr_range(i,2))
end
printf('------------------------------------------------------\n\n\n')

printf(' >  TABLE OF TICKET SLOT\n') 
printf('------------------------------------------------------\n')
printf(' Ticket slot/day     | Probability  | CDF   | Range\n')
printf('------------------------------------------------------\n')
for i=1:length(days)
	printf(' %4d                | %.2f         | %.2f  | %2d-%d\n',tkt_slot(i),tkt_prob(i),tkt_cdf(i),tkt_range(i,1),tkt_range(i,2))
end
printf('------------------------------------------------------\n\n\n')

printf(' >  TABLE OF TICKET TYPE\n') 
printf('------------------------------------------------------\n')
printf(' Ticket type         | Probability  | CDF   | Range\n')
printf('------------------------------------------------------\n')
for i=1:length(days)
	printf(' %4d                | %.2f         | %.2f  | %2d-%d\n',tkt_type_num(i),tkt_type_prob(i),tkt_type_cdf(i),tkt_type_range(i,1),tkt_type_range(i,2))
end
printf('------------------------------------------------------\n\n\n')

printf(' >  TABLE OF TICKET AMOUNT AND PRICE\n') 
printf('-----------------------------------------------------\n')
printf(' Quantity  | Price  | Probability  | CDF   | Range\n')
printf('-----------------------------------------------------\n')
for i=1:length(days)
    printf(' %4d      | %4.2f  | %.2f         | %.2f  | %2d-%d\n',tkt_amt_num(i),price(i),tkt_amt_prob(i),tkt_amt_cdf(i),tkt_amt_range(i,1),tkt_amt_range(i,2))
end
printf('-----------------------------------------------------\n\n\n')

%cust_num = input ('Enter the number of customer: ');
cust_num = 1

intarr_rn = floor(1+(100-1).*rand(cust_num,1));
slot_rn = floor(1+(100-1).*rand(cust_num,1));
type_rn = floor(1+(100-1).*rand(cust_num,1));
svc_rn = floor(1+(100-1).*rand(cust_num,1));
amount_rn =  floor(1+(100-1).*rand(cust_num,1));

k=1;
%Mapping
for k=1:cust_num
	for i=1:6
		if (svc_rn(k) >= svc_range(i,1) & svc_rn(k) <= svc_range(i,2))
			svc_times(k)=i;
		end
	end
end

for k=1:cust_num
	for i=1:3
		if (amount_rn(k) >= tkt_amt_range(i,1) & amount_rn(k) <= tkt_amt_range(i,2))
			tkt_amt(k)=tkt_amt_num(i);
			total_paid(k)=price(i);
		end
	end
end
disp('Amount')
disp(tkt_amt)

for k=1:cust_num
	for i=1:8
		if (intarr_rn(k) >= intarr_range(i,1) & intarr_rn(k) <= intarr_range(i,2))
			intarr_arr_time(k)=i;
		end
	end
end
disp('Inter')
disp(intarr_arr_time)

for k=1:cust_num
	for i=1:3
		if (slot_rn(k) >= tkt_range(i,1) & slot_rn(k) <= tkt_range(i,2))
			tkt_slot_day(k)=i;
		end
	end
end
disp('Slot')
disp(tkt_slot_day)

for k=1:cust_num
	for i=1:3
		if (type_rn(k) >= tkt_type_range(i,1) & type_rn(k) <= tkt_type_range(i,2))
			map_tkt_type(k)=i;
		end
	end
	cust_number(k)=k;
end
disp('Type')
disp(map_tkt_type)
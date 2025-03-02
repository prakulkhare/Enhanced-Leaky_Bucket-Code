#include<stdio.h>

int outgoing, totalbuck_size, buck_size, extrabuck_size,filled_buck = 0;

double calcper() {
	return ((double)filled_buck / buck_size) * 100;
}
void add(int incoming) {
	if (incoming <= (buck_size - filled_buck)) {
		filled_buck += incoming;
		printf("Bucket buffer size %dKB(%.2f%%) out of %dKB\n", filled_buck, calcper(), buck_size);
	}
	else{
		if (incoming <= (totalbuck_size - filled_buck)) {
			buck_size = buck_size + extrabuck_size;
			filled_buck += incoming;
			printf("Bucket buffer size %dKB(%.2f%%) out of %dKB\n", filled_buck, calcper(), buck_size);
		}
		else {
			printf("Packet Dropped\n");
			printf("Bucket buffer size %dKB(%.2f%%) out of %dKB\n", filled_buck, calcper(), buck_size);
		}
	}
	filled_buck = filled_buck - outgoing;

	if (filled_buck <= 0) {
		filled_buck = 0;
		printf("Outgoing: %dKB(%.2f%%) left out of %dKB in buffer\n", filled_buck, calcper(), buck_size);
	}
	else {
		printf("Outgoing: %dKB(%.2f%%) left out of %dKB in buffer\n", filled_buck, calcper(), buck_size);
	}	
}

void wait(int time) {
	printf("Waiting....\n");
	while (time != 0) {
		filled_buck = filled_buck - outgoing;
		if (filled_buck <= 0) {
			filled_buck = 0;
			printf("Outgoing: %dKB(%.2f%%) left out of %dKB in buffer\n", filled_buck, calcper(), buck_size);
			break;
		}
		printf("Outgoing: %dKB(%.2f%%) left out of %dKB in buffer\n", filled_buck, calcper(), buck_size);
		time--;
	}
	if (filled_buck < totalbuck_size / 2) {
		buck_size = buck_size - extrabuck_size;
	}
	printf("\n%dKB(%.2f%%) left out of %dKB in buffer\n", filled_buck, calcper(), buck_size);
}

void calc() {
	printf("Calculating....\n");
	if (filled_buck == 0) {
		printf("Bucket is Empty\n");
	}
	else{
		int count = (filled_buck/outgoing) + 1;
		printf("Calculated Outgoing: %dsecs to empty the bucket\n", count);
		printf("%dKB(%.2f%%) left out of %dKB in buffer\n", filled_buck, calcper(), buck_size);
	}
}

void changeout(int temp) {
	if (temp <= 0)
	{
		printf("Error: Please enter a positive number\n");
	}
	else {
		outgoing = temp;
		printf("Successfully changed the outgoing rate to %dKB/s\n", temp);
	}
}

void warning() {
	if (calcper() >= 85)
	{
		int safteysize = filled_buck - (buck_size / 2);
		int safteycount = safteysize/outgoing;
		printf("\nWarning: Bucket is almost full. Please Wait for %dsecs\n",safteycount);
	}
}

int main() {

	int temp, choice = -1; 

	printf("*****Leaky Bucket*****");
	printf("\n----------------------\n");
    printf("Enter bucket size in KB:\n");
    scanf("%d", &totalbuck_size);
	printf("Enter leak rate in KB/s:\n");
	scanf("%d", &outgoing);

	buck_size = totalbuck_size / 2;
	extrabuck_size = totalbuck_size - buck_size;

	while (choice != 0) {
		printf("\n1.Add incoming packets \n2.Wait \n3.Calculate \n4.Change Outgoing Rate \n0.Exit \n");
		printf("Enter your choice \n");
		scanf("%d", &choice);
		printf("\n");
		switch (choice)
		{
		case 1:
			printf("Enter the incoming packet size in KB:\n");
			scanf("%d", &temp);
			add(temp); 
			warning();
			printf("\n");
			break;
		case 2:
			printf("Enter number of seconds to wait \n");
			scanf("%d", &temp);
			wait(temp);
			warning();
			printf("\n");
			break;
		case 3:
			calc();
			warning();
			printf("\n");
			break;
		case 4:
			printf("Enter the new outgoing rate in KB/s:\n");
			scanf("%d", &temp);
			changeout(temp);
			warning();
			printf("\n");
			break;
		case 0:
			calc();
			printf("Thank you \n");
			return 0;
		default:
			printf("Wrong Input: Try again \n");
		}
	}
	return 0;
}
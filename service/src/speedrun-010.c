#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <fcntl.h>

/* 

   Compilation:
   TODO: ADD FULL RELRO WHEN YOU HAVE INTERNET
   gcc -o speedrun-010 -O0 -pie speedrun-010. c&& strip speedrun-010

   Also need to take the glibc version to give to folks.

 */

typedef struct person {
   char buf[8];
   char name[24];
   int (*print_msg)(char*);
   char type;
} person;

typedef struct message {
   person* person;
   int (*print_msg)(char*);
   char msg[25];
} message;


void say_hello()
{
   printf("Secure Coding is hard!\n");
}

void print_menu()
{
   printf("Choose something.\n");
   printf("1, 2, 3, 4, or 5\n");
}

message* messages[5] = {0};
person* people[5] = {0};

void what_do_they_say()
{
   int num_msg = 0;
   int num_person = 0;
   char choice;
   ssize_t result;
   
   while (1)
   {
	  print_menu();
	  result = read(0, &choice, 1);

	  if (result != 1)
	  {
		 return;
	  }
	  if (choice == '1')
	  {
		 person* new_person;
		 
		 // new person
		 if (num_person > 5)
		 {
			return;
		 }
		 num_person += 1;

		 printf("Need a name\n");
		 new_person = (person*)malloc(sizeof(person));
		 read(0, new_person->name, 23);
		 new_person->name[23] = '\0';
		 new_person->print_msg = (void*)puts;

		 people[num_person - 1] = new_person;
	  }
	  else if (choice == '2')
	  {
		 message* new_message;
		 // new message
		 if (num_msg > 5)
		 {
			return;
		 }
		 num_msg += 1;

		 printf("Need a message\n");
		 new_message = (message*)malloc(sizeof(message));
		 read(0, new_message->msg, 24);
		 new_message->msg[24] = '\0';

		 people[num_person - 1]->print_msg(people[num_person - 1]->name);
		 new_message->print_msg = (void*)puts;
		 
		 new_message->print_msg(" says ");
		 new_message->print_msg(new_message->msg);
		 new_message->print_msg("\n");

		 new_message->person = people[num_person - 1];
		 
		 messages[num_msg - 1] = new_message;
	  }
	  else if (choice == '3')
	  {
		 // free person
		 if (num_person == 0)
		 {
			return;
		 }
		 free(people[num_person - 1]);
	  }
	  else if (choice == '4')
	  {
		 // free message
		 if (num_msg == 0)
		 {
			return;
		 }
		 free(messages[num_msg - 1]);
		 num_msg -= 1;
	  }
	  else
	  {
		 return;
	  }
   }
}

void say_goodbye()
{
   printf("I DID IT\n");
}


int main(int argc, char** argv)
{
   setvbuf(stdout, NULL, _IONBF, 0);

   if (getenv("DEBUG") == NULL)
   {
	  alarm(5);
   }
   say_hello();
   what_do_they_say();
   say_goodbye();
}

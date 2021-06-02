#include "privileges.h"

static char *admin_password;
static struct student students[15];
int std_check[15];
static int available_pos=0;
static void saferFree(void **pp);

void set_admin_password(){
	admin_password=(char *)malloc(strlen("1111")+1);
	strcpy(admin_password,"1111");
}

int check_admin(char *admin_pass) {
	int check;
	if (strcmp(admin_password, admin_pass) == 0)
		check = 1;
	else{
		check = 0;}
	return check;
}

int check_student(int id,char *password){
	int check = 0;
	int i;
	for(i=0;i<15 && check==0 ;i++){
		if(students[i].std_id==id&&strcmp(students[i].std_password,password) == 0)
			check =1;
		else
			check = 0;
	}
	return check;
}

static int available_position(){
	int i ,check=0;
	for(i=0; i<15  && check==0 ;i++){
		if(std_check[i] == 0){
			available_pos=i;
			check=1;
		}
	}
	return check;
}

int add_new_student(char *name,char *password,int degree,int id){
	int add;
	if(available_position()){
		students[available_pos].std_name=(char *)malloc(strlen(name)+1);
		strcpy(students[available_pos].std_name,name);
		students[available_pos].std_password=(char *)malloc(strlen(password)+1);
		strcpy(students[available_pos].std_password,password);
		students[available_pos].std_id=id;
		students[available_pos].std_degree=degree;
		std_check[available_pos] = 1;
		add=1;
	}
	else {
        add = 0;
    }
	return add;
}

int remove_student(int id){
	int i,remove=0;
	for(i=0;i<15 && remove ==0;i++){
		if(std_check[i] == 1 && students[i].std_id==id){
			safeFree(students[i].std_name);
			safeFree(students[i].std_password);
			students[i].std_id=0;
			students[i].std_degree=0;
			std_check[i]=0;
			remove=1;
		}
		else
			remove=0;
	}
	return remove;
}

static void saferFree(void **pp)
{
	if (pp != NULL && *pp != NULL) {
		free(*pp);
		*pp = NULL;
	}
}

int change_student_name(int id,char *name){
	int i, check=0;
	for(i=0 ;i<15 && check==0 ;i++){
		if(std_check[i] == 1 && students[i].std_id==id){
			students[i].std_name = realloc(students[i].std_name,strlen(name)+1);
			strcpy(students[i].std_name,name);
			check=1;
		}
		else
			check=0;
	}
	return check ;
}
int change_student_password(int id,char *password){
	int i, check=0;
	for(i=0 ;i<15 && check==0 ;i++){
		if(students[i].std_id==id){
			students[i].std_password=realloc(students[i].std_password,strlen(password)+1);
			strcpy(students[i].std_password,password);
			check=1;
		}
		else
			check=0;
	}
	return check ;
}
int change_student_degree(int id,int degree){
	int i,check=0;
	for(i=0 ;i<15 && check==0 ;i++){
		if(std_check[i] == 1 && students[i].std_id==id){
			students[i].std_degree=degree;
			check=1;
		}
		else
			check=0;
	}
	return check ;
}
int  student_record(int id){
	int i, check=0;
	for(i=0;  i<15  &&  check==0  ; i++){
		if(std_check[i] == 1 && students[i].std_id==id){
			printf("Name: %s\n",students[i].std_name);
			printf("Password: %s\n",students[i].std_password);
			printf("degree: %d\n",students[i].std_degree);
			check=1;
		}
		else {
            check = 0;
            printf("Wrong ID!");
        }
	}
	return 0;
}



void change_admin_password(char *new_password){
	admin_password = realloc(admin_password,strlen(new_password));
	strcpy(admin_password,new_password);
}
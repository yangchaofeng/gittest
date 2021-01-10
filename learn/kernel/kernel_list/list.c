#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/slab.h>
#include <linux/list.h>

MODULE_LICENSE("GPL");

struct student
{
    char name[100];
    int num;
    struct list_head list;
};

struct student *pstudent;
struct student *tmp_student;
struct list_head student_list;
struct list_head *pos;

static  int __init mylist_init(void)
{
	int i = 0;
	
	INIT_LIST_HEAD(&student_list);
	
	pstudent = kmalloc(sizeof(struct student)*5,GFP_KERNEL);
	memset(pstudent,0,sizeof(struct student)*5);
	
	for(i=0;i<5;i++)
	{
	        sprintf(pstudent[i].name,"Student%d",i+1);
		pstudent[i].num = i+1; 
		list_add( &(pstudent[i].list), &student_list);
	} 
	
	
	list_for_each(pos,&student_list)
	{
		tmp_student = list_entry(pos,struct student,list);
		if(tmp_student->num==3)
			printk("<0>find tmp_student->num==3  sucess\n");
		printk("<0>student %d name: %s\n",tmp_student->num,tmp_student->name);
	}
	
	return 0;
}


static void __exit mylist_exit(void)
{	
	int i ;
	/* ʵ�飺��for����list_for_each������ɾ����㣬�۲�Ҫ���������󣬲����ǽ���취 */
	for(i=0;i<5;i++)
	{
		list_del(&(pstudent[i].list));     
	}
	
	kfree(pstudent);
}

module_init(mylist_init);
module_exit(mylist_exit);

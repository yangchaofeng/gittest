#include <linux/init.h>   
#include <linux/module.h>   
  
  
static int __init hello_init(void)  
{  
    printk("<0> Hello, 2016!\n");  
    return 0;  
}  
  
static void __exit hello_exit(void)  
{  
    printk("<0> Bye, 2016!\n");  
}  
  
module_init(hello_init);  
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL"); 

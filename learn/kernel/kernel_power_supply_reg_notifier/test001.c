#include <linux/init.h>   
#include <linux/module.h>   
 
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/sched.h>
#include <linux/kthread.h>
#include <linux/delay.h>
#include <linux/module.h>
#include <linux/init.h>
#include <linux/proc_fs.h>
#include <linux/string.h>
#include <linux/uaccess.h> 
#include <linux/platform_device.h>

#include <linux/power_supply.h>
#include <linux/workqueue.h>
struct workqueue_struct *lcd_workqueue;
struct notifier_block charger_notifier;
struct delayed_work lcd_bist_work;


static bool lcd_get_charger_ststus(void)
{
	static struct power_supply *batt_psy;
	union power_supply_propval val = { 0, };
	bool status = false;

	if (batt_psy == NULL)
		batt_psy = power_supply_get_by_name("battery");
	if (batt_psy) {
		batt_psy->desc->get_property(batt_psy, POWER_SUPPLY_PROP_STATUS, &val);
	}
	if ((val.intval == POWER_SUPPLY_STATUS_CHARGING) ||
		(val.intval == POWER_SUPPLY_STATUS_FULL)) {
		status = true;
	} else {
		status = false;
	}
	printk("charger status:%d", status);
	return status;
}
static void lcd_bist_work_detect_charger(struct work_struct *work)
{
	//bool charger_mode_old = ts->charger_mode;

	lcd_get_charger_ststus();

}
static int lcd_charger_notify_call(struct notifier_block *nb, unsigned long event, void *data)
{
	struct power_supply *psy = data;

	if (event != PSY_EVENT_PROP_CHANGED) {
		return NOTIFY_DONE;
	}

	if ((strcmp(psy->desc->name, "usb") == 0)
	    || (strcmp(psy->desc->name, "ac") == 0)) {
		if (delayed_work_pending(&lcd_bist_work)) {
			return NOTIFY_DONE;
		}
		queue_delayed_work(lcd_workqueue, &lcd_bist_work, msecs_to_jiffies(500));
	}

	return NOTIFY_DONE;
}
static int __init hello_init(void)  
{ 
    printk("<0> Hello, 2021 0410 V000! \n"); 

	lcd_workqueue = create_singlethread_workqueue("lcd bist workqueue");
	INIT_DELAYED_WORK(&lcd_bist_work, lcd_bist_work_detect_charger);

	charger_notifier.notifier_call = lcd_charger_notify_call;
	power_supply_reg_notifier(&charger_notifier);


	queue_delayed_work(lcd_workqueue, &lcd_bist_work, msecs_to_jiffies(1000));

	msleep(20 * 1000);


	printk("2021 0410, hello_init end!\n"); 
    return 0;  
}  
  
static void __exit hello_exit(void)  
{
    printk("<0> Bye, 2021 0409 end!\n");  
}  
  
module_init(hello_init);  
module_exit(hello_exit);
MODULE_LICENSE("Dual BSD/GPL"); 
